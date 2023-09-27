/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>
#include "qspi.h"
#include "HALhwio.h"
#include "hwio_periph.h"
#include "qcc710.h"
#include "core_cm3.h"
#include "qapi_task.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define SHARED_RAM_START                  0x20000000
#define SHARED_RAM_END                    0x2001FFFF
#define TWO_SAME_SHARED_RAM_DISTANCE      0x7E00000
#define DMA_ADDRESS_CONVERT(__Addr__)     ((((__Addr__) >= SHARED_RAM_START) && ((__Addr__) <= SHARED_RAM_END)) ? ((__Addr__) - TWO_SAME_SHARED_RAM_DISTANCE) : (__Addr__))

#define INT_TO_PTR(__x__)                 ((void *)(uint32_t)(__x__))

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of QSPI transfer direction.
*/
typedef enum
{
    QSPI_MASTER_READ_E,    /**< QSPI read. */
    QSPI_MASTER_WRITE_E    /**< QSPI write. */
} QSPI_TransferDir_t;

/**
   Structur representing the QSPI descriptors.
*/
typedef struct QSPI_Descriptor_s
{
    uint32_t DataAddress;         /**< Descriptor offset  0 = data address[ 7: 0],
                                       descriptor offset  1 = data address[15: 8],
                                       descriptor offset  2 = data address[23:16],
                                       descriptor offset  3 = data address[31:24]. */
    uint32_t NextDescriptor;      /**< Descriptor offset  4 = next descriptor[ 7: 0],
                                       descriptor offset  5 = next descriptor[15: 8],
                                       descriptor offset  6 = next descriptor[23:16],
                                       descriptor offset  7 = next descriptor[31:24]. */
    uint32_t Direction:1;         /**< Descriptor offset  8 = mode/dir. */
    uint32_t MultiIoMode:3;
    uint32_t Reserved1:4;
    uint32_t Fragment:1;          /**< Descriptor offset  9 = fragment. */
    uint32_t Reserved2:7;
    uint32_t Length:16;           /**< Descriptor offset 10 = transfer length[ 7:0],
                                       descriptor offset 11 = transfer length[15:8]. */
    uint32_t BounceSrc;
    uint32_t BounceDst;
    uint32_t BounceLength;
    uint32_t Padding[2];
} QSPI_Descriptor_t;

/**
   Structur representing context for QSPI module.
*/
typedef struct QSPI_Context_s
{
    QSPI_TransferMode_t TransferMode;/**< Record transfer mode. */
    uint8_t            *DmaFreePtr;  /**< Dma free buffer pointer. */
    QSPI_Isr_CB_t       IsrCB;       /**< User registered isr callback. */
    void               *UserParam;   /**< User specified parameter for the callback function. */
} QSPI_Context_t;

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

static QSPI_Descriptor_t QSPI_DmaDescriptors[8] __attribute__((aligned(32)));
static uint8_t QSPI_DmaBuffer[32*4] __attribute__((aligned(32)));
static QSPI_Descriptor_t *QSPI_DmaChain = NULL;
static QSPI_Context_t QSPI_Context;

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
#ifdef FLASH_PIO
/**
   @brief Read data to the RX FIFO.

   @param[in] Ptr       The pointer stored read data.
   @param[in] NumBytes  Total number of data to read.

   @return The number of data actually read.
*/
static uint32_t QSPI_ServiceRxFifo(uint8_t *Ptr, uint32_t NumBytes)
{
    uint32_t FullWords = NumBytes >> 2;
    uint32_t PartialBytes = NumBytes & 0x03;
    uint32_t RdFifoWrCntStatus;
    uint8_t  BytesInFifo;
    uint8_t  WordsInFifo;
    uint32_t WordsToRead;
    uint32_t BytesToRead;
    uint32_t WordValue;
    uint32_t i;

    RdFifoWrCntStatus = HWIO_PERIPH_QSPI_RD_FIFO_STATUS_INM(PERIPH_QSPI_REG_BASE,
                                                            HWIO_PERIPH_QSPI_RD_FIFO_STATUS_WR_CNTS_BMSK);
    BytesInFifo = RdFifoWrCntStatus >> HWIO_PERIPH_QSPI_RD_FIFO_STATUS_WR_CNTS_SHFT;
    WordsInFifo = BytesInFifo >> 2;

    WordsToRead = (WordsInFifo < FullWords) ? (WordsInFifo) : (FullWords);
    BytesToRead = (BytesInFifo < NumBytes)  ? (0) : (PartialBytes);

    for (i = 0; i < WordsToRead; i++)
    {
        WordValue = HWIO_PERIPH_QSPI_RD_FIFOn_INI(PERIPH_QSPI_REG_BASE, 0);
        *(uint32_t *)Ptr = WordValue;  // ptr is word aligned
        Ptr += 4;
    }

    if (BytesToRead)
    {
        WordValue = HWIO_PERIPH_QSPI_RD_FIFOn_INI(PERIPH_QSPI_REG_BASE, 0);
        for (i = 0; i < BytesToRead; i++)
        {
            Ptr[i] = (uint8_t)(WordValue >> i * 8);
        }
    }

    return(WordsToRead * 4 + BytesToRead);
}

/**
   @brief Write data to the TX FIFO.

   @param[in] Ptr       The pointer stored data to be written.
   @param[in] NumBytes  Total number of data to be written.

   @return The number of data actually been written.
*/
static uint32_t QSPI_ServiceTxFifo(uint8_t *Ptr, uint32_t NumBytes)
{
    uint32_t FullWords = NumBytes >> 2;
    uint32_t PartialBytes = NumBytes & 0x03;
    uint32_t PioWrFifoStatus;
    uint32_t RoomInBytes;
    uint32_t RoomInWords;
    uint32_t WordsToSend;
    uint32_t BytesToSend;
    uint32_t WordValue;
    uint32_t i;

    PioWrFifoStatus = HWIO_PERIPH_QSPI_PIO_TRANSFER_STATUS_INM(PERIPH_QSPI_REG_BASE,
                                                               HWIO_PERIPH_QSPI_PIO_TRANSFER_STATUS_WR_FIFO_BYTES_BMSK);

    RoomInBytes = PioWrFifoStatus >> HWIO_PERIPH_QSPI_PIO_TRANSFER_STATUS_WR_FIFO_BYTES_SHFT;
    RoomInWords = RoomInBytes >> 2;

    WordsToSend = (FullWords > RoomInWords) ? (RoomInWords) : (FullWords);
    BytesToSend = (NumBytes  > RoomInBytes) ? (0) : (PartialBytes);

    for (i = 0; i < WordsToSend; i++)
    {
        WordValue = *(uint32_t *)Ptr;  // ptr is word aligned
        HWIO_PERIPH_QSPI_PIO_DATAOUT_4BYTE_OUT(PERIPH_QSPI_REG_BASE, WordValue);
        Ptr += 4;
    }

    for (i = 0; i < BytesToSend; i++)
    {
        HWIO_PERIPH_QSPI_PIO_DATAOUT_1BYTE_OUT(PERIPH_QSPI_REG_BASE, *Ptr);
        Ptr++;
    }

    return(WordsToSend * 4 + BytesToSend);
}

/**
   @brief Perform a PIO read transfer using a single transaction.

   @param[in] Buffer             The pointer stored read data.
   @param[in] NumBytes           Total number of data to read.
   @param[in] PioTransferConfig  PIO transfer configurations.
*/
static void QSPI_PioRead(uint8_t *Buffer, uint32_t NumBytes, uint32_t PioTransferConfig)
{
    uint8_t *Ptr = Buffer;
    uint32_t BytesLeft = NumBytes;
    uint32_t BytesRead;

    HWIO_PERIPH_QSPI_PIO_TRANSFER_CONFIG_OUT(PERIPH_QSPI_REG_BASE, PioTransferConfig);
    HWIO_PERIPH_QSPI_PIO_TRANSFER_CONTROL_OUT(PERIPH_QSPI_REG_BASE, NumBytes);

    /* Poll until all data has been read from the RX FIFO. */
    while (BytesLeft)
    {
        BytesRead = QSPI_ServiceRxFifo(Ptr, BytesLeft);
        BytesLeft -= BytesRead;
        Ptr += BytesRead;
    }
}

/**
   @brief Perform a PIO write transfer using a single transaction.

   @param[in] Buffer             The pointer stored data to be written.
   @param[in] NumBytes           Total number of data to be written.
   @param[in] PioTransferConfig  PIO transfer configurations.
*/
static void QSPI_PioWrite(uint8_t *Buffer, uint32_t NumBytes, uint32_t PioTransferConfig)
{
    uint8_t *Ptr = Buffer;
    uint32_t BytesLeft = NumBytes;
    uint32_t BytesWritten;

    /* Clear latched status bits. */
    HWIO_PERIPH_QSPI_MSTR_INT_STATUS_OUT(PERIPH_QSPI_REG_BASE, 0xFFFFFFFF);
    HWIO_PERIPH_QSPI_PIO_TRANSFER_CONFIG_OUT(PERIPH_QSPI_REG_BASE, PioTransferConfig);
    HWIO_PERIPH_QSPI_PIO_TRANSFER_CONTROL_OUT(PERIPH_QSPI_REG_BASE, NumBytes);

    /* Poll until all data has been written to the TX FIFO. */
    while (BytesLeft)
    {
        BytesWritten = QSPI_ServiceTxFifo(Ptr, BytesLeft);
        BytesLeft -= BytesWritten;
        Ptr += BytesWritten;
    }

    /* Poll until transfer completes over the wire. */
    while (1)
    {
        if (HWIO_PERIPH_QSPI_MSTR_INT_STATUS_INM(PERIPH_QSPI_REG_BASE,
                                                 HWIO_PERIPH_QSPI_MSTR_INT_STATUS_TRANSACTION_DONE_BMSK))
        {
            break;
        }
    }
}

/**
   @brief Transfer a chain of descriptors over the bus using PIO mode.

   @param[in] Chain  QSPI descriptor chain to be transfered.
*/
static void QSPI_PioTransferChain(QSPI_Descriptor_t *Chain)
{
    QSPI_Descriptor_t *Desc = Chain;
    qbool_t            Write;
    uint8_t           *Buffer;
    uint32_t           NumBytes;
    uint32_t           PioTransferConfig;

    while (Desc)
    {
        Write = (Desc->Direction == QSPI_MASTER_WRITE_E);
        Buffer = INT_TO_PTR(Desc->DataAddress);
        NumBytes = Desc->Length;
        PioTransferConfig = (Desc->Fragment ? HWIO_PERIPH_QSPI_PIO_TRANSFER_CONFIG_TRANSFER_FRAGMENT_BMSK : 0) |
                            (Desc->MultiIoMode << HWIO_PERIPH_QSPI_PIO_TRANSFER_CONFIG_MULTI_IO_MODE_SHFT) |
                            (Write ? HWIO_PERIPH_QSPI_PIO_TRANSFER_CONFIG_TRANSFER_DIRECTION_BMSK : 0);
        if (Write)
        {
            QSPI_PioWrite(Buffer, NumBytes, PioTransferConfig);
        }
        else
        {
            QSPI_PioRead(Buffer, NumBytes, PioTransferConfig);
        }

        Desc = INT_TO_PTR(Desc->NextDescriptor);
    }
}
#else
/**
   @brief Stub function for transfer a chain of descriptors over the bus using PIO mode.

   @param[in] Chain  QSPI descriptor chain to be transfered.
*/
static void QSPI_PioTransferChain(QSPI_Descriptor_t *Chain)
{
    return;
}
#endif

/**
   @brief Transfer a chain of descriptors over the bus using DMA mode.

   @param[in] Chain    QSPI descriptor chain to be transfered.
   @param[in] DmaMode  QSPI transfer mode.
*/
static void QSPI_DmaTransferChain(QSPI_Descriptor_t *Chain, QSPI_TransferMode_t DmaMode)
{
    QSPI_Descriptor_t *DmaChain;
    QSPI_Descriptor_t *LastChain;

    /* The shared RAM 0x2000XXX and 0x1820XXXX, 0x2001XXXX and 0x1821XXXX are actually
       mapping to the same memory. If DMA source/dest address is in shared ram, DMA can
       only access address at 0x182XXXXX. */
    DmaChain = Chain;
    LastChain = NULL;
    while (DmaChain)
    {
        if (LastChain != NULL)
        {
            LastChain->NextDescriptor = DMA_ADDRESS_CONVERT((uint32_t)DmaChain);
        }
        
        if (DmaChain->DataAddress)
        {
            DmaChain->DataAddress = DMA_ADDRESS_CONVERT(DmaChain->DataAddress);
        }

        LastChain = DmaChain;

        DmaChain = (QSPI_Descriptor_t *)(DmaChain->NextDescriptor);
    }
    
    /* Clear latched status bits. */
    HWIO_PERIPH_QSPI_MSTR_INT_STATUS_OUT(PERIPH_QSPI_REG_BASE, 0xFFFFFFFF);
    HWIO_PERIPH_QSPI_NEXT_DMA_DESC_ADDR_OUT(PERIPH_QSPI_REG_BASE, DMA_ADDRESS_CONVERT((uint32_t)Chain));

    if (DmaMode == QSPI_DMA_POLL_MODE_E)
    {
        while (1)
        {
            if (HWIO_PERIPH_QSPI_MSTR_INT_STATUS_INM(PERIPH_QSPI_REG_BASE,
                                                     HWIO_PERIPH_QSPI_MSTR_INT_STATUS_DMA_CHAIN_DONE_BMSK))
            {
                break;
            }
        }
    }
    else
    {
        /* Enable DMA_CHAIN_DONE interrupt. */
        HWIO_PERIPH_QSPI_MSTR_INT_ENABLE_OUT(PERIPH_QSPI_REG_BASE,
                                             HWIO_PERIPH_QSPI_MSTR_INT_ENABLE_EN_DMA_CHAIN_DONE_BMSK);
    }
}

/**
   @brief Enable/disable DMA mode via QSPI_MSTR_CONFIG register.

   The current transfer mode is cached to avoid unnecessary register access.

   @param[in] EnableDma  Current transfer mode.
*/
static void QSPI_ConfigDmaMode(QSPI_TransferMode_t EnableDma)
{
    if ((EnableDma != QSPI_PIO_MODE_E) && (QSPI_Context.TransferMode == QSPI_PIO_MODE_E))
    {
        HWIO_PERIPH_QSPI_MSTR_CONFIG_OUTM(PERIPH_QSPI_REG_BASE, HWIO_PERIPH_QSPI_MSTR_CONFIG_DMA_ENABLE_BMSK,
                                          HWIO_PERIPH_QSPI_MSTR_CONFIG_DMA_ENABLE_BMSK);
    }
    else if ((EnableDma == QSPI_PIO_MODE_E) && (QSPI_Context.TransferMode != QSPI_PIO_MODE_E))
    {
        HWIO_PERIPH_QSPI_MSTR_CONFIG_OUTM(PERIPH_QSPI_REG_BASE, HWIO_PERIPH_QSPI_MSTR_CONFIG_DMA_ENABLE_BMSK,
                                          0);
    }

    QSPI_Context.TransferMode = EnableDma;
}

/**
   @brief Flush the existing DMA chain to hardware.

   @param[in] DmaMode  QSPI transfer mode.
*/
static void QSPI_FlushChain(QSPI_TransferMode_t DmaMode)
{
    QSPI_Descriptor_t *Desc= QSPI_DmaChain;
    uint8_t           *Src;
    uint8_t           *Dst;
    uint32_t           i;

    /* Configure DMA */
    QSPI_ConfigDmaMode(DmaMode);

    if (DmaMode == QSPI_PIO_MODE_E)
    {
        QSPI_PioTransferChain(QSPI_DmaChain);
    }
    else
    {
        QSPI_DmaTransferChain(QSPI_DmaChain, DmaMode);
    }

    if (DmaMode != QSPI_DMA_INT_MODE_E)
    {
        /* Copy any bounce data from the descriptors to the client buffer (for reads only). */
        while (Desc)
        {
            Src = INT_TO_PTR(Desc->BounceSrc);
            Dst = INT_TO_PTR(Desc->BounceDst);

            for (i = 0; i < Desc->BounceLength; i++)
            {
                Dst[i] = Src[i];
            }

            Desc = INT_TO_PTR(Desc->NextDescriptor);
        }

        QSPI_Context.DmaFreePtr = QSPI_DmaBuffer;
        QSPI_DmaChain = NULL;
    }
}

/**
   @brief Get the last descriptor in the chain.

   @return Returns a pointer to the last descriptor in the chain or Null if no
           chain exists.
*/
static QSPI_Descriptor_t *QSPI_GetLastDescriptor()
{
    QSPI_Descriptor_t *Desc= QSPI_DmaChain;

    if (Desc)
    {
        while (Desc->NextDescriptor)
        {
            Desc = INT_TO_PTR(Desc->NextDescriptor);
        }
    }

    return Desc;
}

/**
   @brief Allocates a new descriptor, adds it to the chain, and returns a pointer to
   the new descriptor.

   If no descriptors are available or there is not enough free space in the DMA buffer
   then the existing chain will be flushed to HW and a new chain will be created.

   @param[in] BytesNeeded  The number of bytes that needed.
   @param[in] DmaMode      The transfer mode.

   @return Returns a pointer to the new descriptor.
*/
static QSPI_Descriptor_t *QSPI_AllocateDescriptor(uint32_t BytesNeeded, QSPI_TransferMode_t DmaMode)
{
    uint32_t           Alignment;
    uint8_t           *FreePtr;
    uint32_t           Room;
    QSPI_Descriptor_t *Current;
    QSPI_Descriptor_t *Next;

    Alignment = (DmaMode != QSPI_PIO_MODE_E) ? 32 : 4;
    FreePtr = QSPI_Context.DmaFreePtr;
    FreePtr = (uint8_t *)(((uint32_t)FreePtr + Alignment -1) & (~(Alignment - 1)));
    Room = QSPI_DmaBuffer + sizeof(QSPI_DmaBuffer) - FreePtr;

    Current = QSPI_GetLastDescriptor();
    if (Current)
    {
        Next = Current + 1;
    }
    else
    {
        Next = &QSPI_DmaDescriptors[0];
    }

    if ((uint8_t *)Next >= (uint8_t *)QSPI_DmaDescriptors + sizeof(QSPI_DmaDescriptors))
    {
        Next = NULL;
    }

    /* Flushing existing chain if necessary */
    if (Room < BytesNeeded || Next == NULL)
    {
        /* Can not use DMA interrupt here. */
        QSPI_FlushChain((DmaMode != QSPI_DMA_INT_MODE_E) ? DmaMode : QSPI_DMA_POLL_MODE_E);
        FreePtr = QSPI_DmaBuffer;
        Current = NULL;
        Next = &QSPI_DmaDescriptors[0];
    }

    /* Populate descriptor */
    memset(Next, 0, sizeof(QSPI_Descriptor_t));
    Next->DataAddress    = BytesNeeded ? (uint32_t)FreePtr : 0;
    Next->Direction      = QSPI_MASTER_READ_E;
    Next->Fragment       = 1;

    if (Current)
    {
        Current->NextDescriptor = (uint32_t)Next;
    }
    else
    {
        QSPI_DmaChain = Next;
    }

    return Next;
}

/**
   @brief Calculate the room available in the last descriptor in the chain (the
   caller must pass in a pointer to the *last* descriptor).

   @param[in] Last  The last descriptor in the chain.

   @return Returns avilable room in the last descriptor.
*/
static uint32_t QSPI_GetAvailableRoom(QSPI_Descriptor_t *Last)
{
    uint8_t *EndOfBuffer = QSPI_DmaBuffer + sizeof(QSPI_DmaBuffer);

    if (INT_TO_PTR(Last->DataAddress) < (void *)QSPI_DmaBuffer ||
        INT_TO_PTR(Last->DataAddress) >= (void *)EndOfBuffer)
    {
        return 0;
    }

    return (uint32_t)(EndOfBuffer - (Last->DataAddress + Last->Length));
}

/**
   @brief Setting descriptors.

   @param[in] Data       The data buffer containing data to write, or as buffer for reading data.
   @param[in] DataBytes  The number of data.
   @param[in] Mode       The multi IO and DDR mode.
   @param[in] Direction  Transfer direction.
   @param[in] DmaMode    QSPI transfer mode.
*/
static void QSPI_SetDescriptor(uint8_t *Data, uint32_t DataBytes, QSPI_Mode_t Mode, QSPI_TransferDir_t Direction,  QSPI_TransferMode_t DmaMode)
{
    QSPI_Descriptor_t *Desc;
    uint8_t           *Ptr;
    uint32_t           i;

    if (DataBytes == 0 || Data == NULL)
    {
        return;
    }

    Desc = QSPI_GetLastDescriptor();

    /* Check if we can add to the last descriptor else allocate a new one */
    if ((Desc == NULL) ||
        (Desc->Direction != Direction) ||
        (Desc->MultiIoMode != Mode) ||
        (QSPI_GetAvailableRoom(Desc) < DataBytes))
    {
        Desc = QSPI_AllocateDescriptor(DataBytes, DmaMode);
        Desc->Direction = Direction;
        Desc->MultiIoMode = Mode;
    }

    Ptr = INT_TO_PTR(Desc->DataAddress + Desc->Length);

    if (Direction == QSPI_MASTER_WRITE_E)
    {
        for (i = 0; i < DataBytes; i ++)
        {
            Ptr[i] = Data[i];
        }
    }
    else
    {
        Desc->BounceSrc = (uint32_t)Ptr;
        Desc->BounceDst = (uint32_t)Data;
        Desc->BounceLength = DataBytes;
    }

    Desc->Length += DataBytes;
    QSPI_Context.DmaFreePtr = INT_TO_PTR(Desc->DataAddress + Desc->Length);
}

/**
   @brief Queue the 1-byte command opcode (cmd-ADDR-dummy-data).

   @param[in] Opcode   The command opcode
   @param[in] CmdMode  The command mode.
   @param[in] DmaMode  QSPI transfer mode.
*/
static void QSPI_QueueOpcode(uint8_t Opcode, QSPI_Mode_t CmdMode, QSPI_TransferMode_t DmaMode)
{
    QSPI_SetDescriptor(&Opcode, 1, CmdMode, QSPI_MASTER_WRITE_E, DmaMode);
}

/**
   @brief Queue the 3-byte or 4-byte address (cmd-ADDR-dummy-data).

   @param[in] Addr       The address.
   @param[in] AddrBytes  The address bytes.
   @param[in] AddrMode   The address mode.
   @param[in] DmaMode    QSPI transfer mode.
*/
static void QSPI_QueueAddr(uint32_t Addr, uint8_t AddrBytes, QSPI_Mode_t AddrMode, QSPI_TransferMode_t DmaMode)
{
    uint8_t WriteAddr[4];
    uint8_t i;

    if (AddrBytes == 0)
    {
        return;
    }

    for (i = AddrBytes; i > 0; i--)
    {
        WriteAddr[AddrBytes - i] = (uint8_t)(Addr >> (i - 1) *8);
    }

    QSPI_SetDescriptor(WriteAddr, (uint32_t)AddrBytes, AddrMode, QSPI_MASTER_WRITE_E, DmaMode);
}

/**
   @brief Queue the dummy bytes to generate dummy clock cycles (cmd-addr-DUMMY-data).

   Note that we must use a write to drive DQ3 (HOLD_N) high when generating dummy clock cycles
   in 4-wire mode.  If we use a read then we will release DQ2 (WP_N) and DQ3 (HOLD_N) which will
   cause them to go low (assert).  This will cause the slave to ignore all but one of the dummy
   clock cycles (the first one gets through because it takes some time for HOLD_N to go low).

   @param[in] DummyClocks  The dummy clock cycles.
   @param[in] DmaMode      QSPI transfer mode.
*/
static void QSPI_QueueDummy(uint8_t DummyClocks, QSPI_TransferMode_t DmaMode)
{
    QSPI_Descriptor_t *Desc;
    uint8_t           *Ptr = NULL;
    uint32_t           i;
    uint32_t           DummyBytes;
    uint32_t           ClocksPerBytes;
    uint32_t           Remainder;

    if (DummyClocks == 0)
    {
        return;
    }

    Desc = QSPI_GetLastDescriptor();

    /* Check if we can add to the last descriptor else allocate a new one */
    if (Desc && Desc->Direction == QSPI_MASTER_WRITE_E)
    {
        switch (Desc->MultiIoMode)
        {
            case QSPI_SDR_1BIT_E:
                ClocksPerBytes = 8;
                break;

            case QSPI_SDR_2BIT_E:
                ClocksPerBytes = 4;
                break;

            case QSPI_SDR_4BIT_E:
                ClocksPerBytes = 2;
                break;

            case QSPI_DDR_1BIT_E:
                ClocksPerBytes = 4;
                break;

            case QSPI_DDR_2BIT_E:
                ClocksPerBytes = 2;
                break;

            case QSPI_DDR_4BIT_E:
                ClocksPerBytes = 1;
                break;

            default:
                return;
        }

        DummyBytes = DummyClocks / ClocksPerBytes;
        Remainder = DummyClocks % ClocksPerBytes;

        if (Remainder == 0 && QSPI_GetAvailableRoom(Desc) >= DummyBytes)
        {
            Ptr = INT_TO_PTR(Desc->DataAddress + Desc->Length);
        }
    }
    if (Ptr == NULL)
    {
        DummyBytes = DummyClocks;
        Desc = QSPI_AllocateDescriptor(DummyBytes, DmaMode);
        Desc->Direction = QSPI_MASTER_WRITE_E;
        Desc->MultiIoMode = QSPI_DDR_4BIT_E;
        Ptr = INT_TO_PTR(Desc->DataAddress);
    }

    /* Write dummy bytes to descriptor */
    for (i = 0; i < DummyBytes; i++)
    {
        *Ptr++ = 0xFF;
    }

    Desc->Length += DummyBytes;
    QSPI_Context.DmaFreePtr = INT_TO_PTR(Desc->DataAddress + Desc->Length);
}

/**
   @brief Queue direct data. This is data that will be copied directly between the client
          buffer and the hardware (and must be properly aligned).

   @param[in] Data       The data buffer containing data to write, or as buffer for reading data.
   @param[in] DataBytes  The number of data.
   @param[in] DataMode   The data mode.
   @param[in] Write      Write or read, true: write, false: read.
   @param[in] DmaMode    QSPI transfer mode.
*/
static void QSPI_QueueDirectData(uint8_t *Data, uint32_t DataBytes, QSPI_Mode_t DataMode, qbool_t Write, QSPI_TransferMode_t DmaMode)
{
    QSPI_Descriptor_t *Desc;
    uint32_t           ChunkSize;

    while (DataBytes)
    {
        /* Maximum transfer size is 0xFFFF bytes but 0xFFE0 is the largest size that
           maintains 32-byte alignment between chunks. */
        ChunkSize = (DataBytes > 0xFFE0) ? (0xFFE0) : (DataBytes);

        /* Allocate a new descriptor and point it to the client buffer. */
        Desc = QSPI_AllocateDescriptor(0, DmaMode);
        Desc->Direction = Write;
        Desc->MultiIoMode = DataMode;
        Desc->DataAddress = (uint32_t)Data;
        Desc->Length = ChunkSize;

        Data += ChunkSize;
        DataBytes -= ChunkSize;
    }
}

/**
   @brief Queue the data from the client buffer.

   The data may be split into multiple parts to ensure the following:
   1) the buffer starts on a 32-byte boundary (for DMA) or a 4-byte boundary (for PIO)
   2) the buffer ends on a 4-byte boundary (only required for DMA reads)
   3) the buffer is no larger than 65535 (0xFFFF) bytes.
   It is straightforward to handle (3) by splitting the buffer across multiple descriptors.
   Bounce buffers are used to handle (1) and (2).

   @param[in] Data       The data buffer containing data to write, or as buffer for reading data.
   @param[in] DataBytes  The number of data.
   @param[in] DataMode   The data mode.
   @param[in] Write      Write or read, true: write, false: read.
   @param[in] DmaMode    QSPI transfer mode.
*/
static void QSPI_QueueData(uint8_t *Data, uint32_t DataBytes, QSPI_Mode_t DataMode, qbool_t Write, QSPI_TransferMode_t DmaMode)
{
    uint32_t  Alignment;
    uint8_t  *AlignedPtr;
    uint8_t  *EpilogPtr;
    uint32_t  PrologBytes;
    uint32_t  AlignedBytes;
    uint32_t  EpilogBytes;

    if (DataBytes == 0)
    {
        return;
    }

    Alignment = (DmaMode != QSPI_PIO_MODE_E) ? 32 : 4;
    AlignedPtr = (uint8_t *)(((uint32_t)Data + Alignment -1) & (~(Alignment - 1)));
    PrologBytes = ((AlignedPtr - Data) > DataBytes) ? (DataBytes) : (AlignedPtr - Data);
    EpilogBytes = ((DmaMode != QSPI_PIO_MODE_E) && !Write) ? ((DataBytes - PrologBytes) & 0x3) : 0;
    AlignedBytes = DataBytes - PrologBytes - EpilogBytes;
    EpilogPtr = Data + PrologBytes + AlignedBytes;

    if (AlignedBytes == 0)
    {
        /* Combine prolog and epilog if there is nothing between them.  This avoids
           the need to have two bounce buffers in the same descriptor. */
        PrologBytes += EpilogBytes;
        EpilogBytes = 0;
    }
      
    if (PrologBytes)
    {
        QSPI_SetDescriptor(Data, PrologBytes, DataMode, (QSPI_TransferDir_t)Write, DmaMode);
    }
    if (AlignedBytes)
    {
        QSPI_QueueDirectData(AlignedPtr, AlignedBytes, DataMode, Write, DmaMode);
    }
    if (EpilogBytes)
    {
        QSPI_SetDescriptor(EpilogPtr, EpilogBytes, DataMode, (QSPI_TransferDir_t)Write, DmaMode);
    }
}

/**
   @brief Initialize the QSPI registers and put QSPI into a known state.

   @param[in] Config  The QSPI master configurations.
*/
static void QSPI_RegInit(QSPI_MasterConfig_t *Config)
{
    uint32_t SpiMode;
    uint32_t TxDataOeDelay, TxDataDelay;
    uint32_t SblEn;
    uint32_t MstrConfig;

    /* Need to set QSPI_TransferMode to dma disable to ensure the software state is in
       sync with the hardware state in case this function is called more than once. */
    QSPI_Context.TransferMode = QSPI_PIO_MODE_E;
    /* Reinitialize DMA free pointer. */
    QSPI_Context.DmaFreePtr = QSPI_DmaBuffer;

    SpiMode = (Config->ClkPolarity == 0 && Config->ClkPhase == 0) ? 0 :
              (Config->ClkPolarity == 0 && Config->ClkPhase == 1) ? 1 :
              (Config->ClkPolarity == 1 && Config->ClkPhase == 0) ? 2 :
              (Config->ClkPolarity == 1 && Config->ClkPhase == 1) ? 3 :
                                                                    0;

    /* The TX DATA delay is needed for writes in DDR mode using the Micron SPI NOR flash.
       Note that a half cycle of the reference clock is 1/8 cycle of the SPI clock when
       SBL_EN=1 and 1/4 cycle of the SPI clock when SBL_EN=0. */

    TxDataOeDelay = 1;  /* delay half cycle of reference clock. */
    TxDataDelay = 1;  /* delay half cycle of reference clock. */

    SblEn = ((Config->ClkFreq > QSPI_SBL_CLOCK_FREQUENCY) ? 0 : 1);

    MstrConfig = (TxDataOeDelay << HWIO_PERIPH_QSPI_MSTR_CONFIG_TX_DATA_OE_DELAY_SHFT) |
                 (TxDataDelay << HWIO_PERIPH_QSPI_MSTR_CONFIG_TX_DATA_DELAY_SHFT) |
                 (SblEn << HWIO_PERIPH_QSPI_MSTR_CONFIG_SBL_EN_SHFT) |
                 (Config->ChipSelect ? HWIO_PERIPH_QSPI_MSTR_CONFIG_CHIP_SELECT_NUM_BMSK : 0) |
                 (SpiMode << HWIO_PERIPH_QSPI_MSTR_CONFIG_SPI_MODE_SHFT) |
                 (HWIO_PERIPH_QSPI_MSTR_CONFIG_PIN_WPN_BMSK) |
                 (HWIO_PERIPH_QSPI_MSTR_CONFIG_PIN_HOLDN_BMSK) |
                 (HWIO_PERIPH_QSPI_MSTR_CONFIG_FB_CLK_EN_BMSK);

    /* Do not set the CONTINUOUS_MODE bit in RD_FIFO_CONFIG.  If CONTINUOUS_MODE is
       used transfers will hang when we are slow to service the RD_FIFO.  When the
       RD_FIFO is full the QSPI master continues clocking in data over the bus (and
       decrementing REQUEST_COUNT in PIO_TRANSFER_CONTROL) but just drops the data
       with no indication to SW.  This causes the transfer to end before SW has read
       the expected number of bytes from the RD_FIFO. */
    HWIO_PERIPH_QSPI_MSTR_CONFIG_OUT(PERIPH_QSPI_REG_BASE, MstrConfig);
    /* This is the reset state. */
    HWIO_PERIPH_QSPI_AHB_MASTER_CFG_OUT(PERIPH_QSPI_REG_BASE, 0x00001A02);
    /* Disable interrupt. */
    HWIO_PERIPH_QSPI_MSTR_INT_ENABLE_OUT(PERIPH_QSPI_REG_BASE, 0x00000000);
    /* Clear latched status bits. */
    HWIO_PERIPH_QSPI_MSTR_INT_STATUS_OUT(PERIPH_QSPI_REG_BASE, 0xFFFFFFFF);
    HWIO_PERIPH_QSPI_RD_FIFO_CONFIG_OUT(PERIPH_QSPI_REG_BASE, 0x00000000);
    HWIO_PERIPH_QSPI_RD_FIFO_RESET_OUT(PERIPH_QSPI_REG_BASE, HWIO_PERIPH_QSPI_RD_FIFO_RESET_RESET_FIFO_BMSK);
}

/**
   @brief QSPI interrupt handler.
*/
void QSPI_IntHandler(void)
{
    QSPI_Descriptor_t *Desc= QSPI_DmaChain;
    uint8_t           *Src;
    uint8_t           *Dst;
    uint32_t           i;
    uint32_t           Status = 0;

    HWIO_PERIPH_QSPI_MSTR_INT_ENABLE_OUT(PERIPH_QSPI_REG_BASE, 0x00000000);

    if (QSPI_Context.TransferMode == QSPI_DMA_INT_MODE_E)
    {
        Status = HWIO_PERIPH_QSPI_MSTR_INT_STATUS_IN(PERIPH_QSPI_REG_BASE);
        HWIO_PERIPH_QSPI_MSTR_INT_STATUS_OUT(PERIPH_QSPI_REG_BASE, Status);
        
        if (Status & HWIO_PERIPH_QSPI_MSTR_INT_STATUS_DMA_CHAIN_DONE_BMSK)
        {
            /* Copy any bounce data from the descriptors to the client buffer (for reads only). */
            while (Desc)
            {
                Src = INT_TO_PTR(Desc->BounceSrc);
                Dst = INT_TO_PTR(Desc->BounceDst);

                for (i = 0; i < Desc->BounceLength; i++)
                {
                    Dst[i] = Src[i];
                }

                Desc = INT_TO_PTR(Desc->NextDescriptor);
            }

            QSPI_Context.DmaFreePtr = QSPI_DmaBuffer;
            QSPI_DmaChain = NULL;

            /* Call user registered callback. */
            if (QSPI_Context.IsrCB)
            {
                QSPI_Context.IsrCB(Status, QSPI_Context.UserParam);
            }
        }
    }
}

/**
   @brief Initialize the QSPI and the HW it depends on (clocks, GPIOs).

   This function can be called between transfers to change the bus clock
   frequency, chip select, etc.

   @param[in] Config  The QSPI master configurations.

   @return TRUE on success or FALSE on failure.
*/
qbool_t QSPI_Init(QSPI_MasterConfig_t *Config)
{
    memset(&QSPI_Context, 0, sizeof(QSPI_Context_t));

    /* Enable QSPI ref clock and HCLK. */
    qapi_TSK_Enter_Critical();    
    HWIO_PERIPH_CLOCK_CFG_OUTM(PERIPH_MOD_CSR_REG_BASE,
                               (HWIO_PERIPH_CLOCK_CFG_QSPI_REF_CLK_EN_BMSK | HWIO_PERIPH_CLOCK_CFG_QSPI_HCLK_EN_BMSK),
                               (HWIO_PERIPH_CLOCK_CFG_QSPI_REF_CLK_EN_BMSK | HWIO_PERIPH_CLOCK_CFG_QSPI_HCLK_EN_BMSK));
    qapi_TSK_Exit_Critical();    

    /* Reset register */
    QSPI_RegInit(Config);

    /* Regiter ISR callback. */
    QSPI_Context.IsrCB = Config->IsrCB;
    QSPI_Context.UserParam = Config->UserParam;

    /* Clear pending interrupt bit. */
    NVIC_ClearPendingIRQ(QSPI_IRQn);
    /* Enable QSPI interrupt. */
    NVIC_EnableIRQ(QSPI_IRQn);

    return true;
}

/**
   @brief Set QSPI command parameters.

   @param[in] Cmd          Pointer to the command.
   @param[in] Opcode       The instruction code.
   @param[in] AddrBytes    The address bytes.
   @param[in] DummyClocks  The dummy clock cycles.
   @param[in] CmdMode      The instruction mode.
   @param[in] AddrMode     The address mode.
   @param[in] DataMode     The data mode.
   @param[in] Write        Read or Write, true: write, false: read.

   @return TRUE on success or FALSE on failure.
*/
qbool_t QSPI_SetCmd(QSPI_Cmd_t *Cmd, uint8_t Opcode, uint8_t AddrBytes, uint8_t DummyClocks, QSPI_Mode_t CmdMode, QSPI_Mode_t AddrMode, QSPI_Mode_t DataMode, qbool_t Write)
{
    if (Cmd == NULL)
    {
        return false;
    }

    memset (Cmd, 0, sizeof(QSPI_Cmd_t));
    Cmd->Opcode = Opcode;
    Cmd->AddrBytes = AddrBytes;
    Cmd->DummyClocks = DummyClocks;
    Cmd->CmdMode = CmdMode;
    Cmd->AddrMode = AddrMode;
    Cmd->DataMode = DataMode;
    Cmd->Write = Write;

    return true;
}

/**
   @brief Send QSPI command

   @param[in]    Cmd        The command configuration.
   @param[in]    Addr       The address for the command.
   @param[inout] Data       The data buffer containing data to write,
                            or as buffer for reading data.
   @param[in]    DataBytes  The number of data to write or read.
   @param[in]    EnableDma  The command transfer mode.

   @return TRUE on success or FALSE on failure.
*/
qbool_t QSPI_Cmd(QSPI_Cmd_t *Cmd, uint32_t Addr, uint8_t *Data, uint32_t DataBytes, QSPI_TransferMode_t EnableDma)
{
    QSPI_Descriptor_t *Last;

    if (Cmd == NULL || Cmd->AddrBytes > 4 || Cmd->DummyClocks > 16)
    {
        return false;
    }

    QSPI_QueueOpcode(Cmd->Opcode, Cmd->CmdMode, EnableDma);
    QSPI_QueueAddr(Addr, Cmd->AddrBytes, Cmd->AddrMode, EnableDma);
    QSPI_QueueDummy(Cmd->DummyClocks, EnableDma);
    QSPI_QueueData(Data, DataBytes, Cmd->DataMode, Cmd->Write, EnableDma);

    Last = QSPI_GetLastDescriptor();
    Last->Fragment = 0;
    QSPI_FlushChain(EnableDma);

    return true;
}


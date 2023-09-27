/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "HALhwio.h"
#include "hwio_periph.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define FLD_BMSK(reg, field) HWIO_PERIPH_##reg##_##field##_BMSK

#define FLD_SHFT(reg, field) HWIO_PERIPH_##reg##_##field##_SHFT

#define FLD_SET(reg, field, data) \
    (((uint32_t) data << (uint32_t) FLD_SHFT(reg, field)) & (uint32_t) FLD_BMSK(reg, field))

#define FLD_GET(data, reg, field) \
    ((data & FLD_BMSK(reg, field)) >> FLD_SHFT(reg, field))


#define REG_IN(base, hwiosym) HWIO_PERIPH_##hwiosym##_IN(base)

#define REG_OUT(base, hwiosym, value) HWIO_PERIPH_##hwiosym##_OUT(base, value)

#define REG_INI(base, hwiosym, n) HWIO_PERIPH_##hwiosym##_INI(base, n)

#define REG_OUTI(base, hwiosym, n, value) HWIO_PERIPH_##hwiosym##_OUTI(base, n, value)

#define REG_INF(base, hwiosym, field) \
    ((REG_IN(base, hwiosym) & FLD_BMSK(hwiosym, field)) >> FLD_SHFT(hwiosym, field))

#define REG_OUTF(base, hwiosym, field, data) \
    REG_OUT(base, hwiosym, ((REG_IN(base, hwiosym) & ~(FLD_BMSK(hwiosym, field))) | \
                ((data << FLD_SHFT(hwiosym, field)) & FLD_BMSK(hwiosym, field))))


#define GENI4_CFG_REG_BASE           0x0
#define GENI4_IMAGE_REGS_REG_BASE    0x100
#define GENI4_DATA_REG_BASE          0x600
#define QUPV3_SE_DMA_REG_BASE        0xC00
#define GENI4_IMAGE_REG_BASE         0x1000
#define QUPV3_SEC_REG_BASE           0x2000



/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/


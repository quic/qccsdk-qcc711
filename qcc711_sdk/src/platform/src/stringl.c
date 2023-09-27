/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <string.h>
#include <stddef.h>

/**
   @brief Safe version of memcpy.

   This function will copy data from the source buffer to the dest buffer.  The
   amount of data copied with be the minimum of dest_size and source_size.

   @param[out] Dest        Destination buffer for the copy.
   @param[in]  DestSize    Size of the destination buffer.
   @param[in]  Src         Source buffer for the copy.
   @param[in]  SrcSize     Size of the source buffer.

   @return The number of bytes actually copied.
*/
size_t memscpy(void* Dest, size_t DestSize, const void *Src, size_t SrcSize)
{
   if(SrcSize > DestSize)
   {
      SrcSize = DestSize;
   }

   memcpy(Dest, Src, SrcSize);

   return(SrcSize);
}

/**
   @brief Safe version of memmove.

   This function will move data from the source buffer to the dest buffer,
   accounting for possible overlap.  The amount of data moved with be the
   minimum of dest_size and source_size.

   @param[out] Dest        Destination buffer for the move.
   @param[in]  DestSize    Size of the destination buffer.
   @param[in]  Src         Source buffer for the move.
   @param[in]  SrcSize     Size of the source buffer.

   @return The number of bytes actually moved.
*/
size_t memsmove(void* Dest, size_t DestSize, const void *Src, size_t SrcSize)
{
   if(SrcSize > DestSize)
   {
      SrcSize = DestSize;
   }

   memmove(Dest, Src, SrcSize);

   return(SrcSize);
}

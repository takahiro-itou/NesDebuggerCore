//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ----   NES Debugger Project   ----                  **
**                                                                      **
**          Copyright (C), 2026-2026, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Interface of MemoryTable structure.
**
**      @file       NesMan/MemoryTable.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_MEMORY_TABLE_H )
#    define   NESDBG_NESMAN_INCLUDED_MEMORY_TABLE_H

#if !defined( NESDBG_COMMON_INCLUDED_NESDBG_TYPES_H )
#    include    "NesDbg/Common/NesDbgTypes.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//  クラスの前方宣言。  //


//========================================================================
//
//    MemoryTable  structure/
//

struct  MemoryTable
{
    LpByteWriteBuf      addr;
    GuestMemoryAddress  size;
    GuestMemoryAddress  mask;
};

//========================================================================
//
//    Memory Size & Mask.
//

enum {
    /**   0x8000 - 0xFFFF : ROM.    */
    MEM_SIZE_ROM    = 0x00008000;
    MEM_MASK_ROM    = 0x00007FFF;
};

enum {
    MEM_BLOCK_WRAM  = 0,
    MEM_BLOCK_ROM0  = 1,
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

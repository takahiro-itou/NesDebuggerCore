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
**      An Implementation of Dis6502 class.
**
**      @file       NesMan/Dis6502.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "NesDbg/NesMan/MemoryManager.h"

#include    "Dis6502.h"
#include    "InstTable.h"

#include    <ostream>
#include    <sstream>


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

CONSTEXPR_VAR   const   MnemonicMap
dis6502Mnemonics[] = {
    //  NOP 系  //
    { 0xFF, 0x82, "DOP" },
    { 0xFF, 0xC2, "DOP" },
    { 0xFF, 0xE2, "DOP" },
};

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    Dis6502  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

Dis6502::Dis6502()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

Dis6502::~Dis6502()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//----------------------------------------------------------------
//    ニーモニックを表示する。
//

std::ostream  &
Dis6502::writeMnemonic(
        std::ostream       &outStr,
        GuestMemoryAddress  gmAddr,
        GuestMemoryAddress &gmNext)  const
{
    char    buf[256] = { 0 };
    size_t  len = 0;
    size_t  rem = sizeof(buf) - 1;
    char *  dst = buf;

    const uint32_t  opeCode = this->m_pManMem->readMemory<uint32_t>(gmAddr);
    const MnemonicMap *  oc = dis6502Mnemonics;

    const  BtByte   opSize  = g_opeCodeSize[opeCode & 0xFF];
    gmNext  = gmAddr + opSize;

    len = snprintf(dst, rem, "%04x:   %02x", gmAddr, (opeCode & 0xFF));
    dst += len;
    rem -= len;

    uint32_t    ocTemp  = (opeCode >> 8);
    switch ( opSize ) {
    case  3:
        len = snprintf(dst, rem, " %02x", (ocTemp & 0xFF));
        dst += len;
        rem -= len;
        ocTemp  >>= 8;
        //  no break;
    case  2:
        len = snprintf(dst, rem, " %02x", (ocTemp & 0xFF));
        dst += len;
        rem -= len;
        ocTemp  >>= 8;
        //  no break;
    default:
        break;
    }

    outStr  <<  buf;
    return ( outStr );
}

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

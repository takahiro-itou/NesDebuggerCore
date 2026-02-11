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
    { 0x000000FF, 0x00000082, "DOP" },
    { 0x000000FF, 0x000000C2, "DOP" },
    { 0x000000FF, 0x000000E2, "DOP" },

    { 0x000000FF, 0x00000000, "BRK" },
    { 0x000000FF, 0x00000020, "JSR" },
    { 0x000000FF, 0x00000040, "RTI" },
    { 0x000000FF, 0x00000060, "RTS" },
    { 0x000000FF, 0x00000080, "DOP" },
    { 0x000000FF, 0x000000A0, "LDY" },
    { 0x000000FF, 0x000000C0, "CPY" },
    { 0x000000FF, 0x000000E0, "CPX" },

    { 0x000000FF, 0x00000010, "BPL" },
    { 0x000000FF, 0x00000030, "BMI" },
    { 0x000000FF, 0x00000050, "BVC" },
    { 0x000000FF, 0x00000070, "BVS" },
    { 0x000000FF, 0x00000090, "BCC" },
    { 0x000000FF, 0x000000B0, "BCS" },
    { 0x000000FF, 0x000000D0, "BNE" },
    { 0x000000FF, 0x000000F0, "BEQ" },

    { 0x000000FF, 0x00000008, "PHP" },
    { 0x000000FF, 0x00000028, "PLP" },
    { 0x000000FF, 0x00000048, "PHA" },
    { 0x000000FF, 0x00000068, "PLA" },
    { 0x000000FF, 0x00000088, "DEY" },
    { 0x000000FF, 0x000000A8, "TAY" },
    { 0x000000FF, 0x000000C8, "INY" },
    { 0x000000FF, 0x000000E8, "INX" },

    { 0x000000FF, 0x00000018, "CLC" },
    { 0x000000FF, 0x00000038, "SEC" },
    { 0x000000FF, 0x00000058, "CLI" },
    { 0x000000FF, 0x00000078, "SED" },
    { 0x000000FF, 0x00000098, "TYA" },
    { 0x000000FF, 0x000000B8, "CLV" },
    { 0x000000FF, 0x000000D8, "CLD" },
    { 0x000000FF, 0x000000F8, "SED" },

    { 0x00000000, 0x00000000, "[ ??? ]" },
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
    for ( ; (opeCode & oc->mask) != oc->cval; ++ oc );

    const  BtByte   opSize  = g_opeCodeSize[opeCode & 0x000000FF];
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
    len = dst - buf;
    while ( len < 20 ) {
        * (dst ++)  = ' ';
        ++ len;
    }
    outStr  <<  buf;

    const  char  *  src = oc->mnemonic;
    len = snprintf(buf, sizeof(buf), src);
    outStr  <<  buf  <<  std::endl;

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

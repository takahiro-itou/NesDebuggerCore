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

#include    "Dis6502.h"
#include    "InstTable.h"


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

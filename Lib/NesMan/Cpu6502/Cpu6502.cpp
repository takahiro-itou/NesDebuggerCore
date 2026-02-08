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
**      An Implementation of Cpu6502 class.
**
**      @file       NesMan/Cpu6502.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "Cpu6502.h"


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    Cpu6502  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

Cpu6502::Cpu6502(
        NesManager    & manNes,
        MemoryManager & manMem)
    : Super(manNes, manMem)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

Cpu6502::~Cpu6502()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

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

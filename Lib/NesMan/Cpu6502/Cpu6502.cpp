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

#include    "NesDbg/NesMan/MemoryManager.h"
#include    "InstTable.h"
#include    "AddressingMode.h"
#include    "Instructions.inl"

#include    <iostream>


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

//----------------------------------------------------------------
//    現在の命令を実行する。
//

InstExecResult
Cpu6502::executeNextInst()
{
    char    buf[128];

    const  GuestMemoryAddress oldPC = mog_cpuRegs.PC;
    const  OpeCode  opeCode =
        this->m_manMem.readMemory<OpeCode>(oldPC);
    const  BtByte   ocInst  = (opeCode & 0x000000FF);
    const  GuestMemoryAddress   opSize  = g_opeCodeSize[ocInst];

    //  プログラムカウンタを更新する。  //
    mog_cpuRegs.PC  += opSize;

    //  クロックサイクル数を更新する。  //
    mog_ctrStep.totalCycles += g_opeCodeCycles[ocInst];
    ++ mog_ctrStep.numOpeCodes;

    FnInst  pfInst  = s_cpuInstTable[ocInst];
    InstExecResult  ret = InstExecResult::UNDEFINED_OPECODE;
    if ( pfInst != nullptr ) {
        ret = (this ->* pfInst)(opeCode >> 8);
    }
    if ( ret == InstExecResult::UNDEFINED_OPECODE ) {
        snprintf(buf, sizeof(buf) - 1,
                "Undefined Instruction %02X at %04X\n",
                 ocInst, oldPC);
        std::cerr   <<  buf;
        return ( InstExecResult::UNDEFINED_OPECODE );
    }

    return ( ret );
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

//----------------------------------------------------------------
//    フラグを設定する。
//

inline  void
Cpu6502::setupNZFlags(
        const  RegType  value)
{
    mog_cpuRegs.P   &= ~(FLAG_N | FLAG_Z);
    mog_cpuRegs.P   |= (value & FLAG_N);
    mog_cpuRegs.P   |= (value ? 0: FLAG_Z);
}

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

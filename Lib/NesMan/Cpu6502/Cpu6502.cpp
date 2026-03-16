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
#include    "NesDbg/NesMan/NesManager.h"

#include    "InstTable.h"
#include    "AddressingMode.h"
#include    "ArithmeticLogic.h"
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
//    BRK 割り込みを実行する。
//

InstExecResult
Cpu6502::execBrk(
        const  OpeCode  opeCode)
{
    pushValue((mog_cpuRegs.PC >> 8) & 0x000000FF);
    pushValue((mog_cpuRegs.PC     ) & 0x000000FF);

    pushValue( (mog_cpuRegs.P) | (FLAG_R | FLAG_B) );
    mog_cpuRegs.P   |= FLAG_I;

#if defined( _DEBUG )
    std::cerr   <<  "INFO : Interrupt BRK\n";
#endif

    //  サイクル数の増加はテーブルを参照して既に実行した。  //
    //  addCycles(7);
    mog_cpuRegs.PC  = this->m_manMem.readMemory<BtWord>(0xFFFE);

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    IRQ 割り込みを実行する。
//

InstExecResult
Cpu6502::execIrq(
        const  OpeCode  opeCode)
{
    if ( mog_cpuRegs.P & FLAG_I ) {
        //  割り込みが禁止されている。  //
        return ( InstExecResult::SUCCESS_CONTINUE );
    }

    pushValue((mog_cpuRegs.PC >> 8) & 0x000000FF);
    pushValue((mog_cpuRegs.PC     ) & 0x000000FF);

    pushValue( (mog_cpuRegs.P & ~FLAG_B) | (FLAG_R) );
    mog_cpuRegs.P   |= FLAG_I;

#if defined( _DEBUG )
    std::cerr   <<  "INFO : Interrupt IRQ\n";
#endif

    addCycles(7);
    mog_cpuRegs.PC  = this->m_manMem.readMemory<BtWord>(0xFFFE);

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    NMI 割り込みを実行する。
//

InstExecResult
Cpu6502::execNmi(
        const  OpeCode  opeCode)
{
    pushValue((mog_cpuRegs.PC >> 8) & 0x000000FF);
    pushValue((mog_cpuRegs.PC     ) & 0x000000FF);

    pushValue( (mog_cpuRegs.P & ~FLAG_B) | (FLAG_R) );
    mog_cpuRegs.P   |= FLAG_I;

#if defined( _DEBUG )
    std::cerr   <<  "INFO : Interrupt NMI\n";
#endif

    addCycles(7);
    mog_cpuRegs.PC  = this->m_manMem.readMemory<BtWord>(0xFFFA);
    this->m_flagIrq &= ~IRQ::IRQ_NMI;

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    現在の命令を実行する。
//

InstExecResult
Cpu6502::executeNextInst()
{
    char    buf[128];

#if defined( _DEBUG )
    snprintf(buf, sizeof(buf), "IRQ : %02X\n", this->m_flagIrq);
    std::cerr   <<  buf;
#endif

    //  割り込みフラグが立っていればそれを処理する。    //
    if ( this->m_flagIrq & IRQ::IRQ_NMI ) {
        return  execNmi(0xFFFA);
    }
    if ( this->m_flagIrq & IRQ::IRQ_NMI_DELAYED ) {
        //  次のクロックで割り込みを発生させる。    //
        this->m_flagIrq &= ~ IRQ::IRQ_NMI_DELAYED;
        this->m_flagIrq |=   IRQ::IRQ_NMI;
    }

    const  GuestMemoryAddress oldPC = mog_cpuRegs.PC;
    const  OpeCode  opeCode =
        this->m_manMem.readMemory<OpeCode>(oldPC);
    const  BtByte   ocInst  = (opeCode & 0x000000FF);
    const  GuestMemoryAddress   opSize  = g_opeCodeSize[ocInst];

    //  プログラムカウンタを更新する。  //
    mog_cpuRegs.PC  += opSize;

#if defined( _DEBUG )
    snprintf(buf, sizeof(buf), "Try Execute : %02X:", ocInst);
    std::cerr   <<   buf;
    GuestMemoryAddress  pcWork  = oldPC;
    this->m_manNes.writeMnemonic(std::cerr, oldPC, pcWork);
    std::cerr   <<  "\n\n";
#endif

    //  クロックサイクル数を更新する。  //
    const   ClockCount  cycles  = g_opeCodeCycles[ocInst];
    addCycles(cycles);
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
//    スタックからデータを取り出す。
//

inline  const   RegType
Cpu6502::popValue()
{
    mog_cpuRegs.S ++;
    return  this->m_manMem.readMemory<RegType>(0x0100 + mog_cpuRegs.S);
}

//----------------------------------------------------------------
//    スタックにデータを積む。
//

inline  void
Cpu6502::pushValue(
        const  RegType  value)
{
    this->m_manMem.writeMemory<RegType>(0x0100 + mog_cpuRegs.S, value);
    -- mog_cpuRegs.S;
}

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

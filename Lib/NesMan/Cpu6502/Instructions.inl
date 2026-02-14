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
**      An Implementaion of 6502 Instructions.
**
**      @file       NesMan/Cpu6502/Instructions.inl
**/

#if !defined( NESDBG_NESMAN_CPU6502_INCLUDED_INSTRUCTIONS_INL )
#    define   NESDBG_NESMAN_CPU6502_INCLUDED_INSTRUCTIONS_INL


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//----------------------------------------------------------------
//    フラグ操作（クリア）命令。
//

template  <RegType  VAL>
inline  InstExecResult
Cpu6502::execClearFlag(
        const  OpeCode  opeCode)
{
    mog_cpuRegs.P   &= ~VAL;
    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    ロード命令。
//

template  <int REG, typename AM>
inline  InstExecResult
Cpu6502::execLoad(
        const  OpeCode  opeCode)
{
    ClockCount      cyc = 0;
    const  RegType  rOp = AM().getOperandValue(
              opeCode,
              mog_cpuRegs.X, mog_cpuRegs.Y, mog_cpuRegs.PC,
              this->m_manMem, cyc, BOOL_FALSE);
    switch ( REG ) {
    case  0:
        setupNZFlags(mog_cpuRegs.A = rOp);
        break;
    case  1:
        setupNZFlags(mog_cpuRegs.X = rOp);
        break;
    case  2:
        setupNZFlags(mog_cpuRegs.Y = rOp);
        break;
    }

    //  追加サイクルがあれば加算する。  //
    //  アドレスがページを跨いだ時等。   //
    mog_ctrStep.totalCycles += cyc;

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    フラグ操作（セット）命令。
//

template  <RegType  VAL>
inline  InstExecResult
Cpu6502::execSetFlag(
        const  OpeCode  opeCode)
{
    mog_cpuRegs.P   |= VAL;
    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    ロード命令。
//

template  <int REG, typename AM>
inline  InstExecResult
Cpu6502::execStore(
        const  OpeCode  opeCode)
{
    ClockCount      cyc = 0;
    const  GuestMemoryAddress   gmAddr  = AM().getOperandAddress(
            opeCode,
            mog_cpuRegs.X, mog_cpuRegs.Y, mog_cpuRegs.PC,
            this->m_manMem, cyc, BOOL_FALSE);
    switch ( REG ) {
    case  0:
        this->m_manMem.writeMemory<RegType>(gmAddr, mog_cpuRegs.A);
        break;
    case  1:
        this->m_manMem.writeMemory<RegType>(gmAddr, mog_cpuRegs.X);
        break;
    case  2:
        this->m_manMem.writeMemory<RegType>(gmAddr, mog_cpuRegs.Y);
        break;
    }

    //  追加サイクルがあれば加算する。  //
    //  アドレスがページを跨いだ時等。   //
    mog_ctrStep.totalCycles += cyc;

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//========================================================================

const   Cpu6502::FnInst
Cpu6502::s_cpuInstTable[256] = {
    //  0x00 -- 0F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x10 -- 1F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execClearFlag<0x01>,                  //  18  CLC
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0x20 -- 2F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x30 -- 3F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execSetFlag<0x01>,                    //  38  SEC
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0x40 -- 4F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x50 -- 5F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execClearFlag<0x04>,                  //  58  CLI
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0x60 -- 6F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x70 -- 7F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execSetFlag<0x04>,                    //  78  SEI
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0x80 -- 8F  //
    nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execStore<2, Addres::ZeroPage>,       //  84  STY <$nn
    &Cpu6502::execStore<0, Addres::ZeroPage>,       //  85  STA <$nn
    &Cpu6502::execStore<1, Addres::ZeroPage>,       //  86  STX <$nn
    nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x90 -- 9F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0xA0 -- AF  //
    &Cpu6502::execLoad<2, Addres::Immediate>,       //  A0  LDY #
    nullptr,
    &Cpu6502::execLoad<1, Addres::Immediate>,       //  A2  LDX #
    nullptr,                                        //  A3
    &Cpu6502::execLoad<2, Addres::ZeroPage>,        //  A4  LDY <$nn
    &Cpu6502::execLoad<0, Addres::ZeroPage>,        //  A5  LDA <$nn
    &Cpu6502::execLoad<1, Addres::ZeroPage>,        //  A6  LDX <$nn
    nullptr,                                        //  A7
    nullptr,                                        //  A8  TAY
    &Cpu6502::execLoad<0, Addres::Immediate>,       //  A9  LDA #
    nullptr,                                        //  AA  TAX
    nullptr,                                        //  AB
    nullptr, nullptr, nullptr, nullptr,

    //  0xB0 -- BF  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execClearFlag<0x40>,                  //  B8  CLV
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0xC0 -- CF  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0xD0 -- DF  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execClearFlag<0x08>,                  //  D8  CLD
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0xE0 -- EF  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0xF0 -- FF  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execSetFlag<0x08>,                    //  F8  SED
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

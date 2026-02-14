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

namespace  {

enum  IndexRegister  {
    RA  = 0,
    RX  = 1,
    RY  = 2,
    RS  = 3,
};

}   //  End of (Unnamed) namespace.


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

template  <typename AM, int REG>
inline  InstExecResult
Cpu6502::execLoad(
        const  OpeCode  opeCode)
{
    ClockCount      cyc = 0;
    const  RegType  rOp = AM().getOperandValue(
              opeCode,
              mog_cpuRegs.X, mog_cpuRegs.Y, mog_cpuRegs.PC,
              this->m_manMem, cyc);
    switch ( REG ) {
    case  RA:
        setupNZFlags(mog_cpuRegs.A = rOp);
        break;
    case  RX:
        setupNZFlags(mog_cpuRegs.X = rOp);
        break;
    case  RY:
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

template  <typename AM, int REG>
inline  InstExecResult
Cpu6502::execStore(
        const  OpeCode  opeCode)
{
    ClockCount      cyc = 0;
    const  GuestMemoryAddress   gmAddr  = AM().getOperandAddress(
            opeCode,
            mog_cpuRegs.X, mog_cpuRegs.Y, mog_cpuRegs.PC,
            this->m_manMem, cyc);
    switch ( REG ) {
    case  RA:
        this->m_manMem.writeMemory<RegType>(gmAddr, mog_cpuRegs.A);
        break;
    case  RX:
        this->m_manMem.writeMemory<RegType>(gmAddr, mog_cpuRegs.X);
        break;
    case  RY:
        this->m_manMem.writeMemory<RegType>(gmAddr, mog_cpuRegs.Y);
        break;
    }

    //  追加サイクルがあれば加算する。  //
    //  アドレスがページを跨いだ時等。   //
    mog_ctrStep.totalCycles += cyc;

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    レジスタ間転送命令。
//

template  <int SRC, int TRG>
inline  InstExecResult
Cpu6502::execTransfer(
        const  OpeCode  opeCode)
{
    RegType rSrcVal = 0;

    switch ( SRC ) {
    case  RA:
        rSrcVal = mog_cpuRegs.A;    break;
    case  RX:
        rSrcVal = mog_cpuRegs.X;    break;
    case  RY:
        rSrcVal = mog_cpuRegs.Y;    break;
    case  RS:
        rSrcVal = mog_cpuRegs.S;    break;
    }

    switch ( TRG ) {
    case  RA:
        mog_cpuRegs.A   = rSrcVal;  break;
    case  RX:
        mog_cpuRegs.X   = rSrcVal;  break;
    case  RY:
        mog_cpuRegs.Y   = rSrcVal;  break;
    case  RS:
        mog_cpuRegs.S   = rSrcVal;  break;
    }

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
    nullptr,
    &Cpu6502::execStore<Addres::Indirect<RX>, RA>,  //  81  STA ($nn,X)
    nullptr,                                        //  82
    nullptr,                                        //  83
    &Cpu6502::execStore<Addres::ZeroPage<0>, RY>,   //  84  STY <$nn
    &Cpu6502::execStore<Addres::ZeroPage<0>, RA>,   //  85  STA <$nn
    &Cpu6502::execStore<Addres::ZeroPage<0>, RX>,   //  86  STX <$nn
    nullptr,                                        //  87
    nullptr,                                        //  88  DEY
    nullptr,                                        //  89
    &Cpu6502::execTransfer<RX, RA>,                 //  8A  TXA
    nullptr,                                        //  8B
    &Cpu6502::execStore<Addres::Absolute<0>, RY>,   //  8C  STY $nnnn
    &Cpu6502::execStore<Addres::Absolute<0>, RA>,   //  8D  STA $nnnn
    &Cpu6502::execStore<Addres::Absolute<0>, RX>,   //  8E  STX $nnnn
    nullptr,                                        //  8F

    //  0x90 -- 9F  //
    nullptr,                                        //  90  BCC
    &Cpu6502::execStore<Addres::IdxIndY<RY>, RA>,   //  91  STA ($nn),Y
    nullptr,                                        //  92
    nullptr,                                        //  93
    &Cpu6502::execStore<Addres::ZeroPage<RX>, RY>,  //  94  STY $nn X
    &Cpu6502::execStore<Addres::ZeroPage<RX>, RA>,  //  95  STA $nn X
    &Cpu6502::execStore<Addres::ZeroPage<RY>, RX>,  //  96  STX $nn Y
    nullptr,                                        //  97
    &Cpu6502::execTransfer<RY, RA>,                 //  98  TYA
    &Cpu6502::execStore<Addres::Absolute<RY>, RA>,  //  99  STA $nnnn Y
    &Cpu6502::execTransfer<RX, RS>,                 //  9A  TXS
    nullptr,                                        //  9B
    nullptr,                                        //  9C
    &Cpu6502::execStore<Addres::Absolute<RX>, RA>,  //  9D  STA $nnnn X
    nullptr,                                        //  9E
    nullptr,                                        //  9F

    //  0xA0 -- AF  //
    &Cpu6502::execLoad<Addres::Immediate<0>, RY>,   //  A0  LDY #
    &Cpu6502::execLoad<Addres::Indirect<RX>, RA>,   //  A1  LDA ($nn,X)
    &Cpu6502::execLoad<Addres::Immediate<0>, RX>,   //  A2  LDX #
    nullptr,                                        //  A3
    &Cpu6502::execLoad<Addres::ZeroPage<0>, RY>,    //  A4  LDY <$nn
    &Cpu6502::execLoad<Addres::ZeroPage<0>, RA>,    //  A5  LDA <$nn
    &Cpu6502::execLoad<Addres::ZeroPage<0>, RX>,    //  A6  LDX <$nn
    nullptr,                                        //  A7
    &Cpu6502::execTransfer<RA, RY>,                 //  A8  TAY
    &Cpu6502::execLoad<Addres::Immediate<0>, RA>,   //  A9  LDA #
    &Cpu6502::execTransfer<RA, RX>,                 //  AA  TAX
    nullptr,                                        //  AB
    &Cpu6502::execLoad<Addres::Absolute<0>, RY>,    //  AC  LDY $nnnn
    &Cpu6502::execLoad<Addres::Absolute<0>, RA>,    //  AD  LDA $nnnn
    &Cpu6502::execLoad<Addres::Absolute<0>, RX>,    //  AE  LDX $nnnn
    nullptr,                                        //  AF

    //  0xB0 -- BF  //
    nullptr,                                        //  B0  BCS r
    &Cpu6502::execLoad<Addres::IdxIndY<RY>, RA>,    //  B1  LDA ($nn),Y
    nullptr,                                        //  B2
    nullptr,                                        //  B3
    &Cpu6502::execLoad<Addres::ZeroPage<RX>, RY>,   //  B4  LDY $nn,X
    &Cpu6502::execLoad<Addres::ZeroPage<RX>, RA>,   //  B5  LDA $nn,X
    &Cpu6502::execLoad<Addres::ZeroPage<RY>, RX>,   //  B6  LDX $nn,Y
    nullptr,                                        //  B7
    &Cpu6502::execClearFlag<0x40>,                  //  B8  CLV
    nullptr,                                        //  B9  LDA $nnnn,Y
    &Cpu6502::execTransfer<RS, RX>,                 //  BA  TSX
    nullptr,                                        //  BB
    &Cpu6502::execLoad<Addres::Absolute<RX>, RY>,   //  BC  LDY $nnnn,X
    &Cpu6502::execLoad<Addres::Absolute<RX>, RA>,   //  BD  LDA $nnnn,X
    &Cpu6502::execLoad<Addres::Absolute<RY>, RX>,   //  BE  LDX $nnnn,Y
    nullptr,                                        //  BF

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

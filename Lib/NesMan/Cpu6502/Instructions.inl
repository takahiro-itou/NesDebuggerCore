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


//  アドレッシングモード
#define     ADR_IMM         Addres::Immediate<0>
#define     ADR_ZERO        Addres::ZeroPage<&RegBank::Zr>
#define     ADR_ZEROX       Addres::ZeroPage<&RegBank::X>
#define     ADR_ZEROY       Addres::ZeroPage<&RegBank::Y>
#define     ADR_ABSOL       Addres::Absolute<&RegBank::Zr>
#define     ADR_ABS_X       Addres::Absolute<&RegBank::X>
#define     ADR_ABS_Y       Addres::Absolute<&RegBank::Y>
#define     ADR_INDIR       Addres::Indirect<&RegBank::Zr>
#define     ADR_IND_X       Addres::Indirect<&RegBank::X>
#define     ADR_IND_Y       Addres::IdxIndY <&RegBank::Y>

//  オペランド
#define     OPERAND_IMM     Addres::ImmediateOperand<>
#define     OPERAND_REG_A   Addres::RegisterOperand<&RegBank::A>
#define     OPERAND_REG_X   Addres::RegisterOperand<&RegBank::X>
#define     OPERAND_REG_Y   Addres::RegisterOperand<&RegBank::Y>
#define     OPERAND_REG_S   Addres::RegisterOperand<&RegBank::S>
#define     OPERAND_REG_P   Addres::RegisterOperand<&RegBank::P>
#define     OPERAND_ZERPG   Addres::MemoryOperand< ADR_ZERO  >
#define     OPERAND_ZEROX   Addres::MemoryOperand< ADR_ZEROX >
#define     OPERAND_ZEROY   Addres::MemoryOperand< ADR_ZEROY >
#define     OPERAND_ABSOL   Addres::MemoryOperand< ADR_ABSOL >
#define     OPERAND_ABS_X   Addres::MemoryOperand< ADR_ABS_X >
#define     OPERAND_ABS_Y   Addres::MemoryOperand< ADR_ABS_Y >
#define     OPERAND_INDIR   Addres::MemoryOperand< ADR_INDIR >
#define     OPERAND_IND_X   Addres::MemoryOperand< ADR_IND_X >
#define     OPERAND_IND_Y   Addres::MemoryOperand< ADR_IND_Y >

//  対象レジスタ
#define     REG_A           &RegBank::A
#define     REG_X           &RegBank::X
#define     REG_Y           &RegBank::Y
#define     REG_S           &RegBank::S

#define     CMP(reg, or2)   \
    &Cpu6502::execArithLogic<or2, ALU::OpeCMP, ALU::OpeNopR, 0, reg>
#define     CPX(or2)        \
    &Cpu6502::execArithLogic<or2, ALU::OpeCMP, ALU::OpeNopR, 0, REG_X>
#define     CPY(or2)        \
    &Cpu6502::execArithLogic<or2, ALU::OpeCMP, ALU::OpeNopR, 0, REG_Y>

NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

}   //  End of (Unnamed) namespace.


//----------------------------------------------------------------
//    算術論理演算命令。
//

template  <
    typename OPERAND, typename CODE1, typename CODE2,
    int RMWW, TRegPtr REGPTR>
inline  InstExecResult
Cpu6502::execArithLogic(
        const  OpeCode  opeCode)
{
    ClockCount  cyc = 0;
    OPERAND operand(opeCode, mog_cpuRegs, this->m_manMem, cyc);

    RegType lhs = (mog_cpuRegs .* REGPTR);
    RegType rhs = operand.readValue();

    if ( RMWW ) {
        //  Read-Modify-Write 命令は、  //
        //  一回元の値を書き込む仕様。  //
        operand.writeValue(rhs);
    }
    rhs = CODE2()(lhs, rhs, mog_cpuRegs.P);
    if ( RMWW ) {
        operand.writeValue(rhs);
    }

    if ( REGPTR == &RegBank::Zr ) {
        //  ここに来るのは ASL A  などの場合。  //
        //  CODE1 側は何もしない命令。          //
        return ( InstExecResult::SUCCESS_CONTINUE );
    }

    lhs = CODE1()(lhs, rhs, mog_cpuRegs.P);
    (mog_cpuRegs .* REGPTR) = lhs;

    return ( InstExecResult::SUCCESS_CONTINUE );
}


//----------------------------------------------------------------
//    条件分岐命令。
//

template  <RegType MSK, RegType FLG>
inline  InstExecResult
Cpu6502::execBranch(
        const  OpeCode  opeCode)
{
    if ( (mog_cpuRegs.P & MSK) != FLG ) {
        //  条件が成立しなければ、何もしない。  //
        return ( InstExecResult::SUCCESS_CONTINUE );
    }
    ++ mog_ctrStep.totalCycles;
    GuestMemoryAddress  tmp = mog_cpuRegs.PC;
    int32_t     dst;

    dst = (int8_t)(opeCode & 0x000000FF);
    mog_cpuRegs.PC  += dst;

    //  Page-Cross Check..  //
    if ( (tmp ^ mog_cpuRegs.PC) & 0x0100 ) {
        ++ mog_ctrStep.totalCycles;
    }

    return ( InstExecResult::SUCCESS_CONTINUE );
}

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
//    インクリメント、デクリメント命令。
//

template  <typename OPERAND, int VAL>
inline  InstExecResult
Cpu6502::execIncDec(
        const  OpeCode  opeCode)
{
    ClockCount  cyc = 0;

    OPERAND operand(opeCode, mog_cpuRegs, this->m_manMem, cyc);
    RegType val = operand.readValue();

    operand.writeValue(val);
    setupNZFlags(val += VAL);
    operand.writeValue(val);

    mog_ctrStep.totalCycles += cyc;

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    インクリメント、デクリメント命令。
//

template  <TRegPtr REG, int VAL>
inline  InstExecResult
Cpu6502::execIncDecReg(
        const  OpeCode  opeCode)
{
    setupNZFlags((mog_cpuRegs .* REG) += VAL);
    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    ジャンプ命令。
//

inline  InstExecResult
Cpu6502::execJsr(const  OpeCode  opeCode)
{
    //  まず現在 PC をスタックに積むが、            //
    //  積まれるのは次の命令の１バイト手前である。  //
    //  つまり、この命令の最後のバイトをを積む。    //
    //  ここに到達した時点で、既に次の命令の先頭を  //
    //  指しているので１バイト引いて push する。    //
    const   GuestMemoryAddress  pc  = mog_cpuRegs.PC - 1;
    pushValue((pc >> 8) & 0x000000FF);
    pushValue((pc     ) & 0x000000FF);

    //  オペランドは 16 ビットの即値による          //
    //  絶対番地指定なので、そのまま PC にコピー。  //
    mog_cpuRegs.PC  = (opeCode & 0x0000FFFF);

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    ロード命令。
//

template  <typename AM, TRegPtr REG>
inline  InstExecResult
Cpu6502::execLoad(
        const  OpeCode  opeCode)
{
    ClockCount      cyc = 0;
    const  RegType  rOp = AM().getOperandValue(
                opeCode, mog_cpuRegs, this->m_manMem, cyc);

    setupNZFlags((mog_cpuRegs .* REG) = rOp);

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

template  <typename AM, TRegPtr REG>
inline  InstExecResult
Cpu6502::execStore(
        const  OpeCode  opeCode)
{
    ClockCount      cyc = 0;
    const  GuestMemoryAddress   gmAddr  = AM().getOperandAddress(
            opeCode, mog_cpuRegs, this->m_manMem, cyc);

    this->m_manMem.writeMemory<RegType>(gmAddr, (mog_cpuRegs .* REG));

    //  追加サイクルがあれば加算する。  //
    //  アドレスがページを跨いだ時等。   //
    mog_ctrStep.totalCycles += cyc;

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    レジスタ間転送命令。
//

template  <TRegPtr SRCREG, TRegPtr TRGREG>
inline  InstExecResult
Cpu6502::execTransfer(
        const  OpeCode  opeCode)
{
    RegType rSrcVal = 0;

    rSrcVal = (mog_cpuRegs .* SRCREG);
    (mog_cpuRegs .* TRGREG) = rSrcVal;

    return ( InstExecResult::SUCCESS_CONTINUE );
}


//========================================================================

const   Cpu6502::FnInst
Cpu6502::s_cpuInstTable[256] = {
    //  0x00 -- 0F  //
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x10 -- 1F  //
    &Cpu6502::execBranch<FLAG_N, 0>,                //  10  BPL r
    nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execClearFlag<0x01>,                  //  18  CLC
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0x20 -- 2F  //
    &Cpu6502::execJsr,                              //  20  JSR
    nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x30 -- 3F  //
    &Cpu6502::execBranch<FLAG_N, FLAG_N>,           //  30  BMI r
    nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execSetFlag<0x01>,                    //  38  SEC
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0x40 -- 4F  //
    nullptr,                                        //  40  RTI
    nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x50 -- 5F  //
    &Cpu6502::execBranch<FLAG_V, 0>,                //  50  BVC r
    nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execClearFlag<0x04>,                  //  58  CLI
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0x60 -- 6F  //
    nullptr,                                        //  60  RTS
    nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,

    //  0x70 -- 7F  //
    &Cpu6502::execBranch<FLAG_V, FLAG_V>,           //  70  BVS r
    nullptr, nullptr, nullptr,  nullptr, nullptr, nullptr, nullptr,
    &Cpu6502::execSetFlag<0x04>,                    //  78  SEI
    nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr,

    //  0x80 -- 8F  //
    nullptr,
    &Cpu6502::execStore<ADR_IND_X, REG_A>,          //  81   STA ($nn,X)
    nullptr,                                        //  82
    nullptr,                                        //  83
    &Cpu6502::execStore<ADR_ZERO, REG_Y>,           //  84  STY <$nn
    &Cpu6502::execStore<ADR_ZERO, REG_A>,           //  85  STA <$nn
    &Cpu6502::execStore<ADR_ZERO, REG_X>,           //  86  STX <$nn
    nullptr,                                        //  87
    &Cpu6502::execIncDecReg<REG_Y, -1>,             //  88  DEY
    nullptr,                                        //  89
    &Cpu6502::execTransfer<REG_X, REG_A>,           //  8A  TXA
    nullptr,                                        //  8B
    &Cpu6502::execStore<ADR_ABSOL, REG_Y>,          //  8C  STY $nnnn
    &Cpu6502::execStore<ADR_ABSOL, REG_A>,          //  8D  STA $nnnn
    &Cpu6502::execStore<ADR_ABSOL, REG_X>,          //  8E  STX $nnnn
    nullptr,                                        //  8F

    //  0x90 -- 9F  //
    &Cpu6502::execBranch<FLAG_C, 0>,                //  90  BCC r
    &Cpu6502::execStore<ADR_IND_Y, REG_A>,          //  91  STA ($nn),Y
    nullptr,                                        //  92
    nullptr,                                        //  93
    &Cpu6502::execStore<ADR_ZEROX, REG_Y>,          //  94  STY $nn X
    &Cpu6502::execStore<ADR_ZEROX, REG_A>,          //  95  STA $nn X
    &Cpu6502::execStore<ADR_ZEROY, REG_X>,          //  96  STX $nn Y
    nullptr,                                        //  97
    &Cpu6502::execTransfer<REG_Y, REG_A>,           //  98  TYA
    &Cpu6502::execStore<ADR_ABS_Y, REG_A>,          //  99  STA $nnnn Y
    &Cpu6502::execTransfer<REG_X, REG_S>,           //  9A  TXS
    nullptr,                                        //  9B
    nullptr,                                        //  9C
    &Cpu6502::execStore<ADR_ABS_X, REG_A>,          //  9D  STA $nnnn X
    nullptr,                                        //  9E
    nullptr,                                        //  9F

    //  0xA0 -- AF  //
    &Cpu6502::execLoad<ADR_IMM, REG_Y>,             //  A0  LDY #
    &Cpu6502::execLoad<ADR_IND_X, REG_A>,           //  A1  LDA ($nn,X)
    &Cpu6502::execLoad<ADR_IMM, REG_X>,             //  A2  LDX #
    nullptr,                                        //  A3
    &Cpu6502::execLoad<ADR_ZERO, REG_Y>,            //  A4  LDY <$nn
    &Cpu6502::execLoad<ADR_ZERO, REG_A>,            //  A5  LDA <$nn
    &Cpu6502::execLoad<ADR_ZERO, REG_X>,            //  A6  LDX <$nn
    nullptr,                                        //  A7
    &Cpu6502::execTransfer<REG_A, REG_Y>,           //  A8  TAY
    &Cpu6502::execLoad<ADR_IMM, REG_A>,             //  A9  LDA #
    &Cpu6502::execTransfer<REG_A, REG_X>,           //  AA  TAX
    nullptr,                                        //  AB
    &Cpu6502::execLoad<ADR_ABSOL, REG_Y>,           //  AC  LDY $nnnn
    &Cpu6502::execLoad<ADR_ABSOL, REG_A>,           //  AD  LDA $nnnn
    &Cpu6502::execLoad<ADR_ABSOL, REG_X>,           //  AE  LDX $nnnn
    nullptr,                                        //  AF

    //  0xB0 -- BF  //
    &Cpu6502::execBranch<FLAG_C, FLAG_C>,           //  B0  BCS r
    &Cpu6502::execLoad<ADR_IND_Y, REG_A>,           //  B1  LDA ($nn),Y
    nullptr,                                        //  B2
    nullptr,                                        //  B3
    &Cpu6502::execLoad<ADR_ZEROX, REG_Y>,           //  B4  LDY $nn,X
    &Cpu6502::execLoad<ADR_ZEROX, REG_A>,           //  B5  LDA $nn,X
    &Cpu6502::execLoad<ADR_ZEROY, REG_X>,           //  B6  LDX $nn,Y
    nullptr,                                        //  B7
    &Cpu6502::execClearFlag<0x40>,                  //  B8  CLV
    nullptr,                                        //  B9  LDA $nnnn,Y
    &Cpu6502::execTransfer<REG_S, REG_X>,           //  BA  TSX
    nullptr,                                        //  BB
    &Cpu6502::execLoad<ADR_ABS_X, REG_Y>,           //  BC  LDY $nnnn,X
    &Cpu6502::execLoad<ADR_ABS_X, REG_A>,           //  BD  LDA $nnnn,X
    &Cpu6502::execLoad<ADR_ABS_Y, REG_X>,           //  BE  LDX $nnnn,Y
    nullptr,                                        //  BF

    //  0xC0 -- CF  //
    CMP(REG_Y, OPERAND_IMM),                        //  C0  CPY #
    CMP(REG_A, OPERAND_IND_X),                      //  C1  CMP ($nn,X)
    nullptr,                                        //  C2
    nullptr,                                        //  C3
    CMP(REG_Y, OPERAND_ZERPG),                      //  C4  CPY $nn
    CMP(REG_A, OPERAND_ZERPG),                      //  C5  CMP $nn
    &Cpu6502::execIncDec<OPERAND_ZERPG, -1>,        //  C6  DEC $nn
    nullptr,                                        //  C7
    &Cpu6502::execIncDecReg<REG_Y, +1>,             //  C8  INY
    CMP(REG_A, OPERAND_IMM),                        //  C9  CMP #imm
    &Cpu6502::execIncDecReg<REG_X, -1>,             //  CA  DEX
    nullptr,                                        //  CB
    CMP(REG_Y, OPERAND_ABSOL),                      //  CC  CPY $nnnn
    CMP(REG_A, OPERAND_ABSOL),                      //  CD  CMP $nnnn
    &Cpu6502::execIncDec<OPERAND_ABSOL, -1>,        //  CE  DEC $nnnn
    nullptr,                                        //  CF

    //  0xD0 -- DF  //
    &Cpu6502::execBranch<FLAG_Z, 0>,                //  D0  BNE r
    CMP(REG_A, OPERAND_IND_Y),                      //  D1  CMP $(nn),Y
    nullptr,                                        //  D2
    nullptr,                                        //  D3
    nullptr,                                        //  D4
    CMP(REG_A, OPERAND_ZEROX),                      //  D5  CMP $nn,X
    &Cpu6502::execIncDec<OPERAND_ZEROX, -1>,        //  D6  DEC $nn,X
    nullptr,                                        //  D7
    &Cpu6502::execClearFlag<0x08>,                  //  D8  CLD
    CMP(REG_A, OPERAND_ABS_Y),                      //  D9  CMP $nnnn,Y
    nullptr,                                        //  DA
    nullptr,                                        //  DB
    nullptr,                                        //  DC
    CMP(REG_A, OPERAND_ABS_X),                      //  DD  CMP $nnnn,X
    &Cpu6502::execIncDec<OPERAND_ABS_X, -1>,        //  DE  DEC $nnnn,X
    nullptr,                                        //  DF

    //  0xE0 -- EF  //
    CMP(REG_X, OPERAND_IMM),                        //  E0  CPX #imm
    nullptr,                                        //  E1  SBC ($nn,X)
    nullptr,                                        //  E2
    nullptr,                                        //  E3
    CMP(REG_X, OPERAND_ZERPG),                      //  E4  CPX $nn
    nullptr,                                        //  E5  SBC $nn
    &Cpu6502::execIncDec<OPERAND_ZERPG, +1>,        //  E6  INC $nn
    nullptr,                                        //  E7
    &Cpu6502::execIncDecReg<REG_X, +1>,             //  E8  INX
    nullptr,                                        //  E9  SBC #imm
    nullptr,                                        //  EA  NOP
    nullptr,                                        //  EB
    CMP(REG_X, OPERAND_ABSOL),                      //  EC  CPX $nnnn
    nullptr,                                        //  ED  SBC $nnnn
    &Cpu6502::execIncDec<OPERAND_ABSOL, +1>,        //  EE  INC $nnnn
    nullptr,                                        //  EF

    //  0xF0 -- FF  //
    &Cpu6502::execBranch<FLAG_Z, FLAG_Z>,           //  F0  BEQ r
    nullptr,                                        //  F1  SBC ($nn),Y
    nullptr, nullptr,
    nullptr,                                        //  F4
    nullptr,                                        //  F5  SBC $nn,X
    &Cpu6502::execIncDec<OPERAND_ZEROX, +1>,        //  F6  INC $nn,X
    nullptr,                                        //  F7
    &Cpu6502::execSetFlag<0x08>,                    //  F8  SED
    nullptr,                                        //  F9  SBC $nnnn,Y
    nullptr, nullptr,
    nullptr,                                        //  FC
    nullptr,                                        //  FD  SBC $nnnn,X
    &Cpu6502::execIncDec<OPERAND_ABS_X, +1>,        //  FE  INC $nnnn,X
    nullptr,                                        //  FF
};


}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

//  このファイルでしか使わないマクロを解除  //
#undef      ADR_ZERO
#undef      ADR_ZEROX
#undef      ADR_ZEROY
#undef      ADR_ABSOL
#undef      ADR_ABS_X
#undef      ADR_ABS_Y
#undef      ADR_INDIR
#undef      ADR_IND_X
#undef      ADR_IND_Y

#undef      OPERAND_REG_A
#undef      OPERAND_REG_X
#undef      OPERAND_REG_Y
#undef      OPERAND_REG_S
#undef      OPERAND_REG_O
#undef      OPERAND_ZERPG
#undef      OPERAND_ZEROX
#undef      OPERAND_ZEROY
#undef      OPERAND_ABSOL
#undef      OPERAND_ABS_X
#undef      OPERAND_ABS_Y
#undef      OPERAND_INDIR
#undef      OPERAND_IND_X
#undef      OPERAND_IND_Y

#undef      REG_A
#undef      REG_X
#undef      REG_Y
#undef      REG_S

#endif

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

#define     ADC(operand)    \
    &Cpu6502::execArithLogic<operand, ALU::OpeADC, ALU::OpeNopR, 0, REG_A>
#define     ANC(operand)    nullptr
#define     AND(operand)    nullptr
#define     ALR(operand)    nullptr
#define     ARR(operand)    nullptr
#define     ASL(operand)    nullptr
#define     BIT(operand)    nullptr
#define     BRK             nullptr
#define     DOP(operand)    nullptr
#define     EOR(operand)    nullptr
#define     UND_HLT         nullptr
#define     ISB(operand)    nullptr
#define     LSR(operand)    nullptr
#define     UND_NOP         nullptr
#define     ORA(operand)    nullptr
#define     RLA(operand)    nullptr
#define     ROL(operand)    nullptr
#define     ROR(operand)    nullptr
#define     RRA(operand)    nullptr
#define     SAX(operand)    nullptr
#define     SBC(operand)    \
    &Cpu6502::execArithLogic<operand, ALU::OpeSBC, ALU::OpeNopR, 0, REG_A>
#define     SLO(operand)    nullptr
#define     SRE(operand)    nullptr
#define     STR(operand)    nullptr
#define     TOP(operand)    nullptr

#define     CMP(or2, reg)   \
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
Cpu6502::execJmpAbs(const  OpeCode  opeCode)
{
    //  オペランドは 16 ビットの即値による          //
    //  絶対番地指定なので、そのまま PC にコピー。  //
    mog_cpuRegs.PC  = (opeCode & 0x0000FFFF);

    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    ジャンプ命令。
//

inline  InstExecResult
Cpu6502::execJmpIndirect(const  OpeCode  opeCode)
{
    GuestMemoryAddress  gmL, gmH;
    gmL = this->m_manMem.readMemory<BtByte>(opeCode & 0x000000FF);
    gmH = this->m_manMem.readMemory<BtByte>(
                ((opeCode & 0xFF00) << 8) | ((opeCode + 1) & 0x00FF)
    );

    mog_cpuRegs.PC  = ((gmH << 8) | gmL);
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

    return  execJmpAbs(opeCode);
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
//    ポップ命令。
//

template  <TRegPtr TRGREG>
inline  InstExecResult
Cpu6502::execPull(const  OpeCode  opeCode)
{
    (mog_cpuRegs .* TRGREG) = popValue();
    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    プッシュ命令。
//

template  <TRegPtr SECREG>
inline  InstExecResult
Cpu6502::execPush(
        const  OpeCode  opeCode)
{
    pushValue(mog_cpuRegs .* SECREG);
    return ( InstExecResult::SUCCESS_CONTINUE );
}

//----------------------------------------------------------------
//    リターン命令。
//

inline  InstExecResult
Cpu6502::execRti(const  OpeCode  opeCode)
{
    return ( InstExecResult::UNDEFINED_OPECODE );
}

//----------------------------------------------------------------
//    リターン命令。
//

inline  InstExecResult
Cpu6502::execRts(const  OpeCode  opeCode)
{
    mog_cpuRegs.PC  = popValue();
    mog_cpuRegs.PC  |= (popValue() << 8);
    ++ mog_cpuRegs.PC;
    mog_cpuRegs.PC  &= 0x0000FFFF;
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
    BRK,                                            //  00  BRK
    ORA(OPERAND_IND_X),                             //  01  ORA ($nn,X)
    UND_HLT,                                        //  02  hlt
    SLO(OPERAND_IND_X),                             //  03  slo ($nn,X)
    DOP(OPERAND_ZERPG),                             //  04  dop <$nn
    ORA(OPERAND_ZERPG),                             //  05  ORA <$nn
    ASL(OPERAND_ZERPG),                             //  06  ASL <$nn
    SLO(OPERAND_ZERPG),                             //  07  slo <$nn
    &Cpu6502::execPush<&RegBank::P>,                //  08  PHP
    ORA(OPERAND_IMM),                               //  09  ORA #imm
    ASL(OPERAND_REG_A),                             //  0A  ASL A
    ANC(OPERAND_IMM),                               //  0B  anc #imm
    TOP(OPERAND_ABSOL),                             //  0C  TOP $nnnn
    ORA(OPERAND_ABSOL),                             //  0D  ORA $nnnn
    ASL(OPERAND_ABSOL),                             //  0E  ASL $nnnn
    SLO(OPERAND_ABSOL),                             //  0F  slo $nnnn

    //  0x10 -- 1F  //
    &Cpu6502::execBranch<FLAG_N, 0>,                //  10  BPL r
    ORA(OPERAND_IND_Y),                             //  11  ORA ($nn),Y
    UND_HLT,                                        //  12  hlt
    SLO(OPERAND_IND_Y),                             //  13  slo ($nn),Y
    DOP(OPERAND_ZEROX),                             //  14  DOP <$nn,X
    ORA(OPERAND_ZEROX),                             //  15  ORA <$nn,X
    ASL(OPERAND_ZEROX),                             //  16  ASL <$nn,X
    SLO(OPERAND_ZEROX),                             //  17  SLO <$nn,X
    &Cpu6502::execClearFlag<0x01>,                  //  18  CLC
    ORA(OPERAND_ABS_Y),                             //  19  ORA $nnnn,Y
    UND_NOP,                                        //  1A  nop
    SLO(OPERAND_ABS_Y),                             //  1B  slo $nnnn,Y
    TOP(OPERAND_ABS_X),                             //  1C  top $nnnn,X
    ORA(OPERAND_ABS_X),                             //  1D  ORA $nnnn,X
    ASL(OPERAND_ABS_X),                             //  1E  ASL $nnnn,X
    SLO(OPERAND_ABS_X),                             //  1F  ASL,$nnnn,X

    //  0x20 -- 2F  //
    &Cpu6502::execJsr,                              //  20  JSR
    AND(OPERAND_IND_X),                             //  21  AND ($nn,X)
    UND_HLT,                                        //  22  hlt
    RLA(OPERAND_IND_X),                             //  23  rla ($nn,X)
    BIT(OPERAND_ZERPG),                             //  24  BIT <$nn
    AND(OPERAND_ZERPG),                             //  25  AND <$nn
    ROL(OPERAND_ZERPG),                             //  26  ROL <$nn
    RLA(OPERAND_ZERPG),                             //  27  rla <$nn
    &Cpu6502::execPull<&RegBank::P>,                //  28  PLP
    AND(OPERAND_IMM),                               //  29  AND $imm
    ROL(OPERAND_REG_A),                             //  2A  ROL A
    ANC(OPERAND_IMM),                               //  2B  anc #imm
    BIT(OPERAND_ABSOL),                             //  2C  BIT $nnnn
    AND(OPERAND_ABSOL),                             //  2D  AND $nnnn
    ROL(OPERAND_ABSOL),                             //  2E  ROL $nnnn
    RLA(OPERAND_ABSOL),                             //  2F  rla $nnnn

    //  0x30 -- 3F  //
    &Cpu6502::execBranch<FLAG_N, FLAG_N>,           //  30  BMI r
    AND(OPERAND_IND_Y),                             //  31  AND ($nn),Y
    UND_HLT,                                        //  32  hlt
    RLA(OPERAND_IND_Y),                             //  33  rla ($nn),Y
    DOP(OPERAND_ZEROX),                             //  34  dop <$nn,X
    AND(OPERAND_ZEROX),                             //  35  AND <$nn,X
    ROL(OPERAND_ZEROX),                             //  36  ROL <$nn,X
    RLA(OPERAND_ZEROX),                             //  37  rla <$nn,X
    &Cpu6502::execSetFlag<0x01>,                    //  38  SEC
    AND(OPERAND_ABS_Y),                             //  39  AND $nnnn,Y
    UND_NOP,                                        //  3A  nop
    RLA(OPERAND_ABS_Y),                             //  3B  rla $nnnn,Y
    TOP(OPERAND_ABS_X),                             //  3C  top $nnnn,X
    AND(OPERAND_ABS_X),                             //  3D  AND $nnnn,X
    ROL(OPERAND_ABS_X),                             //  3E  ROL $nnnn,X
    RLA(OPERAND_ABS_X),                             //  3F  rla $nnnn,X

    //  0x40 -- 4F  //
    &Cpu6502::execRti,                              //  40  RTI
    EOR(OPERAND_IND_X),                             //  41  EOR ($nn,X)
    UND_HLT,                                        //  42  hlt
    SRE(OPERAND_IND_X),                             //  43  sre ($nn,X)
    DOP(OPERAND_ZERPG),                             //  44  DOP <$nn
    EOR(OPERAND_ZERPG),                             //  45  EOR <$nn
    LSR(OPERAND_ZERPG),                             //  46  LSR <$nn
    SRE(OPERAND_ZERPG),                             //  47  sre <$nn
    &Cpu6502::execPush<&RegBank::A>,                //  48  PHA
    EOR(OPERAND_IMM),                               //  49  EOR #imm
    LSR(OPERAND_REG_A),                             //  4A  LSR A
    ALR(OPERAND_IMM),                               //  4B  alr #imm
    &Cpu6502::execJmpAbs,                           //  4C  JMP $nnnn
    EOR(OPERAND_ABSOL),                             //  4D  EOR $nnnn
    LSR(OPERAND_ABSOL),                             //  4E  LSR $nnnn
    SRE(OPERAND_ABSOL),                             //  4F  sre $nnnn

    //  0x50 -- 5F  //
    &Cpu6502::execBranch<FLAG_V, 0>,                //  50  BVC r
    EOR(OPERAND_IND_Y),                             //  51  EOR ($nn),Y
    UND_HLT,                                        //  52  hlt
    STR(OPERAND_IND_Y),                             //  53  str ($nn),Y
    DOP(OPERAND_ZEROX),                             //  54  dop <$nn,X
    EOR(OPERAND_ZEROX),                             //  55  EOR <$nn,X
    LSR(OPERAND_ZEROX),                             //  56  LSR <$nn,X
    SRE(OPERAND_ZEROX),                             //  57  sre <$nn,X
    &Cpu6502::execClearFlag<0x04>,                  //  58  CLI
    EOR(OPERAND_ABS_Y),                             //  59  EOR $nnnn,Y
    UND_NOP,                                        //  5A  nop
    SRE(OPERAND_ABS_Y),                             //  5B  sre $nnnn,Y
    TOP(OPERAND_ABS_X),                             //  5C  top $nnnn,X
    EOR(OPERAND_ABS_X),                             //  5D  EOR $nnnn,X
    LSR(OPERAND_ABS_X),                             //  5E  LSR $nnnn,X
    SRE(OPERAND_ABS_X),                             //  5F  sre $nnnn,X

    //  0x60 -- 6F  //
    &Cpu6502::execRts,                              //  60  RTS
    ADC(OPERAND_IND_X),                             //  61  ADC $(nn,X)
    UND_HLT,                                        //  62  hlt
    RRA(OPERAND_IND_X),                             //  63  rra $(nn,X)
    DOP(OPERAND_ZERPG),                             //  64  dop <$nn
    ADC(OPERAND_ZERPG),                             //  65  ADC <$nn
    ROR(OPERAND_ZERPG),                             //  66  ROR <$nn
    RRA(OPERAND_ZERPG),                             //  67  rra <$nn
    &Cpu6502::execPull<&RegBank::A>,                //  68  PLA
    ADC(OPERAND_IMM),                               //  69  ADC #imm
    ROR(OPERAND_REG_A),                             //  6A  ROR A
    ARR(OPERAND_IMM),                               //  6B  arr #imm
    &Cpu6502::execJmpIndirect,                      //  6C  JMP ($nnnn)
    ADC(OPERAND_ABSOL),                             //  6D  ADC $nnnn
    ROR(OPERAND_ABSOL),                             //  6E  ROR $nnnn
    RRA(OPERAND_ABSOL),                             //  6F  rra $nnnn

    //  0x70 -- 7F  //
    &Cpu6502::execBranch<FLAG_V, FLAG_V>,           //  70  BVS r
    ADC(OPERAND_IND_Y),                             //  71  ADC $(nn),Y
    UND_HLT,                                        //  72  hlt
    RRA(OPERAND_IND_Y),                             //  73  rra $(nn),Y
    DOP(OPERAND_ZEROX),                             //  74  dop <$nn,X
    ADC(OPERAND_ZEROX),                             //  75  ADC <$nn,X
    ROR(OPERAND_ZEROX),                             //  76  ROR <$nn,X
    RRA(OPERAND_ZEROX),                             //  77  rra <$nn,X
    &Cpu6502::execSetFlag<0x04>,                    //  78  SEI
    ADC(OPERAND_ABS_Y),                             //  79  ADC $nnnn,Y
    UND_NOP,                                        //  7A  nop
    RRA(OPERAND_ABS_Y),                             //  7B  rra $nnnn,Y
    TOP(OPERAND_ABS_X),                             //  7C  top $nnnn,X
    ADC(OPERAND_ABS_X),                             //  7D  ADC $nnnn,X
    ROR(OPERAND_ABS_X),                             //  7E  ROR $nnnn,X
    RRA(OPERAND_ABS_X),                             //  7F  rra $nnnn,X

    //  0x80 -- 8F  //
    DOP(OPERAND_IMM),                               //  80  dop #imm
    &Cpu6502::execStore<ADR_IND_X, REG_A>,          //  81  STA ($nn,X)
    DOP(OPERAND_IMM),                               //  82  dop #imm
    SAX(OPERAND_IND_X),                             //  83  sax ($nn,X)
    &Cpu6502::execStore<ADR_ZERO, REG_Y>,           //  84  STY <$nn
    &Cpu6502::execStore<ADR_ZERO, REG_A>,           //  85  STA <$nn
    &Cpu6502::execStore<ADR_ZERO, REG_X>,           //  86  STX <$nn
    SAX(OPERAND_ZERPG),                             //  87  sax <$nn
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
    &Cpu6502::execLoad<ADR_ABS_Y, REG_A>,           //  B9  LDA $nnnn,Y
    &Cpu6502::execTransfer<REG_S, REG_X>,           //  BA  TSX
    nullptr,                                        //  BB
    &Cpu6502::execLoad<ADR_ABS_X, REG_Y>,           //  BC  LDY $nnnn,X
    &Cpu6502::execLoad<ADR_ABS_X, REG_A>,           //  BD  LDA $nnnn,X
    &Cpu6502::execLoad<ADR_ABS_Y, REG_X>,           //  BE  LDX $nnnn,Y
    nullptr,                                        //  BF

    //  0xC0 -- CF  //
    CMP(OPERAND_IMM,   REG_Y),                      //  C0  CPY #
    CMP(OPERAND_IND_X, REG_A),                      //  C1  CMP ($nn,X)
    nullptr,                                        //  C2
    nullptr,                                        //  C3
    CMP(OPERAND_ZERPG, REG_Y),                      //  C4  CPY $nn
    CMP(OPERAND_ZERPG, REG_A),                      //  C5  CMP $nn
    &Cpu6502::execIncDec<OPERAND_ZERPG, -1>,        //  C6  DEC $nn
    nullptr,                                        //  C7
    &Cpu6502::execIncDecReg<REG_Y, +1>,             //  C8  INY
    CMP(OPERAND_IMM,   REG_A),                      //  C9  CMP #imm
    &Cpu6502::execIncDecReg<REG_X, -1>,             //  CA  DEX
    nullptr,                                        //  CB
    CMP(OPERAND_ABSOL, REG_Y),                      //  CC  CPY $nnnn
    CMP(OPERAND_ABSOL, REG_A),                      //  CD  CMP $nnnn
    &Cpu6502::execIncDec<OPERAND_ABSOL, -1>,        //  CE  DEC $nnnn
    nullptr,                                        //  CF

    //  0xD0 -- DF  //
    &Cpu6502::execBranch<FLAG_Z, 0>,                //  D0  BNE r
    CMP(OPERAND_IND_Y, REG_A),                      //  D1  CMP $(nn),Y
    nullptr,                                        //  D2
    nullptr,                                        //  D3
    nullptr,                                        //  D4
    CMP(OPERAND_ZEROX, REG_A),                      //  D5  CMP $nn,X
    &Cpu6502::execIncDec<OPERAND_ZEROX, -1>,        //  D6  DEC $nn,X
    nullptr,                                        //  D7
    &Cpu6502::execClearFlag<0x08>,                  //  D8  CLD
    CMP(OPERAND_ABS_Y, REG_A),                      //  D9  CMP $nnnn,Y
    nullptr,                                        //  DA
    nullptr,                                        //  DB
    nullptr,                                        //  DC
    CMP(OPERAND_ABS_X, REG_A),                      //  DD  CMP $nnnn,X
    &Cpu6502::execIncDec<OPERAND_ABS_X, -1>,        //  DE  DEC $nnnn,X
    nullptr,                                        //  DF

    //  0xE0 -- EF  //
    CMP(OPERAND_IMM, REG_X),                        //  E0  CPX #imm
    SBC(OPERAND_IND_X),                             //  E1  SBC ($nn,X)
    DOP(OPERAND_IMM),                               //  E2  dop #imm
    ISB(OPERAND_IND_X),                             //  E3  isb ($nn,X)
    CMP(OPERAND_ZERPG, REG_X),                      //  E4  CPX $nn
    SBC(OPERAND_ZERPG),                             //  E5  SBC $nn
    &Cpu6502::execIncDec<OPERAND_ZERPG, +1>,        //  E6  INC $nn
    ISB(OPERAND_ZERPG),                             //  E7  isb $nn
    &Cpu6502::execIncDecReg<REG_X, +1>,             //  E8  INX
    SBC(OPERAND_IMM),                               //  E9  SBC #imm
    nullptr,                                        //  EA  NOP
    SBC(OPERAND_IMM),                               //  EB  sbc $imm
    CMP(OPERAND_ABSOL, REG_X),                      //  EC  CPX $nnnn
    SBC(OPERAND_ABSOL),                             //  ED  SBC $nnnn
    &Cpu6502::execIncDec<OPERAND_ABSOL, +1>,        //  EE  INC $nnnn
    ISB(OPERAND_ABSOL),                             //  EF  isb $nnnn

    //  0xF0 -- FF  //
    &Cpu6502::execBranch<FLAG_Z, FLAG_Z>,           //  F0  BEQ r
    SBC(OPERAND_IND_Y),                             //  F1  SBC ($nn),Y
    nullptr,                                        //  F2  hlt
    ISB(OPERAND_IND_Y),                             //  F3  isb ($nn),Y
    DOP(OPERAND_ZEROX),                             //  F4  dop $nn,X
    SBC(OPERAND_ZEROX),                             //  F5  SBC $nn,X
    &Cpu6502::execIncDec<OPERAND_ZEROX, +1>,        //  F6  INC $nn,X
    ISB(OPERAND_ZEROX),                             //  F7  isb $nn,X
    &Cpu6502::execSetFlag<0x08>,                    //  F8  SED
    SBC(OPERAND_ABS_Y),                             //  F9  SBC $nnnn,Y
    nullptr,                                        //  FA  nop
    ISB(OPERAND_ABS_Y),                             //  FB  isb $nnnn,Y
    TOP(OPERAND_ABS_X),                             //  FC  top $nnnn,X
    SBC(OPERAND_ABS_X),                             //  FD  SBC $nnnn,X
    &Cpu6502::execIncDec<OPERAND_ABS_X, +1>,        //  FE  INC $nnnn,X
    ISB(OPERAND_ABS_X),                             //  FF  isb $nnnn,X
};


}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

//  このファイルでしか使わないマクロを解除  //
#undef      ADC
#undef      AND
#undef      BIT
#undef      CMP
#undef      STR
#undef      TOP

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

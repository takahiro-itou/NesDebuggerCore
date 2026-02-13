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
**      An Implementation of Test Case 'DisCpu6502'.
**
**      @file       NesMan/Tests/DisCpu6502Test.cpp
**/

#include    "TestDriver.h"
#include    "../Cpu6502/Dis6502.h"

#include    "../Cpu6502/InstTable.h"


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

#define     ADC     "ADC"
#define     AND     "AND"
#define     ASL     "ASL"
#define     BCC     "BCC"
#define     BCS     "BCS"
#define     BEQ     "BEQ"
#define     BIT     "BIT"
#define     BMI     "BMI"
#define     BNE     "BNE"
#define     BPL     "BPL"
#define     BRK     "BRK"
#define     BVC     "BVC"
#define     BVS     "BVS"
#define     CLC     "CLC"
#define     CLD     "CLD"
#define     CLI     "CLI"
#define     CLV     "CLV"
#define     CMP     "CMP"
#define     CPX     "CPX"
#define     CPY     "CPY"
#define     DEC     "DEC"
#define     DEX     "DEX"
#define     DEY     "DEY"
#define     EOR     "EOR"
#define     INC     "INC"
#define     INX     "INX"
#define     INY     "INY"
#define     JMP     "JMP"
#define     JSR     "JSR"
#define     LDA     "LDA"
#define     LDX     "LDX"
#define     LDY     "LDY"
#define     LSR     "LSR"
#define     NOP     "NOP"
#define     ORA     "ORA"
#define     PLA     "PLA"
#define     PLP     "PLP"
#define     PHA     "PHA"
#define     PHP     "PHP"
#define     ROL     "ROL"
#define     ROR     "ROR"
#define     RTI     "RTI"
#define     RTS     "RTS"
#define     SBC     "SBC"
#define     SEC     "SEC"
#define     SED     "SED"
#define     SEI     "SEI"
#define     STA     "STA"
#define     STX     "STX"
#define     STY     "STY"
#define     TAX     "TAX"
#define     TAY     "TAY"
#define     TSX     "TSX"
#define     TXA     "TXA"
#define     TXS     "TXS"
#define     TYA     "TYA"

#define     ALR     "alr"
#define     ARR     "arr"
#define     ANC     "anc"
#define     ANE     "ane"
#define     DCP     "dcp"
#define     DOP     "nop"
#define     HLT     "hlt"
#define     ISB     "isb"
#define     LAS     "las"
#define     LAX     "lax"
#define     RLA     "rla"
#define     RRA     "rra"
#define     SAX     "sax"
#define     SBX     "sbx"
#define     SHA     "sha"
#define     SHS     "shs"
#define     SHX     "shx"
#define     SHY     "shy"
#define     SLO     "slo"
#define     SRE     "sre"
#define     TOP     "nop"

#define     UNOP    "nop"
#define     USBC    "sbc"

CONSTEXPR_VAR   OpeCode     NUM_OPS = 256;

CONSTEXPR_VAR
const  char  *  ops[NUM_OPS] = {
    //  0x00 -- 1F  //
    BRK, ORA, HLT, SLO,  DOP, ORA, ASL, SLO,
    PHP, ORA, ASL, ANC,  TOP, ORA, ASL, SLO,
    BPL, ORA, HLT, SLO,  DOP, ORA, ASL, SLO,
    CLC, ORA,UNOP, SLO,  TOP, ORA, ASL, SLO,

    //  0x20 -- 3F  //
    JSR, AND, HLT, RLA,  BIT, AND, ROL, RLA,
    PLP, AND, ROL, ANC,  BIT, AND, ROL, RLA,
    BMI, AND, HLT, RLA,  DOP, AND, ROL, RLA,
    SEC, AND,UNOP, RLA,  TOP, AND, ROL, RLA,

    //  0x40 -- 5F  //
    RTI, EOR, HLT, SRE,  DOP, EOR, LSR, SRE,
    PHA, EOR, LSR, ALR,  JMP, EOR, LSR, SRE,
    BVC, EOR, HLT, SRE,  DOP, EOR, LSR, SRE,
    CLI, EOR,UNOP, SRE,  TOP, EOR, LSR, SRE,

    //  0x60 -- 7F  //
    RTS, ADC, HLT, RRA,  DOP, ADC, ROR, RRA,
    PLA, ADC, ROR, ARR,  JMP, ADC, ROR, RRA,
    BVS, ADC, HLT, RRA,  DOP, ADC, ROR, RRA,
    SEI, ADC,UNOP, RRA,  TOP, ADC, ROR, RRA,

    //  0x80 -- 9F  //
    DOP, STA, DOP, SAX,  STY, STA, STX, SAX,
    DEY, DOP, TXA, ANE,  STY, STA, STX, SAX,
    BCC, STA, HLT, SHA,  STY, STA, STX, SAX,
    TYA, STA, TXS, SHS,  SHY, STA, SHX, SHA,

    //  0xA0 -- BF  //
    LDY, LDA, LDX, LAX,  LDY, LDA, LDX, LAX,
    TAY, LDA, TAX, LAX,  LDY, LDA, LDX, LAX,
    BCS, LDA, HLT, LAX,  LDY, LDA, LDX, LAX,
    CLV, LDA, TSX, LAS,  LDY, LDA, LDX, LAX,

    //  0xC0 -- DF  //
    CPY, CMP, DOP, DCP,  CPY, CMP, DEC, DCP,
    INY, CMP, DEX, SBX,  CPY, CMP, DEC, DCP,
    BNE, CMP, HLT, DCP,  DOP, CMP, DEC, DCP,
    CLD, CMP,UNOP, DCP,  TOP, CMP, DEC, DCP,

    //  0xE0 -- FF  //
    CPX, SBC, DOP, ISB,  CPX, SBC, INC, ISB,
    INX, SBC, NOP,USBC,  CPX, SBC, INC, ISB,
    BEQ, SBC, HLT, ISB,  DOP, SBC, INC, ISB,
    SED, SBC,UNOP, ISB,  TOP, SBC, INC, ISB,
};


//========================================================================
//
//    DisCpu6502Test  class.
//
/**
**    クラス DisCpu6502 の単体テスト。
**/

class  DisCpu6502Test : public  TestFixture
{
    CPPUNIT_TEST_SUITE(DisCpu6502Test);
    CPPUNIT_TEST(testAddressing);
    CPPUNIT_TEST(testMnemonicMap);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testAddressing();
    void  testMnemonicMap();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DisCpu6502Test );

//========================================================================
//
//    Tests.
//

void  DisCpu6502Test::testAddressing()
{
    OpeCode mis = 0;
    char    buf[32];
    CONSTEXPR_VAR  int  amBytes[] = {
        1, 1, 2, 2, 2, 2,  3, 3, 3,  2, 2, 2, 3,
        1, 1, 2, 3,
    };

    for ( OpeCode opeCode = 0; opeCode < NUM_OPS; ++ opeCode ) {
        const   AddressingMode::ModeValues  am
            = AddressingMode::g_opeCodeAddrs[opeCode];
        const   int         expByte = amBytes[am];
        const   ClockCount  expCycl = 0;

        const   int         actByte = g_opeCodeSize[opeCode];
        if ( expByte != actByte ) {
            snprintf(buf, sizeof(buf), "0x%02X", opeCode);
            std::cerr   <<  "\nOpeCode = "  <<  buf
                        <<  "\nExpect  = "  <<  expByte
                        <<  "\nActual  = "  <<  actByte
                        <<  std::endl;
            ++ mis;
        }
    }

    CPPUNIT_ASSERT_EQUAL(OpeCode(0), mis);
    return;
}

void  DisCpu6502Test::testMnemonicMap()
{
    OpeCode mis = 0;
    char    buf[32];

    for ( OpeCode opeCode = 0; opeCode < NUM_OPS; ++ opeCode ) {
        const  std::string  expect  = ops[opeCode];
        const  std::string  actual  = dumpMnemonicMap(opeCode);
        if ( expect != actual ) {
            snprintf(buf, sizeof(buf), "0x%02X", opeCode);
            std::cerr   <<  "\nOpeCode = "  <<  buf
                        <<  "\nExpect  = "  <<  expect
                        <<  "\nActual  = "  <<  actual
                        <<  std::endl;
            ++ mis;
        }
    }

    CPPUNIT_ASSERT_EQUAL(OpeCode(0), mis);
    return;
}

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}

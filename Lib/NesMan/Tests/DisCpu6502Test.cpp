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
#define     EOR     "EOR"
#define     JMP     "JMP"
#define     JSR     "JSR"
#define     LSR     "LSR"
#define     ORA     "ORA"
#define     PLA     "PLA"
#define     PLP     "PLP"
#define     PHA     "PHA"
#define     PHP     "PHP"
#define     ROL     "ROL"
#define     ROR     "ROR"
#define     RTI     "RTI"
#define     RTS     "RTS"
#define     SEC     "SEC"
#define     SED     "SED"
#define     SEI     "SEI"

#define     ALR     "alr"
#define     ARR     "arr"
#define     ANC     "anc"
#define     DOP     "nop"
#define     HLT     "hlt"
#define     RLA     "rla"
#define     RRA     "rra"
#define     SLO     "slo"
#define     SRE     "sre"
#define     TOP     "nop"

#define     UNOP    "nop"

CONSTEXPR_VAR
const  char  *  ops[128] = {
    //  0x00 -- 1F  //
    BRK, ORA, HLT, SLO,  DOP, ORA, ASL, SLO,
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
    CPPUNIT_TEST(testMnemonicMap);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testCtor();
    void  testMnemonicMap();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DisCpu6502Test );

//========================================================================
//
//    Tests.
//

void  DisCpu6502Test::testMnemonicMap()
{
    OpeCode mis = 0;
    char    buf[32];

    for ( OpeCode opeCode = 0; opeCode < 8; ++ opeCode ) {
        const  std::string  expect  = ops[opeCode];
        const  std::string  actual  = dumpMnemonicMap(opeCode);
        if ( expect != actual ) {
            snprintf(buf, sizeof(buf), "0x%02x", opeCode);
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

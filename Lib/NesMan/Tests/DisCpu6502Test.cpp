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

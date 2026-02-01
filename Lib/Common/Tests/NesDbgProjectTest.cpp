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
**      An Implementation of Test Case 'NesDbgProject'.
**
**      @file       Common/Tests/NesDbgProjectTest.cpp
**/

#include    "TestDriver.h"
#include    "NesDbg/Common/NesDbgProject.h"


NESDBG_NAMESPACE_BEGIN

//========================================================================
//
//    NesDbgProjectTest  class.
//
/**
**    クラス NesDbgProject の単体テスト。
**/

class  NesDbgProjectTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(NesDbgProjectTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( NesDbgProjectTest );

//========================================================================
//
//    Tests.
//

void  NesDbgProjectTest::testNameSpace()
{
    return;
}

NESDBG_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}

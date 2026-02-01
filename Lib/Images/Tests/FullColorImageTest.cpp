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
**      An Implementation of Test Case 'FullColorImage'.
**
**      @file       Images/Tests/FullColorImageTest.cpp
**/

#include    "TestDriver.h"
#include    "NesDbg/Images/FullColorImage.h"


SAMPLE_NAMESPACE_BEGIN
namespace  Images  {

//========================================================================
//
//    FullColorImageTest  class.
//
/**
**    クラス FullColorImage の単体テスト。
**/

class  FullColorImageTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(FullColorImageTest);
    CPPUNIT_TEST(testCtor);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testCtor();
};

CPPUNIT_TEST_SUITE_REGISTRATION( FullColorImageTest );

//========================================================================
//
//    Tests.
//

void  FullColorImageTest::testCtor()
{
    FullColorImage  testee;

    return;
}

}   //  End of namespace  Images
SAMPLE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}

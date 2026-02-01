//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---  Library Project.  ---                      **
**                                                                      **
**          Copyright (C), 2016-2024, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'Bar'.
**
**      @file       Bar/Tests/BarTest.cpp
**/

#include    "TestDriver.h"
#include    "Sample/Bar/Bar.h"


SAMPLE_NAMESPACE_BEGIN
namespace  Bar  {

//========================================================================
//
//    BarTest  class.
//
/**
**    クラス Bar  の単体テスト。
**/

class  BarTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(BarTest);
    CPPUNIT_TEST(testFunctionBar1);
    CPPUNIT_TEST(testFunctionBar2);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testFunctionBar1();
    void  testFunctionBar2();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BarTest );

//========================================================================
//
//    Tests.
//

void  BarTest::testFunctionBar1()
{
    CPPUNIT_ASSERT_EQUAL( 0, Bar::functionBar(0) );
    CPPUNIT_ASSERT_EQUAL( 1, Bar::functionBar(1) );
    CPPUNIT_ASSERT_EQUAL( 4, Bar::functionBar(2) );
    CPPUNIT_ASSERT_EQUAL( 9, Bar::functionBar(3) );
}

void  BarTest::testFunctionBar2()
{
    CPPUNIT_ASSERT_EQUAL( 1, Bar::functionBar(-1) );
    CPPUNIT_ASSERT_EQUAL( 4, Bar::functionBar(-2) );
    CPPUNIT_ASSERT_EQUAL( 9, Bar::functionBar(-3) );
}

}   //  End of namespace  Bar
SAMPLE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}

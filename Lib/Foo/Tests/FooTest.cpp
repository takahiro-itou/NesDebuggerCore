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
**      An Implementation of Test Case 'Foo'.
**
**      @file       Foo/Tests/FooTest.cpp
**/

#include    "TestDriver.h"
#include    "Sample/Foo/Foo.h"


SAMPLE_NAMESPACE_BEGIN
namespace  Foo  {

//========================================================================
//
//    FooTest  class.
//
/**
**    クラス Foo  の単体テスト。
**/

class  FooTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(FooTest);
    CPPUNIT_TEST(testFunctionFoo1);
    CPPUNIT_TEST(testFunctionFoo2);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testFunctionFoo1();
    void  testFunctionFoo2();
};

CPPUNIT_TEST_SUITE_REGISTRATION( FooTest );

//========================================================================
//
//    Tests.
//

void  FooTest::testFunctionFoo1()
{
    CPPUNIT_ASSERT_EQUAL(   1, Foo::functionFoo( 0,  1) );
    CPPUNIT_ASSERT_EQUAL(  13, Foo::functionFoo( 2,  3) );
    CPPUNIT_ASSERT_EQUAL(  25, Foo::functionFoo( 3,  4) );
    CPPUNIT_ASSERT_EQUAL( 169, Foo::functionFoo( 5, 12) );
}

void  FooTest::testFunctionFoo2()
{
    CPPUNIT_ASSERT_EQUAL(  25, Foo::functionFoo( 4,  3) );
    CPPUNIT_ASSERT_EQUAL( 169, Foo::functionFoo(12,  5) );
}

}   //  End of namespace  Foo
SAMPLE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}

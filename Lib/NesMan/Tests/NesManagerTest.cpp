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
**      An Implementation of Test Case 'NesManager'.
**
**      @file       NesMan/Tests/NesManagerTest.cpp
**/

#include    "TestDriver.h"
#include    "NesDbg/NesMan/NesManager.h"

#include    "TestConf.h"


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//========================================================================
//
//    NesManagerTest  class.
//
/**
**    クラス NesManager の単体テスト。
**/

class  NesManagerTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(NesManagerTest);
    CPPUNIT_TEST(testCtor);
    CPPUNIT_TEST(testOpenRomFileError);
    CPPUNIT_TEST(testOpenRomFileValid);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testCtor();
    void  testOpenRomFileError();
    void  testOpenRomFileValid();
};

CPPUNIT_TEST_SUITE_REGISTRATION( NesManagerTest );

//========================================================================
//
//    Tests.
//

void  NesManagerTest::testCtor()
{
    NesManager  testee;

    return;
}

void  NesManagerTest::testOpenRomFileError()
{
    ErrCode     retCode;
    NesManager  testee;

    retCode = testee.openRomFile("no-such-file");
    CPPUNIT_ASSERT_EQUAL( ErrCode::FILE_OPEN_ERROR, retCode );

    retCode = testee.openRomFile("/dev/null");
    CPPUNIT_ASSERT_EQUAL( ErrCode::FILE_IO_ERROR, retCode );

    return;
}

void  NesManagerTest::testOpenRomFileValid()
{
    ErrCode     retCode;
    NesManager  testee;

    retCode = testee.openRomFile(LIBTOP_SOURCE_DIR "/GbaMan/Tests/hello.nes");
    //  CPPUNIT_ASSERT_EQUAL( ErrCode::SUCCESS, retCode );

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

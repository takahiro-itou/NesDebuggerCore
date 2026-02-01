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
**      An Interface of Foo class.
**
**      @file       Foo/Foo.h
**/

#if !defined( SAMPLE_FOO_INCLUDED_FOO_H )
#    define   SAMPLE_FOO_INCLUDED_FOO_H

#include    "Sample/Common/SampleSettings.h"


SAMPLE_NAMESPACE_BEGIN
namespace  Foo  {

//========================================================================
//
//    Foo  class.
//

class  Foo
{

//========================================================================
//
//    Constructor(s) and Destructor.
//

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//
public:

    static  CommonType
    functionFoo(
            CommonType  x,
            CommonType  y);

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   FooTest;
};

}   //  End of namespace  Foo
SAMPLE_NAMESPACE_END

#endif

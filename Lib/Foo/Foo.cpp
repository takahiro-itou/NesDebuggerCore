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
**      An Implementation of Foo class.
**
**      @file       Foo/Foo.h
**/

#include    "Sample/Foo/Foo.h"

#include    "Sample/Bar/Bar.h"


SAMPLE_NAMESPACE_BEGIN
namespace  Foo  {

//========================================================================
//
//    Foo  class.
//

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

CommonType
Foo::functionFoo(
        CommonType  x,
        CommonType  y)
{
    return ( Bar::Bar::functionBar(x) + Bar::Bar::functionBar(y) );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Foo
SAMPLE_NAMESPACE_END

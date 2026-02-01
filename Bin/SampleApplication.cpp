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
**      サンプルプログラム。
**
**      @file       Bin/SampleApplication.cpp
**/

#include    "Sample/Foo/Foo.h"

#include    <iostream>

using   namespace   SAMPLE_NAMESPACE;

int  main(int argc, char * argv[])
{
    std::cout   <<  Foo::Foo::functionFoo(2, 3)
                <<  std::endl;
    return ( 0 );
}

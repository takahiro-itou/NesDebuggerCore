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
**      サンプルプログラム。
**
**      @file       Bin/SampleApplication.cpp
**/

#include    "NesDbg/Common/SampleDocument.h"

#include    <iostream>

using   namespace   NESDBG_NAMESPACE;

int  main(int argc, char * argv[])
{
    Common::SampleDocument  test;
    std::string     input;

    std::cout   <<  "Input:";
    std::cin    >>  input;

    test.setMessage(input);
    std::cout   <<  "The number of alphabet in "
                <<  input
                <<  " = "
                <<  test.countAlphabet()
                <<  std::endl;
    return ( 0 );
}

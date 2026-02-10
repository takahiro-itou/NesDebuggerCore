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

#include    "NesDbg/NesMan/BaseCpuCore.h"
#include    "NesDbg/NesMan/NesManager.h"

#include    <iostream>
#include    <time.h>


using   namespace   NESDBG_NAMESPACE;

int  main(int argc, char * argv[])
{
    ErrCode retCode = ErrCode::SUCCESS;;
    NesMan::NesManager  manNes;

    if ( argc < 2 ) {
        std::cerr   <<  "Usage "
                    <<  argv[0]
                    <<  " [rom file]"
                    <<  std::endl;
        return ( 1 );
    }

    if ( (retCode = manNes.openRomFile(argv[1])) != ErrCode::SUCCESS ) {
        std::cerr   <<  "ERROR : Open ROM "
                    <<  argv[1] <<  std::endl;
        return ( 1 );
    }

    //  ハードリセットを行う。  //
    manNes.doHardReset();

    //  最初のレジスタをダンプ。    //
    std::cout   <<  "REGS\n";
    manNes.printRegisters(std::cout)
            <<  std::endl;

    return ( 0 );
}

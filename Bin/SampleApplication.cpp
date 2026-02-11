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

    NesMan::InstExecResult  ret = NesMan::InstExecResult::SUCCESS_CONTINUE;
    NesMan::CounterInfo     ci;
    GuestMemoryAddress      gmNext  = 0;
    int     cnt     = 0;
    clock_t clkSta  = clock();
    while ( ret != NesMan::InstExecResult::UNDEFINED_OPECODE ) {
        ret = manNes.executeCurrentInst();

        //  レジスタをダンプ。  //
        std::cout   <<  "REGS\n";
        manNes.printRegisters(std::cout)
                <<  std::endl;

        //  次の命令を逆アセンブル。    //
        std::cout   <<  "Mnemonic:\t"  <<  cnt  <<  "\n";
        manNes.writeMnemonic(std::cout, manNes.getNextPC(), gmNext)
                <<  std::endl;

        ++ cnt;
        if ( !(cnt & 0x07FFFFFF) ) {
            ci  = manNes.getCpuCounters();
            ClockCount  cc  = ci.totalCycles;
            clock_t clkEnd  = clock();
            const double elapsed = static_cast<double>(clkEnd - clkSta)
                    * 1000.0 / CLOCKS_PER_SEC;
            std::cout   <<  "Instructions: "
                        <<  ci.numOpeCodes  <<  ", "
                        <<  elapsed <<  "ms : "
                        <<  (cnt / elapsed) <<  " kHz\n"
                        <<  "Clock Counts: "
                        <<  cc  <<  ", "
                        <<  elapsed <<  "ms : "
                        <<  (cc / elapsed)  <<  " kHz"
                        <<  std::endl;
        }
    }

    ci  = manNes.getCpuCounters();
    ClockCount  cc  = ci.totalCycles;
    clock_t clkEnd  = clock();
    const double elapsed = static_cast<double>(clkEnd - clkSta)
                                * 1000.0 / CLOCKS_PER_SEC;
    std::cout   <<  "Instructions: "
                <<  cnt <<  ", "
                <<  elapsed <<  "ms : "
                <<  (cnt / elapsed) <<  " kHz\n"
                <<  "Clock Counts: "
                <<  cc  <<  ", "
                <<  elapsed <<  "ms : "
                <<  (cc / elapsed)  <<  " kHz"
                <<  std::endl;
    return ( 0 );
}

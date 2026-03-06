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
#include    "NesDbg/NesMan/BasePpuCore.h"
#include    "NesDbg/NesMan/NesManager.h"
#include    "../Lib/NesMan/PpuNes/NesPpuImpl.h"

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

    //  PPU を初期化する。  //
    NesMan::NesPpuImpl  manPpu(manNes, manNes.getMemoryManager());

    //  ハードリセットを行う。  //
    manNes.doHardReset();

    NesMan::InstExecResult  ret = NesMan::InstExecResult::SUCCESS_CONTINUE;
    NesMan::CounterInfo     ci;
    GuestMemoryAddress      pcPrev, pcWork;
    GuestMemoryAddress      pcNext  = 0;
    ClockCount  cnt     = 0;

    //  最初のレジスタをダンプ。    //
    std::cout   <<  "REGS\n";
    manNes.printRegisters(std::cout)
            <<  std::endl;

    //  最初の命令を逆アセンブル。    //
    std::cout   <<  "Mnemonic:\t"  <<  cnt  <<  "\n";
    pcNext = pcPrev = manNes.getNextPC();
    for ( int i = 0; i < 8; ++i ) {
        manNes.writeMnemonic(std::cout, pcNext, pcNext)
                <<  std::endl;
    }

    clock_t clkSta  = clock();
    while ( ret != NesMan::InstExecResult::UNDEFINED_OPECODE ) {
        ret = manNes.executeCurrentInst();
        manNes.updateCounters();

#if defined( _DEBUG )
        //  レジスタをダンプ。  //
        std::cout   <<  "\nREGS\n";
        manNes.printRegisters(std::cout)
                <<  std::endl;

        //  次の命令を逆アセンブル。    //
        std::cout   <<  "Mnemonic:\t"  <<  cnt  <<  "\n";
        pcNext  = pcPrev;
        pcWork  = manNes.getNextPC();
        for ( int i = 0; i < 8; ++i ) {
            if ( i == 1 && pcNext != pcWork ) {
                std::cout   <<  " --------------------------------\n";
                pcNext  = pcWork;
            }
            manNes.writeMnemonic(std::cout, pcNext, pcNext)
                    <<  std::endl;
        }
        pcPrev  = pcWork;
#endif

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

    manNes.updateCounters();
    ci  = manNes.getCpuCounters();
    ClockCount  cc  = ci.totalCycles;
    clock_t clkEnd  = clock();
    const double elapsed = static_cast<double>(clkEnd - clkSta)
                                * 1000.0 / CLOCKS_PER_SEC;

    {
        //  レジスタをダンプ。  //
        std::cout   <<  "\nREGS\n";
        manNes.printRegisters(std::cout)
                <<  std::endl;

        //  次の命令を逆アセンブル。    //
        std::cout   <<  "Mnemonic:\t"  <<  cnt  <<  "\n";
        pcNext  = pcPrev;
        for ( int i = 0; i < 8; ++i ) {
            manNes.writeMnemonic(std::cout, pcNext, pcNext)
                    <<  std::endl;
        }

        std::cout   <<  "Instructions: "
                    <<  cnt <<  ", "
                    <<  elapsed <<  "ms : "
                    <<  (cnt / elapsed) <<  " kHz\n"
                    <<  "Clock Counts: "
                    <<  cc  <<  ", "
                    <<  elapsed <<  "ms : "
                    <<  (cc / elapsed)  <<  " kHz"
                    <<  std::endl;
    }

    return ( 0 );
}

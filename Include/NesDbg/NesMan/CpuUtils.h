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
**      An Interface of CpuUtils class.
**
**      @file       NesMan/CpuUtils.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_CPU_UTILS_H )
#    define   NESDBG_NESMAN_INCLUDED_CPU_UTILS_H

#if !defined( NESDBG_PCH_INCLUDED_PRE_COMPILE_H )
#    include    "NesDbg/pch/PreCompile.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {


//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    命令の実行結果。
**/

enum class  InstExecResult
{
    /**
    **    正常に実行された。
    **
    **    インタープリターは引き続き次の命令を実行する。
    **/
    SUCCESS_CONTINUE    = 0,

    /**
    **    未定義の命令が実行され、プロセッサが停止した。
    **/
    UNDEFINED_OPECODE   = 1,

    /**
    **    正常に実行されたが、ブレークポイントにヒットした。
    **/
    SUCCESS_BREAKPOINT  = 2,

    /**
    **    正常に実行されたが、次の命令が未定義命令のため、
    **  それを実行する手前でいったん停止した。
    **/
    BEFORE_UNDEFINED    = 3,
};


//----------------------------------------------------------------
/**
**    フラグレジスタ。
**/

enum  StatusRegister  {
    FLAG_N  = 0x80,     //  bit 7 : Negative
    FLAG_V  = 0x40,     //  bit 6 : Overflow
    FLAG_R  = 0x20,     //  bit 5 : Reserved
    FLAG_B  = 0x10,     //  bit 4 : Break
    FLAG_D  = 0x08,     //  bit 3 : Decimal
    FLAG_I  = 0x04,     //  bit 2 : Interrupt
    FLAG_Z  = 0x02,     //  bit 1 : Zero
    FLAG_C  = 0x01,     //  bit 0 : Carry
};


//----------------------------------------------------------------
/**
**    レジスタを管理する構造体。
**/

struct  RegBank
{
    RegType     Zr;     /**<  番兵。        **/

    RegType     A;      /**<  A レジスタ。  **/
    RegType     X;      /**<  X レジスタ。  **/
    RegType     Y;      /**<  Y レジスタ。  **/
    RegType     S;      /**<  S レジスタ。  **/
    RegType     P;      /**<  ステータスレジスタ。  **/

    RegType     rs0;    /**<  予約。アライメント調整。  **/
    RegType     rs1;    /**<  予約。アライメント調整。  **/

    /**  プログラムカウンタ。   **/
    GuestMemoryAddress  PC;
};


//----------------------------------------------------------------
/**
**    レジスタ構造体の特定のレジスタを指すポインタ型。
**/

typedef     RegType (RegBank::* TRegPtr);


//----------------------------------------------------------------
/**
**    カウンタ関連の情報を管理する構造体。
**/

struct  CounterInfo
{
    /**   実行した命令のサイクル数の合計。  **/
    ClockCount          totalCycles;

    /**   実行した命令の総数。  **/
    ClockCount          numOpeCodes;

    /**   最後に実行した命令のサイクル数。  **/
    ClockCount          lastCycles;

    /**   最後の VBlank からのサイクル数。  **/
    ClockCount          clockCycles;

    /**   次の VBlank までの残サイクル数。  **/
    ClockCount          remainClock;
};


//----------------------------------------------------------------
/**
**    PPU カウンタの状態。
**/

enum class  PpuScanLine
{
    /**   通常の描画中。        **/
    VISIBLE_SCANLINE        = 0,

    /**   アイドル期間。        **/
    POST_RENDER_SCANLINE    = 1,

    /**   垂直帰線期間の開始。  **/
    START_VERTICAL_BLANK    = 2,

    /**   垂直帰線期間中。      **/
    VERTICAL_BLANKING_LINE  = 3,

    /**   垂直帰線期間の終了。  **/
    PRE_RENDER_SCANLINE     = 4,
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

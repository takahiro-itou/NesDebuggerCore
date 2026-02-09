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
**      Utility Macros/Functions.
**
**      @file       Common/NesDbgUtils.h
**/

#if !defined( NESDBG_COMMON_INCLUDED_NESDBG_UTILS_H )
#    define   NESDBG_COMMON_INCLUDED_NESDBG_UTILS_H

#if !defined( NESDBG_COMMON_INCLUDED_NESDBG_TYPES_H )
#    include    "NesDbgTypes.h"
#endif


//================================================================
//
//    補助マクロ
//

//
//    分岐予測に関するマクロ
//

#if defined( __GNUC__ )
#    define     LIKELY(x)       __builtin_expect(!!(x), 1)
#    define     UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#    define     LIKELY(x)       (x)
#    define     UNLIKELY(x)     (x)
#endif


/**
**    引数を可能な限りレジスタで渡すようにする。
**/

#if defined(__i386__) || defined(__x86_64__)
#    define     NESDBG_REGPARM      __attribute__((regparm(2)))
#else
#    define     NESDBG_REGPARM
#endif


//=========================================================================
//
//    未使用の変数と引数の警告対応。
//

/**
**    未使用の変数に対する警告を抑制するマクロ。
**/

#define     NESDBG_UNUSED_VAR(var)      (void)(var)

/**
**    未使用の仮引数に対する警告を抑制するマクロ。
**/

#define     NESDBG_UNUSED_ARG(var)      (void)(var)


NESDBG_NAMESPACE_BEGIN

//========================================================================
/**
**    配列の要素数を取得する。
**/

template  <typename  T,  size_t  N>
CONSTEXPR_FUNC
size_t  getArraySize(T  (&)[N])
{
    return ( N );
}

NESDBG_NAMESPACE_END

#endif

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
**      プロジェクトの設定。
**
**      @file       Common/NesDbgProject.h
**/

#if !defined( NESDBG_COMMON_INCLUDED_NESDBG_PROJECT_H )
#    define   NESDBG_COMMON_INCLUDED_NESDBG_PROJECT_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#if defined( NESDBG_USE_PRE_CONFIGURED_MSVC )
#    include    "NesDbg/.Config/PreConfigNesDbg.msvc.h"
#else
#    include    "NesDbg/.Config/ConfiguredNesDbg.h"
#endif

NESDBG_NAMESPACE_BEGIN

/**
**    ダミーの型宣言。
**/

typedef     int     CommonType;

NESDBG_NAMESPACE_END

#endif

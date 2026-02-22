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
**      An Implementation of NesPpuImpl class.
**
**      @file       NesMan/NesPpuImpl.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "NesPpuImpl.h"

#include    "NesDbg/NesMan/MemoryManager.h"
#include    "NesDbg/Images/FullColorImage.h"


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    NesPpuImpl  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

NesPpuImpl::NesPpuImpl(
        NesManager    & manNes,
        MemoryManager & manMem)
    : Super(manNes, manMem)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

NesPpuImpl::~NesPpuImpl()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//----------------------------------------------------------------
//    画面を描画する。
//

ErrCode
NesPpuImpl::drawScreen()
{
    this->m_pImage->drawSample();

    return ( ErrCode::SUCCESS );
}

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

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

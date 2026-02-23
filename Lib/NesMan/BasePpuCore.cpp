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
**      An Implementation of BasePpuCore class.
**
**      @file       NesMan/BasePpuCore.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "NesDbg/NesMan/BasePpuCore.h"
#include    "NesDbg/NesMan/MemoryManager.h"

#include    "NesDbg/Images/FullColorImage.h"

#include    <cstring>


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    BasePpuCore  class.
//

//========================================================================
//
//    Internal Type Definitions.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

BasePpuCore::BasePpuCore(
        NesManager    & manNes,
        MemoryManager & manMem)
    : m_pImage(nullptr),
      m_vMemBuf(),
      m_memPPU(nullptr)
{
    this->m_vMemBuf.clear();
    this->m_vMemBuf.resize(65536);
    this->m_memPPU  = &(this->m_vMemBuf[0]);

    memcpy(this->m_memPPU, manMem.getChrBank(), 0x2000);
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BasePpuCore::~BasePpuCore()
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

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    画面を描画する。
//

ErrCode
BasePpuCore::drawScreen()
{
    const  int  iW  = this->m_pImage->getWidth();
    const  int  iH  = this->m_pImage->getHeight();

    this->m_pImage->fillRectangle(0, 0, iW, iH, 0x00FFFFFF);

    return ( ErrCode::SUCCESS );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    描画先のイメージを取得する。
//

Images::FullColorImage  *
BasePpuCore::getScreenImage()  const
{
    return ( this->m_pImage );
}

//----------------------------------------------------------------
//    描画先のイメージを設定する。
//

ErrCode
BasePpuCore::setScreenImage(
        Images::FullColorImage * const  ptrImg)
{
    this->m_pImage  = ptrImg;
    return ( ErrCode::SUCCESS );
}

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

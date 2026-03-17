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

#include    "PpuNes/NesPpuImpl.h"

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
      m_memPPU(),
      m_manMem(manMem),
      m_ppuDead(2),
      m_flgVbl(BOOL_FALSE),
      m_frameNumber(0),
      m_frameCycels(0),
      m_totalCycles(0),
      m_curScanPt({0, 0}),
      m_flgOddFrame(1),
      m_curEndCycle(341)
{
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

//----------------------------------------------------------------
//    電源オンの処理を行う。
//

ErrCode
BasePpuCore::emulatePowerOn()
{
    this->m_curScanPt.x = 1;
    this->m_curScanPt.y = 241;
    this->m_ppuDead     = 2;
    this->m_flgVbl      = BOOL_FALSE;

    this->m_frameNumber = 0;
    this->m_frameCycels = 0;
    this->m_totalCycles = 0;
    this->m_flgOddFrame = 1;
    this->m_curEndCycle = 1;

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    リセットボタン押下の処理を行う。
//

ErrCode
BasePpuCore::emulateResetButton()
{
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    ROM ファイルをロードした後の処理を行う。
//

ErrCode
BasePpuCore::postprocessOpenRom()
{
    memset(this->m_memPPU, 0, sizeof(this->m_memPPU));

    const   LpcByteReadBuf  chrBank = this->m_manMem.getChrBank();
    if ( chrBank == nullptr ) {
        return ( ErrCode::FAILURE );
    }

    memcpy(this->m_memPPU, chrBank, 0x2000);

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    スキャンライン情報を更新する。
//

PpuScanLine
BasePpuCore::updateScanLine(
        const  int  nCycles)
{
    return ( PpuScanLine::VISIBLE_SCANLINE );
}

//----------------------------------------------------------------
//    スキャンライン情報を更新する。
//

PpuScanLine
BasePpuCore::updateScanLine(
        const  CounterInfo  &ctrStep)
{
    return  updateScanLine(static_cast<int>(ctrStep.lastCycles) * 3);
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    PPU インスタンスを生成する。
//

BasePpuCore  *
BasePpuCore::createInstance(
        NesManager    & manNes,
        MemoryManager & manMem)
{
    return  new NesPpuImpl(manNes, manMem);
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在のスキャン位置を取得する。
//

const   NtPoint
BasePpuCore::getCurrentScanPoint()  const
{
    return ( this->m_curScanPt );
}

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

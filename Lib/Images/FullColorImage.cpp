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
**      An Implementation of FullColorImage class.
**
**      @file       Images/FullColorImage.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "NesDbg/Images/FullColorImage.h"


NESDBG_NAMESPACE_BEGIN
namespace  Images  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    FullColorImage  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

FullColorImage::FullColorImage()
    : m_iWidth (0),
      m_iHeight(0),
      m_cbPixel(3),
      m_lStride(0),
      m_lpAlloc(nullptr),
      m_cbAlloc(0),
      m_lpBits(nullptr),
      m_lpOrig(nullptr)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

FullColorImage::~FullColorImage()
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
//    イメージを作成する。
//

FullColorImage::LpWriteBuf
FullColorImage::allocateImage(
        const  PosUnitType  nWidth,
        const  PosUnitType  nHeight,
        const  LenUnitType  cbPixel,
        const  LenUnitType  lStride)
{
    return ( nullptr );
}

//----------------------------------------------------------------
//    バッファの単純コピーができるか確認する。
//

bool
FullColorImage::canCopyBuffer(
        const  FullColorImage  &imgSrc)  const
{
    return ( false );
}

//----------------------------------------------------------------
//    イメージをコピーする。
//

void
FullColorImage::copyImage(
        const  FullColorImage  &imgSrc)
{
}

//----------------------------------------------------------------
//    イメージの指定範囲をコピーする。
//

void
FullColorImage::copyRectangle(
        const  FullColorImage  &imgSrc,
        const  PosUnitType      x1,
        const  PosUnitType      y1,
        const  PosUnitType      x2,
        const  PosUnitType      y2)
{
}

//----------------------------------------------------------------
//    バッファの内容を単純にコピーする。
//

void
FullColorImage::copyToBuffer(
        LpWriteBuf  ptrDst)  const
{
}

//----------------------------------------------------------------
//    イメージを作成する。
//

void
FullColorImage::createImage(
        const  PosUnitType  nWidth,
        const  PosUnitType  nHeight,
        const  LenUnitType  cbPixel,
        const  LenUnitType  lStride,
        LpWriteBuf   const  lpBits)
{
    //  バッファのアドレスと原点に対応するアドレスを保存。  //
    this->m_lpBits  = static_cast<BtByte *>(lpBits);
    if ( lStride < 0 ) {
        //  ボトムアップ形式。  //
        //  座標  (nHeight - 1, 0)  のアドレスを計算する。  //
        this->m_lpOrig  = this->m_lpBits - ((nHeight - 1) * lStride);
    } else {
        //  トップダウン形式。  //
        this->m_lpOrig  = this->m_lpBits;
    }

    this->m_iWidth  = nWidth;
    this->m_iHeight = nHeight;
    this->m_cbPixel = cbPixel;
    this->m_lStride = lStride;
}

//----------------------------------------------------------------
//    サンプル画像を描画する。
//

void
FullColorImage::drawSample(
        const  ColorArgb32  colBG,
        const  ColorArgb32  colTL,
        const  ColorArgb32  colTR,
        const  ColorArgb32  colBL,
        const  ColorArgb32  colBR)
{
    const  int  iW  = this->m_iWidth;
    const  int  iH  = this->m_iHeight;

    fillRectangle(0, 0, iW, iH, 0x00FFFFFF);

    const  int  rW  = iW / 4;
    const  int  rH  = iH / 4;

    fillRectangle(rW * 1, rH * 1, rW * 1 + rW, rH * 1 + rH, 0x000000FF);
    fillRectangle(rW * 2, rH * 1, rW * 2 + rW, rH * 1 + rH, 0x0000FF00);
    fillRectangle(rW * 1, rH * 2, rW * 1 + rW, rH * 2 + rH, 0x00FF0000);
    fillRectangle(rW * 2, rH * 2, rW * 2 + rW, rH * 2 + rH, 0x0000FFFF);
}

//----------------------------------------------------------------
//    確保したバッファを解放する。
//

void
FullColorImage::freeImageBuffer()
{
}


//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    矩形を描画する。
//

void
FullColorImage::fillRectangle(
        const  PosUnitType  x1,
        const  PosUnitType  y1,
        const  PosUnitType  x2,
        const  PosUnitType  y2,
        const  ColorArgb32  color)
{
    const   BtByte  cB  = ( color        & 0xFF);
    const   BtByte  cG  = ((color >>  8) & 0xFF);
    const   BtByte  cR  = ((color >> 16) & 0xFF);

    for ( PosUnitType y = y1; y < y2; ++ y ) {
        unsigned char * ptr = getPixel(x1, y);
        for ( PosUnitType x = x1; x < x2; ++ x ) {
            *(ptr ++) = cB;
            *(ptr ++) = cG;
            *(ptr ++) = cR;
        }
    }

    return;
}

//----------------------------------------------------------------
//    三角形を描画する。
//

void
FullColorImage::fillTriangle(
        const  PosUnitType  x1,
        const  PosUnitType  y1,
        const  PosUnitType  x2,
        const  PosUnitType  y2,
        const  ColorArgb32  color)
{
}

//----------------------------------------------------------------
//    指定したピクセルの色を設定する。
//

void
FullColorImage::setPixelColor(
        const  PosUnitType  x,
        const  PosUnitType  y,
        const  ColorArgb32  color)
{
    const   unsigned  char  cB  = ( color        & 0xFF);
    const   unsigned  char  cG  = ((color >>  8) & 0xFF);
    const   unsigned  char  cR  = ((color >> 16) & 0xFF);

    unsigned char * ptr = getPixel(x, y);

    *(ptr ++) = cB;
    *(ptr ++) = cG;
    *(ptr ++) = cR;

    return;
}

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

}   //  End of namespace  Images
NESDBG_NAMESPACE_END

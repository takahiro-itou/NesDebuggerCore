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

#include    <algorithm>
#include    <cstring>


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
    freeImageBuffer();
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
    LpWritePixelBuf ptrBuf  = this->m_lpAlloc;
    LenUnitType     cbSize  = 0;
    LenUnitType     wStride = lStride;

    //  イメージバッファに必要なサイズを計算する。  //
    if ( wStride == 0 ) {
        wStride = computeBytesPerPixel(nWidth, cbPixel);
    }
    cbSize  = (wStride >= 0 ? wStride : -wStride) * nHeight;

    //  現在確保しているサイズが必要量以上なら再利用。  //
    if ( this->m_cbAlloc < cbSize ) {
        //  サイズが足りないので解放して再度確保する。  //
        freeImageBuffer();
        ptrBuf  = new BtByte [cbSize];
        std::memset(ptrBuf, 0, cbSize);
        this->m_cbAlloc = cbSize;
    }

    this->createImage(nWidth, nHeight, cbPixel, wStride, ptrBuf);
    return ( this->m_lpAlloc = ptrBuf );
}

//----------------------------------------------------------------
//    バッファの単純コピーができるか確認する。
//

bool
FullColorImage::canCopyBuffer(
        const  FullColorImage  &imgSrc)  const
{
    if ( this->m_lStride != imgSrc.m_lStride ) { return  false; }
    if ( this->m_iWidth  != imgSrc.m_iWidth  ) { return  false; }
    if ( this->m_iHeight != imgSrc.m_iHeight ) { return  false; }

    return ( true );
}

//----------------------------------------------------------------
//    行単位の単純コピーができるか確認する。
//

bool
FullColorImage::canCopyLine(
        const  FullColorImage  &imgSrc)  const
{
    if ( this->m_cbPixel != imgSrc.m_cbPixel ) { return false; }

    return ( true );
}

//----------------------------------------------------------------
//    イメージをコピーする。
//

ErrCode
FullColorImage::copyImage(
        const  FullColorImage  &imgSrc)
{
    if ( this->m_lpBits == imgSrc.m_lpBits ) {
        //  コピー元とコピー先が同じなので何もしない。  //
        return ( ErrCode::SUCCESS );
    }

    if ( canCopyBuffer(imgSrc) ) {
        //  単純コピーが可能。  //
        return  imgSrc.copyToBuffer(this->m_lpBits);
    }

    //  画像の小さいほうに合わせて、矩形コピーを実行。  //
    const  PosUnitType  x2  = std::min(this->m_iWidth,  imgSrc.m_iWidth );
    const  PosUnitType  y2  = std::min(this->m_iHeight, imgSrc.m_iHeight);
    return  this->copyRectangle(imgSrc, 0, 0, x2, y2);
}

//----------------------------------------------------------------
//    イメージをコピーする。
//

ErrCode
FullColorImage::copyImage(
        const  FullColorImage  &imgSrc,
        const  PosUnitType      sx,
        const  PosUnitType      sy)
{
    if ( this->m_lpBits == imgSrc.m_lpBits ) {
        //  コピー元とコピー先が同じなので何もしない。  //
        if ( sx == 0 && sy == 0 ) {
            return ( ErrCode::SUCCESS );
        }
        return ( ErrCode::FAILURE );
    }

    //  画像の小さいほうに合わせて、矩形コピーを実行。  //
    const  PosUnitType  w = std::min(this->m_iWidth  - sx, imgSrc.m_iWidth) ;
    const  PosUnitType  h = std::min(this->m_iHeight - sy, imgSrc.m_iHeight);

    if ( canCopyLine(imgSrc) ) {
        //  単純コピーが可能。  //
        return  copyLines(0, 0, imgSrc, sx, sy, w, h);
    }
    return  this->copyRectangle(0, 0, imgSrc, sx, sy, w, h);
}

//----------------------------------------------------------------
//    イメージをコピーする。
//

ErrCode
FullColorImage::copyLines(
        const  PosUnitType      dx,
        const  PosUnitType      dy,
        const  FullColorImage  &imgSrc,
        const  PosUnitType      sx,
        const  PosUnitType      sy,
        const  PosUnitType      w,
        const  PosUnitType      h)
{
    if ( (this->m_iWidth <= dx + w) || (this->m_iHeight <= dy + h) ) {
        return ( ErrCode::INDEX_OUT_OF_RANGE );
    }
    if ( (imgSrc.m_iWidth <= sx + w) || (imgSrc.m_iHeight <= sy + h) ) {
        return ( ErrCode::INDEX_OUT_OF_RANGE );
    }

    const  LenUnitType  cbCopy  = (this->m_cbPixel) * w;
    for ( PosUnitType y = 0; y < h; ++ y ) {
        LpWritePixelBuf  ptrDst = getPixel(dx, dy + y);
        LpcReadPixelBuf  ptrSrc = getPixel(sx, sy + y);
        copyToBuffer(ptrDst, ptrSrc, cbCopy);
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    イメージの指定範囲をコピーする。
//

ErrCode
FullColorImage::copyRectangle(
        const  FullColorImage  &imgSrc,
        const  PosUnitType      x1,
        const  PosUnitType      y1,
        const  PosUnitType      x2,
        const  PosUnitType      y2)
{
    const  LenUnitType  cbCopy  = std::min(this->m_cbPixel, imgSrc.m_cbPixel);
    const  LenUnitType  remDst  = this->m_cbPixel - cbCopy;
    const  LenUnitType  remSrc  = imgSrc.m_cbPixel - cbCopy;

    for ( PosUnitType y = y1; y < y2; ++ y ) {
        LpWritePixelBuf  ptrDst = getPixel(x1, y);
        LpcReadPixelBuf  ptrSrc = getPixel(x1, y);
        for ( PosUnitType x = x1; x < x2; ++ x ) {
            switch ( cbCopy ) {
            case  4:
                *(ptrDst++) = *(ptrSrc++);
                //  no break;
            case  3:
                *(ptrDst++) = *(ptrSrc++);
                //  no break;
            case  2:
                *(ptrDst++) = *(ptrSrc++);
                //  no break;
            case  1:
                *(ptrDst++) = *(ptrSrc++);
                //  no break;
            }
            ptrDst  += remDst;
            ptrSrc  += remSrc;
        }
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    イメージの指定範囲をコピーする。
//

ErrCode
FullColorImage::copyRectangle(
        const  PosUnitType      dx,
        const  PosUnitType      dy,
        const  FullColorImage  &imgSrc,
        const  PosUnitType      sx,
        const  PosUnitType      sy,
        const  PosUnitType      w,
        const  PosUnitType      h)
{
    const  LenUnitType  cbCopy  = std::min(this->m_cbPixel, imgSrc.m_cbPixel);
    const  LenUnitType  remDst  = this->m_cbPixel  - cbCopy;
    const  LenUnitType  remSrc  = imgSrc.m_cbPixel - cbCopy;

    for ( PosUnitType y = 0; y < h; ++ y ) {
        LpWritePixelBuf  ptrDst = getPixel(dx, dy + y);
        LpcReadPixelBuf  ptrSrc = getPixel(sx, sy + y);
        for ( PosUnitType x = 0; x < w; ++ x ) {
            switch ( cbCopy ) {
            case  4:
                *(ptrDst++) = *(ptrSrc++);
                //  no break;
            case  3:
                *(ptrDst++) = *(ptrSrc++);
                //  no break;
            case  2:
                *(ptrDst++) = *(ptrSrc++);
                //  no break;
            case  1:
                *(ptrDst++) = *(ptrSrc++);
                //  no break;
            }
            ptrDst  += remDst;
            ptrSrc  += remSrc;
        }
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    イメージを作成する。
//

ErrCode
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

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    サンプル画像を描画する。
//

ErrCode
FullColorImage::drawSample(
        const  ColorArgb32  colBG,
        const  ColorArgb32  colTL,
        const  ColorArgb32  colTR,
        const  ColorArgb32  colBL,
        const  ColorArgb32  colBR)
{
    const  PosUnitType  iW  = this->m_iWidth;
    const  PosUnitType  iH  = this->m_iHeight;

    fillRectangle(0, 0, iW, iH, colBG);

    const  PosUnitType  rW  = iW / 4;
    const  PosUnitType  rH  = iH / 4;

    fillTriangle(rW * 1, rH * 1, rW * 1 + rW, rH * 1 + rH, colTL);
    fillTriangle(rW * 2, rH * 1, rW * 2 + rW, rH * 1 + rH, colTR);
    fillTriangle(rW * 1, rH * 2, rW * 1 + rW, rH * 2 + rH, colBL);
    fillTriangle(rW * 2, rH * 2, rW * 2 + rW, rH * 2 + rH, colBR);

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    確保したバッファを解放する。
//

ErrCode
FullColorImage::freeImageBuffer()
{
    LpWritePixelBuf ptr = this->m_lpAlloc;
    if ( ptr == nullptr ) {
        return ( ErrCode::SUCCESS );
    }

    delete  [] ptr;
    this->m_lpAlloc = nullptr;
    this->m_cbAlloc = 0;

    this->m_lpBits  = nullptr;
    this->m_lpOrig  = nullptr;

    return ( ErrCode::SUCCESS );
}


//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    バッファの内容を単純にコピーする。
//

ErrCode
FullColorImage::copyToBuffer(
        LpWriteBuf  ptrDst)  const
{
    const  LenUnitType  cbCopy  = this->m_lStride * this->m_iHeight;
    std::memcpy(ptrDst, this->m_lpBits, cbCopy);
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    バッファの内容を単純にコピーする。
//

ErrCode
FullColorImage::copyToBuffer(
        LpWriteBuf   const  ptrDst,
        LpcReadBuf   const  ptrSrc,
        const  LenUnitType  cbCopy)  const
{
    std::memcpy(ptrDst, ptrSrc, cbCopy);
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    矩形を描画する。
//

ErrCode
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
    const   BtByte  cA  = ((color >> 24) & 0xFF);
    const   LenUnitType     cbRems  = this->m_cbPixel - 3;

    for ( PosUnitType y = y1; y < y2; ++ y ) {
        LpWritePixelBuf ptr = getPixel(x1, y);
        for ( PosUnitType x = x1; x < x2; ++ x ) {
            *(ptr ++) = cB;
            *(ptr ++) = cG;
            *(ptr ++) = cR;
            if ( cbRems == 1 ) {
                *(ptr ++) = cA;
            } else {
                ptr += cbRems;
            }
        }
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    三角形を描画する。
//

ErrCode
FullColorImage::fillTriangle(
        const  PosUnitType  x1,
        const  PosUnitType  y1,
        const  PosUnitType  x2,
        const  PosUnitType  y2,
        const  ColorArgb32  color)
{
    const   BtByte  cB  = ( color        & 0xFF);
    const   BtByte  cG  = ((color >>  8) & 0xFF);
    const   BtByte  cR  = ((color >> 16) & 0xFF);
    const   BtByte  cA  = ((color >> 24) & 0xFF);
    const   LenUnitType     cbRems  = this->m_cbPixel - 3;

    PosUnitType tmp = 1;
    for ( PosUnitType y = y1; y < y2; ++ y ) {
        LpWritePixelBuf ptr = getPixel(x1, y);
        PosUnitType  lastX  = (x1 + tmp);
        if ( x2 < lastX ) { lastX = x2; }
        for ( PosUnitType x = x1; x < lastX; ++ x ) {
            *(ptr ++) = cB;
            *(ptr ++) = cG;
            *(ptr ++) = cR;
            if ( cbRems == 1 ) {
                *(ptr ++) = cA;
            } else {
                ptr += cbRems;
            }
        }
        ++ tmp;
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    指定したピクセルの色を設定する。
//

ErrCode
FullColorImage::setPixelColor(
        const  PosUnitType  x,
        const  PosUnitType  y,
        const  ColorArgb32  color)
{
    const   BtByte  cB  = ( color        & 0xFF);
    const   BtByte  cG  = ((color >>  8) & 0xFF);
    const   BtByte  cR  = ((color >> 16) & 0xFF);
    const   BtByte  cA  = ((color >> 24) & 0xFF);
    const   LenUnitType     cbRems  = this->m_cbPixel - 3;

    LpWritePixelBuf ptr = getPixel(x, y);

    *(ptr ++) = cB;
    *(ptr ++) = cG;
    *(ptr ++) = cR;
    if ( cbRems >= 1 ) {
        *(ptr ++) = cA;
    }

    return ( ErrCode::SUCCESS );
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

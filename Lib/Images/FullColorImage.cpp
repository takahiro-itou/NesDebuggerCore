//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---   Graphics Test Project.   ---                  **
**                                                                      **
**          Copyright (C), 2025-2025, Takahiro Itou                     **
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

#include    "Sample/Images/FullColorImage.h"


SAMPLE_NAMESPACE_BEGIN
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
      m_lpBits(nullptr)
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

void
FullColorImage::createImage(
        const  int  nWidth,
        const  int  nHeight,
        const  int  cbPixel,
        const  int  lStride,
        void  *     lpBits)
{
    this->m_iWidth  = nWidth;
    this->m_iHeight = nHeight;
    this->m_cbPixel = cbPixel;
    this->m_lStride = lStride;
    this->m_lpBits  = static_cast<unsigned char *>(lpBits);
}

//----------------------------------------------------------------
//    サンプル画像を描画する。
//

void
FullColorImage::drawSample()
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

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    矩形を描画する。
//

void
FullColorImage::fillRectangle(
        const  int  x1,
        const  int  y1,
        const  int  x2,
        const  int  y2,
        const  int  color)
{
    const   unsigned  char  cB  = ( color        & 0xFF);
    const   unsigned  char  cG  = ((color >>  8) & 0xFF);
    const   unsigned  char  cR  = ((color >> 16) & 0xFF);

    for ( int y = y1; y < y2; ++ y ) {
        unsigned char * ptr = getPixel(x1, y);
        for ( int x = x1; x < x2; ++ x ) {
            *(ptr ++) = cB;
            *(ptr ++) = cG;
            *(ptr ++) = cR;
        }
    }

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
SAMPLE_NAMESPACE_END

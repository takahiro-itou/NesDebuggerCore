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
**      An Implementation of BitmapRenderer class.
**
**      @file       Images/BitmapRenderer.cpp
**/

#include    "WinAPI/Images/BitmapRenderer.h"


NESDBG_NAMESPACE_BEGIN
namespace  Images  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    BitmapRenderer  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

BitmapRenderer::BitmapRenderer()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BitmapRenderer::~BitmapRenderer()
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

int
BitmapRenderer::createImage(
        const  HDC  hDC,
        const  int  nWidth,
        const  int  nHeight)
{
    constexpr   int  BIT_DEPTH  = 24;

    this->m_iW  = nWidth;
    this->m_iH  = nHeight;
    this->m_iD  = BIT_DEPTH;

    this->m_bytesPerLine    = computeBytesPerLine(nWidth, BIT_DEPTH);
    this->m_bytesPerPixel   = computeBytesPerPixel(BIT_DEPTH);

    this->m_bInfoHeader.biSize          = sizeof(BITMAPINFOHEADER);
    this->m_bInfoHeader.biWidth         = nWidth;
    this->m_bInfoHeader.biHeight        = nHeight;
    this->m_bInfoHeader.biBitCount      = BIT_DEPTH;
    this->m_bInfoHeader.biPlanes        = 1;
    this->m_bInfoHeader.biXPelsPerMeter = 0;
    this->m_bInfoHeader.biYPelsPerMeter = 0;
    this->m_bInfoHeader.biClrUsed       = 0;
    this->m_bInfoHeader.biClrImportant  = 0;
    this->m_bInfoHeader.biCompression   = BI_RGB;
    this->m_bInfoHeader.biSizeImage     = this->m_bytesPerLine * nHeight;

    this->m_Info    = (BITMAPINFO *)(&(this->m_bInfoHeader));
    this->m_hBitmap = CreateDIBSection(
                            hDC, this->m_Info, DIB_RGB_COLORS,
                            (&m_lpBits), NULL, 0);

    return ( this->m_hBitmap != 0 );
}

//----------------------------------------------------------------
//    イメージをデバイスに表示する。
//

int
BitmapRenderer::drawImage(
        const  HDC  hDC,
        const  int  dx,
        const  int  dy,
        const  int  w,
        const  int  h,
        const  int  sx,
        const  int  sy)
{
    HDC     hMemDC  = ::CreateCompatibleDC(hDC);
    HGDIOBJ hOldBmp = ::SelectObject(hMemDC, this->m_hBitmap);

    ::BitBlt(hDC, dx, dy, w, h, hMemDC, sx, sy, SRCCOPY);
    ::GdiFlush();

    ::SelectObject(hMemDC, hOldBmp);
    ::DeleteDC(hMemDC);

    return ( 0 );
}

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

}   //  End of namespace  Images
NESDBG_NAMESPACE_END

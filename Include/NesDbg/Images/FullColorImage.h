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
**      An Interface of FullColorImage class.
**
**      @file       Images/FullColorImage.h
**/

#if !defined( NESDBG_IMAGES_INCLUDED_FULL_COLOR_IMAGE_H )
#    define   NESDBG_IMAGES_INCLUDED_FULL_COLOR_IMAGE_H

#if !defined( NESDBG_PCH_INCLUDED_PRE_COMPILE_H )
#    include    "NesDbg/pch/PreCompile.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  Images  {

//========================================================================
//
//    FullColorImage  class.
//

class  FullColorImage
{

//========================================================================
//
//    Internal Type Definitions.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    FullColorImage();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~FullColorImage();

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
public:

    //----------------------------------------------------------------
    /**   イメージを作成する。
    **
    **  @param [in] nWidth    イメージの幅
    **  @param [in] nHeight   イメージの高さ
    **  @param [in] cbPixel   ピクセル当たりのバイト数。
    **  @param [in] lStride   行当たりのバイト数。
    **  @param [in] lpBits    イメージデータ。
    **/
    virtual  void
    createImage(
            const  int  nWidth,
            const  int  nHeight,
            const  int  cbPixel,
            const  int  lStride,
            void  *     lpBits);

    //----------------------------------------------------------------
    /**   サンプル画像を描画する。
    **
    **/
    virtual  void
    drawSample();

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   矩形を描画する。
    **
    **/
    void
    fillRectangle(
            const  int  x1,
            const  int  y1,
            const  int  x2,
            const  int  y2,
            const  int  color);

//========================================================================
//
//    Accessors.
//
public:

    inline  const   unsigned  long
    getOffset(
            const  int  x,
            const  int  y)  const
    {
        return ( (this->m_iHeight - y - 1) * (this->m_lStride)
                 + ((this->m_cbPixel) * x)
        );
    }

    inline  const   unsigned char  *
    getImage()  const
    {
        return ( this->m_lpBits );
    }

    inline  unsigned char *
    getImage()
    {
        return ( this->m_lpBits );
    }

    inline  const   unsigned char *
    getPixel(
            const  int  x,
            const  int  y)  const
    {
        return ( this->m_lpBits + getOffset(x, y) );
    }

    inline  unsigned char *
    getPixel(
            const  int  x,
            const  int  y)
    {
        return ( this->m_lpBits + getOffset(x, y) );
    }

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    int     m_iWidth;
    int     m_iHeight;
    int     m_cbPixel;
    int     m_lStride;

    unsigned char *     m_lpBits;

//========================================================================
//
//    Other Features.
//
private:
    typedef     FullColorImage      This;
    FullColorImage      (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   FullColorImageTest;
};

}   //  End of namespace  Images
NESDBG_NAMESPACE_END

#endif

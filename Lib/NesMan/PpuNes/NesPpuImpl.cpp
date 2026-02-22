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
    if ( this->m_pImage == nullptr ) {
        return ( ErrCode::FAILURE );
    }

    //  パレットを適当に設定する。  //
    for ( int i = 0; i < 32; i += 4 ){
        this->m_palette[i + 0]  = 0x00000000;
        this->m_palette[i + 1]  = 0x00FFFFFF;
        this->m_palette[i + 2]  = 0x000000FF;
        this->m_palette[i + 3]  = 0x0000FF00;
    }

    BtByte  buf[64];

    for ( int my = 0; my < 16; ++ my ) {
        for ( int mx = 0; mx < 16; ++ mx ) {
            //  パターンを読み出す。    //
            for ( int cy = 0; cy < 8; ++ cy ) {
                for ( int cx = 0; cx < 8; ++ cx ) {
                    buf[cy * 8 + cx]    = 0;
                }
            }
            LpcByteReadBuf  ptr = this->m_memPPU + (my * 16 + mx) * 16;
            for ( int cy = 0; cy < 8; ++ cy ) {
                BtByte  tmp = *(ptr ++);
                for ( int cx = 0; cx < 8; ++ cx ) {
                    if ( tmp & 0x80 ) {
                        buf[cy * 8 + cx] |= 1;
                    }
                    tmp <<= 1;
                }
            }
            for ( int cy = 0; cy < 8; ++ cy ) {
                BtByte  tmp = *(ptr ++);
                for ( int cx = 0; cx < 8; ++ cx ) {
                    if ( tmp & 0x80 ) {
                        buf[cy * 8 + cx] |= 2;
                    }
                    tmp <<= 1;
                }
            }
            //  これにパレットの色を付けて転送する。    //
            for ( int cy = 0; cy < 8; ++ cy ) {
                for ( int cx = 0; cx < 8; ++ cx ) {
                    const  int  col = this->m_palette[buf[cy * 8 + cx]];
                    this->m_pImage->fillRectangle(
                            mx * 8 + cx, my * 8 + cy,
                            mx * 8 + cx + 1, my * 8 + cy + 1,
                            col);
                }
            }
        }
    }

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

//----------------------------------------------------------------
//    属性テーブルを更新する。
//

ErrCode
NesPpuImpl::updateAttributeTable()
{
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    ネームテーブルを更新する。
//

ErrCode
NesPpuImpl::updateNameTable()
{
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

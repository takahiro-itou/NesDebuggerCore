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
    {
        this->m_palette[0]  = 0x00000000;
        this->m_palette[1]  = 0x00FFFFFF;
        this->m_palette[2]  = 0x000000FF;
        this->m_palette[3]  = 0x0000FF00;

        this->m_palette[4]  = 0x00000000;
        this->m_palette[5]  = 0x00FF0000;
        this->m_palette[6]  = 0x0000FFFF;
        this->m_palette[7]  = 0x00FFFFFF;

        this->m_palette[8]  = 0x00000000;
        this->m_palette[9]  = 0x00FF0000;
        this->m_palette[10] = 0x0000FF00;
        this->m_palette[11] = 0x000000FF;

        this->m_palette[12] = 0x00000000;
        this->m_palette[13] = 0x0000FFFF;
        this->m_palette[14] = 0x00FF00FF;
        this->m_palette[15] = 0x00FFFF00;
    }

    initializeAttributeTable();
    updateNameTable();
    // updateAttributeTable(0);
    // updateAttributeTable(1);
    // updateAttributeTable(2);
    // updateAttributeTable(3);
    drawBackGroud();

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
//    背景画面を描画する。
//

ErrCode
NesPpuImpl::drawBackGroud()
{

    BtByte  buf[64];

    LpcByteReadBuf  ptrTile = this->m_memPPU + 0x2000;

    for ( int ny = 0; ny < 30; ++ ny ) {
        for ( int nx = 0; nx < 32; ++ nx ) {
            //  パターン番号を読み出す。    //
            const   BtByte  tid = *(ptrTile ++);

            //  パターンを読み出す。    //
            LpcByteReadBuf  ptrPats = this->m_memPPU + (tid * 16);
            for ( int cy = 0; cy < 8; ++ cy ) {
                BtByte  tmp = *(ptrPats ++);
                for ( int cx = 0; cx < 8; ++ cx ) {
                    if ( tmp & 0x80 ) {
                        buf[cy * 8 + cx] = 1;
                    } else {
                        buf[cy * 8 + cx] = 0;
                    }
                    tmp <<= 1;
                }
            }
            for ( int cy = 0; cy < 8; ++ cy ) {
                BtByte  tmp = *(ptrPats ++);
                for ( int cx = 0; cx < 8; ++ cx ) {
                    if ( tmp & 0x80 ) {
                        buf[cy * 8 + cx] |= 2;
                    }
                    tmp <<= 1;
                }
            }

            //  これにパレットの色を付けて転送する。    //
            const  int  pid = (this->m_palIdx[ny][nx]) & 3;
            for ( int cy = 0; cy < 8; ++ cy ) {
                for ( int cx = 0; cx < 8; ++ cx ) {
                    const  int  col = this->m_palette[
                            pid * 4 + buf[cy * 8 + cx]
                    ];
                    this->m_pImage->setPixelColor(
                            nx * 8 + cx, ny * 8 + cy,
                            col);
                }
            }
        }
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    スプライトを描画する。
//

ErrCode
NesPpuImpl::drawSprite()
{
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    属性テーブルを初期化する。
//

ErrCode
NesPpuImpl::initializeAttributeTable()
{
    //  テスト用ダミーコード。  //
    for ( int ny = 0; ny < 64; ++ ny ) {
        for ( int nx = 0; nx < 64; ++ nx ) {
            this->m_palIdx[ny][nx]  = 0;
        }
    }

    for ( int i = 0; i < 64; ++ i ) {
        writeAttribute(0, i, i);
        writeAttribute(1, i, i);
        writeAttribute(2, i, i);
        writeAttribute(3, i, i);
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    属性テーブルを更新する。
//

ErrCode
NesPpuImpl::updateAttributeTable(
        const  int  scr)
{
    LpcByteReadBuf  ptrAtrb = this->m_memPPU + (scr * 0x0400) + 0x23C0;

    for ( int i = 0; i < 64; ++ i ){
        writeAttribute(scr, i, *(ptrAtrb ++) );
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    ネームテーブルを更新する。
//

ErrCode
NesPpuImpl::updateNameTable()
{
    for ( int ny = 0; ny < 16; ++ ny ) {
        LpByteWriteBuf  ptr = this->m_memPPU + 0x2000 + (ny * 32);
        for ( int nx = 0; nx < 16; ++ nx ) {
            *(ptr ++)   = (ny * 16 + nx);
        }
    }
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    属性テーブルに値を書き込む。
//

ErrCode
NesPpuImpl::writeAttribute(
        const   int     scr,
        const   int     idx,
        const   BtByte  val)
{
    //  インデックスは 00..63 の値をとる。  //
    //  8 で割った剰余で横方向。            //
    //  8 で割った商  で縦方向の番号。      //
    int  nx  = ((idx     ) & 7);
    int  ny  = ((idx >> 3) & 7);

    //  これに画面番号 *8 を加算する。      //
    nx  |= ((scr & 1) << 3);
    ny  |= ((scr >> 1) & 1) << 3;

    //  １バイトで 4*4 マス分を指定する。   //
    nx  *= 4;
    ny  *= 4;

    //  テーブルに書き込む。    //
    BtByte  wrt = (val & 3);
    this->m_palIdx[ny+0][nx+0]  = wrt;
    this->m_palIdx[ny+0][nx+1]  = wrt;
    this->m_palIdx[ny+1][nx+0]  = wrt;
    this->m_palIdx[ny+1][nx+1]  = wrt;

    wrt = (val >> 2) & 3;
    this->m_palIdx[ny+0][nx+2]  = wrt;
    this->m_palIdx[ny+0][nx+3]  = wrt;
    this->m_palIdx[ny+1][nx+2]  = wrt;
    this->m_palIdx[ny+1][nx+3]  = wrt;

    wrt = (val >> 4) & 3;
    this->m_palIdx[ny+2][nx+0]  = wrt;
    this->m_palIdx[ny+2][nx+1]  = wrt;
    this->m_palIdx[ny+3][nx+0]  = wrt;
    this->m_palIdx[ny+3][nx+1]  = wrt;

    wrt = (val >> 6) & 3;
    this->m_palIdx[ny+2][nx+2]  = wrt;
    this->m_palIdx[ny+2][nx+3]  = wrt;
    this->m_palIdx[ny+2][nx+2]  = wrt;
    this->m_palIdx[ny+2][nx+3]  = wrt;

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

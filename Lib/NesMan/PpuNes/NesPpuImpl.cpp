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

#include    <cassert>
#include    <iostream>


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
    : Super(manNes, manMem),
      m_palette(),
      m_palIdx (),
      m_regStat(0),
      m_regAddr(0),
      m_regScroll({0, 0}),
      m_regWrt (0)
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

//----------------------------------------------------------------
//    レジスタの内容を覗く。
//

BtByte
NesPpuImpl::peekRegister(
        const   GuestMemoryAddress  ioAddr)  const
{
#if defined( _DEBUG )
    if ( (ioAddr < 0x2000) || (0x3FFF < ioAddr) ) {
        //  範囲外のアドレス。  //
        std::cerr   <<  "Invalid I/O Address for PPU: "
                    <<  ioAddr  <<  std::endl;
    }
#endif
    assert( (0x2000 <= ioAddr) && (ioAddr <= 0x3FFF) );

    const   GuestMemoryAddress  reg = (ioAddr & 0x0007);
    switch ( reg ) {
    case  0:    /*  PPU 制御レジスタ 1 .    */
        return ( this->m_regCtl0 );
    case  1:    /*  PPU 制御レジスタ 2 .    */
        return ( this->m_regCtl1 );
    case  2:    /*  PPU ステータスレジスタ  */
        return ( this->m_regStat );
    case  3:    /*  スプライトアドレスレジスタ  */
        return ( this->m_sprAddr );
        break;
    case  4:    /*  スプライトアクセスレジスタ  */
        break;
    case  5:    /*  スクロールレジスタ      */
        break;
    case  6:    /*  VRAM  アドレスレジスタ  */
        break;
    case  7:    /*  VRAM  アクセスレジスタ  */
        return ( this->m_memPPU[this->m_regAddr] );
    }

    return ( 0 );
}

//----------------------------------------------------------------
//    レジスタを読み出す。
//

BtByte
NesPpuImpl::readRegister(
        const   GuestMemoryAddress  ioAddr)
{
    const   BtByte  val = peekRegister(ioAddr);

    const   GuestMemoryAddress  reg = (ioAddr & 0x0007);
    switch ( reg ) {
    case  0:    /*  PPU 制御レジスタ 1 .    */
        return ( val );
        break;      //  WRITE ONLY
    case  1:    /*  PPU 制御レジスタ 2 .    */
        return ( val );
        break;      //  WRITE ONLY
    case  2:    /*  PPU ステータスレジスタ  */
        this->m_regStat &= 0x7F;
        this->m_regWrt  =  0;
        return ( val );
    case  3:    /*  スプライトアドレスレジスタ  */
        return ( val );
        break;      //  WRITE ONLY
    case  4:    /*  スプライトアクセスレジスタ  */
        break;
    case  5:    /*  スクロールレジスタ      */
        break;      //  WRITE ONLY
    case  6:    /*  VRAM  アドレスレジスタ  */
        break;      //  WRITE ONLY
    case  7:    /*  VRAM  アクセスレジスタ  */
        this->m_regAddr = (this->m_regAddr + 1) & 0x00003FFF;
        return ( val );
    }

#if defined( _DEBUG )
    {
        char    buf[1024];
        snprintf(buf, sizeof(buf),
                "Not Implemented PPU I/O (Read) : $%04X\n", ioAddr);
        std::cerr   <<  buf;
    }
#endif

    return ( val );
}

//----------------------------------------------------------------
//    レジスタに書き込む。
//

void
NesPpuImpl::writeRegister(
        const   GuestMemoryAddress  ioAddr,
        const   BtByte              regVal)
{
    char    buf[1024];

#if defined( _DEBUG )
    if ( (ioAddr < 0x2000) || (0x3FFF < ioAddr) ) {
        //  範囲外のアドレス。  //
        std::cerr   <<  "Invalid I/O Address for PPU: "
                    <<  ioAddr  <<  std::endl;
    }
#endif
    assert( (0x2000 <= ioAddr) && (ioAddr <= 0x3FFF) );

    const   GuestMemoryAddress  reg = (ioAddr & 0x0007);
    switch ( reg ) {
    case  0:    /*  PPU 制御レジスタ 1 .    */
        this->m_regCtl0 = regVal;
        break;
    case  1:    /*  PPU 制御レジスタ 2 .    */
        this->m_regCtl1 = regVal;
        break;
    case  2:    /*  PPU ステータスレジスタ  */
        this->m_regStat |= (regVal & 0x1F);
        break;
    case  3:    /*  スプライトアドレスレジスタ  */
        this->m_sprAddr = regVal;
        break;
    case  4:    /*  スプライトアクセスレジスタ  */
        break;
    case  5:    /*  スクロールレジスタ      */
        break;
    case  6:    /*  VRAM  アドレスレジスタ  */
        if ( this->m_regWrt == 0 ) {
            //  PPU のメモリ空間は 14 ビット。  //
            this->m_regAddr = (regVal << 8) & 0x00003F00;
            this->m_regWrt  = 1;
        } else {
            this->m_regAddr |= (regVal & 0x000000FF);
            this->m_regWrt  = 0;
        }
        return;
    case  7:    /*  VRAM  アクセスレジスタ  */
#if defined( _DEBUG )
        snprintf(buf, sizeof(buf),
                "Write PPU Memory %04x < %02x\n", this->m_regAddr, regVal);
        std::cerr   <<  buf;
#endif
        if ( this->m_regAddr <= 0x2000 ) {
#if defined( _DEBUG )
            snprintf(buf, sizeof(buf),
                    "WARNING : Write to ROM : %04x < %02x\n",
                    this->m_regAddr, regVal);
            std::cerr   <<  buf;
#endif
            return;
        }
        this->m_memPPU[this->m_regAddr] = regVal;
        this->m_regAddr = (this->m_regAddr + 1) & 0x00003FFF;
        return;
    }

#if defined( _DEBUG )
    {
        snprintf(buf, sizeof(buf),
                "Not Implemented PPU I/O (Write) : $%04X\n", ioAddr);
        std::cerr   <<  buf;
    }
#endif

    return;
}

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
    updateAttributeTable(0);
    updateAttributeTable(1);
    updateAttributeTable(2);
    updateAttributeTable(3);
    drawBackGroud();

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    スキャンライン情報を更新する。
//

PpuScanLine
NesPpuImpl::updateScanLine(
        const  int  nCycles)
{
    PpuScanLine retVal  = PpuScanLine::VISIBLE_SCANLINE;

    //  PPU カウンタを更新する。                //
    //  CPU の３倍のクロックが入力されている。  //
    this->m_curScanPt.x += nCycles;
    this->m_totalCycles += nCycles;
    this->m_frameCycels += nCycles;

    while ( this->m_curScanPt.x >= this->m_curEndCycle ) {
        this->m_curScanPt.x -= this->m_curEndCycle;

        if ( ++ this->m_curScanPt.y == 240 ) {
            //  ここをフレームの区切りとする。  //
            this->m_totalCycles -= 262 * 341;
            ++ this->m_frameNumber;
        }

        if ( this->m_curScanPt.y == 261 ) {
            if ( this->m_flgOddFrame && (this->m_regCtl1 & 0x18) ) {
                //  ここだけ１サイクル少ない。  //
                this->m_curEndCycle = 340;
            } else {
                this->m_curEndCycle = 341;
            }
            this->m_flgOddFrame ^= 1;
        } else {
            this->m_curEndCycle = 341;
        }
    }

    if ( this->m_curScanPt.y == 241 ) {
        if ( this->m_curScanPt.x >= 1 && this->m_curScanPt.x - nCycles < 1 ) {
            //  Start V-BLANK.                  //
            //  ここで VBLANK フラグを立てる。  //
            if ( this->m_ppuDead <= 1 ) {
                this->m_regStat |= 0x80;
            }
        }
        if ( !this->m_flgVbl && this->m_curScanPt.x >= 20
                && this->m_curScanPt.x - nCycles < 20
        ) {
            //  ここで割り込みを発生。  //
            if ( this->m_ppuDead > 0 ) {
                -- this->m_ppuDead;
                retVal  = ( PpuScanLine::VERTICAL_BLANKING_LINE );
            } else {
                retVal  = ( PpuScanLine::START_VERTICAL_BLANK );
            }
            this->m_flgVbl  = BOOL_TRUE;
        }
    }

    if ( this->m_curScanPt.y >= 261 ) {
        //  pre-render scanline.            //
        //  ここで VBLANK フラグを下ろす。  //
        this->m_regStat &= ~0x80;
        this->m_flgVbl  =  BOOL_FALSE;
        this->m_curScanPt.y -= 262;

        retVal  = ( PpuScanLine::PRE_RENDER_SCANLINE );
    }

#if defined( _DEBUG )
    char    buf[532];
    snprintf(buf, sizeof(buf), ", sta=%02X", this->m_regStat);
    std::cout   <<  "PPU : S "  <<  this->m_curScanPt.y
                <<  ", D "      <<  this->m_curScanPt.x
                <<  " / "       <<  this->m_curEndCycle
                <<  ", F "      <<  this->m_frameNumber
                <<  ", "        <<  this->m_frameCycels
                <<  " / "       <<  this->m_totalCycles
                <<  buf
                <<  ", PD="     <<  this->m_ppuDead
                <<  std::endl;
#endif

    if ( retVal != PpuScanLine::VISIBLE_SCANLINE ) {
        return ( retVal );
    }

    if ( this->m_curScanPt.y < 0 ) {
        return ( PpuScanLine::PRE_RENDER_SCANLINE );
    }
    if ( this->m_curScanPt.y >= 241 && this->m_curScanPt.y <= 260 ) {
        return ( PpuScanLine::VERTICAL_BLANKING_LINE );
    }
    if ( this->m_curScanPt.y >= 240 ) {
        return ( PpuScanLine::POST_RENDER_SCANLINE );
    }

    return ( PpuScanLine::VISIBLE_SCANLINE );
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
        this->m_memPPU[0 * 0x0400 + 0x23C0 + i] = i;
        this->m_memPPU[1 * 0x0400 + 0x23C0 + i] = i;
        this->m_memPPU[2 * 0x0400 + 0x23C0 + i] = i;
        this->m_memPPU[3 * 0x0400 + 0x23C0 + i] = i;

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

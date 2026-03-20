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
**      An Interface of NesPpuImpl class.
**
**      @file       NesMan/PpuNes/NesPpuImpl.h
**/

#if !defined( NESDBG_NESMAN_PPUNES_INCLUDED_NES_PPU_IMPL_H )
#    define   NESDBG_NESMAN_PPUNES_INCLUDED_NES_PPU_IMPL_H

#if !defined( NESDBG_NESMAN_INCLUDED_BASE_PPU_CORE_H )
#    include    "NesDbg/NesMan/BasePpuCore.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//========================================================================
//
//    NesPpuImpl  class.
//

class  NesPpuImpl : public BasePpuCore
{

//========================================================================
//
//    Internal Type Definitions.
//
private:

    /**   基底クラス。  **/
    typedef     BasePpuCore             Super;

    /**   アドレス型。  **/
    typedef     GuestMemoryAddress      PpuAddress;


//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （コンストラクタ）。
    **
    **/
    NesPpuImpl(
            NesManager    & manNes,
            MemoryManager & manMem);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~NesPpuImpl();

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//
public:

    //----------------------------------------------------------------
    /**   レジスタの内容を覗く。
    **
    **  @param [in] ioAddr    I/O アドレス。
    **  @return     読み出したバイトを返す。
    **/
    virtual  BtByte
    peekRegister(
            const   GuestMemoryAddress  ioAddr)  const  override;

    //----------------------------------------------------------------
    /**   レジスタを読み出す。
    **
    **  @param [in] ioAddr    I/O アドレス。
    **  @return     読み出したバイトを返す。
    **/
    virtual  BtByte
    readRegister(
            const   GuestMemoryAddress  ioAddr)  override;

    //----------------------------------------------------------------
    /**   レジスタに書き込む。
    **
    **  @param [in] ioAddr    I/O アドレス。
    **  @param [in] regVal    書き込む値。
    **  @return     void.
    **/
    virtual  void
    writeRegister(
            const   GuestMemoryAddress  ioAddr,
            const   BtByte              regVal)  override;


//========================================================================
//
//    Public Member Functions (Overrides).
//
public:

    //----------------------------------------------------------------
    /**   画面を描画する。
    **
    **/
    virtual  ErrCode
    drawScreen()  override;

    //----------------------------------------------------------------
    /**   電源オンの処理を行う。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    emulatePowerOn()  override;

    //----------------------------------------------------------------
    /**   スキャンライン情報を更新する。
    **
    **  @param [in] nCycles   PPU サイクル数。
    **  @return     スキャンラインに関する情報を返す。
    **/
    virtual  PpuScanLine
    updateScanLine(
            const  int  nCycles)  override;

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
    /**   背景画面を描画する。
    **
    **/
    virtual  ErrCode
    drawBackGroud();

    //----------------------------------------------------------------
    /**   スプライトを描画する。
    **
    **/
    virtual  ErrCode
    drawSprite();

    //----------------------------------------------------------------
    /**   ネームテーブルをダンプする。
    **
    **/
    virtual  std::ostream  &
    dumpNameTable(
            const   int     index,
            std::ostream  & outStr)  const;

    //----------------------------------------------------------------
    /**   属性テーブルを初期化する。
    **
    **/
    virtual  ErrCode
    initializeAttributeTable();

    //----------------------------------------------------------------
    /**   属性テーブルを更新する。
    **
    **/
    virtual  ErrCode
    updateAttributeTable(
            const  int  scr);

    //----------------------------------------------------------------
    /**   ネームテーブルを更新する。
    **
    **/
    virtual  ErrCode
    updateNameTable();

    //----------------------------------------------------------------
    /**   属性テーブルに値を書き込む。
    **
    **/
    virtual  ErrCode
    writeAttribute(
            const   int     scr,
            const   int     idx,
            const   BtByte  val);

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

//========================================================================
//
//    Member Variables.
//
private:

    /**   カラーパレット。  **/
    int         m_palette[32];

    /**   パレット番号。    **/
    BtByte      m_palIdx[64][64];

    /**   制御レジスタ。    **/
    BtByte      m_regCtl0;

    BtByte      m_regCtl1;

    /**   ステータスレジスタ。  **/
    BtByte      m_regStat;
    BtByte      m_sprAddr;

    /**   内部レジスタ。    **/
    PpuAddress  m_regAddr;

    /**   スクロールレジスタ。  **/
    NtPoint     m_regScroll;

    /**   内部フラグレジスタ。  **/
    int         m_regWrt;

//========================================================================
//
//    Other Features.
//
private:
    typedef     NesPpuImpl      This;
    NesPpuImpl          (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   NesPpuImplTest;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

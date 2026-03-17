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
**      An Interface of BasePpuCore class.
**
**      @file       NesMan/BasePpuCore.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_BASE_PPU_CORE_H )
#    define   NESDBG_NESMAN_INCLUDED_BASE_PPU_CORE_H

#if !defined( NESDBG_NESMAN_INCLUDED_MEMORY_MAPPED_IO_H )
#    include    "MemoryMappedIO.h"
#endif

#if !defined( NESDBG_NESMAN_INCLUDED_CPU_UTILS_H )
#    include    "CpuUtils.h"
#endif

#if !defined( NESDBG_SYS_STL_INCLUDED_VECTOR )
#    include    <vector>
#    define   NESDBG_SYS_STL_INCLUDED_VECTOR
#endif


NESDBG_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Images  {
class   FullColorImage;
}   //  End of namespace  Images

namespace  NesMan  {

//  クラスの前方宣言。  //
class   NesManager;
class   MemoryManager;


//========================================================================
//
//    BasePpuCore  class.
//

class  BasePpuCore : public IMemoryMappedIO
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
    **  （コンストラクタ）。
    **
    **/
    BasePpuCore(
            NesManager    & manNes,
            MemoryManager & manMem);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BasePpuCore();

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
    /**   画面を描画する。
    **
    **/
    virtual  ErrCode
    drawScreen();

    //----------------------------------------------------------------
    /**   電源オンの処理を行う。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    emulatePowerOn();

    //----------------------------------------------------------------
    /**   リセットボタン押下の処理を行う。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    emulateResetButton();

    //----------------------------------------------------------------
    /**   ROM ファイルをロードした後の処理を行う。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    postprocessOpenRom();

    //----------------------------------------------------------------
    /**   スキャンライン情報を更新する。
    **
    **  @param [in] nCycles   PPU サイクル数。
    **  @return     スキャンラインに関する情報を返す。
    **/
    virtual  PpuScanLine
    updateScanLine(
            const  int  nCycles);

    //----------------------------------------------------------------
    /**   スキャンライン情報を更新する。
    **
    **  @param [in] ctrStep   CPU 側のカウンタ情報。
    **  @return     スキャンラインに関する情報を返す。
    **/
    virtual  PpuScanLine
    updateScanLine(
            const  CounterInfo  &ctrStep);


//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   PPU インスタンスを生成する。
    **
    **  @param [in] manNes
    **  @param [in] manMem
    **  @return     生成したインスタンスを返す。
    **/
    static  BasePpuCore  *
    createInstance(
            NesManager    & manNes,
            MemoryManager & manMem);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在のスキャン位置を取得する。
    **
    **/
    const   NtPoint
    getCurrentScanPoint()  const;

    //----------------------------------------------------------------
    /**   描画先のイメージを取得する。
    **
    **/
    Images::FullColorImage  *
    getScreenImage()  const;

    //----------------------------------------------------------------
    /**   描画先のイメージを設定する。
    **
    **  @param [in] ptrImg    イメージオブジェクト。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setScreenImage(
            Images::FullColorImage * const  ptrImg);

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
protected:

    /**   イメージオブジェクト。    **/
    Images::FullColorImage  *   m_pImage;

    /**   PPU メモリ空間。          **/
    BtByte                      m_memPPU[16384];

    /**  メモリマネージャ。     **/
    MemoryManager  &            m_manMem;

    /**   PPU の初期化期間。        **/
    int             m_ppuDead;

    /**   既に VBLANK 割り込みを発生させたか？  **/
    Boolean         m_flgVbl;

    /**   現在のフレーム番号。  **/
    ClockCount      m_frameNumber;

    /**   現在のフレームのサイクル数。  **/
    ClockCount      m_frameCycels;

    /**   現在の総サイクル数。  **/
    ClockCount      m_totalCycles;

    /**   現在のスキャン位置。  **/
    NtPoint         m_curScanPt;

//========================================================================
//
//    Other Features.
//
private:
    typedef     BasePpuCore     This;
    BasePpuCore         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   BasePpuCoreTest;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

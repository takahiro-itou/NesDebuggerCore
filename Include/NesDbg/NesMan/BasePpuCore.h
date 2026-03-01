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

class  BasePpuCore
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
    /**   プロセッサをリセットする。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    doHardReset();

    //----------------------------------------------------------------
    /**   画面を描画する。
    **
    **/
    virtual  ErrCode
    drawScreen();

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
    /**   カウンタ情報を更新する。
    **
    **  @param [in] ctrStep   CPU 側のカウンタ情報。
    **  @return     スキャンラインに関する情報を返す。
    **/
    virtual  PpuScanLine
    updateCounters(
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
    std::vector<BtByte>         m_vMemBuf;

    LpByteWriteBuf              m_memPPU;

    /**  メモリマネージャ。     **/
    MemoryManager  &            m_manMem;

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

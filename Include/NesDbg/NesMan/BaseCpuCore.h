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
**      An Interface of BaseCpuCore class.
**
**      @file       NesMan/BaseCpuCore.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_BASE_CPU_CORE_H )
#    define   NESDBG_NESMAN_INCLUDED_BASE_CPU_CORE_H

#if !defined( NESDBG_NESMAN_INCLUDED_CPU_UTILS_H )
#    include    "CpuUtils.h"
#endif

#if !defined( NESDBG_SYS_STL_INCLUDED_IOSFWD )
#    include    <iosfwd>
#    define   NESDBG_SYS_STL_INCLUDED_IOSFWD
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//  クラスの前方宣言。  //
class   NesManager;
class   MemoryManager;


#if defined( NESDBG_USE_GLOBALS )

extern  RegBank             mog_cpuRegs;

extern  CounterInfo         mog_cpuInfo;

#endif


//========================================================================
//
//    BaseCpuCore  class.
//

class  BaseCpuCore
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
    BaseCpuCore(
            NesManager    & manNes,
            MemoryManager & manMem);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BaseCpuCore();

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
public:

    //----------------------------------------------------------------
    /**   BRK 割り込みを実行する。
    **
    **/
    virtual  InstExecResult
    execBrk(const  OpeCode  opeCode)  = 0;

    //----------------------------------------------------------------
    /**   IRQ 割り込みを実行する。
    **
    **/
    virtual  InstExecResult
    execIrq(const  OpeCode  opeCode)  = 0;

    //----------------------------------------------------------------
    /**   NMI 割り込みを実行する。
    **
    **/
    virtual  InstExecResult
    execNmi(const  OpeCode  opeCode)  = 0;

    //----------------------------------------------------------------
    /**   現在の命令を実行する。
    **
    **/
    virtual  InstExecResult
    executeNextInst()  = 0;


//========================================================================
//
//    Public Member Functions (Virtual Functions).
//
public:

    //----------------------------------------------------------------
    /**   レジスタをリセットする。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    doHardReset();

    //----------------------------------------------------------------
    /**   レジスタの内容をコピーする。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    getRegisters(
            RegBank  &copyBuf)  const;

    //----------------------------------------------------------------
    /**   V-BLANK 割り込みを発生させる。
    **
    **/
    virtual  ErrCode
    performVBlankInterupt(
            const  PpuScanLine  ppuScan);

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
    /**   レジスタの内容をダンプする。
    **
    **/
    virtual  std::ostream  &
    printRegisters(
            std::ostream  & outStr)  const;

    //----------------------------------------------------------------
    /**   レジスタの内容を設定する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setRegisters(
            const  RegBank  &cpuRegs);

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   現在のカウンタ情報を更新する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    updateCounters();

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在のカウンタ情報を取得する。
    **
    **/
    const   CounterInfo
    getCpuCounters()  const
    {
        return ( mog_cpuInfo );
    }

    //----------------------------------------------------------------
    /**   プログラムカウンタを取得する。
    **
    **/
    const   GuestMemoryAddress
    getNextPC()  const
    {
        return ( mog_cpuRegs.PC );
    }

    //----------------------------------------------------------------
    /**   ステップ分のカウンタ情報を取得する。
    **
    **/
    const   CounterInfo  &
    getStepCounters()  const
    {
        return ( mog_ctrStep );
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
protected:

    NesManager  &           m_manNes;

#if !defined( NESDBG_USE_GLOBALS )
    /**   レジスタ。        **/
    RegBank                 mog_cpuRegs;

    /**   カウンタ関連。    **/
    CounterInfo             mog_cpuInfo;

    CounterInfo             mog_ctrStep;
#endif

    /**  メモリマネージャ。     **/
    MemoryManager  &        m_manMem;


//========================================================================
//
//    Other Features.
//
private:
    typedef     BaseCpuCore     This;
    BaseCpuCore         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   BaseCpuCoreTest;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

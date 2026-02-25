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
**      An Interface of NesManager class.
**
**      @file       NesMan/NesManager.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_NES_MANAGER_H )
#    define   NESDBG_NESMAN_INCLUDED_NES_MANAGER_H

#if !defined( NESDBG_NESMAN_INCLUDED_CPU_UTILS_H )
#    include    "CpuUtils.h"
#endif

#if !defined( NESDBG_NESMAN_INCLUDED_MEMORY_MANAGER_H )
#    include    "MemoryManager.h"
#endif

#if !defined( NESDBG_SYS_STL_INCLUDED_IOSFWD )
#    include    <iosfwd>
#    define   NESDBG_SYS_STL_INCLUDED_IOSFWD
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//  クラスの前方宣言。  //
class   BaseCpuCore;
class   BaseDisCpu;
class   BasePpuCore;
class   Cpu6502;
class   Dis6502;
class   NesPpuImpl;


//========================================================================
//
//    NesManager  class.
//

class  NesManager
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
    NesManager();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~NesManager();

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
    /**   現在動作しているインスタンスを閉じる。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    closeInstance();

    //----------------------------------------------------------------
    /**   リセットを行う。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    doHardReset();

    //----------------------------------------------------------------
    /**   現在の命令を実行する。
    **
    **/
    virtual  InstExecResult
    executeCurrentInst();

    //----------------------------------------------------------------
    /**   現在のカウンタ情報を取得する。
    **
    **/
    virtual  const  CounterInfo
    getCpuCounters()  const;

    //----------------------------------------------------------------
    /**   プログラムカウンタを取得する。
    **
    **/
    virtual  GuestMemoryAddress
    getNextPC()  const;

    //----------------------------------------------------------------
    /**   CPU インスタンスを取得する。
    **
    **  インスタンスが存在しない場合は新規作成する。
    **/
    virtual  BaseCpuCore  &
    getOrCreateCpuInstance();

    //----------------------------------------------------------------
    /**   PPU インスタンスを取得する。
    **
    **  インスタンスが存在しない場合は新規作成する。
    **/
    virtual  BasePpuCore  &
    getOrCreatePpuInstance();

    //----------------------------------------------------------------
    /**   ROM ファイルを読み込む。
    **
    **  @param [in] szFileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    openRomFile(
            const   char *  szFileName);

    //----------------------------------------------------------------
    /**   レジスタの内容をダンプする。
    **
    **/
    virtual  std::ostream  &
    printRegisters(
            std::ostream  & outStr)  const;

    //----------------------------------------------------------------
    /**   現在のカウンタ情報を更新する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    updateCounters();

    //----------------------------------------------------------------
    /**   ニーモニックを表示する。
    **
    **  @param [in,out] outStr    出力ストリーム
    **  @param [in]     gmAddr    ゲスト上のアドレス
    **  @param    [out] gmNext    次の命令のアドレス
    **/
    virtual  std::ostream  &
    writeMnemonic(
            std::ostream       &outStr,
            GuestMemoryAddress  gmAddr,
            GuestMemoryAddress &gmNext)  const;

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   CPU を管理するインスタンスを取得する。
    **
    **/
    BaseCpuCore  &
    getCurrentCpu()  const
    {
        return ( *(this->m_cpuCur) );
    }

    //----------------------------------------------------------------
    /**   メモリマネージャインスタンスを取得する。
    **
    **/
    MemoryManager  &
    getMemoryManager();

    //----------------------------------------------------------------
    /**   メモリマネージャインスタンスを取得する。
    **
    **/
    const  MemoryManager  &
    getMemoryManager()  const;

    //----------------------------------------------------------------
    /**   CHR ROM のバンク数を取得する。
    **
    **  @return     バンク数を返す。
    **/
    const   size_t
    getNumChrBanks()  const;

    //----------------------------------------------------------------
    /**   PRG ROM のバンク数を取得する。
    **
    **  @return     バンク数を返す。
    **/
    const   size_t
    getNumPrgBanks()  const;

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

    /**   メモリ空間。  **/
    MemoryManager   m_manMem;

    /**   現在の CPU .  **/
    BaseCpuCore  *  m_cpuCur;

    /**   現在の PPU .  **/
    BasePpuCore  *  m_ppuCur;

    Cpu6502  *      m_cpu6502;

    NesPpuImpl  *   m_ppuNes;

    BaseDisCpu  *   m_disCur;

//========================================================================
//
//    Other Features.
//
private:
    typedef     NesManager      This;
    NesManager          (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   NesManagerTest;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

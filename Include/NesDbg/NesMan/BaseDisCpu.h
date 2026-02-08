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
**      An Interface of BaseDisCpu class.
**
**      @file       NesMan/BaseDisCpu.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_BASE_DIS_CPU_H )
#    define   NESDBG_NESMAN_INCLUDED_BASE_DIS_CPU_H

#if !defined( NESDBG_PCH_INCLUDED_PRE_COMPILE_H )
#    include    "NesDbg/pch/PreCompile.h"
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


//========================================================================
//
//    BaseDisCpu  class.
//

class  BaseDisCpu
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
    BaseDisCpu(
            NesManager    & manNes,
            MemoryManager & manMem);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BaseDisCpu();

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
    /**   ニーモニックを表示する。
    **
    **  @param [in,out] outStr    出力ストリーム
    **  @param [in]     gmAddr    ゲスト上のアドレス
    **  @param [in]     opeCode   オペコード
    **/
    virtual  std::ostream  &
    writeMnemonic(
            std::ostream       &outStr,
            GuestMemoryAddress  gmAddr,
            const  OpeCode      opeCode)  const  = 0;

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

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
protected:

    NesManager  &           m_manNes;

    /**  メモリマネージャ。     **/
    MemoryManager  &        m_manMem;


//========================================================================
//
//    Other Features.
//
private:
    typedef     BaseDisCpu      This;
    BaseDisCpu          (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   BaseDisCpuTest;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

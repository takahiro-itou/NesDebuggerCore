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

    typedef     BasePpuCore     Super;


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
    /**   描画先のイメージを指定する。
    **
    **  @param [in] ptrImg    イメージオブジェクト。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setScreenImage(
            Images::FullColorImage * const  ptrImage);

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

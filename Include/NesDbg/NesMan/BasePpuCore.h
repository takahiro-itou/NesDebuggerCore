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
    /**   画面を描画する。
    **
    **/
    virtual  ErrCode
    drawScreen();

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
    /**   イメージオブジェクトを取得する。
    **
    **/
    Images::FullColorImage  *
    getImageInstance()  const;

    //----------------------------------------------------------------
    /**   イメージオブジェクトを設定する。
    **
    **/
    BasePpuCore  &
    setImageInstance(
            Images::FullColorImage  *   pImage);

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

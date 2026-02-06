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

#if !defined( NESDBG_IMAGES_INCLUDED_FULL_COLOR_IMAGE_H )
#    define   NESDBG_IMAGES_INCLUDED_FULL_COLOR_IMAGE_H

#if !defined( NESDBG_PCH_INCLUDED_PRE_COMPILE_H )
#    include    "NesDbg/pch/PreCompile.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

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

}   //  End of namespace  NesMan<
NESDBG_NAMESPACE_END

#endif

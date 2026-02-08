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
**      An Interface of Dis6502 class.
**
**      @file       NesMan/Cpu6502/Dis6502.h
**/

#if !defined( NESDBG_NESMAN_CPU6502_INCLUDED_DIS_6502_H )
#    define   NESDBG_NESMAN_CPU6502_INCLUDED_DIS_6502_H

#if !defined( NESDBG_NESMAN_INCLUDED_BASE_DIS_CPU_H )
#    include    "NesDbg/NesMan/BaseDisCpu.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//========================================================================
//
//    Dis6502  class.
//

class  Dis6502 : public BaseDisCpu
{

//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     BaseDisCpu      Super;


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
    Dis6502();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~Dis6502();

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
    typedef     Dis6502     This;
    Dis6502             (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   Dis6502Test;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

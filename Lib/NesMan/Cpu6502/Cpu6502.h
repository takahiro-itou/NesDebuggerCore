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
**      An Interface of Cpu6502 class.
**
**      @file       NesMan/Cpu6502/Cpu6502.h
**/

#if !defined( NESDBG_NESMAN_CPU6502_INCLUDED_CPU_6502_H )
#    define   NESDBG_NESMAN_CPU6502_INCLUDED_CPU_6502_H

#if !defined( NESDBG_NESMAN_INCLUDED_BASE_CPU_CORE_H )
#    include    "NesDbg/NesMan/BaseCpuCore.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//========================================================================
//
//    Cpu6502  class.
//

class  Cpu6502 : public BaseCpuCore
{

//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     BaseCpuCore     Super;


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
    Cpu6502(
            NesManager    & manNes,
            MemoryManager & manMem);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~Cpu6502();

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
    typedef     Cpu6502     This;
    Cpu6502             (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   Cpu6502Test;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

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
**      An Interface of MemoryMappedIO.
**
**      @file       NesMan/MemoryMappedIO.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_MEMORY_MAPPED_IO_H )
#    define   NESDBG_NESMAN_INCLUDED_MEMORY_MAPPED_IO_H

#if !defined( NESDBG_PCH_INCLUDED_PRE_COMPILE_H )
#    include    "NesDbg/pch/PreCompile.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//========================================================================
//
//    MemoryMappedIO  interface.
//

class  IMemoryMappedIO
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
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~IMemoryMappedIO()
    { }


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
    /**   レジスタを読み出す。
    **
    **  @param [in] ioAddr    I/O アドレス。
    **  @return     読み出したバイトを返す。
    **/
    virtual  BtByte
    readFromRegister(
            const   GuestMemoryAddress  ioAddr)  = 0;

    //----------------------------------------------------------------
    /**   レジスタに書き込む。
    **
    **  @param [in] ioAddr    I/O アドレス。
    **  @param [in] regVal    書き込む値。
    **  @return     void.
    **/
    virtual  void
    writeToRegister(
            const   GuestMemoryAddress  ioAddr,
            const   BtByte              regVal)  = 0;


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
public:
    //  テストクラス。  //
    friend  class   MemoryMappedIOTest;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

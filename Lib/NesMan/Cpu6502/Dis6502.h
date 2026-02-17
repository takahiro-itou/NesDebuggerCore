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
public:

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
            GuestMemoryAddress &gmNext)  const override;

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
private:

    //----------------------------------------------------------------
    /**   絶対番地オペランドを表示する。
    **
    **/
    inline  size_t
    writeAbsolute(
            const  OpeCode  opeCode,
            char  *  const  dst,
            const  size_t   remLen,
            const  char     regName,
            const  RegType  idxReg)  const;

    //----------------------------------------------------------------
    /**   即値オペランドを表示する。
    **
    **/
    inline  size_t
    writeImmediage(
            const  OpeCode  opeCode,
            char  *  const  dst,
            const  size_t   remLen)  const;

    //----------------------------------------------------------------
    /**   絶対番地ジャンプ。
    **
    **/
    inline  size_t
    writeJumpAbsolute(
            const  OpeCode  opeCode,
            char  *  const  dst,
            const  size_t   remLen)  const;

    //----------------------------------------------------------------
    /**   インダイレクトジャンプ。
    **
    **/
    inline  size_t
    writeJumpIndirect(
            const  OpeCode  opeCode,
            char  *  const  dst,
            const  size_t   remLen)  const;

    //----------------------------------------------------------------
    /**   インダイレクトオペランドを表示する。
    **
    **/
    inline  size_t
    writePostIndexIndirect(
            const  OpeCode  opeCode,
            char  *  const  dst,
            const  size_t   remLen,
            const  char     regName,
            const  RegType  idxReg)  const;

    //----------------------------------------------------------------
    /**   インダイレクトオペランドを表示する。
    **
    **/
    inline  size_t
    writePreIndexIndirect(
            const  OpeCode  opeCode,
            char  *  const  dst,
            const  size_t   remLen,
            const  char     regName,
            const  RegType  idxReg)  const;

    //----------------------------------------------------------------
    /**   相対アドレスオペランドを表示する。
    **
    **/
    inline  size_t
    writeRelative(
            const  OpeCode  opeCode,
            char  *  const  dst,
            const  size_t   remLen,
            GuestMemoryAddress  regPC,
            const  RegType  regFlag)  const;

    //----------------------------------------------------------------
    /**   ゼロページオペランドを表示する。
    **
    **/
    inline  size_t
    writeZeroPage(
            const  OpeCode  opeCode,
            char  *  const  dst,
            const  size_t   remLen,
            const  char     regName,
            const  RegType  idxReg)  const;

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


//========================================================================
//
//    For Tests.
//

const   std::string
dumpMnemonicMap(
        const  OpeCode  opeCode);

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

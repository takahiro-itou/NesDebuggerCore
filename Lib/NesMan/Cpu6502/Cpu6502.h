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

#if !defined( NESDBG_COMMON_INCLUDED_NESDBG_UTILS_H )
#    include    "NesDbg/Common/NesDbgUtils.h"
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

    typedef     NESDBG_REGPARM  InstExecResult
    (Cpu6502::* FnInst)(
            const  OpeCode  opeCode);

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
public:

    //----------------------------------------------------------------
    /**   現在の命令を実行する。
    **
    **/
    virtual  InstExecResult
    executeNextInst()  override;

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
    /**   算術論理演算命令。
    **
    **/
    template  <typename OPERAND,
               typename CODE1,
               typename CODE2,
               int RMWW = 0,
               TRegPtr REGPTR = &RegBank::A>
    inline  InstExecResult
    execArithLogic(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   条件分岐命令。
    **
    **/
    template  <RegType MSK, RegType FLG>
    inline  InstExecResult
    execBranch(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   フラグ操作（クリア）命令。
    **
    **/
    template  <RegType  VAL>
    inline  InstExecResult
    execClearFlag(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   インクリメント、デクリメント命令。
    **
    **/
    template  <typename OPERAND, int VAL>
    inline  InstExecResult
    execIncDec(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   インクリメント、デクリメント命令。
    **
    **/
    template  <TRegPtr REG, int VAL>
    inline  InstExecResult
    execIncDecReg(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   ジャンプ命令。
    **
    **/
    inline  InstExecResult
    execJmpAbs(const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   ジャンプ命令。
    **
    **/
    inline  InstExecResult
    execJmpIndirect(const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   ジャンプ命令。
    **
    **/
    inline  InstExecResult
    execJsr(const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   ロード命令。
    **
    **/
    template  <typename AM, TRegPtr REG>
    inline  InstExecResult
    execLoad(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   ポップ命令。
    **
    **/
    template  <TRegPtr TRGREG>
    inline  InstExecResult
    execPull(const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   プッシュ命令。
    **
    **/
    template  <TRegPtr SECREG>
    inline  InstExecResult
    execPush(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   リターン命令。
    **
    **/
    inline  InstExecResult
    execRti(const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   リターン命令。
    **
    **/
    inline  InstExecResult
    execRts(const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   フラグ操作（セット）命令。
    **
    **/
    template  <RegType  VAL>
    inline  InstExecResult
    execSetFlag(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   ロード命令。
    **
    **/
    template  <typename AM, TRegPtr REG>
    inline  InstExecResult
    execStore(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   レジスタ間転送命令。
    **
    **/
    template  <TRegPtr SRCREG, TRegPtr TRGREG>
    inline  InstExecResult
    execTransfer(
            const  OpeCode  opeCode);

    //----------------------------------------------------------------
    /**   スタックからデータを取り出す。
    **
    **/
    inline  const   RegType
    popValue();

    //----------------------------------------------------------------
    /**   スタックにデータを積む。
    **
    **/
    inline  void
    pushValue(
            const  RegType  value);

    //----------------------------------------------------------------
    /**   フラグを設定する。
    **
    **/
    inline  void
    setupNZFlags(
            const  RegType  value);

//========================================================================
//
//    Member Variables.
//
private:

    /**   命令テーブル。    **/
    static  const   FnInst  s_cpuInstTable[256];

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

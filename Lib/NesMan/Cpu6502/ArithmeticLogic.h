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
**      An Implementaion of Arithmetic Logic Operations.
**
**      @file       NesMan/Cpu6502/ArithmeticLogic.h
**/

#if !defined( NESDBG_NESMAN_CPU6502_INCLUDED_ARITHMETIC_LOGIC_H )
#    define   NESDBG_NESMAN_CPU6502_INCLUDED_ARITHMETIC_LOGIC_H


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {
namespace  ALU  {


inline  const   RegType
checkCarrySub(
        const  RegType  lhs,
        const  RegType  rhs,
        const  RegType  res)
{
    const  RegType  cy  = (lhs & ~rhs) | ((lhs | ~rhs) & ~res);
    return ( (cy >> 7) & FLAG_C );
}


//========================================================================
//
//    何もしない命令。
//

struct  OpeNopL
{
    const   RegType
    operator()(
            const  RegType  lhs,
            const  RegType  rhs,
            RegType        &flg)
    {
        return ( lhs );
    }
};

struct  OpeNopR
{
    const   RegType
    operator()(
            const  RegType  lhs,
            const  RegType  rhs,
            RegType        &flg)
    {
        return ( rhs );
    }
};

struct  OpeR2L
{
    const   RegType
    operator()(
            const  RegType  lhs,
            const  RegType  rhs,
            RegType        &flg)
    {
        return ( rhs );
    }
};


//========================================================================
//
//    命令 xxxxxx01 に対応する演算
//

//------------------------------------------------------------------------
//    オペコード 000xxx01 : ORA

//------------------------------------------------------------------------
//    オペコード 001xxx01 : AND

//------------------------------------------------------------------------
//    オペコード 010xxx01 : EOR

//------------------------------------------------------------------------
//    オペコード 011xxx01 : ADC

//------------------------------------------------------------------------
//    オペコード 100xxx01 : STA (別途実装)

//------------------------------------------------------------------------
//    オペコード 101xxx01 : LDA (別途実装)

//------------------------------------------------------------------------
//    オペコード 110xxx01 : CMP

struct  OpeCMP
{
    const   RegType
    operator()(
            const  RegType  lhs,
            const  RegType  rhs,
            RegType        &flg)
    {
        //  SBC 命令はキャリーも加えて計算するが、  //
        //  CMP 命令ははキャリーを使わない。        //
        //  またオーバーフローフラグも弄らない。    //
        const  RegType  res = (lhs - rhs);

        flg &= ~(FLAG_N | FLAG_Z | FLAG_C);
        flg |= (res & FLAG_N);
        flg |= (res ? 0 : FLAG_Z);
        flg |= checkCarrySub(lhs, rhs, res);

        return ( lhs );
    }
};

//------------------------------------------------------------------------
//    オペコード 111xxx01 : SBC


//========================================================================
//
//    オペコード xxxxxx10 に対応する演算
//

//--------------------------------------------------------------
//    オペコード 000xxx10 : ASL

//--------------------------------------------------------------
//    オペコード 001xxx10 : ROL

//--------------------------------------------------------------
//    オペコード 010xxx10 : LSR

//--------------------------------------------------------------
//    オペコード 011xxx10 : ROR

//--------------------------------------------------------------
//    オペコード 100xxx10 : STX (別途実装)

//--------------------------------------------------------------
//    オペコード 101xxx10 : LDX (別途実装)

//--------------------------------------------------------------
//    オペコード 110xxx10 : DEC

//--------------------------------------------------------------
//    オペコード 111xxx10 : INC


}   //  End of namespace  ALU
}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

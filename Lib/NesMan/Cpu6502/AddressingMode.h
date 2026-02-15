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
**      An Implementaion of 6502 Addressing Mode.
**
**      @file       NesMan/Cpu6502/AddressingMode.h
**/

#if !defined( NESDBG_NESMAN_CPU6502_INCLUDED_ADDRESSING_MODE_H )
#    define   NESDBG_NESMAN_CPU6502_INCLUDED_ADDRESSING_MODE_H


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {
namespace  Addres  {

enum  IndexRegister  {
    IDX_REG_N   = 0,
    IDX_REG_X   = 1,
    IDX_REG_Y   = 2,
};


//========================================================================
/**
**    アブソリュートオペランド。
**/

template  <int IDXREG = IDX_REG_N, typename TMemMan = MemoryManager>
struct  Absolute
{
    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        return  getTargetAddress(uOperand, rX, rY, addCyc);
    }

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        const   GuestMemoryAddress  gmAddr
            = getTargetAddress(uOperand, rX, rY, addCyc);
        return  manMem.template readMemory<RegType>(gmAddr);
    }

    GuestMemoryAddress
    getTargetAddress(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            ClockCount      &addCyc)  const
    {
        GuestMemoryAddress  regIdx  = 0;

        switch ( IDXREG ) {
        case  1:        //  $nnnn, X
            regIdx  = rX;
            break;
        case  2:        //  $nnnn, Y
            regIdx  = rY;
            break;
        default:        //  $nnnn
            regIdx  = 0;
            break;
        }

        const   GuestMemoryAddress  gmAddr  = (uOperand + regIdx) & 0xFFFF;
        addCyc  = ( (regIdx) > (uint8_t)(gmAddr) ) ? 1 : 0;
        return ( gmAddr );
    }

};

//========================================================================
/**
**    即値オペランド。
**/

template <int IDXREG = IDX_REG_N, typename TMemMan = MemoryManager>
struct  Immediate
{
    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        return ( uOperand & 0x000000FF );
    }
};


//========================================================================
/**
**    インデックスインダイレクトオペランド。
**/

template  <int IDXREG = IDX_REG_N, typename TMemMan = MemoryManager>
struct  Indirect
{
    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        GuestMemoryAddress  gmAddr;
        addCyc  = 0;

        //  ゼロページ内でのアクセスなので、        //
        //  X を加算した繰り上がりは無視される。    //
        BtByte  tmp = (uOperand & 0x000000FF);
        switch ( IDXREG ) {
        case  IDX_REG_X:
            tmp += rX;
            break;
        case  IDX_REG_Y:    //  このモードは実在しない。
            tmp += rY;
            break;
        }

        //  加算した結果のアドレスが境界にある時、  //
        //  下位アドレスを 0x00FF から読み出し、    //
        //  上位アドレスは 0x0000 から読み出す。    //
        //  上位は 0x0100 ではないことに注意する。  //
        gmAddr  =  manMem.template readMemory<RegType>(tmp);
        ++ tmp;
        gmAddr  |= manMem.template readMemory<RegType>(tmp) << 8;

        return ( gmAddr );
    }

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        GuestMemoryAddress  gmAddr  = getOperandAddress(
                uOperand, rX, rY, rPC, manMem, addCyc);
        return  manMem.template readMemory<RegType>(gmAddr);
    }

};


//========================================================================
/**
**    インダイレクトインデックスオペランド。
**/

template  <
    int IDXREG = IDX_REG_Y, int PCC=1,
    typename TMemMan = MemoryManager>
struct  IdxIndY
{
    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        GuestMemoryAddress  rt, gmAddr;
        addCyc  = 0;

        //  ゼロページ内でのアクセスなので、        //
        //  オペランドが 0xFF の場合、              //
        //  下位アドレスを 0x00FF から読み出し、    //
        //  上位アドレスは 0x0000 から読み出す。    //
        BtByte  tmp = (uOperand & 0x000000FF);
        rt  =  manMem.template readMemory<RegType>(tmp);
        ++ tmp;
        rt  |= manMem.template readMemory<RegType>(tmp) << 8;
        gmAddr  = rt;

        switch ( IDXREG ) {
        case  IDX_REG_Y:
            gmAddr  += rY;
            break;
        case  IDX_REG_X:
            gmAddr  += rX;
            break;
        default:
            break;
        }

        //  Page-Cross Check..  //
        if ( (gmAddr ^ rt) & 0x0100 ) {
            addCyc  = PCC;
            gmAddr  ^= 0x0100;
        }

        //  上で gmAddr のページ境界跨ぎは処理したので  //
        //  gmAddr & 0xFFFF でも良い筈だが念のため。    //
        return ( (rt & 0x0000FF00) | (gmAddr & 0x000000FF) );
    }

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        GuestMemoryAddress  gmAddr  =
                getOperandAddress(uOperand, rX, rY, rPC, manMem, addCyc);
        return  manMem.template readMemory<RegType>(gmAddr);
    }

};


//========================================================================
/**
**    ゼロページオペランド。
**/

template  <int IDXREG = IDX_REG_N, typename TMemMan = MemoryManager>
struct  ZeroPage
{
    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        addCyc  = 0;

        switch ( IDXREG ) {
        case  IDX_REG_X:
            return ( (uOperand + rX) & 0x000000FF );
        case  IDX_REG_Y:
            return ( (uOperand + rY) & 0x000000FF );
        }

        return ( uOperand & 0x000000FF );
    }

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        addCyc  = 0;
        GuestMemoryAddress  gmAddr  =
                getOperandAddress(uOperand, rX, rY, rPC, manMem, addCyc);
        return  manMem.template readMemory<RegType>(gmAddr);
    }

};


}   //  End of namespace  Addres
}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

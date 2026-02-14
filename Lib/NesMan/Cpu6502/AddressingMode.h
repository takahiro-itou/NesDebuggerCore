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

//========================================================================
/**
**    即値オペランド。
**/

struct  Immediate
{
    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            MemoryManager   &manMem,
            ClockCount      &addCyc,
            const  Boolean  flgPeek)  const
    {
        return ( uOperand & 0x000000FF );
    }
};


//========================================================================
/**
**    ゼロページオペランド。
**/

struct  ZeroPage
{
    GuestMemoryAddress
    getTargetAddress(
            const  OpeCode  uOperand)  const
    {
        return ( uOperand & 0x000000FF );
    }

    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            MemoryManager   &manMem,
            ClockCount      &addCyc,
            const  Boolean  flgPeek)  const
    {
        addCyc  = 0;
        return  getTargetAddress(uOperand);
    }

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            MemoryManager   &manMem,
            ClockCount      &addCyc,
            const  Boolean  flgPeek)  const
    {
        addCyc  = 0;
        GuestMemoryAddress  gmAddr  = getTargetAddress(uOperand);
        return  manMem.readMemory<RegType>(gmAddr);
    }

};


//========================================================================
/**
**    アブソリュートオペランド。
**/

template  <int  IDXREG>
struct  Absolute
{
    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            MemoryManager   &manMem,
            ClockCount      &addCyc,
            const  Boolean  flgPeek)  const
    {
        return  getTargetAddress(uOperand, rX, rY, addCyc);
    }

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC,
            MemoryManager   &manMem,
            ClockCount      &addCyc,
            const  Boolean  flgPeek)  const
    {
        const   GuestMemoryAddress  gmAddr
            = getTargetAddress(uOperand, rX, rY, addCyc);
        return  manMem.readMemory<RegType>(gmAddr);
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


}   //  End of namespace  Addres
}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

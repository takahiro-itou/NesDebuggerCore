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
    operator()(
            const  OpeCode  uOperand,
            const  RegType  rX,
            const  RegType  rY,
            const  RegType  rPC
            MemoryManager   &manMem)
    {
        return ( uOperand & 0x000000FF );
    }
};

}   //  End of namespace  Addres
}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

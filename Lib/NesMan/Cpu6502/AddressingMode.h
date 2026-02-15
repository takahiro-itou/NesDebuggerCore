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

template  <TRegPtr IDXREG = &RegBank::Zr, typename TMemMan = MemoryManager>
struct  Absolute
{
    typedef     TMemMan     MemManType;

    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegBank  &cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        return  getTargetAddress(uOperand, (cpuRegs .* IDXREG), addCyc);
    }

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegBank  &cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        const   GuestMemoryAddress  gmAddr
            = getTargetAddress(uOperand, (cpuRegs .* IDXREG), addCyc);
        return  manMem.template readMemory<RegType>(gmAddr);
    }

    GuestMemoryAddress
    getTargetAddress(
            const  OpeCode  uOperand,
            const  RegType  regIdx,
            ClockCount      &addCyc)  const
    {
        const   GuestMemoryAddress  gmAddr  = (uOperand + regIdx) & 0xFFFF;
        addCyc  = ( (regIdx) > (uint8_t)(gmAddr) ) ? 1 : 0;
        return ( gmAddr );
    }

};

//========================================================================
/**
**    即値オペランド。
**/

template  <int IDXREG = IDX_REG_N, typename TMemMan = MemoryManager>
struct  Immediate
{
    typedef     TMemMan     MemManType;

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegBank  &cpuRegs,
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

template  <TRegPtr IDXREG = &RegBank::Zr, typename TMemMan = MemoryManager>
struct  Indirect
{
    typedef     TMemMan     MemManType;

    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegBank  &cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        GuestMemoryAddress  gmAddr;
        addCyc  = 0;

        //  ゼロページ内でのアクセスなので、        //
        //  X を加算した繰り上がりは無視される。    //
        BtByte  tmp = (uOperand & 0x000000FF);
        tmp += (cpuRegs .* IDXREG);

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
            const  RegBank  &cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        GuestMemoryAddress  gmAddr  = getOperandAddress(
                uOperand, cpuRegs, manMem, addCyc);
        return  manMem.template readMemory<RegType>(gmAddr);
    }

};


//========================================================================
/**
**    インダイレクトインデックスオペランド。
**/

template  <
    TRegPtr IDXREG = &RegBank::Y,
    int PCC=1,
    typename TMemMan = MemoryManager>
struct  IdxIndY
{
    typedef     TMemMan     MemManType;

    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegBank  &cpuRegs,
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

        //  インデックスレジスタの値を加算する。    //
        gmAddr  += (cpuRegs .* IDXREG);

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
            const  RegBank  &cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        GuestMemoryAddress  gmAddr  =
                getOperandAddress(uOperand, cpuRegs, manMem, addCyc);
        return  manMem.template readMemory<RegType>(gmAddr);
    }

};


//========================================================================
/**
**    ゼロページオペランド。
**/

template  <TRegPtr IDXREG = &RegBank::Zr, typename TMemMan = MemoryManager>
struct  ZeroPage
{
    typedef     TMemMan     MemManType;

    GuestMemoryAddress
    getOperandAddress(
            const  OpeCode  uOperand,
            const  RegBank  &cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        addCyc  = 0;
        return ( (uOperand + (cpuRegs .* IDXREG)) & 0x000000FF );
    }

    RegType
    getOperandValue(
            const  OpeCode  uOperand,
            const  RegBank  &cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)  const
    {
        addCyc  = 0;
        GuestMemoryAddress  gmAddr  =
                getOperandAddress(uOperand, cpuRegs, manMem, addCyc);
        return  manMem.template readMemory<RegType>(gmAddr);
    }

};


//========================================================================
/**
**    メモリオペランド。
**/

template  <typename ADRMODE>
struct  MemoryOperand
{
    typedef     typename  ADRMODE::MemManType   TMemMan;

    GuestMemoryAddress      m_gmAddr;
    const   TMemMan       & m_manMem;

    MemoryOperand(
            const  OpeCode  uOperand,
            RegBank       & cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)
        : m_manMem(manMem)
    {
        this->m_gmAddr  = ADRMODE().getOperandAddress(
                uOperand, cpuRegs.X, cpuRegs.Y, cpuRegs.PC,
                manMem, addCyc);
    }

    RegType
    readValue()  const
    {
        return  m_manMem.template readMemory<RegType>(m_gmAddr);
    }

    void
    wrtieValue(
            const  RegType  valNew)
    {
        m_manMem.template writeMemory<RegType>(m_gmAddr, valNew);
    }

};


//========================================================================
/**
**    レジスタオペランド。
**/

template  <RegType (RegBank::* PTR), typename TMemMan = MemoryManager>
struct  RegisterOperand
{
    RegBank     & m_cpuRegs;

    RegisterOperand(
            const  OpeCode  uOperand,
            RegBank       & cpuRegs,
            const  TMemMan  &manMem,
            ClockCount      &addCyc)
    {
    }

    RegType
    readValue()  const
    {
        return ( m_cpuRegs .* PTR );
    }

    void
    wrtieValue(
            const  RegType  valNew)
    {
        (m_cpuRegs .* PTR)  = valNew;
    }

};


}   //  End of namespace  Addres
}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

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
**      An Implementation of BaseCpuCore class.
**
**      @file       NesMan/BaseCpuCore.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "NesDbg/NesMan/BaseCpuCore.h"
#include    "NesDbg/NesMan/MemoryManager.h"

#include    <cstring>
#include    <ostream>


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    BaseCpuCore  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

BaseCpuCore::BaseCpuCore(
        NesManager    & manNes,
        MemoryManager & manMem)
    : m_manNes(manNes),
#if !defined( NESDBG_USE_GLOBALS )
      mog_cpuRegs(),
      mog_cpuInfo(),
#endif
      m_manMem(manMem)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BaseCpuCore::~BaseCpuCore()
{
}

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

//----------------------------------------------------------------
//    レジスタをリセットする。
//

ErrCode
BaseCpuCore::doHardReset()
{
    mog_cpuRegs.PC  = this->m_manMem.readMemory<BtWord>(0xFFFC);
    mog_cpuRegs.A   = 0;
    mog_cpuRegs.X   = 0;
    mog_cpuRegs.Y   = 0;
    mog_cpuRegs.S   = 0xFF;
    mog_cpuRegs.P   = 0;

    mog_cpuInfo.totalCycles = 7;
    mog_cpuInfo.numOpeCodes = 0;
    mog_cpuInfo.clockCycles = 7;
    mog_cpuInfo.remainClock = 0;

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    レジスタの内容をコピーする。
//

ErrCode
BaseCpuCore::getRegisters(
        RegBank  &copyBuf)  const
{
    return ( ErrCode::FAILURE );
}

//----------------------------------------------------------------
//    レジスタの内容をダンプする。
//

std::ostream  &
BaseCpuCore::printRegisters(
        std::ostream  & outStr)  const
{
    return ( outStr );
}

//----------------------------------------------------------------
//    レジスタの内容を設定する。
//

ErrCode
BaseCpuCore::setRegisters(
        const  RegBank  &cpuRegs)
{
    return ( ErrCode::FAILURE );
}

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

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

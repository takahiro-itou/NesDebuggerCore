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
**      An Implementation of MemoryManager class.
**
**      @file       NesMan/MemoryManager.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "NesDbg/NesMan/MemoryManager.h"


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    MemoryManager  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

MemoryManager::MemoryManager()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

MemoryManager::~MemoryManager()
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
//    メモリを確保する。
//

LpWriteBuf
MemoryManager::allocateMemory(
        const   size_t  numPrgBanks,
        const   size_t  numChrBanks)
{
    this->m_vRomBuf.clear();
    this->m_vRomBuf.resize(numPrgBanks * 0x4000 + numChrBanks * 8192);

    this->m_pRomImg = &(this->m_vRomBuf[0]);
    return ( this->m_pRomImg );
}

//----------------------------------------------------------------
//    メモリマップを構築する。
//

ErrCode
MemoryManager::buildMemoryTable()
{
    return ( ErrCode::FAILURE );
}

//----------------------------------------------------------------
//    メモリを解放する。
//

ErrCode
MemoryManager::releaseMemory()
{
    return ( ErrCode::FAILURE );
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    メモリアドレスを計算する。
//

LpWriteBuf
MemoryManager::getMemoryAddress(
        const   GuestMemoryAddress  gmAddr)  const
{
    return ( nullptr );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    CHR ROM のバンク数を取得する。
//

const   size_t
MemoryManager::getNumChrBanks()  const
{
    return ( this->m_numChrBanks );
}

//----------------------------------------------------------------
//    PRG ROM のバンク数を取得する。
//

const   size_t
MemoryManager::getNumPrgBanks()  const
{
    return ( this->m_numPrgBanks );
}

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

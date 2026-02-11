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
    : m_numPrgBanks(0),
      m_numChrBanks(0),
      m_vRomBuf(),
      m_pRomImg(nullptr),
      m_pPrgRom(nullptr),
      m_pChrRom(nullptr),
      m_memCPU(nullptr),
      m_memPPU(nullptr),
      m_memRAM(nullptr),
      m_memIOM(nullptr),
      m_memROM(nullptr)
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
    this->m_numPrgBanks = numPrgBanks;
    this->m_numChrBanks = numChrBanks;

    this->m_vRomBuf.clear();
    this->m_vRomBuf.resize(numPrgBanks * 0x4000 + numChrBanks * 8192);

    this->m_memCPU  = new BtByte [65536];
    this->m_memPPU  = new BtByte [65536];

    this->m_pRomImg = &(this->m_vRomBuf[0]);
    return ( this->m_pRomImg );
}

//----------------------------------------------------------------
//    メモリマップを構築する。
//

ErrCode
MemoryManager::buildMemoryTable()
{
    this->m_memRAM  = this->m_memCPU + 0;
    this->m_memROM  = pointer_cast<LpByteWriteBuf>(this->m_pRomImg);

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    メモリを解放する。
//

ErrCode
MemoryManager::releaseMemory()
{
    delete []   this->m_memCPU;     this->m_memCPU  = nullptr;
    delete []   this->m_memPPU;     this->m_memPPU  = nullptr;

    this->m_vRomBuf.clear();

    return ( ErrCode::SUCCESS );
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
    if ( gmAddr >= 0x8000 ) {
        return ( this->m_memROM + (gmAddr & 0x7FFF) );
    }
    return ( this->m_memCPU + (gmAddr & 0x7FFF) );
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

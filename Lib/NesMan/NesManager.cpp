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
**      An Implementation of NesManager class.
**
**      @file       NesMan/NesManager.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "NesDbg/NesMan/NesManager.h"

#include    "Cpu6502/Cpu6502.h"
#include    "Cpu6502/Dis6502.h"

#include    <ostream>
#include    <stdio.h>
#include    <sys/stat.h>


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

//  特に内部状態を持たないクラスなのでグローバル変数でも良い。  //
Dis6502     g_disCpu6502;

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    NesManager  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

NesManager::NesManager()
    : m_manMem(),
      m_cpuCur (nullptr),
      m_cpu6502(nullptr),
      m_disCur (&g_disCpu6502)
{
    this->m_cpu6502 = new Cpu6502(*this, this->m_manMem);
    this->m_cpuCur  = this->m_cpu6502;

    g_disCpu6502.setNesDbgManager(*this);
    g_disCpu6502.setMemoryManager(this->m_manMem);
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

NesManager::~NesManager()
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
//    現在動作しているインスタンスを閉じる。
//

ErrCode
NesManager::closeInstance()
{
    return ( ErrCode::FAILURE );
}

//----------------------------------------------------------------
//    リセットを行う。
//

ErrCode
NesManager::doHardReset()
{
    this->m_cpuCur  = this->m_cpu6502;
    //  this->m_cpuCur->doHardReset();

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    現在の命令を実行する。
//

InstExecResult
NesManager::executeCurrentInst()
{
    //  return  this->m_cpuCur->executeNextInst();
    return ( InstExecResult::UNDEFINED_OPECODE );
}

//----------------------------------------------------------------
//    現在のクロック数を取得する。
//

uint64_t
NesManager::getCpuTotalTicks()  const
{
    return  this->m_cpuCur->getCpuTotalTicks();
}

//----------------------------------------------------------------
//    プログラムカウンタを取得する。
//

GuestMemoryAddress
NesManager::getNextPC()  const
{
    return  this->m_cpuCur->getNextPC();
}

//----------------------------------------------------------------
//    ROM ファイルを読み込む。
//

ErrCode
NesManager::openRomFile(
        const   char *  szFileName)
{
    struct stat stbuf;

    //  ファイルの情報を取得する。  //
    int rc  = stat(szFileName, &stbuf);
    if ( rc < 0 ) {
        perror("open rom file");
        return ( ErrCode::FILE_OPEN_ERROR );
    }

    //  ファイルサイズが 0x10 (16)  バイト未満の時は、  //
    //  必要なヘッダが存在していないのでエラーにする。  //
    if ( stbuf.st_size < 16 ) {
        return ( ErrCode::FILE_IO_ERROR );
    }

#if 0
    //  メモリの各領域を確保して、テーブルに保管する。  //
    this->m_manMem.allocateMemory();
    this->m_manMem.buildMemoryTable();

    //  ROM の内容を読み込む。  **/
    const   size_t  cbRead  = (stbuf.st_size < MEM_SIZE_ROM ?
                               stbuf.st_size : MEM_SIZE_ROM);
    FILE *  fp  = fopen(szFileName, "rb");
    if ( fp == nullptr ) {
        this->closeInstance();
        return ( ErrCode::FILE_IO_ERROR );
    }

    LpByteWriteBuf  memRom  = this->m_manMem.getHostAddressOfGuestRom();
    size_t  retRead = fread(memRom, sizeof(uint8_t), cbRead, fp);
    GBDEBUGGER_UNUSED_VAR(retRead);

    fclose(fp);
#endif

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    レジスタの内容をダンプする。
//

std::ostream  &
NesManager::printRegisters(
        std::ostream  & outStr)  const
{
    //  return  this->m_cpuCur->printRegisters(outStr);
    return ( outStr );
}

//----------------------------------------------------------------
//    ニーモニックを表示する。
//

std::ostream  &
NesManager::writeMnemonic(
        std::ostream       &outStr,
        GuestMemoryAddress  gmAddr)  const
{
    return  this->m_disCur->writeMnemonic(outStr, gmAddr);
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

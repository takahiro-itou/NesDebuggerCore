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

#include    "NesDbg/Common/NesDbgUtils.h"

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
    this->m_cpuCur->doHardReset();

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    現在の命令を実行する。
//

InstExecResult
NesManager::executeCurrentInst()
{
    return  this->m_cpuCur->executeNextInst();
}

//----------------------------------------------------------------
//    現在のカウンタ情報を取得する。
//

const   CounterInfo
NesManager::getCpuCounters()  const
{
    return  this->m_cpuCur->getCpuCounters();
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
    BtByte      roHead[16];

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

    //  ファイルを開いてヘッダを読み込む。  //
    FILE *  fp  = nullptr;
#if defined( MSC_VER ) && defined( WIN32 )
    fopen_s(&fp, szFileName, "rb");
#else
    fp  = fopen(szFileName, "rb");
#endif
    if ( fp == nullptr ) {
        this->closeInstance();
        return ( ErrCode::FILE_IO_ERROR );
    }

    size_t  retRead = fread(roHead, sizeof(BtByte), 16, fp);

    //  メモリの各領域を確保して、テーブルに保管する。  //
    LpWriteBuf  memRom  =
            this->m_manMem.allocateMemory(roHead[4], roHead[5]);
    this->m_manMem.buildMemoryTable();

    //  ROM の内容を読み込む。  **/
    const   size_t  cbRead  = (stbuf.st_size - 16);
    retRead = fread(memRom, sizeof(BtByte), cbRead, fp);
    NESDBG_UNUSED_VAR(retRead);

    fclose(fp);

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    レジスタの内容をダンプする。
//

std::ostream  &
NesManager::printRegisters(
        std::ostream  & outStr)  const
{
    return  this->m_cpuCur->printRegisters(outStr);
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

//----------------------------------------------------------------
//    CHR ROM のバンク数を取得する。
//

const   size_t
NesManager::getNumChrBanks()  const
{
    return  this->m_manMem.getNumChrBanks();
}

//----------------------------------------------------------------
//    PRG ROM のバンク数を取得する。
//

const   size_t
NesManager::getNumPrgBanks()  const
{
    return  this->m_manMem.getNumPrgBanks();
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

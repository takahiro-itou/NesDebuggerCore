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
**      An Interface of MemoryManager class.
**
**      @file       NesMan/MemoryManager.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_MEMORY_MANAGER_H )
#    define   NESDBG_NESMAN_INCLUDED_MEMORY_MANAGER_H

#if !defined( NESDBG_PCH_INCLUDED_PRE_COMPILE_H )
#    include    "NesDbg/pch/PreCompile.h"
#endif

#if !defined( NESDBG_SYS_STL_INCLUDED_VECTOR )
#    include    <vector>
#    define   NESDBG_SYS_STL_INCLUDED_VECTOR
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//========================================================================
//
//    MemoryManager  class.
//

class  MemoryManager
{

//========================================================================
//
//    Internal Type Definitions.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    MemoryManager();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~MemoryManager();

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
public:

    //----------------------------------------------------------------
    /**   メモリを確保する。
    **
    **  @return     確保した領域の先頭を返す。
    **/
    virtual  LpWriteBuf
    allocateMemory(
            const   size_t  numPrgBanks,
            const   size_t  numChrBanks);

    //----------------------------------------------------------------
    /**   メモリマップを構築する。
    **
    **/
    virtual  ErrCode
    buildMemoryTable();

    //----------------------------------------------------------------
    /**   メモリを解放する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    releaseMemory();

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   メモリアドレスを計算する。
    **
    **    ゲストのアドレスに対応するホストのアドレスを計算する。
    **
    **  @param [in] gmAddr    ゲストのメモリアドレス。
    **/
    LpWriteBuf
    getMemoryAddress(
            const   GuestMemoryAddress  gmAddr)  const;

    //----------------------------------------------------------------
    /**   メモリの内容を読みだす。
    **
    **/
    template  <typename  T>
    inline  const  T
    readMemory(
            const   GuestMemoryAddress  gmAddr)  const
    {
        if ( gmAddr == 0x2002 ) {
            //  PPU の VBLANK 待ちでよく使われるのでダミーを返す。  //
            return ( static_cast<T>(0x80) );
        }
        const T  *  ptr = static_cast<const T *>(getMemoryAddress(gmAddr));
        return ( *ptr );
    }

    //----------------------------------------------------------------
    /**   メモリの内容を読みだす。
    **
    **/
    template  <typename  T>
    inline  void
    writeMemory(
            const   GuestMemoryAddress  gmAddr,
            const   T                   wValue)  const
    {
        T * ptr = static_cast<T *>(getMemoryAddress(gmAddr));
        (* ptr) = wValue;
    }


//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   CHR ROM のバンク数を取得する。
    **
    **  @return     バンク数を返す。
    **/
    const   size_t
    getNumChrBanks()  const;

    //----------------------------------------------------------------
    /**   PRG ROM のバンク数を取得する。
    **
    **  @return     バンク数を返す。
    **/
    const   size_t
    getNumPrgBanks()  const;

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   PRG ROM のバンク数。  **/
    size_t          m_numPrgBanks;

    /**   CHR ROM のバンク数。  **/
    size_t          m_numChrBanks;

    /**   イメージの全内容。    **/
    std::vector<BtByte>     m_vRomBuf;

    LpWriteBuf      m_pRomImg;

    /**   PRG ROM Bank(s).      **/
    LpcByteReadBuf  m_pPrgRom;

    /**   PPU ROM Bank(s).      **/
    LpcByteReadBuf  m_pChrRom;

    LpByteWriteBuf  m_memCPU;
    LpByteWriteBuf  m_memPPU;

    LpByteWriteBuf  m_memRAM;
    LpByteWriteBuf  m_memIOM;
    LpByteWriteBuf  m_memROM;


//========================================================================
//
//    Other Features.
//
private:
    typedef     MemoryManager       This;
    MemoryManager       (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   MemoryManagerTest;
};

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

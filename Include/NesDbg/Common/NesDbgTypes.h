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
**      Type Definitions.
**
**      @file       Common/NesDbgTypes.h
**/

#if !defined( NESDBG_COMMON_INCLUDED_NESDBG_TYPES_H )
#    define   NESDBG_COMMON_INCLUDED_NESDBG_TYPES_H

#if !defined( NESDBG_COMMON_INCLUDED_NESDBG_PROJECT_H )
#    include    "NesDbgProject.h"
#endif

#if !defined( NESDBG_SYS_INCLUDED_CSTDINT )
#    include    <cstdint>
#    define   NESDBG_SYS_INCLUDED_CSTDINT
#endif

#if !defined( NESDBG_SYS_INCLUDED_STDDEF_H )
#    include    <stddef.h>
#    define   NESDBG_SYS_INCLUDED_STDDEF_H
#endif


NESDBG_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum class  ErrCode
{
    /**   正常終了。    **/
    SUCCESS                 = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    FAILURE                 = 1,

    /**   無効なインデックス指定。  **/
    INDEX_OUT_OF_RANGE      = 2,

    /**   ファイルオープンエラー。  **/
    FILE_OPEN_ERROR         = 3,

    /**   ファイル入出力エラー。    **/
    FILE_IO_ERROR           = 4,

    /**   不正なファイル形式。      **/
    FILE_INVALID_FORMAT     = 5,
};


//----------------------------------------------------------------
//
//    厳格な型の宣言を行うマクロ。
//  将来デバッグ版では厳格な型を利用できるようにするため
//  マクロを予約しておく。
//

#if defined( _DEBUG ) && !defined( NESDBG_DISABLE_STRICT_TYPES )
#    define     DECLARE_STRICT_TYPE(BaseType, DeclType)         \
    typedef     BaseType    DeclType
#else
#    define     DECLARE_STRICT_TYPE(BaseType, DeclType)         \
    typedef     BaseType    DeclType
#endif


//----------------------------------------------------------------
/**
**    読み取り専用バッファ。
**/

typedef     const  void  *      LpcReadBuf;

//--------------------------------------------------------------------------
/**
**    読み書き両用バッファ。
**/

typedef     void  *             LpWriteBuf;


//----------------------------------------------------------------
/**
**    バイト型。
**/

typedef     uint8_t             BtByte;

/**
**    バイト型の読み取り専用バッファ。
**/

typedef     const  BtByte  *    LpcByteReadBuf;

/**
**    バイト型の読み書き両用バッファ。
**/

typedef     BtByte  *           LpByteWriteBuf;


//----------------------------------------------------------------
/**
**    ゲスト上のアドレスを示す整数値。
**/

DECLARE_STRICT_TYPE(uint32_t,   GuestMemoryAddress);

DECLARE_STRICT_TYPE(int32_t,    GuestAddressOffset);

//----------------------------------------------------------------
/**
**    オペコード型。
**/

DECLARE_STRICT_TYPE(uint32_t,   OpeCode);

//----------------------------------------------------------------
/**
**    レジスタの値型。
**/

DECLARE_STRICT_TYPE(uint16_t,   BtWord);

DECLARE_STRICT_TYPE(uint8_t,    RegType);

//----------------------------------------------------------------
/**
**    消費したクロックカウント。
**/

DECLARE_STRICT_TYPE(uint64_t,   ClockCount);


//========================================================================
//
//    安全なポインタ型のキャスト。
//

template  <typename  T>
T  pointer_cast(void  *  p)
{
    return ( static_cast<T>(p) );
}

template  <typename  T>
T  pointer_cast(const  void  *  p)
{
    return ( static_cast<T>(p) );
}


NESDBG_NAMESPACE_END

#endif

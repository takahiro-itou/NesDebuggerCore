//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---  Library Project.  ---                      **
**                                                                      **
**          Copyright (C), 2016-2024, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of SampleDocument class.
**
**      @file       Common/SampleDocument.cpp
**/

#include    "Sample/Common/SampleDocument.h"


SAMPLE_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    SampleDocument  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

SampleDocument::SampleDocument()
    : m_message()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

SampleDocument::~SampleDocument()
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
//    入力メッセージ中に含まれるアルファベットを数える。
//

int
SampleDocument::countAlphabet()  const
{
    const   size_t  len = this->m_message.length();
    size_t  cnt = 0;
    for ( size_t i = 0; i < len; ++ i ) {
        const  char tmp = this->m_message[i];
        if ( ('A' <= tmp) && (tmp <= 'Z') ) {
            ++ cnt;
        } else if ( ('a' <= tmp) && (tmp <= 'z') ) {
            ++ cnt;
        }
    }

    return ( static_cast<int>(cnt) );
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
//    メッセージを設定する。

void
SampleDocument::setMessage(
        const  std::string  &message)
{
    this->m_message = message;
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
SAMPLE_NAMESPACE_END

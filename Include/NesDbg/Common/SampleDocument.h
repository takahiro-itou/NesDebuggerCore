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
**      An Interface of SampleDocument class.
**
**      @file       Common/SampleDocument.h
**/

#if !defined( SAMPLE_COMMON_INCLUDED_SAMPLE_DOCUMENT_H )
#    define   SAMPLE_COMMON_INCLUDED_SAMPLE_DOCUMENT_H

#if !defined( SAMPLE_PCH_INCLUDED_PRE_COMPILE_H )
#    include    "Sample/pch/PreCompile.h"
#endif


SAMPLE_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    SampleDocument  class.
//

class  SampleDocument
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
    SampleDocument();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~SampleDocument();

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
    /**   入力メッセージ中に含まれるアルファベットを数える。
    **
    **  @return     半角アルファベット [A-Za-z] の文字数
    **/
    virtual  int
    countAlphabet()  const;

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   メッセージを設定する。
    **
    **  @param [in] message   入力データ
    **  @return     void.
    **/
    void
    setMessage(
            const  std::string  &message);

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

    std::string     m_message;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   SampleDocumentTest;
};

}   //  End of namespace  Common
SAMPLE_NAMESPACE_END

#endif

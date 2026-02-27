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
**      @file       NesMan/TypeDefs.h
**/

#if !defined( NESDBG_NESMAN_INCLUDED_TYPE_DEFS_H )
#    define   NESDBG_NESMAN_INCLUDED_TYPE_DEFS_H

#if !defined( NESDBG_PCH_INCLUDED_PRE_COMPILE_H )
#    include    "NesDbg/pch/PreCompile.h"
#endif


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

//  クラスの前方宣言。  //
class   BaseCpuCore;
class   BasePpuCore;


//=========================================================================
//
//    Type Definitions.
//

#if defined( NESDBG_DISABLE_SHAREDPTR )
    typedef     BaseCpuCore  *                  BaseCpuCorePtr;
    typedef     BasePpuCore  *                  BasePpuCorePtr;
#else
    typedef     std::shared_ptr<BaseCpuCore>    BaseCpuCorePtr;
    typedef     std::shared_ptr<BasePpuCore>    BasePpuCorePtr;
#endif


}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END

#endif

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
**      Pre-Compiled Header File.
**
**      @file       pch/PreCompile.h
**/

#if !defined( NESDBG_PCH_INCLUDED_PRE_COMPILE_H )
#    define   NESDBG_PCH_INCLUDED_PRE_COMPILE_H


#if defined( WIN32 )
#    if !defined( NESDBG_SYS_INCLUDED_WINDOWS_H )
#        include    <windows.h>
#        define   NESDBG_SYS_INCLUDED_WINDOWS_H
#    endif
#endif  /* defined( WIN32 ) */


#if !defined( NESDBG_SYS_INCLUDED_CSTDINT )
#    include    <cstdint>
#    define   NESDBG_SYS_INCLUDED_CSTDINT
#endif

#if !defined( NESDBG_SYS_INCLUDED_INTTYPES_H )
#    include    <inttypes.h>
#    define   NESDBG_SYS_INCLUDED_INTTYPES_H
#endif

#if !defined( NESDBG_SYS_STL_INCLUDED_IOSFWD )
#    include    <iosfwd>
#    define   NESDBG_SYS_STL_INCLUDED_IOSFWD
#endif

#if !defined( NESDBG_SYS_STL_INCLUDED_MEMORY )
#    include    <memory>
#    define   NESDBG_SYS_STL_INCLUDED_MEMORY
#endif

#if !defined( NESDBG_SYS_INCLUDED_STDDEF_H )
#    include    <stddef.h>
#    define   NESDBG_SYS_INCLUDED_STDDEF_H
#endif

#if !defined( NESDBG_SYS_INCLUDED_STDINT_H )
#    include    <stdint.h>
#    define   NESDBG_SYS_INCLUDED_STDINT_H
#endif

#if !defined( NESDBG_SYS_INCLUDED_STRING )
#    include    <string>
#    define   NESDBG_SYS_INCLUDED_STRING
#endif


#if !defined( NESDBG_COMMON_INCLUDED_NESDBG_TYPES_H )
#    include    "NesDbg/Common/NesDbgTypes.h"
#endif


#endif

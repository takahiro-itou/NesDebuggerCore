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
**      Pre-Compiled Header File.
**
**      @file       pch/PreCompile.h
**/

#if !defined( SAMPLE_PCH_INCLUDED_PRE_COMPILE_H )
#    define   SAMPLE_PCH_INCLUDED_PRE_COMPILE_H

#if !defined( SAMPLE_COMMON_INCLUDED_SAMPLE_SETTINGS_H )
#    include    "Sample/Common/SampleSettings.h"
#endif


#if !defined( SAMPLE_SYS_INCLUDED_STDDEF_H )
#    include    <stddef.h>
#    define   SAMPLE_SYS_INCLUDED_STDDEF_H
#endif

#if !defined( SAMPLE_SYS_INCLUDED_STDINT_H )
#    include    <stdint.h>
#    define   SAMPLE_SYS_INCLUDED_STDINT_H
#endif

#if !defined( SAMPLE_SYS_INCLUDED_STRING )
#    include    <string>
#    define   SAMPLE_SYS_INCLUDED_STRING
#endif

#endif

/////////////////////////////////////////////////////////////////////////////
//
//  CExtend Libraries
//  Copyright (c) 1999, Colin Goodall
//      This software is licensed under the MIT License.
//      See the LICENSE file for details.
//
/////////////////////////////////////////////////////////////////////////////
//
//  Module:
//      CExBase
//
//  File:
//      CExtend\Libraries\CExBase\CExBase.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_h
#define _CExBase_h

/////////////////////////////////////////////////////////////////////////////

#include "CExBase_Platform.h"

/////////////////////////////////////////////////////////////////////////////
//  Some compilers dont support constexpr.  So we use this
//  #define to allow that code to still compile.  Even if its a little
//  less efficient
//

#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    #define CEXTEND_CONSTEXPR_FUNCTION  constexpr

    #define CEXTEND_CONSTEXPR_DECLARE   constexpr
    #define CEXTEND_CONSTEXPR_DEFINE    constexpr
#else
    #define CEXTEND_CONSTEXPR_FUNCTION

    #define CEXTEND_CONSTEXPR_DECLARE
    #define CEXTEND_CONSTEXPR_DEFINE    const
#endif


/////////////////////////////////////////////////////////////////////////////
//  Includes
//

#include "CExBase_MSWindows.h"
#include "CExBase_Linux.h"

#include "CExBase_StdC.h"
#include "CExBase_StdCPP.h"

#include "CExBase_Integers.h"
#include "CExBase_FloatClass.h"
#include "CExBase_Floats.h"

#include "CExBase_VectorTypes.h"
#include "CExBase_DequeTypes.h"
#include "CExBase_ListTypes.h"
#include "CExBase_SetTypes.h"

#include "CExBase_VersionNumber.h"
#include "CExBase_VersionInfo.h"
#include "CExBase_GetLibraryVersionInfo.h"


/////////////////////////////////////////////////////////////////////////////

#endif  // _CExBase_h



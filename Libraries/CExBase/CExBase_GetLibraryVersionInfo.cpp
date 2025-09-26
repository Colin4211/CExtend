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
//      CExtend\Libraries\CExBase\CExBase_GetLibraryVersionInfo.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#include "CExBase.h"
#include "Private_CExBase_VersionStruct.h"

/////////////////////////////////////////////////////////////////////////////
//! void  GetCExtendVersionInfo( CExBase_VersionInfo * ptrVersionInfo )
//
//  :Implementation
//"
#if defined(__cplusplus)
    extern "C"
#else
    extern
#endif // defined(__cplusplus)
void  CExBase_GetCExtendVersionInfo( CExBase_VersionInfo * ptrVersionInfo )
{
    if ( ptrVersionInfo != NULL )
    {
        (*ptrVersionInfo) = Private_CExBaseVersion_VersionInfo;
    }
    return;
}
//.


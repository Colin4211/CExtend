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

namespace CExBase
{

/////////////////////////////////////////////////////////////////////////////
//! bool  GetLibraryVersionInfo( VersionInfo & versionInfo )
//
//  :Implementation
//"
bool  GetLibraryVersionInfo( VersionInfo & versionInfo )
{
    // Clear the provided struct
    memset( &versionInfo, 0, sizeof(VersionInfo) );

    // Copy the version number
    versionInfo.m_VersionNumber.m_Major         = Private_CExBaseVersion_VersionInfo.m_ProductVersionNumber.m_Major     ;
    versionInfo.m_VersionNumber.m_Minor         = Private_CExBaseVersion_VersionInfo.m_ProductVersionNumber.m_Minor     ;
    versionInfo.m_VersionNumber.m_Revision      = Private_CExBaseVersion_VersionInfo.m_ProductVersionNumber.m_Revision  ;
    versionInfo.m_VersionNumber.m_Build         = Private_CExBaseVersion_VersionInfo.m_ProductVersionNumber.m_Build     ;

    // Stupid GCC.  Warns we might truncate string but thats the
    //  whole damn reason were using strncpy to ensure the string
    //  is truncated.  Stupid warning!
    #if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wstringop-truncation"
    #endif

    // Copy the string fields
    strncpy( versionInfo.m_ProductName  ,  Private_CExBaseVersion_VersionInfo.m_ProductName     ,  VersionInfo::max_string_length   );
    strncpy( versionInfo.m_Version      ,  Private_CExBaseVersion_VersionInfo.m_ProductVersion  ,  VersionInfo::max_string_length   );
    strncpy( versionInfo.m_OwnerName    ,  Private_CExBaseVersion_VersionInfo.m_CompanyName     ,  VersionInfo::max_string_length   );
    strncpy( versionInfo.m_Copyright    ,  Private_CExBaseVersion_VersionInfo.m_Copyright       ,  VersionInfo::max_string_length   );
    strncpy( versionInfo.m_Copyright_1  ,  Private_CExBaseVersion_VersionInfo.m_Trademarks      ,  VersionInfo::max_string_length   );
    strncpy( versionInfo.m_Comments_1   ,  Private_CExBaseVersion_VersionInfo.m_Comments        ,  VersionInfo::max_string_length   );

    versionInfo.m_ProductName   [ VersionInfo::max_string_length ] = 0;
    versionInfo.m_Version       [ VersionInfo::max_string_length ] = 0;
    versionInfo.m_OwnerName     [ VersionInfo::max_string_length ] = 0;
    versionInfo.m_Copyright     [ VersionInfo::max_string_length ] = 0;
    versionInfo.m_Copyright_1   [ VersionInfo::max_string_length ] = 0;
    versionInfo.m_Comments_1    [ VersionInfo::max_string_length ] = 0;

    // Re-enable warning disable
    #if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        #pragma GCC diagnostic pop
    #endif


    return (true);
}
//.

/////////////////////////////////////////////////////////////////////////////

}; // namespace CExBase


/////////////////////////////////////////////////////////////////////////////
//! void  CExBase_GetCExtendVersionInfo( CExBase_VersionInfo * ptrVersionInfo )
//
//  :Description
//      This function is marked as obsolete.  Switch to using
//      the GetLibraryVersionInfo() function instead
//
//  :Implementation
//"

    //  #if defined(__cplusplus)
    //     extern "C"
    //  #else
    //     extern
    //  #endif // defined(__cplusplus)

void  CExBase_GetCExtendVersionInfo( CExBase_VersionInfo * ptrVersionInfo )
{
    if ( ptrVersionInfo != NULL )
    {
        (*ptrVersionInfo) = Private_CExBaseVersion_VersionInfo;
    }
    return;
}
//.




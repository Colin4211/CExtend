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
//      CExtend\Libraries\CExBase\CExBase_VersionNumber.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_VersionNumber_h
#define _CExBase_VersionNumber_h

namespace CExBase
{

/////////////////////////////////////////////////////////////////////////////

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    #pragma pack(push,1)
#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    #pragma pack(push,1)
#else
    #error "ERROR: This code is platform specific"
#endif


/////////////////////////////////////////////////////////////////////////////
//! CExBase_VersionNumber
//
//  :Description
//      This structure is used to store a version number.
//
//  :Definition
//"
typedef struct
{
    Uint32          m_Major;
    Uint32          m_Minor;
    Uint32          m_Revision;
    Uint32          m_Build;
} VersionNumber;
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExBase



/////////////////////////////////////////////////////////////////////////////
//! CExBase_VersionNumber
//
//  :Description
//      This structure is used to represent a version number.
//
//  :See Also
//      = VersionInfo
//
//  :Definition
//"
typedef struct
{
    Uint32          m_Major;
    Uint32          m_Minor;
    Uint32          m_Revision;
    Uint32          m_Build;
} CExBase_VersionNumber;
//.

/////////////////////////////////////////////////////////////////////////////

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    #pragma pack(pop)
#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    #pragma pack(pop)
#else
    #error "ERROR: This code is platform specific"
#endif


/////////////////////////////////////////////////////////////////////////////

#endif // _CExBase_VersionNumber_h

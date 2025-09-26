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
//      CExtend\Libraries\CExBase\CExBase_VersionInfo.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_VersionInfo_h
#define _CExBase_VersionInfo_h

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
//! VersionInfo
//
//  :Description
//      This structure is used to store version information.
//
//      - m_VersionNumber is the version number being stored.
//      - m_ProductName is the name of the product.
//      - m_Version is a string version of that the m_VersionNumber.
//      - m_OwnerName is the name of the owner of the product.
//      - m_Copyright is the primary copyright string for the product.
//      - m_Copyright_X are copyright strings for copyrights of
//          products that are contained within the current product.
//      - m_Comments_X are 4 comment strings that include any extra
//          information.
//
//  :Definition
//"
typedef struct
{
    enum { max_string_length = 255 };

    VersionNumber   m_VersionNumber;
    char            m_ProductName       [ max_string_length + 1 ];
    char            m_Version           [ max_string_length + 1 ];
    char            m_OwnerName         [ max_string_length + 1 ];
    char            m_Copyright         [ max_string_length + 1 ];
    char            m_Copyright_1       [ max_string_length + 1 ];
    char            m_Copyright_2       [ max_string_length + 1 ];
    char            m_Copyright_3       [ max_string_length + 1 ];
    char            m_Copyright_4       [ max_string_length + 1 ];
    char            m_Comments_1        [ max_string_length + 1 ];
    char            m_Comments_2        [ max_string_length + 1 ];
    char            m_Comments_3        [ max_string_length + 1 ];
    char            m_Comments_4        [ max_string_length + 1 ];
}  VersionInfo;
//.

/////////////////////////////////////////////////////////////////////////////

}; // namespace CExBase

/////////////////////////////////////////////////////////////////////////////
//! CExBase_VersionInfo
//
//  :Description
//      This structure is tagged as obsolete.  We will continue to use
//      it untill all dependant code has been modified to use
//      the new structure above.
//
//  :Implementation
//"
#define CExBase_VersionInfo_MAX_STRING_LENGTH           (255)
typedef struct
{
    CExBase_VersionNumber    m_ProductVersionNumber;
    CExBase_VersionNumber    m_FileVersionNumber;

    char    m_ProductName       [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
    char    m_ProductVersion    [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
    char    m_FileName          [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
    char    m_FileVersion       [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
    char    m_InternalName      [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
    char    m_CompanyName       [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
    char    m_Copyright         [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
    char    m_Trademarks        [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
    char    m_Comments          [ CExBase_VersionInfo_MAX_STRING_LENGTH + 1 ];
}  CExBase_VersionInfo;
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

#endif // _CExBase_VersionInfo_h


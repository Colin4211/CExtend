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
//      CExOutput
//
//  File:
//      CExtend\Libraries\CExOutput\CExOutput_Exception.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//      <DT_SUB_TOPIC> Exception
//
/////////////////////////////////////////////////////////////////////////////

#include "CExOutput.h"

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! Exception( void )
//
//  :Implementation
//"
Exception::Exception( void )
    :   m_pszSourceFile     ( NULL )
    ,   m_SourceLine        ( 0    )
    ,   m_pszMessageStrA    ( NULL )
    ,   m_pszMessageStrB    ( NULL )
{
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! Exception( const Exception & )
//
//  :Implementation
//"
Exception::Exception( const Exception & rhSide )
    :   m_pszSourceFile     ( rhSide.m_pszSourceFile    )
    ,   m_SourceLine        ( rhSide.m_SourceLine       )
    ,   m_pszMessageStrA    ( rhSide.m_pszMessageStrA   )
    ,   m_pszMessageStrB    ( rhSide.m_pszMessageStrB   )
{
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! explicit Exception( const char *, Uint32, const char *, const char * )
//
//  :Implementation
//"
Exception::Exception( const char *    sourceFile,
                      Uint32          sourceLine,
                      const char *    messageStrA,
                      const char *    messageStrB )
    :   m_pszSourceFile     ( sourceFile   )
    ,   m_SourceLine        ( sourceLine   )
    ,   m_pszMessageStrA    ( messageStrA  )
    ,   m_pszMessageStrB    ( messageStrB  )
{
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~Exception( void )
//
//  :Implementation
//"
Exception::~Exception( void )
{
    m_pszSourceFile     = NULL;
    m_SourceLine        = 0;
    m_pszMessageStrA    = NULL;
    m_pszMessageStrB    = NULL;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const Exception &  operator = ( const Exception & )
//
//  :Implementation
//"
const Exception &  Exception::operator = ( const Exception & rhSide )
{
    if ( this != &rhSide )
    {
        m_pszSourceFile     = rhSide.m_pszSourceFile;
        m_SourceLine        = rhSide.m_SourceLine;
        m_pszMessageStrA    = rhSide.m_pszMessageStrA;
        m_pszMessageStrB    = rhSide.m_pszMessageStrB;
    }
    return (*this);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const char *  source_file( void ) const
//
//  :Implementation
//"
const char *  Exception::source_file( void ) const
{
    return (m_pszSourceFile);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_source_file_string( void ) const
//
//  :Implementation
//"
std::string  Exception::get_source_file_string( void ) const
{
    return (std::string( (m_pszSourceFile==NULL)?"":m_pszSourceFile ));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! Uint32  source_line( void ) const
//
//  :Implementation
//"
Uint32  Exception::source_line( void ) const
{
    return (m_SourceLine);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_source_line_string( void ) const
//
//  :Implementation
//"
std::string  Exception::get_source_line_string( void ) const
{
    char   tempStr[32];
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        _snprintf( tempStr, sizeof(tempStr)-1, "%u", (unsigned int)m_SourceLine );
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        snprintf( tempStr, sizeof(tempStr)-1, "%u", (unsigned int)m_SourceLine );
    #else
        #error "ERROR: This code is platform specific"
    #endif
    tempStr[ sizeof(tempStr)-1 ] = 0;
    return (std::string(tempStr));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const char *  message_a( void ) const
//
//  :Implementation
//"
const char *  Exception::message_a( void ) const
{
    return (m_pszMessageStrA);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_message_a_string( void ) const
//
//  :Implementation
//"
std::string  Exception::get_message_a_string( void ) const
{
    return (std::string( (m_pszMessageStrA==NULL)?"":m_pszMessageStrA ));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const char *  message_b( void ) const
//
//  :Implementation
//"
const char *  Exception::message_b( void ) const
{
    return (m_pszMessageStrB);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_message_b_string( void ) const
//
//  :Implementation
//"
std::string  Exception::get_message_b_string( void ) const
{
    return (std::string( (m_pszMessageStrB==NULL)?"":m_pszMessageStrB ));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_message_string( void ) const
//
//  :Implementation
//"
std::string  Exception::get_message_string( void ) const
{
    std::string msgStrA = get_message_a_string();
    std::string msgStrB = get_message_b_string();
    std::string msgStr  = msgStrA
                        + ( ((msgStrA.empty()==false)&&(msgStrB.empty()==false)) ? " - " : "" )
                        + msgStr;
    return (msgStr);
}
//.

/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput




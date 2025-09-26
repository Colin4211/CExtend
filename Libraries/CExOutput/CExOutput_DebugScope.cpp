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
//      CExtend\Libraries\CExOutput\CExOutput_DebugScope.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//      <DT_SUB_TOPIC> DebugScope
//
/////////////////////////////////////////////////////////////////////////////

#include "CExOutput.h"

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! DebugScope( const char * sourceFile, Uint32 sourceLine, const char * pszName )
//
//  :Description
//      This is the constructor for the DebugScope class.  It will
//      create the object and generate the OM_ETD_ENTER_SCOPE Message.
//
//  :Implementation
//"
DebugScope::DebugScope( const char *   sourceFile,
                        Uint32         sourceLine,
                        const char *   pszScopeName,
                        bool            fGenOutput,
                        bool            fReportScope )
    :   m_SourceFile    ( sourceFile )
    ,   m_SourceLine    ( sourceLine )
    ,   m_PszScopeName  ( pszScopeName )
    ,   m_fGenOutput    ( fGenOutput != false )
    ,   m_fReportScope  ( (fGenOutput != false) && (fReportScope != false) )
{
    if ( m_fReportScope == true )
    {
        CExOutput::Manager::singleton().generate_output_event_va( OM_ETD_ENTER_SCOPE,
                                                                  m_SourceFile,
                                                                  m_SourceLine,
                                                                  m_PszScopeName,
                                                                  ">>>>> SCOPE START >>>>>" );
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~DebugScope( void )
//
//  :Description
//      This is the destructor for the DebugScope class.  It will
//      create the object and generate the OM_ETD_EXIT_SCOPE Message.
//
//  :Implementation
//"
DebugScope::~DebugScope( void )
{
    if ( m_fReportScope == true )
    {
        CExOutput::Manager::singleton().generate_output_event_va( OM_ETD_EXIT_SCOPE,
                                                                  m_SourceFile,
                                                                  m_SourceLine,
                                                                  m_PszScopeName,
                                                                  "<<<<< SCOPE EXIT  <<<<<" );
    }
    return;
}
//.

/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput



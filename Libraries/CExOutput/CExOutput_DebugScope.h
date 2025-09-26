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
//      CExtend\Libraries\CExOutput\CExOutput_DebugScope.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_DebugScope_h
#define _CExOutput_DebugScope_h

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! DebugScope
//
//  :Description
//      This classes works with the OM_DEBUG_SCOPE() macro to generate
//      output messages when a scope is entered or left.
//
//  :Declaration
//"
class DebugScope
{
    // Data Members
    private:
        const char *    m_SourceFile;
        Uint32          m_SourceLine;
        const char *    m_PszScopeName;
        bool            m_fGenOutput;
        bool            m_fReportScope;

    // Construction, Use get_singleton() to access
    public:
        DebugScope( const char *    sourceFile,
                    Uint32          sourceLine,
                    const char *    pszScopeName,
                    bool            fGenOutput,
                    bool            fReportScope );
        ~DebugScope( void );
    // Not Implemented, Do Not Use
    private:
        DebugScope( void );
        DebugScope( const DebugScope & rhSide );
        const DebugScope &  operator = ( const DebugScope & rhSide );

    // Public Interface
    public:
        const char *    scope_name( void ) const    {   return (m_PszScopeName);    };
        bool            gen_output( void ) const    {   return (m_fGenOutput);      };
        bool            report_scope( void ) const  {   return (m_fReportScope);    };
};
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput

#endif // _CExOutput_DebugScope_h



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
//      CExtend\Libraries\CExOutput\CExOutput_Exception.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_Exception_h
#define _CExOutput_Exception_h

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! Exception
//
//  :Declaration
//"
class Exception
{
    // Data Members
    private:
        const char *    m_pszSourceFile;
        Uint32          m_SourceLine;
        const char *    m_pszMessageStrA;
        const char *    m_pszMessageStrB;

    // Construction
    public:
        Exception( void );
        Exception( const Exception & rhSide );
        explicit Exception( const char *    sourceFile,
                            Uint32          sourceLine,
                            const char *    messageStrA,
                            const char *    messageStrB );
        ~Exception( void );
        const Exception &  operator = ( const Exception & rhSide );

    // Public Interface
    public:

        const char *    source_file( void ) const;
        std::string     get_source_file_string( void ) const;
        Uint32          source_line( void ) const;
        std::string     get_source_line_string( void ) const;
        const char *    message_a( void ) const;
        std::string     get_message_a_string( void ) const;
        const char *    message_b( void ) const;
        std::string     get_message_b_string( void ) const;
        std::string     get_message_string( void ) const;

};
//.

}; // namespace CExOutput

#endif // _CExOutput_Exception_h



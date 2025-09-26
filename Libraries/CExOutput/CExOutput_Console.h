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
//      CExtend\Libraries\CExOutput\CExOutput_Console.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_Console_h
#define _CExOutput_Console_h

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! Console
//
//  :Description
//      This class is provides a simple standardized method for sending
//      the Output Manager events to the console.
//
//      This is a very simple class with limited functionality.
//      For more advanced features it is strongly recomended to use
//      the CExUtil::Console class.  Please note that both that
//      class and this class should not be used at the same time.
//
//  :Declaration
//"
class Console
{
    // Friends
    friend Manager;

    // Data Members
    private:
        bool            m_fEnabled;

    // Construction
        // USe singleton() to obtain instance
    private:
        Console( void );
        ~Console( void );
    // Not Implemented, Do Not Use
    private:
        Console( const Console & rhs );
        const Console &  operator = ( const Console & rhs );

    // Public Interface
    public:
        static Console &  singleton( void );

        void    enable( void );
        void    disable( void );
        bool    is_enabled( void ) const    {   return (m_fEnabled!=false);     };

        static  std::string get_event_type_string( OM_EventType eventType );

    // Private Interface
    private:
        static  void  OM_CB_FUNCTION    event_logging_callback( void );

        void    process_events( void );
        void    process_event( const OM_OutputEvent & outputEvent );

        static  void  print_event( const char *   pszPrefix,
                                   OM_EventType   eventType,
                                   const char *   pszSourceFile,
                                   Uint32         sourceLine,
                                   const char *   pszScopeName,
                                   const char *   pszEventStr );


};
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput

#endif // _CExOutput_Console_h



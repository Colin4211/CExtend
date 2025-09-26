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
//      CExtend\Libraries\CExOutput\CExOutput_Console.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//      <DT_SUB_TOPIC> Console
//
/////////////////////////////////////////////////////////////////////////////

#include "CExOutput.h"

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! Console( void )
//
//  :Implementation
//"
Console::Console( void )
    :   m_fEnabled( false )
{
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~Console( void )
//
//  :Implementation
//"
Console::~Console( void )
{
    m_fEnabled = false;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static Console &  singleton( void )
//
//  :Implementation
//"
Console &  Console::singleton( void )
{
    static Console  theOneAndOnly;
    return (theOneAndOnly);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  enable( void )
//
//  :Implementation
//"
void  Console::enable( void )
{
    Manager::singleton().set_callback( event_logging_callback );
    m_fEnabled = true;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  disable( void )
//
//  :Implementation
//"
void  Console::disable( void )
{
    Manager::singleton().set_callback( NULL );
    m_fEnabled = false;
    return;
}
//.



/////////////////////////////////////////////////////////////////////////////
//! static  std::string get_event_type_string( OM_EventType eventType )
//
//  :Description
//      Returns a string version (suitable for display) of the supplied
//      event type.
//
//  :Implementation
//"
/* static */ std::string  Console::get_event_type_string( OM_EventType eventType )
{
    char            tempStr[ 32 ];
    OM_EventType    catType = eventType & OM_ET_MASK_CATAGORY;
    OM_EventType    msgType = eventType & OM_ET_MASK_MESSAGEID;
    std::string     resultStr;

    if ( catType == OM_CATAGORY_REGULAR )
    {
        // Add nothing
    }
    else if ( catType == OM_CATAGORY_DEBUG )
    {
        resultStr += "DBG_";
    }
    else if ( catType == OM_CATAGORY_FILE_OPS )
    {
        resultStr += "FILEOPS_";
    }
    else
    {
        sprintf( tempStr, "CAT[%x]_", (unsigned int)(catType) );
        resultStr += tempStr;
    }

    switch (msgType)
    {
        case OM_MSGID_INFO:             resultStr += "Info";        break;
        case OM_MSGID_WARNING:          resultStr += "Warning";     break;
        case OM_MSGID_ERROR:            resultStr += "Error";       break;
        case OM_MSGID_DETAIL:           resultStr += "Warning";     break;
        case OM_MSGID_HELP:             resultStr += "Help";        break;
        case OM_MSGID_D_DUMP:           resultStr += "Dump";        break;
        case OM_MSGID_D_ASSERT:         resultStr += "Assert";      break;
        case OM_MSGID_D_BREAK:          resultStr += "Break";       break;
        case OM_MSGID_D_ENTER_SCOPE:    resultStr += "ScopeBgn";    break;
        case OM_MSGID_D_EXIT_SCOPE:     resultStr += "ScopeEnd";    break;
        default:
            sprintf( tempStr, "MSGID[%x]", (unsigned int)(msgType) );
            resultStr += tempStr;
            break;
    }

    return (resultStr);
}
//.




/////////////////////////////////////////////////////////////////////////////
//! static void  OM_CB_FUNCTION  event_logging_callback( void )
//
//  :Description
//      This is the callback function which is supplied to the Manager
//      class to trap notifications of new output events.
//
//  :Implementation
//"
void  OM_CB_FUNCTION  Console::event_logging_callback( void )
{
    static Console & theConsole = singleton();
    theConsole.process_events();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  process_events( .... )
//
//  :Description
//      The process_events() function will "pump" the CExOutput event
//      queue and process the events untill the queue is empty, then
//      the function returns.
//
//  :Implementation
//"
void  Console::process_events( void )
{
    OM_OutputEvent      outputEvent;
    static Manager &    theManager  = Manager::singleton();
    while ( theManager.get_output_event( outputEvent ) == true )
    {
        process_event( outputEvent );
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  void  process_event( const OM_OutputEvent & )
//
//  :Implementation
//"
void  Console::process_event( const OM_OutputEvent & outputEvent )
{
    print_event( NULL,
                 outputEvent.m_EventType,
                 outputEvent.m_SourceFile,
                 outputEvent.m_SourceLine,
                 outputEvent.m_ScopeName,
                 outputEvent.m_EventString );
    return;
}

/////////////////////////////////////////////////////////////////////////////

/*static*/  void  Console::print_event( const char *   pszPrefix,
                                        OM_EventType   eventType,
                                        const char *   pszSourceFile,
                                        Uint32         sourceLine,
                                        const char *   pszScopeName,
                                        const char *   pszEventStr )
{
    (void)(pszSourceFile);
    (void)(sourceLine);

    std::string typeStr = get_event_type_string(eventType);
    std::string outputStr;

    #if defined(CEXTEND_DEBUG)
        std::string locationStr;
        if ( pszSourceFile != NULL )
        {
            if ( pszSourceFile[0] != 0 )
            {
                locationStr = pszSourceFile;
                char lineStr[ 32 ];
                sprintf( lineStr, "(%d)", (int)sourceLine );
                locationStr += lineStr;
            }
        }

        if ( locationStr.empty() == false )
        {
            outputStr += locationStr;
            outputStr += " : ";
        }
    #endif // defined(CEXTEND_DEBUG)

    if ( typeStr.empty() == false )
    {
        outputStr += typeStr;
        outputStr += " : ";
    }

    if ( pszScopeName != NULL )
    {
        if ( pszScopeName[0] != 0 )
        {
            outputStr += pszScopeName;
            outputStr += " -=> ";
        }
    }

    if ( pszEventStr != NULL )
    {
        outputStr += pszEventStr;
    }

    if ( pszPrefix != NULL )
    {
        outputStr = pszPrefix + outputStr;
    }

    printf( "%s\n", outputStr.c_str() );
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput




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
//      CExtend\Libraries\CExOutput\CExOutput_OutputEvent.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//      <DT_SUB_TOPIC> OutputEvent
//
/////////////////////////////////////////////////////////////////////////////

#include "CExOutput.h"

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! OutputEvent( void )
//
//  :Description
//      This is the default constructor for the OutputEvent class.  It
//      constructs the object in the empty state.
//
//  :Implementation
//"
OutputEvent::OutputEvent( void )
{
    clear();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! OutputEvent( const OutputEvent & )
//
//  :Description
//      This is the copy constructor for the OutputEvent class.  It creates
//      the current object as a duplicate of the supplied object.
//
//  :Implementation
//"
OutputEvent::OutputEvent( const OutputEvent & rhSide )
    : m_Structure( rhSide.m_Structure )
{
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! explicit  OutputEvent( const OM_OutputEvent & )
//
//  :Description
//      This is an alternate initialization constructor for the OutputEvent
//      class.  It will create the new OutputEvent object with the supplied
//      structure.  This constructor is equivilant to calling the default
//      constructor then the initialize() member function.
//
//  :Implementation
//"
OutputEvent::OutputEvent( const OM_OutputEvent & omOutputEvent )
{
    initialize( omOutputEvent );
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~OutputEvent( void )
//
//  :Description
//      This is the destructor for the OutputEvent class.
//
//  :Implementation
//"
OutputEvent::~OutputEvent( void )
{
    clear();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const OutputEvent &  operator = ( const OutputEvent & )
//
//  :Description
//      This is the assignment operator for the OutputEvent class.  It
//      will copy the contents of the supplied object into the current
//      object.
//
//  :Implementation
//"
const OutputEvent &  OutputEvent::operator = ( const OutputEvent & rhSide )
{
    if ( this != &rhSide )
    {
        m_Structure = rhSide.m_Structure;
    }
    return (*this);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  clear( void )
//
//  :Description
//      This function will clear the contents of the OutputEvent class
//      and return it to the empty state.
//
//  :Implementation
//"
void  OutputEvent::clear( void )
{
    memset( &m_Structure, 0, sizeof(m_Structure) );
    m_Structure.m_TimeStruct = TimeStamp().om_time_struct();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  empty( void ) const
//
//  :Description
//      This function will return true if the current object is in the
//      empty state.
//
//  :Implementation
//"
bool  OutputEvent::empty( void ) const
{
    if ( m_Structure.m_SourcePlatform != 0 )
    {
        return (false);
    }
    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  swap( OutputEvent & rhSide )
//
//  :Description
//      Standard swap function.
//
//  :Implementation
//"
void  OutputEvent::swap( OutputEvent & rhSide )
{
    if ( this != &rhSide )
    {
        std::swap( m_Structure, rhSide.m_Structure );
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////
//! int  compare( const OutputEvent & rhSide ) const
//
//  :Description
//      Function compares two Output events.
//      Comparison is based on mem cmp of both structs.  This
//      behaviour may change in the future.
//
//  :Implementation
//"
int  OutputEvent::compare( const OutputEvent & rhSide ) const
{
    int cmpRes = memcmp( &m_Structure, &(rhSide.m_Structure), sizeof(m_Structure) );
    if ( cmpRes < 0 )
    {
        return (-1);
    }
    else if ( cmpRes > 0 )
    {
        return (+1);
    }
    return (0);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  initialize( const OM_OutputEvent & )
//
//  :Description
//      This function will initialize the current object with the supplied
//      OM_OutputEvent structure.  If the supplied structure is not
//      valid the function will fail and the object will be cleared to
//      the empty state.
//
//      The rules for what is considered a "valid" structure are:
//          - m_SourcePlatform non zero
//          - m_PacketIndex is non-zero
//          - m_TimeStruct is valid (and non-empty)
//          - Strings must be null terminated.
//
//  :Implementation
//"
bool  OutputEvent::initialize( const OM_OutputEvent & omOutputEvent )
{
    clear();

    if ( omOutputEvent.m_SourcePlatform == 0 )
    {
        return (false);
    }
    if ( omOutputEvent.m_PacketIndex == 0 )
    {
        return (false);
    }
    if ( TimeStamp(omOutputEvent.m_TimeStruct).empty() == true )
    {
        return (false);
    }

    for ( int strIndex = 1; strIndex <= 3; strIndex++ )
    {
        const char *    pString = NULL;
        size_t          maxLen  = 0;
        switch ( strIndex )
        {
            case 1:
                pString = &(omOutputEvent.m_SourceFile[0]);
                maxLen  = sizeof(omOutputEvent.m_SourceFile);
                break;
            case 2:
                pString = &(omOutputEvent.m_ScopeName[0]);
                maxLen  = sizeof(omOutputEvent.m_ScopeName);
                break;
            case 3:
                pString = &(omOutputEvent.m_EventString[0]);
                maxLen  = sizeof(omOutputEvent.m_EventString);
                break;
            default:
                break;
        }

        if ( pString != NULL )
        {
            bool fResult = false;
            try
            {
                for ( size_t strPos = 0; strPos < maxLen; strPos++ )
                {
                    if ( pString[strPos] == 0 )
                    {
                        fResult = true;
                        break;
                    }
                }
            }
            catch ( ... )
            {
                fResult = false;
            }
            if ( fResult == false )
            {
                return (false);
            }
        }
    }

    m_Structure = omOutputEvent;
    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  initialize( ... )
//
//  :Description
//      This function will initialize the current OutputEvent object
//      using the supplied values.  Any values not supplied as
//      arguments to the function but required by the structure will
//      be automatically populated.
//
//  :Implementation
//"
bool  OutputEvent::initialize( Uint32              packetIndex,
                               OM_EventType        eventType,
                               const char *        sourceFile,
                               Uint32              sourceLine,
                               const char *        scopeName,
                               const char *        eventString )
{
    clear();

    // Determine the process and thread id's
    OM_ProcessIDType    processId   = 0;
    OM_ThreadIDType     threadId    = 0;

    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        processId   = ::GetCurrentProcessId();
        threadId    = ::GetCurrentThreadId();
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        processId   = getpid();
        threadId    = pthread_self();
    #else
        #error "ERROR: This code is platform specific"
    #endif

    // Determine the curren time
    TimeStamp   timeStamp;
    timeStamp.initialize();

    OM_OutputEvent  omOutputEvent;
    omOutputEvent.m_SourcePlatform  = CEXTEND_PLATFORM_TYPE;
    omOutputEvent.m_SizeOf          = sizeof(m_Structure);
    omOutputEvent.m_ProcessID       = processId;
    omOutputEvent.m_ThreadID        = threadId;
    omOutputEvent.m_PacketIndex     = packetIndex;
    omOutputEvent.m_TimeStruct      = timeStamp.om_time_struct();
    omOutputEvent.m_EventType       = eventType;
    omOutputEvent.m_SourceLine      = sourceLine;

    // Manually copy the filename string character by character
    //  untill we get to the end of the string.  If we hit a path
    //  separator, then we reset the output pos back to the start of
    //  the string, this way if a supplied filename has a path portion
    //  to it, it is stripped off.
    try
    {
        if ( sourceFile != NULL )
        {
            size_t  maxSourceLen    = sizeof(omOutputEvent.m_SourceFile) - 1;
            size_t  outPos          = 0;
            size_t  srcPos          = 0;
            while ( outPos < maxSourceLen )
            {
                char theChar = sourceFile[srcPos];
                omOutputEvent.m_SourceFile[ outPos ] = theChar;
                if (theChar == 0 )
                {
                    break;
                }
                else if ( (theChar =='\\') || (theChar == '/') )
                {
                    outPos = 0;
                    srcPos++;
                }
                else
                {
                    outPos++;
                    srcPos++;
                }
            }
            omOutputEvent.m_SourceFile[ maxSourceLen ] = 0;
        }
    }
    catch ( ... )
    {
        omOutputEvent.m_SourceFile[0] = 0;
    }

    // Now we need to copy in the scope name string.
    try
    {
        SafeStringCopy( omOutputEvent.m_ScopeName,
                        scopeName,
                        sizeof(omOutputEvent.m_ScopeName) );
    }
    catch ( ... )
    {
        omOutputEvent.m_ScopeName[0] = 0;
    }

    // Now we need to copy in the message string.
    try
    {
        SafeStringCopy( omOutputEvent.m_EventString,
                        eventString,
                        sizeof(omOutputEvent.m_EventString) );
    }
    catch ( ... )
    {
        omOutputEvent.m_EventString[0] = 0;
    }

    return (initialize(omOutputEvent));
};
//.

}; // namespace CExOutput



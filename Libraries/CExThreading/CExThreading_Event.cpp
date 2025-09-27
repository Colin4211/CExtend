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
//      CExThreading
//
//  File:
//      CExtend\Libraries\CExThreading\CExThreading_Event.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> Event
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! Event( Style = Style_PROCESS, const char * pszName = NULL, bool fReportState = false );
//
//  :Description:
//      This is the constructor for the Event class.
//
//      If the constructor fails to create the underlying mutex
//      appropriate error messages will be generated.  The caller
//      can determine if the constructor was succesful by calling
//      the is_ok() member function.
//
//  :Implementation
//"
Event::Event( ObjectStyle       objectStyle     /*= ObjectStyle_PROCESS*/,
              const char *      pszName         /*= NULL*/,
              bool              fReportState    /*= false*/ )
    : m_Platform( platformstruct_get_empty() )
{
    // Get a "non-const" reference to the CommonMemberStruct
    //  This is the only time we ever do this.  We handle it here
    //  rather than in the member-init list so we can verify
    //  (and in turn fixup) any of the supplied args
    ObjectIdent &   objectIdent     = const_cast< ObjectIdent & >( m_ObjectIdent );
    objectIdent.initialize( objectStyle,
                            ObjectType_EVENT,
                            pszName,
                            fReportState,
                            true );

    if ( objectIdent.created_flag() == true )
    {
        bool fCreateFlag = false;
        // Now we create the underlying mutex
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            if ( win_create_event() == false )
            {
                OM_TRACE( OM_ETD_ERROR, "Event::Event() ==> Call to win_create_event() failed." );
            }
            else
            {
                fCreateFlag = true;
            }
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            if ( m_ObjectIdent.object_style() != ObjectStyle_PROCESS )
            {
                OM_TRACE( OM_ETD_ERROR, "Event::Event() ==> Linux only supports ObjectStyle_PROCESS." );
                fCreateFlag = false;
            }
            else
            {
                if ( linux_create_event() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Event::Event() ==> Call to linux_create_event() failed." );
                }
                else
                {
                    fCreateFlag = true;
                }
            }
        #else
            #error "ERROR: This code is platform specific"
        #endif
        objectIdent.set_create_flag( fCreateFlag );
    }

    if ( m_ObjectIdent.created_flag() == false )
    {
        m_Platform = platformstruct_get_empty();
    }

    if ( m_ObjectIdent.report_state_flag() != false )
    {
        if ( m_ObjectIdent.created_flag() == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Event::Event() ==> Failed to create Event = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Event::Event() ==> Created Event = %s", m_ObjectIdent.name() );
        }
    }


    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~Event( void )
//
//  :Description
//      This is the destructor for the Event class.
//
//  :Implementation
//"
Event::~Event( void )
{
    bool fResult = false;
    if ( m_ObjectIdent.created_flag() != false )
    {
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            if ( win_destroy_event() == false )
            {
                OM_TRACE( OM_ETD_ERROR, "Event::~Event() ==> Call to win_destroy_event() failed" );
            }
            else
            {
                fResult = true;
            }
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            if ( linux_destroy_event() == false )
            {
                OM_TRACE( OM_ETD_ERROR, "Event::~Event() ==> Call to linux_destroy_event() failed" );
            }
            else
            {
                fResult = true;
            }
        #else
            #error "ERROR: This code is platform specific"
        #endif
    }

    if ( m_ObjectIdent.report_state_flag() != false )
    {
        if ( fResult == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Event::~Event() ==> Failed to destroy Event = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Event::~Event() ==> Destroyed Event = %s", m_ObjectIdent.name() );
        }
    }

    // Blank out all the date members
    ObjectIdent & objectIdent = const_cast< ObjectIdent & >( m_ObjectIdent );
    objectIdent.clear();
    m_Platform = platformstruct_get_empty();

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_ok( void ) const
//
//  :Returns
//      If the Mutex was succesfully created the object is in a valid
//      state and the function returns true.  Otherwise the function
//      returns false.
//
//  :Description
//      This function is used to see if the underlying Mutex
//      object is valid.  If the function returns false to indicate
//      that the object is not valid then the application should not
//      use the object to protect critical sections of there code.
//
//      However, on the whole the likelyhood of the function failing
//      to be created is _extremely_ low.
//
//  :Implementation
//"
bool  Event::is_ok( void ) const
{
    return (m_ObjectIdent.created_flag());
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  set( void )
//
//  :Description
//      This function will "set" the underlying event to the signaled
//      state.
//
//  :Returns
//      If the function succesfully places the event in the "signaled"
//      or "set" state the function returns true.  Otherwise the function
//      returns false.
//
//  :Implementation
//"
bool  Event::set( void )
{
    // Verify the state
    if (m_ObjectIdent.created_flag() == false)
    {
        OM_TRACE( OM_ETD_ERROR, "Event::set() ==> Event object is not valid." );
        return (false);
    }

    bool fResult = false;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        fResult = win_set_event();
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        fResult = linux_set_event();
    #else
        #error "ERROR: This code is platform specific"
    #endif

    if ( m_ObjectIdent.report_state_flag() == true )
    {
        if ( fResult == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Event::set() ==> Failed to Set Event = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Event::set() ==> Set Event = %s", m_ObjectIdent.name() );
        }
    }

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  reset( void )
//
//  :Description
//      This function will "reset" the underlying event to the unsignaled
//      state.
//
//  :Returns
//      If the function succesfully places the event in the "unsignaled"
//      state the function returns true.  Otherwise the function
//      returns false.
//
//  :Implementation
//"
bool  Event::reset( void )
{
    // Verify the state
    if (m_ObjectIdent.created_flag() == false)
    {
        OM_TRACE( OM_ETD_ERROR, "Event::reset() ==> Event object is not valid." );
        return (false);
    }

    bool    fResult = false;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        fResult = win_reset_event();
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        fResult = linux_reset_event();
    #else
        #error "ERROR: This code is platform specific"
    #endif

    if ( m_ObjectIdent.report_state_flag() == true )
    {
        if ( fResult == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Event::reset() ==> Failed to Reset Event = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Event::reset() ==> Reset Event = %s", m_ObjectIdent.name() );
        }
    }

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  wait( WaitMode = WaitMode_FOREVER, WaitTime = WaitTime_EMPTY )
//
//  :Description
//      This function will wait for the current event to become signalled.
//
//  :Arguments
//      = WaitMode waitMode = WaitMode_FOREVER
//          Instructs the function on how to wait.
//      = WaitTime waitTime = 0
//          If the waitMode supplied is WaitMode_TIMER then this argument
//          is the number of milliseconds to wait for the lock before
//          giving up.
//          If the waitMode supplied is WaitMode_FOREVER then this
//          argument is not used and should be set to zero.
//
//  :Returns
//      If the current event became signalled then the function returns
//      true.  If the function failed to wait until the event became
//      signalled the function returns false.
//
//  :Implementation
//"
bool  Event::wait( WaitMode waitMode /*= WaitMode_FOREVER*/, WaitTime waitTime /*= WaitTime_EMPTY*/ )
{
    // Verify the state
    if (m_ObjectIdent.created_flag() == false)
    {
        OM_TRACE( OM_ETD_ERROR, "Event::wait() ==> Event object is not valid." );
        return (false);
    }

    // Verify the waitTime argument.
    WaitTime    actualWaitTime = waitTime;
    if  ( actualWaitTime > WaitTime_MAX )
    {
        OM_TRACE( OM_ETD_ERROR, "Event::wait() ==> WaitTime out of range, clamping." );
        actualWaitTime = WaitTime_MAX;
    }

    // Verify the waitMode argument
    switch ( waitMode )
    {
        case WaitMode_TIMED:
            break;
        case WaitMode_FOREVER:
            actualWaitTime = WaitTime_EMPTY;
            OM_DEBUG_ASSERT( waitTime == 0 );
            break;
        default:
            OM_TRACE( OM_ETD_ERROR, "Event::wait() ==> Invalid WaitMode." );
            return (false);
    }

    if ( m_ObjectIdent.report_state_flag() == true )
    {
        OM_TRACE1( OM_ETD_INFO, "Event::wait() ==> Waiting for Event = %s", m_ObjectIdent.name() );
    }

    bool    fResult = false;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        fResult = win_wait_event( waitMode, waitTime );
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        fResult = linux_wait_event( waitMode, waitTime );
    #else
        #error "ERROR: This code is platform specific"
    #endif

    if ( m_ObjectIdent.report_state_flag() == true )
    {
        if ( fResult == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Event::wait() ==> Failed to Wait for Event = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Event::wait() ==> Event is Signalled = %s", m_ObjectIdent.name() );
        }
    }

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ObjectIdent  get_object_ident( void ) const
//
//  :Returns
//      This function returns a copy of the ObjectIdent object associated
//      with this Event object.
//
//  :Implementation
//"
ObjectIdent  Event::get_object_ident( void ) const
{
    return (m_ObjectIdent);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static PlatformStruct  platformstruct_get_empty( void )
//
//  :Implementation
//"
Event::PlatformStruct  Event::platformstruct_get_empty( void )
{
    PlatformStruct    platformStruct;
    memset( &platformStruct, 0, sizeof(platformStruct) );
    return (platformStruct);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  win_create_event( void );
//
//  :Description
//      This function is used to create the underlying event in the Win32
//      implementation of this class.  This function should only be called
//      once from the constructor of the Event object.
//
//  :Returns
//      If the event is succesfully created the function returns true.
//      Otherwise the Event object is invalid and the function returns
//      false.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Event::win_create_event( void )
    {
        BOOL fManualReset = TRUE;
        m_Platform.m_hEvent = ::CreateEventA( m_ObjectIdent.get_ptr_security_attributes(),
                                              fManualReset,
                                              FALSE,
                                              m_ObjectIdent.system_name() );
        if (m_Platform.m_hEvent == NULL )
        {
            OM_SYSTEM_ERROR( "Event::win_create_event() == Call to ::CreateEvent() failed.", ::GetLastError() );
            return (false);
        }

        return (true);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  win_set_event( void )
//
//  :Description
//      This function will "set" the event to the signaled
//      state.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Event::win_set_event( void )
    {
        return (::SetEvent(m_Platform.m_hEvent) != FALSE);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  win_reset_event( void )
//
//  :Description
//      This function will "reset" the event to the unsignaled
//      state.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Event::win_reset_event( void )
    {
        return (::ResetEvent(m_Platform.m_hEvent) != FALSE);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool win_wait_event( WaitMode waitMode = WaitMode_FOREVER, WaitTime waitTime = 0 );
//
//  :Description
//      This function will wait for the current event to become signalled.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool Event::win_wait_event( WaitMode waitMode, WaitTime waitTime )
    {
        bool    fResult     = false;
        DWORD   theWaitTime = static_cast< DWORD >( waitTime );
        if (waitMode == WaitMode_FOREVER)
        {
            theWaitTime =INFINITE;
        }
        DWORD   dWaitResult = ::WaitForSingleObject( m_Platform.m_hEvent, theWaitTime );
        if ( (dWaitResult == WAIT_ABANDONED) || (dWaitResult == WAIT_OBJECT_0) )
        {
            fResult = true;
        }

        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  win_destroy_event( void )
//
//  :Returns
//      If the mutex was succesfully destroyed the function returns true.
//      Otherwise it returns false.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Event::win_destroy_event( void )
    {
        BOOL fResult = FALSE;
        if ( m_Platform.m_hEvent != NULL )
        {
            fResult = ::CloseHandle( m_Platform.m_hEvent );
        }
        m_Platform.m_hEvent = NULL;
        return (fResult != FALSE);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  linux_create_event( void );
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Event::linux_create_event( void )
    {
        bool fResult = false;
        try
        {
            if ( pthread_mutex_init( &(m_Platform.m_ProcessMutex),
                                     m_ObjectIdent.get_ptr_mutexattr() ) != 0 )
            {
                OM_TRACE( OM_ETD_ERROR, "Mutex::linux_create_event() ==> Call to pthread_mutex_init() failed." );
                m_Platform.m_fCreateMutex = false;
            }
            else
            {
                m_Platform.m_fCreateMutex = true;
            }

            if ( pthread_cond_init( &(m_Platform.m_ProcessCondition),
                                    NULL ) != 0 )
            {
                OM_TRACE( OM_ETD_ERROR, "Mutex::linux_create_event() ==> Call to pthread_cond_init() failed." );
                m_Platform.m_fCreateCondition = false;
            }
            else
            {
                m_Platform.m_fCreateCondition = true;
            }
            m_Platform.m_fStateFlag = false;
            fResult = ( (m_Platform.m_fCreateMutex==true) && (m_Platform.m_fCreateCondition==true) );
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Event::linux_create_event() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  linux_set_event( void );
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Event::linux_set_event( void )
    {
        bool    fResult = false;
        try
        {
            if ( pthread_mutex_lock( &(m_Platform.m_ProcessMutex) ) == 0 )
            {
                m_Platform.m_fStateFlag = true;
                if ( pthread_mutex_unlock( &(m_Platform.m_ProcessMutex) ) == 0 )
                {
                    if ( pthread_cond_broadcast( &(m_Platform.m_ProcessCondition) ) == 0 )
                    {
                        fResult = true;
                    }
                }
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Event::linux_set_event() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  linux_reset_event( void );
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Event::linux_reset_event( void )
    {
        bool    fResult = false;
        try
        {
            if ( pthread_mutex_lock( &(m_Platform.m_ProcessMutex) ) == 0 )
            {
                m_Platform.m_fStateFlag = false;
                if ( pthread_mutex_unlock( &(m_Platform.m_ProcessMutex) ) == 0 )
                {
                    if ( pthread_cond_broadcast( &(m_Platform.m_ProcessCondition) ) == 0 )
                    {
                        fResult = true;
                    }
                }
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Event::linux_reset_event() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool linux_wait_event( WaitMode waitMode = WaitMode_FOREVER, WaitTime waitTime = 0 );
//
//  :Description
//      This function will wait for the current event to become signalled.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool Event::linux_wait_event( WaitMode waitMode, WaitTime waitTime )
    {
        bool    fResult = false;
        try
        {
            if ( waitMode == WaitMode_TIMED )
            {
                SimpleTimer         simpleTimer;
                struct timespec     absTimeout;
                simpleTimer.start_milliseconds( waitTime );
                m_ObjectIdent.get_abs_timeout( absTimeout, waitTime );

                if ( pthread_mutex_timedlock( &(m_Platform.m_ProcessMutex),
                                              &absTimeout ) == 0 )
                {
                    while ( (m_Platform.m_fStateFlag == false)  &&
                            (simpleTimer.is_expired() == false) )
                    {
                        pthread_cond_timedwait( &(m_Platform.m_ProcessCondition),
                                                &(m_Platform.m_ProcessMutex),
                                                &absTimeout );
                        if ( simpleTimer.empty() == true )
                        {
                            break;
                        }
                    }
                    fResult = (m_Platform.m_fStateFlag != false);
                    pthread_mutex_unlock( &(m_Platform.m_ProcessMutex) );
                }
            }
            else
            {
                if ( pthread_mutex_lock( &(m_Platform.m_ProcessMutex) ) == 0 )
                {
                    while ( m_Platform.m_fStateFlag == false )
                    {
                        pthread_cond_wait( &(m_Platform.m_ProcessCondition),
                                        &(m_Platform.m_ProcessMutex) );
                    }
                    fResult = (m_Platform.m_fStateFlag != false);
                    pthread_mutex_unlock( &(m_Platform.m_ProcessMutex) );
                }
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Event::linux_reset_event() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  linux_destroy_event( void );
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Event::linux_destroy_event( void )
    {
        bool fResult = false;
        try
        {
            fResult = true;
            if ( m_Platform.m_fCreateMutex == true )
            {
                if ( pthread_mutex_destroy( &(m_Platform.m_ProcessMutex) ) != 0 )
                {
                    fResult = false;
                }
            }
            if ( m_Platform.m_fCreateCondition == true )
            {
                if ( pthread_cond_destroy( &(m_Platform.m_ProcessCondition) ) != 0 )
                {
                    fResult = false;
                }
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Event::linux_destroy_event() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.

};  // namespace CExThreading



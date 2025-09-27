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
//      CExtend\Libraries\CExThreading\CExThreading_Mutex.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> Mutex
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! Mutex( ObjectStyle = ObjectStyle_PROCESS, const char * pszName = NULL, bool fReportState = false );
//
//  :Description:
//      This is the default constructor for the Mutex class.
//      This constructor is the recomended method of creating a Mutex
//      object.
//
//  :Implementation
//"
Mutex::Mutex( ObjectStyle       objectStyle     /*= ObjectStyle_PROCESS*/,
              const char *      pszName         /*= NULL*/,
              bool              fReportState    /*= false*/ )
    : m_Platform( platformstruct_get_empty() )
{
    // printf( "Mutex::Mutex() ==> Constructing --> %s\n", pszName ); fflush(stdout);

    // Get a "non-const" reference to the CommonMemberStruct
    //  This is the only time we ever do this.  We handle it here
    //  rather than in the member-init list so we can verify
    //  (and in turn fixup) any of the supplied args
    ObjectIdent &   objectIdent     = const_cast< ObjectIdent & >( m_ObjectIdent );
    objectIdent.initialize( objectStyle,
                            ObjectType_MUTEX,
                            pszName,
                            fReportState,
                            true );

    if ( objectIdent.created_flag() == true )
    {
        bool fCreateFlag = false;
        // Now we create the underlying mutex
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            if ( objectIdent.object_style() == ObjectStyle_PROCESS )
            {
                if ( win_process_create() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::Mutex() ==> Call to win_process_create() failed." );
                }
                else
                {
                    fCreateFlag = true;
                }
            }
            else if ( objectIdent.object_style() == ObjectStyle_SYSTEM )
            {
                if ( win_system_create() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::Mutex() ==> Call to win_system_create() failed." );
                }
                else
                {
                    fCreateFlag = true;
                }
            }
            else
            {
                OM_TRACE( OM_ETD_ERROR, "Mutex::Mutex() ==> Internal Error, bad Style member" );
                OM_DEBUG_BREAK();
            }
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            if ( objectIdent.object_style() == ObjectStyle_PROCESS )
            {
                if ( linux_process_create() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::Mutex() ==> Call to linux_process_create() failed." );
                }
                else
                {
                    fCreateFlag = true;
                }
            }
            else if ( objectIdent.object_style() == ObjectStyle_SYSTEM )
            {
                if ( linux_system_create() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::Mutex() ==> Call to linux_system_create() failed." );
                }
                else
                {
                    fCreateFlag = true;
                }
            }
            else
            {
                OM_TRACE( OM_ETD_ERROR, "Mutex::Mutex() ==> Internal Error, bad Style member" );
                OM_DEBUG_BREAK();
            }
        #else
            #error "ERROR: This code is platform specific"
        #endif
        objectIdent.set_create_flag( fCreateFlag );
    }

    if ( m_ObjectIdent.created_flag() == false )
    {
        printf( "Mutex::Mutex() ==> Create Flag Empty --> %s\n", pszName ); fflush(stdout);
        m_Platform = platformstruct_get_empty();
    }

    if ( m_ObjectIdent.report_state_flag() != false )
    {
        if ( m_ObjectIdent.created_flag() == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Mutex::Mutex() ==> Failed to create Mutex = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Mutex::Mutex() ==> Created Mutex = %s", m_ObjectIdent.name() );
        }
    }


    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~Mutex( void )
//
//  :Description
//      This is the destructor for the Mutex class.
//
//  :Implementation
//"
Mutex::~Mutex( void )
{
    bool fResult = false;
    if ( m_ObjectIdent.created_flag() != false )
    {
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            if ( m_ObjectIdent.object_style() == ObjectStyle_PROCESS )
            {
                if ( win_process_destroy() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::~Mutex() ==> Call to win_process_destroy() failed" );
                }
                else
                {
                    fResult = true;
                }
            }
            else if ( m_ObjectIdent.object_style() == ObjectStyle_SYSTEM )
            {
                if ( win_system_destroy() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::~Mutex() ==> Call to win_system_destroy() failed" );
                }
                else
                {
                    fResult = true;
                }
            }
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            if ( m_ObjectIdent.object_style() == ObjectStyle_PROCESS )
            {
                if ( linux_process_destroy() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::~Mutex() ==> Call to linux_process_destroy() failed" );
                }
                else
                {
                    fResult = true;
                }
            }
            else if ( m_ObjectIdent.object_style() == ObjectStyle_SYSTEM )
            {
                if ( linux_system_destroy() == false )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::~Mutex() ==> Call to linux_system_destroy() failed" );
                }
                else
                {
                    fResult = true;
                }
            }
        #else
            #error "ERROR: This code is platform specific"
        #endif
    }

    if ( m_ObjectIdent.report_state_flag() != false )
    {
        if ( fResult == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Mutex::~Mutex() ==> Failed to destroy Mutex = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Mutex::~Mutex() ==> Destroyed Mutex = %s", m_ObjectIdent.name() );
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
bool  Mutex::is_ok( void ) const
{
    return (m_ObjectIdent.created_flag());
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool lock( WaitMode waitMode = WaitMode_FOREVER, WaitTime waitTime = WaitTime_EMPTY );
//
//  :Arguments
//      = WaitMode waitMode = WaitMode_FOREVER
//          Instructs the function on how to wait.
//      = WaitTime waitTime = WaitTime_EMPTY
//          If the waitMode supplied is WaitMode_TIMER then this argument
//          is the number of milliseconds to wait for the lock before
//          giving up.
//          If the waitMode supplied is WaitMode_FOREVER then this
//          argument is not used and should be set to WaitTime_EMPTY.
//
//  :Returns
//      If the Mutex was succesfully lock()'ed then the function returns
//      true.  If the lock() fails the function returns false.
//
//  :Description
//      This function will attempt to lock the Mutex object.
//
//      For every succesful call to lock() then the code in the
//      calling thread must make a matching call to the
//      release() function.
//
//  :Implementation
//"
bool Mutex::lock( WaitMode waitMode, WaitTime waitTime /*= WaitTime_EMPTY*/ )
{
    // Verify the state
    if (m_ObjectIdent.created_flag() == false)
    {
        OM_TRACE( OM_ETD_ERROR, "Mutex::lock() ==> Mutex object is not valid." );
        return (false);
    }

    // Verify the waitTime argument.
    WaitTime    actualWaitTime = waitTime;
    if  ( actualWaitTime > WaitTime_MAX )
    {
        OM_TRACE( OM_ETD_ERROR, "Mutex::lock() ==> WaitTime out of range, clamping." );
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
            OM_TRACE( OM_ETD_ERROR, "Mutex::lock() ==> Invalid WaitMode." );
            return (false);
    }

    if ( m_ObjectIdent.report_state_flag() == true )
    {
        OM_TRACE1( OM_ETD_INFO, "Mutex::lock() ==> Attempting To Lock Mutex = %s", m_ObjectIdent.name() );
    }

    // Actually perform the lock
    //  This code is platform specific.
    bool    fResult = false;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        if ( m_ObjectIdent.object_style() == Style_PROCESS )
        {
            fResult = win_process_lock( waitMode, actualWaitTime );
        }
        else if ( m_ObjectIdent.object_style() == Style_SYSTEM )
        {
            fResult = win_system_lock( waitMode, actualWaitTime );
        }
        else
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::lock() ==> Internal Error, Unknown mutex style." );
            OM_DEBUG_BREAK();
            fResult = (false);
        }
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        if ( m_ObjectIdent.object_style() == ObjectStyle_PROCESS )
        {
            fResult = linux_process_lock( waitMode, actualWaitTime );
        }
        else if ( m_ObjectIdent.object_style() == ObjectStyle_SYSTEM )
        {
            fResult = linux_system_lock( waitMode, actualWaitTime );
        }
        else
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::lock() ==> Internal Error, Unknown mutex style." );
            OM_DEBUG_BREAK();
            fResult = (false);
        }
    #else
        #error "ERROR: This code is platform specific"
    #endif

    if ( m_ObjectIdent.report_state_flag() == true )
    {
        if ( fResult == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Mutex::lock() ==> Failed to Lock Mutex = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Mutex::lock() ==> Locked Mutex = %s", m_ObjectIdent.name() );
        }
    }

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool release( void )
//
//  :Returns
//      If the mutex was succesfully released the function returns true.
//      Otherwise the function returns false.
//
//  :Description
//      This function is called to release the Mutex.  It must be called
//      (in a given thread) for every succesful call to the lock()
//      function.
//
//  :Implementation
//"
bool  Mutex::release( void )
{
    // Verify the state
    if (m_ObjectIdent.created_flag() == false)
    {
        OM_TRACE( OM_ETD_ERROR, "Mutex::release() ==> Mutex object is not valid." );
        return (false);
    }

    if ( m_ObjectIdent.report_state_flag() == true )
    {
        OM_TRACE1( OM_ETD_INFO, "Mutex::release() ==> Attempting To Release Mutex = %s", m_ObjectIdent.name() );
    }

    // Actually perform the release
    //  This code is platform specific.
    bool    fResult = false;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        if ( m_ObjectIdent.object_style() == ObjectStyle_PROCESS )
        {
            fResult = win_process_release();
        }
        else if ( m_ObjectIdent.object_style() == ObjectStyle_SYSTEM )
        {
            fResult = win_system_release();
        }
        else
        {
            OM_TRACE( OM_ETD_WARNING, "Mutex::release() ==> Unknown mutex style." );
            OM_DEBUG_BREAK();
            fResult = (false);
        }
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        if ( m_ObjectIdent.object_style() == ObjectStyle_PROCESS )
        {
            fResult = linux_process_release();
        }
        else if ( m_ObjectIdent.object_style() == ObjectStyle_SYSTEM )
        {
            fResult = linux_system_release();
        }
        else
        {
            OM_TRACE( OM_ETD_WARNING, "Mutex::release() ==> Unknown mutex style." );
            OM_DEBUG_BREAK();
            fResult = (false);
        }

    #else
        #error "ERROR: This code is platform specific"
    #endif

    if ( m_ObjectIdent.report_state_flag() == true )
    {
        if ( fResult == false )
        {
            OM_TRACE1( OM_ETD_ERROR, "Mutex::release() ==> Failed to Release Mutex = %s", m_ObjectIdent.name() );
        }
        else
        {
            OM_TRACE1( OM_ETD_INFO, "Mutex::release() ==> Released Mutex = %s", m_ObjectIdent.name() );
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
//      with this Mutex object.
//
//  :Implementation
//"
ObjectIdent  Mutex::get_object_ident( void ) const
{
    return (m_ObjectIdent);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static PlatformStruct  platformstruct_get_empty( void )
//
//  :Implementation
//"
Mutex::PlatformStruct  Mutex::platformstruct_get_empty( void )
{
    PlatformStruct    platformStruct;
    memset( &platformStruct, 0, sizeof(platformStruct) );
    return (platformStruct);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   win_process_create( void )
//
//  :Description
//      This function is used to create a Win32 critical section.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Mutex::win_process_create( void )
    {
        bool fResult = false;
        try
        {
            InitializeCriticalSection( &m_Platform.m_CriticalSection );
            fResult = true;
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::win_process_create() ==> Caught Exception during call to InitializeCriticalSection()." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   win_process_lock( WaitMode, WaitTime )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Mutex::win_process_lock( WaitMode waitMode, WaitTime waitTime )
    {
        bool fResult = false;
        try
        {
            if ( waitMode == WaitMode_TIMED )
            {
                DWORD   waitMilli   = static_cast< DWORD >( waitTime );
                time_t  waitSeconds = static_cast< time_t >( (waitTime / 1000)+1 );
                DWORD   endMilli    = ::GetTickCount() + waitMilli;
                time_t  endSeconds  = time(NULL) + waitSeconds;

                fResult = ( TryEnterCriticalSection( &m_Platform.m_CriticalSection ) != FALSE );
                while ( fResult == false )
                {
                    DelayMilliseconds( CritSectionWaitDelayMS );
                    fResult = ( TryEnterCriticalSection( &m_Platform.m_CriticalSection ) != FALSE );
                    if ( fResult == false )
                    {
                        if ( (::GetTickCount() >= endMilli)     ||
                             (time(NULL) >= endSeconds)         )
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                EnterCriticalSection( &m_Platform.m_CriticalSection );
                fResult = true;
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::win_process_lock() ==> Caught Exception during call to EnterCriticalSection()." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   win_process_release( void )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Mutex::win_process_release( void )
    {
        bool fResult = false;
        try
        {
            LeaveCriticalSection( &m_Platform.m_CriticalSection );
            fResult = true;
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::win_process_release() ==> Caught Exception during call to LeaveCriticalSection()." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   win_process_destroy( void )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Mutex::win_process_destroy( void )
    {
        bool fResult = false;
        try
        {
            DeleteCriticalSection( &m_Platform.m_CriticalSection );
            fResult = true;
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::win_process_destroy() ==> Caught Exception during call to DeleteCriticalSection()." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  win_system_create( void )
//
//  :Arguments
//      = const char *  pszName
//          The name to supply to the OS ::CreateMutex() API call.  If this
//          is NULL (which is really the recomended way to do it) then a
//          unique name is generated for this instance of Mutex.
//
//  :Returns
//      If the mutex is succesfully created the function returns true.
//      Otherwise the Mutex object is invalid and the function returns
//      false.
//
//  :Description
//      This function is used to create the underlying mutex in the Win32
//      implementation of this class.  This function should only be called
//      once from the constructor of the Mutex object.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Mutex::win_system_create( void )
    {
        m_Platform.m_hMutex = ::CreateMutexA( m_ObjectIdent.get_ptr_security_attributes(),
                                              FALSE,
                                              m_ObjectIdent.system_name() );
        if (m_Platform.m_hMutex == NULL )
        {
            OM_SYSTEM_ERROR( "Mutex::win_system_create() == Call to ::CreateMutex() failed.", ::GetLastError() );
            return (false);
        }

        return (true);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   win_system_lock( WaitMode, WaitTime )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Mutex::win_system_lock( WaitMode waitMode, WaitTime waitTime )
    {
        bool fResult = false;
        DWORD theWaitTime = waitTime;
        if (waitMode == WaitMode_FOREVER)
        {
            theWaitTime =INFINITE;
        }
        DWORD   dWaitResult = ::WaitForSingleObject( m_Platform.m_hMutex, theWaitTime );
        if ( (dWaitResult == WAIT_ABANDONED) || (dWaitResult == WAIT_OBJECT_0) )
        {
            fResult = true;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   win_system_release( void )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Mutex::win_system_release( void )
    {
        BOOL fReleaseResult = ::ReleaseMutex( m_Platform.m_hMutex );
        bool fResult = (fReleaseResult != FALSE);
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  win_system_destroy( void )
//
//  :Returns
//      If the mutex was succesfully destroyed the function returns true.
//      Otherwise it returns false.
//
//  :Description
//      This member function is called to destroy the underlying mutex.
//      This function should only be called from the destructor.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Mutex::win_system_destroy( void )
    {
        BOOL fResult = ::CloseHandle( m_Platform.m_hMutex );
        m_Platform.m_hMutex = NULL;
        return (fResult != FALSE);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   linux_process_create( void )
//
//  :Description
//      This function is used to create a Win32 critical section.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Mutex::linux_process_create( void )
    {
        bool fResult = false;
        try
        {
            if ( pthread_mutex_init( &(m_Platform.m_ProcessMutex),
                                     m_ObjectIdent.get_ptr_mutexattr() ) != 0 )
            {
                OM_TRACE( OM_ETD_ERROR, "Mutex::linux_process_create() ==> Call to pthread_mutex_init() failed." );
                m_Platform.m_fCreateMutex = false;
            }
            else
            {
                m_Platform.m_fCreateMutex = true;
                fResult = true;
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_process_create() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   linux_process_lock( WaitMode, WaitTime )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Mutex::linux_process_lock( WaitMode waitMode, WaitTime waitTime )
    {
        bool fResult = false;
        try
        {
            if ( waitMode == WaitMode_TIMED )
            {
                struct timespec     absTimeout;
                m_ObjectIdent.get_abs_timeout( absTimeout, waitTime );

                //Uint32  fullMilliseconds    = static_cast< Uint32 >( waitTime );
                //Uint32  numSeconds          = fullMilliseconds / 1000;
                //Uint32  remainMilli         = fullMilliseconds - (numSeconds * 1000);
                //Uint32  remainNano          = remainMilli * 1000000;
                //Uint32  nanoInSecond        = 1000000000;
                //if ( remainNano >= nanoInSecond )
                //{
                //    numSeconds++;
                //    remainNano = remainNano - nanoInSecond;
                //}
                //struct timespec     absTimeout;
                //clock_gettime( CLOCK_REALTIME, &absTimeout );

                ////struct timespec
                ////  {
                ////    __time_t tv_sec;        /* Seconds.  */
                ////    long int tv_nsec;       /* Nanoseconds.  */
                ////  };
                //absTimeout.tv_sec  += numSeconds;
                //absTimeout.tv_nsec += remainNano;

                if ( pthread_mutex_timedlock( &(m_Platform.m_ProcessMutex),
                                              &absTimeout ) == 0 )
                {
                    fResult = true;
                }
                else
                {
                    fResult = false;
                }

                // Crappy old fake polling method!
                //unsigned long   waitLimit   = static_cast< unsigned long >( waitTime / PThreadWaitDelayMS );
                //unsigned long   waitCount   = 0;
                //while ( fResult == false )
                //{
                //    if ( pthread_mutex_trylock( &(m_Platform.m_ProcessMutex) ) == 0 )
                //    {
                //        fResult = true;
                //    }
                //    else if ( waitCount > waitLimit )
                //    {
                //        fResult = false;
                //        break;
                //    }
                //    else
                //    {
                //        DelayMilliseconds( PThreadWaitDelayMS );
                //        waitCount++;
                //    }
                //}
            }
            else
            {
                if ( pthread_mutex_lock( &(m_Platform.m_ProcessMutex) ) != 0 )
                {
                    fResult = false;
                }
                else
                {
                    fResult = true;
                }
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_process_lock() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   linux_process_release( void )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Mutex::linux_process_release( void )
    {
        bool fResult = false;
        try
        {
            if ( pthread_mutex_unlock( &(m_Platform.m_ProcessMutex) ) != 0 )
            {
                fResult = false;
            }
            else
            {
                fResult = true;
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_process_release() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   linux_process_destroy( void )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Mutex::linux_process_destroy( void )
    {
        bool fResult = false;
        try
        {
            if ( m_Platform.m_fCreateMutex == true )
            {
                if ( pthread_mutex_destroy( &(m_Platform.m_ProcessMutex) ) != 0 )
                {
                    OM_TRACE( OM_ETD_ERROR, "Mutex::linux_process_destroy() ==> Call to pthread_mutex_destroy() failed." );
                    fResult = false;
                }
                else
                {
                    fResult = true;
                }
            }
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_process_destroy() ==> Caught Exception." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   linux_system_create( void )
//
//  :Description
//      This function is used to create a Win32 critical section.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Mutex::linux_system_create( void )
    {
        bool fResult = false;
        try
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_system_create() ==> Not Implemented Yet!" );
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_process_create() ==> Caught Exception during sem_t creation." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   linux_system_lock( WaitMode, WaitTime )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Mutex::linux_system_lock( WaitMode /*waitMode*/, WaitTime /*waitTime*/ )
    {
        bool fResult = false;
        try
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_system_lock() ==> Not Implemented Yet!" );
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_system_lock() ==> Caught Exception while attempting to lock sem_t." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   linux_system_release( void )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Mutex::linux_system_release( void )
    {
        bool fResult = false;
        try
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_system_release() ==> Not Implemented Yet!" );
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_system_release() ==> Caught Exception while attempting to release sem_t." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   linux_system_destroy( void )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    bool  Mutex::linux_system_destroy( void )
    {
        bool fResult = false;
        try
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_system_destroy() ==> Not Implemented Yet!" );
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "Mutex::linux_system_destroy() ==> Caught Exception during call to pthread_mutex_destroy()." );
            fResult = false;
        }
        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


};  // namespace Tasking


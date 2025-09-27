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
//      CExtend\Libraries\CExThreading\CExThreading_Thread.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> Thread
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! Thread( const char * pszName = NULL, bool fReportState = false )
//
//  :Implementation
//"
Thread::Thread( const char * pszName /*= NULL*/, bool fReportState /*= false*/, bool fRegisterSignalHandle /*= true*/ )
    :   m_fRegisterSignalHandle( fRegisterSignalHandle != false )
{
    AutoLock   localMutexZone( m_Mutex );

    // Get a "non-const" reference to the CommonMemberStruct
    //  This is the only time we ever do this.  We handle it here
    //  rather than in the member-init list so we can verify
    //  (and in turn fixup) any of the supplied args
    ObjectIdent &   objectIdent     = const_cast< ObjectIdent & >( m_ObjectIdent );
    objectIdent.initialize( ObjectStyle_PROCESS,
                            ObjectType_THREAD,
                            pszName,
                            fReportState,
                            true );

    ThreadLaunch::threadinfostruct_clear( m_ThreadInfoStruct );
    m_CurrentState = State_OFF;
    m_StateChangeEvent.reset();

    // Register the thread with the signal handler
    if ( m_fRegisterSignalHandle != false )
    {
        SignalHandler::singleton().thread_add( this );
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~Thread( void )
//
//  :Description
//      This is the destructor for the thread class.  The thread must
//      be fully stopped before the destructor executes.
//
//      If the thread is still active then a program break is issued.  IF
//      execution is then resumed the destructor will explictly force
//      the stopping of the thread.
//
//  :Implementation
//"
Thread::~Thread( void )
{
    if (thread_is_on() == true)
    {
        OM_OUTPUT1( OM_ETD_ERROR, "Thread::~Thread(%s) ==> Thread is still on.", m_ObjectIdent.name() );
        OM_DEBUG_BREAK_NOTHROW();
        thread_stop();
    }

    AutoLock localMutexZone( m_Mutex );
    OM_DEBUG_ASSERT_NOTHROW( m_CurrentState == State_OFF );
    m_CurrentState = State_ERROR;
    m_StateChangeEvent.reset();

    // UnRegister the thread with the signal handler
    if ( m_fRegisterSignalHandle != false )
    {
        SignalHandler::singleton().thread_remove( this );
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ObjectIdent  get_object_ident( void ) const
//
//  :Returns
//      This function returns the ObjectIdent structure associated with
//      the current Thread object.
//
//  :Implementation
//"
ObjectIdent  Thread::get_object_ident( void ) const
{
    AutoLock localMutexZone( m_Mutex );
    ObjectIdent     resultVal = m_ObjectIdent;
    return (resultVal);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! State  thread_state( void ) const
//
//  :Description
//      Returns the current state of the thread.
//
//  :Implementation
//"
Thread::State  Thread::thread_state( void ) const
{
    AutoLock localMutexZone( m_Mutex );
    OM_DEBUG_ASSERT( (m_CurrentState==State_OFF)              ||
                     (m_CurrentState==State_START_ISSUED)     ||
                     (m_CurrentState==State_START_CONFIRMED)  ||
                     (m_CurrentState==State_RUNNING)          ||
                     (m_CurrentState==State_STOPPING)         );
    return (m_CurrentState);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_is_off( void ) const
//
//  :Description
//      This function returns true if the thread is totally inactive.
//      (State == State_OFF)
//
//  :Implementation
//"
bool  Thread::thread_is_off( void ) const
{
    AutoLock localMutexZone( m_Mutex );
    OM_DEBUG_ASSERT( (m_CurrentState==State_OFF)              ||
                     (m_CurrentState==State_START_ISSUED)     ||
                     (m_CurrentState==State_START_CONFIRMED)  ||
                     (m_CurrentState==State_RUNNING)          ||
                     (m_CurrentState==State_STOPPING)         );
    return (m_CurrentState == State_OFF);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_is_on( void ) const
//
//  :Description
//      This function returns true if the thread is totally inactive.
//      (State == State_STARTING or State_ON or State_STOPPING)
//
//  :Implementation
//"
bool  Thread::thread_is_on( void ) const
{
    AutoLock localMutexZone( m_Mutex );
    OM_DEBUG_ASSERT( (m_CurrentState==State_OFF)              ||
                     (m_CurrentState==State_START_ISSUED)     ||
                     (m_CurrentState==State_START_CONFIRMED)  ||
                     (m_CurrentState==State_RUNNING)          ||
                     (m_CurrentState==State_STOPPING)         );
    bool fResult = ( (m_CurrentState==State_START_ISSUED)       ||
                     (m_CurrentState==State_START_CONFIRMED)    ||
                     (m_CurrentState==State_RUNNING)            ||
                     (m_CurrentState==State_STOPPING)           );
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_is_stop_triggered( void ) const
//
//  :Description
//      This function returns true if the thread is in the
//      State_STOPPING state.
//
//  :Implementation
//"
bool  Thread::thread_is_stop_triggered( void ) const
{
    AutoLock localMutexZone( m_Mutex );
    OM_DEBUG_ASSERT( (m_CurrentState==State_OFF)              ||
                     (m_CurrentState==State_START_ISSUED)     ||
                     (m_CurrentState==State_START_CONFIRMED)  ||
                     (m_CurrentState==State_RUNNING)          ||
                     (m_CurrentState==State_STOPPING)         );
    return ( m_CurrentState == State_STOPPING );
}
//.



/////////////////////////////////////////////////////////////////////////////
//! bool  thread_start( void )
//
//  :Description
//      This member function starts the execution of the thread.
//
//      It will first verify its state and then attempt to start the
//      actual thread using the appropriate OS primitives.  Once started
//      it waits for the thread_is_active() function to return true
//      indicating the thread is up and running.
//
//  :Implementation
//"
bool Thread::thread_start( void )
{
    bool fResult = true;
    // We use try catch blocks for their obvious protection
    //  and to allow us to use the AutoLock mechanism to lock
    //  the mutex.
    try
    {
        AutoLock    localMutexZone( m_Mutex );

        // Check to make sure thread is not already exist
        OM_DEBUG_ASSERT( (m_CurrentState==State_OFF)              ||
                        (m_CurrentState==State_START_ISSUED)     ||
                        (m_CurrentState==State_START_CONFIRMED)  ||
                        (m_CurrentState==State_RUNNING)          ||
                        (m_CurrentState==State_STOPPING)         );
        if ( m_CurrentState != State_OFF )
        {
            OM_TRACE2( OM_ETD_ERROR, "Thread::thread_start(%s) ==> Invalid state (%s), doing nothing!",
                                     m_ObjectIdent.name(),
                                     state_as_string(m_CurrentState) );
            return (false);
        }

        // Set to the "starting" state.
        thread_change_state( State_START_ISSUED, "thread_start" );

        // Start The Thread
        size_t  stackSize = 0;
        ThreadLaunch::launch( thread_entry_point,
                              this,
                              stackSize,
                              m_ThreadInfoStruct );
    }
    catch ( ... )
    {
        OM_TRACE1( OM_ETD_ERROR, "Thread::thread_start(%s) ==> Caught Exception.", m_ObjectIdent.name() );
        fResult = false;
    }

    // We are now at a point where there mutex is unlocked.  We need to wait
    //  until the  state changes from START_ISSUED to START_CONFIRMED.
    while ( thread_state() == State_START_ISSUED )
    {
        thread_wait_state_change( MiniWaitTime );
    }

    // Relock the mutex and finish up
    try
    {
        AutoLock    localMutexZone( m_Mutex );

        // Mark as running and generate a message
        OM_DEBUG_ASSERT( m_CurrentState == State_START_CONFIRMED )
        if ( m_CurrentState != State_START_CONFIRMED )
        {
            OM_TRACE1( OM_ETD_ERROR, "Thread::thread_start(%s) ==> Failed to detect thread start confirmation.", m_ObjectIdent.name() );
        }
        else
        {
            thread_change_state( State_RUNNING, "thread_start" );
        }
    }
    catch ( ... )
    {
        OM_TRACE1( OM_ETD_ERROR, "Thread::thread_start(%s) ==> Caught Exception.", m_ObjectIdent.name() );
        fResult = false;
    }

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  thread_stop( void )
//
//  :Description
//      This member function issues a stop.  It then checks to see if the
//      thread is active.  If it isn't it sleeps for a short period of
//      time then checks again.  It does so untill the thread has stopped
//      execution.
//
//      This function does NOT force the thread to stop.
//
//  :Implementation
//"
void Thread::thread_stop( void )
{
    thread_trigger_stop();

    while (thread_is_on() == true)
    {
        thread_wait_state_change( MiniWaitTime );
    }

    //AutoLock localMutexZone( m_Mutex );
    //OM_DEBUG_ASSERT( m_CurrentState == State_OFF );

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_kill( void )
//
//  :Description
//      This member function outright kills the thread.
//
//      This function FORCES the thread to stop.  It is only to be used
//      as a last resort as the thread process was not allowed to properly
//      exit and deallocate resources.
//
//  :Implementation
//"
bool Thread::thread_kill( void )
{
    bool fResult = false;
    try
    {
        AutoLock    localMutexZone( m_Mutex );

        if ( thread_is_off() == true )
        {
            // Do nothing
        }
        else
        {
            if ( ThreadLaunch::kill( m_ThreadInfoStruct ) != false )
            {
                thread_change_state( State_OFF, "thread_kill" );
                fResult = true;
            }
        }
    }
    catch ( ... )
    {
        OM_TRACE1( OM_ETD_ERROR, "Thread::thread_kill(%s) ==> Caught Exception.", m_ObjectIdent.name() );
        fResult = false;
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  thread_trigger_stop( void )
//
//  :Description
//      If the thread is started (or active) this function will set the
//      stop flag to true.
//
//  :Implementation
//"
void Thread::thread_trigger_stop( void )
{
    AutoLock localMutexZone( m_Mutex );

    OM_DEBUG_ASSERT( (m_CurrentState==State_OFF)              ||
                     (m_CurrentState==State_START_ISSUED)     ||
                     (m_CurrentState==State_START_CONFIRMED)  ||
                     (m_CurrentState==State_RUNNING)          ||
                     (m_CurrentState==State_STOPPING)         );
    if ( m_CurrentState == State_OFF )
    {
        // OM_TRACE2( OM_ETD_ERROR, "Thread::thread_trigger_stop(%s) ==> Invalid state (%s), doing nothing!", m_Name.c_str(), thread_state_as_string(m_State) );
    }
    else
    {
        thread_change_state( State_STOPPING, "thread_trigger_stop" );
    }

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  const char *  state_as_string( State )
//
//  :Description
//      Returns the provided state as a string.
//
//  :Implementation
//"
const char *  Thread::state_as_string( State theState )
{
    switch ( theState )
    {
        case State_ERROR:           return "State_ERROR";
        case State_OFF:             return "State_OFF";
        case State_START_ISSUED:    return "State_START_ISSUED";
        case State_START_CONFIRMED: return "State_START_CONFIRMED";
        case State_RUNNING:         return "State_RUNNING";
        case State_STOPPING:        return "State_STOPPING";
        default:
            break;
    }
    return ("State_?????");
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_wait_stop_triggered( WaitTime waitTime ) const
//
//  :Description
//      This function will wait for the indicated number of milliseconds for
//      the stop to be triggered.
//
//  :Returns
//      If the object is in the State_STOPPING state then it returns
//      immediately and returns true.
//
//      If the object is in the State_START_ISSUED, State_START_CONFIRMED
//      or State_RUNNING states then the function will wait for a change
//      state event.  When it occurs the function will re-examine the
//      current state and if it is State_STOPPING then the function
//      returns true.
//
//      In any other situation the function returns false.
//
//  :Implementation
//"
bool  Thread::thread_wait_stop_triggered( WaitTime waitTime ) const
{
    switch ( thread_state() )
    {
        case State_START_ISSUED:
        case State_START_CONFIRMED:
        case State_RUNNING:
            thread_wait_state_change(waitTime);
            break;
        default:
            break;
    }

    return ( thread_is_stop_triggered() );
}
//.



/////////////////////////////////////////////////////////////////////////////
//! static void  thread_entry_point( void * )
//
//  :Description
//      This is the function that is called by the OS to start the thread.
//      We use it to pull out the Thread pointer from the void pointer
//      and call the member function thread_start_function() to handle
//      the work of acknowledging the new thread.
//
//  :Implementation
//"
void  Thread::thread_entry_point( void * pData )
{
    OM_DEBUG_ASSERT( pData != NULL );
    Thread * pThread = (Thread *)pData;
    pThread->thread_start_function();

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  thread_start_function( void )
//
//  :Description
//      This function acknowledges the start of the thread then calls
//      the pure virtual function thread_function() to actually run
//      the thread.
//
//  :Implementation
//"
void Thread::thread_start_function( void )
{
    // Acknowledge the start of the thread
    thread_acknowledge();

    // Wait for the acknowledge flag before returning from function
    while ( thread_state() == State_START_CONFIRMED )
    {
        thread_wait_state_change( MiniWaitTime );
    }

    // Call the virtual function which implements
    //  the "thread" code.
    try
    {
        thread_function();
    }
    catch ( const CExOutput::Exception & outMgrException )
    {
        const char * pszSourceFile  = outMgrException.source_file();
        const char * pszMessageA    = outMgrException.message_a();
        const char * pszMessageB    = outMgrException.message_b();

        OM_OUTPUT5( OM_ETD_ERROR, "Thread::thread_start_function(%s) ==> CExOutput::Exception Caught From -- %s[%u] - %s - %s",
                m_ObjectIdent.name(),
                ((pszSourceFile==NULL)?"":pszSourceFile),
                static_cast<unsigned int>(outMgrException.source_line()),
                ((pszMessageA==NULL)?"":pszMessageA),
                ((pszMessageB==NULL)?"":pszMessageB) );
    }
    catch ( ... )
    {
        OM_TRACE1( OM_ETD_ERROR, "Thread::thread_start_function(%s) ==> Unknown Exception caught during execution of thread", m_ObjectIdent.name() );
    }

    // Signal exit of thread
    thread_change_state( State_OFF, "thread_start_function" );

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  thread_acknowledge( void )
//
//  :Description
//      This member function is used by the thread_start_function() to
//      mark the thread as active.
//
//  :Implementation
//"
void  Thread::thread_acknowledge( void )
{
    AutoLock localMutexZone( m_Mutex );

    OM_DEBUG_ASSERT( (m_CurrentState==State_OFF)              ||
                     (m_CurrentState==State_START_ISSUED)     ||
                     (m_CurrentState==State_START_CONFIRMED)  ||
                     (m_CurrentState==State_RUNNING)          ||
                     (m_CurrentState==State_STOPPING)         );

    if ( m_CurrentState == State_START_ISSUED )
    {
        // This is exactly what we are looking for!
        thread_change_state( State_START_CONFIRMED, "thread_acknowledge" );
    }
    else
    {
        OM_TRACE2( OM_ETD_ERROR, "Thread::thread_acknowledge(%s) ==> Invalid state (%s), doing nothing!",
                                 m_ObjectIdent.name(),
                                 state_as_string(m_CurrentState) );
    }

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  thread_change_state( State )
//
//  :Description
//      This function will change the current state of the object
//      to the indicated state.  The function will also set the
//      state change event if the state has actually changed.
//
//  :Implementation
//"
void  Thread::thread_change_state( State newState, const char * /*funcName*/ )
{
    AutoLock localMutexZone( m_Mutex );

    OM_DEBUG_ASSERT( (newState==State_OFF)                ||
                     (newState==State_START_ISSUED)       ||
                     (newState==State_START_CONFIRMED)    ||
                     (newState==State_RUNNING)            ||
                     (newState==State_STOPPING)           );

    State oldState = m_CurrentState;
    if ( oldState != newState )
    {
        m_CurrentState = newState;
        if ( m_ObjectIdent.report_state_flag() == true )
        {
            //OM_OUTPUT5( OM_ETD_INFO,
            //            "Thread::%s(%s,%s) ==> STATE CHANGE ==>  From:%s  ==>  To:%s",
            //            funcName,
            //            m_ObjectIdent.name(),
            //            ThreadLaunch::get_current_threadid_string().c_str(),
            //            state_as_string(oldState),
            //            state_as_string(newState) );
            OM_OUTPUT4( OM_ETD_INFO,
                        "Thread ==> %s:%s ==>  From:%s  ==>  To:%s",
                        m_ObjectIdent.name(),
                        ThreadLaunch::get_current_threadid_string().c_str(),
                        state_as_string(oldState),
                        state_as_string(newState) );
        }
        m_StateChangeEvent.set();
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  thread_wait_state_change( WaitTime ) const
//
//  :Description
//      This function will wait the indicated number of milliseconds
//      for the state change event to be set.  If the
//      function detects that the event has been set then it
//      resets the event and returns.  If the wait period expires and
//      the event has not been set then the function simply returns.
//
//  :Implementation
//"
void  Thread::thread_wait_state_change( WaitTime waitTime ) const
{
    if ( m_StateChangeEvent.wait( CExThreading::WaitMode_TIMED, waitTime ) == true )
    {
        m_StateChangeEvent.reset();
    }
    return;
}
//.

};  // namespace CExThreading



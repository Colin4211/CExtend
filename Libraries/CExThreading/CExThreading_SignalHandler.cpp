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
//      CExtend\Libraries\CExThreading\CExThreading_SignalHandler.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> SignalHandler
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"


namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! SignalHandler( void )
//
//  :Implementation
//"
SignalHandler::SignalHandler( void )
    :   m_Mutex( ObjectStyle_PROCESS, "CExThreading::SignalHandler", false )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    m_ThreadPtrSet.clear();
    initialize();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~SignalHandler( void )
//
//  :Implementation
//"
SignalHandler::~SignalHandler( void )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    disable();
    clear();
    m_ThreadPtrSet.clear();

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  SignalHandler &  singleton( void )
//
//  :Implementation
//"
SignalHandler &  SignalHandler::singleton( void )
{
    static SignalHandler    theOneAndOnly;
    return (theOneAndOnly);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  clear( void )
//
//  :Implementation
//"
void  SignalHandler::clear( void )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    disable();

    m_SignalMap             .clear();
    m_fStopped              = false;
    m_fEnabled              = false;

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  initialize( void )
//
//  :Implementation
//"
void  SignalHandler::initialize( void )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    clear();

    // Set the default signal struct
    //  (signal code of zero)
    SignalStruct    signalStruct;
    signalStruct.m_Counter              = 0;
    signalStruct.m_OptionStruct         = get_global_default_option_struct();
    signalStruct.m_PfnSignalCallbackMap .clear();
    m_SignalMap.insert( SignalMap::value_type( 0, signalStruct ) );

    signal_set( SIGABRT  );  // Abnormal termination
    signal_set( SIGILL   );  // Illegal instruction
    signal_set( SIGINT   );  // CTRL+C signal
    signal_set( SIGSEGV  );  // Illegal storage access
    signal_set( SIGTERM  );  // Termination request

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  empty( void ) const
//
//  :Implementation
//"
bool  SignalHandler::empty( void ) const
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    bool fEmpty = (m_SignalMap.empty() == true);
    return (fEmpty);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  enable( void )
//
//  :Implementation
//"
bool  SignalHandler::enable( void )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    if ( empty() == true )
    {
        return (false);
    }

    for ( SignalMap::iterator iterWalk = m_SignalMap.begin();
          iterWalk != m_SignalMap.end();
          iterWalk++ )
    {
        const int &     sigCode         = iterWalk->first;
        if ( sigCode > 0 )
        {
            #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
                signal( sigCode, signal_callback_mswin );
            #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
                signal( sigCode, signal_callback_linux );
            #else
                #error "ERROR: This code is platform specific"
            #endif
        }
    }

    m_fEnabled = true;

    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  disable( void )
//
//  :Implementation
//"
bool  SignalHandler::disable( void )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    if ( empty() == true )
    {
        return (false);
    }

    for ( SignalMap::iterator iterWalk = m_SignalMap.begin();
          iterWalk != m_SignalMap.end();
          iterWalk++ )
    {
        const int & sigCode = iterWalk->first;
        if ( sigCode > 0 )
        {
            signal( sigCode, NULL );
        }
    }

    m_fEnabled = false;

    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_enabled( void ) const
//
//  :Implementation
//"
bool  SignalHandler::is_enabled( void ) const
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    bool fResult = m_fEnabled;
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  signal_set( int sigCode )
//
//  :Implementation
//"
bool  SignalHandler::signal_set( int sigCode )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    OptionStruct optionStruct = get_signal_default_option_struct();
    return (signal_set(sigCode,optionStruct));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool signal_set( int sigCode, const OptionStruct & optionStruct )
//
//  :Implementation
//"
bool  SignalHandler::signal_set( int sigCode, const OptionStruct & optionStruct )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    if ( empty() == true )
    {
        return (false);
    }
    if ( sigCode < 0 )
    {
        return (false);
    }


    OptionStruct    newOptionStruct = optionStruct;
    if ( sigCode > 0 )
    {
        if ( (newOptionStruct.m_AutoResetSignal != OptValue_DEFAULT)    &&
             (newOptionStruct.m_AutoResetSignal != OptValue_ON)         &&
             (newOptionStruct.m_AutoResetSignal != OptValue_OFF)        )
        {
            newOptionStruct.m_AutoResetSignal = OptValue_DEFAULT;
        }
        if ( (newOptionStruct.m_TriggerThreadStop != OptValue_DEFAULT)    &&
             (newOptionStruct.m_TriggerThreadStop != OptValue_ON)         &&
             (newOptionStruct.m_TriggerThreadStop != OptValue_OFF)        )
        {
            newOptionStruct.m_TriggerThreadStop = OptValue_DEFAULT;
        }
        if ( (newOptionStruct.m_AutoResetSignal != OptValue_DEFAULT)    &&
             (newOptionStruct.m_AutoResetSignal != OptValue_ON)         &&
             (newOptionStruct.m_AutoResetSignal != OptValue_OFF)        )
        {
            newOptionStruct.m_AutoResetSignal = OptValue_DEFAULT;
        }
    }

    SignalMap::iterator iterFind = m_SignalMap.find( sigCode );
    if ( iterFind == m_SignalMap.end() )
    {
        OM_DEBUG_ASSERT( sigCode != 0 );
        SignalStruct    newSignalStruct;
        newSignalStruct.m_Counter               = 0;
        newSignalStruct.m_PfnSignalCallbackMap  .clear();
        newSignalStruct.m_OptionStruct          = newOptionStruct;
        m_SignalMap.insert( SignalMap::value_type( sigCode, newSignalStruct ) );
    }
    else
    {
        OptionStruct & curOptionStruct = iterFind->second.m_OptionStruct;
        if ( sigCode == 0 )
        {
            curOptionStruct = get_final_option_struct( newOptionStruct, curOptionStruct );
        }
        else
        {
            curOptionStruct = newOptionStruct;
        }
    }

    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool    signal_remove( int sigCode )
//
//  :Implementation
//"
bool  SignalHandler::signal_remove( int sigCode )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    if ( empty() == true )
    {
        return (false);
    }

    SignalMap::iterator iterFind = m_SignalMap.find( sigCode );
    if ( iterFind == m_SignalMap.end() )
    {
        return (false);
    }
    m_SignalMap.erase( iterFind );
    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_add( Thread & theThread )
//
//  :Implementation
//"
bool  SignalHandler::thread_add( Thread & theThread )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    return (thread_add(&theThread));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_add( Thread * ptrThread )
//
//  :Implementation
//"
bool  SignalHandler::thread_add( Thread * ptrThread )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    if ( ptrThread == NULL )
    {
        return (false);
    }
    m_ThreadPtrSet.insert( ptrThread );
    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_remove( Thread & theThread )
//
//  :Implementation
//"
bool  SignalHandler::thread_remove( Thread & theThread )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    return (thread_remove(&theThread));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  thread_remove( Thread * ptrThread )
//
//  :Implementation
//"
bool  SignalHandler::thread_remove( Thread * ptrThread )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    ThreadPtrSet::iterator iterFind = m_ThreadPtrSet.find( ptrThread );
    if ( iterFind == m_ThreadPtrSet.end() )
    {
        return (false);
    }
    m_ThreadPtrSet.erase( iterFind );
    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  callback_add( int sigCode, PfnSignalCallback pfnSignalCallback, void * ptrDataEx )
//
//  :Implementation
//"
bool  SignalHandler::callback_add( int sigCode, PfnSignalCallback pfnSignalCallback, void * ptrDataEx )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    if ( empty() == true )
    {
        return (false);
    }
    if ( sigCode < 0 )
    {
        return (false);
    }
    if ( pfnSignalCallback == NULL )
    {
        return (false);
    }

    SignalMap::iterator iterFind = m_SignalMap.find( sigCode );
    if ( iterFind == m_SignalMap.end() )
    {
        return (false);
    }

    SignalStruct & signalStruct = iterFind->second;
    signalStruct.m_PfnSignalCallbackMap.insert( PfnSignalCallbackMap::value_type( pfnSignalCallback, ptrDataEx ) );

    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  callback_remove( int sigCode, PfnSignalCallback pfnSignalCallback )
//
//  :Implementation
//"
bool  SignalHandler::callback_remove( int sigCode, PfnSignalCallback pfnSignalCallback )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    if ( empty() == true )
    {
        return (false);
    }
    if ( sigCode < 0 )
    {
        return (false);
    }
    if ( pfnSignalCallback == NULL )
    {
        return (false);
    }

    SignalMap::iterator iterFind = m_SignalMap.find( sigCode );
    if ( iterFind == m_SignalMap.end() )
    {
        return (false);
    }

    SignalStruct & signalStruct = iterFind->second;
    signalStruct.m_PfnSignalCallbackMap.erase( pfnSignalCallback );

    return (true);

    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const bool &  stop_trigger( void ) const
//
//  :Implementation
//"
const bool &  SignalHandler::stop_trigger( void ) const
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    return (m_fStopped);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  get_signals( IntSet & sigCodeSet ) const
//
//  :Implementation
//"
bool  SignalHandler::get_signals( IntSet & sigCodeSet ) const
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    sigCodeSet.clear();
    if ( empty() == true )
    {
        return (false);
    }

    for ( SignalMap::const_iterator iterWalk = m_SignalMap.begin();
          iterWalk != m_SignalMap.end();
          iterWalk++ )
    {
        const int & sigCode = iterWalk->first;
        if ( sigCode != 0 )
        {
            sigCodeSet.insert( sigCode );
        }
    }

    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  get_active_signals( IntSet & sigCodeSet ) const
//
//  :Implementation
//"
bool  SignalHandler::get_active_signals( IntSet & sigCodeSet ) const
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    sigCodeSet.clear();
    if ( empty() == true )
    {
        return (false);
    }

    for ( SignalMap::const_iterator iterWalk = m_SignalMap.begin();
          iterWalk != m_SignalMap.end();
          iterWalk++ )
    {
        const int &             sigCode         = iterWalk->first;
        const SignalStruct &    signalStruct    = iterWalk->second;
        if ( sigCode == 0 )
        {
            continue;
        }
        if ( signalStruct.m_Counter > 0 )
        {
            sigCodeSet.insert( sigCode );
        }
    }

    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  get_signal_count( int sigCode, Uint32 & signalCount ) const
//
//  :Implementation
//"
bool  SignalHandler::get_signal_count( int sigCode, Uint32 & signalCount ) const
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    signalCount = 0;
    if ( empty() == true )
    {
        return (false);
    }

    SignalMap::const_iterator iterFind = m_SignalMap.find( sigCode );
    if ( iterFind == m_SignalMap.end() )
    {
        return (false);
    }

    const SignalStruct & signalStruct = iterFind->second;
    signalCount = signalStruct.m_Counter;
    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  get_signal_options( int sigCode, OptionStruct & optionStruct ) const
//
//  :Implementation
//"
bool  SignalHandler::get_signal_options( int sigCode, OptionStruct & optionStruct ) const
{
    CExThreading::AutoLock localMutexZone( m_Mutex );
    optionStruct = get_global_default_option_struct();
    if ( empty() == true )
    {
        return (false);
    }

    SignalMap::const_iterator iterFind = m_SignalMap.find( sigCode );
    if ( iterFind == m_SignalMap.end() )
    {
        return (false);
    }

    const SignalStruct & signalStruct = iterFind->second;
    optionStruct = signalStruct.m_OptionStruct;
    return (true);
}
//.



#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    /////////////////////////////////////////////////////////////////////////////
    //! static  void  __cdecl  signal_callback_mswin( int sigCode );
    //
    //  :Implementation
    //"
    void  SignalHandler::signal_callback_mswin( int sigCode )
    {
        singleton().signal_handler( sigCode );
        return;
    }
    //.

#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    /////////////////////////////////////////////////////////////////////////////
    //! static  void  __cdecl  signal_callback_linux( int sigCode );
    //
    //  :Implementation
    //"
    void  SignalHandler::signal_callback_linux( int sigCode )
    {
        singleton().signal_handler( sigCode );
        return;
    }
    //.

#else
    #error "ERROR: This code is platform specific"
#endif


/////////////////////////////////////////////////////////////////////////////
//! void  signal_handler( int )
//
//  :Notes
//      Be very careful in this function.  Depending on the platform
//      there are limitation as to what system functions can be called
//      from this function.
//
//  :Implementation
//"
void  SignalHandler::signal_handler( int sigCode )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    if ( empty() == true )
    {
        OM_TRACE1( OM_ETD_ERROR, "SignalHandler::signal_handler(%d) ==> object not initialized", sigCode );
        return;
    }
    if ( m_fEnabled == false )
    {
        OM_TRACE1( OM_ETD_ERROR, "SignalHandler::signal_handler(%d) ==> Handlers not enabled", sigCode );
        return;
    }

    // This should never happen!
    if ( sigCode <= 0 )
    {
        OM_TRACE1( OM_ETD_ERROR, "SignalHandler::signal_handler(%d) ==> Invalid signal code", sigCode );
        return;
    }

    // Find the global and signal specific signal structs
    try
    {
        SignalStruct *  ptrGlobalSignalStruct   = NULL;
        SignalStruct *  ptrSignalStruct         = NULL;

        SignalMap::iterator iterGlobal  = m_SignalMap.find( 0 );
        if ( iterGlobal != m_SignalMap.end() )
        {
            SignalStruct & signalStruct = iterGlobal->second;
            ptrGlobalSignalStruct = &signalStruct;
        }

        SignalMap::iterator iterLocal   = m_SignalMap.find( sigCode );
        if ( iterLocal != m_SignalMap.end() )
        {
            SignalStruct & signalStruct = iterLocal->second;
            ptrSignalStruct = &signalStruct;
        }

        if ( ptrGlobalSignalStruct == NULL )
        {
            OM_TRACE1( OM_ETD_ERROR, "SignalHandler::signal_handler(%d) ==> Failed to locate global signal options", sigCode );
        }
        else if ( ptrSignalStruct == NULL )
        {
            OM_TRACE1( OM_ETD_ERROR, "SignalHandler::signal_handler(%d) ==> Failed to locate signal options", sigCode );
        }
        else
        {
            signal_processor( sigCode, *ptrGlobalSignalStruct, *ptrSignalStruct );
        }
    }
    catch ( ... )
    {
        // Dont issue an error for this exception because
        //  we are already in a signal interupt handler
        OM_TRACE1( OM_ETD_ERROR, "SignalHandler::signal_handler(%d) ==> Caught exception while handling signal", sigCode );
    }

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  signal_processor( int sigCode, SignalStruct & globalSignalStruct, SignalStruct & curSignalStruct )
//
//  :Notes
//      Be very careful in this function.  Depending on the platform
//      there are limitation as to what system functions can be called
//      from this function.
//
//  :Implementation
//"
void  SignalHandler::signal_processor( int sigCode, SignalStruct & globalSignalStruct, SignalStruct & curSignalStruct )
{
    CExThreading::AutoLock localMutexZone( m_Mutex );

    try
    {
        OptionStruct    theOptionStruct = get_final_option_struct( curSignalStruct.m_OptionStruct, globalSignalStruct.m_OptionStruct );

        // Increment Counts
        if ( globalSignalStruct.m_Counter < Uint32_MAX )
        {
            globalSignalStruct.m_Counter++;
        }
        if ( curSignalStruct.m_Counter < Uint32_MAX )
        {
            curSignalStruct.m_Counter++;
        }

        // Set the stop flag
        if ( theOptionStruct.m_SetStopFlag != OptValue_OFF )
        {
            m_fStopped = true;
        }

        // Trigger Stops
        if ( theOptionStruct.m_TriggerThreadStop != OptValue_OFF )
        {
            for ( ThreadPtrSet::iterator iterWalk = m_ThreadPtrSet.begin();
                  iterWalk != m_ThreadPtrSet.end();
                  iterWalk++ )
            {
                Thread * ptrThread = (*iterWalk);
                if ( ptrThread != NULL )
                {
                    ptrThread->thread_trigger_stop();
                }
            }
        }

        // Do the callbacks
        for ( int nMap = 1; nMap <= 2; nMap++ )
        {
            PfnSignalCallbackMap & callbackMap = ( (nMap==1) ? curSignalStruct.m_PfnSignalCallbackMap : globalSignalStruct.m_PfnSignalCallbackMap );
            for ( PfnSignalCallbackMap::iterator iterWalk = callbackMap.begin();
                  iterWalk != callbackMap.end();
                  iterWalk++ )
            {
                PfnSignalCallback       pfnSignalCallback   = iterWalk->first;
                void *                  ptrExData           = iterWalk->second;
                if ( pfnSignalCallback != NULL )
                {
                    (*pfnSignalCallback)( *this, ptrExData, sigCode );
                }
            }
        }

        // Only do this on Windows???
        if ( theOptionStruct.m_AutoResetSignal != OptValue_OFF )
        {
            #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
                signal( sigCode, signal_callback_mswin );
            #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
                signal( sigCode, signal_callback_linux );
            #else
                #error "ERROR: This code is platform specific"
            #endif
        }

        // Finally we check the kill flag
        bool fKill = false;
        if ( globalSignalStruct.m_OptionStruct.m_KillAfterThisManySignals != 0 )
        {
            if ( globalSignalStruct.m_Counter >= static_cast<Uint32>(globalSignalStruct.m_OptionStruct.m_KillAfterThisManySignals) )
            {
                fKill = true;
            }
        }
        if ( curSignalStruct.m_OptionStruct.m_KillAfterThisManySignals != 0 )
        {
            if ( curSignalStruct.m_Counter >= static_cast<Uint32>(curSignalStruct.m_OptionStruct.m_KillAfterThisManySignals) )
            {
                fKill = true;
            }
        }
        if ( fKill == true )
        {
            OM_TRACE1( OM_ETD_ERROR, "SignalHandler::signal_processor(%d) ==> Signal count exceeded, killing process", sigCode );
            KillProcess();
        }

    }
    catch ( ... )
    {
        // Dont issue an error for this exception because
        //  we are already in a signal interupt handler
        OM_TRACE1( OM_ETD_ERROR, "SignalHandler::signal_processor(%d) ==> Caught exception while handling signal", sigCode );
    }

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! OptionStruct  get_final_option_struct( OptionStruct & curOptions, OptionStruct & baseOptions )
//
//  :Implementation
//"
SignalHandler::OptionStruct  SignalHandler::get_final_option_struct( OptionStruct & curOptions, OptionStruct & baseOptions )
{
    OptionStruct    resultStruct = curOptions;
    if ( (resultStruct.m_AutoResetSignal != OptValue_ON)      &&
         (resultStruct.m_AutoResetSignal != OptValue_OFF)     )
    {
        resultStruct.m_AutoResetSignal = baseOptions.m_AutoResetSignal;
    }

    if ( (resultStruct.m_TriggerThreadStop != OptValue_ON)      &&
         (resultStruct.m_TriggerThreadStop != OptValue_OFF)     )
    {
        resultStruct.m_TriggerThreadStop = baseOptions.m_TriggerThreadStop;
    }

    if ( resultStruct.m_KillAfterThisManySignals == 0 )
    {
        resultStruct.m_KillAfterThisManySignals = baseOptions.m_KillAfterThisManySignals;
    }

    if ( (resultStruct.m_AutoResetSignal != OptValue_ON)      &&
         (resultStruct.m_AutoResetSignal != OptValue_OFF)     )
    {
        resultStruct.m_AutoResetSignal = baseOptions.m_AutoResetSignal;
    }

    return (resultStruct);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! OptionStruct  get_global_default_option_struct( void ) const
//
//  :Implementation
//"
SignalHandler::OptionStruct  SignalHandler::get_global_default_option_struct( void ) const
{
    OptionStruct    defaultStruct;

    defaultStruct.m_SetStopFlag                 = OptValue_ON;
    defaultStruct.m_TriggerThreadStop           = OptValue_ON;
    defaultStruct.m_KillAfterThisManySignals    = KillCountDefaultLimit;
    defaultStruct.m_AutoResetSignal             = OptValue_ON;

    return (defaultStruct);
}
//.



/////////////////////////////////////////////////////////////////////////////
//! OptionStruct  get_signal_default_option_struct( void ) const
//
//  :Implementation
//"
SignalHandler::OptionStruct  SignalHandler::get_signal_default_option_struct( void ) const
{
    OptionStruct    defaultStruct;

    defaultStruct.m_SetStopFlag                 = OptValue_DEFAULT;
    defaultStruct.m_TriggerThreadStop           = OptValue_DEFAULT;
    defaultStruct.m_KillAfterThisManySignals    = 0;
    defaultStruct.m_AutoResetSignal             = OptValue_DEFAULT;

    return (defaultStruct);
}
//.


}; // namespace CExThreading


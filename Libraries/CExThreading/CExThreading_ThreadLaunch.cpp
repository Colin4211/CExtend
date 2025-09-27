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
//      CExtend\Libraries\CExThreading\CExThreading_ThreadLaunch.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> ThreadLaunch
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! static  bool  launch( PfnThreadFunction, void * pData )
//
//  :Implementation
//"
bool  ThreadLaunch::launch( PfnThreadFunction pfnThreadFunction, void * pData )
{
    ThreadInfoStruct    threadInfoStruct;
    threadinfostruct_clear( threadInfoStruct );
    return (launch(pfnThreadFunction,pData,0,threadInfoStruct));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  bool    launch( PfnThreadFunction, void *, ThreadInfoStruct & )
//
//  :Description
//      This function is used to actually launch the thread.  The
//      function will launch a thread which calls the supplied function
//      with the supplied data pointer.
//
//      The ThreadInfoStruct is platform specific and contains any
//      information (like thread handles) that were obtained
//      during the launch of the thread.
//
//  :Implementation
//"
bool  ThreadLaunch::launch( PfnThreadFunction   pfnThreadFunction,
                            void *              pData,
                            size_t              stackSize,
                            ThreadInfoStruct &  threadInfoStruct )
{
    threadinfostruct_clear( threadInfoStruct );

    if ( pfnThreadFunction == NULL )
    {
        return (false);
    }

    LaunchDataStruct *   pLaunchData     = NULL;
    try
    {
        pLaunchData = new LaunchDataStruct;
    }
    catch ( ... )
    {
        OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::launch() ==> Caught Exception while creating LaunchDataStruct" );
    }

    bool fResult = false;
    try
    {
        if ( pLaunchData == NULL )
        {
            OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::launch() ==> Failed to allocate LaunchDataStruct.\n" );
        }
        else
        {
            pLaunchData->m_PfnActualFunction  = pfnThreadFunction;
            pLaunchData->m_pData              = pData;

            #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
                threadInfoStruct.m_hThread = ::CreateThread( NULL,                              //  LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                                             stackSize,                         //  SIZE_T dwStackSize,
                                                             win_thread_start,                  //  LPTHREAD_START_ROUTINE lpStartAddress,
                                                             pLaunchData,                       //  LPVOID lpParameter,
                                                             0,                                 //  DWORD dwCreationFlags,
                                                             &(threadInfoStruct.m_ThreadID) );  //  LPDWORD lpThreadId
                if ( threadInfoStruct.m_hThread == NULL )
                {
                    OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::launch() ==> Call to CreateThread() failed\n" );
                    fResult = false;
                }
                else
                {
                    fResult = true;
                }
            #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
                pthread_attr_t  threadAttr;

                // initialize the thread attribute
                //  And set the stack size
                pthread_attr_init( &(threadAttr) );
                if ( stackSize != 0 )
                {
                    pthread_attr_setstacksize( &(threadAttr), stackSize );
                }

                // Set thread to detached state. No need for pthread_join
                pthread_attr_setdetachstate( &(threadAttr), PTHREAD_CREATE_DETACHED);

                // Create the thread
                if ( pthread_create( &(threadInfoStruct.m_ThreadId),
                                     &(threadAttr),
                                     linux_thread_start,
                                     pLaunchData ) == 0 )
                {
                    fResult = true;
                }
                else
                {
                    fResult = false;
                }

                // Destroy the thread attributes
                pthread_attr_destroy(&threadAttr);
            #else
                #error "ERROR: Platform dependant code"
            #endif
            // If the launch worked, null the pointer so it doesn't get
            //  deleted.
            if ( fResult == true )
            {
                pLaunchData = NULL;
            }
        }
    }
    catch ( ... )
    {
        OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::launch() ==> Caught Exception" );
    }

    if ( pLaunchData != NULL )
    {
        // Release the data
        try
        {
            delete pLaunchData;
        }
        catch ( ... )
        {
            OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::launch() ==> Caught Exception while deleting launch data." );
        }
    }

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  void  threadinfostruct_clear( ThreadInfoStruct & )
//
//  :Implementation
//"
void  ThreadLaunch::threadinfostruct_clear( ThreadInfoStruct & threadInfoStruct )
{
    memset( &threadInfoStruct, 0, sizeof(ThreadInfoStruct) );
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  std::string  threadinfostruct_get_threadid_string( ThreadInfoStruct & )
//
//  :Returns
//      This function returns the the threadid from the supplied
//      ThreadInfoStruct in a printable string form.  This function
//      is intended for debugging output purposes.
//
//  :Note
//      If the calling code needs the actual thread id it should use the
//      appropriate platform specific calls.
//
//  :Implementation
//"
std::string  ThreadLaunch::threadinfostruct_get_threadid_string( ThreadInfoStruct & threadInfoStruct )
{
    std::string resultStr;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        char    tempStr[32];
        sprintf( tempStr, "%08lX", (unsigned long)(threadInfoStruct.m_ThreadID) );
        tempStr[ sizeof(tempStr)-1 ] = 0;
        resultStr = tempStr;

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        char    tempStr[32];
        sprintf( tempStr, "%08lX", (unsigned long)(threadInfoStruct.m_ThreadId) );
        tempStr[ sizeof(tempStr)-1 ] = 0;
        resultStr = tempStr;

    #else
        #error "ERROR: Platform dependant code"
    #endif

    return (resultStr);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  void  threadinfostruct_create_current( ThreadInfoStruct & )
//
//  :Description
//      This function will populate the supplied ThreadInfoStruct with
//      information describing the currently running thread.
//
//  :Note
//      This function does not guarantees that all fields will be
//      properly populated.  It will generate enough information
//      to:
//          - Allow the threadid_string to be generated.
//
//  :Implementation
//"
void  ThreadLaunch::threadinfostruct_create_current( ThreadInfoStruct & threadInfoStruct )
{
    threadinfostruct_clear( threadInfoStruct );
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        threadInfoStruct.m_ThreadID = ::GetCurrentThreadId();

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        threadInfoStruct.m_ThreadId = ::pthread_self();

    #else
        #error "ERROR: Platform dependant code"
    #endif
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  std::string  get_current_threadid_string( void )
//
//  :Description
//      This function returns the the threadid of the currently
//      executing thread in a printable string form.  This function
//      is intended for debugging output purposes.  If the calling
//      code needs the actual thread id it should use the appropriate
//      platform specific calls.
//
//  :Implementation
//"
std::string  ThreadLaunch::get_current_threadid_string( void )
{
    ThreadInfoStruct    threadInfoStruct;
    threadinfostruct_create_current( threadInfoStruct );
    return ( threadinfostruct_get_threadid_string( threadInfoStruct ) );
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  bool    kill( ThreadInfoStruct & threadInfoStruct );
//
//  :Implementation
//"
bool  ThreadLaunch::kill( ThreadInfoStruct & threadInfoStruct )
{
    bool fResult = false;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        if ( ::TerminateThread( threadInfoStruct.m_hThread, 0 ) != FALSE )
        {
            fResult = true;
        }
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        printf( "ThreadLaunch::kill() ==> Killing thread \n" );
        pthread_kill( threadInfoStruct.m_ThreadId, 9 );
    #else
        #error "ERROR: This code is platform specific"
        fResult = false;
    #endif
    if ( fResult == true )
    {
        memset( &threadInfoStruct, 0, sizeof(ThreadInfoStruct) );
    }
    return (fResult);
}
//.



/////////////////////////////////////////////////////////////////////////////
//! static  DWORD  WINAPI win_thread_start( LPVOID )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    DWORD  WINAPI  ThreadLaunch::win_thread_start( LPVOID lpParameter )
    {
        //LaunchDataStruct * pLaunchData = reinterpret_cast< LaunchDataStruct * >( pData );
        LaunchDataStruct * pLaunchData = reinterpret_cast< LaunchDataStruct * >( lpParameter );
        if ( pLaunchData != NULL )
        {
            // Run the thread
            try
            {
                if ( pLaunchData->m_PfnActualFunction != NULL )
                {
                    (*(pLaunchData->m_PfnActualFunction))( pLaunchData->m_pData );
                }
            }
            catch ( ... )
            {
                OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::win_thread_start() ==> Caught Exception while running thread." );
            }

            // Release the data
            try
            {
                delete pLaunchData;
            }
            catch ( ... )
            {
                OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::win_thread_start() ==> Caught Exception while deleting launch data." );
            }
        }
        return (0);
    }

#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! static void *  linux_thread_start( void * )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    void *  ThreadLaunch::linux_thread_start( void * pData )
    {
        LaunchDataStruct * pLaunchData = reinterpret_cast< LaunchDataStruct * >( pData );
        if ( pLaunchData != NULL )
        {
            // Run the thread
            try
            {
                if ( pLaunchData->m_PfnActualFunction != NULL )
                {
                    (*(pLaunchData->m_PfnActualFunction))( pLaunchData->m_pData );
                }
            }
            catch ( ... )
            {
                OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::linux_thread_start() ==> Caught Exception while running thread." );
            }

            // Release the data
            try
            {
                delete pLaunchData;
            }
            catch ( ... )
            {
                OM_TRACE( OM_ETD_ERROR, "ThreadLaunch::linux_thread_start() ==> Caught Exception while deleting launch data." );
            }
        }
        return (NULL);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


}; // namespace CExThreading


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
//      CExtend\Libraries\CExThreading\CExThreading_Mutex.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_Mutex_h
#define _CExThreading_Mutex_h

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! Mutex
//
//  :Description
//      This class provides a mechanism for a mutex.  Only one thread
//      at a time can lock() the mutex.  But a given thread can lock the
//      mutex more than once.  For every succesful call to the
//      lock() functions the thread must make a matching call to the
//      release() function.
//
//      NOTE:   It is STRONGLY recomended that the calling code
//              use the AutoLock class for a safer way of locking
//              and unlocking the Mutex class.
//
//      You may create a mutex with or without a name.  If no name is
//      supplied then the mutex object is intended only for use inside
//      the current process.  If a name is supplied then the mutex object
//      is intended for use between processes.
//
//      This class will use different underyling OS mechanisms based on
//      wether or not this is a named mutex (and is therefore relevant
//      across processes).
//
//  :Platform Specific Notes
//
//      On the Microsoft windows platform the CriticalSection API
//      is used for mutex's of type System_PROCESS.  For Mutex's of
//      Style_SYSTEM the code uses the CreateMutex() API.
//          - A modified copy of the name argument (if supplied)
//              is used for the call to CreateMutex when the mutex
//              is Style_SYSTEM.  If a name is not supplied one will
//              be created.
//          - The wait function for CriticalSection's does not
//              have a timeout.  Therefore when the Mutex style
//              on Windows is Style_PROCESS the wait timeout
//              is simulated by using "Trys" and then a very
//              short wait.
//
//      On Linux there is simply no "process" wide Mutex
//      available.  There are named semaphores, but these
//      (at the time of this writting) look like they would
//      work, except if you recursed and called the lock twice
//      then it would fail.  So under linux the Style_PROCESS
//      mutex's are not supported.  If you try and create
//      a mutex on linux with Style_PROCESS an CExOutMgr error
//      message and DebugBreak are issued every time an
//      operation is performed on the mutex (creation, lock,
//      release, destruction).  So for the time being dont
//      use them!
//
//      Also, on linux there is no graceful timeout wait
//      for the pthread_mutex() mechanism.  So much like
//      the critical section on windows the delay wait
//      is simulated using try's and small delays.
//
//  :Definition
//"
class Mutex
{
    // Embedded Types
    private:

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            typedef struct
            {
                HANDLE              m_hMutex;
                CRITICAL_SECTION    m_CriticalSection;
            } PlatformStruct;
            enum { CritSectionWaitDelayMS   = 10 };
            enum { CritSectionSpinCount     = 100 };

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            typedef struct
            {
                bool                m_fCreateMutex;
                pthread_mutex_t     m_ProcessMutex;
            } PlatformStruct;
            enum { PThreadWaitDelayMS   = 1 };

        #else
            #error "ERROR: Platform dependant code"
        #endif


    // Data Members
    private:
        const ObjectIdent       m_ObjectIdent;
        PlatformStruct          m_Platform;

    // Construction
    public:
        Mutex( ObjectStyle objectStyle = ObjectStyle_PROCESS, const char * pszName = NULL, bool fReportState = false );
        ~Mutex( void );

        // Not implemented, do not use
    private:
        Mutex( const Mutex & other );
        const Mutex & operator = ( const Mutex & other );

    // Public Interface
    public:
        bool is_ok( void ) const;
        bool lock( WaitMode waitMode = WaitMode_FOREVER, WaitTime waitMillseconds = WaitTime_EMPTY );
        bool release( void );

        ObjectIdent     get_object_ident( void ) const;

    // Private Interface
    private:
        static PlatformStruct   platformstruct_get_empty( void );
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            bool    win_process_create( void );
            bool    win_process_lock( WaitMode waitMode, WaitTime waitTime );
            bool    win_process_release( void );
            bool    win_process_destroy( void );
            bool    win_system_create( void );
            bool    win_system_lock( WaitMode waitMode, WaitTime waitTime );
            bool    win_system_release( void );
            bool    win_system_destroy( void );
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            bool    linux_process_create( void );
            bool    linux_process_lock( WaitMode waitMode, WaitTime waitTime );
            bool    linux_process_release( void );
            bool    linux_process_destroy( void );
            bool    linux_system_create( void );
            bool    linux_system_lock( WaitMode waitMode, WaitTime waitTime );
            bool    linux_system_release( void );
            bool    linux_system_destroy( void );
        #else
            #error "ERROR: Platform dependant code"
        #endif
};
//.


/////////////////////////////////////////////////////////////////////////////

};  // namespace CExThreading

#endif // _CExThreading_Mutex_h



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
//      CExtend\Libraries\CExThreading\CExThreading_Thread.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_Thread_h
#define _CExThreading_Thread_h

namespace CExThreading
{


/////////////////////////////////////////////////////////////////////////////
//!  Thread
//
//  :Description
//      This class is used as a container for operating "threads" of
//      execution.  It provides member functions to start and stop the
//      thread as well as determine the state of the current thread
//      (if any) associated with with this object.
//
//      This class cannot be used "as-is".  Another class must be derived
//      from this class and implement the pure virtual thread_function().
//      It is in this function where the actual "thread" will run.
//      (Think of this as the main() function for the thread).
//
//      All member functions may be safely called from any thread context.
//
//      There is one of four states the class can be in. They are:
//          OFF, START_ISSUED, START_CONFIRMED, RUNNING, STOPPING
//
//  :Definition
//"
class Thread
{
    // Embedded Types
    public:
        enum State
        {
            State_ERROR,
            State_OFF,
            State_START_ISSUED,
            State_START_CONFIRMED,
            State_RUNNING,
            State_STOPPING
        };
    private:
        enum { MiniWaitTime     = 100 }; // use with blocking wait calls
        enum { MiniSleepTime    =   5 };

    // Data Members
    protected:
        const ObjectIdent               m_ObjectIdent;
        const bool                      m_fRegisterSignalHandle;
    private:
        mutable Mutex                   m_Mutex;
        ThreadLaunch::ThreadInfoStruct  m_ThreadInfoStruct;
        State                           m_CurrentState;
        mutable Event                   m_StateChangeEvent;

    // Construction
    public:
        Thread( const char * pszName = NULL, bool fReportState = false, bool fRegisterSignalHandle = true );
        virtual ~Thread( void );

        //  Not Implemented, do not use
    private:
        Thread( const Thread & rhs );
        const Thread & operator = ( const Thread & rhs );

    // Public Interface
    public:
        ObjectIdent     get_object_ident( void ) const;

        State           thread_state( void ) const;
        bool            thread_is_off( void ) const;
        bool            thread_is_on( void ) const;
        bool            thread_is_stop_triggered( void ) const;

        bool            thread_start( void );
        void            thread_stop( void );
        bool            thread_kill( void );
        void            thread_trigger_stop( void );

        static  const char *    state_as_string( State theState );

    // Protected Interface
    protected:
        bool                    thread_wait_stop_triggered( WaitTime waitTime ) const;

    // Private Interface
    private:
        virtual void            thread_function( void ) = 0;
        static  void            thread_entry_point( void * pData );
        void                    thread_start_function( void );
        void                    thread_acknowledge( void );
        void                    thread_change_state( State newState, const char * funcName );
        void                    thread_wait_state_change( WaitTime waitTime ) const;
};
//.

};  // namespace CExThreading

#endif // _CExThreading_Thread_h



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
//      CExtend\Libraries\CExThreading\CExThreading_Event.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_Event_h
#define _CExThreading_Event_h

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! Event
//
//  :Description
//      This class provides an Event mechanism.  Multithreaded applications
//      can use this class to syncrhonize behaviour.
//
//  :Definition
//"
class Event
{
    // Embedded Types
    public:

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            typedef struct
            {
                HANDLE              m_hEvent;
            } PlatformStruct;

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            typedef struct
            {
                bool                m_fCreateMutex;
                pthread_mutex_t     m_ProcessMutex;
                bool                m_fCreateCondition;
                pthread_cond_t      m_ProcessCondition;
                bool                m_fStateFlag;
            } PlatformStruct;

        #else
            #error "ERROR: Platform dependant code"
        #endif

    // Data Members
    private:
        const ObjectIdent   m_ObjectIdent;
        PlatformStruct      m_Platform;

    // Construction
    public:
        Event( ObjectStyle objectStyle = ObjectStyle_PROCESS, const char * pszName = NULL, bool fReportState = false );
        ~Event( void );

        // Not implemented, do not use
    private:
        Event( const Event & other );
        const Event & operator = ( const Event & other );

    // Public Interface
    public:
        bool is_ok( void ) const;
        bool set( void );
        bool reset( void );
        bool wait( WaitMode waitMode = WaitMode_FOREVER, WaitTime waitTime = WaitTime_EMPTY );

        ObjectIdent     get_object_ident( void ) const;

    // Private Interface
    private:
        static PlatformStruct   platformstruct_get_empty( void );
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            bool    win_create_event( void );
            bool    win_set_event( void );
            bool    win_reset_event( void  );
            bool    win_wait_event( WaitMode waitMode, WaitTime waitTime );
            bool    win_destroy_event( void );
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            bool    linux_create_event( void );
            bool    linux_set_event( void );
            bool    linux_reset_event( void  );
            bool    linux_wait_event( WaitMode waitMode, WaitTime waitTime );
            bool    linux_destroy_event( void );
        #else
            #error "ERROR: Platform dependant code"
        #endif
};
//.


/////////////////////////////////////////////////////////////////////////////

};  // namespace CExThreading

#endif // _CExThreading_Event_h



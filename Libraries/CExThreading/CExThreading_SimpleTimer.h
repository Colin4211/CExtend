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
//      CExtend\Libraries\CExThreading\CExThreading_SimpleTimer.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_SimpleTimer_h
#define _CExThreading_SimpleTimer_h

namespace CExThreading
{


/////////////////////////////////////////////////////////////////////////////
//! SimpleTimer
//
//  :Description
//      The SimpleTimer class provides a simple method of measuring
//      elapsed time (with a resolution of milliseconds) and
//      to determine if a preset amount of time has expired.
//
//      This is a _SIMPLE_ timer class.  This class is not thread safe.
//      For a thread safe version of this class see the Timer class.
//      The only intent of this class is to encapsulate the platform
//      specific methods of measuring time at the millisecond level
//      into a common interface.
//
//      Note that only the non-const functions will update the
//      internal expired flag.  If the const version of member functions
//      are called the object will not recalculate the elapsed time
//      and make an expiration determination.
//
//  :Definition
//"
class SimpleTimer
{
    // Embedded Types
    private:
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            typedef struct
            {
                FILETIME        m_FileTimeStart;
                FILETIME        m_FileTimeEnd;
            } PlatformStruct;

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            typedef struct
            {
                struct timeval      m_TimeValStart;
                struct timeval      m_TimeValEnd;
            } PlatformStruct;

        #else
            #error "ERROR: Platform dependant code"
        #endif

    // Data Members
    private:
        WaitTime        m_WaitTimeDuration;
        WaitTime        m_WaitTimeElapsed;
        bool            m_fStarted;
        bool            m_fExpired;
        PlatformStruct  m_PlatformTimer;

    // Construction
    public:
        SimpleTimer( void );
        SimpleTimer( const SimpleTimer & rhSide );
        ~SimpleTimer( void );
        const SimpleTimer & operator = ( const SimpleTimer & rhSide );

    // Public Interface
    public:
        void    clear( void );
        bool    empty( void ) const;

        bool    start_seconds( WaitTimeSeconds waitTimeSeconds = WaitTimeSeconds_MAX );
        bool    start_milliseconds( WaitTime  waitTime = WaitTime_MAX );
        bool    expire( void );

        bool    is_running( void );
        bool    is_running( void ) const;
        bool    is_expired( void );
        bool    is_expired( void ) const;

        WaitTimeSeconds     get_duration_seconds( void ) const;
        WaitTime            get_duration( void ) const;

        WaitTimeSeconds     get_elapsed_seconds( void );
        WaitTimeSeconds     get_elapsed_seconds( void ) const;
        WaitTime            get_elapsed( void );
        WaitTime            get_elapsed( void ) const;

        std::string         get_duration_seconds_as_string( void ) const;
        std::string         get_duration_as_string( void ) const;

        std::string         get_elapsed_seconds_as_string( void );
        std::string         get_elapsed_seconds_as_string( void ) const;
        std::string         get_elapsed_as_string( void );
        std::string         get_elapsed_as_string( void ) const;

        static std::string  waittimeseconds_as_string( WaitTimeSeconds waitTime );
        static std::string  waittime_as_string( WaitTime waitTime );

    // Private Interface
    private:
        void    check_and_update( void );

        static  void    platformstruct_clear( PlatformStruct & platformStruct );
        static  bool    platformstruct_start( PlatformStruct & platformStruct );
        static  bool    platformstruct_update( PlatformStruct & platformStruct );
        static  bool    platformstruct_calc( const PlatformStruct & platformStruct, WaitTime & waitTimeElapsed );
};
//.

};  // namespace CExThreading

#endif // _CExThreading_SimpleTimer_h


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
//      CExtend\Libraries\CExThreading\CExThreading_SimpleTimer.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> SimpleTimer
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{


/////////////////////////////////////////////////////////////////////////////
//! SimpleTimer( void )
//
//  :Description
//      This is the default constructor for the SimpleTimer class.
//      It creates a SimpleTimer object that is initially empty.
//
//  :Implementation
//"
SimpleTimer::SimpleTimer( void )
{
    clear();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! SimpleTimer( const SimpleTimer & )
//
//  :Description
//      This is the copy constructor for the SimpleTimer class.
//      It creates a SimpleTimer object that is in the same state
//      as the supplied object.
//
//      Note:   This function will not update the expire flag for
//              either the source or this object.
//
//  :Implementation
//"
SimpleTimer::SimpleTimer( const SimpleTimer & rhSide )
{
    clear();
    (*this) = rhSide;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~SimpleTimer( void )
//
//  :Description
//      This is the destructor for the SimpleTimer class.
//
//  :Implementation
//"
SimpleTimer::~SimpleTimer( void )
{
    clear();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const SimpleTimer & operator = ( const SimpleTimer & )
//
//  :Description
//      This function will make the current object an exact duplicate
//      of the supplied object.
//
//      Note:   The expiration flag and elapsed time will not
//              be updated for either the current object or the
//              rhSide object.
//
//  :Implementation
//"
const SimpleTimer &  SimpleTimer::operator = ( const SimpleTimer & rhSide )
{
    if ( this != &rhSide )
    {
        m_WaitTimeDuration  =   rhSide.m_WaitTimeDuration;
        m_WaitTimeElapsed   =   rhSide.m_WaitTimeElapsed;
        m_fStarted          =   rhSide.m_fStarted;
        m_fExpired          =   rhSide.m_fExpired;
        m_PlatformTimer     =   rhSide.m_PlatformTimer;
    }
    return (*this);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  clear( void )
//
//  :Description
//      This function will clear the current SimpleTimer object.  Any
//      timing operations in progress will end.
//
//  :Implementation
//"
void  SimpleTimer::clear( void )
{
    m_WaitTimeDuration  = WaitTime_EMPTY;
    m_WaitTimeElapsed   = WaitTime_EMPTY;
    m_fStarted          = false;
    m_fExpired          = false;
    platformstruct_clear( m_PlatformTimer );

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  empty( void ) const
//
//  :Description
//      If the current SimpleTimer is empty then the function returns
//      true.  The SimpleTimer class interprets having any timing
//      operations in effect (either running or expired) as non empty
//      in which case the function returns false.
//
//  :Implementation
//"
bool  SimpleTimer::empty( void ) const
{
    bool fResult = (m_fStarted == false);
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  start_seconds( WaitTimeSeconds = WaitTimeSeconds_MAX )
//
//  :Description
//      This function will start the SimpleTimer with a duration of the
//      indicated number of seconds.
//
//      This function merely converts the supplied seconds value to
//      milliseconds and calls the star_milliseconds() function.
//      For further details see that function.
//
//  :Implementation
//"
bool  SimpleTimer::start_seconds( WaitTimeSeconds waitTimeSeconds /*= WaitTimeSeconds_MAX*/ )
{
    WaitTime    waitTime = static_cast< WaitTime >( waitTimeSeconds * 1000 );
    return (start_milliseconds(waitTime));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  start_milliseconds( WaitTime = WaitTime_MAX )
//
//  :Description
//      This function will start the SimpleTimer with a duration of the
//      indicated number of milliseconds.
//
//      The number of milliseconds must be between WaitTime_MIN and
//      WaitTime_MAX.  (This is 1 millisecond to 1 week respectively)
//
//      If the timer is succesfully started the function returns true.
//      If the timer is not started the function returns false and
//      the object is cleared to the empty state.
//
//  :Implementation
//"
bool  SimpleTimer::start_milliseconds( WaitTime  waitTime /*= WaitTime_MAX*/ )
{
    clear();

    PlatformStruct  platformStruct;
    bool fResult = ( (waitTime>=WaitTime_MIN) && (waitTime<=WaitTime_MAX) );
    if ( fResult == true )
    {
        fResult = platformstruct_start( platformStruct );
    }

    if (fResult == true )
    {
        m_WaitTimeDuration  = waitTime;
        m_WaitTimeElapsed   = 0;
        m_fStarted          = true;
        m_fExpired          = false;
        m_PlatformTimer     = platformStruct;
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  expire( void )
//
//  :Description
//      This function will mark the currently running timer as expired.
//
//      If the timer is already expired then the function makes no changes
//      and returns false. (But is_expired() still returns true).
//
//      If a timer operation is in progress it is stopped and the timer
//      is marked as expired, the elapsed time is set at the point
//      in time this function is called, and the function returns true.
//
//      If there is no timing operation in progress or the timing
//      operation is already expired then the function will return false
//      and the function remains empty.
//
//  :Implementation
//"
bool  SimpleTimer::expire( void )
{
    bool fResult = false;
    if ( m_fStarted == true )
    {
        if ( m_fExpired == false )
        {
            PlatformStruct  backupStruct    = m_PlatformTimer;
            WaitTime        waitTime        = WaitTime_EMPTY;

            fResult =  platformstruct_update( m_PlatformTimer );
            fResult &= platformstruct_calc( m_PlatformTimer, waitTime );

            if ( fResult == false )
            {
                // If the operation fails, which it never should,
                //  we revert to the backup struct, since we dont know
                //  what state the failed functions left them in
                //  and mark the timer as expired.
                m_PlatformTimer     = backupStruct;
                m_fExpired          = true;
                m_WaitTimeElapsed   = WaitTime_MAX;
            }
            else
            {
                // Since we are "expiring" the timer, we mark it as
                //  expired!
                m_WaitTimeElapsed   = waitTime;
                if ( m_WaitTimeElapsed >= m_WaitTimeDuration )
                {
                    m_WaitTimeElapsed = m_WaitTimeDuration;
                }
                m_fExpired  = true;
            }
        }
    }

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_running( void )
//
//  :Description
//      If there is a timer running, but not yet expired the function
//      returns true.  Otherwise the function returns false.
//
//      Note:   This is the NON-const version of the function.  Therefore
//              this function will update the elapsed time and (if
//              necessary) the expired flag before determining the value
//              to return.
//
//  :Implementation
//"
bool  SimpleTimer::is_running( void )
{
    check_and_update();
    bool fResult = ( (m_fStarted!=false) && (m_fExpired==false) );
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_running( void ) const
//
//  :Description
//      If there is a timer running, but not yet expired the function
//      returns true.  Otherwise the function returns false.
//
//      Note:   This is the const version of the function.  Therefore
//              this function will not update either the elapsed time or
//              the expired flag before determining the value to return.
//
//  :Implementation
//"
bool  SimpleTimer::is_running( void ) const
{
    bool fResult = ( (m_fStarted!=false) && (m_fExpired==false) );
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_expired( void )
//
//  :Description
//      If the current timer has expired then the function returns true.
//      Otherwise the function returns false.
//
//      Note:   This is the NON-const version of the function.  Therefore
//              this function will update the elapsed time and (if
//              necessary) the expired flag before determining the value
//              to return.
//
//  :Implementation
//"
bool  SimpleTimer::is_expired( void )
{
    check_and_update();
    bool fResult = ( m_fExpired != false );
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_expired( void ) const
//
//  :Description
//      If the current timer has expired then the function returns true.
//      Otherwise the function returns false.
//
//      Note:   This is the const version of the function.  Therefore
//              this function will not update either the elapsed time or
//              the expired flag before determining the value to return.
//
//  :Implementation
//"
bool  SimpleTimer::is_expired( void ) const
{
    bool fResult = ( m_fExpired != false );
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! WaitTimeSeconds  get_duration_seconds( void ) const
//
//  :Descripition
//      This function will return the timer duration.  The duration is
//      the value that was supplied when the start_xxxx() function
//      was called.
//
//      Please note that if seconds value is calculated from the underlying
//      milliseconds value and rounding errors may occur.
//
//  :Implementation
//"
WaitTimeSeconds  SimpleTimer::get_duration_seconds( void ) const
{
    WaitTimeSeconds resultVal = static_cast< WaitTimeSeconds >(m_WaitTimeDuration / 1000);
    return (resultVal);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! WaitTime  get_duration( void ) const
//
//  :Descripition
//      This function will return the timer duration.  The duration is
//      the value that was supplied when the start_xxxx() function
//      was called.  The timer duration is returned as milliseconds.
//
//  :Implementation
//"
WaitTime  SimpleTimer::get_duration( void ) const
{
    WaitTimeSeconds resultVal = m_WaitTimeDuration;
    return (resultVal);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! WaitTimeSeconds  get_elapsed_seconds( void )
//
//  :Descripition
//      This function will return the elapsed time.  The elapsed time is
//      the difference between the time the start_xxxx() function was
//      called and either now, or when the timer expired.
//
//      Please note that if seconds value is calculated from the underlying
//      milliseconds value and rounding errors may occur.
//
//      Note:   This is the NON-const version of the function.  Therefore
//              this function will update the elapsed time and (if
//              necessary) the expired flag before determining the value
//              to return.
//
//  :Implementation
//"
WaitTimeSeconds  SimpleTimer::get_elapsed_seconds( void )
{
    check_and_update();
    WaitTimeSeconds resultVal = static_cast< WaitTimeSeconds >(m_WaitTimeElapsed / 1000);
    return (resultVal);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! WaitTimeSeconds  get_elapsed_seconds( void ) const
//
//  :Descripition
//      This function will return the elapsed time.  The elapsed time is
//      the difference between the time the start_xxxx() function was
//      called and either now, or when the timer expired.
//
//      Please note that if seconds value is calculated from the underlying
//      milliseconds value and rounding errors may occur.
//
//      Note:   This is the const version of the function.  Therefore
//              this function will not update either the elapsed time or
//              the expired flag before determining the value to return.
//
//  :Implementation
//"
WaitTimeSeconds  SimpleTimer::get_elapsed_seconds( void ) const
{
    WaitTimeSeconds resultVal = static_cast< WaitTimeSeconds >(m_WaitTimeElapsed / 1000);
    return (resultVal);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! WaitTime  get_elapsed( void )
//
//  :Descripition
//      This function will return the elapsed time.  The elapsed time is
//      the difference between the time the start_xxxx() function was
//      called and either now, or when the timer expired.
//      The elapsed time is returned as milliseconds.
//
//      Note:   This is the NON-const version of the function.  Therefore
//              this function will update the elapsed time and (if
//              necessary) the expired flag before determining the value
//              to return.
//
//  :Implementation
//"
WaitTime  SimpleTimer::get_elapsed( void )
{
    check_and_update();
    WaitTimeSeconds resultVal = m_WaitTimeElapsed;
    return (resultVal);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! WaitTime  get_elapsed( void ) const
//
//  :Descripition
//      This function will return the elapsed time.  The elapsed time is
//      the difference between the time the start_xxxx() function was
//      called and either now, or when the timer expired.
//      The elapsed time is returned as milliseconds.
//
//      Note:   This is the const version of the function.  Therefore
//              this function will not update either the elapsed time or
//              the expired flag before determining the value to return.
//
//  :Implementation
//"
WaitTime  SimpleTimer::get_elapsed( void ) const
{
    WaitTimeSeconds resultVal = m_WaitTimeElapsed;
    return (resultVal);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_duration_seconds_as_string( void ) const
//
//  :Descripition
//      This function will return the timer duration in string form.
//      The duration is the value that was supplied when the start_xxxx()
//      function was called.
//
//  :Implementation
//"
std::string  SimpleTimer::get_duration_seconds_as_string( void ) const
{
    return (waittimeseconds_as_string(get_duration_seconds()));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_duration_as_string( void ) const
//
//  :Descripition
//      This function will return the timer duration in string form.
//      The duration is the value that was supplied when the start_xxxx()
//      function was called.
//
//  :Implementation
//"
std::string  SimpleTimer::get_duration_as_string( void ) const
{
    return (waittime_as_string(get_duration()));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_elapsed_seconds_as_string( void )
//
//  :Descripition
//      This function will return the elapsed time as a string.  The elapsed
//      time is the difference between the time the start_xxxx() function
//      was called and either now, or when the timer expired.
//
//      Please note that if seconds value is calculated from the underlying
//      milliseconds value and rounding errors may occur.
//
//      Note:   This is the NON-const version of the function.  Therefore
//              this function will update the elapsed time and (if
//              necessary) the expired flag before determining the value
//              to return.
//
//  :Implementation
//"
std::string  SimpleTimer::get_elapsed_seconds_as_string( void )
{
    return (waittimeseconds_as_string(get_elapsed_seconds()));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_elapsed_seconds_as_string( void ) const
//
//  :Descripition
//      This function will return the elapsed time as a string.  The elapsed
//      time is the difference between the time the start_xxxx() function
//      was called and either now, or when the timer expired.
//
//      Please note that if seconds value is calculated from the underlying
//      milliseconds value and rounding errors may occur.
//
//      Note:   This is the const version of the function.  Therefore
//              this function will not update either the elapsed time or
//              the expired flag before determining the value to return.
//
//  :Implementation
//"
std::string  SimpleTimer::get_elapsed_seconds_as_string( void ) const
{
    return (waittimeseconds_as_string(get_elapsed_seconds()));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_elapsed_as_string( void )
//
//  :Descripition
//      This function will return the elapsed time as a string.  The elapsed
//      time is the difference between the time the start_xxxx() function
//      was called and either now, or when the timer expired.
//      The elapsed time is returned as milliseconds.
//
//      Note:   This is the NON-const version of the function.  Therefore
//              this function will update the elapsed time and (if
//              necessary) the expired flag before determining the value
//              to return.
//
//  :Implementation
//"
std::string  SimpleTimer::get_elapsed_as_string( void )
{
    return (waittime_as_string(get_elapsed()));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! std::string  get_elapsed_as_string( void ) const
//
//  :Descripition
//      This function will return the elapsed time as a string.  The elapsed
//      time is the difference between the time the start_xxxx() function
//      was called and either now, or when the timer expired.
//      The elapsed time is returned as milliseconds.
//
//      Note:   This is the const version of the function.  Therefore
//              this function will not update either the elapsed time or
//              the expired flag before determining the value to return.
//
//  :Implementation
//"
std::string  SimpleTimer::get_elapsed_as_string( void ) const
{
    return (waittime_as_string(get_elapsed()));
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  std::string  waittimeseconds_as_string( WaitTimeSeconds )
//
//  :Description
//      This function will return a string representation of the
//      supplied WaitTimeSeconds value.  If the supplied value
//      is out of range then the function returns an empty string.
//
//  :Implementation
//"
std::string  SimpleTimer::waittimeseconds_as_string( WaitTimeSeconds waitTime )
{
    std::string resultStr;
    if ( waitTime <= WaitTimeSeconds_MAX )
    {
        char    tempBuffer[32];
        tempBuffer[0] = 0;

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            sprintf( tempBuffer, "%lu", (unsigned long)waitTime );

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            sprintf( tempBuffer, "%lu", (unsigned long)waitTime );

        #else
            #error "ERROR: Platform dependant code"
        #endif

        resultStr = tempBuffer;
    }
    return (resultStr);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  std::string  waittime_as_string( WaitTime )
//
//  :Description
//      This function will return a string representation of the
//      supplied WaitTime value.  If the supplied value
//      is out of range then the function returns an empty string.
//
//  :Implementation
//"
std::string  SimpleTimer::waittime_as_string( WaitTime waitTime )
{
    std::string resultStr;
    if ( waitTime <= WaitTime_MAX )
    {
        char    tempBuffer[32];
        tempBuffer[0] = 0;

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            sprintf( tempBuffer, "%lu", (unsigned long)waitTime );

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            sprintf( tempBuffer, "%lu", (unsigned long)waitTime );

        #else
            #error "ERROR: Platform dependant code"
        #endif

        resultStr = tempBuffer;
    }
    return (resultStr);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  check_and_update( void )
//
//  :Description
//      This function will update the end time in the platform structure,
//      calculate the elapsed time and then update the elapsed time
//      member and (if necessary) the expired flag.
//
//  :Implementation
//"
void  SimpleTimer::check_and_update( void )
{
    if ( (m_fStarted == false) || (m_fExpired == true) )
    {
        return;
    }

    PlatformStruct     backupStruct = m_PlatformTimer;
    if ( platformstruct_update( m_PlatformTimer ) == false )
    {
        m_PlatformTimer     = backupStruct;
        m_fExpired          = true;
        m_WaitTimeElapsed   = WaitTime_MAX;
        return;
    }
    WaitTime    waitTime = WaitTime_EMPTY;
    if ( platformstruct_calc( m_PlatformTimer, waitTime ) == false )
    {
        m_PlatformTimer     = backupStruct;
        m_fExpired          = true;
        m_WaitTimeElapsed   = WaitTime_MAX;
        return;
    }

    if ( waitTime > m_WaitTimeDuration )
    {
        m_WaitTimeElapsed   = m_WaitTimeDuration;
        m_fExpired          = true;
    }
    else
    {
        m_WaitTimeElapsed   = waitTime;
    }

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static void  platformstruct_clear( PlatformStruct & )
//
//  :Description
//      This function returns an empty PlatformTimerStruct.
//
//  :Implementation
//"
void  SimpleTimer::platformstruct_clear( PlatformStruct & platformStruct )
{
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        memset( &platformStruct, 0, sizeof(PlatformStruct) );
        //platformStruct.m_FileTimeStart.dwHighDateTime   = 0;
        //platformStruct.m_FileTimeStart.dwLowDateTime    = 0;
        //platformStruct.m_FileTimeEnd.dwHighDateTime     = 0;
        //platformStruct.m_FileTimeEnd.dwLowDateTime      = 0;
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        memset( &platformStruct, 0, sizeof(PlatformStruct) );
        //platformStruct.m_TimeValStart.tv_sec            = 0;
        //platformStruct.m_TimeValStart.tv_usec           = 0;
        //platformStruct.m_TimeValEnd.tv_sec              = 0;
        //platformStruct.m_TimeValEnd.tv_usec             = 0;
    #else
        #error "ERROR: Platform dependant code"
    #endif
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  bool  platformstruct_start( PlatformStruct & )
//
//  :Description
//      This function is called to start a timer operation.  If the
//      function is succesful then the structure is in a suitable state
//      to later call the other platformtimerstruct_xxxxx() functions.
//
//  :Implementation
//"
bool  SimpleTimer::platformstruct_start( PlatformStruct & platformStruct )
{
    bool    fResult = false;
    platformstruct_clear( platformStruct );

    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        SYSTEMTIME  sysTime;
        FILETIME    fileTime;
        ::GetSystemTime( &sysTime );
        if ( ::SystemTimeToFileTime( &sysTime, &fileTime ) != FALSE )
        {
            platformStruct.m_FileTimeStart = fileTime;
            fResult = true;
        }

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        struct timeval timeVal;
        if ( gettimeofday( &timeVal, NULL ) == 0 )
        {
            platformStruct.m_TimeValStart = timeVal;
            fResult = true;
        }

    #else
        #error "ERROR: Platform dependant code"
    #endif

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  bool  platformstruct_update( PlatformStruct & )
//
//  :Description
//      This function is called to set the current end time of
//      a timer operation.  If the function is succesful then the
//      structure is in a suitable state to later call the
//      platformtimerstruct_calc() function.
//
//  :Implementation
//"
bool  SimpleTimer::platformstruct_update( PlatformStruct & platformStruct )
{
    bool    fResult = false;

    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        SYSTEMTIME  sysTime;
        FILETIME    fileTime;
        ::GetSystemTime( &sysTime );
        if ( ::SystemTimeToFileTime( &sysTime, &fileTime ) != FALSE )
        {
            platformStruct.m_FileTimeEnd = fileTime;
            fResult = true;
        }

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        struct timeval timeVal;
        if ( gettimeofday( &timeVal, NULL ) == 0 )
        {
            platformStruct.m_TimeValEnd = timeVal;
            fResult = true;
        }

    #else
        #error "ERROR: Platform dependant code"
    #endif

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  bool  platformstruct_calc( const PlatformStruct &, WaitTime & )
//
//  :Description
//      This function will calculate the difference in milliseconds between
//      when the platformtimerstruct_start() and the last time the
//      platformtimerstruct_update() function was called.
//
//  :Implementation
//"
bool  SimpleTimer::platformstruct_calc( const PlatformStruct & platformStruct, WaitTime & waitTimeElapsed )
{
    bool    fResult = false;

    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        Uint64                  startTimeLow    = 0;
        Uint64                  startTimeHigh   = 0;
        Uint64                  startTime       = 0;
        Uint64                  endTimeLow      = 0;
        Uint64                  endTimeHigh     = 0;
        Uint64                  endTime         = 0;
        static const Uint64     timeLimit       = static_cast< Uint64 >( WaitTime_MAX );
        Uint64                  diffTimeNano    = 0;
        Uint64                  diffTime        = 0;

        // Turn the start time into a Uint64
        startTimeLow    = platformStruct.m_FileTimeStart.dwLowDateTime;
        startTimeHigh   = platformStruct.m_FileTimeStart.dwHighDateTime;
        startTimeHigh   <<= 32;
        startTime       = startTimeLow | startTimeHigh;

        // Turn the end time into a Uint64
        endTimeLow      = platformStruct.m_FileTimeEnd.dwLowDateTime;
        endTimeHigh     = platformStruct.m_FileTimeEnd.dwHighDateTime;
        endTimeHigh     <<= 32;
        endTime         = endTimeLow | endTimeHigh;

        // Determine the difference
        diffTimeNano    = endTime - startTime;

        // FILETIME is in 100 nanosecond units
        //  Divide by 10000 to get milliseconds
        diffTime    = diffTimeNano / 10000;

        // Clamp the range
        //  And if the result is positive then cast
        //  to the resulting waittime
        if ( diffTime > timeLimit )
        {
            diffTime = timeLimit;
        }
        waitTimeElapsed = static_cast< WaitTime >( diffTime );
        fResult = true;

    #elif defined(CEXTEND_PLATFORM_TYPE_LINUX_I32) || defined(CEXTEND_PLATFORM_TYPE_LINUX_ARM32)

        //struct timeval {
        //    time_t      tv_sec;     /* seconds */
        //    suseconds_t tv_usec;    /* microseconds */
        //};

        // We know that the time_t on linux32 is
        //  a 32 bit value.  Furthermore we know
        //  that the value that is in the tv_usec
        //  member is the number os microseconds in
        //  a second.  So both those values will
        //  happily fit in a Uint64
        OM_DEBUG_ASSERT( sizeof(time_t) == 4 );

        Uint64  startValue      = static_cast< Uint64 >( platformStruct.m_TimeValStart.tv_sec );
        Uint64  startValueMS    = static_cast< Uint64 >( platformStruct.m_TimeValStart.tv_usec );
        startValue      = startValue * 1000; // Convert to milliseconds
        startValueMS    = startValueMS / 1000; // Convert to milliseconds
        startValue      = startValue + startValueMS;

        Uint64  endValue        = static_cast< Uint64 >( platformStruct.m_TimeValEnd.tv_sec );
        Uint64  endValueMS      = static_cast< Uint64 >( platformStruct.m_TimeValEnd.tv_usec );
        endValue        = endValue * 1000; // Convert to milliseconds
        endValueMS      = endValueMS / 1000; // Convert to milliseconds
        endValue        = endValue + endValueMS;

        // Determine the difference
        Uint64  diffTime    = endValue - startValue;

        // Clamp the range
        //  And if the result is positive then cast
        //  to the resulting waittime
        static const Uint64     timeLimit       = static_cast< Uint64 >( WaitTime_MAX );
        if ( diffTime > timeLimit )
        {
            diffTime = timeLimit;
        }
        waitTimeElapsed = static_cast< WaitTime >( diffTime );
        fResult = true;

    #elif defined(CEXTEND_PLATFORM_TYPE_LINUX_I64) || defined(CEXTEND_PLATFORM_TYPE_LINUX_ARM64)

        //struct timeval {
        //    time_t      tv_sec;     /* seconds */
        //    suseconds_t tv_usec;    /* microseconds */
        //};

        // We know that the time_t on linux64 is a 64 bit value.
        OM_DEBUG_ASSERT( sizeof(time_t) == 8 );

        Uint64  startValue      = static_cast< Uint64 >( platformStruct.m_TimeValStart.tv_sec );
        Uint64  startValueMS    = static_cast< Uint64 >( platformStruct.m_TimeValStart.tv_usec );
        startValue      = startValue * 1000; // Convert to milliseconds
        startValueMS    = startValueMS / 1000; // Convert to milliseconds
        startValue      = startValue + startValueMS;

        Uint64  endValue        = static_cast< Uint64 >( platformStruct.m_TimeValEnd.tv_sec );
        Uint64  endValueMS      = static_cast< Uint64 >( platformStruct.m_TimeValEnd.tv_usec );
        endValue        = endValue * 1000; // Convert to milliseconds
        endValueMS      = endValueMS / 1000; // Convert to milliseconds
        endValue        = endValue + endValueMS;

        // Determine the difference
        Uint64  diffTime    = endValue - startValue;

        // Clamp the range
        //  And if the result is positive then cast
        //  to the resulting waittime
        static const Uint64     timeLimit       = static_cast< Uint64 >( WaitTime_MAX );
        if ( diffTime > timeLimit )
        {
            diffTime = timeLimit;
        }
        waitTimeElapsed = static_cast< WaitTime >( diffTime );
        fResult = true;

    #else
        #error "ERROR: Platform dependant code"
    #endif

    return (fResult);
}
//.

};  // namespace CExThreading



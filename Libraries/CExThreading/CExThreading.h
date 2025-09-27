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
//      CExtend\Libraries\CExThreading\CExThreading.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_h
#define _CExThreading_h

/////////////////////////////////////////////////////////////////////////////
//  Additional Includes
//


#include "CExBase.h"

#include "CExOutput.h"

#include <signal.h>

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    #include <process.h>
    #include <accctrl.h>
    #include <aclapi.h>
#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    #include <pthread.h>
    #include <semaphore.h>
    #include <fcntl.h>
    #include <time.h>
    #include <sys/time.h>
#else
    #error "ERROR: Platform dependant code"
#endif


/////////////////////////////////////////////////////////////////////////////
//! Simple Types
//
//  :Definitions
//"
namespace CExThreading
{
        // This type is used to indicate how long to wait
        //  for an operation to complete.
    enum WaitMode
    {
        WaitMode_ERROR      = 0,
        WaitMode_FOREVER    = 1,
        WaitMode_TIMED      = 2
    };

        // Some of the types in this library
        //  can work in the context of the current process, or in the
        //  context of the entire operating system.  This type is used
        //  to indicate the distinction.
    enum Style
    {
        Style_ERROR,
        Style_PROCESS,
        Style_SYSTEM
    };
    enum ObjectStyle
    {
        ObjectStyle_ERROR,
        ObjectStyle_PROCESS,
        ObjectStyle_SYSTEM
    };

        // This is used by the ObjectIdent class, and
        //  in turn all classes which use the ObjectIdent
        //  to help identify the type of class
    enum ObjectType
    {
        ObjectType_ERROR,
        ObjectType_MUTEX,
        ObjectType_EVENT,
        ObjectType_THREAD
    };


        // This is the maximum length of the name used for
        //  any types in this library (name of mutex, event,
        //  thread, etc...)
    enum { MaxNameLength = 256 };

        // This type represents the time to wait.
        //  The WaitTime type always represents
        //  the time in Milliseconds.
        //  The WaitTimeSeconds always represents
        //  the wait time in seconds
    typedef Uint32      WaitTimeSeconds;
    typedef Uint32      WaitTime;

    extern const WaitTimeSeconds    WaitTimeSeconds_EMPTY;
    extern const WaitTimeSeconds    WaitTimeSeconds_MIN;
    extern const WaitTimeSeconds    WaitTimeSeconds_MAX;

    extern const WaitTime           WaitTime_EMPTY;
    extern const WaitTime           WaitTime_MIN;
    extern const WaitTime           WaitTime_MAX;

    // Prototype Classes
    //  We need to prototype certain classes to allow
    //  compilation to occur properly.
    class   Mutex;
    class   Event;
    class   Thread;

    class   SignalHandler;

}; // namespace CExThreading
//.


/////////////////////////////////////////////////////////////////////////////
//  Function Prototypes
//

namespace CExThreading
{
    void    DelayMilliseconds( WaitTime waitMilliseconds );
    void    DelaySeconds( WaitTimeSeconds waitSeconds );

    WaitTime    GetTickMilliseconds( void );
}; // namespace CExThreading


/////////////////////////////////////////////////////////////////////////////
//  CExThreading Declarations
//

#include "CExThreading_SimpleTimer.h"
#include "CExThreading_ObjectIdent.h"
#include "CExThreading_ThreadLaunch.h"
#include "CExThreading_KillProcess.h"
#include "CExThreading_Mutex.h"
#include "CExThreading_Event.h"
#include "CExThreading_AutoLock.h"
#include "CExThreading_SafeObject.h"
#include "CExThreading_SafeDeque.h"
#include "CExThreading_Thread.h"
#include "CExThreading_SignalHandler.h"


/////////////////////////////////////////////////////////////////////////////

#endif // _CExThreading_h



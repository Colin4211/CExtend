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
//      CExtend\Libraries\CExThreading\CExThreading_DelayMilliseconds.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> DelayMilliseconds
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! void  DelayMilliseconds( WaitTime )
//
//  :Arguments
//      = WaitTime waitMilliseconds
//          The number of milliseconds to wait before returning.  The maximum
//          allowed time is equivilant to 1 day.
//
//  :Description
//      This function will halt the current thread of execution for the
//      specified amount of time.  (Up to a maximum of 1 day).
//
//  :Note
//      Depending on the OS the function will attempt to delay in the
//      most graceful way possible.  This means that the function
//      implementation will strive to avoid "busy" loops.  Which
//      actually consume considerable CPU cycles while executing.
//
//  :Implementation
//"
void  DelayMilliseconds( WaitTime waitMilliseconds )
{
    // Verify Arguments
    if ( waitMilliseconds > WaitTime_MAX)
    {
        waitMilliseconds = WaitTime_MAX;
    }

    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        DWORD milliSeconds = static_cast< DWORD >( waitMilliseconds );
        ::Sleep( milliSeconds );
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        WaitTime        lengthOfMicrosecond = 1000;
        unsigned int    microSeconds = static_cast< unsigned int >( waitMilliseconds * lengthOfMicrosecond );
        ::usleep( microSeconds );
    #else
        #error "ERROR: This code is platform specific"
    #endif

    return;
};
//.

}; // namespace CExThreading



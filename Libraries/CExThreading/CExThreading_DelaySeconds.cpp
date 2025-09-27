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
//      CExtend\Libraries\CExThreading\CExThreading_DelaySeconds.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> DelaySeconds
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! void  DelaySeconds( WaitTimeSeconds )
//
//  :Arguments
//      = WaitTimeSeconds waitSeconds
//          The number of seconds to wait before returning.  The maximum
//          allowed time is 1 day.
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
void  DelaySeconds( WaitTimeSeconds waitSeconds )
{
    // Verify Arguments
    if ( waitSeconds > WaitTimeSeconds_MAX)
    {
        waitSeconds = WaitTimeSeconds_MAX;
    }

    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        WaitTimeSeconds     lengthOfSecond  = 1000;
        DWORD               milliSeconds    = static_cast< DWORD >( waitSeconds * lengthOfSecond );
        ::Sleep( milliSeconds );
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        unsigned int    sleepSeconds    = static_cast< unsigned int >( waitSeconds );
        ::sleep( sleepSeconds );
    #else
        #error "ERROR: This code is platform specific"
    #endif

    return;
};
//.


}; // namespace CExThreading



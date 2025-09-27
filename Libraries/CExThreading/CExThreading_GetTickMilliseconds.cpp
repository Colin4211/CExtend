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
//      CExtend\Libraries\CExThreading\CExThreading_GetTickMilliseconds.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> GetTickMilliseconds
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! WaitTime  GetTickMilliseconds( void )
//
//  :Returns
//      This function returns the number of milliseconds since the system
//      started.  Depending on OS and hardware this value will have varying
//      degrees of granularity.
//
//  :Implementation
//"
WaitTime  GetTickMilliseconds( void )
{
    WaitTime    resultVal = 0;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        resultVal = ::GetTickCount();
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        struct  timespec timeSpec;
        clock_gettime( CLOCK_MONOTONIC, &timeSpec );
        resultVal   =   timeSpec.tv_nsec / 1000000;
        resultVal   +=  timeSpec.tv_sec * 1000;
    #else
        #error "ERROR: This code is platform specific"
    #endif

    return (resultVal);
};
//.


}; // namespace CExThreading



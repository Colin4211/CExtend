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
//      CExtend\Libraries\CExThreading\CExThreading_KillProcess.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> KillProcess
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! void KillProcess( void )
//
//  :Description
//      This function will kill (end with malice) the current process.
//      Use of this function is recomended only in extreme circumstances.
//
//  :Implementation
//"
void  KillProcess( void )
{
    OM_TRACE0( OM_ETD_WARNING, "CExThreading::KillProcess() ==> Called." );
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        ::TerminateProcess( GetCurrentProcess(), 0 );
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        kill( getpid(), SIGKILL );
    #else
        #error "ERROR: This code is platform specific"
    #endif
    return;
}
//.


};  // namespace Tasking


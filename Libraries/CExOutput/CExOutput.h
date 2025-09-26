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
//      CExOutput
//
//  File:
//      CExtend\Libraries\CExOutput\CExOutput.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_h
#define _CExOutput_h

/////////////////////////////////////////////////////////////////////////////

#include "CExBase.h"

/////////////////////////////////////////////////////////////////////////////
//  Class Prototypes
//

namespace CExOutput
{
    class Manager;
    class Manager;

    class Console;

    void    SystemErrorEvent( const char *   sourceFile,
                              unsigned long  sourceLine,
                              const char *   outMsg,
                              unsigned long  sysErr );

}; // namespace CExOutput


/////////////////////////////////////////////////////////////////////////////
//  Additional Include Files
//

#include "CExOutput_Interface.h"
#include "CExOutput_SafeStringCopy.h"
#include "CExOutput_TimeStamp.h"
#include "CExOutput_OutputEvent.h"
#include "CExOutput_Manager.h"
#include "CExOutput_Console.h"
#include "CExOutput_Exception.h"
#include "CExOutput_Obsolete.h"
#include "CExOutput_DebugScope.h"
#include "CExOutput_Macros.h"


/////////////////////////////////////////////////////////////////////////////

#endif // _CExOutput_h

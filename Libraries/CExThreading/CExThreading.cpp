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
//      CExtend\Libraries\CExThreading\CExThreading.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

/////////////////////////////////////////////////////////////////////////////
//! Constants
//
//  :Implementation
//"
namespace CExThreading
{
    const WaitTimeSeconds       WaitTimeSeconds_EMPTY   = 0;
    const WaitTimeSeconds       WaitTimeSeconds_MIN     = 0;
    const WaitTimeSeconds       WaitTimeSeconds_MAX     = (7 * 24 * 60 * 60);           // 1 week in seconds

    const WaitTime              WaitTime_EMPTY          = 0;
    const WaitTime              WaitTime_MIN            = 0;
    const WaitTime              WaitTime_MAX            = (7 * 24 * 60 * 60 * 1000);    // 1 week in milliseconds

}; // namespace CExThreading
//.


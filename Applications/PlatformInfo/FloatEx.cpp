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
//      PlatformInfo
//
//  File:
//      CExtend\Applications\PlatformInfo\FloatEx.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Apps
//      <DT_SUB_TOPIC> PlatformInfo
//
/////////////////////////////////////////////////////////////////////////////

#include "precomp.h"
#include "FloatEx.h"

/////////////////////////////////////////////////////////////////////////////

std::string  FloatEx_FloatAsString( const float & theFloat, bool fFloat )
{
    char                tempStr[ 256 ];
    std::string         strFormat = ( (fFloat==false)? "%g" : "%.1f" );
    sprintf( tempStr, strFormat.c_str(), theFloat );
    tempStr[sizeof(tempStr)-1] = 0;
    return (std::string(tempStr));
}

/////////////////////////////////////////////////////////////////////////////

std::string  FloatEx_FloatAsString( const double & theFloat, bool fFloat )
{
    char    tempStr[ 256 ];
    std::string         strFormat = ( (fFloat==false)? "%g" : "%.1f" );
    sprintf( tempStr, strFormat.c_str(), theFloat );
    tempStr[sizeof(tempStr)-1] = 0;
    return (std::string(tempStr));
}

/////////////////////////////////////////////////////////////////////////////

std::string  FloatEx_FloatAsString( const long double & theFloat, bool fFloat )
{
    char    tempStr[ 256 ];
    std::string         strFormat = ( (fFloat==false)? "%Lg" : "%.1Lf" );
    sprintf( tempStr, strFormat.c_str(), theFloat );
    tempStr[sizeof(tempStr)-1] = 0;
    return (std::string(tempStr));
}

/////////////////////////////////////////////////////////////////////////////

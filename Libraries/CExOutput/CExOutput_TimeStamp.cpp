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
//      CExtend\Libraries\CExOutput\CExOutput_TimeStamp.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//      <DT_SUB_TOPIC> TimeStamp
//
/////////////////////////////////////////////////////////////////////////////

#include "CExOutput.h"

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! TimeStamp( void )
//
//  :Description
//      This is the default constructor for the TimeStamp class.  It will
//      create the object in the empty state.
//
//  :Implementation
//"
TimeStamp::TimeStamp( void )
{
    clear();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! TimeStamp( const TimeStamp & )
//
//  :Description
//      This is the copy constructor for the TimeStamp class.  It will
//      create the object as a duplicate of the supplied object.
//
//  :Implementation
//"
TimeStamp::TimeStamp( const TimeStamp & rhSide )
    : m_TimeStruct( rhSide.m_TimeStruct )
{
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! explicit  TimeStamp( const OM_TimeStruct & )
//
//  :Description
//      This is an alternate initialization constructor for the TimeStamp
//      class.  It will create the new TimeStamp object with the supplied
//      structure.  This constructor is equivilant to calling the default
//      constructor then the initialize() member function.
//
//  :Implementation
//"
TimeStamp::TimeStamp( const OM_TimeStruct & omTimeStruct )
{
    initialize( omTimeStruct );
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~TimeStamp( void )
//
//  :Description
//      This is the destructor for the TimeStamp class.
//
//  :Implementation
//"
TimeStamp::~TimeStamp( void )
{
    clear();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const TimeStamp &  operator = ( const TimeStamp & )
//
//  :Description
//      This is the assignment operator for the TimeStamp class.  It
//      will copy the contents of the supplied object into the current
//      object.
//
//  :Implementation
//"
const TimeStamp &  TimeStamp::operator = ( const TimeStamp & rhSide )
{
    if ( this != &rhSide )
    {
        m_TimeStruct = rhSide.m_TimeStruct;
    }
    return (*this);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  clear( void )
//
//  :Description
//      This function will clear the current object to the empty state.
//
//      Note:  The underlying structure will be populated with values
//              equivilant to those values used in the Util::Date
//              and Util::Time classes.
//
//  :Implementation
//"
void  TimeStamp::clear( void )
{
    m_TimeStruct.m_Year     = Int16_MIN;
    m_TimeStruct.m_Month    = -1;
    m_TimeStruct.m_Day      = -1;
    m_TimeStruct.m_Hour     = -1;
    m_TimeStruct.m_Minute   = -1;
    m_TimeStruct.m_Second   = -1;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  empty( void ) const
//
//  :Description
//      This function will return true if the current TimeStamp
//      object is in the empty state.
//
//  :Implementation
//"
bool  TimeStamp::empty( void ) const
{
    return ( m_TimeStruct.m_Year == Int16_MIN );
}
//.


/////////////////////////////////////////////////////////////////////////////
//! int  compare( const TimeStamp & ) const
//
//  :Description
//      This function will compare the current TimeStamp to the supplied
//      TimeStamp and will return an integer (-1,0,1) indicating their
//      relative ordering.
//
//  :Implementation
//"
int  TimeStamp::compare( const TimeStamp & rhSide ) const
{
    bool    fLeftEmpty  = empty();
    bool    fRightEmpty = rhSide.empty();
    if ( (fLeftEmpty==true) && (fRightEmpty==true) )
    {
        return (0);
    }
    else if ( fLeftEmpty == true )
    {
        return (-1);
    }
    else if ( fRightEmpty == true )
    {
        return (1);
    }

    if ( m_TimeStruct.m_Year < rhSide.m_TimeStruct.m_Year )
    {
        return (-1);
    }
    if ( m_TimeStruct.m_Year > rhSide.m_TimeStruct.m_Year )
    {
        return (1);
    }

    if ( m_TimeStruct.m_Month < rhSide.m_TimeStruct.m_Month )
    {
        return (-1);
    }
    if ( m_TimeStruct.m_Month > rhSide.m_TimeStruct.m_Month )
    {
        return (1);
    }

    if ( m_TimeStruct.m_Day < rhSide.m_TimeStruct.m_Day )
    {
        return (-1);
    }
    if ( m_TimeStruct.m_Day > rhSide.m_TimeStruct.m_Day )
    {
        return (1);
    }

    if ( m_TimeStruct.m_Hour < rhSide.m_TimeStruct.m_Hour )
    {
        return (-1);
    }
    if ( m_TimeStruct.m_Hour > rhSide.m_TimeStruct.m_Hour )
    {
        return (1);
    }

    if ( m_TimeStruct.m_Minute < rhSide.m_TimeStruct.m_Minute )
    {
        return (-1);
    }
    if ( m_TimeStruct.m_Minute > rhSide.m_TimeStruct.m_Minute )
    {
        return (1);
    }

    if ( m_TimeStruct.m_Second < rhSide.m_TimeStruct.m_Second )
    {
        return (-1);
    }
    if ( m_TimeStruct.m_Second > rhSide.m_TimeStruct.m_Second )
    {
        return (1);
    }

    return (0);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  initialize( const OM_TimeStruct & )
//
//  :Description
//      This function will inititalize the current TimeStamp object
//      using the supplied structure.  If the supplied structure is
//      invalid the function will fail and the object will be cleared
//      to the empty state.
//
//      Note:   This function will make a best guess attempt at verifying
//              the supplied structure is valid.  However, it does not
//              know about leap years and such.  So in reality this
//              function will accept any structure that is mostly
//              correct.
//
//  :Implementation
//"
bool  TimeStamp::initialize( const OM_TimeStruct & omTimeStruct )
{
    clear();
    if ( omTimeStruct.m_Year == Int16_MIN )
    {
        return (false);
    }

    if ( omTimeStruct.m_Day < 1 )
    {
        return (false);
    }
    switch ( omTimeStruct.m_Month )
    {
        case 1:     // jan
        case 3:     // mar
        case 5:     // may
        case 7:     // jul
        case 8:     // aug
        case 10:    // oct
        case 12:    // dec
            if ( omTimeStruct.m_Day > 31 )
            {
                return (false);
            }
            break;
        case 2:
            if ( (((int)omTimeStruct.m_Year) % 4) == 0 )
            {
                if ( omTimeStruct.m_Day > 29 )
                {
                    return (false);
                }
            }
            else
            {
                if ( omTimeStruct.m_Day > 28 )
                {
                    return (false);
                }
            }
            break;
        case 4:     // april
        case 6:     // june
        case 9:     // sept
        case 11:    // nov
            if ( omTimeStruct.m_Day > 30 )
            {
                return (false);
            }
            break;
        default:
            return (false);
    }

    if ( (omTimeStruct.m_Hour < 0) || (omTimeStruct.m_Hour > 23) )
    {
        return (false);
    }
    if ( (omTimeStruct.m_Minute < 0) || (omTimeStruct.m_Hour > 59) )
    {
        return (false);
    }
    if ( (omTimeStruct.m_Second < 0) || (omTimeStruct.m_Second > 59) )
    {
        return (false);
    }

    m_TimeStruct = omTimeStruct;
    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  initialize( void )
//
//  :Description
//      This function will initialize the current TimeStamp object to
//      the current time.
//
//      Note:   That the TimeStamp class, being a wrapper around the
//              OM_TimeStruct, is always considered to be in the
//              context of UTC/GMT.
//
//  :Implementation
//"
bool  TimeStamp::initialize( void )
{
    clear();
    time_t  curTime = time(NULL);
    struct tm * pTM = gmtime( &curTime );
    struct tm   gmTm;
    if ( pTM == NULL )
    {
        return (false);
    }
    else
    {
        gmTm = (*pTM);
    }

    OM_TimeStruct   omTimeStruct;
    //omTimeStruct.m_Year     = 1970 + gmTm.tm_year;
    omTimeStruct.m_Year     = 1900 + gmTm.tm_year;
    omTimeStruct.m_Month    = 1 + gmTm.tm_mon;
    omTimeStruct.m_Day      = gmTm.tm_mday;
    omTimeStruct.m_Hour     = gmTm.tm_hour;
    omTimeStruct.m_Minute   = gmTm.tm_min;
    omTimeStruct.m_Second    = gmTm.tm_sec;

    return (initialize(omTimeStruct));
}
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput



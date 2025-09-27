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
//      CExtend\Libraries\CExThreading\CExThreading_AutoLock.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> AutoLock
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! AutoLock( Mutex *, WaitMode, WaitTimeType )
//
//  :Arguments
//      = Mutex *  pMutex
//          A pointer to the Mutex object that is to be locked.
//      = WaitMode  waitMode = WaitMode_FOREVER
//          The WaitMode to pass to the lock() function.
//      = WaitTime  waitTime = WaitTime_EMPTY
//          The WaitTime to pass to the lock() function.
//
//  :Description
//      The constructor will attempt to lock the provided Mutex with the
//      provided arguments.  The result of the lock() function can
//      be checked using the is_locked() member function.
//
//  :Implementation
//"
AutoLock::AutoLock( Mutex *       pMutex,
                    WaitMode      waitMode /* = WaitMode_FOREVER */,
                    WaitTime      waitTime  /* = WaitTime_EMPTY */ )
    :   m_pMutex( pMutex )
        #if defined(CEXTEND_DEBUG)
            ,   m_PszFile( NULL ) , m_LineNumber( 0 )
        #endif // defined(CEXTEND_DEBUG)
{
    do_lock( waitMode, waitTime );
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! AutoLock( Mutex &, WaitMode, WaitTime )
//
//  :Arguments
//      = Mutex &  theMutex
//          A reference to the Mutex object that is to be locked.
//      = Mutex::WaitMode  waitMode = Mutex::WaitMode_FOREVER
//          The WaitMode to pass to the lock() function.
//      = Mutex::WaitTime  waitTime = 0
//          The WaitTime to pass to the lock() function.
//
//  :Description
//      The constructor will attempt to lock the provided Mutex with the
//      provided arguments.  The result of the lock() function can
//      be checked using the is_locked() member function.
//
//  :Implementation
//"
AutoLock::AutoLock( Mutex &       theMutex,
                    WaitMode      waitMode /* = WaitMode_FOREVER */,
                    WaitTime      waitTime  /* = WaitTime_EMPTY */ )
    :   m_pMutex( &theMutex )
        #if defined(CEXTEND_DEBUG)
            ,   m_PszFile( NULL ) , m_LineNumber( 0 )
        #endif // defined(CEXTEND_DEBUG)
{
    do_lock( waitMode, waitTime );
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! AutoLock( Mutex &, WaitMode, WaitTime )
//
//  :Arguments
//      = Mutex &  theMutex
//          A reference to the Mutex object that is to be locked.
//      = Mutex::WaitMode  waitMode = Mutex::WaitMode_FOREVER
//          The WaitMode to pass to the lock() function.
//      = Mutex::WaitTime  waitTime = 0
//          The WaitTime to pass to the lock() function.
//
//  :Description
//      The constructor will attempt to lock the provided Mutex with the
//      provided arguments.  The result of the lock() function can
//      be checked using the is_locked() member function.
//
//  :Implementation
//"
#if defined(CEXTEND_DEBUG)
    AutoLock::AutoLock( const char *  pszFile,
                        size_t        lineNumber,
                        Mutex &       theMutex,
                        WaitMode      waitMode /* = WaitMode_FOREVER */,
                        WaitTime      waitTime  /* = WaitTime_EMPTY */ )
        :   m_pMutex( &theMutex )
        ,   m_PszFile( pszFile )
        ,   m_LineNumber( lineNumber )
    {
        do_lock( waitMode, waitTime );
        return;
    }
#endif // defined(CEXTEND_DEBUG)
//.


/////////////////////////////////////////////////////////////////////////////
//! ~AutoLock( void )
//
//  :Description
//      When the object is destroyed it will automatically call the
//      release() function for the mutex supplied at create time.  But
//      only if the call to lock() called at create time was
//      succesful.
//
//  :Implementation
//"
AutoLock::~AutoLock( void )
{
    do_unlock();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_locked( void )
//
//  :Returns
//      If the Mutex supplied at construction was lock()'d succesfully
//      then this function returns true.  Otherwise the function returns
//      false.
//
//  :Description
//      This function is called to determine if the Mutex supplied to
//      the constructor was succesfully locked.
//
//  :Implementation
//"
bool  AutoLock::is_locked( void )
{
    bool fResult = false;
    if ( m_pMutex != NULL )
    {
        fResult = true;
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_locked( void )
//
//  :Returns
//      Function returns true if the mutex is locked.
//      Otherwise returns false and sets Mutex ptr to NULL.
//
//  :Implementation
//"
bool  AutoLock::do_lock( WaitMode waitMode, WaitTime waitTime  )
{
    std::string strTag = "";
    #if defined(CEXTEND_DEBUG)
        if ( m_PszFile != NULL )
        {
            char numString[32];
            sprintf( numString, "[%lu]", (unsigned long)m_LineNumber );
            strTag      +=  m_PszFile;
            strTag      +=  numString;
        }
    #endif // defined(CEXTEND_DEBUG)

    bool fReportState = false;
    if ( m_pMutex == NULL )
    {
        //OM_TRACE1( OM_ETD_ERROR, "AutoLock::do_lock() ==> Mutex PTR Is NULL - %s", strTag.c_str() );
        m_pMutex = NULL;
        return (false);
    }
    else
    {
        ObjectIdent     objectIdent = m_pMutex->get_object_ident();
        fReportState                = objectIdent.report_state_flag();
        if ( strTag.empty() == false )
        {
            strTag += " - ";
        }
        strTag += objectIdent.name();
    }

    if ( m_pMutex->is_ok() == false )
    {
        if ( fReportState == true )
        {
            OM_TRACE1( OM_ETD_ERROR, "AutoLock::do_lock() ==> Mutex is NOT Ok - %s", strTag.c_str() );
        }
        m_pMutex = NULL;
        return (false);
    }

    if (m_pMutex->lock(waitMode,waitTime) == false)
    {
        if ( fReportState == true )
        {
            OM_TRACE1( OM_ETD_ERROR, "AutoLock::do_lock() ==> Failed to Lock Mutex A - %s", strTag.c_str() );
        }
        m_pMutex = NULL;
        return (false);
    }

    if ( fReportState == true )
    {
        OM_TRACE1( OM_ETD_INFO, "AutoLock::do_lock() ==> Mutex was locked - %s", strTag.c_str() );
    }

    return (true);
}


/////////////////////////////////////////////////////////////////////////////

bool  AutoLock::do_unlock( void )
{
    std::string strTag = "";
    #if defined(CEXTEND_DEBUG)
        if ( m_PszFile != NULL )
        {
            char numString[32];
            sprintf( numString, "[%lu]", (unsigned long)m_LineNumber );
            strTag      +=  m_PszFile;
            strTag      +=  numString;
        }
    #endif // defined(CEXTEND_DEBUG)

    bool fReportState = false;
    if ( m_pMutex == NULL )
    {
        //OM_TRACE1( OM_ETD_ERROR, "AutoLock::do_unlock() ==> Mutex PTR Is NULL - %s", strTag.c_str() );
        return (false);
    }
    else
    {
        ObjectIdent     objectIdent = m_pMutex->get_object_ident();
        fReportState                = objectIdent.report_state_flag();
        if ( strTag.empty() == false )
        {
            strTag += " - ";
        }
        strTag += objectIdent.name();
    }

    if ( m_pMutex->release() == false )
    {
        if ( fReportState == true )
        {
            OM_TRACE1( OM_ETD_ERROR, "AutoLock::do_unlock() ==> Failed to Release Mutex - %s", strTag.c_str() );
        }
        return (false);
    }

    if ( fReportState == true )
    {
        OM_TRACE1( OM_ETD_INFO, "AutoLock::do_unlock() ==> Mutex was released - %s", strTag.c_str() );
    }
    m_pMutex = NULL;
    return (true);
}

/////////////////////////////////////////////////////////////////////////////

};  // namespace CExThreading



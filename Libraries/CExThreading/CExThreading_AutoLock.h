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
//      CExtend\Libraries\CExThreading\CExThreading_AutoLock.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_AutoLock_h
#define _CExThreading_AutoLock_h

namespace CExThreading
{

#if defined(CEXTEND_DEBUG)
    #define CEXTHREADING_AUTOLOCK( THEMUTEX )   CExThreading::AutoLock  __localMutexZone( __FILE__, __LINE__, THEMUTEX );
#else
    #define CEXTHREADING_AUTOLOCK( THEMUTEX )   CExThreading::AutoLock  __localMutexZone( THEMUTEX );
#endif

/////////////////////////////////////////////////////////////////////////////
//! AutoLock
//
//  :Description
//      This class is provided to aid in the use of the Mutex class.
//      Succesful instantiation of this class lock()'s the supplied
//      mutex.  When the AutoLock object is destroyed (such as when
//      the code exits the scope of execution it was declared in) then
//      the mutex is releas()'ed.
//
//      The calling code can use the is_locked() member function to
//      determine if the lock() occured succesfully at construct time.
//
//  :Member Variables
//      = Mutex *  m_pMutex
//          A pointer to the Mutex object supplied to the constructor.
//          The pointer is only stored if the lock() was succesful.
//
//  :Definition
//"
class AutoLock
{
    // Data Members
    private:
        Mutex *         m_pMutex;
        #if defined(CEXTEND_DEBUG)
            const char *    m_PszFile;
            size_t          m_LineNumber;
        #endif // defined(CEXTEND_DEBUG)

    // Construction
    public:
        AutoLock( Mutex *      pMutex,
                  WaitMode     waitMode = WaitMode_FOREVER,
                  WaitTime     waitTime = WaitTime_EMPTY );
        AutoLock( Mutex &      theMutex,
                  WaitMode     waitMode = WaitMode_FOREVER,
                  WaitTime     waitTime = WaitTime_EMPTY );
        #if defined(CEXTEND_DEBUG)
            AutoLock( const char *  pszFile,
                      size_t        lineNumber,
                      Mutex &       theMutex,
                      WaitMode      waitMode = WaitMode_FOREVER,
                      WaitTime      waitTime = WaitTime_EMPTY );
        #endif // defined(CEXTEND_DEBUG)
        ~AutoLock( void );

    // Public Interface
    public:
        bool    is_locked( void );

    // Private Interface
    private:
        bool    do_lock( WaitMode waitMode, WaitTime waitTime );
        bool    do_unlock( void );
};
//.


/////////////////////////////////////////////////////////////////////////////

};  // namespace CExThreading

#endif // _CExThreading_AutoLock_h


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
//      CExtend\Libraries\CExThreading\CExThreading_ThreadLaunch.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_ThreadLaunch_h
#define _CExThreading_ThreadLaunch_h

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! ThreadLaunch
//
//  :Definition
//"
class ThreadLaunch
{
    // Embedded Types
    public:
        typedef void (* PfnThreadFunction)( void * pData );


        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            typedef struct
            {
                HANDLE          m_hThread;
                DWORD           m_ThreadID;
            } ThreadInfoStruct;

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            typedef struct
            {
                pthread_t           m_ThreadId;
            } ThreadInfoStruct;

        #else
            #error "ERROR: Platform dependant code"
        #endif

    private:
        typedef struct
        {
            PfnThreadFunction   m_PfnActualFunction;
            void *              m_pData;
        } LaunchDataStruct;

    // Not Implemented, do not use
    private:
        ThreadLaunch( void );
        ThreadLaunch( const ThreadLaunch & rhSide );
        ~ThreadLaunch( void );
        const ThreadLaunch &  operator = ( const ThreadLaunch & rhSide );

    // Public Interface
    public:
        static  bool    launch( PfnThreadFunction pfnThreadFunction, void * pData );
        static  bool    launch( PfnThreadFunction   pfnThreadFunction,
                                void *              pData,
                                size_t              stackSize,
                                ThreadInfoStruct &  threadInfoStruct );

        static  void            threadinfostruct_clear( ThreadInfoStruct & threadInfoStruct );
        static  std::string     threadinfostruct_get_threadid_string( ThreadInfoStruct & threadInfoStruct );
        static  void            threadinfostruct_create_current( ThreadInfoStruct & threadInfoStruct );

        static  std::string     get_current_threadid_string( void );

        static  bool    kill( ThreadInfoStruct & threadInfoStruct );

    // Private Interface
    private:
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            static  DWORD  WINAPI win_thread_start( LPVOID lpParameter );
            //static void  __cdecl win_thread_start( void * );
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            static void *   linux_thread_start( void * pData );
        #else
            #error "ERROR: Platform dependant code"
        #endif

};
//.



};  // namespace CExThreading

#endif // _CExThreading_ThreadLaunch_h


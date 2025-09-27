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
//      CExtend\Libraries\CExThreading\CExThreading_SignalHandler.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_SignalHandler_h
#define _CExThreading_SignalHandler_h

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! SignalHandler
//
//  :Description
//

//  :Definition
//"
class SignalHandler
{
    // Embedded Types
    public:
        enum { ForceThreadStopTimeout = 5 };
        typedef  void (*  PfnSignalCallback)( SignalHandler & signalHandler, void * ptrDataEx, int sigCode );

        enum { KillCountDefaultLimit = 2 };

        enum OptValue
        {
            OptValue_DEFAULT    = 1,
            OptValue_ON         = 2,
            OptValue_OFF        = 3
        };

        typedef struct
        {
            OptValue    m_SetStopFlag;
            OptValue    m_TriggerThreadStop;
            Uint8       m_KillAfterThisManySignals;
            OptValue    m_AutoResetSignal;
        } OptionStruct;

    private:

        typedef std::set< Thread * >                    ThreadPtrSet;
        typedef std::map< PfnSignalCallback, void * >   PfnSignalCallbackMap;
        typedef struct
        {
            Uint32                  m_Counter;
            OptionStruct            m_OptionStruct;
            PfnSignalCallbackMap    m_PfnSignalCallbackMap;
        } SignalStruct;
        typedef std::map< int , SignalStruct >      SignalMap;

    // Data Members
    private:
        mutable CExThreading::Mutex    m_Mutex;

        ThreadPtrSet                m_ThreadPtrSet;

        SignalMap                   m_SignalMap;
        bool                        m_fStopped;
        bool                        m_fEnabled;

    // Construction
    //  Use the singleton() object to obtain instance
    protected:
        SignalHandler( void );
        ~SignalHandler( void );
    private:
        SignalHandler( const SignalHandler & rhSide );
        const SignalHandler &  operator = ( const SignalHandler & rhSide );

    // Public Interface
    public:
        static  SignalHandler &     singleton( void );

        void    clear( void );
        void    initialize( void );
        bool    empty( void ) const;

        bool    enable( void );
        bool    disable( void );
        bool    is_enabled( void ) const;

        bool    signal_set( int sigCode );
        bool    signal_set( int sigCode, const OptionStruct & optionStruct );
        bool    signal_remove( int sigCode );

        bool    thread_add( Thread & theThread );
        bool    thread_add( Thread * ptrThread );
        bool    thread_remove( Thread & theThread );
        bool    thread_remove( Thread * ptrThread );

        bool    callback_add( int sigCode, PfnSignalCallback pfnSignalCallback, void * ptrDataEx );
        bool    callback_remove( int sigCode, PfnSignalCallback pfnSignalCallback );

        const bool &    stop_trigger( void ) const;

        bool    get_signals( IntSet & sigCodeSet ) const;
        bool    get_active_signals( IntSet & sigCodeSet ) const;
        bool    get_signal_count( int sigCode, Uint32 & signalCount ) const;
        bool    get_signal_options( int sigCode, OptionStruct & optionStruct ) const;

    // Protected Interface
    protected:
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            static  void  __cdecl  signal_callback_mswin( int sigCode );
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            static  void      signal_callback_linux( int sigCode );
        #else
            #error "ERROR: This code is platform specific"
        #endif
        void    signal_handler( int sigCode );
        void    signal_processor( int sigCode, SignalStruct & globalSignalStruct, SignalStruct & curSignalStruct );

        OptionStruct    get_final_option_struct( OptionStruct & curOptions, OptionStruct & baseOptions );
        OptionStruct    get_global_default_option_struct( void ) const;
        OptionStruct    get_signal_default_option_struct( void ) const;
};
//.

}; // namespace CExThreading

#endif // _CExThreading_SignalHandler_h


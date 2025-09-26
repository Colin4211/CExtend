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
//      CExtend\Libraries\CExOutput\CExOutput_Manager.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_Manager_h
#define _CExOutput_Manager_h

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! Manager
//
//  :Description
//      The Manager object is a singleton object which dynamically loads
//      the OutputManagerManager and provides the interface to that
//      library.
//
//      By using this class to dynamically load the application you allow
//      the application to run even if the CExOutputManager object is
//      not present.
//
//  :Definition
//"
class Manager
{
    // Embedded Types
    public:
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            enum { MaxPathLength = _MAX_PATH };
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            enum { MaxPathLength = 1024 };
        #else
            #error "ERROR: This code is platform specific"
        #endif

    // Data Members
    private:
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            HMODULE      m_hWindowsHandle;
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            void *       m_hLinuxHandle;
        #else
            #error "ERROR: This code is platform specific"
        #endif

        char                         m_ModuleName[ MaxPathLength ];

        OM_PtrVerifyVersion          m_pfnVerifyVersion;
        OM_PtrGenerateOutputEvent    m_pfnGenerateOutputEvent;
        OM_PtrGetOutputEventCount    m_pfnGetOutputEventCount;
        OM_PtrGetOutputEvent         m_pfnGetOutputEvent;
        OM_PtrSetCallback            m_pfnSetCallback;
        OM_PtrRedirectOpen           m_pfnRedirectOpen;
        OM_PtrRedirectIsOpen         m_pfnRedirectIsOpen;
        OM_PtrRedirectClose          m_pfnRedirectClose;
        bool                         m_fAutoload;

    // Construction
    private:
        Manager( void );
        ~Manager( void );
    // Not Implemented, do not use
    private:
        Manager( const Manager & rhSide );
        const Manager &  operator = ( const Manager & rhSide );

    // Public Interface
    public:
        static  Manager &   singleton( void );

        bool    is_open( void ) const;
        bool    open_module( void );
        bool    open_module_by_name( const char * pszFileName );

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            bool    open_module_by_handle( HINSTANCE hManagerInstance );
        #endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        bool    open_module_by_funcptr( OM_PtrVerifyVersion        pfnVerifyVersion,
                                        OM_PtrGenerateOutputEvent  pfnGenerateOutputEvent,
                                        OM_PtrGetOutputEventCount  pfnGetOutputEventCount,
                                        OM_PtrGetOutputEvent       pfnGetOutputEvent,
                                        OM_PtrSetCallback          pfnSetCallback,
                                        OM_PtrRedirectOpen         pfnRedirectOpen,
                                        OM_PtrRedirectIsOpen       pfnRedirectIsOpen,
                                        OM_PtrRedirectClose        pfnRedirectClose );
        void            close_module( void );
        const char *    get_module_name( void ) const;
        bool            get_full_module_file_name( char * pszBuff, size_t buffLen );

        void    generate_output_event( OM_EventType   eventType,
                                       const char *   sourceFile,
                                       Uint32         sourceLine,
                                       const char *   scopeName,
                                       const char *   eventStr );
        void    generate_output_event_va( OM_EventType   eventType,
                                          const char *   sourceFile,
                                          Uint32         sourceLine,
                                          const char *   scopeName,
                                          const char *   eventStrFmt, ... );

        int     get_output_event_count( void );
        bool    get_output_event( OM_OutputEvent & outputEvent );
        void    set_callback( OM_pfnNotifyProc pfnNotify );

        bool    redirect_open( OM_RedirectType reType, const char * openStr );
        bool    redirect_is_open( OM_RedirectType reType );
        bool    redirect_close( OM_RedirectType reType );

        void    system_error_event( const char *    sourceFile,
                                    Uint32          sourceLine,
                                    const char *    scopeName,
                                    const char *    outMsg,
                                    Uint32          sysErr );

        void    set_autoload( bool fAutoload );

        void    get_system_error_string( Uint32 sysErr, std::string & sysErrStr );

    // Private Interface
    private:
        void     perform_autoload( void );
};
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput

#endif // _CExOutput_Manager_h


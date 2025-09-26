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
//      CExtend\Libraries\CExOutput\CExOutput_Manager.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//      <DT_SUB_TOPIC> Manager
//
/////////////////////////////////////////////////////////////////////////////

#include "CExOutput.h"

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    // nothing to include
#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    #include <dlfcn.h>
    #include <link.h>
#else
    #error "ERROR: This code is platform specific"
#endif

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! Manager( void )
//
//  :Implementation
//"
Manager::Manager( void )
{
    //printf( "CExOutput --> Manager active\n");

    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        m_hWindowsHandle     = NULL;
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        m_hLinuxHandle       = NULL;
    #else
        #error "ERROR: This code is platform specific"
    #endif

    m_ModuleName[ 0 ] = 0;
    memset( &m_ModuleName, 0, sizeof(m_ModuleName) );

    m_pfnVerifyVersion          = NULL;
    m_pfnGenerateOutputEvent    = NULL;
    m_pfnGetOutputEventCount    = NULL;
    m_pfnGetOutputEvent         = NULL;
    m_pfnSetCallback            = NULL;
    m_pfnRedirectOpen           = NULL;
    m_pfnRedirectIsOpen         = NULL;
    m_pfnRedirectClose          = NULL;
    m_fAutoload                 = true;

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~Manager( void )
//
//  :Implementation
//"
Manager::~Manager( void )
{
    close_module();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  Manager &   singleton( void )
//
//  :Implementation
//"
Manager &  Manager::singleton( void )
{
    static Manager theOneAndOnly;
    return (theOneAndOnly);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  is_open( void ) const
//
//  :Returns
//      If there is an CExOutputManager open the function returns
//      true.  Otherwise the function returns false.
//
//  :Implementation
//"
bool  Manager::is_open( void ) const
{
    bool fResult = false;
    try
    {
        if ( (m_pfnVerifyVersion       == NULL) ||
             (m_pfnGenerateOutputEvent == NULL) ||
             (m_pfnGetOutputEventCount == NULL) ||
             (m_pfnGetOutputEvent      == NULL) ||
             (m_pfnSetCallback         == NULL) ||
             (m_pfnRedirectOpen        == NULL) ||
             (m_pfnRedirectIsOpen      == NULL) ||
             (m_pfnRedirectClose       == NULL) )
        {
            fResult = (false);
        }
        else
        {
            fResult = (true);
        }
    }
    catch ( ... )
    {
        fResult = (false);
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  open_module( void )
//
//  :Implementation
//"
bool  Manager::open_module( void )
{
    //printf( "CExOutput::Manager::open_module() ==> Called\n" );
    if ( is_open() == true )
    {
        return (true);
    }

    //////////////////////

    char    baseNameBuffer[256];
    //sprintf( baseNameBuffer, "CExOutput_Module_v%d_%d_", (int)(OM_INTERFACE_VERSION_MAJOR), (int)(OM_INTERFACE_VERSION_MINOR) );
    sprintf( baseNameBuffer, "CExOutputModule_" );
    std::string baseName = baseNameBuffer;

    //printf( "CExOutput::Manager::open_module() ==> baseName -->%s<--\n", baseName.c_str() );

    //////////////////////

    std::string     appPath;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        char            appName[ 1024 ];
        if ( ::GetModuleFileNameA( NULL, appName, sizeof(appName)-1 ) != 0 )
        {
            appName[ sizeof(appName)-1 ] = 0;
            std::string             workStr     = appName;
            std::string::size_type  slashPos    = workStr.find_last_of( "\\/" );
            if ( slashPos != std::string::npos )
            {
                appPath = workStr.substr( 0, slashPos+1 );
            }
        }

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        pid_t           curPid          = getpid();
        char            linkName[ 64 ];
        const size_t    procDataSize    = 4096;
        char            procDataBuffer[ procDataSize ];
        sprintf( linkName, "/proc/%lu/exe", (unsigned long)curPid );
        char *          ptrProcDataStr  = static_cast< char * > ( &procDataBuffer[0] );

        if ( ptrProcDataStr != NULL )
        {
            ssize_t rlRes = readlink( linkName,
                                      ptrProcDataStr,
                                      procDataSize-1 );
            if ( rlRes >= 1 )
            {
                ptrProcDataStr[ rlRes ] = 0;
                std::string  workStr = ptrProcDataStr;
                std::string::size_type  slashPos    = workStr.find_last_of( "\\/" );
                if ( slashPos != std::string::npos )
                {
                    appPath = workStr.substr( 0, slashPos+1 );
                }
            }
        }

    #else

        #error "ERROR: This code is platform specific"

    #endif

    //////////////////////

    StringList  moduleList;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        #if defined(CEXTEND_PLATFORM_TYPE_MSWIN_I32)
            std::string     titleDebug      = baseName + "Win32_d.dll";
            std::string     titleRelease    = baseName + "Win32.dll";
        #elif defined(CEXTEND_PLATFORM_TYPE_MSWIN_I64)
            std::string     titleDebug      = baseName + "Win64_d.dll";
            std::string     titleRelease    = baseName + "Win64.dll";
        #else
            #error "ERROR: This code is platform specific"
        #endif

        if ( appPath.empty() == false )
        {
            moduleList.push_back( appPath + titleDebug );
            moduleList.push_back( appPath + titleRelease );
        }

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        #if defined(CEXTEND_PLATFORM_TYPE_LINUX_I32)
            std::string     titleDebug      = baseName + "LinuxI32_d.so";
            std::string     titleRelease    = baseName + "LinuxI32.so";
        #elif defined(CEXTEND_PLATFORM_TYPE_LINUX_I64)
            std::string     titleDebug      = baseName + "LinuxI64_d.so";
            std::string     titleRelease    = baseName + "LinuxI64.so";
        #elif defined(CEXTEND_PLATFORM_TYPE_LINUX_ARM32)
            std::string     titleDebug      = baseName + "LinuxARM_d.so";
            std::string     titleRelease    = baseName + "LinuxARM.so";
        #elif defined(CEXTEND_PLATFORM_TYPE_LINUX_ARM64)
            std::string     titleDebug      = baseName + "Generic_d.so";
            std::string     titleRelease    = baseName + "Generic.so";
        #else
            #error "ERROR: This code is platform specific"
        #endif

        if ( appPath.empty() == false )
        {
            moduleList.push_back( appPath + titleDebug );
            moduleList.push_back( appPath + titleRelease );
        }

    #else
        #error "ERROR: This code is platform specific"
    #endif

    //////////////////////

    //printf( "open_module(%p) --> %s\n", this, "trying" );

    StringList::const_iterator  iterWalk = moduleList.begin();
    StringList::const_iterator  iterEol  = moduleList.end();
    while ( iterWalk != iterEol )
    {
        const std::string & moduleName = (*iterWalk);
        #if defined(CEXTEND_DEBUG)
            //printf( "CExOutput::Manager::open_module(%p) ==> Trying --> %s \n", this,moduleName.c_str() );
        #endif // defined(CEXTEND_DEBUG)
        if ( open_module_by_name( moduleName.c_str() ) == true )
        {
            #if defined(CEXTEND_DEBUG)
                //printf( "CExOutput::Manager::open_module(%p) ==> Loaded --> %s \n", this, moduleName.c_str() );
            #endif // defined(CEXTEND_DEBUG)
            return (true);
        }
        iterWalk++;
    }

    return (false);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  open_module_by_name( const char * )
//
//  :Arguments
//      = const char * pszManagerName
//          The name of the module to open.  A NULL or empty string
//          is permissible for this argument.
//
//  :Returns
//      If the module is succesfully opened the function returns true.
//      Otherwise the function returns false and the Manager is in the
//      closed state.
//
//  :Implementation
//"
bool  Manager::open_module_by_name( const char * pszManagerName )
{
    //printf( "Manager::open_module_by_name() ==> Called - %s\n", pszManagerName );
    if ( pszManagerName == NULL )
    {
        return (false);
    }
    if ( pszManagerName[0] == 0 )
    {
        return (false);
    }
    if ( is_open() == true )
    {
        close_module();
    }

    bool  fResult = false;
    try
    {
        strncpy( m_ModuleName, pszManagerName, sizeof(m_ModuleName)-1 );
        m_ModuleName[ sizeof(m_ModuleName)-1 ] = 0;

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            m_hWindowsHandle = ::LoadLibraryA( m_ModuleName );
            if (m_hWindowsHandle != NULL )
            {
                HINSTANCE hInstance = (HINSTANCE)m_hWindowsHandle;
                m_pfnVerifyVersion          = (OM_PtrVerifyVersion)      ::GetProcAddress(hInstance,"OM_VerifyVersion");
                m_pfnGenerateOutputEvent    = (OM_PtrGenerateOutputEvent)::GetProcAddress(hInstance,"OM_GenerateOutputEvent");
                m_pfnGetOutputEventCount    = (OM_PtrGetOutputEventCount)::GetProcAddress(hInstance,"OM_GetOutputEventCount");
                m_pfnGetOutputEvent         = (OM_PtrGetOutputEvent)     ::GetProcAddress(hInstance,"OM_GetOutputEvent");
                m_pfnSetCallback            = (OM_PtrSetCallback)        ::GetProcAddress(hInstance,"OM_SetCallback");
                m_pfnRedirectOpen           = (OM_PtrRedirectOpen)       ::GetProcAddress(hInstance,"OM_RedirectOpen");
                m_pfnRedirectIsOpen         = (OM_PtrRedirectIsOpen)     ::GetProcAddress(hInstance,"OM_RedirectIsOpen");
                m_pfnRedirectClose          = (OM_PtrRedirectClose)      ::GetProcAddress(hInstance,"OM_RedirectClose");
                if ( (m_pfnVerifyVersion       != NULL) &&
                     (m_pfnGenerateOutputEvent != NULL) &&
                     (m_pfnGetOutputEventCount != NULL) &&
                     (m_pfnGetOutputEvent      != NULL) &&
                     (m_pfnSetCallback         != NULL) &&
                     (m_pfnRedirectOpen        != NULL) &&
                     (m_pfnRedirectIsOpen      != NULL) &&
                     (m_pfnRedirectClose       != NULL) )
                {
                    if ( (*m_pfnVerifyVersion)(OM_INTERFACE_VERSION) == OM_Result_OK )
                    {
                        fResult = true;
                    }
                }
                else
                {
                    ::FreeLibrary( m_hWindowsHandle );
                    m_hWindowsHandle = NULL;
                    m_ModuleName[0] = 0;
                    fResult = false;
                }
            }
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            m_hLinuxHandle = ::dlopen( m_ModuleName, RTLD_NOW|RTLD_LOCAL|RTLD_DEEPBIND );
            if (m_hLinuxHandle != NULL )
            {
                void *  hLibrary = (void *)m_hLinuxHandle;
                m_pfnVerifyVersion          = (OM_PtrVerifyVersion)      ::dlsym(hLibrary,"OM_VerifyVersion");
                m_pfnGenerateOutputEvent    = (OM_PtrGenerateOutputEvent)::dlsym(hLibrary,"OM_GenerateOutputEvent");
                m_pfnGetOutputEventCount    = (OM_PtrGetOutputEventCount)::dlsym(hLibrary,"OM_GetOutputEventCount");
                m_pfnGetOutputEvent         = (OM_PtrGetOutputEvent)     ::dlsym(hLibrary,"OM_GetOutputEvent");
                m_pfnSetCallback            = (OM_PtrSetCallback)        ::dlsym(hLibrary,"OM_SetCallback");
                m_pfnRedirectOpen           = (OM_PtrRedirectOpen)       ::dlsym(hLibrary,"OM_RedirectOpen");
                m_pfnRedirectIsOpen         = (OM_PtrRedirectIsOpen)     ::dlsym(hLibrary,"OM_RedirectIsOpen");
                m_pfnRedirectClose          = (OM_PtrRedirectClose)      ::dlsym(hLibrary,"OM_RedirectClose");
                if ( (m_pfnVerifyVersion       != NULL) &&
                     (m_pfnGenerateOutputEvent != NULL) &&
                     (m_pfnGetOutputEventCount != NULL) &&
                     (m_pfnGetOutputEvent      != NULL) &&
                     (m_pfnSetCallback         != NULL) &&
                     (m_pfnRedirectOpen        != NULL) &&
                     (m_pfnRedirectIsOpen      != NULL) &&
                     (m_pfnRedirectClose       != NULL) )
                {
                    if ( (*m_pfnVerifyVersion)(OM_INTERFACE_VERSION) == OM_Result_OK )
                    {
                        fResult = true;
                    }
                }
                else
                {
                    //printf( "Manager::open_module_by_name() ==> dlsym() Failed - %s\n", pszManagerName );
                    ::dlclose( m_hLinuxHandle );
                    m_hLinuxHandle = NULL;
                    m_ModuleName[0] = 0;
                    fResult = false;
                }
            }
            else
            {
                //printf( "Manager::open_module_by_name() ==> dlopen() Failed - %s\n", pszManagerName );
                //printf( "Manager::open_module_by_name() ==> dlopen() Failed - %s\n", dlerror() );
            }
        #else
            #error "ERROR: This code is platform specific"
        #endif
    }
    catch ( ... )
    {
        fResult = false;
    }

    if ( fResult == false )
    {
        close_module();
    }

    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  open_module_by_handle( HINSTANCE )
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    bool  Manager::open_module_by_handle( HINSTANCE hManagerInstance )
    {
        bool  fResult = false;

        try
        {
            m_fAutoload = false;

            close_module();

            if ( hManagerInstance == NULL )
            {
                fResult = false;
            }
            else
            {
                m_ModuleName[0] = 0;
                m_pfnVerifyVersion          = (OM_PtrVerifyVersion)      ::GetProcAddress(hManagerInstance,"OM_VerifyVersion");
                m_pfnGenerateOutputEvent    = (OM_PtrGenerateOutputEvent)::GetProcAddress(hManagerInstance,"OM_GenerateOutputEvent");
                m_pfnGetOutputEventCount    = (OM_PtrGetOutputEventCount)::GetProcAddress(hManagerInstance,"OM_GetOutputEventCount");
                m_pfnGetOutputEvent         = (OM_PtrGetOutputEvent)     ::GetProcAddress(hManagerInstance,"OM_GetOutputEvent");
                m_pfnSetCallback            = (OM_PtrSetCallback)        ::GetProcAddress(hManagerInstance,"OM_SetCallback");
                m_pfnRedirectOpen           = (OM_PtrRedirectOpen)       ::GetProcAddress(hManagerInstance,"OM_RedirectOpen");
                m_pfnRedirectIsOpen         = (OM_PtrRedirectIsOpen)     ::GetProcAddress(hManagerInstance,"OM_RedirectIsOpen");
                m_pfnRedirectClose          = (OM_PtrRedirectClose)      ::GetProcAddress(hManagerInstance,"OM_RedirectClose");
                if ( (m_pfnVerifyVersion       != NULL) &&
                    (m_pfnGenerateOutputEvent != NULL) &&
                    (m_pfnGetOutputEventCount != NULL) &&
                    (m_pfnGetOutputEvent      != NULL) &&
                    (m_pfnSetCallback         != NULL) &&
                    (m_pfnRedirectOpen        != NULL) &&
                    (m_pfnRedirectIsOpen      != NULL) &&
                    (m_pfnRedirectClose       != NULL) )
                {
                    m_hWindowsHandle = hManagerInstance;
                    if ( (*m_pfnVerifyVersion)(OM_INTERFACE_VERSION) == OM_Result_OK )
                    {
                        fResult = true;
                    }
                }
            }
        }
        catch ( ... )
        {
            fResult = false;
        }

        if ( fResult == false )
        {
            close_module();
        }

        return (fResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  open_module_by_funcptr( ... )
//
//  :Implementation
//"
bool  Manager::open_module_by_funcptr( OM_PtrVerifyVersion        pfnVerifyVersion,
                                       OM_PtrGenerateOutputEvent  pfnGenerateOutputEvent,
                                       OM_PtrGetOutputEventCount  pfnGetOutputEventCount,
                                       OM_PtrGetOutputEvent       pfnGetOutputEvent,
                                       OM_PtrSetCallback          pfnSetCallback,
                                       OM_PtrRedirectOpen         pfnRedirectOpen,
                                       OM_PtrRedirectIsOpen       pfnRedirectIsOpen,
                                       OM_PtrRedirectClose        pfnRedirectClose )
{
    bool fResult = false;

    try
    {
        close_module();
        m_pfnVerifyVersion          = pfnVerifyVersion;
        m_pfnGenerateOutputEvent    = pfnGenerateOutputEvent;
        m_pfnGetOutputEventCount    = pfnGetOutputEventCount;
        m_pfnGetOutputEvent         = pfnGetOutputEvent;
        m_pfnSetCallback            = pfnSetCallback;
        m_pfnRedirectOpen           = pfnRedirectOpen;
        m_pfnRedirectIsOpen         = pfnRedirectIsOpen;
        m_pfnRedirectClose          = pfnRedirectClose;
        if ( (m_pfnVerifyVersion       != NULL) &&
             (m_pfnGenerateOutputEvent != NULL) &&
             (m_pfnGetOutputEventCount != NULL) &&
             (m_pfnGetOutputEvent      != NULL) &&
             (m_pfnSetCallback         != NULL) &&
             (m_pfnRedirectOpen        != NULL) &&
             (m_pfnRedirectIsOpen      != NULL) &&
             (m_pfnRedirectClose       != NULL) )
        {
            if ( (*m_pfnVerifyVersion)(OM_INTERFACE_VERSION) == OM_Result_OK )
            {
                fResult = true;
            }
        }
    }
    catch ( ... )
    {
        fResult = false;
    }

    if ( fResult == false )
    {
        close_module();
    }

    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  close_module( void )
//
//  :Description
//      This function is used to close the currently open
//      CExOutputManager.  When this function returns the Manager is in
//      the closed state.
//
//  :Implementation
//"
void  Manager::close_module( void )
{
    // First we NULL all the function pointers
    m_ModuleName[ 0 ]           = 0;
    m_pfnVerifyVersion          = NULL;
    m_pfnGenerateOutputEvent    = NULL;
    m_pfnGetOutputEventCount    = NULL;
    m_pfnGetOutputEvent         = NULL;
    m_pfnSetCallback            = NULL;
    m_pfnRedirectOpen           = NULL;
    m_pfnRedirectIsOpen         = NULL;
    m_pfnRedirectClose          = NULL;

    // Now we perform the close
    try
    {
        m_fAutoload = false;

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            if ( (m_hWindowsHandle != NULL)    &&
                 (m_ModuleName[0] != 0) )
            {
                ::FreeLibrary( (HINSTANCE)(m_hWindowsHandle) );
            }
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            m_hLinuxHandle = NULL;
            if ( (m_hLinuxHandle != NULL)    &&
                 (m_ModuleName[0] != 0) )
            {
                ::dlclose( m_hLinuxHandle );
            }
            m_hLinuxHandle = NULL;
        #else
            #error "ERROR: This code is platform specific"
        #endif
    }
    catch( ... )
    {
        // Do Nothing
    }

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static const char * get_module_name( void ) const
//
//  :Implementation
//"
const char *  Manager::get_module_name( void ) const
{
    return (m_ModuleName);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  get_full_module_file_name( char *, int )
//
//  :Description
//      This function returns the full filename of the module that is
//      currently loaded (if possible).
//
//      NOTE:   Under linux this is not possible.  The name returned will
//              likely be the name supplied when the module was loaded.
//              This is due to the fact that there is no reliable
//              equivilant of the GetModuleFileName() under linux.
//
//  :Implementation
//"
bool  Manager::get_full_module_file_name( char * pszBuff, size_t buffLen )
{
    if ( (pszBuff == NULL) || (buffLen < 2) )
    {
        return (false);
    }
    bool fResult = false;
    try
    {
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            if ( m_hWindowsHandle == NULL )
            {
                return (false);
            }
            DWORD dwRes = ::GetModuleFileNameA( m_hWindowsHandle, pszBuff, (DWORD)buffLen );
            if (dwRes == 0)
            {
                return (false);
            }
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            struct link_map * pLinkMap = NULL;
            if ( dlinfo( m_hLinuxHandle, RTLD_DI_LINKMAP, &pLinkMap ) == -1 )
            {
                return (false);
            }
            if ( pLinkMap == NULL )
            {
                return (false);
            }
            if ( pLinkMap->l_name == NULL )
            {
                return (false);
            }
            strncpy( pszBuff, pLinkMap->l_name, buffLen-1 );
            pszBuff[ buffLen-1 ] = 0;
        #else
            #error "ERROR: This code is platform specific"
        #endif
    }
    catch ( ... )
    {
        fResult = false;
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  generate_output_event( OM_EventType, const char *, Uint32, const char * )
//
//  :Arguments
//      = OM_EventType  eventType
//          The event type for this event.
//      = const char *  sourceFile
//          The name of the source file in which the event was generated.
//      = unsigned long  sourceLine
//          The line number in the source file from where the event was
//          generated.
//      = const char *  eventStr
//          The message string to associate with this output event.
//
//  :Description
//      This function routes the generate_output_event() function call
//      to the currently open CExOutputManager for processing.
//
//      If there is no module currently open then the function simply
//      returns and the event is not captured.
//
//  :Implementation
//"
void  Manager::generate_output_event( OM_EventType   eventType,
                                      const char *   sourceFile,
                                      Uint32         sourceLine,
                                      const char *   scopeName,
                                      const char *   eventStr )
{
    try
    {
        perform_autoload();
        if ( is_open() == true )
        {
            if ( m_pfnGenerateOutputEvent != NULL )
            {
                (*m_pfnGenerateOutputEvent)( eventType,
                                             sourceFile,
                                             sourceLine,
                                             scopeName,
                                             eventStr );
            }
        }
        //else if ( m_fEnableLocal == true )
        //{
            //Console::print_event( "Output: ",
                                  //eventType,
                                  //NULL, //sourceFile,
                                  //0, // sourceLine,
                                  //scopeName,
                                  //eventStr );

        //}
    }
    catch ( ... )
    {
        //printf( "Manager::generate_output_event() ==> Caught exception\n" );
        // Do nothing
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  generate_output_event_va( OM_EventType, const char *, Uint32, const char *, ... )
//
//  :Arguments
//      = OM_EventType  eventType
//          The event type for this event.
//      = const char *  sourceFile
//          The name of the source file in which the event was generated.
//      = unsigned long  sourceLine
//          The line number in the source file from where the event was
//          generated.
//      = const char *  eventStrFmt, ...
//          The sprintf compatible format string and associated arguments
//          which form the string to associate with this output event.
//
//  :Description
//      This function routes the generate_output_event() function call
//      to the currently open CExOutputManager for processing.
//
//      If there is no module currently open then the function simply
//      returns and the event is not captured.
//
//  :Implementation
//"
void  Manager::generate_output_event_va( OM_EventType   eventType,
                                         const char *   sourceFile,
                                         Uint32         sourceLine,
                                         const char *   scopeName,
                                         const char *   eventStrFmt, ... )
{
    try
    {

        char eventStr[ OM_MAX_EVENT_STRING_LENGTH ];
        va_list argList;
        va_start( argList, eventStrFmt );

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            _vsnprintf( eventStr, OM_MAX_EVENT_STRING_LENGTH-1, eventStrFmt, argList );
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            vsnprintf( eventStr, OM_MAX_EVENT_STRING_LENGTH-1, eventStrFmt, argList );
        #else
            #error "ERROR: This code is platform specific"
        #endif

        eventStr[ OM_MAX_EVENT_STRING_LENGTH-1 ] = 0;
        va_end( argList );

        // Call the non-va version
        generate_output_event( eventType, sourceFile, sourceLine, scopeName, eventStr );
    }
    catch ( ... )
    {
        // Do Nothing
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! int  get_output_event_count( void )
//
//  :Returns
//      The function returns the number of output events currently
//      stored in the queue.  On failure the function returns (-1).
//
//  :Description
//      This function routes the get_output_event_count() function call
//      to the currently open CExOutputManager for processing.
//
//      If there is no module currently open then the function simply
//      returns (-1) to indicate failure.
//
//  :Implementation
//"
int  Manager::get_output_event_count( void )
{
    int resultVal = (-1);
    try
    {
        perform_autoload();
        if ( is_open() == true )
        {
            if ( m_pfnGetOutputEventCount != NULL )
            {
                Uint32  getCount = 0;
                if ( (*m_pfnGetOutputEventCount)(&getCount) == OM_Result_OK )
                {
                    resultVal = (int)(getCount);
                }
            }
        }
    }
    catch ( ... )
    {
        resultVal = (-1);
    }
    return (resultVal);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  get_output_event( OM_OutputEvent & )
//
//  :Arguments
//      = OM_OutputEvent &  outputEvent
//          A reference to a caller supplied OM_OutputEvent which will
//          receive the output event.
//
//  :Returns
//      On success the function returns true and fills the provided
//      OM_EventPacket with the event packet removed from the top of the
//      internal event queue.
//
//      On failure the function returns false.
//
//  :Description
//      This function routes the get_output_event() function call
//      to the currently open CExOutputManager for processing.
//
//      If there is no module currently open then the function simply
//      returns (0) to indicate failure.
//
//  :Implementation
//"
bool  Manager::get_output_event( OM_OutputEvent & outputEvent )
{
    bool fResult = false;
    try
    {
        perform_autoload();
        if ( is_open() == true )
        {
            if ( m_pfnGetOutputEvent != NULL )
            {
                OM_Result omResult = (*m_pfnGetOutputEvent)( &outputEvent,
                                                            sizeof(OM_OutputEvent) );
                fResult = (omResult == OM_Result_OK);
            }
        }
    }
    catch ( ... )
    {
        fResult = false;
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  set_callback( OM_pfnNotifyProc )
//
//  :Arguments
//      = OM_pfnNotifyProc  pfnNotify
//          A pointer to a caller supplied callback function.
//
//  :Description
//      This function routes the set_callback() function call
//      to the currently open CExOutputManager for processing.
//
//      If there is no module currently open then the function does
//      nothing.
//
//  :Implementation
//"
void  Manager::set_callback( OM_pfnNotifyProc pfnNotify )
{
    try
    {
        perform_autoload();
        if ( is_open() == true )
        {
            if ( m_pfnSetCallback != NULL )
            {
                (*m_pfnSetCallback)( pfnNotify );
            }
        }
    }
    catch ( ... )
    {
        // Do Nothing
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  redirect_open( OM_RedirectType, const char * )
//
//  :Implementation
//"
bool  Manager::redirect_open( OM_RedirectType reType, const char * openStr )
{
    bool fResult = false;
    try
    {
        perform_autoload();
        if ( is_open() == true )
        {
            if ( m_pfnRedirectOpen != NULL )
            {
                OM_Result omResult = (*m_pfnRedirectOpen)( reType, openStr );
                fResult = (omResult == OM_Result_OK);
            }
        }
    }
    catch ( ... )
    {
        fResult = false;
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  redirect_is_open( OM_RedirectType )
//
//  :Implementation
//"
bool  Manager::redirect_is_open( OM_RedirectType reType )
{
    bool fResult = false;
    try
    {
        perform_autoload();
        if ( is_open() == true )
        {
            if ( m_pfnRedirectIsOpen != NULL )
            {
                OM_Result omResult = (*m_pfnRedirectIsOpen)( reType );
                fResult = (omResult == OM_Result_OK);
            }
        }
    }
    catch ( ... )
    {
        fResult = false;
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  redirect_close( OM_RedirectType )
//
//  :Implementation
//"
bool  Manager::redirect_close( OM_RedirectType reType )
{
    bool fResult = false;
    try
    {
        perform_autoload();
        if ( is_open() == true )
        {
            if ( m_pfnRedirectClose != NULL )
            {
                OM_Result omResult = (*m_pfnRedirectClose)( reType );
                fResult = (omResult == OM_Result_OK);
            }
        }
    }
    catch ( ... )
    {
        fResult = false;
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  void  system_error_event( const char *, Uint32, const char *, Uint32 )
//
//  :Arguments
//      = const char *  sourceFile
//          The name of the source file in which the event was generated.
//      = unsigned long  sourceLine
//          The line number in the source file from where the event was
//          generated.
//      = const char *   outMsg
//          The output message to generate
//      = unsigned long  sysErr
//          The OS error code to be converted to a string
//
//  :Description
//      This function generates an OM_ETD_ERROR event.  It will take the
//      supplied sysErr and convert it to a string.  It will then append
//      that string to the end of the supplied outMsg and use
//      the resulting string to generate the output event.
//
//      The specific meaning and text for the system error codes is platform
//      specific
//
//  :Implementation
//"
void  Manager::system_error_event( const char *  sourceFile,
                                   Uint32        sourceLine,
                                   const char *  scopeName,
                                   const char *  outMsg,
                                   Uint32        sysErr )
{
    char    newEventText[ OM_MAX_EVENT_STRING_LENGTH ];
    newEventText[0] = 0;

    try
    {
        perform_autoload();

        std::string sysErrStr;
        get_system_error_string( sysErr, sysErrStr );

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            if ( outMsg != NULL )
            {
                _snprintf( newEventText,
                           OM_MAX_EVENT_STRING_LENGTH-1,
                           "%s --> SystemError(%lu) --> %s",
                           outMsg,
                           sysErr,
                           sysErrStr.c_str() );
            }
            else
            {
                _snprintf( newEventText,
                           OM_MAX_EVENT_STRING_LENGTH-1,
                           "SystemError(%lu) --> %s",
                           sysErr,
                           sysErrStr.c_str() );
            }
            newEventText[ OM_MAX_EVENT_STRING_LENGTH-1 ] = 0;

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            if ( outMsg != NULL )
            {
                snprintf( newEventText,
                          OM_MAX_EVENT_STRING_LENGTH-1,
                          "%s --> SystemError(%lu) --> %s",
                          outMsg,
                          (unsigned long)sysErr,
                          sysErrStr.c_str() );
            }
            else
            {
                snprintf( newEventText,
                          OM_MAX_EVENT_STRING_LENGTH-1,
                          "SystemError(%lu) --> %s",
                          (unsigned long)sysErr,
                          sysErrStr.c_str() );
            }
            newEventText[ OM_MAX_EVENT_STRING_LENGTH-1 ] = 0;

        #else
            #error "ERROR: This code is platform specific"
        #endif
    }
    catch ( ... )
    {
        newEventText[0] = 0;
    }

    generate_output_event( OM_ETD_ERROR,
                           sourceFile,
                           sourceLine,
                           scopeName,
                           newEventText );
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  set_autoload( bool )
//
//  :Implementation
//"
void  Manager::set_autoload( bool fAutoload )
{
    //printf( "set_autoload(%p) --> %s\n", this, ((fAutoload==false)?"FALSE":"TRUE") );
    m_fAutoload = fAutoload;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  get_system_error_string( Uint32, std::string & )
//
//  :Description
//      This function will lookup the supplied error code and attempt
//      to generate the string equivilant of the error code.  That string
//      will be set into the supplied sysErrStr argument.
//
//  :Implementation
//"
void  Manager::get_system_error_string( Uint32 sysErr, std::string & sysErrStr )
{
    sysErrStr.clear();
    try
    {
        char    newEventText[ OM_MAX_EVENT_STRING_LENGTH ];
        newEventText[0] = 0;

        char    errNumString[ OM_MAX_EVENT_STRING_LENGTH ];
        errNumString[0] = 0;

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            _snprintf( errNumString, OM_MAX_EVENT_STRING_LENGTH-1, "{%lu}", (unsigned long)sysErr );

            // Now we build the system error message string, appending
            //  to the event text.  Once we are done this we
            //  free the message buffer.
            LPVOID  lpMsgBuf;
            DWORD   dwFlags = ( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                FORMAT_MESSAGE_FROM_SYSTEM |
                                FORMAT_MESSAGE_IGNORE_INSERTS );
            DWORD   langID  = MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT );
            ::FormatMessageA( dwFlags, NULL, sysErr, langID, (LPSTR)&lpMsgBuf, 0, NULL );

            if ( lpMsgBuf != NULL )
            {
                strncpy( newEventText, (const char *)lpMsgBuf, OM_MAX_EVENT_STRING_LENGTH-1 );
                LocalFree( lpMsgBuf );
            }

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            snprintf( errNumString, OM_MAX_EVENT_STRING_LENGTH-1, "{%lu}", (unsigned long)sysErr );

            char * ptrResult = strerror_r( sysErr, newEventText, OM_MAX_EVENT_STRING_LENGTH-1 );
            newEventText[ OM_MAX_EVENT_STRING_LENGTH-1 ] = 0;
            if ( ptrResult != &(newEventText[0]) )
            {
                strncpy( newEventText, ptrResult, OM_MAX_EVENT_STRING_LENGTH-1 );
                newEventText[ OM_MAX_EVENT_STRING_LENGTH-1 ] = 0;
            }
            else
            {
                newEventText[ OM_MAX_EVENT_STRING_LENGTH-1 ] = 0;
            }

        #else
            #error "ERROR: This code is platform specific"
        #endif

        // Make sure there are no special characters in the string
        //  (CR's, LF's tabs etc.)
        for ( size_t strPos = 0; strPos < OM_MAX_EVENT_STRING_LENGTH; strPos++ )
        {
            if ( newEventText[strPos] == 0 )
            {
                break;
            }
            else if ( (newEventText[strPos] == 127) ||
                      (newEventText[strPos] < 32)   )
            {
                newEventText[strPos] = ' ';
            }
        }

        newEventText[ OM_MAX_EVENT_STRING_LENGTH-1 ] = 0;
        errNumString[ OM_MAX_EVENT_STRING_LENGTH-1 ] = 0;
        sysErrStr = newEventText;
        if ( sysErrStr.empty() == true )
        {
            sysErrStr = errNumString;
        }
    }
    catch ( ... )
    {
        sysErrStr.clear();
    }

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  perform_autoload( void )
//
//  :Implementation
//"
void  Manager::perform_autoload( void )
{
    if ( m_fAutoload == false )
    {
        return;
    }
    //printf( "perform_autoload(%p) --> %s\n", this, "trying" );
    m_fAutoload = false;
    if ( is_open() == true )
    {
        return;
    }
    open_module();
    return;
}
//.

}; // namespace CExOutput


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
//      CExtend\Libraries\CExThreading\CExThreading_ObjectIdent.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//      <DT_SUB_TOPIC> ObjectIdent
//
/////////////////////////////////////////////////////////////////////////////

#include "CExThreading.h"

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! ObjectIdent( void )
//
//  :Description
//      This is the default constructor for the ObjectIndent class.  It
//      creates the object in the empty state.
//
//  :Implementation
//"
ObjectIdent::ObjectIdent( void )
{
    platformstruct_clear();
    clear();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ObjectIdent( const ObjectIdent & )
//
//  :Description
//      This is the copy constructor for the ObjectIdent class.  It will
//      create the new object as an exact duplicate of the supplied
//      object.
//
//  :Implementation
//"
ObjectIdent::ObjectIdent( const ObjectIdent & rhSide )
{
    platformstruct_clear();
    (*this) = rhSide;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~ObjectIdent( void )
//
//  :Description
//      This is the destructor for the ObjectIdent class.
//
//  :Implementation
//"
ObjectIdent::~ObjectIdent( void )
{
    clear();
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const ObjectIdent & operator = ( const ObjectIdent & )
//
//  :Description
//      This is the copy operator for the ObjectIdent class.  It will
//      copy the contents of the supplied object into the current
//      object.
//
//  :Implementation
//"
const ObjectIdent &  ObjectIdent::operator = ( const ObjectIdent & rhSide )
{
    if ( this != &rhSide )
    {
        clear();

        m_ObjectStyle   = rhSide.m_ObjectStyle;
        m_ObjectType    = rhSide.m_ObjectType;
        strncpy( m_Name, rhSide.m_Name, MaxNameLength-1 );
        m_Name[ MaxNameLength-1 ] = 0;
        strncpy( m_SystemName, rhSide.m_SystemName, MaxNameLength-1 );
        m_SystemName[ MaxNameLength-1 ] = 0;
        m_fReportState  = rhSide.m_fReportState;
        m_fCreated      = rhSide.m_fCreated;
    }
    return (*this);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  clear( void )
//
//  :Description
//      This function clears the contents of the ObjectIdent class
//      and returns it to the empty state.
//
//  :Implementation
//"
void  ObjectIdent::clear( void )
{
    platformstruct_destroy();

    m_ObjectStyle   = ObjectStyle_ERROR;
    m_ObjectType    = ObjectType_ERROR;
    memset( m_Name, 0, MaxNameLength );
    memset( m_SystemName, 0, MaxNameLength );
    m_fReportState  = false;
    m_fCreated      = false;

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  empty( void ) const
//
//  :Returns
//      If the current object is empty the function returns true.
//      Otherwise the function returns false to indicate that the
//      object contains valid information.
//
//  :Implementation
//"
bool  ObjectIdent::empty( void ) const
{
    return ( m_ObjectStyle == ObjectStyle_ERROR );
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ObjectStyle  object_style( void ) const
//
//  :Returns
//      This function returns the Style attribute associated with
//      the current ObjectIdent.
//
//  :Implementation
//"
ObjectStyle  ObjectIdent::object_style( void ) const
{
    return (m_ObjectStyle);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ObjectType  object_type( void ) const
//
//  :Returns
//      This function returns the ObjectType attribute associated with
//      the current ObjectIdent.
//
//  :Implementation
//"
ObjectType  ObjectIdent::object_type( void ) const
{
    return (m_ObjectType);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const char *  name( void ) const
//
//  :Returns
//      A pointer to the name attribute assoicated with the
//      current ObjectIdent.
//
//  :Implementation
//"
const char *  ObjectIdent::name( void ) const
{
    return (m_Name);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! const char *  system_name( void ) const
//
//  :Returns
//      A pointer to the system name attribute assoicated with the
//      current ObjectIdent.
//
//  :Implementation
//"
const char *  ObjectIdent::system_name( void ) const
{
    return (m_SystemName);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  report_state_flag( void ) const
//
//  :Returns
//      This functon returns the report state flag attribute assoicated
//      with the current ObjectIdent.
//
//  :Implementation
//"
bool  ObjectIdent::report_state_flag( void ) const
{
    return (m_fReportState);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  created_flag( void ) const
//
//  :Returns
//      This functon returns the created flag attribute assoicated
//      with the current ObjectIdent.
//
//  :Implementation
//"
bool  ObjectIdent::created_flag( void ) const
{
    return (m_fCreated);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static const char *  objectstyle_to_string( ObjectStyle )
//
//  :Description
//      This function will return a pointer to a string representing
//      a text version of the supplied ObjectStyle.
//
//      If the supplied ObjectStyle is invalid then the function will
//      return a NULL pointer.  This behaviour can be used to determine
//      if a given ObjectStyle is valid, merely call this function
//      and check for a non-NULL result.
//
//  :Implementation
//"
const char *  ObjectIdent::objectstyle_to_string( ObjectStyle objectStyle )
{
    switch ( objectStyle )
    {
        case ObjectStyle_PROCESS:       return ("ObjectStyle_PROCESS");
        case ObjectStyle_SYSTEM:        return ("ObjectStyle_SYSTEM");
        default:
            break;
    }
    return (NULL);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static const char *  objecttype_to_string( ObjectType objectStyle )
//
//  :Description
//      This function will return a pointer to a string representing
//      a text version of the supplied ObjectStyle.
//
//      If the supplied ObjectStyle is invalid then the function will
//      return a NULL pointer.  This behaviour can be used to determine
//      if a given ObjectStyle is valid, merely call this function
//      and check for a non-NULL result.
//
//  :Implementation
//"
const char *  ObjectIdent::objecttype_to_string( ObjectType objectType )
{
    switch ( objectType )
    {
        case ObjectType_MUTEX:          return ("ObjectType_MUTEX");
        case ObjectType_EVENT:          return ("ObjectType_EVENT");
        case ObjectType_THREAD:         return ("ObjectType_THREAD");
        default:
            break;
    }
    return (NULL);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  initialize( ... )
//
//  :Arguments
//      = ObjectStyle  objectStyle
//          The style parameter that the controlling object
//          was created with.  If the calling object does not
//          support a given style then it is up to that object not
//          to supply the value to this function.
//      = ObjectType  objectType
//          The type of the object that this ObjectIdent is associated
//          with.  This info is used when auto-generating names
//      = const char *  pszName
//          The name of the object.  If this is NULL or an empty
//          string then the function will auto-generate a name.
//          This function will accept any NULL terminated string
//          up to MaxNameLength characters.
//      = bool fReportState
//          This flag is used to indicate if the controlling object
//          is to report state changes during operation.
//      = bool fCreated
//          This flag is used to indicate if the original object
//          was succesfully created.
//
//  :Description
//      This object is used to initialize an instance of ObjectIdent.
//
//  :Returns
//      If the object is succesfully initialized, then the function
//      returns true.  If the initialization fails the function
//      returns false and clears the object to the empty state.
//
//  :Implementation
//"
bool  ObjectIdent::initialize( ObjectStyle     objectStyle,
                               ObjectType      objectType,
                               const char *    pszName,
                               bool            fReportState,
                               bool            fCreated )
{
    // Perform an initial clear so we know everything is
    //  in a sane state.
    clear();

    // Assume true, flip to false if any problems occur,
    //  then at the end if its false, clear the object and
    //  return failure.
    bool fResult = true;
    try
    {
        // Store the style style_to_string
        fResult &= ( objectstyle_to_string(objectStyle) != NULL );
        m_ObjectStyle = objectStyle;

        // Store the ObjectType
        fResult &= ( objecttype_to_string(objectType) != NULL );
        m_ObjectType = objectType;

        // Store the name, generate if necessary
        std::string regName = ( (pszName==NULL) ? "" : pszName );
        if ( regName.empty() == true )
        {
            regName = generate_name( m_ObjectStyle, m_ObjectType, "", this );
        }
        strncpy( m_Name, regName.c_str(), MaxNameLength-1 );
        m_Name[ MaxNameLength-1 ] = 0;
        fResult &= ( m_Name[0] != 0 );

        // Generate the system name
        std::string sysName = generate_system_name( m_ObjectStyle, m_ObjectType, regName );
        strncpy( m_SystemName, regName.c_str(), MaxNameLength-1 );
        m_SystemName[ MaxNameLength-1 ] = 0;
        fResult &= ( m_SystemName[0] != 0 );

        // Create the platform struct info
        if ( fResult == true )
        {
            fResult = platformstruct_create();
            if (fResult == false )
            {
                platformstruct_destroy();
            }
        }

        // Set the flags
        m_fReportState  = ( fReportState != false );
        m_fCreated      = ( fCreated != false );
    }
    catch ( ... )
    {
        OM_TRACE( OM_ETD_ERROR, "ObjectIdent::initialize() ==> Caught Exception" );
        fResult = false;
    }

    if ( fResult == false )
    {
        clear();
    }
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  set_create_flag( bool )
//
//  :Description
//      This function is used to change the state of the create flag.
//      If the state of the create flag is changed the function returns
//      true.  On failure (the object was empty) the function returns
//      false and the create flag is not changed.
//
//  :Implementation
//"
bool  ObjectIdent::set_create_flag( bool fCreate )
{
    if ( empty() == true )
    {
        return (false);
    }
    m_fCreated = (fCreate != false);
    return (true);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! SECURITY_ATTRIBUTES *  get_ptr_security_attributes( void ) const
//
//  :Description
//      This function returns a pointer to the SECURITY_ATTRIBUTES
//      structure that is to be passed to the underlying OS call
//      (::CreateEvent(), ::CreateMutex(), etc).
//
//      It is completely possible that the pointer returned by this
//      function will be NULL.  That is acceptable and in that case
//      the NULL pointer is what gets passed to the underlying function.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    SECURITY_ATTRIBUTES *  ObjectIdent::get_ptr_security_attributes( void ) const
    {
        return (m_PlatformStruct.m_pSA);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
//.


/////////////////////////////////////////////////////////////////////////////
//! pthread_mutexattr_t *  get_ptr_mutexattr( void ) const
//
//  :Description
//      This function returns a pointer to the pthread_mutexattr_t
//      structure that is to be passed to the underlying OS call
//      pthread_mutex_init().
//
//      It is completely possible that the pointer returned by this
//      function will be NULL.  That is acceptable and in that case
//      the NULL pointer is what gets passed to the underlying function.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    pthread_mutexattr_t *  ObjectIdent::get_ptr_mutexattr( void ) const
    {
        pthread_mutexattr_t * pResult = const_cast< pthread_mutexattr_t * >( &(m_PlatformStruct.m_MutexAttribs) );
        return (pResult);
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! void  get_abs_timeout( timespec &, WaitTime ) const
//
//  :Description
//      This function will fill the supplied timespec with the
//      an absolute time representing a point waitTime milliseconds
//      in the future.  This structure can then be used in calls
//      to various OS timedlock() like functions.
//
//  :Implementation
//"
#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    void  ObjectIdent::get_abs_timeout( timespec & absTimeout, WaitTime waitTime ) const
    {
        clock_gettime( CLOCK_REALTIME, &absTimeout );

        Uint32  fullMilliseconds    = static_cast< Uint32 >( waitTime );
        Uint32  numSeconds          = fullMilliseconds / 1000;
        Uint32  remainMilli         = fullMilliseconds - (numSeconds * 1000);
        Uint32  remainNano          = remainMilli * 1000000;
        Uint32  nanoInSecond        = 1000000000;
        while ( remainNano >= nanoInSecond )
        {
            numSeconds++;
            remainNano = remainNano - nanoInSecond;
        }

        absTimeout.tv_sec  += numSeconds;
        absTimeout.tv_nsec += remainNano;

        while ( absTimeout.tv_nsec >= ((signed long)nanoInSecond) )
        {
            absTimeout.tv_sec++;
            absTimeout.tv_nsec = absTimeout.tv_nsec - nanoInSecond;
        }

        return;
    }
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)
//.


/////////////////////////////////////////////////////////////////////////////
//! static  std::string  generate_name( ObjectStyle, ObjectType, const std::string & )
//
//  :Description
//      This function is used to generate a unique name for the
//      ObjectIdent (and in turn the controlling object) when an
//      explicit name was not supplied.
//
//      This function generates an appropriate prefix string then calls
//      the generate_name(std::String) function to complete the work
//
//  :Implementation
//"
std::string  ObjectIdent::generate_name( ObjectStyle objectStyle, ObjectType objectType, const std::string & prefixStr, void * pObjectPtr )
{
    // Generate a prefix string
    //  If the call did not supply one, we generate one based
    //  on the ObjectType.
    std::string prefixString = prefixStr;
    if ( prefixString.empty() == true )
    {
        const char *    pszTypeName     = objecttype_to_string( objectType );
        std::string     prefixString    = ( (pszTypeName==NULL) ? "" : pszTypeName );
        std::string::size_type  uScorePos = prefixString.find_first_of( '_' );
        if ( uScorePos != std::string::npos )
        {
            prefixString = prefixString.substr( uScorePos + 1 );
        }
    }
    if ( prefixString.empty() == true )
    {
        prefixString = "ObjectIdent";
    }

    // Generate an identity string.  This string should
    //  be unique.  (Sorta like a uuid).
    char    identBuffer[ 64 ];
    if ( objectStyle == ObjectStyle_PROCESS )
    {
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            sprintf( identBuffer, "%08p", pObjectPtr );
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            sprintf( identBuffer, "%08lX", (unsigned long)pObjectPtr );
        #else
            #error "ERROR: Platform dependant code"
        #endif
    }
    else
    {
        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            unsigned long   processId   = static_cast< unsigned long >( GetCurrentProcessId() );
            unsigned long   tickValue   = static_cast< unsigned long >( GetTickCount() );
            sprintf( identBuffer, "%08lu_%08lu_%08p",
                        processId, tickValue, pObjectPtr );
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            unsigned long processId   = static_cast< unsigned long >( getpid() );
            unsigned long tickValue   = static_cast< unsigned long >( clock() );
            sprintf( identBuffer, "%08lu_%08lu_%08lX",
                        processId, tickValue, (unsigned long)pObjectPtr );
        #else
            #error "ERROR: This code is platform specific"
        #endif
    }
    if ( identBuffer[0] == 0 )
    {
        srand( (unsigned int)(time(NULL)) );
        sprintf( identBuffer, "%08lX", (unsigned long)rand() );
    }
    // Absolutely ensure null termination and convert
    //  to uppercase.
    identBuffer[sizeof(identBuffer)-1] = 0;
    for ( size_t strPos = 0; identBuffer[strPos] != 0; strPos++ )
    {
        identBuffer[strPos] = toupper( identBuffer[strPos] );
    }

    // Combine the prefix and the identity string
    std::string resultStr = prefixString + "_";
    resultStr += identBuffer;

    return (resultStr);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  std::string  generate_system_name( ObjectStyle, ObjectType, const std::string & )
//
//  :Description
//      This function will take the regular ObjectIdent name (either
//      what was supplied or auto-generated) and turn it into a form
//      suitable for use in OS specific calls.  The name generated
//      by this function is specific to the platform as well as
//      the style, type and name information provided.
//
//  :Implementation
//"
std::string  ObjectIdent::generate_system_name( ObjectStyle objectStyle, ObjectType objectType, const std::string & regName )
{
    std::string     resultString = regName;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        // After v5 of NT we need the "Global\\" prefix added
        //  to the name, but only for ObjectStyle_SYSTEM names.
        if ( objectStyle == ObjectStyle_SYSTEM )
        {
            DWORD   dwVersion               = ::GetVersion();
            DWORD   dwWindowsMajorVersion   =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
            DWORD   dwWindowsMinorVersion   =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
            if ( (dwVersion & 0x80000000) == 0 )
            {
                if ( dwWindowsMajorVersion >= 5 )
                {
                    resultString = "Global\\" + regName;
                }
            }
        }
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        // nothing to do

        //  The GCC compiler whines about these two parameters
        //  being unused.  So this snippit of code really
        //  only exists to make GCC happy.
        if ( (objectStyle == ObjectStyle_ERROR)     &&
             (objectType == ObjectType_ERROR)       &&
             (regName.empty() == true)              )
        {
            resultString.clear();
        }
    #else
        #error "ERROR: Platform dependant code"
    #endif

    return (resultString);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  platformstruct_clear( void )
//
//  :Description
//      This function will clear the contents of the contained
//      PlatformStruct and return it to the empty state.
//      NOTE:  This function does not clear-free any resources,
//             as such the calling code should ensure that
//             platformstruct_destroy() is first called if
//             necessary.
//
//  :Implementation
//"
void  ObjectIdent::platformstruct_clear( void )
{
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        m_PlatformStruct.m_fCreateSID   = false;
        m_PlatformStruct.m_pSID         = NULL;
        memset( &(m_PlatformStruct.m_ExplicitAccess), 0, sizeof(EXPLICIT_ACCESS) );
        m_PlatformStruct.m_fCreateACL   = false;
        m_PlatformStruct.m_pACL         = NULL;
        m_PlatformStruct.m_fCreateSD    = false;
        m_PlatformStruct.m_pSD          = NULL;
        memset( &(m_PlatformStruct.m_SA), 0, sizeof(SECURITY_ATTRIBUTES) );
        m_PlatformStruct.m_pSA          = NULL;

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        m_PlatformStruct.m_fCreateMutexAttribs   = false;
        memset( &(m_PlatformStruct.m_MutexAttribs), 0, sizeof(pthread_mutexattr_t) );

    #else
        #error "ERROR: Platform dependant code"
    #endif
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  platformstruct_create( void )
//
//  :Description
//      This function will create the necessary elements in this
//      structure based on the current ObjectStyle and ObjectType
//      members.
//
//  :Implementation
//"
bool  ObjectIdent::platformstruct_create( void )
{
    bool fResult = false;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        bool    fCreateSecurity = ( m_ObjectStyle == ObjectStyle_SYSTEM );
        if ( fCreateSecurity == false )
        {
            fResult = true;
        }
        else
        {
            SID_IDENTIFIER_AUTHORITY    sidAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
            if ( ::AllocateAndInitializeSid( &sidAuthWorld,
                                             1,
                                             SECURITY_WORLD_RID,
                                             0, 0, 0, 0, 0, 0, 0,
                                             &m_PlatformStruct.m_pSID ) == FALSE )
            {
                OM_SYSTEM_ERROR( "ObjectIdent::platformstruct_create() == Call to ::AllocateAndInitializeSid() failed.", ::GetLastError() );
            }
            else
            {
                m_PlatformStruct.m_fCreateSID = true;

                m_PlatformStruct.m_ExplicitAccess.grfAccessPermissions              = GENERIC_ALL; // KEY_READ;
                m_PlatformStruct.m_ExplicitAccess.grfAccessMode                     = SET_ACCESS;
                m_PlatformStruct.m_ExplicitAccess.grfInheritance                    = NO_INHERITANCE; // OBJECT_INHERIT_ACE;
                m_PlatformStruct.m_ExplicitAccess.Trustee.pMultipleTrustee          = NULL;
                m_PlatformStruct.m_ExplicitAccess.Trustee.MultipleTrusteeOperation  = NO_MULTIPLE_TRUSTEE;
                m_PlatformStruct.m_ExplicitAccess.Trustee.TrusteeForm               = TRUSTEE_IS_SID;
                m_PlatformStruct.m_ExplicitAccess.Trustee.TrusteeType               = TRUSTEE_IS_WELL_KNOWN_GROUP;
                m_PlatformStruct.m_ExplicitAccess.Trustee.ptstrName                 = (LPTSTR)m_PlatformStruct.m_pSID;

                DWORD dwRes = ::SetEntriesInAcl( 1,
                                                 &(m_PlatformStruct.m_ExplicitAccess),
                                                 NULL,
                                                 &(m_PlatformStruct.m_pACL) );
                if ( dwRes != ERROR_SUCCESS )
                {
                    OM_SYSTEM_ERROR( "ObjectIdent::platformstruct_create() == Call to ::SetEntriesInAcl() failed.", ::GetLastError() );
                }
                else
                {
                    m_PlatformStruct.m_fCreateACL = true;

                    m_PlatformStruct.m_pSD = (PSECURITY_DESCRIPTOR)::LocalAlloc( LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH );
                    if (m_PlatformStruct.m_pSD == NULL)
                    {
                        OM_SYSTEM_ERROR( "ObjectIdent::platformstruct_create() == Call to ::LocalAlloc() failed.", ::GetLastError() );
                    }
                    else
                    {
                        m_PlatformStruct.m_fCreateSD = true;

                        // Init the Security descriptor
                        if ( ::InitializeSecurityDescriptor( m_PlatformStruct.m_pSD, SECURITY_DESCRIPTOR_REVISION ) == FALSE )
                        {
                            OM_SYSTEM_ERROR( "ObjectIdent::platformstruct_create() == Call to ::InitializeSecurityDescriptor() failed.", ::GetLastError() );
                        }
                        else
                        {
                            // Add the ACL to the security descriptor.
                            if ( ::SetSecurityDescriptorDacl( m_PlatformStruct.m_pSD,  TRUE, m_PlatformStruct.m_pACL, FALSE) == FALSE )
                            {
                                OM_SYSTEM_ERROR( "ObjectIdent::platformstruct_create() == Call to ::SetSecurityDescriptorDacl() failed.", ::GetLastError() );
                            }
                            else
                            {
                                m_PlatformStruct.m_SA.nLength               = sizeof( SECURITY_ATTRIBUTES );
                                m_PlatformStruct.m_SA.lpSecurityDescriptor  = m_PlatformStruct.m_pSD;
                                m_PlatformStruct.m_SA.bInheritHandle        = FALSE;

                                m_PlatformStruct.m_pSA = &(m_PlatformStruct.m_SA);

                                fResult = true;
                            }
                        }
                    }
                }
            }
        }

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        bool    fCreateSecurity = ( m_ObjectStyle == ObjectStyle_PROCESS );
        if ( fCreateSecurity == false )
        {
            fResult = true;
        }
        else
        {
            if ( pthread_mutexattr_init( &(m_PlatformStruct.m_MutexAttribs) ) != 0 )
            {
                OM_TRACE( OM_ETD_ERROR, "ObjectIdent::platformstruct_create() == Call to pthread_mutexattr_init() failed." );
            }
            else
            {
                m_PlatformStruct.m_fCreateMutexAttribs = true;
                if ( pthread_mutexattr_settype( &(m_PlatformStruct.m_MutexAttribs), PTHREAD_MUTEX_RECURSIVE_NP ) != 0 )
                {
                    OM_TRACE( OM_ETD_ERROR, "ObjectIdent::platformstruct_create() ==> Call to pthread_mutexattr_settype() failed." );
                }
                else
                {
                    fResult = true;
                }
            }
        }

    #else
        #error "ERROR: Platform dependant code"
    #endif
    return (fResult);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool  platformstruct_destroy( void )
//
//  :Description
//      This function will destroy any created elements in this
//      structure and will then return the structure to the empty
//      state.
//
//  :Implementation
//"
bool  ObjectIdent::platformstruct_destroy( void )
{
    bool fResult = false;
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

        fResult = true;
        if ( m_PlatformStruct.m_fCreateSD == true )
        {
            LocalFree( m_PlatformStruct.m_pSD );
        }
        if ( m_PlatformStruct.m_fCreateSID == true )
        {
            ::FreeSid( m_PlatformStruct.m_pSID );
        }
        if ( m_PlatformStruct.m_fCreateACL == true )
        {
            ::LocalFree( m_PlatformStruct.m_pACL );
        }

    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

        if ( m_PlatformStruct.m_fCreateMutexAttribs == true )
        {
            if ( pthread_mutexattr_destroy( &(m_PlatformStruct.m_MutexAttribs) ) != 0 )
            {
                OM_TRACE( OM_ETD_ERROR, "ObjectIdent::platformstruct_destroy() ==> Call to pthread_mutexattr_destroy() failed." );
                fResult = false;
            }
        }

    #else
        #error "ERROR: Platform dependant code"
    #endif
    platformstruct_clear();
    return (fResult);
}
//.



};  // namespace Tasking


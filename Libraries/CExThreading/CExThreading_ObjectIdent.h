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
//      CExtend\Libraries\CExThreading\CExThreading_ObjectIdent.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_ObjectIdent_h
#define _CExThreading_ObjectIdent_h

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! ObjectIdent
//
//  :Description
//      This
//

//  :Definition
//"
class ObjectIdent
{
    // Friends
        friend class Mutex;
        friend class Thread;
        friend class Event;

    // Embedded Types
    private:
        enum { MaxNameLength = 256 };

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

            typedef struct
            {
                bool                    m_fCreateSID;
                PSID                    m_pSID;
                EXPLICIT_ACCESS         m_ExplicitAccess;
                bool                    m_fCreateACL;
                PACL                    m_pACL;
                bool                    m_fCreateSD;
                PSECURITY_DESCRIPTOR    m_pSD;
                SECURITY_ATTRIBUTES     m_SA;
                SECURITY_ATTRIBUTES *   m_pSA;
            } PlatformStruct;

        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

            typedef struct
            {
                bool                    m_fCreateMutexAttribs;
                pthread_mutexattr_t     m_MutexAttribs;
            } PlatformStruct;

        #else
            #error "ERROR: Platform dependant code"
        #endif

    // Data Members
    private:
        ObjectStyle         m_ObjectStyle;
        ObjectType          m_ObjectType;
        char                m_Name[ MaxNameLength ];
        char                m_SystemName[ MaxNameLength ];
        bool                m_fReportState;
        bool                m_fCreated;

        PlatformStruct      m_PlatformStruct;

    // Construction
    public:
        ObjectIdent( void );
        ObjectIdent( const ObjectIdent & rhSide );
        ~ObjectIdent( void );
        const ObjectIdent & operator = ( const ObjectIdent & rhSide );

    // Public Interface
    public:
        void    clear( void );
        bool    empty( void ) const;

        ObjectStyle     object_style( void ) const;
        ObjectType      object_type( void ) const;
        const char *    name( void ) const;
        const char *    system_name( void ) const;
        bool            report_state_flag( void ) const;
        bool            created_flag( void ) const;

        static  const char *    objectstyle_to_string( ObjectStyle objectStyle );
        static  const char *    objecttype_to_string( ObjectType objectType );

    // Protected Interface
    protected:
        bool    initialize( ObjectStyle     objectStyle,
                            ObjectType      objectType,
                            const char *    pszName,
                            bool            fReportState,
                            bool            fCreated );
        bool    set_create_flag( bool fCreate );

        #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
            SECURITY_ATTRIBUTES *   get_ptr_security_attributes( void ) const;
        #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
            pthread_mutexattr_t *   get_ptr_mutexattr( void ) const;
            void    get_abs_timeout( timespec & absTimeout, WaitTime waitTime ) const;
        #else
            #error "ERROR: Platform dependant code"
        #endif

    // Private Interface
    private:
        static  std::string     generate_name( ObjectStyle objectStyle, ObjectType objectType, const std::string & prefixStr, void * pObjectPtr );
        static  std::string     generate_system_name( ObjectStyle objectStyle, ObjectType objectType, const std::string & regName );

        void    platformstruct_clear( void );
        bool    platformstruct_create( void );
        bool    platformstruct_destroy( void );
};
//.


/////////////////////////////////////////////////////////////////////////////

};  // namespace CExThreading

#endif // _CExThreading_ObjectIdent_h



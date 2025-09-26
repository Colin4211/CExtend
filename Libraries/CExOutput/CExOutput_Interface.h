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
//      CExtend\Libraries\CExOutput\CExOutput_Interface.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_Interface_h
#define _CExOutput_Interface_h

/////////////////////////////////////////////////////////////////////////////
//  Additional Includes
//

#include "CExBase.h"


/////////////////////////////////////////////////////////////////////////////
//  Begin "C" linkage
//

#if defined(__cplusplus)
    extern "C" {
#endif //   defined(__cplusplus)


/////////////////////////////////////////////////////////////////////////////
//!  OM_FUNCTION
//
//  :Description
//      This macros is used in the definition of the functions exported
//      from the OMM.  They are used to ensure the compiler
//      and linker use the appropriate calling conventions when calling
//      the exported functions.
//
//  :Definition
//"
#if defined(OM_BUILD_LIBRARY)
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        #define OM_FUNCTION         __declspec(dllexport)   __stdcall
        #define OM_PTR_FUNCTION     __stdcall
        #define OM_CB_FUNCTION      __stdcall
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        #define OM_FUNCTION         __attribute__ ((visibility("default")))
        #define OM_PTR_FUNCTION
        #define OM_CB_FUNCTION
    #else
        #error "ERROR: This code is platform specific"
    #endif
#else
    #if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
        #define OM_FUNCTION         __declspec(dllimport)   __stdcall
        #define OM_PTR_FUNCTION     __stdcall
        #define OM_CB_FUNCTION      __stdcall
    #elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
        #define OM_FUNCTION
        #define OM_PTR_FUNCTION
        #define OM_CB_FUNCTION
    #else
        #error "ERROR: This code is platform specific"
    #endif
#endif // !defined(OM_CB_FUNCTION)
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_VERSION
//
//  :Description
//      This version number is to be supplied to the OM_VerifyVersion
//      function to ensure that the interface supplied by the library
//      is what the user of this header file expects
//
//      This is a Uint32 and the intended use is that each 8-bit segment
//      from MSB to LSB indicates the major-minor-rev-build part of the
//      version number.
//
//      Note that the library may be implementing a slightly different
//      version that what the caller specifies.  But if the library
//      (DLL or SO) supports the interface specified by the supplied
//      value, it will return success indicating further calls to the
//      interface can be made.
//
//  :Definition
//"
#define OM_INTERFACE_VERSION_SHIFT      (10000)
#define OM_INTERFACE_VERSION_MAJOR      (4)
#define OM_INTERFACE_VERSION_MINOR      (1)
#define OM_INTERFACE_VERSION            ((OM_INTERFACE_VERSION_MAJOR+OM_INTERFACE_VERSION_SHIFT)+OM_INTERFACE_VERSION_MINOR)
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_EventType
//
//  :Description
//      This event type is used to describe what type of event is being
//      generated.  An value may be supplied for this type.  However
//      the library encourages the use of the various predefined event
//      types whenever possible.
//
//  :Definition
//"

typedef     Uint16                      OM_EventType;

#define     OM_ET_MASK_CATAGORY         ((OM_EventType)(0xF000))
#define     OM_ET_MASK_RESERVED         ((OM_EventType)(0x0F00))
#define     OM_ET_MASK_MESSAGEID        ((OM_EventType)(0x00FF))

#define     OM_CATAGORY_REGULAR         ((OM_EventType)(0x1000))
#define     OM_CATAGORY_DEBUG           ((OM_EventType)(0x2000))
#define     OM_CATAGORY_FILE_OPS        ((OM_EventType)(0x3000))

#define     OM_MSGID_INFO               ((OM_EventType)(0x0011))
#define     OM_MSGID_WARNING            ((OM_EventType)(0x0012))
#define     OM_MSGID_ERROR              ((OM_EventType)(0x0013))
#define     OM_MSGID_DETAIL             ((OM_EventType)(0x0014))
#define     OM_MSGID_HELP               ((OM_EventType)(0x0015))
#define     OM_MSGID_D_DUMP             ((OM_EventType)(0x0021))
#define     OM_MSGID_D_ASSERT           ((OM_EventType)(0x0022))
#define     OM_MSGID_D_BREAK            ((OM_EventType)(0x0023))
#define     OM_MSGID_D_ENTER_SCOPE      ((OM_EventType)(0x0024))
#define     OM_MSGID_D_EXIT_SCOPE       ((OM_EventType)(0x0025))
#define     OM_MSGID_D_OBSOLETE         ((OM_EventType)(0x0026))

#define     OM_ET_INFO                  ((OM_EventType)(OM_CATAGORY_REGULAR|OM_MSGID_INFO))
#define     OM_ET_WARNING               ((OM_EventType)(OM_CATAGORY_REGULAR|OM_MSGID_WARNING))
#define     OM_ET_ERROR                 ((OM_EventType)(OM_CATAGORY_REGULAR|OM_MSGID_ERROR))
#define     OM_ET_DETAIL                ((OM_EventType)(OM_CATAGORY_REGULAR|OM_MSGID_DETAIL))
#define     OM_ET_HELP                  ((OM_EventType)(OM_CATAGORY_REGULAR|OM_MSGID_HELP))

#define     OM_ETD_INFO                 ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_INFO))
#define     OM_ETD_WARNING              ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_WARNING))
#define     OM_ETD_ERROR                ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_ERROR))
#define     OM_ETD_DETAIL               ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_DETAIL))
#define     OM_ETD_HELP                 ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_HELP))
#define     OM_ETD_DUMP                 ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_D_DUMP))
#define     OM_ETD_ASSERT               ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_D_ASSERT))
#define     OM_ETD_BREAK                ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_D_BREAK))
#define     OM_ETD_ENTER_SCOPE          ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_D_ENTER_SCOPE))
#define     OM_ETD_EXIT_SCOPE           ((OM_EventType)(OM_CATAGORY_DEBUG|OM_MSGID_D_EXIT_SCOPE))


//.


/////////////////////////////////////////////////////////////////////////////
//! OM_Result
//
//  :Definition
//"
typedef     Uint32                          OM_Result;
#define     OM_Result_OK                    ((OM_Result)(0))
#define     OM_Result_ERROR                 ((OM_Result)(1))
#define     OM_Result_BAD_VERSION           ((OM_Result)(2))
#define     OM_Result_INVALID_ARGS          ((OM_Result)(3))
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_MAX_EVENT_COUNT
//
//  :Description
//      This constant is used by the OM as the
//      maximum number of output events which will be queued at any
//      time.  If the OMs internal queue reaches this
//      size the oldest events are discarded and the new event is still
//      added to the internal queue.
//
//  :Definition
//"
#define OM_MAX_EVENT_COUNT      (1024)
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_MAX_FILENAME_LENGTH
//
//  :Description
//      This constant represents the maximum length of the string which
//      stores the name of the file which generated the event.
//      This filename will be trimmed down to eliminate the path
//      portion of the name and if longer than this constants will be
//      truncated.
//
//  :Definition
//"
#define OM_MAX_FILENAME_LENGTH    (64)
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_MAX_SCOPE_NAME_LENGTH
//
//  :Description
//      This constant represents the maximum length of the string
//      used to store the scope name of the event.
//
//      Longer strings may be safely supplied.  But they will be truncated.
//
//  :Definition
//"
#define OM_MAX_SCOPE_NAME_LENGTH      (128)
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_MAX_EVENT_STRING_LENGTH
//
//  :Description
//      This constant represents the maximum length of the event string value
//      captured by the EventLogging library.
//
//      Longer strings may be safely supplied.  But they will be truncated.
//      This allows calling code to eliminate excessive code by not
//      worrying about potential buffer overruns.
//
//  :Definition
//"
#define OM_MAX_EVENT_STRING_LENGTH      (512)
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_LogFileType
//
//  :Description
//      This is the type string supplied to the OM_RedirectXXXXX() string.
//
//      = OM_RedirectType_LOGFILE_TEXT, OM_RedirectType_LOGFILE_BINARY
//          Both these types open a logfile and redirect output to it.
//          If the filename supplied is empty, one is generated based
//          on the application name.  If the supplied name is a directory
//          then the filename is still generated automatically and it
//          is written to that directory. If the filename is prefixed
//          with a number then a '|' character then the logfile will
//          be reopened if that many seconds has elapsed since the
//          log file was first opened.
//
//  :Definition
//"
typedef     const char *                            OM_RedirectType;
#define     OM_RedirectType_ERROR                   ((OM_RedirectType)(NULL))
#define     OM_RedirectType_LOGFILE_TEXT            ((OM_RedirectType)("LogFile_Text"))
#define     OM_RedirectType_LOGFILE_BINARY          ((OM_RedirectType)("LogFile_Binary"))
#define     OM_RedirectType_INET_DGRAM_TEXT         ((OM_RedirectType)("INet_DGram_Binary"))
#define     OM_RedirectType_INET_DGRAM_BINARY       ((OM_RedirectType)("INet_DGram_Binary"))
#define     OM_RedirectType_DEBUG_OUTPUT            ((OM_RedirectType)("DebugOutput"))
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_TimeStruct
//
//  :Description
//      This structure is used to store the time of the event.
//      Originally a TimeT value was used.  However in the creation
//      of the v3.x release the use of TimeT values in the CExtend
//      libraries was depreciated in favour of a time structure.
//
//      This structure can be copied (on a member by member basis)
//      over to the Util::Time time structure.  Its members are always
//      considered to be UTC time zone.
//
//  :Implementation
//"
typedef struct
{
    Int16   m_Year;
    Int8    m_Month;
    Int8    m_Day;
    Int8    m_Hour;
    Int8    m_Minute;
    Int8    m_Second;
} OM_TimeStruct;
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_ProcessIDType
//
//  :Description
//      This type is used to represent a process identifier in the
//      OM_OutputEvent structure.
//
//  :Definition
//"
typedef Uint64          OM_ProcessIDType;
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_ThreadIDType
//
//  :Description
//      This type is used to represent a thread identifier in the
//      OM_OutputEvent structure.
//
//  :Definition
//"
typedef Uint64          OM_ThreadIDType;
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_OutputEvent
//
//  :Description
//      When retrieving events from the OMM they are
//      returned as a single structure.  It includes all the information
//      supplied to the function EM_PostEvent() as well as additional
//      information generated at the time of the call.
//
//  :Member Variables
//      = Uint32  m_ProcessID
//          The OS supplied process ID for the process which generated
//          the event.
//      = Uint32  m_ThreadID;
//          The OS supplied thread ID for the process which generated
//          the event.
//      = Uint32  m_PacketNumber
//          The number of this packet.  Packet numbers are auto-generated
//          starting at zero and increasing.  If/When the max number is
//          reached the index rolls around to zero.
//      = OM_TimeStruct  m_TimeT
//          The system time as returned by the "C" library time()
//          function.
//      = OM_EventType  m_EventType
//          This is a value supplied by the caller and denotes the type
//          of event being generated.
//      = OM_Char m_SourceFile[ OM_MAX_STRING_LENGTH ]
//          This is the name of the source code file from which the event
//          was generated.  The calling code should have used the
//          __FILE__ macro for this
//      = Uint32 m_SourceLine
//          This is the line number in the source code file from which
//          the event was generated.  The calling code should have used
//          the __LINE__ macro for this
//      = OM_Char m_ScopeName[ OM_MAX_SCOPE_NAME_LENGTH ]
//          This is a string describing the scope from which then
//          event was generated.  This is an optional field and
//          generally only used when calling the OM_LTRACEx()
//          macros.
//      = OM_Char m_EventString[ OM_MAX_STRING_LENGTH ]
//          This is the actual "text" message associated with the event.
//
//  :Declaration
//"
typedef struct
{
    Uint32              m_SourcePlatform;
    Uint32              m_SizeOf;
    OM_ProcessIDType    m_ProcessID;
    OM_ThreadIDType     m_ThreadID;
    Uint32              m_PacketIndex;
    OM_TimeStruct       m_TimeStruct;
    OM_EventType        m_EventType;
    char                m_SourceFile[ OM_MAX_FILENAME_LENGTH ];
    Uint32              m_SourceLine;
    char                m_ScopeName[ OM_MAX_SCOPE_NAME_LENGTH ];
    char                m_EventString[ OM_MAX_EVENT_STRING_LENGTH ];
} OM_OutputEvent;
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_pfnNotifyProc;
//
//  :Description
//      If the application which is using the CExOutput desires it
//      can capture the generated messages as they happen.  The calling
//      application must supply a callback function to the library
//      which matches this function signature.
//
//      The OMM will then call this function every time
//      the OM_GenerateEvent() function is called.
//
//  :Definition
//"
typedef void (OM_CB_FUNCTION * OM_pfnNotifyProc)( void );
//.



/////////////////////////////////////////////////////////////////////////////
//! OM_Result  OM_FUNCTION  OM_VerifyVersion( Uint32 )
//
//  :Defintion
//"
typedef OM_Result
    (OM_PTR_FUNCTION * OM_PtrVerifyVersion)( Uint32 omVersion );
OM_Result   OM_FUNCTION  OM_VerifyVersion( Uint32 omVersion );
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_Result   OM_FUNCTION  OM_GenerateOutputEvent( OM_EventType, const char *, Uint32, const char * )
//
//  :Defintion
//"
typedef OM_Result
    (OM_PTR_FUNCTION * OM_PtrGenerateOutputEvent)( OM_EventType       eventType,
                                                   const char *       sourceFile,
                                                   Uint32             sourceLine,
                                                   const char *       functionName,
                                                   const char *       eventStr );
OM_Result   OM_FUNCTION  OM_GenerateOutputEvent( OM_EventType       eventType,
                                                 const char *       sourceFile,
                                                 Uint32             sourceLine,
                                                 const char *       functionName,
                                                 const char *       eventStr );
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_Result   OM_FUNCTION  OM_GetOutputEventCount( Uint32 * )
//
//  :Definition
//"
typedef OM_Result
    (OM_PTR_FUNCTION * OM_PtrGetOutputEventCount)( Uint32 * pEventCount );
OM_Result   OM_FUNCTION  OM_GetOutputEventCount( Uint32 * pEventCount );
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_Result   OM_FUNCTION  OM_GetOutputEvent( OM_OutputEvent *, Uint32 )
//
//  :Definition
//"
typedef OM_Result
    (OM_PTR_FUNCTION * OM_PtrGetOutputEvent)( OM_OutputEvent * pPacket, Uint32 sizeofPacket );
OM_Result   OM_FUNCTION  OM_GetOutputEvent( OM_OutputEvent * pPacket, Uint32 sizeofPacket );
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_Result   OM_FUNCTION  OM_SetCallback( OM_pfnNotifyProc )
//
//  :Definition
//"
typedef OM_Result
    (OM_PTR_FUNCTION * OM_PtrSetCallback)( OM_pfnNotifyProc pfnNotify );
OM_Result   OM_FUNCTION  OM_SetCallback( OM_pfnNotifyProc pfnNotify );
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_Result   OM_FUNCTION  OM_RedirectOpen( OM_RedirectType, const char * )
//
//  :Definition
//"
typedef OM_Result
    (OM_PTR_FUNCTION * OM_PtrRedirectOpen)( OM_RedirectType reType, const char * openStr );
OM_Result   OM_FUNCTION  OM_RedirectOpen( OM_RedirectType reType, const char * openStr );
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_Result   OM_FUNCTION  OM_RedirectIsOpen( OM_RedirectType )
//
//  :Definition
//"
typedef OM_Result
    (OM_PTR_FUNCTION * OM_PtrRedirectIsOpen)( OM_RedirectType reType );
OM_Result   OM_FUNCTION  OM_RedirectIsOpen( OM_RedirectType reType );
//.


/////////////////////////////////////////////////////////////////////////////
//! OM_Result   OM_FUNCTION  OM_RedirectClose( OM_RedirectType )
//
//  :Definition
//"
typedef OM_Result
    (OM_PTR_FUNCTION * OM_PtrRedirectClose)( OM_RedirectType reType );
OM_Result   OM_FUNCTION  OM_RedirectClose( OM_RedirectType reType );
//.


///////////////////////////////////////////////////////////////////////////*/
// End "C" linkage
//

#if defined(__cplusplus)
    }
#endif // defined(__cplusplus)


/////////////////////////////////////////////////////////////////////////////

#endif // _CExOutput_Interface_h

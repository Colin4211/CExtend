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
//      CExtend\Libraries\CExOutput\CExOutput_NewMaxros.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_NewMaxros_h
#define _CExOutput_NewMaxros_h


/////////////////////////////////////////////////////////////////////////////
//! OM_DEBUG_SCOPE()
//
//  :Description
//      Use this macro at the start of the function (or some other
//      scope).  It can only be declared once in a given scope.
//
//      The macro takes three arguments.  The first is the name of the
//      scope. The second argument is a bool value indicating if debug
//      output from this scope is generated.  The third is a bool value
//      indicating if the entry and exit of the scope should generate
//      a debug message.
//
//      Use of the OMS_TRACEx() macros requie the definition
//      of this macro in the same (or accesible) scope.
//
//      In the release build this macro generates no code.  It is
//      only used in the DEBUG build of the code.
//
//      One of the benefits of this macro along with the
//      OMS_TRACEx() macros is the ability to equip a function with
//      a large number of TRACE statements and then turn them on or
//      off only when needed during debugging, but they are never
//      in the release build.
//
//  :Implementation
//"

#if defined(CEXTEND_DEBUG)
    #define OM_DEBUG_SCOPE(NAME,OUTPUT,REPORT)  CExOutput::DebugScope   ___CExOutput_DebugScope(__FILE__,__LINE__,NAME,OUTPUT,REPORT);
#else
    #define OM_DEBUG_SCOPE(NAME,OUTPUT,REPORT)  ;
#endif

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_OUTPUT( OM_EventType, const char * )
//
//  :Arguments
//      = OM_EventType  eType
//          The event type for this output event.
//      = const char *  outMsg
//          The message to be output.
//
//  :Description
//      The OM_OUTPUT macro is used to simplify the act of sending
//      output to the CExOutput::Manager class.
//
//  :Definition
//"
#define OM_OUTPUT(eType,outMsg)                             \
    {   CExOutput::Manager::singleton().generate_output_event( (eType),    \
            (__FILE__), (__LINE__), (NULL), (outMsg) );             }

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_OUTPUTn( OM_EventType, const char *, ... )
//
//  :Arguments
//      = OM_EventType  eType
//          The event type for this output event.
//      = const char *  outMsgFmt
//          The sprintf compatible format string for the message to be
//          output.
//
//  :Description
//      The OM_OUTPUT macro is used to simplify the act of sending
//      output to the CExOutput::Manager class.
//
//      Due to the limitations of the C++ language: NewMaxros do not
//      support var-args.  Therefore we must supply a series of
//      numbered macros.  The number indicates the number of
//      additional arguments that are being supplied.
//
//  :Definition
//"

#define OM_OUTPUT6(eType,outMsgFmt,argA,argB,argC,argD,argE,argF)       \
    {   CExOutput::Manager::singleton().generate_output_event_va(       \
            (eType), (__FILE__), (__LINE__), (NULL), (outMsgFmt),       \
            (argA), (argB), (argC), (argD), (argE), (argF) );           }

#define OM_OUTPUT5(eType,outMsgFmt,argA,argB,argC,argD,argE) \
            OM_OUTPUT6(eType,outMsgFmt,argA,argB,argC,argD,argE,0)

#define OM_OUTPUT4(eType,outMsgFmt,argA,argB,argC,argD) \
            OM_OUTPUT6(eType,outMsgFmt,argA,argB,argC,argD,0,0)

#define OM_OUTPUT3(eType,outMsgFmt,argA,argB,argC) \
            OM_OUTPUT6(eType,outMsgFmt,argA,argB,argC,0,0,0)

#define OM_OUTPUT2(eType,outMsgFmt,argA,argB) \
            OM_OUTPUT6(eType,outMsgFmt,argA,argB,0,0,0,0)

#define OM_OUTPUT1(eType,outMsgFmt,argA) \
            OM_OUTPUT6(eType,outMsgFmt,argA,0,0,0,0,0)

#define OM_OUTPUT0(eType,outMsgFmt) \
            OM_OUTPUT6(eType,outMsgFmt,0,0,0,0,0,0)

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_SYSTEM_ERROR( const char *, unsigned long )
//
//  :Arguments
//      = const char *   outMsg
//          The output message to generate
//      = unsigned long  sysErr
//          The OS error code to be converted to a string
//
//  :Description
//      This function calls the SystemErrorEvent() to generate the event.
//
//  :Implementation
//"

#define OM_SYSTEM_ERROR(outMsg,sysErr)                                  \
    {   CExOutput::Manager::singleton().system_error_event(             \
            (__FILE__), (__LINE__), (NULL),                             \
            (outMsg), (unsigned long)(sysErr) );                        }

#if defined(CEXTEND_DEBUG)

    #define OMS_SYSTEM_ERROR(outMsg,sysErr)                             \
        {   if ( ___CExOutput_DebugScope.gen_output() == true ) {       \
                CExOutput::Manager::singleton().system_error_event(     \
                    (__FILE__), (__LINE__),                             \
                    ___CExOutput_DebugScope.scope_name(),               \
                    (outMsg), (unsigned long)(sysErr) );                } }

#else

    #define OMS_SYSTEM_ERROR(outMsg,sysErr)         { }

#endif

//.


/////////////////////////////////////////////////////////////////////////////
//! _OM_OS_BREAK
//
//  :Description
//      This macro is used to generate a debugger break.
//      If the argument supplied is NULL then only the debugger break
//      is issued.
//
//      If the argument supplied is a string then a
//      CExOutput::Exception is thrown with the supplied message before
//      the debugger break.
//
//      It is present in both debug and release and is not intended
//      for direct use.  Use the OS_DEBUG_BREAK macro instead.
//
//  :Definition
//"

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    #define _OM_OS_BREAK_NOTHROW()   {  \
        ::DebugBreak();                 }

    #define _OM_OS_BREAK_THROW(pszExMsgA,pszExMsgB)   {         \
        throw CExOutput::Exception( (__FILE__), (__LINE__),     \
            pszExMsgA , pszExMsgB );                            \
        ::DebugBreak();                                         }


#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    #define _OM_OS_BREAK_NOTHROW()   {                          \
        fprintf( stdout, "\n--==[DebugBreak]==--\n");           \
        fprintf( stdout, "File: %s\n", __FILE__);               \
        fprintf( stdout, "Line: %d\n", __LINE__ );              \
        fprintf( stdout, "--==[DebugBreak]==--\n\n" );          \
        fflush( stdout ); __builtin_trap();                     }

    #define _OM_OS_BREAK_THROW(pszExMsgA,pszExMsgB)   {         \
        fprintf( stdout, "\n--==[DebugBreak]==--\n");           \
        fprintf( stdout, "File: %s\n", __FILE__);               \
        fprintf( stdout, "Line: %d\n", __LINE__ );              \
        fprintf( stdout, "--==[DebugBreak]==--\n\n" );          \
        fflush( stdout );                                       \
        throw CExOutput::Exception( (__FILE__), (__LINE__),     \
            pszExMsgA , pszExMsgB );                            \
        __builtin_trap();                                       }

#else

    #error "ERROR: This code is platform specific"

#endif

//.



/////////////////////////////////////////////////////////////////////////////
//! OM_BREAK
//
//  :Description
//      This macro is used to generate a break event message and
//      halt the execution of the program.
//
//      This macro is present in both debug and release builds
//
//  :Definition
//"

#define OM_BREAK() {                                            \
    CExOutput::Manager::singleton().generate_output_event(      \
            OM_ETD_BREAK, (__FILE__), (__LINE__), (NULL),       \
            "Break Encountered (throw exception)" );            \
    _OM_OS_BREAK_THROW( "Break Encountered", "");               }

#define OM_BREAK_NOTHROW() {                                    \
    CExOutput::Manager::singleton().generate_output_event(      \
            OM_ETD_BREAK, (__FILE__), (__LINE__), (NULL),       \
            "Break Encountered (no throw exception)" );        \
    _OM_OS_BREAK_NOTHROW();                                     }

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_DEBUG_BREAK
//
//  :Description
//      This macro is used to generate a debugger break
//      event message and halt the execution of the program.
//
//      This macro is present in only the debug builds.
//
//  :Definition
//"


#if defined(CEXTEND_DEBUG)

    #define OM_DEBUG_BREAK() {                                  \
        CExOutput::Manager::singleton().generate_output_event(  \
            OM_ETD_BREAK, (__FILE__), (__LINE__), (NULL),       \
            "Debug Breakpoint (throw)" );                       \
        _OM_OS_BREAK_THROW( "Debug Break Encountered", "" );    }

    #define OM_DEBUG_BREAK_NOTHROW() {                          \
        CExOutput::Manager::singleton().generate_output_event(  \
            OM_ETD_BREAK, (__FILE__), (__LINE__), (NULL),       \
            "Debug Breakpoint (nothrow)" );                     \
        _OM_OS_BREAK_NOTHROW();                                 }

    #define OMS_DEBUG_BREAK() {                                 \
        CExOutput::Manager::singleton().generate_output_event(  \
            OM_ETD_BREAK, (__FILE__), (__LINE__),               \
            ___CExOutput_DebugScope.scope_name(),               \
            "Debug Breakpoint (throw)" );                       \
        _OM_OS_BREAK_THROW( "Debug Break Encountered",          \
            ___CExOutput_DebugScope.scope_name() );             }

    #define OMS_DEBUG_BREAK_NOTHROW() {                         \
        CExOutput::Manager::singleton().generate_output_event(  \
            OM_ETD_BREAK, (__FILE__), (__LINE__),               \
            ___CExOutput_DebugScope.scope_name(),               \
            "Debug Breakpoint (nothrow)" );                     \
        _OM_OS_BREAK_NOTHROW();                                 }

#else // if defined(CEXTEND_DEBUG)

    #define OM_DEBUG_BREAK()                {}
    #define OM_DEBUG_BREAK_NOTHROW()        {}

    #define OMS_DEBUG_BREAK()               {}
    #define OMS_DEBUG_BREAK_NOTHROW()       {}

#endif // defined(CEXTEND_DEBUG)

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_TRACE( OM_EventType, const char * )
//
//  :Arguments
//      = OM_EventType  eType
//          The event type for this output event.
//      = const char *  outMsg
//          The message to be output.
//
//  :Description
//      The OM_TRACE behaves identically to the OM_OUTPUT macro in the
//      debug (CEXTEND_DEBUG) build of the software.  In the release build
//      (CEXTEND_RELEASE) the macro performs no actions.
//
//      The notable different between the OM_TRACEx() and OM_TRACE()
//      macro is that this macro does not run the supplied outMsg
//      argument through vsprintf().  It is stored directly
//      as supplied.
//
//  :Definition
//"

#if defined(CEXTEND_DEBUG)

    #define OM_TRACE(eType,outMsg) {                                \
        CExOutput::Manager::singleton().generate_output_event(      \
            (eType), (__FILE__), (__LINE__), (NULL), (outMsg) );    }

    #define OMS_TRACE() {                                           \
        if ( ___CExOutput_DebugScope.gen_output() == true ) {       \
            CExOutput::Manager::singleton().generate_output_event(  \
                OM_ETD_INFO, (__FILE__), (__LINE__),                \
                ___CExOutput_DebugScope.scope_name(), (outMsg)); }  }

#else // if defined(CEXTEND_DEBUG)

    #define OM_TRACE(eType,outMsg)      {}
    #define OMS_TRACE(eType,outMsg)     {}

#endif // defined(CEXTEND_DEBUG)

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_TRACEn( OM_EventType, const char *, ... )
//
//  :Arguments
//      = OM_EventType  eType
//          The event type for this output event.
//      = const char *  outMsgFmt
//          The sprintf compatible format string for the message to be
//          output.
//
//  :Description
//      The OM_TRACEn behaves identically to the OM_OUTPUTn macro in the
//      debug (CEXTEND_DEBUG) build of the software.  In the release build
//      (CEXTEND_RELEASE) the macro performs no actions.
//
//  :Definition
//"

#if defined(CEXTEND_DEBUG)

    #define OM_TRACE6(eType,outMsgFmt,argA,argB,argC,argD,argE,argF) {  \
        CExOutput::Manager::singleton().generate_output_event_va(       \
            (eType), (__FILE__), (__LINE__), (NULL), (outMsgFmt),       \
            (argA), (argB), (argC), (argD), (argE), (argF) );           }

    #define OM_TRACE5(eType,outMsgFmt,argA,argB,argC,argD,argE) \
                OM_TRACE6(eType,outMsgFmt,argA,argB,argC,argD,argE,0)

    #define OM_TRACE4(eType,outMsgFmt,argA,argB,argC,argD) \
                OM_TRACE6(eType,outMsgFmt,argA,argB,argC,argD,0,0)

    #define OM_TRACE3(eType,outMsgFmt,argA,argB,argC) \
                OM_TRACE6(eType,outMsgFmt,argA,argB,argC,0,0,0)

    #define OM_TRACE2(eType,outMsgFmt,argA,argB) \
                OM_TRACE6(eType,outMsgFmt,argA,argB,0,0,0,0)

    #define OM_TRACE1(eType,outMsgFmt,argA) \
                OM_TRACE6(eType,outMsgFmt,argA,0,0,0,0,0)

    #define OM_TRACE0(eType,outMsgFmt) \
                OM_TRACE6(eType,outMsgFmt,0,0,0,0,0,0)

    #define OMS_TRACE6(eType,outMsgFmt,argA,argB,argC,argD,argE,argF) { \
        if ( ___CExOutput_DebugScope.gen_output() == true ) {           \
            CExOutput::Manager::singleton().generate_output_event_va(   \
                eType, (__FILE__), (__LINE__),                          \
                ___CExOutput_DebugScope.scope_name(), (outMsgFmt),      \
                (argA), (argB), (argC), (argD), (argE), (argF) ); }     }

    #define OMS_TRACE5(eType,outMsgFmt,argA,argB,argC,argD,argE) \
                OMS_TRACE6(eType,outMsgFmt,argA,argB,argC,argD,argE,0)

    #define OMS_TRACE4(eType,outMsgFmt,argA,argB,argC,argD) \
                OMS_TRACE6(eType,outMsgFmt,argA,argB,argC,argD,0,0)

    #define OMS_TRACE3(eType,outMsgFmt,argA,argB,argC) \
                OMS_TRACE6(eType,outMsgFmt,argA,argB,argC,0,0,0)

    #define OMS_TRACE2(eType,outMsgFmt,argA,argB) \
                OMS_TRACE6(eType,outMsgFmt,argA,argB,0,0,0,0)

    #define OMS_TRACE1(eType,outMsgFmt,argA) \
                OMS_TRACE6(eType,outMsgFmt,argA,0,0,0,0,0)

    #define OMS_TRACE0(eType,outMsgFmt) \
                OMS_TRACE6(eType,outMsgFmt,0,0,0,0,0,0)


#else // if defined(CEXTEND_DEBUG)

    #define OM_TRACE6(eType,outMsgFmt,argA,argB,argC,argD,argE,argF)    {}
    #define OM_TRACE5(eType,outMsgFmt,argA,argB,argC,argD,argE)         {}
    #define OM_TRACE4(eType,outMsgFmt,argA,argB,argC,argD)              {}
    #define OM_TRACE3(eType,outMsgFmt,argA,argB,argC)                   {}
    #define OM_TRACE2(eType,outMsgFmt,argA,argB)                        {}
    #define OM_TRACE1(eType,outMsgFmt,argA)                             {}
    #define OM_TRACE0(eType,outMsgFmt)                                  {}

    #define OMS_TRACE6(eType,outMsgFmt,argA,argB,argC,argD,argE,argF)   {}
    #define OMS_TRACE5(eType,outMsgFmt,argA,argB,argC,argD,argE)        {}
    #define OMS_TRACE4(eType,outMsgFmt,argA,argB,argC,argD)             {}
    #define OMS_TRACE3(eType,outMsgFmt,argA,argB,argC)                  {}
    #define OMS_TRACE2(eType,outMsgFmt,argA,argB)                       {}
    #define OMS_TRACE1(eType,outMsgFmt,argA)                            {}
    #define OMS_TRACE0(eType,outMsgFmt)                                 {}

#endif // defined(CEXTEND_DEBUG)

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_ASSERT
//
//  :Arguments
//      = bool
//          The result of some expression.
//
//  :Description
//      The OM_ASSERT behaves like most macros.
//
//      In the debug build (CEXTEND_DEBUG) tt takes the result of
//      the supplied expression and ensures the result is true.
//
//      If the result is false then the macro generates an output
//      event of the type OM_ETD_ASSERT and then generates a
//      debugger break.  Finally it throws an CExOutput::Exception.
//
//      If the result of the test is true then the macro does
//      nothing.
//
//      In the release build the macro evaluates the expression
//      and throws an CExOutput::Exception if the result is false.
//      It does not genereate a debugger break.
//
//  :OM_DEBUG_ASSERT
//      The OM_DEBUG_ASSERT() macro resolves to the OM_ASSERT() macro
//      in the debug build.  In the release build the OM_DEBUG_ASSERT()
//      resolves to an empty expression (no code).
//
//  :Definition
//"

#define OM_ASSERT(test) {                                           \
    if ( !(test) ) {                                                \
        CExOutput::Manager::singleton().generate_output_event_va(   \
            OM_ETD_ASSERT, (__FILE__), (__LINE__), (NULL),          \
            "Assertion failed (throw) ==> %s", #test );             \
        _OM_OS_BREAK_THROW( "Assertion Failed", #test ); }          }

#define OM_ASSERT_NOTHROW(test) {                                   \
    if ( !(test) ) {                                                \
        CExOutput::Manager::singleton().generate_output_event_va(   \
            OM_ETD_ASSERT, (__FILE__), (__LINE__), (NULL),          \
            "Assertion failed (nothrow) ==> %s", #test );           \
        _OM_OS_BREAK_NOTHROW(); }                                   }

#if defined(CEXTEND_DEBUG)

    #define OM_DEBUG_ASSERT(test)           OM_ASSERT(test)
    #define OM_DEBUG_ASSERT_NOTHROW(test)   OM_ASSERT_NOTHROW(test)

    #define OMS_DEBUG_ASSERT(test) {                                    \
        if ( !(test) ) {                                                \
            CExOutput::Manager::singleton().generate_output_event_va(   \
                OM_ETD_ASSERT, (__FILE__), (__LINE__),                  \
                ___CExOutput_DebugScope.scope_name(),                   \
                "Debug Assertion failed (throw) ==> %s", #test );       \
            _OM_OS_BREAK_THROW( "Assertion Failed", #test ); }          }

    #define OMS_DEBUG_ASSERT_NOTHROW(test) {                            \
        if ( !(test) ) {                                                \
            CExOutput::Manager::singleton().generate_output_event_va(   \
                OM_ETD_ASSERT, (__FILE__), (__LINE__),                  \
                ___CExOutput_DebugScope.scope_name(),                   \
                "Debug Assertion failed (no throw) ==> %s", #test );    \
            _OM_OS_BREAK_NOTHROW(); }                                   }

#else // #if defined(CEXTEND_DEBUG) else RELEASE


    #define OM_DEBUG_ASSERT(test)               {}
    #define OM_DEBUG_ASSERT_NOTHROW(test)       {}

    #define OMS_DEBUG_ASSERT(test)              {}
    #define OMS_DEBUG_ASSERT_NOTHROW(test)      {}

#endif // #if defined(CEXTEND_DEBUG)

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_REPLACE_MFC_TRACE_ASSERT
//
//  :Description
//      If this macro is defined before the inclusion of the
//      CExOutput header files then the standard MFC macros
//      TRACE and ASSERT will be undef'd and replaced with
//      our own versions
//
//  :Defintion
//"

#if defined(OM_REPLACE_MFC_TRACE_ASSERT)
    // Undefine the existing macros
    #if defined(ASSERT)
        #undef ASSERT
    #endif // defined(ASSERT)
    #if defined(TRACE)
        #undef  TRACE
        #undef  TRACE0
        #undef  TRACE1
        #undef  TRACE2
        #undef  TRACE3
    #endif // defined(TRACE)

    #define ASSERT(test)        OM_ASSERT( test )
    #define TRACE(msg)          OM_TRACE( OM_ETD_INFO, msg )
    #define TRACE0(msg)         OM_TRACE0( OM_ETD_INFO, msg )
    #define TRACE1(msg,a)       OM_TRACE1( OM_ETD_INFO, msg, a )
    #define TRACE2(msg,a,b)     OM_TRACE2( OM_ETD_INFO, msg, a, b )
    #define TRACE3(msg,a,b,c)   OM_TRACE3( OM_ETD_INFO, msg, a, b, c )

#endif // defined(OM_REPLACE_MFC_TRACE_ASSERT)

//.


/////////////////////////////////////////////////////////////////////////////
//! OM_REPORT_OBSOLETE
//
//  :Description
//      This macro is used to mark a function as obsolete or replaced.
//
//  :Implementation
//"
#define     OM_REPORT_OBSOLETE(itemName)                                        \
    { CExOutput::Obsolete::get_singleton().trigger(itemName);                   }

#define     OM_REPORT_OBSOLETE_REPLACE(itemName,replaceName)                        \
    { CExOutput::Obsolete::get_singleton().set_replacement(itemName,replaceName);   \
      CExOutput::Obsolete::get_singleton().trigger(itemName);                       }


/////////////////////////////////////////////////////////////////////////////

#endif // _CExOutput_NewMaxros_h



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
//      CExBase
//
//  File:
//      CExtend\Libraries\CExBase\CExBase_StdCPP.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_StdCPP_h
#define _CExBase_StdCPP_h

/////////////////////////////////////////////////////////////////////////////
//! Standard C++ Libraries
//
//  :Description
//      The "CExBase.h" file also includes the most commonly used
//      ANSI "C++" template header files.
//
//  :Warning
//      Microsoft's Visual C++ compiler tends to have a problem with the
//      standard C++ template classes.  When it generates its own internal
//      "mangeled" names in the debug version they exceed the maximum
//      length allowed by the compiler.  This is just a warning, but one
//      which gets re-issued for every instance of a template class.
//      Very irritating!
//
//      To avoid this situation we issue a #pragma to disable that
//      specific warning.  However, we have to issue it both before
//      and after the inclusion of all the C++ header files.
//
//  :Definition
//"

#if defined(CEXTEND_PLATFORM_TYPE_MSWIN32)
    #pragma warning( disable : 4786 )
    #pragma warning( disable : 4503 )
#endif // defined(CEXTEND_PLATFORM_TYPE_MSWIN32)

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    #include <functional>
    #include <vector>
    #include <list>
    #include <deque>
    #include <queue>
    #include <stack>
    #include <set>
    #include <map>
    #include <string>
    #include <algorithm>

#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    #include <functional>
    #include <vector>
    #include <list>
    #include <deque>
    #include <queue>
    #include <stack>
    #include <set>
    #include <map>
    #include <string>
    #include <algorithm>

#else
    #error  "ERROR: This code is platform specific"
#endif


//.

#endif // _CExBase_StdCPP_h


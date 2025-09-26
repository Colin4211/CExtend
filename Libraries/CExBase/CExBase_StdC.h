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
//      CExtend\Libraries\CExBase\CExBase_StdC.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_StdC_h
#define _CExBase_StdC_h

/////////////////////////////////////////////////////////////////////////////
//! Standard C Libraries
//
//  :Description
//      The "CExBase.h" file also includes the most commonly used
//      "C" header files.
//
//  :Definition
//"

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    #define ANSI
    #include <stdarg.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <time.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <float.h>
    #include <math.h>
    #include <limits.h>
    #include <time.h>
    #include <limits.h>

#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    #define ANSI
    #include <stdarg.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <time.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <math.h>
    #include <float.h>
    #include <limits.h>
    #include <time.h>
    #include <float.h>
    #include <limits.h>

#else
    #error  "ERROR: This code is platform specific"
#endif
//.

#endif // _CExBase_StdC_h


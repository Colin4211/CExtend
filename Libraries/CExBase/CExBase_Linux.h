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
//      CExtend\Libraries\CExBase\CExBase_Linux.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_Linux_h
#define _CExBase_Linux_h

/////////////////////////////////////////////////////////////////////////////
//! Linux Specific Includes
//
//  :Description
//      The platform.h header file also includes the most common
//      header files for the current platform type.
//
//  :Definition
//"

#if defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    #define _FILE_OFFSET_BITS 64

    #include <unistd.h>
    #include <errno.h>
    #include <dirent.h>
    #include <fnmatch.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/ioctl.h>
    #include <sys/timeb.h>
    #include <pthread.h>

#endif

//.

#endif // _CExBase_Linux_h

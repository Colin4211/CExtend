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
//      CExtend\Libraries\CExBase\CExBase_Floats.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_Floats_h
#define _CExBase_Floats_h

/////////////////////////////////////////////////////////////////////////////

#if defined(CEXTEND_PLATFORM_TYPE_LINUX_ARM32)
    #define CEXBASE_FLOATS_HAS_IEEE
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        #include <arm-linux-gnueabihf/ieee754.h>
    #endif // defined(CEXBASE_FLOATS_HAS_IEEE)
#elif defined(CEXTEND_PLATFORM_TYPE_LINUX_ARM64)
    #define CEXBASE_FLOATS_HAS_IEEE
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        #include <aarch64-linux-gnu/ieee754.h>
    #endif // defined(CEXBASE_FLOATS_HAS_IEEE)
#elif defined(CEXTEND_PLATFORM_TYPE_LINUX_I32)
    #define CEXBASE_FLOATS_HAS_IEEE
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        #include <i386-linux-gnu/ieee754.h>
    #endif // defined(CEXBASE_FLOATS_HAS_IEEE)
#elif defined(CEXTEND_PLATFORM_TYPE_LINUX_I64)
    #define CEXBASE_FLOATS_HAS_IEEE
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        #include <x86_64-linux-gnu/ieee754.h>
    #endif // defined(CEXBASE_FLOATS_HAS_IEEE)
#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX)


/////////////////////////////////////////////////////////////////////////////
//! Float_Types
//
//  :Description
//      This class is used as an adaptor in template based functions
//      allowing access to the specific FloatXXX_Info type.
//      There are specializations of this template for each defined
//      FloatXXX types.
//
//  :Example
//      |   template < typename T_FLOAT >
//      |       void  print_info( const T_FLOAT & theFloat )
//      |   {
//      |       typename CExBase::Float_Types<T_FLOAT>::float_info_type floatInfo;
//      |       printf( "FloatInfo - %s - %lu\n",
//      |           floatInfo.float_type_name(),
//      |           floatInfo.get_bitsize_total() );
//      |       return;
//      |   }
//      |   void    function1( void )
//      |   {
//      |       Float32     theFloat32 = 0;
//      |       Float64     theFloat64 = 0;
//      |       print_info( theFloat32 );
//      |       print_info( theFloat64 );
//      |       return;
//      |   }
//
//  :Declaration
//"
namespace CExBase
{
    template  < typename T_FLOAT >
        class Float_Types
        {
            Float_Types( void ) { return; };
        };
}
//.


/////////////////////////////////////////////////////////////////////////////
//! FloatXXX
//
//  :Description
//      The Typename for the different sized floats is
//      FloatXXX where XXX is the number of bits actually used
//      to store the floating point number.
//
//      To retrieve various metrics about a specific sized float
//      and the values contained within use the appropriate
//      FloatXXX_Info type.
//
//      Please note that the number of bits used in the name may not
//      be the number of bits actually used in memory to store the
//      float.  See the FloatXXX_Info::get_bitsize_empty() function.
//
//      There are several #define's that describe the size of a
//      float.
//          = FloatXXX_BITSIZE_MANTISSA
//              Number of bits used in MANTISSA
//          = FloatXXX_BITSIZE_EXPONENT
//              Number of bits used in EXPONENT
//          = FloatXXX_BITSIZE_SIGN
//              Number of bits in SIGN
//          = FloatXXX_BITSIZE_EXTRA
//              Number of extra bits in value.  There may be float types
//              that have bits that dont fall in the above catagory but
//              are part of the value.
//              This number represents the number of those bits
//          = FloatXXX_BITSIZE_TOTAL
//              Total number of bits actually used.  This is the sum
//              of MANTISSA+EXPONENT+SIGN+EXTRA
//          = FloatXXX_BITSIZE_EMPTY
//              Number of empty or unused bits.  The total number of
//              bits used to store this value in memory is equal to
//              the value TOTAL+EMPTY
//
//      If a type size cannot be represented on a given platform then
//      the type will NOT be defined.  It is recomended that testing
//      definition of the symbol FloatXXX_SIZEOF be used to determine
//      if that type is available.
//      Example:
//          #if defined(Float32_SIZEOF)
//              ---- do something with it
//          #endif
//
//      The value of this symbol (if defined) is the number of bytes
//      (sizeof()) of the float.  Note that the following constraints
//      always apply
//          -   FloatXXX_BITSIZE_TOTAL <= (FloatXXX_SIZEOF*8)
//          -   (FloatXXX_BITSIZE_TOTAL+FloatXXX_BITSIZE_EMPTY) == (FloatXXX_SIZEOF*8)
//
//      If a FloatXXX type is defined then there is a FloatXXX_Union
//      as part of CExBase namespace.  This union allows direct access
//      to the individual fields of a floating point number.
//      Various function signatures and types are defined in the
//      Union to ease its use by providing a consistent interface.
//      (useful with template functions)
//
//      Some Float types have extra or empty bits.  The FloatXXX_Union
//      type has a validate function that is always present even if the
//      FloatXXX type has no extra or empty bits.  The validate()
//      function is used to automatically set these bits to an
//      appropriate and consistent value.
//
//.

/////////////////////////////////////////////////////////////////////////////

#include "CExBase_Float32.h"
#include "CExBase_Float64.h"
#include "CExBase_Float80.h"
#include "CExBase_Float96.h"
#include "CExBase_Float128.h"

/////////////////////////////////////////////////////////////////////////////

#endif  // _CExBase_Floats_h



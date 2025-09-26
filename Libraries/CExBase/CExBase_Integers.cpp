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
//      CExtend\Libraries\CExBase\CExBase.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#include "CExBase.h"

namespace CExBase
{

/////////////////////////////////////////////////////////////////////////////

#if defined(Uint8_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Uint8>         Uint8_INFO( 8 );
#endif // defined(Uint8_SIZEOF)

#if defined(Int8_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Int8>          Int8_INFO( 7 );
#endif // defined(Int8_SIZEOF)

/////////////////////////////////////////////////////////////////////////////

#if defined(Uint16_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Uint16>        Uint16_INFO( 16 );
#endif // defined(Uint16_SIZEOF)

#if defined(Int16_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Int16>         Int16_INFO( 15 );
#endif // defined(Int16_SIZEOF)

/////////////////////////////////////////////////////////////////////////////

#if defined(Uint32_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Uint32>        Uint32_INFO( 32 );
#endif // defined(Uint32_SIZEOF)

#if defined(Int32_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Int32>         Int32_INFO( 31 );
#endif // defined(Int32_SIZEOF)

/////////////////////////////////////////////////////////////////////////////

#if defined(Uint64_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Uint64>        Uint64_INFO( 64 );
#endif // defined(Uint64_SIZEOF)

#if defined(Int64_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Int64>         Int64_INFO( 63 );
#endif // defined(Int64_SIZEOF)

/////////////////////////////////////////////////////////////////////////////

#if defined(Uint128_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Uint128>       Uint128_INFO( 128 );
#endif // defined(Uint128_SIZEOF)

#if defined(Int128_SIZEOF)
    CEXTEND_CONSTEXPR_DEFINE    Integer_INFO<Int128>        Int128_INFO( 127 );
#endif // defined(Int128_SIZEOF)

/////////////////////////////////////////////////////////////////////////////

}; // namespace CExBase



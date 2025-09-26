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
//      CExtend\Libraries\CExBase\CExBase_SetTypes.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_SetTypes_h
#define _CExBase_SetTypes_h

/////////////////////////////////////////////////////////////////////////////
//! Set Types
//
//  :Definition
//"


typedef std::set< int >                     IntSet;
typedef std::set< std::string >             StringSet;
typedef std::set< std::wstring >            WStringSet;

#if defined(Uint8_SIZEOF)
    typedef std::set< Uint8 >               Uint8Set;
#endif // defined(Uint8_SIZEOF)

#if defined(Uint16_SIZEOF)
    typedef std::set< Uint16 >              Uint16Set;
#endif // defined(Uint16_SIZEOF)

#if defined(Uint32_SIZEOF)
    typedef std::set< Uint32 >              Uint32Set;
#endif // defined(Uint32_SIZEOF)

#if defined(Uint64_SIZEOF)
    typedef std::set< Uint64 >              Uint64Set;
#endif // defined(Uint64_SIZEOF)

#if defined(Uint128_SIZEOF)
    typedef std::set< Uint128 >             Uint128Set;
#endif // defined(Uint128_SIZEOF)


#if defined(Int8_SIZEOF)
    typedef std::set< Int8 >                Int8Set;
#endif // defined(Int8_SIZEOF)

#if defined(Int16_SIZEOF)
    typedef std::set< Int16 >               Int16Set;
#endif // defined(Int16_SIZEOF)

#if defined(Int32_SIZEOF)
    typedef std::set< Int32 >               Int32Set;
#endif // defined(Int32_SIZEOF)

#if defined(Int64_SIZEOF)
    typedef std::set< Int64 >               Int64Set;
#endif // defined(Int64_SIZEOF)

#if defined(Int128_SIZEOF)
    typedef std::set< Int128 >              Int128Set;
#endif // defined(Int128_SIZEOF)

#if defined(Float32_SIZEOF)
    typedef std::set< Float32 >             Float32Set;
#endif // defined(Float32_SIZEOF)

#if defined(Float64_SIZEOF)
    typedef std::set< Float64 >             Float64Set;
#endif // defined(Float64_SIZEOF)

#if defined(Float128_SIZEOF)
    typedef std::set< Float128 >            Float128Set;
#endif // defined(Float128_SIZEOF)


//.

#endif // _CExBase_SetTypes_h


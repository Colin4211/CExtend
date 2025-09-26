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
//      CExtend\Libraries\CExBase\CExBase_ListTypes.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_ListTypes_h
#define _CExBase_ListTypes_h

/////////////////////////////////////////////////////////////////////////////
//! List Types
//
//  :Definition
//"

typedef std::list< int >                    IntList;
typedef std::list< std::string >            StringList;
typedef std::list< std::wstring >           WStringList;

#if defined(Uint8_SIZEOF)
    typedef std::list< Uint8 >              Uint8List;
#endif // defined(Uint8_SIZEOF)

#if defined(Uint16_SIZEOF)
    typedef std::list< Uint16 >             Uint16List;
#endif // defined(Uint16_SIZEOF)

#if defined(Uint32_SIZEOF)
    typedef std::list< Uint32 >             Uint32List;
#endif // defined(Uint32_SIZEOF)

#if defined(Uint64_SIZEOF)
    typedef std::list< Uint64 >             Uint64List;
#endif // defined(Uint64_SIZEOF)

#if defined(Uint128_SIZEOF)
    typedef std::list< Uint128 >            Uint128List;
#endif // defined(Uint128_SIZEOF)


#if defined(Int8_SIZEOF)
    typedef std::list< Int8 >               Int8List;
#endif // defined(Int8_SIZEOF)

#if defined(Int16_SIZEOF)
    typedef std::list< Int16 >              Int16List;
#endif // defined(Int16_SIZEOF)

#if defined(Int32_SIZEOF)
    typedef std::list< Int32 >              Int32List;
#endif // defined(Int32_SIZEOF)

#if defined(Int64_SIZEOF)
    typedef std::list< Int64 >              Int64List;
#endif // defined(Int64_SIZEOF)

#if defined(Int128_SIZEOF)
    typedef std::list< Int128 >             Int128List;
#endif // defined(Int128_SIZEOF)


#if defined(Float32_SIZEOF)
    typedef std::list< Float32 >            Float32List;
#endif // defined(Float32_SIZEOF)

#if defined(Float64_SIZEOF)
    typedef std::list< Float64 >            Float64List;
#endif // defined(Float64_SIZEOF)

#if defined(Float128_SIZEOF)
    typedef std::list< Float128 >           Float128List;
#endif // defined(Float128_SIZEOF)

//.

#endif // _CExBase_ListTypes_h


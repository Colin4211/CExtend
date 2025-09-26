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
//      CExtend\Libraries\CExBase\CExBase_VectorTypes.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_VectorTypes_h
#define _CExBase_VectorTypes_h

/////////////////////////////////////////////////////////////////////////////
//! Vector Types
//
//  :Definition
//"

typedef std::vector< std::string >          StringVector;
typedef std::vector< std::wstring >         WStringVector;

#if defined(Uint8_SIZEOF)
    typedef std::vector< Uint8 >            Uint8Vector;
#endif // defined(Uint8_SIZEOF)

#if defined(Uint16_SIZEOF)
    typedef std::vector< Uint16 >           Uint16Vector;
#endif // defined(Uint16_SIZEOF)

#if defined(Uint32_SIZEOF)
    typedef std::vector< Uint32 >           Uint32Vector;
#endif // defined(Uint32_SIZEOF)

#if defined(Uint64_SIZEOF)
    typedef std::vector< Uint64 >           Uint64Vector;
#endif // defined(Uint64_SIZEOF)

#if defined(Uint128_SIZEOF)
    typedef std::vector< Uint128 >          Uint128Vector;
#endif // defined(Uint128_SIZEOF)


#if defined(Int8_SIZEOF)
    typedef std::vector< Int8 >             Int8Vector;
#endif // defined(Int8_SIZEOF)

#if defined(Int16_SIZEOF)
    typedef std::vector< Int16 >            Int16Vector;
#endif // defined(Int16_SIZEOF)

#if defined(Int32_SIZEOF)
    typedef std::vector< Int32 >            Int32Vector;
#endif // defined(Int32_SIZEOF)

#if defined(Int64_SIZEOF)
    typedef std::vector< Int64 >            Int64Vector;
#endif // defined(Int64_SIZEOF)

#if defined(Int128_SIZEOF)
    typedef std::vector< Int128 >           Int128Vector;
#endif // defined(Int128_SIZEOF)



#if defined(Float32_SIZEOF)
    typedef std::vector< Float32 >          Float32Vector;
#endif // defined(Float32_SIZEOF)

#if defined(Float64_SIZEOF)
    typedef std::vector< Float64 >          Float64Vector;
#endif // defined(Float64_SIZEOF)

#if defined(Float128_SIZEOF)
    typedef std::vector< Float128 >         Float128Vector;
#endif // defined(Float128_SIZEOF)

//.

#endif // _CExBase_VectorTypes_h


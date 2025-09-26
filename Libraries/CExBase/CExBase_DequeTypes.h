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
//      CExtend\Libraries\CExBase\CExBase_DequeTypes.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_DequeTypes_h
#define _CExBase_DequeTypes_h

/////////////////////////////////////////////////////////////////////////////
//! Deque Types
//
//  :Definition
//"

typedef std::deque< int >                   IntDeque;
typedef std::deque< std::string >           StringDeque;
typedef std::deque< std::wstring >          WStringDeque;

#if defined(Uint8_SIZEOF)
    typedef std::deque< Uint8 >             Uint8Deque;
#endif // defined(Uint8_SIZEOF)

#if defined(Uint16_SIZEOF)
    typedef std::deque< Uint16 >            Uint16Deque;
#endif // defined(Uint16_SIZEOF)

#if defined(Uint32_SIZEOF)
    typedef std::deque< Uint32 >            Uint32Deque;
#endif // defined(Uint32_SIZEOF)

#if defined(Uint64_SIZEOF)
    typedef std::deque< Uint64 >            Uint64Deque;
#endif // defined(Uint64_SIZEOF)

#if defined(Uint128_SIZEOF)
    typedef std::deque< Uint128 >           Uint128Deque;
#endif // defined(Uint128_SIZEOF)


#if defined(Int8_SIZEOF)
    typedef std::deque< Int8 >              Int8Deque;
#endif // defined(Int8_SIZEOF)

#if defined(Int16_SIZEOF)
    typedef std::deque< Int16 >             Int16Deque;
#endif // defined(Int16_SIZEOF)

#if defined(Int32_SIZEOF)
    typedef std::deque< Int32 >             Int32Deque;
#endif // defined(Int32_SIZEOF)

#if defined(Int64_SIZEOF)
    typedef std::deque< Int64 >             Int64Deque;
#endif // defined(Int64_SIZEOF)

#if defined(Int128_SIZEOF)
    typedef std::deque< Int128 >            Int128Deque;
#endif // defined(Int128_SIZEOF)



#if defined(Float32_SIZEOF)
    typedef std::deque< Float32 >           Float32Deque;
#endif // defined(Float32_SIZEOF)

#if defined(Float64_SIZEOF)
    typedef std::deque< Float64 >           Float64Deque;
#endif // defined(Float64_SIZEOF)

#if defined(Float128_SIZEOF)
    typedef std::deque< Float128 >          Float128Deque;
#endif // defined(Float128_SIZEOF)


//.

#endif // _CExBase_DequeTypes_h


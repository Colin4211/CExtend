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
//      CExtend\Libraries\CExBase\CExBase_Integers.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_Integers_h
#define _CExBase_Integers_h

/////////////////////////////////////////////////////////////////////////////
//! Integer_CONSTANT
//
//  :Description
//      This class works in conjunction with the UintXX_CONSTANT() and
//      IntXX_CONSTANT().  The purpose is that given an integer number
//      it converts it to a constant of the specified type.
//
//      Normally this could be achieved by typing the number as
//      1234i64.  To get a signed 64 bit int.  But support for this
//      for all types varies by platform and compiler.  Especially
//      for some of the larger types that are only partially supported
//
//      Looking at Int128.  You cant declare super large numbers
//      at compile time.
//
//      The solution is this class.  In combination with the
//      IntXX_CONSTANT() macro this will convert a number to a
//      value.
//
//      It uses a slight of hand trick to convert the supplied number
//      to a string.  Which is then converted back to a integer by
//      the class.
//
//      Please note that the conversion function is not robust if
//      it is called with bad data.  (Like a string with non digits)
//      And does not handle overflow.  It is up to the caller to ensure
//      that the values supplied to this class are themselved valid.
//
//      Also, it is possible (because of how constexpr works) that this
//      function will execute at run time and not compile time
//      (Bad, we want compile time). So the UintXX_CONSTANT() macros
//      only use this function when they absolutely have to.  (That is
//      there is no compiler supplied mechanism to do so directly)
//
//      Consider using the constexpr keyword with the value that
//      receives the value from the UintXX_CONSTANT() macro.
//
//      Further to this, some compilers do not support constexpr
//      and the code may not be able to run at compile time.
//
//  :Implementation
//"
namespace CExBase
{

template < typename T_INT_TYPE >
    class  Integer_CONSTANT
{
    private:
        const T_INT_TYPE   m_ResultVal;
    public:
        CEXTEND_CONSTEXPR_DECLARE Integer_CONSTANT( const char * pszString )
            : m_ResultVal( get_value(pszString) )
        {
            return;
        }
        CEXTEND_CONSTEXPR_DECLARE  T_INT_TYPE  value( void ) const { return (m_ResultVal); };
    private:
        CEXTEND_CONSTEXPR_DECLARE  T_INT_TYPE  get_value( const char * pszString )
        {
            T_INT_TYPE resultVal = 0;
            {
                if ( pszString != NULL )
                {
                    bool fNeg = false;
                    for ( size_t strPos = 0; pszString[strPos] != 0; strPos++ )
                    {
                        char theChar = pszString[strPos];
                        if ( (theChar=='-') && (strPos==0) )
                        {
                            fNeg = true;
                        }
                        else if ( (theChar>='0') && (theChar<='9') )
                        {
                            T_INT_TYPE theValue = static_cast<T_INT_TYPE>(theChar-'0');
                            resultVal   *= 10;
                            resultVal   += theValue;
                        }
                        else
                        {
                            resultVal = (0);
                            break;
                        }
                    }
                    if ( fNeg == true )
                    {
                        CEXTEND_CONSTEXPR_DECLARE  T_INT_TYPE   minusOne = 0 - 1;
                        resultVal = resultVal * minusOne;
                    }
                }
            }
            return (resultVal);
        };
};

}; // namespace CExBase

/////////////////////////////////////////////////////////////////////////////
//! Integer_INFO
//
//  :Description
//      This constexpr compatible class is used to calculate

namespace CExBase
{

template < typename T_INT_TYPE >
    class  Integer_INFO
{
    private:
        const T_INT_TYPE    m_DummyNumber;
        const size_t        m_SizeBytes;
        const size_t        m_SizeBits;
        const bool          m_fSignedType;
        const T_INT_TYPE    m_MinValue;
        const T_INT_TYPE    m_MaxValue;
    public:
        CEXTEND_CONSTEXPR_DECLARE  Integer_INFO( const T_INT_TYPE & dummyNumber )
            :   m_DummyNumber( dummyNumber )
            ,   m_SizeBytes( sizeof(T_INT_TYPE) )
            ,   m_SizeBits( sizeof(T_INT_TYPE) * 8 )
            ,   m_fSignedType( get_signed_type() )
            ,   m_MinValue( get_min_value() )
            ,   m_MaxValue( get_max_value() )
        {
            return;
        }
        CEXTEND_CONSTEXPR_DECLARE size_t        size_bytes( void ) const    { return (m_SizeBytes);     };
        CEXTEND_CONSTEXPR_DECLARE size_t        size_bits( void ) const     { return (m_SizeBits);      };
        CEXTEND_CONSTEXPR_DECLARE bool          signed_type( void ) const   { return (m_fSignedType);   };
        CEXTEND_CONSTEXPR_DECLARE T_INT_TYPE    min_value( void ) const     { return (m_MinValue);      };
        CEXTEND_CONSTEXPR_DECLARE T_INT_TYPE    max_value( void ) const     { return (m_MaxValue);      };

    private:
        CEXTEND_CONSTEXPR_DECLARE   bool    get_signed_type( void )
            {
                T_INT_TYPE nValue = 0;
                nValue--;
                return ( (nValue > 0) ? false : true );
            };
        CEXTEND_CONSTEXPR_DECLARE   T_INT_TYPE  get_min_value( void )
            {
                T_INT_TYPE resultVal = 0;
                if ( get_signed_type() == false )
                {
                    resultVal = 0;
                }
                else
                {
                    size_t  bitShift = (sizeof(T_INT_TYPE) * 8) - 1;
                    resultVal = 1;
                    resultVal = resultVal << bitShift;
                }
                return (resultVal);
            };
        CEXTEND_CONSTEXPR_DECLARE  T_INT_TYPE  get_max_value( void )
            {
                T_INT_TYPE resultVal = 0;
                if ( get_signed_type() == false )
                {
                    resultVal = 0;
                    resultVal--;
                    return (resultVal);
                }
                else
                {
                    size_t  bitShift = (sizeof(T_INT_TYPE) * 8) - 1;
                    resultVal = 1;
                    resultVal = resultVal << bitShift;
                    resultVal = ~resultVal;
                }
                return (resultVal);
            }
};


}; // namespace CExBase


/////////////////////////////////////////////////////////////////////////////
//! Integer Types
//
//  :Description
//      These sized types are designed to allow easier development of
//      portable code.  These types will always represent the exact
//      size that they advertise.  If that size of type is not available
//      on a given platform then the type is undefined.
//
//      To write portable code use the Typename_SIZEOF macro
//      to determine if a type is available.
//
//      For Example
//          #if defined(Uint32_SIZEOF)
//              Uint32  myCounter = 0;
//          #else
//              #error "ERROR: Uint32 not available on this platform"
//          #endif
//
//  :Definition
//"


/////////////////////////////////////////////////////////////////////////////
//  Uint8 - Int8

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    typedef unsigned char           Uint8;
    #define Uint8_SIZEOF            (sizeof(Uint8))
    #define Uint8_MIN               (0)
    #define Uint8_MAX               (UCHAR_MAX)
    #define Uint8_CONSTANT(nVal)    (static_cast<Uint8>(nVal))

    typedef signed char             Int8;
    #define Int8_SIZEOF             (sizeof(Int8))
    #define Int8_MIN                (SCHAR_MIN)
    #define Int8_MAX                (SCHAR_MAX)
    #define Int8_CONSTANT(nVal)     (static_cast<Int8>(nVal))

#elif  defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    typedef __UINT8_TYPE__              Uint8;
    #define Uint8_SIZEOF                (sizeof(Uint8))
    #define Uint8_MIN                   (0)
    #define Uint8_MAX                   (__UINT8_MAX__)
    #define Uint8_CONSTANT(nVal)        (__UINT8_C(nVal))

    typedef __INT8_TYPE__               Int8;
    #define Int8_SIZEOF                 (sizeof(Int8))
    #define Int8_MIN                    (SCHAR_MIN)
    #define Int8_MAX                    (__INT8_MAX__)
    #define Int8_CONSTANT(nVal)         (__INT8_C(nVal))

#else

    #error "ERROR: This code is platform specific"

#endif // defined(CEXTEND_PLATFORM_TYPE_MSWIN32)


#if defined(Uint8_SIZEOF)

    namespace CExBase
    {
        extern const Integer_INFO<Uint8>       Uint8_INFO;
    }

    #if !defined(Uint8_MIN)
        #define Uint8_MIN                           (CExBase::Uint8_INFO.min_value())
    #endif // !defined(Uint8_MIN)

    #if !defined(Uint8_MAX)
        #define Uint8_MAX                           (CExBase::Uint8_INFO.max_value())
    #endif // !defined(Uint8_MAX)

    #if !defined(Uint8_CONSTANT)
        #define Uint8_CONSTANT(NUMBER)              (CExBase::Integer_CONSTANT<Uint8>(#NUMBER).value())
    #endif // !defined(Uint8_CONSTANT)

#endif // defined(Uint8_SIZEOF)

#if defined(Int8_SIZEOF)

    namespace CExBase
    {
        extern const Integer_INFO<Int8>        Int8_INFO;
    }

    #if !defined(Int8_MIN)
        #define Int8_MIN                            (CExBase::Int8_INFO.min_value())
    #endif // !defined(Int8_MIN)

    #if !defined(Int8_MAX)
        #define Int8_MAX                            (CExBase::Int8_INFO.max_value())
    #endif // !defined(Int8_MAX)

    #if !defined(Int8_CONSTANT)
        #define Int8_CONSTANT(NUMBER)               (CExBase::Integer_CONSTANT<Int8>(#NUMBER).value())
    #endif // !defined(Int8_CONSTANT)

#endif // defined(Int8_SIZEOF)


/////////////////////////////////////////////////////////////////////////////
//  Uint16 - Int16

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    typedef unsigned short              Uint16;
    #define Uint16_SIZEOF               (sizeof(Uint16))
    #define Uint16_MIN                  (0)
    #define Uint16_MAX                  (USHRT_MAX)
    #define Uint16_CONSTANT(nVal)       (static_cast<Uint16>(nVal))

    typedef signed short                Int16;
    #define Int16_SIZEOF                (sizeof(Int16))
    #define Int16_MIN                   (SHRT_MIN)
    #define Int16_MAX                   (SHRT_MAX)
    #define Int16_CONSTANT(nVal)        (static_cast<Int16>(nVal))

#elif  defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    typedef __UINT16_TYPE__             Uint16;
    #define Uint16_SIZEOF               (sizeof(Uint16))
    #define Uint16_MIN                  (0)
    #define Uint16_MAX                  (__UINT16_MAX__)
    #define Uint16_CONSTANT(nVal)       (__UINT16_C(nVal))

    typedef __INT16_TYPE__              Int16;
    #define Int16_SIZEOF                (sizeof(Int16))
    #define Int16_MIN                   (SHRT_MIN)
    #define Int16_MAX                   (__INT16_MAX__)
    #define Int16_CONSTANT(nVal)        (__INT16_C(nVal))

#else

    #error "ERROR: This code is platform specific"

#endif // defined(CEXTEND_PLATFORM_TYPE_MSWIN32)


#if defined(Uint16_SIZEOF)

    namespace CExBase
    {
        extern const Integer_INFO<Uint16>      Uint16_INFO;
    }

    #if !defined(Uint16_MIN)
        #define Uint16_MIN                          (CExBase::Uint16_INFO.min_value())
    #endif // !defined(Uint16_MIN)

    #if !defined(Uint16_MAX)
        #define Uint16_MAX                          (CExBase::Uint16_INFO.max_value())
    #endif // !defined(Uint16_MAX)

    #if !defined(Uint16_CONSTANT)
        #define Uint16_CONSTANT(NUMBER)             (CExBase::Integer_CONSTANT<Uint16>(#NUMBER).value())
    #endif // !defined(Uint16_CONSTANT)

#endif // defined(Uint16_SIZEOF)


#if defined(Int16_SIZEOF)

    namespace CExBase
    {
        extern const Integer_INFO<Int16>       Int16_INFO;
    }

    #if !defined(Int16_MIN)
        #define Int16_MIN                           (CExBase::Int16_INFO.min_value())
    #endif // !defined(Int16_MIN)

    #if !defined(Int16_MAX)
        #define Int16_MAX                           (CExBase::Int16_INFO.max_value())
    #endif // !defined(Int16_MAX)

    #if !defined(Int16_CONSTANT)
        #define Int16_CONSTANT(NUMBER)              (CExBase::Integer_CONSTANT<Int16>(#NUMBER).value())
    #endif // !defined(Int16_CONSTANT)

#endif // defined(Int16_SIZEOF)



/////////////////////////////////////////////////////////////////////////////
//  Uint32 - Int32

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    typedef unsigned int                Uint32;
    #define Uint32_SIZEOF               (sizeof(Uint32))
    #define Uint32_MIN                  (0)
    #define Uint32_MAX                  (UINT_MAX)
    #define Uint32_CONSTANT(nVal)       (static_cast<Uint32>(nVal))

    typedef signed int                  Int32;
    #define Int32_SIZEOF                (sizeof(Int32))
    #define Int32_MIN                   (INT_MIN)
    #define Int32_MAX                   (INT_MAX)
    //#define Int32_CONSTANT(nVal)        (static_cast<Int32>(nVal))

#elif  defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    typedef __UINT32_TYPE__             Uint32;
    #define Uint32_SIZEOF               (sizeof(Uint32))
    #define Uint32_MIN                  (0)
    #define Uint32_MAX                  (__UINT32_MAX__)
    #define Uint32_CONSTANT(nVal)       (__UINT32_C(nVal))

    typedef __INT32_TYPE__              Int32;
    #define Int32_SIZEOF                (sizeof(Int32))
    #define Int32_MIN                   (INT_MIN)
    #define Int32_MAX                   (__INT32_MAX__)
    #define Int32_CONSTANT(nVal)        (__INT32_C(nVal))

#else

    #error "ERROR: This code is platform specific"

#endif // defined(CEXTEND_PLATFORM_TYPE_MSWIN32)


#if defined(Uint32_SIZEOF)

    namespace CExBase
    {
        extern const CExBase::Integer_INFO<Uint32>      Uint32_INFO;
    }

    #if !defined(Uint32_MIN)
        #define Uint32_MIN                          (CExBase::Uint32_INFO.min_value())
    #endif // !defined(Uint32_MIN)

    #if !defined(Uint32_MAX)
        #define Uint32_MAX                          (CExBase::Uint32_INFO.max_value())
    #endif // !defined(Uint32_MAX)

    #if !defined(Uint32_CONSTANT)
        #define Uint32_CONSTANT(NUMBER)             (CExBase::Integer_CONSTANT<Uint32>(#NUMBER).value())
    #endif // !defined(Uint32_CONSTANT)

#endif // defined(Uint32_SIZEOF)


#if defined(Int32_SIZEOF)

    namespace CExBase
    {
        extern const CExBase::Integer_INFO<Int32>       Int32_INFO;
    }

    #if !defined(Int32_MIN)
        #define Int32_MIN                           (CExBase::Int32_INFO.min_value())
    #endif // !defined(Int32_MIN)

    #if !defined(Int32_MAX)
        #define Int32_MAX                           (CExBase::Int32_INFO.max_value())
    #endif // !defined(Int32_MAX)

    #if !defined(Int32_CONSTANT)
        #define Int32_CONSTANT(NUMBER)              (CExBase::Integer_CONSTANT<Int32>(#NUMBER).value())
    #endif // !defined(Int32_CONSTANT)

#endif // defined(Int32_SIZEOF)


/////////////////////////////////////////////////////////////////////////////
//  Uint64 - Int64

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    typedef unsigned __int64            Uint64;
    #define Uint64_SIZEOF               (sizeof(Uint64))
    #define Uint64_MIN                  (0)
    #define Uint64_MAX                  (_UI64_MAX)
    #define Uint64_CONSTANT(nVal)       (static_cast<Uint64>(nVal##i64))


    typedef signed __int64              Int64;
    #define Int64_SIZEOF                (sizeof(Int64))
    #define Int64_MIN                   (_I64_MIN)
    #define Int64_MAX                   (_I64_MAX)
    //#define Int64_CONSTANT(nVal)        (static_cast<Int64>(nVal))

#elif  defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    typedef __UINT64_TYPE__             Uint64;
    #define Uint64_SIZEOF               (sizeof(Uint64))
    #define Uint64_MIN                  (0)
    #define Uint64_MAX                  (__UINT64_MAX__)
    #define Uint64_CONSTANT(nVal)       (__UINT64_C(nVal))

    typedef __INT64_TYPE__              Int64;
    #define Int64_SIZEOF                (sizeof(Int64))
    #define Int64_MIN                   (LLONG_MIN)
    #define Int64_MAX                   (__INT64_MAX__)
    //#define Int64_CONSTANT(nVal)        (__INT64_C(nVal))

#else

    #error "ERROR: This code is platform specific"

#endif // defined(CEXTEND_PLATFORM_TYPE_MSWIN64)


#if defined(Uint64_SIZEOF)

    namespace CExBase
    {
        extern const CExBase::Integer_INFO<Uint64>      Uint64_INFO;
    }

    #if !defined(Uint64_MIN)
        #define Uint64_MIN                          (CExBase::Uint64_INFO.min_value())
    #endif // !defined(Uint64_MIN)

    #if !defined(Uint64_MAX)
        #define Uint64_MAX                          (CExBase::Uint64_INFO.max_value())
    #endif // !defined(Uint64_MAX)

    #if !defined(Uint64_CONSTANT)
        #define Uint64_CONSTANT(NUMBER)             (CExBase::Integer_CONSTANT<Uint64>(#NUMBER).value())
    #endif // !defined(Uint64_CONSTANT)

#endif // defined(Uint64_SIZEOF)


#if defined(Int64_SIZEOF)

    namespace CExBase
    {
        extern const CExBase::Integer_INFO<Int64>       Int64_INFO;
    }

    #if !defined(Int64_MIN)
        #define Int64_MIN                           (CExBase::Int64_INFO.min_value())
    #endif // !defined(Int64_MIN)

    #if !defined(Int64_MAX)
        #define Int64_MAX                           (CExBase::Int64_INFO.max_value())
    #endif // !defined(Int64_MAX)

    #if !defined(Int64_CONSTANT)
        #define Int64_CONSTANT(NUMBER)              (CExBase::Integer_CONSTANT<Int64>(#NUMBER).value())
    #endif // !defined(Int64_CONSTANT)

#endif // defined(Int64_SIZEOF)



/////////////////////////////////////////////////////////////////////////////
//  Uint128 - Int128

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

    // 128bit int not supported on MSWin

#elif  defined(CEXTEND_PLATFORM_TYPE_LINUX_ARM32)

    // 128bit int not supported on Linux_ARM32

#elif  defined(CEXTEND_PLATFORM_TYPE_LINUX_I32)

    // 128bit int not supported on Linux_I32

#elif  defined(CEXTEND_PLATFORM_FAMILY_LINUX)

    typedef unsigned __int128           Uint128;
    #define Uint128_SIZEOF              (sizeof(Uint128))

    typedef signed __int128             Int128;
    #define Int128_SIZEOF               (sizeof(Int128))

#else

    #error "ERROR: This code is platform specific"

#endif // defined(CEXTEND_PLATFORM_TYPE_MSWIN128)


#if defined(Uint128_SIZEOF)

    namespace CExBase
    {
        extern const CExBase::Integer_INFO<Uint128>      Uint128_INFO;
    }

    #if !defined(Uint128_MIN)
        #define Uint128_MIN                          (CExBase::Uint128_INFO.min_value())
    #endif // !defined(Uint128_MIN)

    #if !defined(Uint128_MAX)
        #define Uint128_MAX                          (CExBase::Uint128_INFO.max_value())
    #endif // !defined(Uint128_MAX)

    #if !defined(Uint128_CONSTANT)
        #define Uint128_CONSTANT(NUMBER)             (CExBase::Integer_CONSTANT<Uint128>(#NUMBER).value())
    #endif // !defined(Uint128_CONSTANT)

#endif // defined(Uint128_SIZEOF)


#if defined(Int128_SIZEOF)

    namespace CExBase
    {
        extern const CExBase::Integer_INFO<Int128>       Int128_INFO;
    }

    #if !defined(Int128_MIN)
        #define Int128_MIN                           (CExBase::Int128_INFO.min_value())
    #endif // !defined(Int128_MIN)

    #if !defined(Int128_MAX)
        #define Int128_MAX                           (CExBase::Int128_INFO.max_value())
    #endif // !defined(Int128_MAX)

    #if !defined(Int128_CONSTANT)
        #define Int128_CONSTANT(NUMBER)              (CExBase::Integer_CONSTANT<Int128>(#NUMBER).value())
    #endif // !defined(Int128_CONSTANT)

#endif // defined(Int128_SIZEOF)

/////////////////////////////////////////////////////////////////////////////


#endif  // _CExBase_Integers_h



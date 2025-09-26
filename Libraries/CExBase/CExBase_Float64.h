/////////////////////////////////////////////////////////////////////////////
//
//  CExtend Libraries
//  Copyright (c) 2025, Colin Goodall
//      This software is licensed under the MIT License.
//      See the LICENSE file for details.
//
/////////////////////////////////////////////////////////////////////////////
//
//  Module:
//      CExBase
//
//  File:
//      CExtend\Libraries\CExBase\CExBase_Float64.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_Float64_h_
#define _CExBase_Float64_h_

#if  defined(CEXTEND_PLATFORM_FAMILY_LINUX) || defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

/////////////////////////////////////////////////////////////////////////////
//! Float64
//
//  :Declaration
//"
typedef double                      Float64;
#define Float64_SIZEOF              (sizeof(Float64))
#define Float64_CONSTANT(nVal)      (static_cast<Float64>(nVal))

namespace CExBase
{

typedef union tagFloat64_Info
{
    // Constants
    private:
        static const size_t     bitsize_manitissa   = 52;
        static const size_t     bitsize_exponent    = 11;
        static const size_t     bitsize_sign        = 1;
        static const size_t     bitsize_extra       = 0;
        static const size_t     bitsize_total       = 64;
        static const size_t     bitsize_empty       = 0;
        static const size_t     bitsize             = 64 + 0;
        static const size_t     bytesize            = 8;

    // Embedded Types
    public:
        typedef Float64         float_type;
        typedef Uint8           byte_type;
        typedef Uint64          uint_type;
        typedef Int64           int_type;

    // Union Members
    public:
        float_type          m_Float;
        struct
        {
            byte_type       m_Byte0;
            byte_type       m_Byte1;
            byte_type       m_Byte2;
            byte_type       m_Byte3;
            byte_type       m_Byte4;
            byte_type       m_Byte5;
            byte_type       m_Byte6;
            byte_type       m_Byte7;
        } m_Bytes;
        struct {
            byte_type       m_Mantissa0                 ; // 7         8
            byte_type       m_Mantissa1                 ; // 6         16
            byte_type       m_Mantissa2                 ; // 5         24
            byte_type       m_Mantissa3                 ; // 4         32
            byte_type       m_Mantissa4                 ; // 3         40
            byte_type       m_Mantissa5                 ; // 2         48
            byte_type       m_Mantissa6         :   4   ; // 1(4)      52
            byte_type       m_Exponent0         :   4   ; // 1(4)      56
            byte_type       m_Exponent1         :   4   ; // 0(7)      63
            byte_type       m_Exponent2         :   3   ; // 0(7)      63
            byte_type       m_Sign              :   1   ; // 0(1)      64
        } m_Bits;
        uint_type           m_Uint;
        struct {
            uint_type   m_Mantissa : bitsize_manitissa;
            uint_type   m_Exponent : bitsize_exponent;
            uint_type   m_Sign     : bitsize_sign;
        } m_WideBits;

    // The IEEE field is only available if the compiler supplies
    //  IEEE union definitions.  (Typically only on GNU compilers)
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        typedef ieee754_double  ieee_union_type;
        ieee_union_type         m_IEEE;
    #endif // defined(CEXBASE_FLOATS_HAS_IEEE)

    // Construction
    public:
        tagFloat64_Info( void );
        tagFloat64_Info( const float_type & theFloat );
        explicit tagFloat64_Info( const char & initChar );
        tagFloat64_Info( const byte_type & byte0, const byte_type & byte1, const byte_type & byte2, const byte_type & byte3,
                          const byte_type & byte4, const byte_type & byte5, const byte_type & byte6, const byte_type & byte7 );
        operator float_type( void ) const;
        const float_type & operator = ( const float_type & rhSide );

    // Public Interface
    public:
        void            clear( void );
        const char *    float_type_name( void ) const;
        void            validate( void );
        float_type      get_float( void ) const;
        void            set_float( const float_type & theFloat, bool fValidate = true );
        void            set_nan( bool fPositive = true );
        void            set_infinity( bool fPositive = true );
        void            set_zero( bool fPositive = true );

            // Byte indexing is lowest bits first
            //  So a value of 0x654321 is { 0x21, 0x43, 0x65 }
        byte_type       get_byte( size_t nIndex ) const;
        byte_type       get_byte_mantissa( size_t nIndex ) const;
        byte_type       get_byte_exponent( size_t nIndex ) const;

        bool            get_bit( size_t nBitIndex ) const;
        bool            get_bit_mantissa( size_t nBitIndex ) const;
        bool            get_bit_exponent( size_t nBitIndex ) const;

        bool            is_negative( void ) const           {   return (m_WideBits.m_Sign!=0);                      };
        bool            is_positive( void ) const           {   return (m_WideBits.m_Sign==0);                      };
        bool            is_exponent_ones( void ) const      {   return (m_WideBits.m_Exponent==0x07FF);             };
        bool            is_exponent_zero( void ) const      {   return (m_WideBits.m_Exponent==0);                  };
        bool            is_mantissa_zero( void ) const      {   return (m_WideBits.m_Mantissa==0);                  };
        bool            is_mantissa_non_zero( void ) const  {   return (m_WideBits.m_Mantissa!=0);                  };
        FloatClass      get_float_class( void ) const;
        bool            is_zero( void ) const               {   return (get_float_class()==FloatClass_ZERO);        };
        bool            is_normal( void ) const             {   return (get_float_class()==FloatClass_NORMAL);      };
        bool            is_subnormal( void ) const          {   return (get_float_class()==FloatClass_SUBNORMAL);   };
        bool            is_infinity( void ) const           {   return (get_float_class()==FloatClass_INFINITY);    };
        bool            is_nan( void ) const                {   return (get_float_class()==FloatClass_NAN);         };
        bool            is_finite( void ) const             {   return (get_float_class().is_finite());             };

        bool            set_byte( size_t nIndex, const byte_type & theByte );
        bool            set_byte_mantissa( size_t nIndex, const byte_type & theByte );
        bool            set_byte_exponent( size_t nIndex, const byte_type & theByte );
        bool            set_sign( bool fPositive );
        bool            set_positive( void )                {   return (set_sign(true));            };
        bool            set_negative( void )                {   return (set_sign(false));           };

        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bitsize_mantissa( void ) const          {   return (bitsize_manitissa);         };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bitsize_exponent( void ) const          {   return (bitsize_exponent);          };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bitsize_sign( void ) const              {   return (bitsize_sign);              };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bitsize_extra( void ) const             {   return (bitsize_extra);             };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bitsize_total( void ) const             {   return (bitsize_total);             };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bitsize_empty( void ) const             {   return (bitsize_empty);             };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bitsize( void ) const                   {   return (bitsize);                   };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bytesize( void ) const                  {   return (bytesize);                  };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bytesize_mantissa( void ) const         {   return ((bitsize_manitissa+7)/8);   };
        CEXTEND_CONSTEXPR_FUNCTION  size_t          get_bytesize_exponent( void ) const         {   return ((bitsize_exponent+7)/8);    };

        CEXTEND_CONSTEXPR_FUNCTION  float_type      get_limits_min( void ) const                {   return (DBL_MIN);                   };
        CEXTEND_CONSTEXPR_FUNCTION  float_type      get_limits_max( void ) const                {   return (DBL_MAX);                   };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_min_exp( void ) const            {   return (DBL_MIN_EXP);               };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_max_exp( void ) const            {   return (DBL_MAX_EXP);               };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_min_10_exp( void ) const         {   return (DBL_MIN_10_EXP);            };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_max_10_exp( void ) const         {   return (DBL_MAX_10_EXP);            };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_mantissa_digits( void ) const    {   return (DBL_MANT_DIG);              };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_digits( void ) const             {   return (DBL_DIG);                   };

        // These functions are always defined even if the IEEE definitions
        //  are not present on the target system.
        // If the IEEE definitions are not present then all these functions
        //  return a value of zero.
        float_type      get_ieee_float( void ) const;
        unsigned int    get_ieee_mantissa( size_t nIndex ) const;
        unsigned int    get_ieee_exponent( size_t nIndex ) const;
        unsigned int    get_ieee_sign( void ) const;
        size_t          get_ieee_mantissa_count( void ) const;
        size_t          get_ieee_exponent_count( void ) const;

} Float64_Info;


template <>
    class Float_Types< Float64 >
    {
        public:
        typedef Float64         float_type;
        typedef Float64_Info    float_info_type;
        Float_Types( void ) { return; };
    };

template <>
    class Float_Types< Float64_Info >
    {
        public:
        typedef Float64         float_type;
        typedef Float64_Info    float_info_type;
        Float_Types( void ) { return; };
    };

// Special Case here
//  On some platforms there is a long double.  But it is identical to
//  a double.  So they are both Float64 types.  This
//  Float_Types specialization allows that reverse lookup
//  to occur.  (That is, supplying a long double gets you
//  a Float64_Info which is what we want)
#if defined(CEXTEND_PLATFORM_TYPE_MSWIN_I32) || defined(CEXTEND_PLATFORM_TYPE_MSWIN_I64) || defined(CEXTEND_PLATFORM_TYPE_LINUX_ARM32)
    template <>
        class Float_Types< long double >
        {
            public:
            typedef Float64         float_type;
            typedef Float64_Info    float_info_type;
            Float_Types( void ) { return; };
        };
#endif // defined(CEXTEND_PLATFORM_TYPE_MSWIN_I32)


}; // namespace CExBase

//.


/////////////////////////////////////////////////////////////////////////////

#endif //  defined(CEXTEND_PLATFORM_FAMILY_LINUX) || defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

#endif // _CExBase_Float64_h_


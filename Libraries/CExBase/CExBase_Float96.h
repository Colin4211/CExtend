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
//      CExtend\Libraries\CExBase\CExBase_Float96.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_Float96_h_
#define _CExBase_Float96_h_

#if defined(CEXTEND_PLATFORM_TYPE_LINUX_I32)

/////////////////////////////////////////////////////////////////////////////
//! Float96
//
//  :Declaration
//"
typedef long double                 Float96;
#define Float96_SIZEOF             (sizeof(Float96))
#define Float96_CONSTANT(nVal)     (static_cast<Float96>(nVal##L))

namespace CExBase
{

typedef union tagFloat96_Info
{
    // Constants
    private:
        static const size_t     bitsize_manitissa   = 63;
        static const size_t     bitsize_one_bit     = 1;
        static const size_t     bitsize_exponent    = 15;
        static const size_t     bitsize_sign        = 1;
        static const size_t     bitsize_extra       = 1;
        static const size_t     bitsize_total       = 80;
        static const size_t     bitsize_empty       = 16;
        static const size_t     bitsize             = 80 + 16;
        static const size_t     bytesize            = 12;

    // Embedded Types
    public:
        typedef Float96         float_type;
        typedef Uint8           byte_type;
        typedef Uint64          uint_type;
        typedef Uint32          uint2_type;
        typedef Int64           int_type;

    // Union Members
    public:
        float_type      m_Float;
        struct
        {
            byte_type       m_Byte00;
            byte_type       m_Byte01;
            byte_type       m_Byte02;
            byte_type       m_Byte03;
            byte_type       m_Byte04;
            byte_type       m_Byte05;
            byte_type       m_Byte06;
            byte_type       m_Byte07;
            byte_type       m_Byte08;
            byte_type       m_Byte09;
            byte_type       m_Byte10;
            byte_type       m_Byte11;
        } m_Bytes;
        struct {
            byte_type   m_Mantissa00;           //  8
            byte_type   m_Mantissa01;           //  16
            byte_type   m_Mantissa02;           //  24
            byte_type   m_Mantissa03;           //  32
            byte_type   m_Mantissa04;           //  40
            byte_type   m_Mantissa05;           //  48
            byte_type   m_Mantissa06;           //  56
            byte_type   m_Mantissa07    : 7;    //  63      63
            uint_type   m_OneBit        : 1;    //  1       64
            byte_type   m_Exponent0;            //  8       72
            byte_type   m_Exponent1     : 7;    //  15      79
            byte_type   m_Sign          : 1;    //  1       80
            byte_type   m_Empty0;               //  8       88
            byte_type   m_Empty1;               //  15      96
        } m_Bits;
        struct
        {
            uint_type           m_Uint0;
            uint2_type          m_Uint1;
        };
        struct {
            uint_type   m_Mantissa  : bitsize_manitissa;    //  63  63
            uint_type   m_OneBit    : bitsize_one_bit;      //  1   64
            uint2_type  m_Exponent  : bitsize_exponent;     //  15  79
            uint2_type  m_Sign      : bitsize_sign;         //  1   80
            uint2_type  m_Empty     : bitsize_empty;        //  16  96
        } m_WideBits;

    // The IEEE field is only available if the compiler supplies
    //  IEEE union definitions.  (Typically only on GNU compilers)
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        typedef ieee854_long_double     ieee_union_type;
        ieee_union_type                 m_IEEE;
    #endif // defined(CEXBASE_FLOATS_HAS_IEEE)

    // Construction
    public:
        tagFloat96_Info( void );
        tagFloat96_Info( const float_type & theFloat );
        explicit tagFloat96_Info( const char & initChar );
        tagFloat96_Info( const byte_type & byte0, const byte_type & byte1, const byte_type & byte2, const byte_type & byte3,
                          const byte_type & byte4, const byte_type & byte5, const byte_type & byte6, const byte_type & byte7,
                          const byte_type & byte8, const byte_type & byte9, const byte_type & byte10, const byte_type & byte11 );
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
        bool            is_exponent_ones( void ) const      {   return (m_WideBits.m_Exponent==0x07FFF);            };
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

        CEXTEND_CONSTEXPR_FUNCTION  float_type      get_limits_min( void ) const                {   return (LDBL_MIN);                  };
        CEXTEND_CONSTEXPR_FUNCTION  float_type      get_limits_max( void ) const                {   return (LDBL_MAX);                  };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_min_exp( void ) const            {   return (LDBL_MIN_EXP);              };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_max_exp( void ) const            {   return (LDBL_MAX_EXP);              };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_min_10_exp( void ) const         {   return (LDBL_MIN_10_EXP);           };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_max_10_exp( void ) const         {   return (LDBL_MAX_10_EXP);           };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_mantissa_digits( void ) const    {   return (LDBL_MANT_DIG);             };
        CEXTEND_CONSTEXPR_FUNCTION  int             get_limits_digits( void ) const             {   return (LDBL_DIG);                  };

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

} Float96_Info;


template <>
    class Float_Types< Float96 >
    {
        public:
        typedef Float96         float_type;
        typedef Float96_Info    float_info_type;
        Float_Types( void ) { return; };
    };

template <>
    class Float_Types< Float96_Info >
    {
        public:
        typedef Float96         float_type;
        typedef Float96_Info    float_info_type;
        Float_Types( void ) { return; };
    };

}; // namespace CExBase

//.


/////////////////////////////////////////////////////////////////////////////

#endif // defined(CEXTEND_PLATFORM_TYPE_LINUX_I32)

#endif // _CExBase_Float96_h_


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
//      CExtend\Libraries\CExBase\CExBase_Float80.cpp
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

#if defined(CEXTEND_PLATFORM_TYPE_LINUX_I64)

/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::tagFloat80_Info( void )
{
    clear();
    return;
}


/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::tagFloat80_Info( const float_type & theFloat )
    : m_Float( theFloat )
{
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::tagFloat80_Info( const char & initChar )
{
    clear();
    if ( (initChar=='n') || (initChar=='N') )   {   set_nan();      }
    if ( (initChar=='i') || (initChar=='I') )   {   set_infinity(); }
    if ( (initChar=='z') || (initChar=='Z') )   {   set_zero();     }
    if ( (initChar=='N')    ||
         (initChar=='I')    ||
         (initChar=='Z')    )
    {
        set_negative();  // Capitol Letters are negative
    }
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::tagFloat80_Info( const byte_type & byte0, const byte_type & byte1, const byte_type & byte2, const byte_type & byte3,
                                  const byte_type & byte4, const byte_type & byte5, const byte_type & byte6, const byte_type & byte7,
                                  const byte_type & byte8, const byte_type & byte9, const byte_type & byte10, const byte_type & byte11,
                                  const byte_type & byte12, const byte_type & byte13, const byte_type & byte14, const byte_type & byte15  )
{
    m_Bytes.m_Byte00    = byte0;
    m_Bytes.m_Byte01    = byte1;
    m_Bytes.m_Byte02    = byte2;
    m_Bytes.m_Byte03    = byte3;
    m_Bytes.m_Byte04    = byte4;
    m_Bytes.m_Byte05    = byte5;
    m_Bytes.m_Byte06    = byte6;
    m_Bytes.m_Byte07    = byte7;
    m_Bytes.m_Byte08    = byte8;
    m_Bytes.m_Byte09    = byte9;
    m_Bytes.m_Byte10    = byte10;
    m_Bytes.m_Byte11    = byte11;
    m_Bytes.m_Byte12    = byte12;
    m_Bytes.m_Byte13    = byte13;
    m_Bytes.m_Byte14    = byte14;
    m_Bytes.m_Byte15    = byte15;
    return;
}


/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::operator Float80( void ) const
{
    return (m_Float);
}

/////////////////////////////////////////////////////////////////////////////

const  tagFloat80_Info::float_type &  tagFloat80_Info::operator = ( const float_type & rhSide )
{
    m_Float = rhSide;
    validate();
    return (m_Float);
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat80_Info::clear( void )
{
    m_Bytes.m_Byte00    = 0;
    m_Bytes.m_Byte01    = 0;
    m_Bytes.m_Byte02    = 0;
    m_Bytes.m_Byte03    = 0;
    m_Bytes.m_Byte04    = 0;
    m_Bytes.m_Byte05    = 0;
    m_Bytes.m_Byte06    = 0;
    m_Bytes.m_Byte07    = 0;
    m_Bytes.m_Byte08    = 0;
    m_Bytes.m_Byte09    = 0;
    m_Bytes.m_Byte10    = 0;
    m_Bytes.m_Byte11    = 0;
    m_Bytes.m_Byte12    = 0;
    m_Bytes.m_Byte13    = 0;
    m_Bytes.m_Byte14    = 0;
    m_Bytes.m_Byte15    = 0;
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

const char *  tagFloat80_Info::float_type_name( void ) const
{
    return ("Float80");
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat80_Info::validate( void )
{
    m_Bits.m_OneBit    = 0;
    if ( (m_Bits.m_Exponent0!=0) ||
         (m_Bits.m_Exponent1!=0) )
    {
        m_Bits.m_OneBit = 1;
    }
    else if ( (m_Bits.m_Mantissa0!=0)  ||
              (m_Bits.m_Mantissa1!=0)  ||
              (m_Bits.m_Mantissa2!=0)  ||
              (m_Bits.m_Mantissa3!=0)  ||
              (m_Bits.m_Mantissa4!=0)  ||
              (m_Bits.m_Mantissa5!=0)  ||
              (m_Bits.m_Mantissa6!=0)  ||
              (m_Bits.m_Mantissa7!=0)  )
    {
        m_Bits.m_OneBit = 1;
    }
    m_Bits.m_Empty0    = 0;
    m_Bits.m_Empty1    = 0;
    m_Bits.m_Empty2    = 0;
    m_Bits.m_Empty3    = 0;
    m_Bits.m_Empty4    = 0;
    m_Bits.m_Empty5    = 0;
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::float_type  tagFloat80_Info::get_float( void ) const
{
    return (m_Float);
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat80_Info::set_float( const float_type & theFloat, bool fValidate /*= true*/ )
{
    m_Float = theFloat;
    if ( fValidate != false )
    {
        validate();
    }
    return;
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat80_Info::set_nan( bool fPositive /*= true*/  )
{
    clear();
    m_WideBits.m_Exponent   = 0x07FFF;
    m_WideBits.m_Mantissa   = 1;
    m_WideBits.m_Mantissa   <<= (bitsize_manitissa-1);
    set_sign( fPositive );
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat80_Info::set_infinity( bool fPositive /*= true*/  )
{
    clear();
    m_WideBits.m_Exponent   = 0x07FFF;
    m_WideBits.m_Mantissa   = 0;
    set_sign( fPositive );
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat80_Info::set_zero( bool fPositive /*= true*/  )
{
    clear();
    set_sign( fPositive );
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::byte_type  tagFloat80_Info::get_byte( size_t nIndex ) const
{
    byte_type resultVal = 0;
    if ( nIndex == 0 )          {   resultVal = m_Bytes.m_Byte00;    }
    else if ( nIndex == 1 )     {   resultVal = m_Bytes.m_Byte01;    }
    else if ( nIndex == 2 )     {   resultVal = m_Bytes.m_Byte02;    }
    else if ( nIndex == 3 )     {   resultVal = m_Bytes.m_Byte03;    }
    else if ( nIndex == 4 )     {   resultVal = m_Bytes.m_Byte04;    }
    else if ( nIndex == 5 )     {   resultVal = m_Bytes.m_Byte05;    }
    else if ( nIndex == 6 )     {   resultVal = m_Bytes.m_Byte06;    }
    else if ( nIndex == 7 )     {   resultVal = m_Bytes.m_Byte07;    }
    else if ( nIndex == 8 )     {   resultVal = m_Bytes.m_Byte08;    }
    else if ( nIndex == 9 )     {   resultVal = m_Bytes.m_Byte09;    }
    else if ( nIndex == 10)     {   resultVal = m_Bytes.m_Byte10;    }
    else if ( nIndex == 11)     {   resultVal = m_Bytes.m_Byte11;    }
    else if ( nIndex == 12)     {   resultVal = m_Bytes.m_Byte12;    }
    else if ( nIndex == 13)     {   resultVal = m_Bytes.m_Byte13;    }
    else if ( nIndex == 14)     {   resultVal = m_Bytes.m_Byte14;    }
    else if ( nIndex == 15)     {   resultVal = m_Bytes.m_Byte15;    }
    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::byte_type  tagFloat80_Info::get_byte_mantissa( size_t nIndex ) const
{
    byte_type resultVal = 0;
    if ( nIndex == 0 )      {   resultVal = m_Bits.m_Mantissa0;    }
    else if ( nIndex == 1 ) {   resultVal = m_Bits.m_Mantissa1;    }
    else if ( nIndex == 2 ) {   resultVal = m_Bits.m_Mantissa2;    }
    else if ( nIndex == 3 ) {   resultVal = m_Bits.m_Mantissa3;    }
    else if ( nIndex == 4 ) {   resultVal = m_Bits.m_Mantissa4;    }
    else if ( nIndex == 5 ) {   resultVal = m_Bits.m_Mantissa5;    }
    else if ( nIndex == 6 ) {   resultVal = m_Bits.m_Mantissa6;    }
    else if ( nIndex == 7 ) {   resultVal = m_Bits.m_Mantissa7;    }
    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::byte_type  tagFloat80_Info::get_byte_exponent( size_t nIndex ) const
{
    byte_type resultVal = 0;
    if ( nIndex == 0 )
    {
        resultVal                           = m_Bits.m_Exponent0;
    }
    else if ( nIndex == 1 )
    {
        resultVal                           = m_Bits.m_Exponent1;
    }

    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat80_Info::get_bit( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat80_Info::get_bit_mantissa( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte_mantissa( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat80_Info::get_bit_exponent( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte_exponent( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}

/////////////////////////////////////////////////////////////////////////////

FloatClass  tagFloat80_Info::get_float_class( void ) const
{
    if ( is_exponent_zero() == true )
    {
        if ( is_mantissa_zero() == true )
        {
            return (FloatClass_ZERO);
        }
        else
        {
            return (FloatClass_SUBNORMAL);
        }
    }
    else if ( is_exponent_ones() == true )
    {
        if ( is_mantissa_zero() == true )
        {
            return (FloatClass_INFINITY);
        }
        else
        {
            return (FloatClass_NAN);
        }
    }
    return (FloatClass_NORMAL);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat80_Info::set_byte( size_t nIndex, const byte_type & theByte )
{
         if ( nIndex == 0)      {   m_Bytes.m_Byte00 = theByte;    return (true);  }
    else if ( nIndex == 1)      {   m_Bytes.m_Byte01 = theByte;    return (true);  }
    else if ( nIndex == 2)      {   m_Bytes.m_Byte02 = theByte;    return (true);  }
    else if ( nIndex == 3)      {   m_Bytes.m_Byte03 = theByte;    return (true);  }
    else if ( nIndex == 4)      {   m_Bytes.m_Byte04 = theByte;    return (true);  }
    else if ( nIndex == 5)      {   m_Bytes.m_Byte05 = theByte;    return (true);  }
    else if ( nIndex == 6)      {   m_Bytes.m_Byte06 = theByte;    return (true);  }
    else if ( nIndex == 7)      {   m_Bytes.m_Byte07 = theByte;    return (true);  }
    else if ( nIndex == 8)      {   m_Bytes.m_Byte08 = theByte;    return (true);  }
    else if ( nIndex == 9)      {   m_Bytes.m_Byte09 = theByte;    return (true);  }
    else if ( nIndex == 10)     {   m_Bytes.m_Byte10 = theByte;    return (true);  }
    else if ( nIndex == 11)     {   m_Bytes.m_Byte11 = theByte;    return (true);  }
    else if ( nIndex == 12)     {   m_Bytes.m_Byte12 = theByte;    return (true);  }
    else if ( nIndex == 13)     {   m_Bytes.m_Byte13 = theByte;    return (true);  }
    else if ( nIndex == 14)     {   m_Bytes.m_Byte14 = theByte;    return (true);  }
    else if ( nIndex == 15)     {   m_Bytes.m_Byte15 = theByte;    return (true);  }
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat80_Info::set_byte_mantissa( size_t nIndex, const byte_type & theByte )
{
    if ( nIndex == 0 )          {   m_Bits.m_Mantissa0 = theByte;  return (true); }
    else if ( nIndex == 1 )     {   m_Bits.m_Mantissa1 = theByte;  return (true); }
    else if ( nIndex == 2 )     {   m_Bits.m_Mantissa2 = theByte;  return (true); }
    else if ( nIndex == 3 )     {   m_Bits.m_Mantissa3 = theByte;  return (true); }
    else if ( nIndex == 4 )     {   m_Bits.m_Mantissa4 = theByte;  return (true); }
    else if ( nIndex == 5 )     {   m_Bits.m_Mantissa5 = theByte;  return (true); }
    else if ( nIndex == 6 )     {   m_Bits.m_Mantissa6 = theByte;  return (true); }
    else if ( nIndex == 7 )     {   m_Bits.m_Mantissa7 = theByte;  return (true); }
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat80_Info::set_byte_exponent( size_t nIndex, const byte_type & theByte )
{
    if ( nIndex == 0 )          {   m_Bits.m_Exponent0 = theByte;  return (true); }
    else if ( nIndex == 1 )     {   m_Bits.m_Exponent1 = theByte;  return (true); }
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat80_Info::set_sign( bool fPositive )
{
    m_Bits.m_Sign = ( (fPositive==false) ? 1 : 0 );
    return (true);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat80_Info::float_type  tagFloat80_Info::get_ieee_float( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (m_IEEE.d);
    #else
        return (Float80_CONSTANT(0));
    #endif
}

/////////////////////////////////////////////////////////////////////////////

unsigned int  tagFloat80_Info::get_ieee_mantissa( size_t nIndex ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        if ( nIndex == 0 )
        {
            unsigned int                resultVal   = m_IEEE.ieee.mantissa0;
            static const unsigned int   valMask     = 0x7FFFFFFF;
            resultVal &= valMask;
            return (resultVal);
        }
        else if ( nIndex == 1 )
        {
            return (m_IEEE.ieee.mantissa1);
        }
        return (0);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

unsigned int  tagFloat80_Info::get_ieee_exponent( size_t nIndex ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        if ( nIndex == 0 )  {   return (m_IEEE.ieee.exponent);   }
        return (0);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

unsigned int  tagFloat80_Info::get_ieee_sign( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (m_IEEE.ieee.negative);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

size_t  tagFloat80_Info::get_ieee_mantissa_count( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (2);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

size_t  tagFloat80_Info::get_ieee_exponent_count( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (1);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

#endif // defined(CEXTEND_PLATFORM_TYPE_LINUX_I64)

}; // namespace CExBase



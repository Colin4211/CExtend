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
//      CExtend\Libraries\CExBase\CExBase_Float96.cpp
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

#if defined(CEXTEND_PLATFORM_TYPE_LINUX_I32)

/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::tagFloat96_Info( void )
{
    clear();
    return;
}


/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::tagFloat96_Info( const float_type & theFloat )
    : m_Float( theFloat )
{
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::tagFloat96_Info( const char & initChar )
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

tagFloat96_Info::tagFloat96_Info( const byte_type & byte0, const byte_type & byte1, const byte_type & byte2, const byte_type & byte3,
                                  const byte_type & byte4, const byte_type & byte5, const byte_type & byte6, const byte_type & byte7,
                                  const byte_type & byte8, const byte_type & byte9, const byte_type & byte10, const byte_type & byte11 )
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
    return;
}


/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::operator Float96( void ) const
{
    return (m_Float);
}

/////////////////////////////////////////////////////////////////////////////

const  tagFloat96_Info::float_type &  tagFloat96_Info::operator = ( const float_type & rhSide )
{
    m_Float = rhSide;
    validate();
    return (m_Float);
}


/////////////////////////////////////////////////////////////////////////////

void  tagFloat96_Info::clear( void )
{
    m_Uint0 = 0;
    m_Uint1 = 0;
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

const char *  tagFloat96_Info::float_type_name( void ) const
{
    return ("Float96");
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat96_Info::validate( void )
{
    m_Bits.m_OneBit    = 0;
    if ( (m_Bits.m_Exponent0!=0) ||
         (m_Bits.m_Exponent1!=0) )
    {
        m_Bits.m_OneBit = 1;
    }
    else if ( (m_Bits.m_Mantissa00!=0)  ||
              (m_Bits.m_Mantissa01!=0)  ||
              (m_Bits.m_Mantissa02!=0)  ||
              (m_Bits.m_Mantissa03!=0)  ||
              (m_Bits.m_Mantissa04!=0)  ||
              (m_Bits.m_Mantissa05!=0)  ||
              (m_Bits.m_Mantissa06!=0)  ||
              (m_Bits.m_Mantissa07!=0)  )
    {
        m_Bits.m_OneBit = 1;
    }
    m_Bits.m_Empty0    = 0;
    m_Bits.m_Empty1    = 0;
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::float_type  tagFloat96_Info::get_float( void ) const
{
    return (m_Float);
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat96_Info::set_float( const float_type & theFloat, bool fValidate /*= true*/ )
{
    m_Float = theFloat;
    if ( fValidate != false )
    {
        validate();
    }
    return;
}


/////////////////////////////////////////////////////////////////////////////

void  tagFloat96_Info::set_nan( bool fPositive /*= true*/ )
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

void  tagFloat96_Info::set_infinity( bool fPositive /*= true*/ )
{
    clear();
    m_WideBits.m_Exponent   = 0x07FFF;
    m_WideBits.m_Mantissa   = 0;
    set_sign( fPositive );
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat96_Info::set_zero( bool fPositive /*= true*/ )
{
    clear();
    set_sign( fPositive );
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::byte_type  tagFloat96_Info::get_byte( size_t nIndex ) const
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
    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::byte_type  tagFloat96_Info::get_byte_mantissa( size_t nIndex ) const
{
    byte_type resultVal = 0;
         if ( nIndex ==  0 )    {   resultVal = m_Bits.m_Mantissa00;    }
    else if ( nIndex ==  1 )    {   resultVal = m_Bits.m_Mantissa01;    }
    else if ( nIndex ==  2 )    {   resultVal = m_Bits.m_Mantissa02;    }
    else if ( nIndex ==  3 )    {   resultVal = m_Bits.m_Mantissa03;    }
    else if ( nIndex ==  4 )    {   resultVal = m_Bits.m_Mantissa04;    }
    else if ( nIndex ==  5 )    {   resultVal = m_Bits.m_Mantissa05;    }
    else if ( nIndex ==  6 )    {   resultVal = m_Bits.m_Mantissa06;    }
    else if ( nIndex ==  7 )    {   resultVal = m_Bits.m_Mantissa07;    }
    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::byte_type  tagFloat96_Info::get_byte_exponent( size_t nIndex ) const
{
    byte_type resultVal = 0;
    if ( nIndex == 0 )
    {
        resultVal   = m_Bits.m_Exponent0;
    }
    else if ( nIndex == 1 )
    {
        resultVal   = m_Bits.m_Exponent1;
    }

    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat96_Info::get_bit( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat96_Info::get_bit_mantissa( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte_mantissa( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat96_Info::get_bit_exponent( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte_exponent( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}


/////////////////////////////////////////////////////////////////////////////

FloatClass  tagFloat96_Info::get_float_class( void ) const
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

bool  tagFloat96_Info::set_byte( size_t nIndex, const byte_type & theByte )
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
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat96_Info::set_byte_mantissa( size_t nIndex, const byte_type & theByte )
{
         if ( nIndex ==  0 )    {   m_Bits.m_Mantissa00 = theByte;  return (true); }
    else if ( nIndex ==  1 )    {   m_Bits.m_Mantissa01 = theByte;  return (true); }
    else if ( nIndex ==  2 )    {   m_Bits.m_Mantissa02 = theByte;  return (true); }
    else if ( nIndex ==  3 )    {   m_Bits.m_Mantissa03 = theByte;  return (true); }
    else if ( nIndex ==  4 )    {   m_Bits.m_Mantissa04 = theByte;  return (true); }
    else if ( nIndex ==  5 )    {   m_Bits.m_Mantissa05 = theByte;  return (true); }
    else if ( nIndex ==  6 )    {   m_Bits.m_Mantissa06 = theByte;  return (true); }
    else if ( nIndex ==  7 )    {   m_Bits.m_Mantissa07 = theByte;  return (true); }
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat96_Info::set_byte_exponent( size_t nIndex, const byte_type & theByte )
{
    if ( nIndex == 0 )          {   m_Bits.m_Exponent0 = theByte;  return (true); }
    else if ( nIndex == 1 )     {   m_Bits.m_Exponent1 = theByte;  return (true); }
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat96_Info::set_sign( bool fPositive )
{
    m_Bits.m_Sign = ( (fPositive==false) ? 1 : 0 );
    return (true);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat96_Info::float_type  tagFloat96_Info::get_ieee_float( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (m_IEEE.d);
    #else
        return (Float96_CONSTANT(0));
    #endif
}

/////////////////////////////////////////////////////////////////////////////

unsigned int  tagFloat96_Info::get_ieee_mantissa( size_t nIndex ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        if ( nIndex == 0 )
        {
            unsigned int nResult    = m_IEEE.ieee.mantissa0;
            unsigned int oneBitMask = 0x7FFFFFFF;
            nResult &= oneBitMask;
            return (nResult);
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

unsigned int  tagFloat96_Info::get_ieee_exponent( size_t nIndex ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        if ( nIndex == 0 )  {   return (m_IEEE.ieee.exponent);   }
        return (0);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

unsigned int  tagFloat96_Info::get_ieee_sign( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (m_IEEE.ieee.negative);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

size_t  tagFloat96_Info::get_ieee_mantissa_count( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (2);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

size_t  tagFloat96_Info::get_ieee_exponent_count( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (1);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

#endif // defined(CEXTEND_PLATFORM_TYPE_LINUX_I32)

}; // namespace CExBase



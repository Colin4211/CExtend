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
//      CExtend\Libraries\CExBase\CExBase_Float64.cpp
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

#if  defined(CEXTEND_PLATFORM_FAMILY_LINUX) || defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::tagFloat64_Info( void )
{
    clear();
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::tagFloat64_Info( const float_type & theFloat )
{
    m_Float = theFloat;
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::tagFloat64_Info( const char & initChar )
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

tagFloat64_Info::tagFloat64_Info( const byte_type & byte0, const byte_type & byte1, const byte_type & byte2, const byte_type & byte3,
                                    const byte_type & byte4, const byte_type & byte5, const byte_type & byte6, const byte_type & byte7 )
{
    m_Bytes.m_Byte0 = byte0;
    m_Bytes.m_Byte1 = byte1;
    m_Bytes.m_Byte2 = byte2;
    m_Bytes.m_Byte3 = byte3;
    m_Bytes.m_Byte4 = byte4;
    m_Bytes.m_Byte5 = byte5;
    m_Bytes.m_Byte6 = byte6;
    m_Bytes.m_Byte7 = byte7;
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::operator Float64( void ) const
{
    return (m_Float);
}

/////////////////////////////////////////////////////////////////////////////

const  tagFloat64_Info::float_type &  tagFloat64_Info::operator = ( const float_type & rhSide )
{
    m_Float = rhSide;
    validate();
    return (m_Float);
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat64_Info::clear( void )
{
    m_Uint = 0;
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

const char *  tagFloat64_Info::float_type_name( void ) const
{
    return ("Float64");
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat64_Info::validate( void )
{
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::float_type  tagFloat64_Info::get_float( void ) const
{
    return (m_Float);
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat64_Info::set_float( const float_type & theFloat, bool fValidate /*= true*/ )
{
    m_Float = theFloat;
    if ( fValidate != false )
    {
        validate();
    }
    return;
}


/////////////////////////////////////////////////////////////////////////////

void  tagFloat64_Info::set_nan( bool fPositive /*= true*/ )
{
    clear();
    m_WideBits.m_Exponent   = 0x07FF;
    m_WideBits.m_Mantissa   = 1;
    m_WideBits.m_Mantissa   <<= (bitsize_manitissa-1);
    set_sign( fPositive );
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat64_Info::set_infinity( bool fPositive /*= true*/ )
{
    clear();
    m_WideBits.m_Exponent   = 0x07FF;
    m_WideBits.m_Mantissa   = 0;
    set_sign( fPositive );
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

void  tagFloat64_Info::set_zero( bool fPositive /*= true*/ )
{
    clear();
    set_sign( fPositive );
    validate();
    return;
}

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::byte_type  tagFloat64_Info::get_byte( size_t nIndex ) const
{
    byte_type resultVal = 0;
    if ( nIndex == 0)       {   resultVal = m_Bytes.m_Byte0;    }
    else if ( nIndex == 1)  {   resultVal = m_Bytes.m_Byte1;    }
    else if ( nIndex == 2)  {   resultVal = m_Bytes.m_Byte2;    }
    else if ( nIndex == 3)  {   resultVal = m_Bytes.m_Byte3;    }
    else if ( nIndex == 4)  {   resultVal = m_Bytes.m_Byte4;    }
    else if ( nIndex == 5)  {   resultVal = m_Bytes.m_Byte5;    }
    else if ( nIndex == 6)  {   resultVal = m_Bytes.m_Byte6;    }
    else if ( nIndex == 7)  {   resultVal = m_Bytes.m_Byte7;    }
    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::byte_type  tagFloat64_Info::get_byte_mantissa( size_t nIndex ) const
{
    byte_type resultVal = 0;
    if ( nIndex == 0 )      {   resultVal = m_Bits.m_Mantissa0;    }
    else if ( nIndex == 1 ) {   resultVal = m_Bits.m_Mantissa1;    }
    else if ( nIndex == 2 ) {   resultVal = m_Bits.m_Mantissa2;    }
    else if ( nIndex == 3 ) {   resultVal = m_Bits.m_Mantissa3;    }
    else if ( nIndex == 4 ) {   resultVal = m_Bits.m_Mantissa4;    }
    else if ( nIndex == 5 ) {   resultVal = m_Bits.m_Mantissa5;    }
    else if ( nIndex == 6 ) {   resultVal = m_Bits.m_Mantissa6;    }
    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::byte_type  tagFloat64_Info::get_byte_exponent( size_t nIndex ) const
{
    byte_type resultVal = 0;
    if ( nIndex == 0 )
    {
        resultVal   =   m_Bits.m_Exponent1;
        resultVal   <<= 4;
        resultVal   |=  m_Bits.m_Exponent0;
    }
    else if ( nIndex == 1 )
    {
        resultVal   =   m_Bits.m_Exponent2;
    }

    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat64_Info::get_bit( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat64_Info::get_bit_mantissa( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte_mantissa( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat64_Info::get_bit_exponent( size_t nBitIndex ) const
{
    size_t      nByteIndex      = nBitIndex / 8;
    size_t      nByteBitIndex   = nBitIndex % 8;
    byte_type   theByte         = get_byte_exponent( nByteIndex );
    byte_type   bitMask         = ((byte_type)1) << nByteBitIndex;
    return ( ((theByte&bitMask) == 0) ? false : true );
}

/////////////////////////////////////////////////////////////////////////////

FloatClass  tagFloat64_Info::get_float_class( void ) const
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

bool  tagFloat64_Info::set_byte( size_t nIndex, const byte_type & theByte )
{
    if ( nIndex == 0)       {   m_Bytes.m_Byte0 = theByte;    return (true);  }
    else if ( nIndex == 1)  {   m_Bytes.m_Byte1 = theByte;    return (true);  }
    else if ( nIndex == 2)  {   m_Bytes.m_Byte2 = theByte;    return (true);  }
    else if ( nIndex == 3)  {   m_Bytes.m_Byte3 = theByte;    return (true);  }
    else if ( nIndex == 4)  {   m_Bytes.m_Byte4 = theByte;    return (true);  }
    else if ( nIndex == 5)  {   m_Bytes.m_Byte5 = theByte;    return (true);  }
    else if ( nIndex == 6)  {   m_Bytes.m_Byte6 = theByte;    return (true);  }
    else if ( nIndex == 7)  {   m_Bytes.m_Byte7 = theByte;    return (true);  }
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat64_Info::set_byte_mantissa( size_t nIndex, const byte_type & theByte )
{
    if ( nIndex == 0 )          {   m_Bits.m_Mantissa0 = theByte;  return (true); }
    else if ( nIndex == 1 )     {   m_Bits.m_Mantissa1 = theByte;  return (true); }
    else if ( nIndex == 2 )     {   m_Bits.m_Mantissa2 = theByte;  return (true); }
    else if ( nIndex == 3 )     {   m_Bits.m_Mantissa3 = theByte;  return (true); }
    else if ( nIndex == 4 )     {   m_Bits.m_Mantissa4 = theByte;  return (true); }
    else if ( nIndex == 5 )     {   m_Bits.m_Mantissa5 = theByte;  return (true); }
    else if ( nIndex == 6 )     {   m_Bits.m_Mantissa6 = theByte;  return (true); }
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat64_Info::set_byte_exponent( size_t nIndex, const byte_type & theByte )
{
    if ( nIndex == 0 )
    {
        m_Bits.m_Exponent0     = theByte & 0x0F;
        m_Bits.m_Exponent1     = ( (theByte&0xF0) >> 4 );
        return (true);
    }
    else if ( nIndex == 1 )
    {
        m_Bits.m_Exponent2     = theByte;
        return (true);
    }
    return (false);
}

/////////////////////////////////////////////////////////////////////////////

bool  tagFloat64_Info::set_sign( bool fPositive )
{
    m_Bits.m_Sign = ( (fPositive==false) ? 1 : 0 );
    return (true);
}

/////////////////////////////////////////////////////////////////////////////

tagFloat64_Info::float_type  tagFloat64_Info::get_ieee_float( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (m_IEEE.d);
    #else
        return (Float64_CONSTANT(0));
    #endif
}

/////////////////////////////////////////////////////////////////////////////

unsigned int  tagFloat64_Info::get_ieee_mantissa( size_t nIndex ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        if ( nIndex == 0 )  {   return (m_IEEE.ieee.mantissa0);   }
        if ( nIndex == 1 )  {   return (m_IEEE.ieee.mantissa1);   }
        return (0);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

unsigned int  tagFloat64_Info::get_ieee_exponent( size_t nIndex ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        if ( nIndex == 0 )  {   return (m_IEEE.ieee.exponent);   }
        return (0);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

unsigned int  tagFloat64_Info::get_ieee_sign( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (m_IEEE.ieee.negative);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

size_t  tagFloat64_Info::get_ieee_mantissa_count( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (2);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

size_t  tagFloat64_Info::get_ieee_exponent_count( void ) const
{
    #if defined(CEXBASE_FLOATS_HAS_IEEE)
        return (1);
    #else
        return (0);
    #endif
}

/////////////////////////////////////////////////////////////////////////////

#endif // defined(CEXTEND_PLATFORM_FAMILY_LINUX) || defined(CEXTEND_PLATFORM_FAMILY_MSWIN)

}; // namespace CExBase



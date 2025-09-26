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
//      PlatformInfo
//
//  File:
//      CExtend\Applications\PlatformInfo\FloatEx.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Apps
//      <DT_SUB_TOPIC> PlatformInfo
//
/////////////////////////////////////////////////////////////////////////////

#include "IntEx.h"

#ifndef _FloatEx_h_
#define _FloatEx_h_

/////////////////////////////////////////////////////////////////////////////

std::string  FloatEx_FloatAsString( const float & theFloat, bool fFloat = false );
std::string  FloatEx_FloatAsString( const double & theFloat, bool fFloat = false );
std::string  FloatEx_FloatAsString( const long double & theFloat, bool fFloat = false );

/////////////////////////////////////////////////////////////////////////////

template < typename T_FLOAT >
    void    FloatEx_PrintInfo( const T_FLOAT & theFloat )
{
    (void)(theFloat);
    typename CExBase::Float_Types<T_FLOAT>::float_info_type floatInfo = theFloat;

    printf( "%s -- sizeof -      float_type - %s\n",  floatInfo.float_type_name(), IntEx_IntToString(sizeof(typename CExBase::Float_Types<T_FLOAT>::float_type)).c_str() );
    printf( "%s -- sizeof - float_info_type - %s\n",  floatInfo.float_type_name(), IntEx_IntToString(sizeof(typename CExBase::Float_Types<T_FLOAT>::float_info_type)).c_str() );
    //#if defined(CEXTEND_DEBUG)
    //    printf( "%s -- sizeof -         T_FLOAT - %s\n",  floatInfo.float_type_name(), IntEx_IntToString(sizeof(T_FLOAT)).c_str() );
    //    printf( "%s -- sizeof -             all - %s\n",  floatInfo.float_type_name(), IntEx_IntToString(sizeof(floatInfo)).c_str() );
    //    printf( "%s -- sizeof -          m_Bits - %s\n",  floatInfo.float_type_name(), IntEx_IntToString(sizeof(floatInfo.m_Bits)).c_str() );
    //    printf( "%s -- sizeof -      m_WideBits - %s\n",  floatInfo.float_type_name(), IntEx_IntToString(sizeof(floatInfo.m_WideBits)).c_str() );
    //#endif // defined(CEXTEND_DEBUG)

    printf( "%s --  Storage = bytes=%-3s bits=%-3s\n",
                floatInfo.float_type_name(),
                IntEx_IntToString(floatInfo.get_bytesize()).c_str(),
                IntEx_IntToString(floatInfo.get_bytesize()*8).c_str() );
    if ( sizeof(floatInfo) != floatInfo.get_bytesize() )
    {
        printf( "%s -- ERROR: info sizeof (%s) does not match bytesize(%s)\n",
                floatInfo.float_type_name(),
                IntEx_IntToString(sizeof(floatInfo)).c_str(),
                IntEx_IntToString(floatInfo.get_bytesize()).c_str() );
    }
    if ( sizeof(T_FLOAT) != floatInfo.get_bytesize() )
    {
        printf( "%s -- ERROR: float sizeof (%s) does not match bytesize(%s)\n",
                floatInfo.float_type_name(),
                IntEx_IntToString(sizeof(T_FLOAT)).c_str(),
                IntEx_IntToString(floatInfo.get_bytesize()).c_str() );
    }

    printf( "%s --     Bits = mantissa=%1s exponent=%2s sign=%s extra=%s total=%s empty=%s\n",
                floatInfo.float_type_name(),
                IntEx_IntToString(floatInfo.get_bitsize_mantissa()).c_str(),
                IntEx_IntToString(floatInfo.get_bitsize_exponent()).c_str(),
                IntEx_IntToString(floatInfo.get_bitsize_sign()).c_str(),
                IntEx_IntToString(floatInfo.get_bitsize_extra()).c_str(),
                IntEx_IntToString(floatInfo.get_bitsize_total()).c_str(),
                IntEx_IntToString(floatInfo.get_bitsize_empty()).c_str() );
    printf( "%s --   Limits =    min=%-20s    max=%-20s\n",
                floatInfo.float_type_name(),
                FloatEx_FloatAsString(floatInfo.get_limits_min()).c_str(),
                FloatEx_FloatAsString(floatInfo.get_limits_max()).c_str() );
    printf( "%s -- Exponent =    min=%-7s  min10=%-7s  max=%-7s  max10=%-7s\n",
                floatInfo.float_type_name(),
                IntEx_IntToString(floatInfo.get_limits_min_exp()).c_str(),
                IntEx_IntToString(floatInfo.get_limits_min_10_exp()).c_str(),
                IntEx_IntToString(floatInfo.get_limits_max_exp()).c_str(),
                IntEx_IntToString(floatInfo.get_limits_max_10_exp()).c_str() );

    printf( "%s -- Mantissa = digits=%-5s digits10=%-5s\n",
                floatInfo.float_type_name(),
                IntEx_IntToString(floatInfo.get_limits_mantissa_digits()).c_str(),
                IntEx_IntToString(floatInfo.get_limits_digits()).c_str() );
    return;
}

/////////////////////////////////////////////////////////////////////////////

template < typename T_FLOAT_INFO >
    void    FloatEx_PrintFloatValue( const std::string & tagStr, const T_FLOAT_INFO & floatInfo )
{
    std::string typeStr = floatInfo.float_type_name();
    printf( "%s --- %s ----------------------------------------\n", typeStr.c_str(), tagStr.c_str() );
    printf( "%s -- Float -- Value = %s - %s\n", typeStr.c_str(), FloatEx_FloatAsString(floatInfo.get_float()).c_str(), floatInfo.get_float_class().c_str() );
    if ( floatInfo.get_ieee_mantissa_count() > 0 )
    {
        printf( "%s -- Float -- IEEE = %s\n", typeStr.c_str(), FloatEx_FloatAsString(floatInfo.get_ieee_float()).c_str()  );
    }

    //////////

    printf( "%s -- Uint = size = %s\n", typeStr.c_str(), IntEx_IntToString(floatInfo.get_bytesize()).c_str()  );
    std::string             uintStr     = "";
    unsigned long long      uintValue   = 0;
    for ( int nIndex = static_cast<int>(floatInfo.get_bytesize())-1; nIndex >= 0; nIndex-- )
    {
        Uint8 theByte = floatInfo.get_byte(nIndex);
        uintStr += " " + IntEx_IntToHexString( theByte , false );
        uintValue <<= 8;
        uintValue |= theByte;
    }
    printf( "%s -- Uint =  str = $$%s\n", typeStr.c_str(), uintStr.c_str()  );
    printf( "%s -- Uint = uint = %s = %s\n", typeStr.c_str(), IntEx_IntToHexString(uintValue).c_str(), IntEx_IntToString(uintValue).c_str()  );

    //////////

    if ( floatInfo.get_ieee_mantissa_count() > 0 )
    {
        printf( "%s -- Sign =  IEEE = %s\n", typeStr.c_str(), IntEx_IntToHexString(floatInfo.get_ieee_sign()).c_str()  );
    }
    printf( "%s -- Sign = isneg = %s\n", typeStr.c_str(), ( (floatInfo.is_negative()==false) ? "POS" : "NEG" ) );

    //////////

    if ( floatInfo.get_ieee_mantissa_count() > 0 )
    {
        std::string strIEEEMantissa = "";
        for ( size_t nIndex = 0; nIndex < floatInfo.get_ieee_mantissa_count(); nIndex++ )
        {
            unsigned int theVal = floatInfo.get_ieee_mantissa(nIndex);
            strIEEEMantissa += IntEx_IntToHexString(theVal);
            strIEEEMantissa += " - ";
        }
        printf( "%s -- Mantissa = IEEE = %s\n", typeStr.c_str(), strIEEEMantissa.c_str() );
    }
    printf( "%s -- Mantissa = size = %s\n", typeStr.c_str(), IntEx_IntToString(floatInfo.get_bytesize_mantissa()).c_str()  );
    std::string             strMantissa     = "";
    unsigned long long      uintMantissa    = 0;
    for ( int nIndex = static_cast<int>(floatInfo.get_bytesize_mantissa())-1; nIndex >= 0; nIndex-- )
    {
        Uint8 theByte = floatInfo.get_byte_mantissa(nIndex);
        strMantissa += " " + IntEx_IntToHexString( theByte , false );
        uintMantissa <<= 8;
        uintMantissa |= theByte;
    }
    printf( "%s -- Mantissa =  str = $$%s\n", typeStr.c_str(), strMantissa.c_str()  );
    printf( "%s -- Mantissa = uint = %s = %s\n", typeStr.c_str(), IntEx_IntToHexString(uintMantissa).c_str(), IntEx_IntToString(uintMantissa).c_str()  );

    //////////

    if ( floatInfo.get_ieee_mantissa_count() > 0 )
    {
        std::string strIEEEExponent;
        for ( size_t nIndex = 0; nIndex < floatInfo.get_ieee_exponent_count(); nIndex++ )
        {
            unsigned int theVal = floatInfo.get_ieee_exponent(nIndex);
            strIEEEExponent += IntEx_IntToHexString(theVal);
            strIEEEExponent += " ";
        }
        printf( "%s -- Exponent = IEEE = %s\n", typeStr.c_str(), strIEEEExponent.c_str()  );
    }
    printf( "%s -- Exponent = size = %s\n", typeStr.c_str(), IntEx_IntToString(floatInfo.get_bytesize_exponent()).c_str()  );
    std::string         strExponent     = "";
    unsigned long long  uintExponent    = 0;
    for ( int nIndex = static_cast<int>(floatInfo.get_bytesize_mantissa())-1; nIndex >= 0; nIndex-- )
    {
        Uint8 theByte = floatInfo.get_byte_exponent(nIndex);
        //printf( "get_byte_exponent(%s) = %s\n", IntEx_IntToString(nByte).c_str(), IntEx_IntToHexString(theByte).c_str() );
        strExponent += " " + IntEx_IntToHexString( theByte , false );
        uintExponent <<= 8;
        uintExponent |= theByte;
    }
    printf( "%s -- Exponent =  str = $$%s\n", typeStr.c_str(), strExponent.c_str()  );
    printf( "%s -- Exponent = uint = %s = %s\n", typeStr.c_str(), IntEx_IntToHexString(uintExponent).c_str(), IntEx_IntToString(uintExponent).c_str()  );

    //////////

    return;
}

/////////////////////////////////////////////////////////////////////////////

#endif // _FloatEx_h_



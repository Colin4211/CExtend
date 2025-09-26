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
//      CExtend\Applications\PlatformInfo\IntEx.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Apps
//      <DT_SUB_TOPIC> PlatformInfo
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _IntEx_h_
#define _IntEx_h_

/////////////////////////////////////////////////////////////////////////////

template < typename T_INT >
    std::string     IntEx_IntToString( T_INT theInt )
{
    std::string     resultStr;

    T_INT  workValue   = theInt;
    T_INT  divValue    = 10;
    do
    {
        T_INT  lastDigit = workValue % divValue;
        if ( lastDigit < 1 )
        {
            lastDigit = 0 - lastDigit;
        }
        char    theChar = (char)lastDigit + '0';
        resultStr = theChar + resultStr;
        workValue = workValue / divValue;
    } while ( workValue != 0 );

    if ( (theInt<= 0)    &&
         (theInt!=0)     )
    {
        resultStr = "-" + resultStr;
    }

    return (resultStr);
}

/////////////////////////////////////////////////////////////////////////////

template < typename T_INT >
    std::string     IntEx_IntToHexString( T_INT theInt , bool fPretty = true )
{
    std::string     resultStr;

    size_t  numDigits = ((sizeof(T_INT)*8)/4);


    T_INT  workValue   = theInt;
    T_INT  divValue    = 16;
    for ( size_t nDigit = 0; nDigit < numDigits; nDigit++ )
    //do
    {
        if ( (fPretty!=false) && ((nDigit%2) == 0) )
        {
            resultStr = " " + resultStr;
        }
        T_INT  lastDigit = workValue % divValue;
        if ( lastDigit < 1 )
        {
            lastDigit = 0 - lastDigit;
        }
        char    theChar = (char)lastDigit + '0';
        if ( lastDigit >= 10 )
        {
            T_INT shiftDigit = lastDigit - 10;
            theChar = (char)shiftDigit + 'A';
        }
        resultStr = theChar + resultStr;
        workValue = workValue / divValue;
    } // while ( workValue != 0 );

    if ( fPretty != false )
    {
        resultStr = "$$ " + resultStr;
    }

    return (resultStr);
}

/////////////////////////////////////////////////////////////////////////////

template < typename T_INT >
    void    IntEx_PrintInfo( const std::string &  typeStr,
                             T_INT               /*theInt*/ )
{
    bool    fSigned     = false;
    T_INT  testValue   = 0;
    T_INT  numberOne   = 1;
    testValue = testValue - numberOne;
    fSigned = (testValue < 1);

    int byteSize    = (int)(sizeof(T_INT));
    int bitSize     = (int)(byteSize*8);

    T_INT  minValue = 0;
    if ( fSigned != false )
    {
        minValue = 1;
        for ( int nCount = 1; nCount < bitSize; nCount++ )
        {
            minValue <<= 1;
            //printf( "minValue [%d] = %s\n", nCount, IntEx_IntToString(minValue).c_str() );
        }
    }

    T_INT  maxValue = 0;
    for ( int nCount = 1; nCount < bitSize; nCount++ )
    {
        maxValue <<= 1;
        maxValue |= 1;
        // printf( "maxValue [%d] = %s\n", nCount, IntEx_IntToString(maxValue).c_str() );
    }

    std::string     maxStr = IntEx_IntToString( maxValue );
    std::string     minStr = IntEx_IntToString( minValue );

    std::string typeString;
    typeString = "                                                                      " + typeStr;
    typeString = typeString.substr( typeString.length()-32 );

    printf( "%s <%2d-%2d>  min=%-20s  max=%-20s -- %s\n",
            ( (fSigned==false) ? "+ " : "+-" ),
            bitSize,
            byteSize,
            minStr.c_str(),
            maxStr.c_str(),
            typeStr.c_str() );

    return;
}


/////////////////////////////////////////////////////////////////////////////

#endif // _IntEx_h_



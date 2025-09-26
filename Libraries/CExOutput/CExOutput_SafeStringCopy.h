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
//      CExOutput
//
//  File:
//      CExtend\Libraries\CExOutput\CExOutput_SafeStringCopy.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_SafeStringCopy_h
#define _CExOutput_SafeStringCopy_h

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
template < typename CHARTYPE_B >
    bool    SafeStringCopy( std::string &       destStr,
                            const CHARTYPE_B *  pszSource,
                            size_t              maxLen )
{
    destStr.clear();
    if ( maxLen < 1 )
    {
        return (false);
    }
    bool fResult = false;
    try
    {
        if ( pszSource != NULL )
        {
            size_t  walkEnd = maxLen - 1;
            for ( size_t destIndex = 0; destIndex < walkEnd; destIndex++ )
            {
                char theChar = static_cast< char >( pszSource[destIndex] );
                if ( theChar == 0 )
                {
                    break;
                }
                destStr += theChar;
            }
        }
        fResult = true;
    }
    catch ( ... )
    {
        destStr.clear();
        fResult = false;
    }
    return (fResult);
}
//.

/////////////////////////////////////////////////////////////////////////////
template < typename CHARTYPE_A, typename CHARTYPE_B >
    bool    SafeStringCopy( CHARTYPE_A *        pszDest,
                            const CHARTYPE_B *  pszSource,
                            size_t              maxLen )
{
    if ( (pszDest == NULL)  ||
         (maxLen < 1)       )
    {
        return (false);
    }
    bool fResult = false;
    try
    {
        if ( pszSource == NULL )
        {
            for ( size_t destIndex = 0; destIndex < maxLen; destIndex++ )
            {
                pszDest[destIndex] = 0;
            }
        }
        else
        {
            size_t  walkEnd         = maxLen - 1;
            bool    fEndOfString    = false;
            for ( size_t destIndex = 0; destIndex < walkEnd; destIndex++ )
            {
                CHARTYPE_A theChar  = 0;
                if ( fEndOfString == false )
                {
                    theChar = static_cast< CHARTYPE_A >( pszSource[destIndex] );
                }
                if ( theChar == 0 )
                {
                    fEndOfString = true;
                }
                pszDest[destIndex]  = theChar;
            }
            pszDest[walkEnd]    = 0;
        }
        fResult = true;
    }
    catch ( ... )
    {
        fResult = false;
    }
    try
    {
        if ( fResult == false )
        {
            pszDest[0] = 0;
        }
    }
    catch ( ... )
    {
        fResult = false;
    }
    return (fResult);
}
//.



/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput

#endif // _CExOutput_SafeStringCopy_h

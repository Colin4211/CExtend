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
//      CExtend\Libraries\CExBase\CExBase_FloatClass.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//      <DT_SUB_TOPIC> FloatClass
//
/////////////////////////////////////////////////////////////////////////////

#include "CExBase.h"

namespace CExBase
{

/////////////////////////////////////////////////////////////////////////////

const FloatClass::ElemStruct  FloatClass::m_Elements[ FloatClass::ElemCount ] =
    {
        {   FloatClass::Value_ERROR         ,   "FloatClass[ERROR]"         ,   ""              ,   false   },
        {   FloatClass::Value_ZERO          ,   "FloatClass[ZERO]"          ,   "ZERO"          ,   true    },
        {   FloatClass::Value_NORMAL        ,   "FloatClass[NORMAL]"        ,   "NORMAL"        ,   true    },
        {   FloatClass::Value_SUBNORMAL     ,   "FloatClass[SUBNORMAL]"     ,   "SUBNORMAL"     ,   true    },
        {   FloatClass::Value_INFINITY      ,   "FloatClass[INFINITY]"      ,   "INFINITY"      ,   false   },
        {   FloatClass::Value_NAN           ,   "FloatClass[NAN]"           ,   "NAN"           ,   false   }
    };
const size_t  FloatClass::m_EmptyIndex = 0;

const FloatClass     FloatClass_ERROR          ( FloatClass::Value_ERROR        );
const FloatClass     FloatClass_ZERO           ( FloatClass::Value_ZERO         );
const FloatClass     FloatClass_NORMAL         ( FloatClass::Value_NORMAL       );
const FloatClass     FloatClass_SUBNORMAL      ( FloatClass::Value_SUBNORMAL    );
const FloatClass     FloatClass_INFINITY       ( FloatClass::Value_INFINITY     );
const FloatClass     FloatClass_NAN            ( FloatClass::Value_NAN          );


/////////////////////////////////////////////////////////////////////////////

FloatClass::FloatClass( void )
    : m_Index( m_EmptyIndex )
{
    return;
}

/////////////////////////////////////////////////////////////////////////////

FloatClass::FloatClass( const FloatClass & rhSide )
    : m_Index( rhSide.m_Index )
{
    return;
}

/////////////////////////////////////////////////////////////////////////////

FloatClass::FloatClass( const char * pszString )
    : m_Index( m_EmptyIndex )
{
    initialize( pszString );
    return;
}

/////////////////////////////////////////////////////////////////////////////

FloatClass::FloatClass( value_type theValue )
    : m_Index( m_EmptyIndex )
{
    initialize( theValue );
    return;
}

/////////////////////////////////////////////////////////////////////////////

FloatClass::~FloatClass( void )
{
    clear();
    return;
}

/////////////////////////////////////////////////////////////////////////////

const FloatClass &  FloatClass::operator = ( const FloatClass & rhSide )
{
    if ( this != &rhSide )
    {
        m_Index = rhSide.m_Index;
    }
    return (*this);
}

/////////////////////////////////////////////////////////////////////////////

void  FloatClass::clear( void )
{
    m_Index = m_EmptyIndex;
    return;
}

/////////////////////////////////////////////////////////////////////////////

bool  FloatClass::empty( void ) const
{
    return (m_Index == m_EmptyIndex);
}

/////////////////////////////////////////////////////////////////////////////

int  FloatClass::compare( const FloatClass & rhSide ) const
{
    if ( m_Index < rhSide.m_Index )
    {
        return (-1);
    }
    else if ( m_Index > rhSide.m_Index )
    {
        return (1);
    }
    return (0);
}

/////////////////////////////////////////////////////////////////////////////

void  FloatClass::swap( FloatClass & rhSide )
{
    std::swap( m_Index, rhSide.m_Index );
    return;
}

/////////////////////////////////////////////////////////////////////////////

bool  FloatClass::initialize( const char * pszString )
{

#if defined(CEXTEND_PLATFORM_FAMILY_MSWIN)
    #define STR_CASE_CMP(STR1,STR2) (_stricmp(STR1,STR2))
#elif defined(CEXTEND_PLATFORM_FAMILY_LINUX)
    #define STR_CASE_CMP(STR1,STR2) (strcasecmp(STR1,STR2))
#else
    #error "ERROR: This code is platform specific"
#endif


    clear();
    bool fResult = false;
    try
    {
        if ( pszString != NULL )
        {
            if ( pszString[0] != 0 )
            {
                for ( size_t nIndex = 0; ( (fResult==false) && (nIndex < ElemCount) ); nIndex++ )
                {
                    if ( STR_CASE_CMP( pszString, m_Elements[nIndex].m_pszString ) == 0 )
                    {
                        fResult = true;
                        m_Index = nIndex;
                        break;
                    }
                    else if ( STR_CASE_CMP( pszString, m_Elements[nIndex].m_pszPrettyString ) == 0 )
                    {
                        fResult = true;
                        m_Index = nIndex;
                        break;
                    }
                }
            }
        }
    }
    catch ( ... )
    {
        fResult = false;
    }
    if ( fResult == false )
    {
        clear();
        return (false);
    }
#undef STR_CASE_CMP
    return (true);
}

/////////////////////////////////////////////////////////////////////////////

bool  FloatClass::initialize( value_type theValue )
{
    clear();
    bool fResult = false;
    for ( size_t nIndex = 0; nIndex < ElemCount; nIndex++ )
    {
        if ( theValue == m_Elements[nIndex].m_Value )
        {
            fResult = true;
            m_Index = nIndex;
            break;
        }
    }
    if ( fResult == false )
    {
        clear();
        return (false);
    }
    return (true);
}

/////////////////////////////////////////////////////////////////////////////

const char *  FloatClass::c_str( void ) const
{
    return (m_Elements[m_Index].m_pszString);
}

/////////////////////////////////////////////////////////////////////////////

std::string  FloatClass::as_string( void ) const
{
    return (std::string(m_Elements[m_Index].m_pszString));
}

/////////////////////////////////////////////////////////////////////////////

const char *  FloatClass::pretty_c_str( void ) const
{
    return (m_Elements[m_Index].m_pszPrettyString);
}

/////////////////////////////////////////////////////////////////////////////

std::string  FloatClass::as_pretty_string( void ) const
{
    return (std::string(m_Elements[m_Index].m_pszPrettyString));
}

/////////////////////////////////////////////////////////////////////////////

FloatClass::value_type  FloatClass::value( void ) const
{
    return (m_Elements[m_Index].m_Value);
}

/////////////////////////////////////////////////////////////////////////////

bool  FloatClass::is_finite( void ) const
{
    return (m_Elements[m_Index].m_fFinite);
}

/////////////////////////////////////////////////////////////////////////////

/* static */ size_t  FloatClass::enum_item_count( void )
{
    return (ElemCount);
}

/////////////////////////////////////////////////////////////////////////////

/* static */ FloatClass  FloatClass::enum_item_at( size_t nIndex )
{
    FloatClass resultVal;
    if ( (nIndex>=0) && (nIndex<ElemCount) )
    {
        resultVal.m_Index = nIndex;
    }
    return (resultVal);
}

/////////////////////////////////////////////////////////////////////////////

const FloatClass &  FloatClass::empty_instance( void )
{
    static  const FloatClass  emptyObject;
    return (emptyObject);
}

/////////////////////////////////////////////////////////////////////////////

}; // namespace CExBase



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
//      CExtend\Libraries\CExBase\CExBase_FloatClass.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExBase
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExBase_FloatClass_h
#define _CExBase_FloatClass_h

namespace CExBase
{

/////////////////////////////////////////////////////////////////////////////
//! FloatClass
//
//  :Declaration
//"
class FloatClass
{
    // Embedded Types
    public:
        typedef Uint8       value_type;
    private:
        typedef struct
        {
            value_type      m_Value;
            const char *    m_pszString;
            const char *    m_pszPrettyString;
            bool            m_fFinite;
        } ElemStruct;
        enum { ElemCount = 7 };

    // Data Members
    private:
        size_t     m_Index;

    // Static Data Members
    private:
        static const ElemStruct     m_Elements[ ElemCount ];
        static const size_t         m_EmptyIndex;

    public:
        static  const value_type    Value_ERROR     = 0;
        static  const value_type    Value_ZERO      = 'z';
        static  const value_type    Value_NORMAL    = 'f';
        static  const value_type    Value_SUBNORMAL = 's';
        static  const value_type    Value_INFINITY  = 'i';
        static  const value_type    Value_NAN       = 'n';

    // Construction
    public:
        FloatClass( void );
        FloatClass( const FloatClass & rhSide );
        explicit FloatClass( const char * pszString );
        explicit FloatClass( value_type theValue );
        ~FloatClass( void );
        const FloatClass &  operator = ( const FloatClass & rhSide );

    // Public Interface
    public:
        void    clear( void );
        bool    empty( void ) const;
        int     compare( const FloatClass & rhSide ) const;
        void    swap( FloatClass & rhSide );

        // Initialization
        bool    initialize( const char * pszString );
        bool    initialize( value_type theValue );

        // General Access
        const char *    c_str( void ) const;
        std::string     as_string( void ) const;

        const char *    pretty_c_str( void ) const;
        std::string     as_pretty_string( void ) const;

        value_type      value( void ) const;

        bool            is_finite( void ) const;

        // Enumeration
        static  size_t                          enum_item_count( void );
        static  FloatClass                      enum_item_at( size_t nIndex );
        static  const FloatClass &              empty_instance( void );

    // Protected Interface
    protected:
        bool    is_valid( void ) const;

};

inline bool operator == ( const FloatClass & lhSide, const FloatClass & rhSide )    {   return (lhSide.compare(rhSide) == 0);   };
inline bool operator != ( const FloatClass & lhSide, const FloatClass & rhSide )    {   return (lhSide.compare(rhSide) != 0);   };
inline bool operator <= ( const FloatClass & lhSide, const FloatClass & rhSide )    {   return (lhSide.compare(rhSide) <= 0);   };
inline bool operator <  ( const FloatClass & lhSide, const FloatClass & rhSide )    {   return (lhSide.compare(rhSide) <  0);   };
inline bool operator >= ( const FloatClass & lhSide, const FloatClass & rhSide )    {   return (lhSide.compare(rhSide) >= 0);   };
inline bool operator >  ( const FloatClass & lhSide, const FloatClass & rhSide )    {   return (lhSide.compare(rhSide) >  0);   };

// Constants
extern const FloatClass     FloatClass_ERROR        ;
extern const FloatClass     FloatClass_ZERO         ;
extern const FloatClass     FloatClass_NORMAL       ;
extern const FloatClass     FloatClass_SUBNORMAL    ;
extern const FloatClass     FloatClass_INFINITY     ;
extern const FloatClass     FloatClass_NAN          ;

//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExBase

#endif // CExBase_FloatClass



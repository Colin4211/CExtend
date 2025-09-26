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
//      CExtend\Libraries\CExOutput\CExOutput_TimeStamp.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_TimeStamp_h
#define _CExOutput_TimeStamp_h

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! TimeStamp
//
//  :Declaration
//"
class TimeStamp
{
    // Data Members
    private:
        OM_TimeStruct       m_TimeStruct;

    // Construction
    public:
        TimeStamp( void );
        TimeStamp( const TimeStamp & rhSide );
        explicit  TimeStamp( const OM_TimeStruct & omTimeStruct );
        ~TimeStamp( void );
        const TimeStamp &  operator = ( const TimeStamp & rhSide );

    // Public Interface
    public:
        void    clear( void );
        bool    empty( void ) const;
        int     compare( const TimeStamp & rhSide ) const;

        bool    initialize( const OM_TimeStruct & omTimeStruct );
        bool    initialize( void );

        const OM_TimeStruct &   om_time_struct( void ) const
            {
                return (m_TimeStruct);
            };
        Int16  get_year( void ) const
            {
                return (m_TimeStruct.m_Year);
            };
        Int8  get_month( void ) const
            {
                return (m_TimeStruct.m_Month);
            };
        Int8  get_day( void ) const
            {
                return (m_TimeStruct.m_Day);
            };
        Int8  get_hour( void ) const
            {
                return (m_TimeStruct.m_Hour);
            };
        Int8  get_minute( void ) const
            {
                return (m_TimeStruct.m_Minute);
            };
        Int8  get_second( void ) const
            {
                return (m_TimeStruct.m_Second);
            };
};
//.




/////////////////////////////////////////////////////////////////////////////
//  <DG_SUB_TOPIC> TimeStamp
//  Inline Implementation

/////////////////////////////////////////////////////////////////////////////
//! Comparison Operators
//
//  :Implementation
//"
inline bool  operator == ( const TimeStamp & lhSide, const TimeStamp & rhSide )
{
    return ( lhSide.compare(rhSide) == 0 );
}

inline bool  operator != ( const TimeStamp & lhSide, const TimeStamp & rhSide )
{
    return ( lhSide.compare(rhSide) != 0 );
}

inline bool  operator <= ( const TimeStamp & lhSide, const TimeStamp & rhSide )
{
    return ( lhSide.compare(rhSide) <= 0 );
}

inline bool  operator < ( const TimeStamp & lhSide, const TimeStamp & rhSide )
{
    return ( lhSide.compare(rhSide) < 0 );
}

inline bool  operator >= ( const TimeStamp & lhSide, const TimeStamp & rhSide )
{
    return ( lhSide.compare(rhSide) >= 0 );
}

inline bool  operator > ( const TimeStamp & lhSide, const TimeStamp & rhSide )
{
    return ( lhSide.compare(rhSide) > 0 );
}
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput

#endif // _CExOutput_TimeStamp_h



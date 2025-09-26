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
//      CExtend\Libraries\CExOutput\CExOutput_OutputEvent.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_OutputEvent_h
#define _CExOutput_OutputEvent_h

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! OutputEvent
//
//  :Implementation
//"
class OutputEvent
{
    // Data Members
    private:
        OM_OutputEvent      m_Structure;

    // Construction
    public:
        OutputEvent( void );
        OutputEvent( const OutputEvent & rhSide );
        explicit  OutputEvent( const OM_OutputEvent & omOutputEvent );
        ~OutputEvent( void );
        const OutputEvent & operator = ( const OutputEvent & rhSide );

    // Public Interface
    public:
        void    clear( void );
        bool    empty( void ) const;
        void    swap( OutputEvent & rhSide );
        int     compare( const OutputEvent & rhSide ) const;

        bool    initialize( const OM_OutputEvent & omOutputEvent );
        bool    initialize( Uint32              packetIndex,
                            OM_EventType        eventType,
                            const char *        sourceFile,
                            Uint32              sourceLine,
                            const char *        scopeName,
                            const char *        eventString );

        const OM_OutputEvent &  om_output_event( void ) const
            {
                return (m_Structure);
            };
        Uint8   get_source_platform_id( void ) const
            {
                return (m_Structure.m_SourcePlatform);
            };
        Uint16   get_structure_size_of( void ) const
            {
                return (m_Structure.m_SizeOf);
            };
        OM_ProcessIDType   get_process_id( void ) const
            {
                return (m_Structure.m_ProcessID);
            };
        OM_ThreadIDType   get_thread_id( void ) const
            {
                return (m_Structure.m_ThreadID);
            };
        Uint32   get_packet_index( void ) const
            {
                return (m_Structure.m_PacketIndex);
            };
        OM_TimeStruct   get_time_struct( void ) const
            {
                return (m_Structure.m_TimeStruct);
            };
        TimeStamp  get_time_stamp( void ) const
            {
                return (TimeStamp(m_Structure.m_TimeStruct));
            };
        OM_EventType   get_event_type( void ) const
            {
                return (m_Structure.m_EventType);
            };
        std::string  get_source_file( void ) const
            {
                std::string resultStr;
                SafeStringCopy( resultStr, m_Structure.m_SourceFile, sizeof(m_Structure.m_SourceFile) );
                return (resultStr);
            };
        Uint32   get_source_line( void ) const
            {
                return (m_Structure.m_SourceLine);
            };
        std::string  get_scope_string( void ) const
            {
                std::string resultStr;
                SafeStringCopy( resultStr, m_Structure.m_ScopeName, sizeof(m_Structure.m_ScopeName) );
                return (resultStr);
            };
        std::string  get_event_string( void ) const
            {
                std::string resultStr;
                SafeStringCopy( resultStr, m_Structure.m_EventString, sizeof(m_Structure.m_EventString) );
                return (resultStr);
            };

};
//.


/////////////////////////////////////////////////////////////////////////////
//  <DG_SUB_TOPIC> OutputEvent
//  Inline Implementation

/////////////////////////////////////////////////////////////////////////////
//! bool operator == ( const OutputEvent &, const OutputEvent & )
//
//  :Implementation
//"
inline bool  operator == ( const OutputEvent & lhSide, const OutputEvent & rhSide )
{
    return ( lhSide.compare(rhSide) == 0 );
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool operator != ( const OutputEvent &, const OutputEvent & )
//
//  :Implementation
//"
inline bool  operator != ( const OutputEvent & lhSide, const OutputEvent & rhSide )
{
    return ( lhSide.compare(rhSide) != 0 );
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool operator <= ( const OutputEvent &, const OutputEvent & )
//
//  :Implementation
//"
inline bool  operator <= ( const OutputEvent & lhSide, const OutputEvent & rhSide )
{
    return ( lhSide.compare(rhSide) <= 0 );
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool operator < ( const OutputEvent &, const OutputEvent & )
//
//  :Implementation
//"
inline bool  operator < ( const OutputEvent & lhSide, const OutputEvent & rhSide )
{
    return ( lhSide.compare(rhSide) < 0 );
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool operator >= ( const OutputEvent &, const OutputEvent & )
//
//  :Implementation
//"
inline bool  operator >= ( const OutputEvent & lhSide, const OutputEvent & rhSide )
{
    return ( lhSide.compare(rhSide) >= 0 );
}
//.


/////////////////////////////////////////////////////////////////////////////
//! bool operator > ( const OutputEvent &, const OutputEvent & )
//
//  :Implementation
//"
inline bool  operator > ( const OutputEvent & lhSide, const OutputEvent & rhSide )
{
    return ( lhSide.compare(rhSide) > 0 );
}
//.


}; // namespace CExOutput

#endif // _CExOutput_OutputEvent_h

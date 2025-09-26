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
//      CExtend\Libraries\CExOutput\CExOutput_Obsolete.cpp
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//      <DT_SUB_TOPIC> Obsolete
//
/////////////////////////////////////////////////////////////////////////////

#include "CExOutput.h"

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! Obsolete( void )
//
//  :Description
//      This is the default constructor for the Obsolete class.  It will
//      create the object in the empty state.
//
//  :Implementation
//"
Obsolete::Obsolete( void )
    :   m_EventType( OM_MSGID_D_OBSOLETE|OM_CATAGORY_DEBUG )
    ,   m_ItemMap()
{
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! ~Obsolete( void )
//
//  :Description
//      This is the destructor for the Obsolete class.
//
//  :Implementation
//"
Obsolete::~Obsolete( void )
{
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! static  Obsolete &  get_singleton( void )
//
//  :Implementation
//"
Obsolete &  Obsolete::get_singleton( void )
{
    static Obsolete theOneAndOnly;
    return (theOneAndOnly);
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  trigger( const char *, size_t, const std::string & )
//
//  :Implementation
//"
void  Obsolete::trigger( const std::string & itemName )
{
    // Locate data struct for item (create if necessary)
    ItemMap::iterator iterCurrent = m_ItemMap.find( itemName );
    if ( iterCurrent == m_ItemMap.end() )
    {
        private_create_entry( itemName );
        iterCurrent = m_ItemMap.find( itemName );
    }
    if ( iterCurrent == m_ItemMap.end() )
    {
        return;
    }
    DataStruct &    dataStruct = iterCurrent->second;

    // Increment counter
    dataStruct.m_Count++;

    // Report if necessary
    if ( dataStruct.m_Count < dataStruct.m_Limit )
    {
        std::string messageStr = "Obsolete Item --> " + itemName;
        if ( dataStruct.m_ReplaceName.empty() == false )
        {
            messageStr += " --> Use This Instead --> " + dataStruct.m_ReplaceName + " instead.";
        }
        OM_TRACE1( m_EventType, "%s", messageStr.c_str() );
    }

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  set_limit( const std::string & itemName, Uint64 newLimit)
//
//  :Implementation
//"
void  Obsolete::set_limit( const std::string & itemName, Uint64 newLimit)
{
    // Locate data struct for item (create if necessary)
    ItemMap::iterator iterCurrent = m_ItemMap.find( itemName );
    if ( iterCurrent == m_ItemMap.end() )
    {
        private_create_entry( itemName );
        iterCurrent = m_ItemMap.find( itemName );
    }
    if ( iterCurrent == m_ItemMap.end() )
    {
        return;
    }
    DataStruct &    dataStruct = iterCurrent->second;

    // Set the new limit
    dataStruct.m_Limit = newLimit;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  set_replacement( const std::string & itemName, const std::string & replaceItemName )
//
//  :Implementation
//"
void  Obsolete::set_replacement( const std::string & itemName, const std::string & replaceItemName )
{
    // Verify replace name
    if ( replaceItemName.length() > MaxItemNameLength )
    {
        return;
    }

    // Locate data struct for item (create if necessary)
    ItemMap::iterator iterCurrent = m_ItemMap.find( itemName );
    if ( iterCurrent == m_ItemMap.end() )
    {
        private_create_entry( itemName );
        iterCurrent = m_ItemMap.find( itemName );
    }
    if ( iterCurrent == m_ItemMap.end() )
    {
        return;
    }
    DataStruct &    dataStruct = iterCurrent->second;

    // Store the replacement name
    dataStruct.m_ReplaceName = replaceItemName;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  reset_counter( const std::string & itemName );
//
//  :Implementation
//"
void  Obsolete::reset_counter( const std::string & itemName )
{
    // Locate data struct for item (create if necessary)
    ItemMap::iterator iterCurrent = m_ItemMap.find( itemName );
    if ( iterCurrent == m_ItemMap.end() )
    {
        private_create_entry( itemName );
        iterCurrent = m_ItemMap.find( itemName );
    }
    if ( iterCurrent == m_ItemMap.end() )
    {
        return;
    }
    DataStruct &    dataStruct = iterCurrent->second;

    // Reset the counter
    dataStruct.m_Count = 0;
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  report( const std::string & itemName ) const;
//
//  :Implementation
//"
void  Obsolete::report( const std::string & itemName ) const
{
    ItemMap::const_iterator iterCurrent = m_ItemMap.find( itemName );
    if ( iterCurrent == m_ItemMap.end() )
    {
        return;
    }
    const DataStruct & dataStruct = iterCurrent->second;

    private_report( dataStruct );
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  report_all( void ) const;
//
//  :Implementation
//"
void  Obsolete::report_all( void ) const
{
    for ( ItemMap::const_iterator iterWalk = m_ItemMap.begin();
          iterWalk != m_ItemMap.end();
          iterWalk++ )
    {
        const DataStruct & dataStruct = iterWalk->second;
        private_report( dataStruct );
    }
    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void    private_create_entry( const std::string & itemName )
//
//  :Implementation
//"
void  Obsolete::private_create_entry( const std::string & itemName )
{
    // Verify item name
    if ( (itemName.empty() == true)                 ||
         (itemName.length() > MaxItemNameLength)    )
    {
        return;
    }

    DataStruct  dataStruct;
    dataStruct.m_ItemName           = itemName;
    dataStruct.m_Count              = 0;
    dataStruct.m_Limit              = DefaultReportLimit;
    dataStruct.m_ReplaceName        .clear();

    m_ItemMap.insert( ItemMap::value_type( itemName, dataStruct ) );

    return;
}
//.


/////////////////////////////////////////////////////////////////////////////
//! void  private_report( const DataStruct & dataStruct ) const
//
//  :Implementation
//"
void  Obsolete::private_report( const DataStruct & dataStruct ) const
{
    (void)(dataStruct);
    OM_TRACE0( m_EventType, "--- Obsolete Item --------------------------------------" );
    OM_TRACE1( m_EventType, "        Name = %s", dataStruct.m_ItemName.c_str() );
    OM_TRACE1( m_EventType, " Replacement = %s", dataStruct.m_ReplaceName.c_str() );
    OM_TRACE1( m_EventType, "       Count = %lu", static_cast<unsigned long>(dataStruct.m_Count) );
    OM_TRACE0( m_EventType, "--------------------------------------------------------" );
    return;
}
//.


}; // namespace CExOutput



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
//      CExtend\Libraries\CExOutput\CExOutput_Obsolete.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExOutput
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExOutput_Obsolete_h
#define _CExOutput_Obsolete_h

namespace CExOutput
{

/////////////////////////////////////////////////////////////////////////////
//! Obsolete
//
//  :Description
//      This class is used by the macros
//          - OM_REPORT_OBSOLETE
//          - OM_REPORT_OBSOLETE_REPLACE
//
//      These macros are used to denote a function or piece of code as
//      obsolete.  Useful for when refactoring code and the old function
//      signature needs to be maintained.
//
//      Placing a copy of the above macro in your obsolete function will
//      cause an output message to be generated on the first call
//      of the function but not later calls.
//
//      There is also functionality to generate a report on all
//      obsolete functions used to date.  (Useful in large code bases
//      while your migrating the code)
//
//  :Declaration
//"
class Obsolete
{
    // Embedded Types
    public:
        enum { MaxItemNameLength    = 256 };
        enum { DefaultReportLimit   = 16  };
    private:
        typedef struct
        {
            std::string     m_ItemName;
            Uint32          m_Count;
            Uint32          m_Limit;
            std::string     m_ReplaceName;
        } DataStruct;
        typedef std::map< std::string , DataStruct >    ItemMap;

    // Data Members
    private:
        const OM_EventType  m_EventType;
        ItemMap             m_ItemMap;

    // Construction, Use get_singleton() to access
    private:
        Obsolete( void );
    public:
        ~Obsolete( void );
    // Not Implemented, Do Not Use
    private:
        Obsolete( const Obsolete & rhSide );
        const Obsolete &  operator = ( const Obsolete & rhSide );

    // Public Interface
    public:
        static  Obsolete &  get_singleton( void );

        void    trigger( const std::string &  itemName );

        void    set_limit( const std::string & itemName, Uint64 newLimit);
        void    set_replacement( const std::string & itemName, const std::string & replaceItemName );
        void    reset_counter( const std::string & itemName );

        void    report( const std::string & itemName ) const;
        void    report_all( void ) const;

    // Private Interface
    private:
        void    private_create_entry( const std::string & itemName );
        void    private_report( const DataStruct & dataStruct ) const;
};
//.

/////////////////////////////////////////////////////////////////////////////

}; // namespace CExOutput

#endif // _CExOutput_Obsolete_h



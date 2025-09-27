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
//      CExThreading
//
//  File:
//      CExtend\Libraries\CExThreading\CExThreading_SafeObject.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_SafeObject_h
#define _CExThreading_SafeObject_h

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! SafeObject
//
//  :Description
//      This class is used to provide a mechanism to wrap an instance
//      of a user supplied data type in such a way that access to the
//      underlying data can be performed safely from multiple threads
//      of execution.
//
//      This is a template class.  The contained type must support
//      the following member function signatures
//          - default constructor, destructor
//          - assignment operator
//
//  :Definition
//"
template < typename T >
    class SafeObject
{
    // Data Members
    private:
        mutable Mutex   m_Mutex;
        T               m_Data;

    // Construction
    public:
        SafeObject( void );
        explicit SafeObject( const T & initVal );
        SafeObject( const SafeObject &  rhSide );
        ~SafeObject( void );
        const SafeObject &  operator = ( const T & initVal );
        const SafeObject &  operator = ( const SafeObject &  rhSide );

    // Public Interface
    public:
        void    set( const T &  newVal );
        void    get( T & theVal ) const;
        T       value( void ) const;
};
//.


// <DG_SUB_TOPIC> SafeObject

/////////////////////////////////////////////////////////////////////////////
//! template < typename T > SafeObject( void )
//
//  :Description
//      This is the standard constructor for the SafeObject class.
//
//  :Implementation
//"
template < typename T >
    SafeObject< T >::SafeObject( void )
    {
        AutoLock   localMutexZone( m_Mutex );
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > SafeObject( const T & )
//
//  :Description
//      This is the standard copy constructor for the SafeObject class.
//
//  :Implementation
//"
template < typename T >
    SafeObject< T >::SafeObject( const T &  initVal )
    {
        set( initVal );
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > SafeObject( const SafeObject< T > &  )
//
//  :Description
//      This is the standard copy constructor for the SafeObject class.
//
//  :Implementation
//"
template < typename T >
    SafeObject< T >::SafeObject( const SafeObject< T > & rhSide )
    {
        T   tempValue;
        rhSide.get( tempValue );
        set( tempValue );
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > ~SafeObject( void )
//
//  :Description
//      This is the destructor for the SafeObject class.
//
//  :Implementation
//"
template < typename T >
    SafeObject< T >::~SafeObject( void )
    {
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > const SafeObject< T > &  operator = ( const T & )
//
//  :Description
//      This is the extended copy operator for the SafeObject class.
//      It acts the same as the set() function.
//
//  :Implementation
//"
template < typename T >
    const SafeObject< T > &  SafeObject< T >::operator = ( const T & initVal )
    {
        set( initVal );
        return (*this);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > const SafeObject< T > &  operator = ( const SafeObject< T > & )
//
//  :Description
//      This is the standard copy operator for the SafeObject class.
//
//  :Implementation
//"
template < typename T >
    const SafeObject< T > &  SafeObject< T >::operator = ( const SafeObject< T > & rhSide )
    {
        if ( this != &rhSide )
        {
            T   tempValue;
            rhSide.get( tempValue );
            set( tempValue );
        }
        return (*this);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  void  set( const T & )
//
//  :Arguments
//      = const T &  newVal
//          The new value the SafeObject class will store.
//
//  :Description
//      This function is called to set the underlying data element
//      stored by this class.
//
//  :Implementation
//"
template < typename T >
    void  SafeObject< T >::set( const T & newVal )
    {
        AutoLock   localMutexZone( m_Mutex );
        m_Data = newVal;
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  void  get( T & theVal ) const
//
//  :Arguments
//      = T &  theVal
//          A reference to the caller supplied instance of T into which
//          the currently contained copy of T will be copied.
//
//  :Description
//      This function is called to retrieve a copy of the currently
//      stored data element.
//
//  :Implementation
//"
template < typename T >
    void  SafeObject< T >::get( T & theVal ) const
    {
        AutoLock   localMutexZone( m_Mutex );
        theVal = m_Data;
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  T  value( void ) const
//
//  :Description
//      This function will return a copy of the currently stored data
//      element.
//
//  :Implementation
//"
template < typename T >
    T  SafeObject< T >::value( void ) const
    {
        AutoLock   localMutexZone( m_Mutex );
        T returnValue = m_Data;
        return (returnValue);
    }
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExThreading

#endif // _CExThreading_SafeObject_h


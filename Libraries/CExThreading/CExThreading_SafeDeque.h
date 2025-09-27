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
//      CExtend\Libraries\CExThreading\CExThreading_SafeDeque.h
//
//  DocTool Settings:
//      <DT_SUB_TOPIC> .
//      <DT_SUB_TOPIC> Libs
//      <DT_SUB_TOPIC> CExThreading
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _CExThreading_SafeDeque_h
#define _CExThreading_SafeDeque_h

namespace CExThreading
{

/////////////////////////////////////////////////////////////////////////////
//! SafeDeque
//
//  :Description
//      This class is used to provide a mechanism to wrap an instance
//      of a user supplied data type in such a way that access to the
//      underlying data can be performed safely from multiple threads
//      of execution.
//
//  :Definition
//"
template < typename T >
    class SafeDeque
{
    // Embedded Types
    private:
        typedef std::deque< T >                     ObjectDeque;
    public:
        typedef typename ObjectDeque::size_type     size_type;

    // Data Members
    private:
        mutable Mutex   m_Mutex;
        ObjectDeque     m_ObjectDeque;
        bool            m_fAllowEmpty;
        size_type       m_MaxSize;

    // Construction
    public:
        SafeDeque( bool fAllowEmpty = true, size_type maxSize = 0 );
        SafeDeque( const SafeDeque &  rhSide );
        ~SafeDeque( void );
        const SafeDeque &  operator = ( const SafeDeque &  rhSide );

    // Public Interface
    public:
        bool        empty( void ) const;
        size_type   size( void ) const;
        size_type   max_size( void ) const;
        bool        allow_empty( void ) const;

        bool    push_front( const T &  newVal );
        bool    push_back( const T &  newVal );
        bool    pop_front( T & theVal );
        bool    pop_back( T & theVal );
};
//.


/////////////////////////////////////////////////////////////////////////////
//  Inline Implementation
//  <DG_SUB_TOPIC> SafeDeque


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > SafeDeque( bool = true, size_type = 0 )
//
//  :Description
//      This is the standard constructor for the SafeDeque class.
//
//      If the fAllowEmpty flag is supplied as false then the class
//      will not permit empty objects to be added to the Deque.
//
//      The maxSize argument is used to place a limit on the maximum
//      number of objects that can be stored by this class.  If
//      the supplied value is zero (the default value) then there is
//      no limit enforced.
//
//  :Implementation
//"
template < typename T >
    SafeDeque< T >::SafeDeque( bool fAllowEmpty /*= true*/, size_type maxSize /*= 0*/ )
    {
        AutoLock   localMutexZone( m_Mutex );
        m_ObjectDeque.clear();
        m_fAllowEmpty   = (fAllowEmpty != false);
        m_MaxSize       = maxSize;
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > SafeDeque( const SafeDeque< T > &  )
//
//  :Description
//      This is the standard copy constructor for the SafeDeque class.
//
//  :Implementation
//"
template < typename T >
    SafeDeque< T >::SafeDeque( const SafeDeque< T > & rhSide )
    {
        bool        fAllowEmpty = false;
        size_type   maxSize     = 0;
        ObjectDeque tempDeque;
        {
            AutoLock   localMutexZone( rhSide.m_Mutex );
            tempDeque   = rhSide.m_ObjectDeque;
            fAllowEmpty = rhSide.m_fAllowEmpty;
            maxSize     = rhSide.m_MaxSize;
        }
        AutoLock   localMutexZone( m_Mutex );
        m_ObjectDeque.swap ( tempDeque );
        m_fAllowEmpty   = fAllowEmpty;
        m_MaxSize       = maxSize;
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > ~SafeDeque( void )
//
//  :Description
//      This is the destructor for the SafeDeque class.
//
//  :Implementation
//"
template < typename T >
    SafeDeque< T >::~SafeDeque( void )
    {
        AutoLock   localMutexZone( m_Mutex );
        m_ObjectDeque.clear();
        return;
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T > const SafeDeque< T > &  operator = ( const SafeDeque< T > & )
//
//  :Description
//      This is the standard copy operator for the SafeDeque class.
//
//  :Implementation
//"
template < typename T >
    const SafeDeque< T > &  SafeDeque< T >::operator = ( const SafeDeque< T > & rhSide )
    {
        if ( this != &rhSide )
        {
            bool        fAllowEmpty = false;
            size_type   maxSize     = 0;
            ObjectDeque tempDeque;
            {
                AutoLock   localMutexZone( rhSide.m_Mutex );
                tempDeque   = rhSide.m_ObjectDeque;
                fAllowEmpty = rhSide.m_fAllowEmpty;
                maxSize     = rhSide.m_MaxSize;
            }
            AutoLock   localMutexZone( m_Mutex );
            m_ObjectDeque.swap ( tempDeque );
            m_fAllowEmpty   = fAllowEmpty;
            m_MaxSize       = maxSize;
        }
        return (*this);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  bool  empty( void ) const
//
//  :Returns
//      If the current object is empty (size() of the deque is zero)
//      then the function returns true.  Otherwise the function
//      returns false.
//
//  :Implementation
//"
template < typename T >
    bool  SafeDeque< T >::empty( void ) const
    {
        AutoLock   localMutexZone( m_Mutex );
        bool fResult = m_ObjectDeque.empty();
        return (fResult);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  size_type   size( void ) const
//
//  :Description
//      This function returns the current number of objects stored
//      by the current SafeDeque object.
//
//  :Implementation
//"
template < typename T >
    typename SafeDeque< T >::size_type  SafeDeque< T >::size( void ) const
    {
        AutoLock   localMutexZone( m_Mutex );
        size_type sResult = m_ObjectDeque.size();
        return (sResult);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  size_type   max_size( void ) const
//
//  :Description
//      This function returns the maximum number of objects the
//      current SafeDeque object can contain.  If the value returned
//      is zero then the class enforces no maximum limit.
//
//  :Implementation
//"
template < typename T >
    typename SafeDeque< T >::size_type  SafeDeque< T >::max_size( void ) const
    {
        AutoLock   localMutexZone( m_Mutex );
        size_type sResult = m_MaxSize;
        return (sResult);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! bool   allow_empty( void ) const
//
//  :Description
//      If this function returns true, then the current object will allow
//      empty objects to be added to the current SafeDeque.  If this
//      function returns false then the push_xx() functions will
//      fail if empty objects are supplied.
//
//  :Implementation
//"
template < typename T >
    bool  SafeDeque< T >::allow_empty( void ) const
    {
        AutoLock   localMutexZone( m_Mutex );
        bool fAllowEmpty = (m_fAllowEmpty != false);
        return (fAllowEmpty);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  bool  push_front( const T & )
//
//  :Arguments
//      = const T &  newVal
//          The new value the SafeDeque class will store.
//
//  :Description
//      This function is called to push a copy of the supplied object
//      onto the front of the deque.
//
//      This function will obey the fAllowEmpty and MaxSize attributes
//      when adding the supplied object.
//
//  :Returns
//      If the supplied object is succesfully added to the current
//      SafeDeque the function returns true.  If the function
//      cannot add the indicated object (max size or empty) then
//      the function returns false and the object is not added.
//
//  :Implementation
//"
template < typename T >
    bool  SafeDeque< T >::push_front( const T & newVal )
    {
        AutoLock   localMutexZone( m_Mutex );
        if ( m_MaxSize != 0 )
        {
            if ( m_ObjectDeque.size() >= m_MaxSize )
            {
                return  (false);
            }
        }
        if ( m_fAllowEmpty == false )
        {
            if ( newVal.empty() == true )
            {
                return (false);
            }
        }
        m_ObjectDeque.push_front( newVal );
        return (true);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  bool  push_back( const T & )
//
//  :Arguments
//      = const T &  newVal
//          The new value the SafeDeque class will store.
//
//  :Description
//      This function is called to push a copy of the supplied object
//      onto the back of the queue.
//
//      This function will obey the fAllowEmpty and MaxSize attributes
//      when adding the supplied object.
//
//  :Returns
//      If the supplied object is succesfully added to the current
//      SafeDeque the function returns true.  If the function
//      cannot add the indicated object (max size or empty) then
//      the function returns false and the object is not added.
//
//  :Implementation
//"
template < typename T >
    bool  SafeDeque< T >::push_back( const T & newVal )
    {
        AutoLock   localMutexZone( m_Mutex );
        if ( m_MaxSize != 0 )
        {
            if ( m_ObjectDeque.size() >= m_MaxSize )
            {
                return  (false);
            }
        }
        if ( m_fAllowEmpty == false )
        {
            if ( newVal.empty() == true )
            {
                return (false);
            }
        }
        m_ObjectDeque.push_back( newVal );
        return (true);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  bool  pop_front( T & theVal )
//
//  :Arguments
//      = T &  theVal
//          A reference to the caller supplied instance of T into which
//          the currently contained copy of T will be copied.
//
//  :Description
//      This function is called to retrieve a copy of the object at the
//      front of the queue.
//
//  :Returns
//      If the queue is non empty the supplied object is made equal
//      to the front element and then the front element is removed from
//      the internal queue.  The function then returns true.
//
//      If the queue is empty the supplied object is set equal to
//      a new empty instance of itself and the function returns false.
//
//  :Implementation
//"
template < typename T >
    bool  SafeDeque< T >::pop_front( T & theVal )
    {
        AutoLock   localMutexZone( m_Mutex );
        bool    fResult = false;
        if ( m_ObjectDeque.empty() == true )
        {
            theVal = T();
        }
        else
        {
            theVal = m_ObjectDeque.front();
            m_ObjectDeque.pop_front();
            fResult = true;
        }
        return (fResult);
    }
//.


/////////////////////////////////////////////////////////////////////////////
//! template < typename T >  bool  pop_back( T & theVal )
//
//  :Arguments
//      = T &  theVal
//          A reference to the caller supplied instance of T into which
//          the currently contained copy of T will be copied.
//
//  :Description
//      This function is called to retrieve a copy of the object at the
//      front of the queue.
//
//  :Returns
//      If the queue is non empty the supplied object is made equal
//      to the front element and then the front element is removed from
//      the internal queue.  The function then returns true.
//
//      If the queue is empty the supplied object is set equal to
//      a new empty instance of itself and the function returns false.
//
//  :Implementation
//"
template < typename T >
    bool  SafeDeque< T >::pop_back( T & theVal )
    {
        AutoLock   localMutexZone( m_Mutex );
        bool    fResult = false;
        if ( m_ObjectDeque.empty() == true )
        {
            theVal = T();
        }
        else
        {
            theVal = m_ObjectDeque.back();
            m_ObjectDeque.pop_back();
            fResult = true;
        }
        return (fResult);
    }
//.


/////////////////////////////////////////////////////////////////////////////

}; // namespace CExThreading

#endif // _CExThreading_SafeDeque_h


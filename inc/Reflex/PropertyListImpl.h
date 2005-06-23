// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Reflex_PropertyListImpl
#define ROOT_Reflex_PropertyListImpl


// Include files
#include "Reflex/Kernel.h"
#include "Reflex/Any.h"
#include <map>
#include <iostream>

namespace ROOT {
  namespace Reflex {

    /**
     * @class PropertyList PropertyList.h Reflex/PropertyList.h
     * @author Stefan Roiser
     * @date 24/11/2003
     * @ingroup Ref
     */
    class PropertyListImpl {

      friend std::ostream & operator << ( std::ostream & s,
                                          const PropertyListImpl & p );
    public:

      /** default constructor */
      PropertyListImpl();


     /** copy constructor */
      PropertyListImpl( const PropertyListImpl & pl);


      /** destructor */
      virtual ~PropertyListImpl();


      /**
       * AddProperty will add a key value pair to the PropertyNth lsit
       * @param key the key of the PropertyNth
       * @param value the value of the PropertyNth (as any object)
       */
      void AddProperty( const std::string & key,
                        const Any & value );


      /**
       * AddProperty will add a key value pair to the PropertyNth lsit
       * @param key the key of the PropertyNth
       * @param value the value of the PropertyNth (as any object)
       */
      void AddProperty( const std::string & key,
                        const char * value );

      
      /**
       * ClearProperties will remove all properties from the list
       */
      void ClearProperties();

      
      /**
       * RemoveProperty will remove a key value pair to the PropertyNth lsit
       * @param key the key of the PropertyNth
       */
      void RemoveProperty( const std::string & key );


      /**
       * HasKey will return true if the PropertyNth list contains the key
       * @param  key the PropertyNth key
       * @return nth PropertyNth key
       */
      bool HasKey( const std::string & key ) const;


      /**
       * PropertyCount will return the number of properties attached
       * to this item
       * @return number of properties
       */
      size_t PropertyCount() const;


      /**
       * PropertyKeys will return all keys of this PropertyNth list
       * @return all PropertyNth keys
       */
      std::string PropertyKeys() const;


      /**
       * propertyNumString will return the nth PropertyNth as a string if printable
       * @param  key the PropertyNth key
       * @return nth PropertyNth value as string
       */
      std::string PropertyAsString(const std::string & key) const;


      /**
       * propertyNumValue will return the nth PropertyNth value 
       * @param  key the PropertyNth key
       * @return nth PropertyNth value
       */
      Any PropertyValue(const std::string & key) const;

    private:

      /** the TypeNth of properties */
      typedef std::map< std::string, Any > Properties;

      
      /** the properties of the item */
      Properties * fProperties;

    }; // class PropertyListImpl

    /** 
     * will put the PropertyNth (key and value) on the ostream if printable
     * @param s the reference to the stream
     * @return the stream
     */
    std::ostream & operator << ( std::ostream & s,
				 const PropertyListImpl & p );

  } //namespace Reflex
} //namespace ROOT


//-------------------------------------------------------------------------------
inline ROOT::Reflex::PropertyListImpl::PropertyListImpl() 
//-------------------------------------------------------------------------------
  : fProperties( 0 ) {}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::PropertyListImpl::PropertyListImpl( const PropertyListImpl & pl ) 
//-------------------------------------------------------------------------------
  : fProperties( pl.fProperties ) {}

  
//-------------------------------------------------------------------------------
inline ROOT::Reflex::PropertyListImpl::~PropertyListImpl() {
//-------------------------------------------------------------------------------
  if ( fProperties ) delete fProperties;
}


//-------------------------------------------------------------------------------
inline void ROOT::Reflex::PropertyListImpl::AddProperty( const std::string & key,
                                                         const Any & value ) {
//-------------------------------------------------------------------------------
  if ( ! fProperties ) fProperties = new Properties();
  (*fProperties)[ key ] = value;
}


//-------------------------------------------------------------------------------
inline void ROOT::Reflex::PropertyListImpl::AddProperty( const std::string & key,
                                                         const char* value ) {
//-------------------------------------------------------------------------------
  if ( ! fProperties ) fProperties = new Properties();
  (*fProperties)[ key ] = value;
}


//-------------------------------------------------------------------------------
inline void ROOT::Reflex::PropertyListImpl::RemoveProperty( const std::string & key ) {
//-------------------------------------------------------------------------------
  if ( fProperties ) fProperties->erase( key );
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::PropertyListImpl::HasKey( const std::string & key ) const {
//-------------------------------------------------------------------------------
  if ( fProperties && fProperties->find( key ) != fProperties->end() ) 
    return true;
  return false;
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::PropertyListImpl::PropertyCount() const {
//-------------------------------------------------------------------------------
  if ( fProperties ) return fProperties->size();
  return 0;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Any
ROOT::Reflex::PropertyListImpl::PropertyValue( const std::string & key ) const {
//-------------------------------------------------------------------------------
  if ( fProperties ) return (*fProperties)[ key ];
  return Any();
}

#endif // ROOT_Reflex_PropertyListImpl

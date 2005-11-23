// @(#)root/reflex:$Name:  $:$Id: PropertyListImpl.cxx,v 1.2 2005/11/03 15:24:40 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#include "Reflex/PropertyListImpl.h"

#include <sstream>

//-------------------------------------------------------------------------------
std::ostream & ROOT::Reflex::operator<<( std::ostream & s,
                                         const PropertyListImpl & p ) {
//-------------------------------------------------------------------------------
   if ( p.fProperties ) {
      for ( PropertyListImpl::Properties::const_iterator pIter = p.fProperties->begin();
            pIter != p.fProperties->end(); ++pIter) {
         s << pIter->first << " : " << pIter->second << std::endl;
      }
   }
   return s;
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::PropertyListImpl::ClearProperties() {
//-------------------------------------------------------------------------------
   if ( fProperties ) delete fProperties;
   fProperties = 0;
}


//-------------------------------------------------------------------------------
std::string ROOT::Reflex::PropertyListImpl::PropertyKeys() const {
//-------------------------------------------------------------------------------
   std::string s = "";
   if ( fProperties ) {
      for(Properties::const_iterator pIter = fProperties->begin(); 
          pIter != fProperties->end(); ) {
         s += pIter->first;
         if (++pIter != fProperties->end() ) { s += ", "; }
      }
   }
   return s;
}


//-------------------------------------------------------------------------------
std::string 
ROOT::Reflex::PropertyListImpl::PropertyAsString( const std::string & key ) const {
//-------------------------------------------------------------------------------
   if ( fProperties && HasKey(key) ) {
      std::ostringstream o;
      o << PropertyValue(key);
      return o.str();
   }
   return "";
}



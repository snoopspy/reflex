// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#include "Function.h"

#include "Reflex/Tools.h"

//-------------------------------------------------------------------------------
ROOT::Reflex::Function::Function( const Type & ReturnType,
                                  std::vector< Type > parameters,
                                  const std::type_info & TypeInfo,
                                  TYPE functionType) 
//-------------------------------------------------------------------------------
  : TypeBase( BuildTypeName(ReturnType, parameters, QUALIFIED | SCOPED).c_str(), 0, functionType, TypeInfo ),
    fParameters(parameters),
    fReturnType(ReturnType),
    fModifiers(0) { }


//-------------------------------------------------------------------------------
std::string ROOT::Reflex::Function::Name( unsigned int mod ) const {
//-------------------------------------------------------------------------------
  return BuildTypeName( fReturnType, fParameters, mod );
}


//-------------------------------------------------------------------------------
std::string ROOT::Reflex::Function::BuildTypeName( const Type & ret, 
                                                   const std::vector< Type > & pars,
                                                   unsigned int mod ) {
//-------------------------------------------------------------------------------
  std::string tyname = ret.Name( mod )+ " (";
  if ( pars.size() > 0 ) {
    std::vector< Type >::const_iterator it;
    for ( it = pars.begin(); it != pars.end(); ) {
      tyname += it->Name( mod );
      if ( ++it != pars.end() ) tyname += ", ";
    }
  }
  else {
    tyname += "void";
  }
  tyname += ")";
  return tyname;
}

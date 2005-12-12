// @(#)root/reflex:$Name:  $:$Id: VariableBuilder.cxx,v 1.4 2005/11/23 16:08:08 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#include "Reflex/Builder/VariableBuilder.h"

#include "Namespace.h"
#include "DataMember.h"

//-------------------------------------------------------------------------------
ROOT::Reflex::VariableBuilderImpl::VariableBuilderImpl( const char * nam,
                                                        const Type & typ,
                                                        size_t offs,
                                                        unsigned int modifiers ) 
   : fDataMember(Member()) {
//-------------------------------------------------------------------------------
   std::string declScope = "";
   std::string memName = std::string( nam );
   size_t pos = memName.rfind( "::" );
   if ( pos != std::string::npos ) {
      declScope = memName.substr( 0, pos );
      memName = memName.substr( pos + 2 );
   }

   Scope sc = Scope::ByName(declScope);
  
   if ( ! sc ) {
      sc = (new Namespace(declScope.c_str()))->ThisScope();
   }
  
   if ( ! sc.IsNamespace()) throw RuntimeError("Declaring At is not a namespace");

   sc.AddDataMember( memName.c_str(),
                     typ,
                     offs,
                     modifiers );
}


//-------------------------------------------------------------------------------
ROOT::Reflex::VariableBuilderImpl::~VariableBuilderImpl() {
//-------------------------------------------------------------------------------
   FireFunctionCallback( fDataMember );
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::VariableBuilderImpl::AddProperty( const char * key, 
                                                     const char * value ) {
//-------------------------------------------------------------------------------
   fDataMember.Properties().AddProperty( key , value );
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::VariableBuilderImpl::AddProperty( const char * key, 
                                                     Any value ) {
//-------------------------------------------------------------------------------
   fDataMember.Properties().AddProperty( key , value );
}


//-------------------------------------------------------------------------------
ROOT::Reflex::VariableBuilder::VariableBuilder( const char * nam, 
                                                const Type & typ,
                                                size_t offs,
                                                unsigned int modifiers) 
   : fDataMember( Member()) {
//-------------------------------------------------------------------------------
   std::string declScope = Tools::GetScopeName(nam);
   std::string memName = Tools::GetBaseName(nam);
   
   Scope sc = Scope::ByName(declScope);
  
   if ( ! sc ) {
      sc = (new Namespace(declScope.c_str()))->ThisScope();
   }
  
   if ( ! sc.IsNamespace()) throw RuntimeError("Declaring scope is not a namespace");

   DataMember* dm = new DataMember( memName.c_str(),
                                    typ,
                                    offs,
                                    modifiers );
   sc.AddDataMember(Member(dm));
   fDataMember = Member(dm);
}


//-------------------------------------------------------------------------------
ROOT::Reflex::VariableBuilder::~VariableBuilder() {
//-------------------------------------------------------------------------------
  
   FireFunctionCallback( fDataMember );
}


//-------------------------------------------------------------------------------
ROOT::Reflex::VariableBuilder & 
ROOT::Reflex::VariableBuilder::AddProperty( const char * key, 
                                            const char * value ) {
//-------------------------------------------------------------------------------
   fDataMember.Properties().AddProperty( key , value );
   return * this;
}


//-------------------------------------------------------------------------------
ROOT::Reflex::VariableBuilder & 
ROOT::Reflex::VariableBuilder::AddProperty( const char * key, 
                                            Any value ) {
//-------------------------------------------------------------------------------
   fDataMember.Properties().AddProperty( key , value );
   return * this;
}


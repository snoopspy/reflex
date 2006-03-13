// @(#)root/reflex:$Name:  $:$Id: PointerToMember.cxx,v 1.4 2006/03/06 12:51:46 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2006, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#define REFLEX_BUILD

#include "PointerToMember.h"

//-------------------------------------------------------------------------------
ROOT::Reflex::PointerToMember::PointerToMember( const Type & pointerToMemberType,
                                                const std::type_info & ti ) 
//------------------------------------------------------------------------------- 
   : TypeBase( BuildTypeName( pointerToMemberType ).c_str(), sizeof(void*), POINTERTOMEMBER, ti ),
     fPointerToMemberType( pointerToMemberType ) {}


//-------------------------------------------------------------------------------
std::string ROOT::Reflex::PointerToMember::Name( unsigned int mod ) const { 
//-------------------------------------------------------------------------------
   return BuildTypeName( fPointerToMemberType, mod );
}


//-------------------------------------------------------------------------------
std::string ROOT::Reflex::PointerToMember::BuildTypeName( const Type & pointerToMemberType,
                                                          unsigned int mod ) {
//-------------------------------------------------------------------------------
   return pointerToMemberType.Name( mod ) + " ::*";
}
                                                          

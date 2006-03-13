// @(#)root/reflex:$Name:  $:$Id: Union.cxx,v 1.5 2006/03/06 12:51:46 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2006, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#define REFLEX_BUILD

#include "Union.h"

#include "Reflex/Tools.h"

//-------------------------------------------------------------------------------
ROOT::Reflex::Union::Union( const char * unionType,
                            size_t size,
                            const std::type_info & ti ) 
//-------------------------------------------------------------------------------
   : TypeBase( unionType, size, UNION, ti ),
     ScopeBase( unionType, UNION) {}


//-------------------------------------------------------------------------------
ROOT::Reflex::Union::~Union() {
//-------------------------------------------------------------------------------
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member ROOT::Reflex::Union::MemberAt( size_t nth ) const {
//-------------------------------------------------------------------------------
   return ScopeBase::MemberAt( nth );
}

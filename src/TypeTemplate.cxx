// @(#)root/reflex:$Name: HEAD $:$Id: TypeTemplate.cxx,v 1.9 2006/07/04 15:02:55 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2006, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef REFLEX_BUILD
#define REFLEX_BUILD
#endif

#include "Reflex/TypeTemplate.h"
#include "Reflex/Type.h"
#include "Reflex/Member.h"
                                                             
//-------------------------------------------------------------------------------
void ROOT::Reflex::TypeTemplate::AddTemplateInstance( const Type & templateInstance ) const {
//-------------------------------------------------------------------------------
// Add template instance to this template family.
   if ( * this ) fTypeTemplateImpl->AddTemplateInstance( templateInstance );
}

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::TypeTemplate::TemplateInstanceAt( size_t nth ) const {
//-------------------------------------------------------------------------------
// Return the nth template instance of this family.
   if ( * this ) return fTypeTemplateImpl->TemplateInstanceAt( nth );
   return Type();
}



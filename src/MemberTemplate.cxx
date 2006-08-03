// @(#)root/reflex:$Name:  $:$Id: MemberTemplate.cxx,v 1.9 2006/08/01 09:14:33 roiser Exp $
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

#include "Reflex/MemberTemplate.h"
#include "Reflex/internal/OwnedMember.h"
                                              
//-------------------------------------------------------------------------------
const ROOT::Reflex::Member & ROOT::Reflex::MemberTemplate::TemplateInstanceAt( size_t nth ) const {
//-------------------------------------------------------------------------------
// Return the nth template instance of this family.
   if ( * this ) return fMemberTemplateImpl->TemplateInstanceAt( nth );
   return Dummy::Member();
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::MemberTemplate::AddTemplateInstance( const Member & templateInstance ) const {
//-------------------------------------------------------------------------------
// Add member templateInstance to this template family.
   if ( * this ) fMemberTemplateImpl->AddTemplateInstance( templateInstance );
}


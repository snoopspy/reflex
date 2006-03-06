// @(#)root/reflex:$Name:  $:$Id: Enum.cxx,v 1.4 2005/12/12 09:14:14 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2006, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#include "Enum.h"

#include "Reflex/Tools.h"

#include <sstream>


//-------------------------------------------------------------------------------
ROOT::Reflex::Enum::Enum( const char * enumType,
                          const std::type_info & ti )
//-------------------------------------------------------------------------------
   : TypeBase( enumType, sizeof(int), ENUM, ti ),
     ScopeBase( enumType, ENUM ) {}


//-------------------------------------------------------------------------------
ROOT::Reflex::Enum::~Enum() {
//-------------------------------------------------------------------------------
}



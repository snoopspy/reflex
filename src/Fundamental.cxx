// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#include "Fundamental.h"


//-------------------------------------------------------------------------------
ROOT::Reflex::Fundamental::Fundamental( const char * typ,
                                        size_t size,
                                        const std::type_info & ti ) 
//-------------------------------------------------------------------------------
  : TypeBase( typ, size, FUNDAMENTAL, ti ) {}


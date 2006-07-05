// @(#)root/reflex:$Name: HEAD $:$Id: MemberBase.cxx,v 1.9 2006/07/04 15:02:55 roiser Exp $
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

#include "Reflex/MemberBase.h"

#include "Reflex/Member.h"
#include "Reflex/Scope.h"
#include "Reflex/Type.h"
#include "Reflex/Base.h"
#include "Reflex/Object.h"
#include "Reflex/PropertyList.h"

#include "Reflex/Tools.h"
#include "Class.h"

//-------------------------------------------------------------------------------
ROOT::Reflex::MemberBase::MemberBase( const char *  name,
                                      const Type &  type,
                                      TYPE          memberType,
                                      unsigned int  modifiers )
//-------------------------------------------------------------------------------
   : fType( type, modifiers & ( CONST | VOLATILE | REFERENCE ), true ),
     fModifiers( modifiers ),
     fName( name ),
     fScope( Scope() ),
     fMemberType( memberType ),
     fPropertyList( PropertyList( new PropertyListImpl())) {
   // Construct the dictionary info for a member
}


//-------------------------------------------------------------------------------
ROOT::Reflex::MemberBase::~MemberBase() {
//-------------------------------------------------------------------------------
   // destructor.
   fPropertyList.ClearProperties();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::MemberBase::operator ROOT::Reflex::Member () const {
//-------------------------------------------------------------------------------
   // Conversion operator to Member.
   return Member( this );
}


//-------------------------------------------------------------------------------
void * ROOT::Reflex::MemberBase::CalculateBaseObject( const Object & obj ) const {
//-------------------------------------------------------------------------------
   // Return the object address a member lives in.
   char * mem = (char*)obj.Address();
   // check if its a dummy object 
   Type cl = obj.TypeOf();
   // if the object type is not implemented return the Address of the object
   if ( ! cl ) return mem; 
   if ( cl.IsClass() ) {
      if ( DeclaringScope() && ( cl.Id() != (dynamic_cast<const Class*>(DeclaringScope().ToScopeBase()))->ThisType().Id())) {
         // now we know that the Member type is an inherited one
         std::vector < OffsetFunction > basePath = (dynamic_cast<const Class*>(cl.ToTypeBase()))->PathToBase( DeclaringScope());
         if ( basePath.size() ) {
            // there is a path described from the object to the class containing the MemberAt
            std::vector < OffsetFunction >::iterator pIter;
            for ( pIter = basePath.begin(); pIter != basePath.end(); ++pIter ) {
               mem += (*pIter)(mem);
            }
         }
         else {
            throw RuntimeError(std::string(": ERROR: There is no path available from class ")
                               + cl.Name(SCOPED) + " to " + Name(SCOPED));
         }
      }
   }
   else {
      throw RuntimeError(std::string("Object ") + cl.Name(SCOPED) + " does not represent a class");
   }
   return (void*)mem;
}



//-------------------------------------------------------------------------------
ROOT::Reflex::Scope ROOT::Reflex::MemberBase::DeclaringScope() const {
//-------------------------------------------------------------------------------
   // Return the scope the member lives in.
   return fScope;
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::MemberBase::DeclaringType() const {
//-------------------------------------------------------------------------------
   // Return the type the member lives in.
   return DeclaringScope();
}


//-------------------------------------------------------------------------------
std::string ROOT::Reflex::MemberBase::MemberTypeAsString() const {
//-------------------------------------------------------------------------------
// Remember type of the member as a string.
   switch ( fMemberType ) {
   case DATAMEMBER:
      return "DataMember";
      break;
   case FUNCTIONMEMBER:
      return "FunctionMember";
      break;
   default:
      return Reflex::Argv0() + ": ERROR: Member " + Name() +
         " has no Species associated";
   }
}

//-------------------------------------------------------------------------------
ROOT::Reflex::PropertyList ROOT::Reflex::MemberBase::Properties() const {
//-------------------------------------------------------------------------------
// Return the property list attached to this member.
   return fPropertyList;
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::MemberBase::TemplateArgumentAt( size_t /* nth */ ) const {
//-------------------------------------------------------------------------------
// Return the nth template argument (in FunMemTemplInstance)
   return Type();
}


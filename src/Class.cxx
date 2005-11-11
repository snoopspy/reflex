// @(#)root/reflex:$Name:  $:$Id: Class.cxx,v 1.3 2005/11/03 15:24:40 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#include "Class.h"

#include "Reflex/Object.h"
#include "Reflex/Type.h"
#include "Reflex/Base.h"

#include "DataMember.h"
#include "FunctionMember.h"
#include "Reflex/Tools.h"

#include <typeinfo>
#include <iostream>
#include <algorithm>
#if defined (__linux) || defined (__APPLE__)
#include <cxxabi.h>
#endif

//-------------------------------------------------------------------------------
ROOT::Reflex::Class::Class(  const char *           typ, 
                             size_t                 size,
                             const std::type_info & ti,
                             unsigned int           modifiers,
                             TYPE                   classType )
//-------------------------------------------------------------------------------
  : TypeBase( typ, size, classType, ti ),
    ScopeBase( typ, classType ),
    fModifiers( modifiers ),
    fAllBases( 0 ),
    fCompleteType( false ),
    fConstructors( std::vector< Member >()),
    fDestructor( Member()),
    fPathsToBase( PathsToBase()) {}
    

//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::AddBase( const Type &   bas,
                                   OffsetFunction offsFP,
                                   unsigned int   modifiers ) const {
//-------------------------------------------------------------------------------
  Base b( bas, offsFP, modifiers );
  fBases.push_back( b );
}

    
//-------------------------------------------------------------------------------
ROOT::Reflex::Object ROOT::Reflex::Class::CastObject( const Type & to, 
                                                      const Object & obj ) const {
//-------------------------------------------------------------------------------
  std::vector< Base > path = std::vector< Base >();
  if ( HasBase( to, path )) { // up cast 
    // in case of up cast the Offset has to be calculated by Reflex
    size_t obj2 = (size_t)obj.Address();
    for( std::vector< Base >::reverse_iterator bIter = path.rbegin();
         bIter != path.rend(); ++bIter ) {
      obj2 += bIter->Offset((void*)obj2);
    }
    return Object(to,(void*)obj2);
  }
  path.clear();
  Type t = *this;
  if ( to.HasBase( t ) ) {  // down cast
  // use the internal dynamic casting of the compiler (e.g. libstdc++.so)
    void * obj3 = 0;
#if defined (__linux) || defined (__APPLE__)
    obj3 = abi::__dynamic_cast(obj.Address(),
                               (const abi::__class_type_info*)&this->TypeInfo(),
                               (const abi::__class_type_info*)&to.TypeInfo(),
                               -1); 
#elif defined (_WIN32)
    obj3 = __RTDynamicCast(obj.Address(),
                           0,
                           (void*)&this->TypeInfo(),
                           (void*)&to.TypeInfo(),
                           0);
#endif
    return Object(to, obj3);
  }
  // fixme cross cast missing ?? internal cast possible ??

  // if the same At was passed return the object
  if ((Type)(*this) == to) return obj;

  // if everything fails return the dummy object
  return Object();
}

    
/*/-------------------------------------------------------------------------------
ROOT::Reflex::Object ROOT::Reflex::Class::Construct( const Type & signature, 
                                                     std::vector < Object > args, 
                                                     void * mem ) const {
//------------------------------------------------------------------------------- 
  static Type defSignature = Type::ByName("void (void)");
  Type signature2 = signature;
  
  Member constructor = Member();
  if ( !signature &&  fConstructors.size() > 1 ) 
    signature2 = defSignature; 
  
  for (size_t i = 0; i < fConstructors.size(); ++ i) {
    if ( !signature2 || fConstructors[i].TypeOf().Id() == signature2.Id()) {
      constructor = fConstructors[i];
      break;
    }
  }
  
  if ( constructor.TypeOf() ) {
    // no memory Address passed -> Allocate memory for class
    if ( mem == 0 ) mem = Allocate();
    Object obj = Object( TypeOf(), mem );
    constructor.Invoke( obj, args );
    return obj;
  }
  else {
    throw RuntimeError("No suitable constructor found");
  }
}
*/

    
//-------------------------------------------------------------------------------
ROOT::Reflex::Object ROOT::Reflex::Class::Construct( const Type & signature, 
                                                     std::vector < void * > args, 
                                                     void * mem ) const {
//------------------------------------------------------------------------------- 
  static Type defSignature = Type::ByName("void (void)");
  Type signature2 = signature;
  
  Member constructor = Member();
  if ( !signature &&  fConstructors.size() > 1 ) 
    signature2 = defSignature; 
  
  for (size_t i = 0; i < fConstructors.size(); ++ i) {
    if ( !signature2 || fConstructors[i].TypeOf().Id() == signature2.Id()) {
      constructor = fConstructors[i];
      break;
    }
  }
  
  if ( constructor.TypeOf() ) {
    // no memory Address passed -> Allocate memory for class
    if ( mem == 0 ) mem = Allocate();
    Object obj = Object( ThisType(), mem );
    constructor.Invoke( obj, args );
    return obj;
  }
        
  throw RuntimeError("No suitable constructor found");
}

    
//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::Destruct( void * instance, 
                                    bool dealloc ) const {
//-------------------------------------------------------------------------------
  if ( ! fDestructor.TypeOf() ) {
    // destructor for this class not yet revealed
    for ( size_t i = 0; i < ScopeBase::FunctionMemberSize(); ++i ) {
      Member fm = ScopeBase::FunctionMemberAt( i );
      // constructor found Set the cache pointer
      if ( fm.IsDestructor() ) {
        fDestructor = fm; 
        break;
      }
    }
  }
  if ( fDestructor.TypeOf()) {
    // we found a destructor -> Invoke it
    Object dummy = Object(Type(), instance);
    fDestructor.Invoke( dummy );
    // if deallocation of memory wanted 
    if ( dealloc ) { Deallocate( instance ); }
  }
  else {
    // this class has no destructor defined we call the operator delete on it
    ::operator delete(instance);
   }
}


//-------------------------------------------------------------------------------
struct DynType {
//-------------------------------------------------------------------------------
  virtual ~DynType() {}
};

    
//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::Class::DynamicType( const Object & obj ) const {
//-------------------------------------------------------------------------------
  // If no virtual_function_table return itself
  if ( IsVirtual() ) {
    // Avoid the case that the first word is a virtual_base_offset_table instead of
    // a virtual_function_table  
    long Offset = **(long**)obj.Address();
    if ( Offset == 0 ) return * this;
    else {
      Type dytype = Type::ByTypeInfo(typeid(*(DynType*)obj.Address()));
      if ( dytype && dytype.IsClass() ) return dytype;
      else                              return * this;
    }
  }
  else {
    return * this; 
  }
}


//-------------------------------------------------------------------------------
bool ROOT::Reflex::Class::HasBase( const Type & cl ) const {
//-------------------------------------------------------------------------------
  std::vector<Base> v = std::vector<Base>();
  return HasBase(cl, v);
}


//-------------------------------------------------------------------------------
bool ROOT::Reflex::Class::HasBase( const Type & cl,  
                                   std::vector< Base > & path ) const {
//-------------------------------------------------------------------------------
  for ( size_t i = 0; i < BaseSize(); ++i ) {
    // is the final BaseAt class one of the current class ?
    if ( BaseAt( i ).ToType().Id() == cl.Id() ) { 
      // remember the path to this class
      path.push_back( BaseAt( i )); 
      return true; 
    }
    // if searched BaseAt class is not direct BaseAt look in the bases of this one
    else if ( BaseAt( i ) && BaseAt( i ).BaseClass()->HasBase( cl, path )) {
      // if successfull remember path
      path.push_back( BaseAt( i )); 
      return true; 
    }
  }
  return false;
}


//-------------------------------------------------------------------------------
bool ROOT::Reflex::Class::IsComplete() const {
//-------------------------------------------------------------------------------
  if ( ! fCompleteType ) fCompleteType = IsComplete2(); 
  return fCompleteType;
}


//-------------------------------------------------------------------------------
bool ROOT::Reflex::Class::IsComplete2() const {
//-------------------------------------------------------------------------------
  for (size_t i = 0; i < BaseSize(); ++i) {
    Type baseType = BaseAt( i ).ToType();
    if ( ! baseType )  return false;
    if ( ! baseType.IsComplete()) return false;
  }
  return true;
}

    
//-------------------------------------------------------------------------------
size_t ROOT::Reflex::Class::AllBases() const {
//-------------------------------------------------------------------------------
  size_t aBases = 0;
  for ( size_t i = 0; i < BaseSize(); ++i ) {
    ++aBases;
    if ( BaseAt( i )) { 
      aBases += BaseAt( i ).BaseClass()->AllBases();
    }
  }
  return aBases;
}


//-------------------------------------------------------------------------------
bool ROOT::Reflex::Class::NewBases() const {
//-------------------------------------------------------------------------------
  if ( ! fCompleteType ) {
    size_t numBases = AllBases();
    if ( fAllBases != numBases ) {
      fCompleteType = IsComplete2();
      fAllBases = numBases;
      return true;
    }
  }
  return false;
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::UpdateMembers() const {
//-------------------------------------------------------------------------------
  std::vector < OffsetFunction > basePath = std::vector < OffsetFunction >();
  UpdateMembers2( fMembers, 
                  fDataMembers, 
                  fFunctionMembers,
                  fPathsToBase,
                  basePath );
}

    
//-------------------------------------------------------------------------------
const std::vector < ROOT::Reflex::OffsetFunction > & 
ROOT::Reflex::Class::PathToBase( const Scope & bas ) const {
//-------------------------------------------------------------------------------
  std::vector < OffsetFunction > * PathToBase = fPathsToBase[ bas.Id() ];
  if ( ! PathToBase ) {
    UpdateMembers();
    PathToBase = fPathsToBase[ bas.Id() ];
    /* fixme can Get rid of UpdateMembers() ?
    std::cerr << Reflex::Argv0() << ": WARNING: No path found from " 
              << this->Name() << " to " << bas.Name() << std::endl;
    if ( NewBases()) {
      std::cerr << Reflex::Argv0() << ": INFO: Not all base classes have resolved, "
                << "do Class::UpdateMembers() and try again " << std::endl; 
    }
    */
  }
  return * PathToBase;
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::UpdateMembers2( Members & members,
                                          Members & dataMembers,
                                          Members & functionMembers,
                                          PathsToBase & pathsToBase,
                                          std::vector < OffsetFunction > & basePath ) const {
//-------------------------------------------------------------------------------
  std::vector < Base >::const_iterator bIter;
  for ( bIter = fBases.begin(); bIter != fBases.end(); ++bIter ) {
    Type bType = bIter->ToType();
    basePath.push_back( bIter->OffsetFP());
    if ( bType ) {
    pathsToBase[ (dynamic_cast<const Class*>(bType.ToTypeBase()))->ThisScope().Id() ] = new std::vector < OffsetFunction >( basePath );
      size_t i = 0;
      for ( i = 0; i < bType.DataMemberSize(); ++i ) {
        Member dm = bType.DataMemberAt(i);
        if ( std::find( dataMembers.begin(),
                        dataMembers.end(),
                        dm ) == dataMembers.end()) {
          members.push_back( dm );
          dataMembers.push_back( dm );
        }
      }
      for ( i = 0; i < bType.FunctionMemberSize(); ++i ) {
        Member fm = bType.FunctionMemberAt( i );
        if ( std::find( functionMembers.begin(), 
                        functionMembers.end(),
                        fm ) == functionMembers.end()) {
          members.push_back( fm );
          functionMembers.push_back( fm );
        }
      }
      if ( bType ) (dynamic_cast<const Class*>(bType.ToTypeBase()))->UpdateMembers2( members,
                                                                                   dataMembers, 
                                                                                   functionMembers,
                                                                                   pathsToBase,
                                                                                   basePath );
    }
    basePath.pop_back();
  }
  /*
  // breath first search to find the "lowest" members in the hierarchy
  for ( bIter = fBases.begin(); bIter != fBases.end(); ++bIter ) {
  const Class * bClass = (*bIter)->toClass();
  if ( bClass ) {  bClass->UpdateMembers2( members,
  dataMembers, 
  functionMembers,
  pathsToBase,
  basePath );
  }
  }
  */
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::AddDataMember( const Member & dm ) const {
//-------------------------------------------------------------------------------
  ScopeBase::AddDataMember( dm );
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::AddDataMember( const char * nam,
                                         const Type & typ,
                                         size_t offs,
                                         unsigned int modifiers ) const {
//-------------------------------------------------------------------------------
  ScopeBase::AddDataMember( nam, typ, offs, modifiers );
}

    
//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::RemoveDataMember( const Member & dm ) const {
//-------------------------------------------------------------------------------
  ScopeBase::RemoveDataMember( dm );
}

    
//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::AddFunctionMember( const Member & fm ) const {
//-------------------------------------------------------------------------------
  ScopeBase::AddFunctionMember( fm );
  if ( fm.IsConstructor() )    fConstructors.push_back( fm );
  else if ( fm.IsDestructor() ) fDestructor = fm;
}

    
//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::AddFunctionMember( const char * nam,
                                             const Type & typ,
                                             StubFunction stubFP,
                                             void * stubCtx,
                                             const char * params,
                                             unsigned int modifiers ) const {
//-------------------------------------------------------------------------------
  ScopeBase::AddFunctionMember(nam,typ,stubFP,stubCtx,params,modifiers);
  if ( 0 !=  (modifiers & CONSTRUCTOR )) fConstructors.push_back(fFunctionMembers[fFunctionMembers.size()-1]);
  // setting the destructor is not needed because it is always provided when building the class
}


//-------------------------------------------------------------------------------
void ROOT::Reflex::Class::RemoveFunctionMember( const Member & fm ) const {
//-------------------------------------------------------------------------------
  ScopeBase::RemoveFunctionMember( fm );
}

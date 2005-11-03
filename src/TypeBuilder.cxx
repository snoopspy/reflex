// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#include "Reflex/Builder/TypeBuilder.h"

#include "Reflex/Type.h"
#include "Reflex/TypeName.h"

#include "Pointer.h"
#include "Function.h"
#include "Array.h"
#include "Enum.h"
#include "Typedef.h"
#include "Reflex/Tools.h"


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::TypeBuilder( const char * n, 
                                              unsigned int modifiers ) {
//-------------------------------------------------------------------------------
  Type ret = Type::ByName(n);
  if ( ret.Id() ) return Type(ret, modifiers);
  else {
    TypeName* tname = new TypeName(n, 0);
    std::string sname = Tools::GetScopeName(n);
    if ( ! Scope::ByName( sname ).Id() )  new ScopeName( sname.c_str(), 0 );
    return Type(tname, modifiers);
  }
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::ConstBuilder(const Type & t) {
//-------------------------------------------------------------------------------
  unsigned int mod = CONST;
  if ( t.IsVolatile() ) mod |= VOLATILE;
  return Type(t,mod);    
}

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::VolatileBuilder(const Type & t) {
//-------------------------------------------------------------------------------
  unsigned int mod = VOLATILE;
  if ( t.IsConst() )    mod |= CONST;
  return Type(t,mod);    
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::PointerBuilder( const Type & t,
                                                 const std::type_info & ti ) {
//-------------------------------------------------------------------------------
  Type ret = Type::ByName( Pointer::BuildTypeName(t));
  if ( ret ) return ret;
  else       return (new Pointer(t, ti))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::ReferenceBuilder(const Type & t) {
//-------------------------------------------------------------------------------
  unsigned int mod = REFERENCE;
  if ( t.IsConst() )    mod |= CONST;
  if ( t.IsVolatile() ) mod |= VOLATILE;
  return Type(t,mod);    
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::ArrayBuilder( const Type & t, 
                                               size_t n,
                                               const std::type_info & ti ) {
//-------------------------------------------------------------------------------
  Type ret = Type::ByName(Array::BuildTypeName(t,n));
  if ( ret ) return ret;
  else       return (new Array(t, n, ti))->TypeGet();
}

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::EnumTypeBuilder( const char * Name, 
                                                  const char * values,
                                                  const std::type_info & ti ) {
//-------------------------------------------------------------------------------
  Type ret = Type::ByName(Name);
  if ( ret ) return ret;
  Enum * e = new Enum(Name, ti);

  std::vector<std::string> valVec;
  Tools::StringSplit(valVec, values, ";");

  Type int_t = Type::ByName("int");
  for (std::vector<std::string>::const_iterator it = valVec.begin(); 
       it != valVec.end(); ++it ) {
    std::string iname, ivalue;
    Tools::StringSplitPair(iname, ivalue, *it, "=");
    long val = atol(ivalue.c_str());
    e->AddDataMember( iname.c_str(), int_t, val, 0);
  }  
  return e->TypeGet();
}

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::TypedefTypeBuilder(const char * Name, 
                                                    const Type & t) {
//-------------------------------------------------------------------------------
  Type ret = Type::ByName(Name);
  if ( ret ) return ret;
  else       return (new Typedef( Name , t ))->TypeGet();        
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder( const Type & r,
                                                      const std::vector<Type> & p,
                                                      const std::type_info & ti ) {
//-------------------------------------------------------------------------------
  return (new Function( r, p, ti))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r) {
//-------------------------------------------------------------------------------
  std::vector< Type > v;
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}
 

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7,
                                                     const Type & t8) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7, t8);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7,
                                                     const Type & t8,
                                                     const Type & t9) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}
 

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7,
                                                     const Type & t8,
                                                     const Type & t9,
                                                     const Type & t10) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7,
                                                     const Type & t8,
                                                     const Type & t9,
                                                     const Type & t10,
                                                     const Type & t11) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}
 

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7,
                                                     const Type & t8,
                                                     const Type & t9,
                                                     const Type & t10,
                                                     const Type & t11,
                                                     const Type & t12) {
//-------------------------------------------------------------------------------
  std::vector< Type > v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}
 

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7,
                                                     const Type & t8,
                                                     const Type & t9,
                                                     const Type & t10,
                                                     const Type & t11,
                                                     const Type & t12,
                                                     const Type & t13) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}


//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7,
                                                     const Type & t8,
                                                     const Type & t9,
                                                     const Type & t10,
                                                     const Type & t11,
                                                     const Type & t12,
                                                     const Type & t13,
                                                     const Type & t14) {
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}
 

//-------------------------------------------------------------------------------
ROOT::Reflex::Type ROOT::Reflex::FunctionTypeBuilder(const Type & r, 
                                                     const Type & t0, 
                                                     const Type & t1,
                                                     const Type & t2,
                                                     const Type & t3,
                                                     const Type & t4,
                                                     const Type & t5,
                                                     const Type & t6,
                                                     const Type & t7,
                                                     const Type & t8,
                                                     const Type & t9,
                                                     const Type & t10,
                                                     const Type & t11,
                                                     const Type & t12,
                                                     const Type & t13,
                                                     const Type & t14,
                                                     const Type & t15) { 
//-------------------------------------------------------------------------------
  std::vector<Type> v = Tools::makeVector(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
  Type ret = Type::ByName(Function::BuildTypeName(r,v));
  if ( ret ) return ret;
  else       return (new Function(r, v, typeid(UnknownType)))->TypeGet();
}




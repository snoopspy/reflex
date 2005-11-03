// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Reflex_Scope
#define ROOT_Reflex_Scope


// Include files
#include "Reflex/Kernel.h"
#include <string>
#include <typeinfo>

namespace ROOT {
  namespace Reflex {

    // forward declarations
    class Class;
    class Base;
    class InstantiatedTemplateClass;
    class Member;
    class Namespace;
    class PropertyList;
    class Type;
    class ScopeBase;
    class ScopeName;
    class TypeTemplate;
    class MemberTemplate;

    /**
     * @class Scope Scope.h Reflex/Scope.h
     * @author Stefan Roiser
     * @date 24/11/2003
     * @ingroup Ref
     */
    class Scope {

    public:

      /** constructor */
      Scope( const ScopeName * scopeName = 0 );


      /** copy constructor */
      Scope( const Scope & rh );


      /** destructor */
      ~Scope();


      /**
       * inequal operator 
       */
      bool operator != ( const Scope & rh ) const;


      /**
       * the bool operator will return true if the Scope is resolved (implemented)
       * @return true if Scope is implemented
       */
      operator bool () const;


      /** 
       * the operator Type will return a corresponding Type object to the ScopeNth if
       * applicable (i.e. if the Scope is also a Type e.g. Class, Union, Enum)
       */
      operator Type () const;


      /**
       * nthBase will return the nth BaseNth class information
       * @param  nth nth BaseNth class
       * @return pointer to BaseNth class information
       */
      Base BaseNth( size_t nth ) const;


      /**
       * BaseCount will return the number of BaseNth classes
       * @return number of BaseNth classes
       */
      size_t BaseCount() const;


      Base_Iterator Base_Begin() const;
      Base_Iterator Base_End() const;
      Reverse_Base_Iterator Base_Rbegin() const;
      Reverse_Base_Iterator Base_Rend() const;


      /**
       * ByName will return a pointer to a ScopeNth which is given as an argument
       * or 0 if none is found
       * @param  Name fully qualified Name of ScopeNth
       * @return pointer to ScopeNth or 0 if none is found
       */
      static Scope ByName( const std::string & name );


      /**
       * DataMemberNth will return the nth data MemberNth of the ScopeNth
       * @param  nth data MemberNth
       * @return pointer to data MemberNth
       */
      Member DataMemberNth( size_t nth ) const;


      /**
       * DataMemberNth will return the MemberNth with Name
       * @param  Name of data MemberNth
       * @return data MemberNth
       */
      Member DataMemberNth( const std::string & name ) const;


      /**
       * DataMemberCount will return the number of data members of this ScopeNth
       * @return number of data members
       */
      size_t DataMemberCount() const;


      Member_Iterator DataMember_Begin() const;
      Member_Iterator DataMember_End() const;
      Reverse_Member_Iterator DataMember_Rbegin() const;
      Reverse_Member_Iterator DataMember_Rend() const;


      /**
       * DeclaringScope will return a pointer to the ScopeNth of this one
       * @return pointer to declaring ScopeNth
       */
      Scope DeclaringScope() const;


      /**
       * FunctionMemberNth will return the nth function MemberNth of the ScopeNth
       * @param  nth function MemberNth
       * @return pointer to function MemberNth
       */
      Member FunctionMemberNth( size_t nth ) const;


      /**
       * FunctionMemberNth will return the MemberNth with the Name, 
       * optionally the signature of the function may be given
       * @param  Name of function MemberNth
       * @param  signature of the MemberNth function 
       * @return function MemberNth
       */
      // this overloading is unfortunate but I can't include Type.h here
      Member FunctionMemberNth( const std::string & name ) const;
      Member FunctionMemberNth( const std::string & name,
                                const Type & signature ) const;


      /**
       * FunctionMemberCount will return the number of function members of
       * this ScopeNth
       * @return number of function members
       */
      size_t FunctionMemberCount() const;


      Member_Iterator FunctionMember_Begin() const;
      Member_Iterator FunctionMember_End() const;
      Reverse_Member_Iterator FunctionMember_Rbegin() const;
      Reverse_Member_Iterator FunctionMember_Rend() const;


      /**
       * Id returns a unique identifier of the TypeNth in the system
       * @return unique identifier
       */
      void * Id() const;


      /** 
       * IsClass returns true if the TypeNth represents a Class
       * @return true if TypeNth represents a Class
       */
      bool IsClass() const;


      /** 
       * IsEnum returns true if the TypeNth represents a Enum
       * @return true if TypeNth represents a Enum
       */
      bool IsEnum() const;


      /** 
       * IsNamespace returns true if the TypeNth represents a Namespace
       * @return true if TypeNth represents a Namespace
       */
      bool IsNamespace() const;


      /** 
       * IsTemplateInstance returns true if the TypeNth represents a 
       * ClassTemplateInstance
       * @return true if TypeNth represents a InstantiatedTemplateClass
       */
      bool IsTemplateInstance() const;


      /**
       * IsTopScope will return true if the current ScopeNth is the top
       * (Empty) namespace
       * @return true if current sope is top namespace
       */
      bool IsTopScope() const;

 
      /** 
       * IsUnion returns true if the TypeNth represents a Union
       * @return true if TypeNth represents a 
       */
      bool IsUnion() const;


      /**
       * MemberNth will return the first MemberNth with a given Name
       * @param  MemberNth Name
       * @return pointer to MemberNth
       */
      // this overloading is unfortunate but I can't include Type.h here
      Member MemberNth( const std::string & name ) const;
      Member MemberNth( const std::string & name,
                        const Type & signature ) const;


      /**
       * MemberNth will return the nth MemberNth of the ScopeNth
       * @param  nth MemberNth
       * @return pointer to nth MemberNth
       */
      Member MemberNth( size_t nth ) const;


      /**
       * MemberCount will return the number of members
       * @return number of members
       */
      size_t MemberCount() const;

      
      Member_Iterator Member_Begin() const;
      Member_Iterator Member_End() const;
      Reverse_Member_Iterator Member_Rbegin() const;
      Reverse_Member_Iterator Member_Rend() const;
      

      /** 
       * MemberTemplateNth will return the nth MemberNth template of this ScopeNth
       * @param nth MemberNth template
       * @return nth MemberNth template
       */
      MemberTemplate MemberTemplateNth( size_t nth ) const;


      /** 
       * MemberTemplateCount will return the number of MemberNth templates in this socpe
       * @return number of defined MemberNth templates
       */
      size_t MemberTemplateCount() const;


      MemberTemplate_Iterator MemberTemplate_Begin() const;
      MemberTemplate_Iterator MemberTemplate_End() const;
      Reverse_MemberTemplate_Iterator MemberTemplate_Rbegin() const;
      Reverse_MemberTemplate_Iterator MemberTemplate_Rend() const;


      /**
       * Name will return a string representation of Name of the ScopeNth 
       * @return string representation of ScopeNth
       */
      std::string Name( unsigned int mod = 0 ) const;


      /**
        * Name_c_str returns a char* pointer to the unqualified TypeNth Name
       * @ return c string to unqualified TypeNth Name
       */
      const char * Name_c_str() const;
      
      
      /**
       * PropertyListGet will return a pointer to the PropertyNth list attached
       * to this item
       * @return pointer to PropertyNth list
       */
      PropertyList PropertyListGet() const;

      
      /**
       * findAll will return a vector of all scopes currently available
       * resolvable scopes
       * @param  nth ScopeNth defined in the system
       * @return vector of all available scopes
       */
      static Scope ScopeNth( size_t nth );


      /**
       * ScopeCount will return the number of currently defined scopes
       * (resolved and unresolved ones)
       * @return number of currently defined scopes
       */
      static size_t ScopeCount();

      
      static Scope_Iterator Scope_Begin();
      static Scope_Iterator Scope_End();
      static Reverse_Scope_Iterator Scope_Rbegin();
      static Reverse_Scope_Iterator Scope_Rend();


      /**
       * ScopeType will return which kind of ScopeNth is represented
       * @return TypeNth of ScopeNth
       */
      TYPE ScopeType() const;


      /**
       * ScopeTypeAsString will return the string representation of the enum
       * representing the current Scope (e.g. "CLASS")
       * @return string representation of enum for Scope
       */
      std::string ScopeTypeAsString() const;


      /**
       * SubScopeNth will return a pointer to a sub-scopes
       * @param  nth sub-ScopeNth
       * @return pointer to nth sub-ScopeNth
       */
      Scope SubScopeNth( size_t nth ) const;


      /**
       * ScopeCount will return the number of sub-scopes
       * @return number of sub-scopes
       */
      size_t SubScopeCount() const;


      Scope_Iterator SubScope_Begin() const;
      Scope_Iterator SubScope_End() const;
      Reverse_Scope_Iterator SubScope_Rbegin() const;
      Reverse_Scope_Iterator SubScope_Rend() const;


      /**
       * nthType will return a pointer to the nth sub-TypeNth
       * @param  nth sub-TypeNth
       * @return pointer to nth sub-TypeNth
       */
      Type SubTypeNth( size_t nth ) const;


      /**
       * TypeCount will returnt he number of sub-types
       * @return number of sub-types
       */
      size_t SubTypeCount() const;


      Type_Iterator SubType_Begin() const;
      Type_Iterator SubType_End() const;
      Reverse_Type_Iterator SubType_Rbegin() const;
      Reverse_Type_Iterator SubType_Rend() const;


      /**
       * TemplateArgumentNth will return a pointer to the nth template argument
       * @param  nth nth template argument
       * @return pointer to nth template argument
       */
      Type TemplateArgumentNth( size_t nth ) const;


      /**
       * templateArgCount will return the number of template arguments
       * @return number of template arguments
       */
      size_t TemplateArgumentCount() const;


      Type_Iterator TemplateArgument_Begin() const;
      Type_Iterator TemplateArgument_End() const;
      Reverse_Type_Iterator TemplateArgument_Rbegin() const;
      Reverse_Type_Iterator TemplateArgument_Rend() const;


      /**
       * TypeTemplateNth returns the corresponding TypeTemplate if any
       * @return corresponding TypeTemplate
       */
      TypeTemplate TemplateFamily() const;


      /** 
       * TypeTemplateNth will return the nth TypeNth template of this ScopeNth
       * @param nth TypeNth template
       * @return nth TypeNth template
       */
      TypeTemplate TypeTemplateNth( size_t nth ) const;


      /** 
       * TypeTemplateCount will return the number of TypeNth templates in this socpe
       * @return number of defined TypeNth templates
       */
      size_t TypeTemplateCount() const;


      TypeTemplate_Iterator TypeTemplate_Begin() const;
      TypeTemplate_Iterator TypeTemplate_End() const;
      Reverse_TypeTemplate_Iterator TypeTemplate_Rbegin() const;
      Reverse_TypeTemplate_Iterator TypeTemplate_Rend() const;

    public:

      /** */
      const ScopeBase * ScopeBaseNth() const;
 
      /**
       * AddDataMember will add the information about a data MemberNth
       * @param dm pointer to data MemberNth
       */
      void AddDataMember( const Member & dm ) const;
      void AddDataMember( const char * name,
                          const Type & type,
                          size_t offset,
                          unsigned int modifiers = 0 ) const;


      /**
       * AddFunctionMember will add the information about a function MemberNth
       * @param fm pointer to function MemberNth
       */
      void AddFunctionMember( const Member & fm ) const;
      void AddFunctionMember( const char * name,
                              const Type & type,
                              StubFunction stubFP,
                              void * stubCtx = 0,
                              const char * params = 0,
                              unsigned int modifiers = 0 ) const;


      /**
       * AddSubScope will add a sub-ScopeNth to this one
       * @param sc pointer to Scope
       */
      void AddSubScope( const Scope & sc ) const;
      void AddSubScope( const char * scope,
                        TYPE scopeType = NAMESPACE ) const;


      /**
       * AddSubType will add a sub-TypeNth to this ScopeNth
       * @param sc pointer to Type
       */
      void AddSubType( const Type & ty ) const;
      void AddSubType( const char * type,
                       size_t size,
                       TYPE typeType,
                       const std::type_info & typeInfo,
                       unsigned int modifiers = 0 ) const;


      /**
       * RemoveDataMember will remove the information about a data MemberNth
       * @param dm pointer to data MemberNth
       */
      void RemoveDataMember( const Member & dm ) const;


      /**
       * RemoveFunctionMember will remove the information about a function MemberNth
       * @param fm pointer to function MemberNth
       */
      void RemoveFunctionMember( const Member & fm ) const;


      /**
       * RemoveSubScope will remove a sub-ScopeNth to this one
       * @param sc pointer to Scope
       */
      void RemoveSubScope( const Scope & sc ) const;


      /**
       * RemoveSubType will remove a sub-TypeNth to this ScopeNth
       * @param sc pointer to Type
       */
      void RemoveSubType( const Type & ty ) const;     


      void AddMemberTemplate( const MemberTemplate & mt ) const ;


      void AddTypeTemplate( const TypeTemplate & mt ) const ;


      void RemoveMemberTemplate( const MemberTemplate & mt ) const;


      void RemoveTypeTemplate( const TypeTemplate & tt ) const;

    public:
      
      /**
       * @label __NIRVANA__
       * @link association 
       */
      static Scope __NIRVANA__;

    private:

      /**
       * pointer to the resolved Scope
       * @label ScopeNth BaseNth
       * @link aggregation
       * @supplierCardinality 1
       * @clientCardinality 1..*
       */
      const ScopeName * fScopeName;

    }; // class Scope

    bool operator < ( const Scope & lh, 
                      const Scope & rh); 

    bool operator == ( const Scope & lh,
                       const Scope & rh );

  } // namespace Reflex
} // namespace ROOT

#include "Reflex/ScopeBase.h"
#include "Reflex/ScopeName.h"
#include "Reflex/PropertyList.h"

//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Scope::operator != ( const Scope & rh ) const {
//-------------------------------------------------------------------------------
  return ( fScopeName != rh.fScopeName );
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::operator < ( const Scope & lh, 
                                       const Scope & rh ) {
//-------------------------------------------------------------------------------
  return const_cast<Scope*>(&lh)->Id() < const_cast<Scope*>(&rh)->Id();
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::operator == ( const Scope & lh,
                                        const Scope & rh ) {
//-------------------------------------------------------------------------------
  return const_cast<Scope*>(&lh)->Id() == const_cast<Scope*>(&rh)->Id();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope::Scope( const ScopeName * scopeName ) 
//-------------------------------------------------------------------------------
  : fScopeName( scopeName ) {}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope::Scope( const Scope & rh ) 
//-------------------------------------------------------------------------------
  : fScopeName( rh.fScopeName ) {}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope::~Scope() {
//-------------------------------------------------------------------------------
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope::operator bool () const {
//-------------------------------------------------------------------------------
  if ( this->fScopeName && this->fScopeName->fScopeBase ) return true;
  //throw RuntimeError("Scope is not implemented");
  return false;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Base_Iterator ROOT::Reflex::Scope::Base_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->Base_Begin();
  return Base_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Base_Iterator ROOT::Reflex::Scope::Base_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->Base_End();
  return Base_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Base_Iterator ROOT::Reflex::Scope::Base_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->Base_Rbegin();
  return Reverse_Base_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Base_Iterator ROOT::Reflex::Scope::Base_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->Base_Rend();
  return Reverse_Base_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::Scope::DataMember_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->DataMember_Begin();
  return Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::Scope::DataMember_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->DataMember_End();
  return Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::Scope::DataMember_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->DataMember_Rbegin();
  return Reverse_Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::Scope::DataMember_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->DataMember_Rend();
  return Reverse_Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope ROOT::Reflex::Scope::DeclaringScope() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->DeclaringScope(); 
  return Scope();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::Scope::FunctionMember_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->FunctionMember_Begin();
  return Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::Scope::FunctionMember_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->FunctionMember_End();
  return Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::Scope::FunctionMember_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->FunctionMember_Rbegin();
  return Reverse_Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::Scope::FunctionMember_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->FunctionMember_Rend();
  return Reverse_Member_Iterator();
}


//-------------------------------------------------------------------------------
inline void * ROOT::Reflex::Scope::Id() const {
//-------------------------------------------------------------------------------
  return (void*)fScopeName;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Scope::IsClass() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->IsClass(); 
  return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Scope::IsEnum() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->IsEnum(); 
  return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Scope::IsNamespace() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->IsNamespace(); 
  return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Scope::IsTemplateInstance() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->IsTemplateInstance(); 
  return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Scope::IsTopScope() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->IsTopScope(); 
  return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Scope::IsUnion() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->IsUnion(); 
  return false;
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::Scope::MemberCount() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->MemberCount(); 
  return 0;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::Scope::Member_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->Member_Begin();
  return Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::Scope::Member_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->Member_End();
  return Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::Scope::Member_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->Member_Rbegin();
  return Reverse_Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::Scope::Member_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->Member_Rend();
  return Reverse_Member_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::MemberTemplate_Iterator ROOT::Reflex::Scope::MemberTemplate_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->MemberTemplate_Begin();
  return MemberTemplate_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::MemberTemplate_Iterator ROOT::Reflex::Scope::MemberTemplate_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->MemberTemplate_End();
  return MemberTemplate_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_MemberTemplate_Iterator ROOT::Reflex::Scope::MemberTemplate_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->MemberTemplate_Rbegin();
  return Reverse_MemberTemplate_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_MemberTemplate_Iterator ROOT::Reflex::Scope::MemberTemplate_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->MemberTemplate_Rend();
  return Reverse_MemberTemplate_Iterator();
}


//-------------------------------------------------------------------------------
inline const char * ROOT::Reflex::Scope::Name_c_str() const {
//-------------------------------------------------------------------------------
  if ( fScopeName ) return fScopeName->Name_c_str();
  return "";
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::PropertyList ROOT::Reflex::Scope::PropertyListGet() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->PropertyListGet();
  return PropertyList();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::TYPE ROOT::Reflex::Scope::ScopeType() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->ScopeType(); 
  return UNRESOLVED;
}


//-------------------------------------------------------------------------------
inline std::string ROOT::Reflex::Scope::ScopeTypeAsString() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->ScopeTypeAsString(); 
  return "UNRESOLVED";
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope_Iterator ROOT::Reflex::Scope::Scope_Begin() {
//-------------------------------------------------------------------------------
  return ScopeName::Scope_Begin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope_Iterator ROOT::Reflex::Scope::Scope_End() {
//-------------------------------------------------------------------------------
  return ScopeName::Scope_End();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Scope_Iterator ROOT::Reflex::Scope::Scope_Rbegin() {
//-------------------------------------------------------------------------------
  return ScopeName::Scope_Rbegin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Scope_Iterator ROOT::Reflex::Scope::Scope_Rend() {
//-------------------------------------------------------------------------------
  return ScopeName::Scope_Rend();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope ROOT::Reflex::Scope::SubScopeNth( size_t nth ) const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubScopeNth( nth ); 
  return Scope();
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::Scope::SubScopeCount() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubScopeCount(); 
  return 0;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope_Iterator ROOT::Reflex::Scope::SubScope_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubScope_Begin();
  return Scope_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope_Iterator ROOT::Reflex::Scope::SubScope_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubScope_End();
  return Scope_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Scope_Iterator ROOT::Reflex::Scope::SubScope_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubScope_Rbegin();
  return Reverse_Scope_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Scope_Iterator ROOT::Reflex::Scope::SubScope_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubScope_Rend();
  return Reverse_Scope_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::Scope::SubType_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubType_Begin();
  return Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::Scope::SubType_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubType_End();
  return Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::Scope::SubType_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubType_Rbegin();
  return Reverse_Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::Scope::SubType_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->SubType_Rend();
  return Reverse_Type_Iterator();
}


//-------------------------------------------------------------------------------
inline const ROOT::Reflex::ScopeBase * ROOT::Reflex::Scope::ScopeBaseNth() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase;
  return 0;
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::Scope::TemplateArgumentCount() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TemplateArgumentCount();
  return 0;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::Scope::TemplateArgument_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TemplateArgument_Begin();
  return Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::Scope::TemplateArgument_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TemplateArgument_End();
  return Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::Scope::TemplateArgument_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TemplateArgument_Rbegin();
  return Reverse_Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::Scope::TemplateArgument_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TemplateArgument_Rend();
  return Reverse_Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::TypeTemplate_Iterator ROOT::Reflex::Scope::TypeTemplate_Begin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TypeTemplate_Begin();
  return TypeTemplate_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::TypeTemplate_Iterator ROOT::Reflex::Scope::TypeTemplate_End() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TypeTemplate_End();
  return TypeTemplate_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_TypeTemplate_Iterator ROOT::Reflex::Scope::TypeTemplate_Rbegin() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TypeTemplate_Rbegin();
  return Reverse_TypeTemplate_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_TypeTemplate_Iterator ROOT::Reflex::Scope::TypeTemplate_Rend() const {
//-------------------------------------------------------------------------------
  if ( * this ) return fScopeName->fScopeBase->TypeTemplate_Rend();
  return Reverse_TypeTemplate_Iterator();
}


//-------------------------------------------------------------------------------
inline void ROOT::Reflex::Scope::AddSubScope( const Scope & sc ) const {
//-------------------------------------------------------------------------------
  if ( * this) fScopeName->fScopeBase->AddSubScope( sc );
}


//-------------------------------------------------------------------------------
inline void ROOT::Reflex::Scope::AddSubScope( const char * scope,
                                              TYPE scopeType ) const {
//-------------------------------------------------------------------------------
  if ( * this ) fScopeName->fScopeBase->AddSubScope( scope, scopeType );
}


//-------------------------------------------------------------------------------
inline void ROOT::Reflex::Scope::RemoveSubScope( const Scope & sc ) const {
//-------------------------------------------------------------------------------
  if ( * this) fScopeName->fScopeBase->RemoveSubScope( sc );
}



#endif // ROOT_Reflex_Scope

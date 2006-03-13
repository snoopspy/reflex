// @(#)root/reflex:$Name:  $:$Id: ScopeBase.h,v 1.5 2006/03/06 12:51:46 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2006, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Reflex_ScopeBase
#define ROOT_Reflex_ScopeBase

// Include files
#include "Reflex/Kernel.h"

#include "Reflex/Scope.h"
#include "Reflex/PropertyList.h"
#include <vector>

namespace ROOT {
   namespace Reflex {

      // forward declarations
      class Scope;
      class ScopeName;
      class Namespace;
      class Class;
      class Member;
      class TypeTemplate;
      class MemberTemplate;
      class Type;

      /**
       * @class ScopeBase ScopeBase.h Reflex/ScopeBase.h
       * @author Stefan Roiser
       * @date 24/11/2003
       * @ingroup Ref
       */
      class RFLX_API ScopeBase {

      public:

         /** constructor within a At*/
         ScopeBase( const char * scope, 
                    TYPE scopeType );


         /** destructor */
         virtual ~ScopeBase();


         /** 
          * operator Scope will return the corresponding Scope object
          * @return Scope corresponding to this ScopeBase
          */
         operator Scope () const;


         /** 
          * the operator Type will return a corresponding Type object to the At if
          * applicable (i.e. if the Scope is also a Type e.g. Class, Union, Enum)
          */
         operator Type () const;


         /**
          * nthBase will return the nth BaseAt class information
          * @param  nth nth BaseAt class
          * @return pointer to BaseAt class information
          */
         virtual Base BaseAt( size_t nth ) const;


         /**
          * BaseSize will return the number of BaseAt classes
          * @return number of BaseAt classes
          */
         virtual size_t BaseSize() const;


         virtual Base_Iterator Base_Begin() const;
         virtual Base_Iterator Base_End() const;
         virtual Reverse_Base_Iterator Base_RBegin() const;
         virtual Reverse_Base_Iterator Base_REnd() const;


         /**
          * nthDataMember will return the nth data MemberAt of the At
          * @param  nth data MemberAt
          * @return pointer to data MemberAt
          */
         Member DataMemberAt( size_t nth ) const;


         /**
          * DataMemberByName will return the MemberAt with Name
          * @param  Name of data MemberAt
          * @return data MemberAt
          */
         Member DataMemberByName( const std::string & nam ) const;


         /**
          * DataMemberSize will return the number of data members of this At
          * @return number of data members
          */
         size_t DataMemberSize() const;

      
         Member_Iterator DataMember_Begin() const;
         Member_Iterator DataMember_End() const;
         Reverse_Member_Iterator DataMember_RBegin() const;
         Reverse_Member_Iterator DataMember_REnd() const;


         /**
          * DeclaringScope will return a pointer to the At of this one
          * @return pointer to declaring At
          */
         Scope DeclaringScope() const;


         /**
          * nthFunctionMember will return the nth function MemberAt of the At
          * @param  nth function MemberAt
          * @return pointer to function MemberAt
          */
         Member FunctionMemberAt( size_t nth ) const;

 
         /**
          * FunctionMemberByName will return the MemberAt with the Name, 
          * optionally the signature of the function may be given
          * @param  Name of function MemberAt
          * @param  signature of the MemberAt function 
          * @return function MemberAt
          */
         Member FunctionMemberByName( const std::string & name,
                                      const Type & signature ) const;


         /**
          * FunctionMemberSize will return the number of function members of
          * this At
          * @return number of function members
          */
         size_t FunctionMemberSize() const;


         Member_Iterator FunctionMember_Begin() const;
         Member_Iterator FunctionMember_End() const;
         Reverse_Member_Iterator FunctionMember_RBegin() const;
         Reverse_Member_Iterator FunctionMember_REnd() const;


         /** 
          * IsClass returns true if the At represents a Class
          * @return true if At represents a Class
          */
         bool IsClass() const;

 
         /** 
          * IsEnum returns true if the At represents a Enum
          * @return true if At represents a Enum
          */
         bool IsEnum() const;

      
         /** 
          * IsNamespace returns true if the At represents a Namespace
          * @return true if At represents a Namespace
          */
         bool IsNamespace() const;


         /** 
          * IsTemplateInstance returns true if the At represents a 
          * ClassTemplateInstance
          * @return true if At represents a InstantiatedTemplateClass
          */
         bool IsTemplateInstance() const;


         /**
          * IsTopScope will return true if the current At is the top
          * (Empty) namespace
          * @return true if current sope is top namespace
          */
         bool IsTopScope() const;


         /** 
          * IsUnion returns true if the At represents a Union
          * @return true if At represents a 
          */
         bool IsUnion() const;


         /**
          * MemberByName will return the first MemberAt with a given Name
          * @param Name  MemberAt Name
          * @return pointer to MemberAt
          */
         Member MemberByName( const std::string & name,
                              const Type & signature ) const;


         /**
          * MemberAt will return the nth MemberAt of the At
          * @param  nth MemberAt
          * @return pointer to nth MemberAt
          */
         Member MemberAt( size_t nth ) const;


         Member_Iterator Member_Begin() const;
         Member_Iterator Member_End() const;
         Reverse_Member_Iterator Member_RBegin() const;
         Reverse_Member_Iterator Member_REnd() const;


         /**
          * MemberSize will return the number of members
          * @return number of members
          */
         size_t MemberSize() const;


         /** 
          * MemberTemplateAt will return the nth MemberAt template of this At
          * @param nth MemberAt template
          * @return nth MemberAt template
          */
         MemberTemplate MemberTemplateAt( size_t nth ) const;


         /** 
          * MemberTemplateSize will return the number of MemberAt templates in this socpe
          * @return number of defined MemberAt templates
          */
         size_t MemberTemplateSize() const;


         MemberTemplate_Iterator MemberTemplate_Begin() const;
         MemberTemplate_Iterator MemberTemplate_End() const;
         Reverse_MemberTemplate_Iterator MemberTemplate_RBegin() const;
         Reverse_MemberTemplate_Iterator MemberTemplate_REnd() const;


         /**
          * Name will return the Name of the At
          * @return Name of At
          */
         virtual std::string Name( unsigned int mod = 0 ) const;


         /**
          * Properties will return a pointer to the PropertyNth list attached
          * to this item
          * @return pointer to PropertyNth list
          */
         virtual PropertyList Properties() const;

      
         /** 
          * At will return the At Object of this ScopeBase
          * @return corresponding Scope
          */
         Scope ThisScope() const;

      
         /**
          * ScopeType will return which kind of At is represented
          * @return At of At
          */
         TYPE ScopeType() const;


         /**
          * ScopeTypeAsString will return the string representation of the enum
          * representing the current Scope (e.g. "CLASS")
          * @return string representation of enum for Scope
          */
         std::string ScopeTypeAsString() const;


         /**
          * SubScopeAt will return a pointer to a sub-scopes
          * @param  nth sub-At
          * @return pointer to nth sub-At
          */
         Scope SubScopeAt( size_t nth ) const;


         /**
          * ScopeSize will return the number of sub-scopes
          * @return number of sub-scopes
          */
         size_t SubScopeSize() const;


         Scope_Iterator SubScope_Begin() const;
         Scope_Iterator SubScope_End() const;
         Reverse_Scope_Iterator SubScope_RBegin() const;
         Reverse_Scope_Iterator SubScope_REnd() const;


         /**
          * At will return a pointer to the nth sub-At
          * @param  nth sub-At
          * @return pointer to nth sub-At
          */
         Type SubTypeAt( size_t nth ) const;


         /**
          * TypeSize will returnt he number of sub-types
          * @return number of sub-types
          */
         size_t SubTypeSize() const;


         Type_Iterator SubType_Begin() const;
         Type_Iterator SubType_End() const;
         Reverse_Type_Iterator SubType_RBegin() const;
         Reverse_Type_Iterator SubType_REnd() const;


         /**
          * TemplateArgumentAt will return a pointer to the nth template argument
          * @param  nth nth template argument
          * @return pointer to nth template argument
          */
         virtual Type TemplateArgumentAt( size_t nth ) const;


         /**
          * templateArgSize will return the number of template arguments
          * @return number of template arguments
          */
         virtual size_t TemplateArgumentSize() const;


         virtual Type_Iterator TemplateArgument_Begin() const;
         virtual Type_Iterator TemplateArgument_End() const;
         virtual Reverse_Type_Iterator TemplateArgument_RBegin() const;
         virtual Reverse_Type_Iterator TemplateArgument_REnd() const;


         /**
          * SubTypeTemplateAt returns the corresponding TypeTemplate if any
          * @return corresponding TypeTemplate
          */
         virtual TypeTemplate TemplateFamily() const;


         /** 
          * SubTypeTemplateAt will return the nth At template of this At
          * @param nth At template
          * @return nth At template
          */
         TypeTemplate SubTypeTemplateAt( size_t nth ) const;


         /** 
          * SubTypeTemplateSize will return the number of At templates in this socpe
          * @return number of defined At templates
          */
         size_t SubTypeTemplateSize() const;


         TypeTemplate_Iterator SubTypeTemplate_Begin() const;
         TypeTemplate_Iterator SubTypeTemplate_End() const;
         Reverse_TypeTemplate_Iterator SubTypeTemplate_RBegin() const;
         Reverse_TypeTemplate_Iterator SubTypeTemplate_REnd() const;

      protected:

         /** protected constructor for initialisation of the global namespace */
         ScopeBase();

      public:

         /**
          * AddDataMember will add the information about a data MemberAt
          * @param dm pointer to data MemberAt
          */
         virtual void AddDataMember( const Member & dm ) const;
         virtual void AddDataMember( const char * name,
                                     const Type & type,
                                     size_t offset,
                                     unsigned int modifiers = 0 ) const;


         /**
          * AddFunctionMember will add the information about a function MemberAt
          * @param fm pointer to function MemberAt
          */
         virtual void AddFunctionMember( const Member & fm ) const;
         virtual void AddFunctionMember( const char * name,
                                         const Type & type,
                                         StubFunction stubFP,
                                         void * stubCtx = 0,
                                         const char * params = 0,
                                         unsigned int modifiers = 0 ) const;


         virtual void AddMemberTemplate( const MemberTemplate & mt ) const ;


         /**
          * AddSubScope will add a sub-At to this one
          * @param sc pointer to Scope
          */
         virtual void AddSubScope( const Scope & sc ) const;
         virtual void AddSubScope( const char * scope,
                                   TYPE scopeType ) const;


         /**
          * AddSubType will add a sub-At to this At
          * @param sc pointer to Type
          */
         virtual void AddSubType( const Type & ty ) const;
         virtual void AddSubType( const char * type,
                                  size_t size,
                                  TYPE typeType,
                                  const std::type_info & ti,
                                  unsigned int modifiers = 0 ) const;


         void AddSubTypeTemplate( const TypeTemplate & tt ) const;


         /**
          * RemoveDataMember will remove the information about a data MemberAt
          * @param dm pointer to data MemberAt
          */
         virtual void RemoveDataMember( const Member & dm ) const;


         /**
          * RemoveFunctionMember will remove the information about a function MemberAt
          * @param fm pointer to function MemberAt
          */
         virtual void RemoveFunctionMember( const Member & fm ) const;


         virtual void RemoveMemberTemplate( const MemberTemplate & mt ) const;


         /**
          * RemoveSubScope will remove a sub-At to this one
          * @param sc pointer to Scope
          */
         virtual void RemoveSubScope( const Scope & sc ) const;


         /**
          * RemoveSubType will remove a sub-At to this At
          * @param sc pointer to Type
          */
         virtual void RemoveSubType( const Type & ty ) const;


         virtual void RemoveSubTypeTemplate( const TypeTemplate & tt ) const;

      protected:
      
         /** container for all members of the At */
         typedef std::vector < Member > Members;

         /**
          * pointers to members
          * @label At members
          * @link aggregationByValue
          * @supplierCardinality 0..*
          * @clientCardinality 1
          */
         mutable
            std::vector< Member > fMembers;

         /**
          * container with pointers to all data members in this At
          * @label At datamembers
          * @link aggregationByValue
          * @clientCardinality 1
          * @supplierCardinality 0..*
          */
         mutable
            std::vector< Member > fDataMembers;

         /**
          * container with pointers to all function members in this At
          * @label At functionmembers
          * @link aggregationByValue
          * @supplierCardinality 0..*
          * @clientCardinality 1
          */
         mutable
            std::vector< Member > fFunctionMembers;

      private:

         /**
          * pointer to the At Name
          * @label At Name
          * @link aggregation
          * @clientCardinality 1
          * @supplierCardinality 1
          */
         ScopeName * fScopeName;


         /**
          * At of At
          * @link aggregationByValue
          * @label At At
          * @clientCardinality 1
          * @supplierCardinality 1
          */
         TYPE fScopeType;


         /**
          * pointer to declaring At
          * @label declaring At
          * @link aggregationByValue
          * @clientCardinality 1
          * @supplierCardinality 1
          */
         Scope fDeclaringScope;


         /**
          * pointers to sub-scopes
          * @label sub scopes
          * @link aggregationByValue
          * @supplierCardinality 0..*
          * @clientCardinality 1
          */
         mutable
            std::vector< Scope > fSubScopes;
 

         /**
          * pointer to types
          * @label At types
          * @link aggregationByValue
          * @supplierCardinality 0..*
          * @clientCardinality 1
          */
         mutable
            std::vector < Type > fSubTypes;


         /**
          * container for At templates defined in this At
          * @label At templates
          * @link aggregationByValue
          * @supplierCardinality 0..*
          * @clientCardinality 1
          */
         mutable
            std::vector < TypeTemplate > fTypeTemplates;
 
 
         /**
          * container for At templates defined in this At
          * @label At templates
          * @link aggregationByValue
          * @supplierCardinality 0..*
          * @clientCardinality 1
          */
         mutable
            std::vector < MemberTemplate > fMemberTemplates;


         /**
          * pointer to the PropertyNth list
          * @label propertylist
          * @link aggregationByValue
          * @clientCardinality 1
          * @supplierCardinality 1
          */
         PropertyList fPropertyList;


         /** 
          * The position where the unscoped Name starts in the scopename
          */
         size_t fBasePosition;

      }; // class ScopeBase
   } //namespace Reflex
} //namespace ROOT


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::ScopeBase::BaseSize() const {
//-------------------------------------------------------------------------------
   return 0;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Base_Iterator ROOT::Reflex::ScopeBase::Base_Begin() const {
//-------------------------------------------------------------------------------
   return Base_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Base_Iterator ROOT::Reflex::ScopeBase::Base_End() const {
//-------------------------------------------------------------------------------
   return Base_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Base_Iterator ROOT::Reflex::ScopeBase::Base_RBegin() const {
//-------------------------------------------------------------------------------
   return Reverse_Base_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Base_Iterator ROOT::Reflex::ScopeBase::Base_REnd() const {
//-------------------------------------------------------------------------------
   return Reverse_Base_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope ROOT::Reflex::ScopeBase::DeclaringScope() const {
//-------------------------------------------------------------------------------
   return fDeclaringScope;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::ScopeBase::DataMember_Begin() const {
//-------------------------------------------------------------------------------
   return fDataMembers.begin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::ScopeBase::DataMember_End() const {
//-------------------------------------------------------------------------------
   return fDataMembers.end();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::ScopeBase::DataMember_RBegin() const {
//-------------------------------------------------------------------------------
   return fDataMembers.rbegin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::ScopeBase::DataMember_REnd() const {
//-------------------------------------------------------------------------------
   return fDataMembers.rend();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::ScopeBase::FunctionMember_Begin() const {
//-------------------------------------------------------------------------------
   return fFunctionMembers.begin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::ScopeBase::FunctionMember_End() const {
//-------------------------------------------------------------------------------
   return fFunctionMembers.end();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::ScopeBase::FunctionMember_RBegin() const {
//-------------------------------------------------------------------------------
   return fFunctionMembers.rbegin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::ScopeBase::FunctionMember_REnd() const {
//-------------------------------------------------------------------------------
   return fFunctionMembers.rend();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::ScopeBase::Member_Begin() const {
//-------------------------------------------------------------------------------
   return fMembers.begin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member_Iterator ROOT::Reflex::ScopeBase::Member_End() const {
//-------------------------------------------------------------------------------
   return fMembers.end();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::ScopeBase::Member_RBegin() const {
//-------------------------------------------------------------------------------
   return fMembers.rbegin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Member_Iterator ROOT::Reflex::ScopeBase::Member_REnd() const {
//-------------------------------------------------------------------------------
   return fMembers.rend();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::MemberTemplate_Iterator ROOT::Reflex::ScopeBase::MemberTemplate_Begin() const {
//-------------------------------------------------------------------------------
   return fMemberTemplates.begin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::MemberTemplate_Iterator ROOT::Reflex::ScopeBase::MemberTemplate_End() const {
//-------------------------------------------------------------------------------
   return fMemberTemplates.end();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_MemberTemplate_Iterator ROOT::Reflex::ScopeBase::MemberTemplate_RBegin() const {
//-------------------------------------------------------------------------------
   return fMemberTemplates.rbegin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_MemberTemplate_Iterator ROOT::Reflex::ScopeBase::MemberTemplate_REnd() const {
//-------------------------------------------------------------------------------
   return fMemberTemplates.rend();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope_Iterator ROOT::Reflex::ScopeBase::SubScope_Begin() const {
//-------------------------------------------------------------------------------
   return fSubScopes.begin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope_Iterator ROOT::Reflex::ScopeBase::SubScope_End() const {
//-------------------------------------------------------------------------------
   return fSubScopes.end();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Scope_Iterator ROOT::Reflex::ScopeBase::SubScope_RBegin() const {
//-------------------------------------------------------------------------------
   return fSubScopes.rbegin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Scope_Iterator ROOT::Reflex::ScopeBase::SubScope_REnd() const {
//-------------------------------------------------------------------------------
   return fSubScopes.rend();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::ScopeBase::SubType_Begin() const {
//-------------------------------------------------------------------------------
   return fSubTypes.begin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::ScopeBase::SubType_End() const {
//-------------------------------------------------------------------------------
   return fSubTypes.end();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::ScopeBase::SubType_RBegin() const {
//-------------------------------------------------------------------------------
   return fSubTypes.rbegin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::ScopeBase::SubType_REnd() const {
//-------------------------------------------------------------------------------
   return fSubTypes.rend();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::ScopeBase::TemplateArgument_Begin() const {
//-------------------------------------------------------------------------------
   return Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::ScopeBase::TemplateArgument_End() const {
//-------------------------------------------------------------------------------
   return Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::ScopeBase::TemplateArgument_RBegin() const {
//-------------------------------------------------------------------------------
   return Reverse_Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::ScopeBase::TemplateArgument_REnd() const {
//-------------------------------------------------------------------------------
   return Reverse_Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::TypeTemplate_Iterator ROOT::Reflex::ScopeBase::SubTypeTemplate_Begin() const {
//-------------------------------------------------------------------------------
   return fTypeTemplates.begin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::TypeTemplate_Iterator ROOT::Reflex::ScopeBase::SubTypeTemplate_End() const {
//-------------------------------------------------------------------------------
   return fTypeTemplates.end();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_TypeTemplate_Iterator ROOT::Reflex::ScopeBase::SubTypeTemplate_RBegin() const {
//-------------------------------------------------------------------------------
   return fTypeTemplates.rbegin();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_TypeTemplate_Iterator ROOT::Reflex::ScopeBase::SubTypeTemplate_REnd() const {
//-------------------------------------------------------------------------------
   return fTypeTemplates.rend();
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::ScopeBase::IsClass() const {
//-------------------------------------------------------------------------------
   return ( fScopeType == CLASS || fScopeType == TYPETEMPLATEINSTANCE );
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::ScopeBase::IsEnum() const {
//-------------------------------------------------------------------------------
   return ( fScopeType == ENUM );
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::ScopeBase::IsNamespace() const {
//-------------------------------------------------------------------------------
   return ( fScopeType == NAMESPACE );
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::ScopeBase::IsTemplateInstance() const {
//-------------------------------------------------------------------------------
   return ( fScopeType == TYPETEMPLATEINSTANCE );
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::ScopeBase::IsUnion() const {
//-------------------------------------------------------------------------------
   return ( fScopeType == UNION );
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::TYPE ROOT::Reflex::ScopeBase::ScopeType() const {
//-------------------------------------------------------------------------------
   return fScopeType;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope ROOT::Reflex::ScopeBase::SubScopeAt( size_t nth ) const {
//-------------------------------------------------------------------------------
   if ( nth < fSubScopes.size() ) { return fSubScopes[ nth ]; }
   return Scope( 0 );
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::ScopeBase::SubScopeSize() const {
//-------------------------------------------------------------------------------
   return fSubScopes.size();
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::ScopeBase::TemplateArgumentSize() const {
//-------------------------------------------------------------------------------
   return 0;
}

#endif // ROOT_Reflex_ScopeBase

// @(#)root/reflex:$Name:  $:$Id: Member.h,v 1.3 2005/11/11 07:18:05 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Reflex_Member
#define ROOT_Reflex_Member

// Include files
#include "Reflex/Kernel.h"

namespace ROOT {
   namespace Reflex {

      // forward declarations
      class MemberBase;
      class Type;
      class Scope;
      class PropertyList;
      class Object;
      class MemberTemplate;

      /**
       * @class Member Member.h Reflex/Member.h
       * @author Stefan Roiser
       * @date 24/11/2003
       * @ingroup Ref
       */
      class Member {

      public:

         /** default constructor */
         Member( const MemberBase * memberBase = 0 );


         /** Copy Constructor */
         Member( const Member & rh );


         /** destructor */
         ~Member();


         /**
          * lesser than operator 
          */
         bool operator < ( const Member & rh ) const;
      

         /** 
          * equal operator 
          */
         bool operator == ( const Member & rh ) const;


         /**
          * not equal operator 
          */
         bool operator != ( const Member & rh ) const;


         /** 
          * assignment operator 
          */
         Member & operator = ( const Member & rh );
      

         /** 
          * operator bool will return true if the member is valid
          * @return true if member is implemented
          */
         operator bool () const;


         /** 
          * DeclaringScope will return the scope which the member lives in
          * @return the declaring scope of the member
          */
         Scope DeclaringScope() const;


         /** 
          * DeclaringType will return the type which the member lives in
          * (i.e. the same as the Scope)
          * @return the declaring type of the member
          */
         Type DeclaringType() const;


         /** 
          * Get a static data member value 
          * @return member value as object
          */
         Object Get() const;


         /** 
          * Get the data member value 
          * @return member value as object
          */
         Object Get( const Object & obj) const;


         /*Object Invoke( const Object & obj, 
           const std::vector < Object > & paramList ) const;*/
         /** 
          * Invoke a member function
          * @param obj the object which owns the member function
          * @param paramList a vector of addresses to paramter values
          * @return the return value of the function as object
          */
         Object Invoke( const Object & obj, 
                        const std::vector < void * > & paramList = 
                        std::vector<void*>()) const;


         //Object Invoke( const std::vector < Object > & paramList ) const;
         /** 
          * Invoke a static function 
          * @param paramList a vector of addresses to parameter values
          * @return the return value of the function as object
          */
         Object Invoke( const std::vector < void * > & paramList = 
                        std::vector<void*>()) const;


         /** 
          * IsAuto checks whether auto is set for the data member 
          * @return true if auto modifier is set for this member
          */
         bool IsAuto() const;


         /** 
          * IsConstructor checks whether the function member is a constructor 
          * @return true if member is a constructor
          */
         bool IsConstructor() const;


         /** 
          * IsConverter checks whether the function member is a user defined conversion function 
          * @return true if member is a conversion operator
          */
         bool IsConverter() const;


         /** 
          *IsCopyConstructor checks whether the function member is a copy constructor 
          * @return true if member is a copy constructor 
          */
         bool IsCopyConstructor() const;


         /** 
          * IsDataMember returns true if this is a data member 
          * @return true if this member is a data member
          */
         bool IsDataMember() const;


         /** 
          * check whether the function member is a destructor 
          * @return true if this member is a destructor
          */
         bool IsDestructor() const;


         /** 
          * IsExplicit checks whether explicit is set for the function member 
          * @return true if explicit modifier is set for this member
          */
         bool IsExplicit() const;


         /** 
          * IsExtern checks whether extern is set for the data member 
          * @return true if extern modifier is set for this member
          */
         bool IsExtern() const;


         /** 
          * IsFunctionMember returns true if this is a function member 
          * @return true if this member is a function member
          */
         bool IsFunctionMember() const;


         /** 
          * IsInline checks whether inline is set for the function member 
          * @return true if inline modifier is set for this member
          */
         bool IsInline() const;

      
         /** 
          * IsMutable check whether mutable is set for the data member 
          * @return true if mutable modifier is set for this member
          */
         bool IsMutable() const;


         /** 
          * IsOperator check whether the function member is an operator 
          * @return true if this member is an operator function
          */
         bool IsOperator() const;


         /** 
          * IsPrivate checks whether the function member is private 
          * @return true if access to this member is private
          */
         bool IsPrivate() const;


         /** 
          * IsProtected checks whether the function member is protected 
          * @return true if access to this member is protected
          */
         bool IsProtected() const;


         /** 
          * IsPublic checks whether the function member is public 
          * @return true if access to this member is public
          */
         bool IsPublic() const;


         /** 
          * IsRegister checks whether register is set for the data member 
          * @return true if register modifier is set for this member
          */
         bool IsRegister() const;


         /* 
          * IsStatic checks whether static is set for the data member 
          * @return true is static modifier is set for this member
          */
         bool IsStatic() const;

 
         /** 
          * IsTemplateInstance returns true if the member represents a 
          * templated member function
          * @return true if member represents a templated member function
          */
         bool IsTemplateInstance() const;


         /** 
          * IsTransient checks whether the function member is transient 
          * @return true if transient modifier is set for this member (not a C++ modifier)
          */
         bool IsTransient() const;


         /** 
          * IsVirtual checks whether virtual is set for the function member 
          * @return true if virtual modifier is set for this member
          */
         bool IsVirtual() const;


         /** 
          * MemberType return the type of the member as enum value (function or data member) 
          * @return member type as enum
          */
         TYPE MemberType() const;


         /** 
          * MemberTypeAsString returns the string representation of the member species 
          * @return member type as string representation
          */
         std::string MemberTypeAsString() const;


         /** 
          * Name returns the Name of the member 
          * @param mod modifiers can be or'ed as argument
          * SCOPED - fully scoped name
          * FINAL  - resolve all typedefs
          * QUALIFIED - cv and reference qualification
          * @return name of the member
          */
         std::string Name( unsigned int mod = 0 ) const;


         /** 
          * Offset returns the offset of the data member relative to the start of the scope
          * @return offset of member as int
          */
         size_t Offset() const;


         /** 
          * FunctionParameterSize returns the number of parameters 
          * @param required if true only returns the number of required parameters
          * @return number of parameters
          */
         size_t FunctionParameterSize( bool required = false ) const;


         /** FunctionParameterAt nth default value if declared*/
         std::string FunctionParameterDefaultAt( size_t nth ) const;


         StdString_Iterator FunctionParameterDefault_Begin() const;
         StdString_Iterator FunctionParameterDefault_End() const;
         Reverse_StdString_Iterator FunctionParameterDefault_RBegin() const;
         Reverse_StdString_Iterator FunctionParameterDefault_REnd() const;


         /** 
          * FunctionParametertNameAt returns the nth parameter name 
          * @param nth parameter name
          * @return nth parameter name
          */
         std::string FunctionParameterNameAt( size_t nth ) const;


         StdString_Iterator FunctionParameterName_Begin() const;
         StdString_Iterator FunctionParameterName_End() const;
         Reverse_StdString_Iterator FunctionParameterName_RBegin() const;
         Reverse_StdString_Iterator FunctionParameterName_REnd() const;


         /**
          * Properties will return the properties attached to this item
          * @return properties of this member
          */
         PropertyList Properties() const;


         /*void Set( const Object & instance,
           const Object & value ) const;*/
         /**
          * Set will set the value of a data member
          * @param instance of the object owning the data member
          * @param value the memory address of the value to set
          */
         void Set( const Object & instance,
                   const void * value ) const;


         /** 
          * SetScope will set the Scope of the member 
          * @param sc scope to set
          */
         void SetScope( const Scope & sc ) const;


         /** 
          * Stubcontext returns a pointer to the context of the member 
          * @return pointer to member context
          */
         void * Stubcontext() const;


         /** 
          * Stubfunction returns the pointer to the stub function 
          * @return function pointer to stub function
          */
         StubFunction Stubfunction() const;


         /**
          * TemplateArgumentAt will return the nth template argument
          * @param  nth template argument
          * @return nth template argument
          */
         Type TemplateArgumentAt( size_t nth ) const;


         /**
          * TemplateArgumentSize will return the number of template arguments
          * @return number of template arguments
          */
         size_t TemplateArgumentSize() const;


         Type_Iterator TemplateArgument_Begin() const;
         Type_Iterator TemplateArgument_End() const;
         Reverse_Type_Iterator TemplateArgument_RBegin() const;
         Reverse_Type_Iterator TemplateArgument_REnd() const;


         /**
          * TemplateFamily returns the corresponding MemberTemplate if any
          * @return corresponding MemberTemplate
          */
         MemberTemplate TemplateFamily() const;


         /** 
          * TypeOf returns the member type 
          * @return member type
          */
         Type TypeOf() const;

      private:

         /** the pointer to the member implementation 
          * @link aggregation
          * @supplierCardinality 1
          * @clientCardinality 1..*
          * @label member BaseAt*/
         const MemberBase * fMemberBase;

      }; // class Member

   } //namespace Reflex
} //namespace ROOT

#include "Reflex/MemberBase.h"
#include "Reflex/Scope.h"
#include "Reflex/PropertyList.h"
#include "Reflex/Type.h"
#include "Reflex/MemberTemplate.h"

//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::operator < ( const Member & rh ) const {
//-------------------------------------------------------------------------------
   if ( (*this) && rh ) 
      return ( TypeOf() < rh.TypeOf() && Name() < rh.Name());
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::operator == ( const Member & rh ) const {
//-------------------------------------------------------------------------------
   if ( (*this) && rh ) 
      return ( TypeOf() == rh.TypeOf() && Name() == rh.Name() );
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::operator != ( const Member & rh ) const {
//-------------------------------------------------------------------------------
   return ! ( *this == rh );
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member & ROOT::Reflex::Member::operator = ( const Member & rh ) {
//-------------------------------------------------------------------------------
   fMemberBase = rh.fMemberBase;
   return * this;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Member::operator bool () const {
//-------------------------------------------------------------------------------
   return 0 != fMemberBase;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Scope ROOT::Reflex::Member::DeclaringScope() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->DeclaringScope();
   return Scope();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type ROOT::Reflex::Member::DeclaringType() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->DeclaringScope();
   return Type();
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsAuto() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsAuto();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsConstructor() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsConstructor();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsConverter() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsConverter();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsCopyConstructor() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsCopyConstructor();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsDataMember() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsDataMember();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsDestructor() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsDestructor();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsExplicit() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsExplicit();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsExtern() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsExtern();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsFunctionMember() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsFunctionMember();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsInline() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsInline();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsMutable() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsMutable();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsOperator() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsOperator();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsPrivate() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsPrivate();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsProtected() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsProtected();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsPublic() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsPublic();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsRegister() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsRegister();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsStatic() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsStatic();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsTemplateInstance() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsTemplateInstance();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsTransient() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsTransient();
   return false;
}


//-------------------------------------------------------------------------------
inline bool ROOT::Reflex::Member::IsVirtual() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->IsVirtual();
   return false;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::TYPE ROOT::Reflex::Member::MemberType() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->MemberType();
   return UNRESOLVED;
}


//-------------------------------------------------------------------------------
inline std::string ROOT::Reflex::Member::MemberTypeAsString() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->MemberTypeAsString();
   return "";
}


//-------------------------------------------------------------------------------
inline std::string ROOT::Reflex::Member::Name( unsigned int mod ) const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->Name( mod );
   return "";
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::Member::Offset() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->Offset();
   return 0;
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::Member::FunctionParameterSize( bool required ) const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterSize( required );
   return 0;
}


//-------------------------------------------------------------------------------
inline std::string ROOT::Reflex::Member::FunctionParameterDefaultAt( size_t nth ) const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterDefaultAt( nth );
   return "";
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::StdString_Iterator ROOT::Reflex::Member::FunctionParameterDefault_Begin() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterDefault_Begin();
   return StdString_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::StdString_Iterator ROOT::Reflex::Member::FunctionParameterDefault_End() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterDefault_End();
   return StdString_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_StdString_Iterator ROOT::Reflex::Member::FunctionParameterDefault_RBegin() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterDefault_RBegin();
   return Reverse_StdString_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_StdString_Iterator ROOT::Reflex::Member::FunctionParameterDefault_REnd() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterDefault_REnd();
   return Reverse_StdString_Iterator();
}


//-------------------------------------------------------------------------------
inline std::string ROOT::Reflex::Member::FunctionParameterNameAt( size_t nth ) const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterNameAt( nth );
   return "";
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::StdString_Iterator ROOT::Reflex::Member::FunctionParameterName_Begin() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterName_Begin();
   return StdString_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::StdString_Iterator ROOT::Reflex::Member::FunctionParameterName_End() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterName_End();
   return StdString_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_StdString_Iterator ROOT::Reflex::Member::FunctionParameterName_RBegin() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterName_RBegin();
   return Reverse_StdString_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_StdString_Iterator ROOT::Reflex::Member::FunctionParameterName_REnd() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->FunctionParameterName_REnd();
   return Reverse_StdString_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::PropertyList ROOT::Reflex::Member::Properties() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->Properties();
   return PropertyList();
}


//-------------------------------------------------------------------------------
inline void ROOT::Reflex::Member::SetScope( const Scope & sc ) const  {
//-------------------------------------------------------------------------------
   if ( *this ) fMemberBase->SetScope( sc );
}


//-------------------------------------------------------------------------------
inline void * ROOT::Reflex::Member::Stubcontext() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->Stubcontext();
   return 0;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::StubFunction ROOT::Reflex::Member::Stubfunction() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->Stubfunction();
   return 0;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type ROOT::Reflex::Member::TemplateArgumentAt( size_t nth ) const {
//-------------------------------------------------------------------------------
   if ( * this ) return fMemberBase->TemplateArgumentAt( nth );
   return Type();
}


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::Member::TemplateArgumentSize() const {
//-------------------------------------------------------------------------------
   if ( * this ) return fMemberBase->TemplateArgumentSize();
   return 0;
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::Member::TemplateArgument_Begin() const {
//-------------------------------------------------------------------------------
   if ( * this ) return fMemberBase->TemplateArgument_Begin();
   return Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type_Iterator ROOT::Reflex::Member::TemplateArgument_End() const {
//-------------------------------------------------------------------------------
   if ( * this ) return fMemberBase->TemplateArgument_End();
   return Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::Member::TemplateArgument_RBegin() const {
//-------------------------------------------------------------------------------
   if ( * this ) return fMemberBase->TemplateArgument_RBegin();
   return Reverse_Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Reverse_Type_Iterator ROOT::Reflex::Member::TemplateArgument_REnd() const {
//-------------------------------------------------------------------------------
   if ( * this ) return fMemberBase->TemplateArgument_REnd();
   return Reverse_Type_Iterator();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::MemberTemplate ROOT::Reflex::Member::TemplateFamily() const {
//-------------------------------------------------------------------------------
   if ( * this ) return fMemberBase->TemplateFamily();
   return MemberTemplate();
}


//-------------------------------------------------------------------------------
inline ROOT::Reflex::Type ROOT::Reflex::Member::TypeOf() const {
//-------------------------------------------------------------------------------
   if ( *this ) return fMemberBase->TypeOf();
   return Type();
}



#endif // ROOT_Reflex_Member




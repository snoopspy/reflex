// @(#)root/reflex:$Name:  $:$Id: EnumBuilder.h,v 1.3 2005/11/23 16:08:08 roiser Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Reflex_EnumBuilder
#define ROOT_Reflex_EnumBuilder

// Include files
#include "Reflex/Builder/TypeBuilder.h"
#include "Reflex/Member.h"

namespace ROOT{
   namespace Reflex{

      // forward declarations
      class Enum;

      /**
       * @class EnumBuilder EnumBuilder.h Reflex/Builder/EnumBuilder.h
       * @author Stefan Roiser
       * @date 14/3/2005
       * @ingroup RefBld
       */
      class EnumBuilder {

      public:
      
         /** constructor */
         EnumBuilder( const char * name,
                      const std::type_info & ti );


         /** destructor */
        virtual ~EnumBuilder();


         /** 
          * AddProperty will add a PropertyNth to the PropertyNth stack
          * which will be emptied with the next enum / item build
          * @param  key the PropertyNth key
          * @param  value the value of the PropertyNth
          * @return a reference to the building class
          */
         EnumBuilder &  AddItem ( const char * nam,
                                  long value );


         /** 
          * AddProperty will add a PropertyNth 
          * @param  key the PropertyNth key
          * @param  value the value of the PropertyNth
          */
         EnumBuilder & AddProperty( const char * key,
                            Any value );


         /** 
          * AddProperty will add a PropertyNth 
          * @param  key the PropertyNth key
          * @param  value the value of the PropertyNth
          */
         EnumBuilder &  AddProperty( const char * key,
                                     const char * value );

      private:

         /** current enum being built */
         Enum * fEnum;

         /** last added enum item */
         Member fLastMember;

      }; // class EnumBuilder


      /** 
       * @class EnumBuilder EnumBuilder.h Reflex/Builder/EnumBuilder.h
       * @author Stefan Roiser
       * @ingroup RefBld
       * @date 30/3/2004
       */
      template < typename T >
         class EnumBuilderT  {

         public:            

         /** constructor */
         EnumBuilderT();


         /** constructor */
         EnumBuilderT( const char * nam );


         /** destructor */
         virtual ~EnumBuilderT() {}


         /** 
          * AddItem add a new item in the enum
          * @param  Name item Name
          * @param  value the value of the item
          * @return a reference to the building class
          */
         EnumBuilderT & AddItem( const char * nam, 
                                 long value );


         /** 
          * AddProperty will add a PropertyNth to the PropertyNth stack
          * which will be emptied with the next enum / item build
          * @param  key the PropertyNth key
          * @param  value the value of the PropertyNth
          * @return a reference to the building class
          */
         template  < typename P >
            EnumBuilderT & AddProperty( const char * key, 
                                        P value );

         private:

         /** the enums and values */
         EnumBuilder fEnumBuilderImpl;

      }; // class EnumBuilder

   } // namespace Reflex
} // namespace ROOT


//-------------------------------------------------------------------------------
template < typename T >
inline ROOT::Reflex::EnumBuilderT<T>::EnumBuilderT() 
//-------------------------------------------------------------------------------
   : fEnumBuilderImpl( Tools::Demangle( typeid(T) ).c_str(), 
                       typeid(T) ) {}


//-------------------------------------------------------------------------------
template < typename T >
inline ROOT::Reflex::EnumBuilderT<T>::EnumBuilderT( const char * nam )
//-------------------------------------------------------------------------------
   : fEnumBuilderImpl( nam, 
                       typeid(UnknownType) ) {}


//-------------------------------------------------------------------------------
template < typename T >
inline ROOT::Reflex::EnumBuilderT<T> & 
ROOT::Reflex::EnumBuilderT<T>::AddItem( const char * nam, 
                                        long value ) {
//-------------------------------------------------------------------------------
   fEnumBuilderImpl.AddItem( nam, value );
   return * this;
}


//-------------------------------------------------------------------------------
template < typename T > template < typename P >
inline ROOT::Reflex::EnumBuilderT<T> & 
ROOT::Reflex::EnumBuilderT<T>::AddProperty( const char * key, 
                                            P value ) {
//-------------------------------------------------------------------------------
   fEnumBuilderImpl.AddProperty( key, value );
   return * this;
}


#endif // ROOT_Reflex_EnumBuilder

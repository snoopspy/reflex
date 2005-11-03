// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Reflex_DataMember
#define ROOT_Reflex_DataMember

// Include files
#include "Reflex/MemberBase.h"

namespace ROOT {
  namespace Reflex {

    // forward declarations
    class TypeBase;
    class Type;

    /**
     * @class DataMember DataMember.h Reflex/DataMember.h
     * @author Stefan Roiser
     * @date 24/11/2003
     * @ingroup Ref
     */
    class DataMember : public MemberBase {

    public:

      /** default constructor */
      DataMember( const char *   nam,
                  const Type &   typ, 
                  size_t         offs,
                  unsigned int   modifiers = 0 );


      /** destructor */
      virtual ~DataMember();


      /** return Name of data MemberNth */
      std::string Name( unsigned int mod = 0 ) const;


      /** Get the MemberNth value (as void*) */
      Object Get( const Object & obj ) const;


      /** return the Offset of the MemberNth */
      size_t Offset() const;


      /** Set the MemberNth value */
      /*void Set( const Object & instance,
        const Object & value ) const;*/
      void Set( const Object & instance,
                const void * value ) const;

    private:

      /** Offset of the MemberNth */
      size_t fOffset;

    }; // class DataMember
  } //namespace Reflex
} //namespace ROOT


//-------------------------------------------------------------------------------
inline size_t ROOT::Reflex::DataMember::Offset() const {
//-------------------------------------------------------------------------------
  return fOffset;
}

#endif // ROOT_Reflex_DataMember


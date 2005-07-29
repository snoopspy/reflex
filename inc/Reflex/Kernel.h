// @(#)root/reflex:$Name:  $:$Id: Kernel.h,v 1.1 2005/06/23 10:21:06 brun Exp $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2005, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef ROOT_Reflex_Kernel
#define ROOT_Reflex_Kernel

// include config.h generated by autoconf
#if defined (HAVE_CONFIG)
#include "config.h"
#endif

#if defined (_AIX)
#define ANSICPP
#define NEED_STRCASECMP
#endif

#if defined(__alpha) && !defined(__linux)
#define __USE_STD_IOSTREAM
#endif

// Some pragmas to avoid warnings in VisualC
#ifdef _WIN32
// Disable warning C4786: identifier was truncated to '255' characters in the debug information
#pragma warning ( disable : 4786 )
// Disable warning C4291: no matching operator delete found; memory will not be freed if 
// initialization throws an exception
#pragma warning ( disable : 4291 )
// Disable warning C4250: inheritance via dominance
#pragma warning ( disable : 4250 )
#endif

// some compilers define the macros below in limits
#include <limits>

// Large integer definition depends of the platform
#ifdef _WIN32
  typedef __int64 longlong;
  typedef unsigned __int64 ulonglong;
#elif defined(__linux) || defined(sun) || defined(__sgi) || defined(__APPLE__) || (defined(__CYGWIN__)&&defined(__GNUC__)) || defined(_AIX) || (defined(__alpha)&&!defined(__linux))
  typedef long long int longlong;
  typedef unsigned long long int ulonglong;
#endif
#ifndef LONGLONG_MAX
  #define LONGLONG_MAX 0x7FFFFFFFFFFFFFFFLL
#endif
#ifndef LONGLONG_MIN
  #define LONGLONG_MIN 0x8000000000000000LL
#endif
#ifndef ULONGLONG_MAX
  #define ULONGLONG_MAX 0xFFFFFFFFFFFFFFFFLL
#endif
#ifndef ULONGLONG_MIN
  #define ULONGLONG_MIN 0x0000000000000000LL
#endif

// Include files
#include <string>
#include <vector>
#include <utility>
#include <exception>

namespace ROOT {
  namespace Reflex {

    /** some general information about the Reflex package */
    struct Reflex {
      
      /** default constructor */
      Reflex();
      
      /** the Name of the package - used for messages */
      static const std::string & Argv0(); // returns "Seal Reflex";
      
    }; // struct Reflex


    // these defines are used for the modifiers they are used in the following 
    // classes
    // BA = BASE
    // CL = CLASS
    // FU = FUNCTION
    // DM = DATAMEMBER
    // FM = FUNCTIONMEMBER 
    // TY = TYPE
    // ME = MEMBER
    //                              BA  CL  FU  DM  FM  TY  ME 
    enum {
      PUBLIC          = (1<<0),  //  X           X   X       X
      PROTECTED       = (1<<1),  //  X           X   X       X
      PRIVATE         = (1<<2),  //  X           X   X       X
      REGISTER        = (1<<3),  //              X   X       X
      STATIC          = (1<<4),  //              X   X       X
      CONSTRUCTOR     = (1<<5),  //                  X       X
      DESTRUCTOR      = (1<<6) , //                  X       X
      EXPLICIT        = (1<<7),  //                  X       X
      EXTERN          = (1<<8) , //              X   X       X
      COPYCONSTRUCTOR = (1<<9) , //                  X       X
      OPERATOR        = (1<<10), //                  X       X
      INLINE          = (1<<11), //                  X       X
      CONVERTER       = (1<<12), //                  X       X
      AUTO            = (1<<13), //              X           X
      MUTABLE         = (1<<14), //              X           X
      CONST           = (1<<15), //              X       X   X
      VOLATILE        = (1<<16), //              X       X   X
      REFERENCE       = (1<<17), //              X           X
      ABSTRACT        = (1<<18), //      X               X
      VIRTUAL         = (1<<19), //  X   X               X
      TRANSIENT       = (1<<20)  //              X           X
    };


    /** enum for printing names */
    enum {
      FINAL     = (1<<0),
      QUALIFIED = (1<<1),
      SCOPED    = (1<<2),
      F         = (1<<4),
      Q         = (1<<5),
      S         = (1<<6)
    };
      

    /** enum containing all possible types and scopes */
    enum TYPE { CLASS = 0,
                STRUCT,
                ENUM, 
                FUNCTION, 
                ARRAY, 
                FUNDAMENTAL, 
                POINTER, 
                POINTERTOMEMBER, 
                TYPEDEF, 
                UNION, 
                TYPETEMPLATEINSTANCE, 
                MEMBERTEMPLATEINSTANCE, 
                NAMESPACE, 
                DATAMEMBER, 
                FUNCTIONMEMBER,
                UNRESOLVED
    };


    /** all possible status codes of the package */
    enum STATUS { SUCCESS = 0,
                  FAILURE
    };
    
    /** the Name of the status code -- don't use this to check */
    #define SRSTATUSNAME rstat
    /** the Name of the status code to check for */
    #define SRSTATUS Reflex::SRSTATUSNAME
        

    /**
      * typedef for function MemberNth TypeNth (necessary for return value of
      * getter function)
      */
    typedef void * (* StubFunction) ( void *, const std::vector < void * > &, void *);

    /** typedef for function for Offset calculation */
    typedef size_t( * OffsetFunction ) ( void * );

    /** dummy types for type_info purposes */
    struct NullType {};
    struct UnknownType {};
    /** place holders for unnamed types (also typeinfo purposes) */
    struct UnnamedClass {};
    struct UnnamedEnum {};
    struct UnnamedNamespace {};
    struct UnnamedStruct {};
    struct UnnamedUnion {};
    
    /** exception classes */
    struct RuntimeError : public std::exception {
      RuntimeError(const std::string& msg) : fMsg(Reflex::Argv0() + ": " + msg) { }
      ~RuntimeError() throw() {}
      virtual const char * What() const throw( ) { return fMsg.c_str();}
      std::string fMsg;
    };

  } // namespace Reflex
} // namespace ROOT

#endif // ROOT_Reflex_Kernel


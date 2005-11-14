// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// CppUnit include file
#include "cppunit/extensions/HelperMacros.h"

// Seal include files
#include "Reflex/Reflex.h"

#include "src/Fundamental.h"
#include "src/Pointer.h"
#include "src/DataMember.h"
#include "src/Array.h"
#include "src/Typedef.h"
#include "src/Namespace.h"
#include "src/Function.h"
#include "src/FunctionMember.h"
#include "src/Class.h"
#include "src/ClassTemplateInstance.h"

// Standard C++ include files
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace ROOT::Reflex;
using namespace std;


/** test_SealKenel_Properties.cpp
  *
  * Simple test cases to exercise Framework properties
  */

class ReflexUnitTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( ReflexUnitTest );
  CPPUNIT_TEST( any_type );
  CPPUNIT_TEST( empty_type );
  CPPUNIT_TEST( empty_scope );
  CPPUNIT_TEST( empty_member );
  CPPUNIT_TEST( exception );
  CPPUNIT_TEST( property_list );
  CPPUNIT_TEST( fundamental_type );
  CPPUNIT_TEST( pointer_type );
  CPPUNIT_TEST( reference_type );
  CPPUNIT_TEST( array_type );
  CPPUNIT_TEST( typedef_type );
  CPPUNIT_TEST( class_type );
  CPPUNIT_TEST( type_base );
  CPPUNIT_TEST( object_basics );
  CPPUNIT_TEST( namespace_scope );
  CPPUNIT_TEST( namespace_members );
  CPPUNIT_TEST( function_member );
  CPPUNIT_TEST( type_template );
  CPPUNIT_TEST( member );
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp () {}
  void any_type();
  void empty_type();
  void empty_scope();
  void empty_member();
  void exception();
  void property_list();
  void fundamental_type();
  void pointer_type();
  void reference_type();
  void array_type();
  void typedef_type();
  void class_type();
  void type_base();
  void object_basics();
  void typedef_basics();
  void namespace_scope();
  void namespace_members();
  void function_member();
  void type_template();
  void member();
  void tearDown() {}
};

struct foo { 
  foo(int i) : m(i) {}
  int m; 
};

struct bar { 
  bar(float i) :b(i) {}
  float b; 
};

void ReflexUnitTest::any_type()
{
  Any empty;
  CPPUNIT_ASSERT(empty.Empty());
  empty = foo(20); 
  CPPUNIT_ASSERT(!empty.Empty());
  CPPUNIT_ASSERT_EQUAL(typeid(foo).name(),empty.TypeInfo().name());

  Any i(10);
  CPPUNIT_ASSERT(!i.Empty());
  CPPUNIT_ASSERT_EQUAL(10, any_cast<int>(i));
  //CPPUNIT_ASSERT_THROW(any_cast<float>(i), ROOT::Reflex::bad_any_cast);
  try {
    any_cast<float>(i);
  }
  catch (ROOT::Reflex::bad_any_cast e) {
    CPPUNIT_ASSERT_EQUAL(std::string("bad_any_cast: failed conversion using any_cast"), std::string(e.What()));
  }
  Any f(10.66F);
  CPPUNIT_ASSERT_EQUAL(10.66F, any_cast<float>(f));
  Any d(99.77);
  CPPUNIT_ASSERT_EQUAL(99.77, any_cast<double>(d));
  Any s(string("string"));
  CPPUNIT_ASSERT_EQUAL(string("string"), any_cast<string>(s));
  const char* cs = "c-string";
  Any c(cs);
  CPPUNIT_ASSERT_EQUAL(cs, any_cast<const char*>(c));
  stringstream ss;
  ss << i;
  CPPUNIT_ASSERT_EQUAL(ss.str(), string("10"));

}


void ReflexUnitTest::empty_type() {
  Type t;
  CPPUNIT_ASSERT_EQUAL(40, int(Type::TypeSize()));
  CPPUNIT_ASSERT(!t);
  CPPUNIT_ASSERT_EQUAL(0, int(t.Allocate()));
  CPPUNIT_ASSERT(!t.BaseAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.BaseSize()));
  CPPUNIT_ASSERT(!t.CastObject(Type(),Object()));
  CPPUNIT_ASSERT(!t.Construct());
  CPPUNIT_ASSERT(!t.DataMemberAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.DataMemberSize()));
  CPPUNIT_ASSERT(!t.DeclaringScope());
  CPPUNIT_ASSERT(!t.DynamicType(Object()));
  CPPUNIT_ASSERT(!t.FunctionMemberAt(0));
  CPPUNIT_ASSERT_EQUAL(0,int(t.FunctionMemberSize()));
  CPPUNIT_ASSERT(!t.HasBase(Type()));
  CPPUNIT_ASSERT_EQUAL(0, int(t.Id()));
  CPPUNIT_ASSERT_EQUAL(false, t.IsAbstract());
  CPPUNIT_ASSERT_EQUAL(false, t.IsArray());
  CPPUNIT_ASSERT_EQUAL(false, t.IsClass());
  CPPUNIT_ASSERT_EQUAL(false, t.IsComplete());
  CPPUNIT_ASSERT_EQUAL(false, t.IsConst());
  CPPUNIT_ASSERT_EQUAL(false, t.IsConstVolatile());
  CPPUNIT_ASSERT_EQUAL(false, t.IsEnum());
  CPPUNIT_ASSERT_EQUAL(true, t.IsEquivalentTo(Type()));
  CPPUNIT_ASSERT_EQUAL(false, t.IsFunction());
  CPPUNIT_ASSERT_EQUAL(false, t.IsFundamental());
  CPPUNIT_ASSERT_EQUAL(false, t.IsPointer());
  CPPUNIT_ASSERT_EQUAL(false, t.IsPointerToMember());
  CPPUNIT_ASSERT_EQUAL(false, t.IsReference());
  CPPUNIT_ASSERT_EQUAL(false, t.IsStruct());
  CPPUNIT_ASSERT_EQUAL(false, t.IsTemplateInstance());
  CPPUNIT_ASSERT_EQUAL(false, t.IsTypedef());
  CPPUNIT_ASSERT_EQUAL(false, t.IsUnion());
  CPPUNIT_ASSERT_EQUAL(true, t.IsUnqualified());
  CPPUNIT_ASSERT_EQUAL(false, t.IsVirtual());
  CPPUNIT_ASSERT_EQUAL(false, t.IsVolatile());
  CPPUNIT_ASSERT_EQUAL(0, int(t.ArrayLength()));
  CPPUNIT_ASSERT(!t.MemberByName(""));
  CPPUNIT_ASSERT(!t.MemberAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.MemberSize()));
  CPPUNIT_ASSERT(!t.MemberTemplateAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.MemberTemplateSize()));
  CPPUNIT_ASSERT_EQUAL(std::string(""), t.Name());
  CPPUNIT_ASSERT_EQUAL(std::string(""), std::string(t.Name_c_str()));
  CPPUNIT_ASSERT(!t.FunctionParameterAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.FunctionParameterSize()));
  CPPUNIT_ASSERT(!t.Properties());
  CPPUNIT_ASSERT(!t.ReturnType());
  CPPUNIT_ASSERT(!t.DeclaringScope());
  CPPUNIT_ASSERT_EQUAL(0, int(t.SizeOf()));
  CPPUNIT_ASSERT(!t.SubScopeAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.SubScopeSize()));
  CPPUNIT_ASSERT(!t.SubTypeAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.SubTypeSize()));
  CPPUNIT_ASSERT(!t.TemplateArgumentAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.TemplateArgumentSize()));
  CPPUNIT_ASSERT(!t.TemplateFamily());
  CPPUNIT_ASSERT(!t.ToType());
  CPPUNIT_ASSERT_EQUAL(std::string(typeid(void).name()), std::string(t.TypeInfo().name()));
  CPPUNIT_ASSERT(!t.SubTypeTemplateAt(0));
  CPPUNIT_ASSERT_EQUAL(0, int(t.SubTypeTemplateSize()));
  CPPUNIT_ASSERT_EQUAL(UNRESOLVED,t.TypeType());
  CPPUNIT_ASSERT_EQUAL(std::string("UNRESOLVED"), t.TypeTypeAsString());
}

void ReflexUnitTest::empty_scope() {
  Scope s;
  CPPUNIT_ASSERT(!s.DataMemberAt(0));
}

void ReflexUnitTest::empty_member() {
  Member m;
  CPPUNIT_ASSERT(!m.Get());
}

void ReflexUnitTest::exception() {
  Type t = Type::ByName("int");
  CPPUNIT_ASSERT(t);
  //CPPUNIT_ASSERT_THROW(t.updateMembers(), ROOT::Reflex::RuntimeError);
  try {
    t.UpdateMembers();
  }
  catch (ROOT::Reflex::RuntimeError e) {
    CPPUNIT_ASSERT_EQUAL(std::string("SEAL REFLEX: Function UpdateMembers can only be called on Class/Struct"), std::string(e.What()));
  }
}

void ReflexUnitTest::property_list()
{
  PropertyList pl = PropertyList(new PropertyListImpl());
  
  pl.AddProperty("int", 10);
  CPPUNIT_ASSERT(pl.HasKey("int"));
  CPPUNIT_ASSERT_EQUAL(10, any_cast<int>(pl.PropertyValue("int")));
  CPPUNIT_ASSERT_EQUAL(string("10"), pl.PropertyAsString("int"));

  pl.AddProperty("double", 10.8);
  CPPUNIT_ASSERT(pl.HasKey("double"));
  CPPUNIT_ASSERT_EQUAL(10.8, any_cast<double>(pl.PropertyValue("double")));
  CPPUNIT_ASSERT_EQUAL(string("10.8"), pl.PropertyAsString("double"));
  
  pl.AddProperty("char*", "this is a char*" );
  CPPUNIT_ASSERT(pl.HasKey("char*"));
  CPPUNIT_ASSERT(!strcmp("this is a char*",any_cast<const char*>(pl.PropertyValue("char*"))));
  CPPUNIT_ASSERT_EQUAL(string("this is a char*"), pl.PropertyAsString("char*"));

  string s = "this is a string";
  pl.AddProperty("string", s);
  CPPUNIT_ASSERT(pl.HasKey("string"));
  CPPUNIT_ASSERT_EQUAL(s, any_cast<string>(pl.PropertyValue("string")));
  CPPUNIT_ASSERT_EQUAL(s, pl.PropertyAsString("string"));
  CPPUNIT_ASSERT_EQUAL(string(""), pl.PropertyAsString("none"));

  CPPUNIT_ASSERT_EQUAL((size_t)4, pl.PropertySize());
  CPPUNIT_ASSERT_EQUAL(string("char*, double, int, string"), pl.PropertyKeys());
  
  pl.RemoveProperty("char*");
  CPPUNIT_ASSERT(!pl.HasKey("char*"));
  CPPUNIT_ASSERT_EQUAL((size_t)3, pl.PropertySize());

}

struct myInt { int m;};

void ReflexUnitTest::fundamental_type()
{
  Fundamental itype("myInt",sizeof(myInt),typeid(myInt));
  CPPUNIT_ASSERT(itype.IsFundamental());
  CPPUNIT_ASSERT(!itype.IsClass());
  CPPUNIT_ASSERT_EQUAL( sizeof(myInt), itype.SizeOf());
  CPPUNIT_ASSERT_EQUAL( string("myInt"), itype.Name());

  Type itypet = itype;
  Object iobj = itypet.Construct();
  CPPUNIT_ASSERT( iobj.TypeOf() == itype.ThisType() );
  itype.Destruct(iobj.Address());
}

//struct MyUnknownType {};

void ReflexUnitTest::type_base() {
  {
    Fundamental f("fundamental",0,typeid(UnknownType));
    Type ft = Type::ByName("fundamental");
    CPPUNIT_ASSERT(ft);
    Type ftt = f;
    CPPUNIT_ASSERT(ft.Id()==ftt.Id());

    Type fy = Type::ByTypeInfo(typeid(UnknownType));
    CPPUNIT_ASSERT(fy);
    Type fyy = fy;
    CPPUNIT_ASSERT(fy.Id()==fyy.Id());
  }
  Type ft = Type::ByName("fundamental"); // Type is not deleted
  CPPUNIT_ASSERT(!ft);
  Fundamental f("fundamental",0,typeid(UnknownType));
  CPPUNIT_ASSERT(ft);
}

void ReflexUnitTest::pointer_type() {
  Fundamental f("fundamental",0,typeid(UnknownType));
  Pointer fp(f.ThisType(),typeid(void*));
  Type fpt = Type::ByName("fundamental*");
  CPPUNIT_ASSERT(fpt);
  CPPUNIT_ASSERT(fpt.IsPointer());
  CPPUNIT_ASSERT(!fpt.IsFundamental());
  CPPUNIT_ASSERT_EQUAL(string("fundamental*"), fpt.Name());
  CPPUNIT_ASSERT_EQUAL(string("fundamental*"), fpt.Name());
  CPPUNIT_ASSERT(f.ThisType() == fpt.ToType());
}

void ReflexUnitTest::reference_type() {
  Fundamental f("fundamental",0,typeid(UnknownType));
  DataMember d("myDataMember",f.ThisType(),0,REFERENCE);
  Type frt = d.TypeOf();
  CPPUNIT_ASSERT(frt);
  CPPUNIT_ASSERT(frt.IsReference());
  CPPUNIT_ASSERT(!frt.IsPointer());
  CPPUNIT_ASSERT(frt.IsFundamental());
  CPPUNIT_ASSERT_EQUAL(string("fundamental"), frt.Name());
  CPPUNIT_ASSERT_EQUAL(string("fundamental&"), frt.Name(Q));
  CPPUNIT_ASSERT(f.ThisType() == d.TypeOf());
}

void ReflexUnitTest::array_type() {
  Type f = Type::ByName("float");
  Array fa(f, 10, typeid(float[10]));
  Type fat = Type::ByName("float[10]");
  CPPUNIT_ASSERT(fat);
  CPPUNIT_ASSERT(fat.IsArray());
  CPPUNIT_ASSERT(!fat.IsPointer());
  CPPUNIT_ASSERT(!fat.IsFundamental());
  CPPUNIT_ASSERT_EQUAL(string("float[10]"), fat.Name());
  CPPUNIT_ASSERT_EQUAL(string("float[10]"), fat.Name(Q));
  CPPUNIT_ASSERT(f == fat.ToType());
  CPPUNIT_ASSERT_EQUAL(10*sizeof(float), fat.SizeOf());
}

void ReflexUnitTest::typedef_type() {

  //Fundamental i("int",sizeof(int),typeid(int));
  Typedef my_i("myInt", Type::ByName("int"));
  Typedef your_i("yourInt", Type::ByName("myInt"));
  CPPUNIT_ASSERT(my_i.IsTypedef());
  CPPUNIT_ASSERT(your_i.IsTypedef());
  CPPUNIT_ASSERT_EQUAL(string("myInt"), my_i.Name());
  CPPUNIT_ASSERT_EQUAL(string("yourInt"), your_i.Name());
  CPPUNIT_ASSERT_EQUAL(string("int"), my_i.Name(F));
  CPPUNIT_ASSERT_EQUAL(string("int"), your_i.Name(F));
  CPPUNIT_ASSERT_EQUAL(sizeof(int), my_i.SizeOf());
}

void ReflexUnitTest::namespace_scope() {
  {
    Namespace ns("Namespace");
    Scope s = Scope::ByName("Namespace");
    CPPUNIT_ASSERT(s);
    CPPUNIT_ASSERT_EQUAL(NAMESPACE, s.ScopeType());
    CPPUNIT_ASSERT_EQUAL(string("NAMESPACE"), s.ScopeTypeAsString());
    CPPUNIT_ASSERT(s.IsNamespace());
    CPPUNIT_ASSERT(!s.IsClass());
    CPPUNIT_ASSERT(!s.IsTopScope());
    CPPUNIT_ASSERT_EQUAL(string("Namespace"), s.Name());

    Scope g = Scope::ByName("");
    CPPUNIT_ASSERT(g);
    CPPUNIT_ASSERT(g.IsTopScope());
    CPPUNIT_ASSERT(g.IsNamespace());
    CPPUNIT_ASSERT_EQUAL(string(""), g.Name());
    CPPUNIT_ASSERT(ns.DeclaringScope() == g);
    Namespace s1("Namespace::Subspace1");
    Namespace s2("Namespace::Subspace2");
    CPPUNIT_ASSERT(Scope::ByName("Namespace::Subspace1"));
    CPPUNIT_ASSERT(Scope::ByName("Namespace::Subspace2"));
    CPPUNIT_ASSERT_EQUAL(s.Id(), s1.DeclaringScope().Id());
    CPPUNIT_ASSERT_EQUAL(s.Id(), s2.DeclaringScope().Id());
    CPPUNIT_ASSERT_EQUAL(size_t(2), s.SubScopeSize());
    CPPUNIT_ASSERT_EQUAL(size_t(1), g.SubScopeSize());
    CPPUNIT_ASSERT_EQUAL(s1.ThisScope().Id(), s.SubScopeAt(0).Id());
    CPPUNIT_ASSERT_EQUAL(s2.ThisScope().Id(), s.SubScopeAt(1).Id());
  }
  CPPUNIT_ASSERT(!Scope::ByName("Namespace"));
  CPPUNIT_ASSERT(!Scope::ByName("Namespace::Subspace1"));
  CPPUNIT_ASSERT(!Scope::ByName("Namespace::Subspace2"));
  Namespace s1("Namespace::Subspace1");
  CPPUNIT_ASSERT(Scope::ByName("Namespace::Subspace1"));
}

void * s_f1( void*, const vector<void*>&, void* ) {return 0;}

void ReflexUnitTest::namespace_members() {
  Namespace n("Members");
  CPPUNIT_ASSERT_EQUAL(size_t(0), n.MemberSize());

  Type i = Type::ByName("int");
  Type f = Type::ByName("float");
  Member m1 = Member(new DataMember("d1",i,0));
  Member m2 = Member(new DataMember("d2",f,4));
  n.AddDataMember(m1);
  n.AddDataMember(m2);
  CPPUNIT_ASSERT_EQUAL(size_t(2), n.MemberSize());
  CPPUNIT_ASSERT_EQUAL(size_t(2), n.DataMemberSize());
  CPPUNIT_ASSERT_EQUAL(string("d1"), n.DataMemberAt(0).Name());
  CPPUNIT_ASSERT_EQUAL(string("d2"), n.DataMemberAt(1).Name());

  vector<Type> params;
  params.push_back(i);
  params.push_back(f);
  Function fun(f, params, typeid(void (void)) );
  CPPUNIT_ASSERT_EQUAL(string("float (int, float)"), fun.Name());

  Member m3 = Member(new FunctionMember("f1",fun.ThisType(),s_f1,0,"i;f=99.9"));
  Member m4 = Member(new FunctionMember("f2",fun.ThisType(),s_f1,0,"j=10"));
  n.AddFunctionMember(m3);
  n.AddFunctionMember(m4);
  CPPUNIT_ASSERT_EQUAL(size_t(2), n.FunctionMemberSize());
  CPPUNIT_ASSERT_EQUAL(string("f1"), n.FunctionMemberAt(0).Name());
  CPPUNIT_ASSERT_EQUAL(string("f2"), n.FunctionMemberAt(1).Name());

  CPPUNIT_ASSERT_EQUAL(size_t(4), n.MemberSize());
  CPPUNIT_ASSERT_EQUAL(string("d1"), n.MemberAt(0).Name());
  CPPUNIT_ASSERT_EQUAL(string("d2"), n.MemberAt(1).Name());
  CPPUNIT_ASSERT_EQUAL(string("f1"), n.MemberAt(2).Name());
  CPPUNIT_ASSERT_EQUAL(string("f2"), n.MemberAt(3).Name());
}

void ReflexUnitTest::function_member() {
  vector<Type> params;
  params.push_back(Type::ByName("int"));
  params.push_back(Type::ByName("double"));
  params.push_back(Type::ByName("bool"));
  Function fun(Type::ByName("float"),params,typeid(void (void)) );
  Member fun1 (new FunctionMember("fun1",fun.ThisType(),0,0,"arg1;arg2;arg3",STATIC));
  Member fun2 (new FunctionMember("fun2",fun.ThisType(),0,0,"arg1;arg2=99.9;arg3=true"));
  Member fun3 (new FunctionMember("fun3",fun.ThisType(),0,0,"arg1;arg2"));
  CPPUNIT_ASSERT_EQUAL(size_t(3), fun1.FunctionParameterSize() );
  CPPUNIT_ASSERT_EQUAL(string("arg1"), fun1.FunctionParameterNameAt(0) );
  CPPUNIT_ASSERT_EQUAL(string("arg2"), fun1.FunctionParameterNameAt(1) );
  CPPUNIT_ASSERT_EQUAL(string("arg3"), fun1.FunctionParameterNameAt(2) );
  CPPUNIT_ASSERT_EQUAL(string(""),     fun2.FunctionParameterDefaultAt(0) );
  CPPUNIT_ASSERT_EQUAL(string("99.9"), fun2.FunctionParameterDefaultAt(1) );
  CPPUNIT_ASSERT_EQUAL(string("true"), fun2.FunctionParameterDefaultAt(2) );
  CPPUNIT_ASSERT_EQUAL(string("arg1"), fun3.FunctionParameterNameAt(0) );
  CPPUNIT_ASSERT_EQUAL(string("arg2"), fun3.FunctionParameterNameAt(1) );
  CPPUNIT_ASSERT_EQUAL(string(""),     fun3.FunctionParameterNameAt(2) );
}


void ReflexUnitTest::object_basics() {
  Type i = Type::ByName("int");
  Object o1 = i.Construct();
  Object o2 = o1;
  CPPUNIT_ASSERT(o1 == o2);
}

void ReflexUnitTest::class_type() {
  {
    Class _foo = Class("foo", sizeof(foo), typeid(foo));
    Class _bar = Class("bar", sizeof(bar), typeid(bar));
    CPPUNIT_ASSERT(Type::ByName("foo"));
    CPPUNIT_ASSERT(_foo.ThisType() == Type::ByName("foo"));
    CPPUNIT_ASSERT(_foo.ThisType() == Type::ByTypeInfo(typeid(foo)));
    CPPUNIT_ASSERT(_bar.ThisType() == Type::ByName("bar"));
    CPPUNIT_ASSERT(_bar.ThisType() == Type::ByTypeInfo(typeid(bar)));
  }
  CPPUNIT_ASSERT(!Type::ByName("foo"));
  CPPUNIT_ASSERT(Type::ByName("foo").Id());
  CPPUNIT_ASSERT(!Type::ByTypeInfo(typeid(foo)));
  CPPUNIT_ASSERT(!Type::ByName("bar"));
  CPPUNIT_ASSERT(Type::ByName("bar").Id());
  CPPUNIT_ASSERT(!Type::ByTypeInfo(typeid(bar)));
}


void ReflexUnitTest::type_template() {
  Namespace _n = Namespace("mmm");
  ClassTemplateInstance _cti = ClassTemplateInstance("mmm::template<int,float,dummy>",
                                                     1,
                                                     typeid(int),
                                                     0);

  Scope s = Scope::ByName("mmm");

  CPPUNIT_ASSERT_EQUAL(1, (int)s.SubTypeTemplateSize());
  
  TypeTemplate tt = s.SubTypeTemplateAt(0);
  
  CPPUNIT_ASSERT(tt == true);
  CPPUNIT_ASSERT(tt.Name()       == "template");
  CPPUNIT_ASSERT(tt.Name(SCOPED) == "mmm::template");
  
  CPPUNIT_ASSERT_EQUAL(1, (int)tt.TemplateInstanceSize());
  
  Type t1 = tt.TemplateInstanceAt(0); 
  CPPUNIT_ASSERT( t1 );
  CPPUNIT_ASSERT_EQUAL(std::string("mmm::template<int,float,dummy>"), t1.Name(S|Q|F));
  CPPUNIT_ASSERT( t1.IsClass() );
  CPPUNIT_ASSERT( t1.IsTemplateInstance() );

  Type c1 = Type::ByName("mmm::template<int,float,dummy>");
  CPPUNIT_ASSERT( c1 );
  CPPUNIT_ASSERT(c1 == t1);
  CPPUNIT_ASSERT_EQUAL(std::string("mmm::template<int,float,dummy>"), c1.Name(S|Q|F));
  CPPUNIT_ASSERT_EQUAL(std::string("template<int,float,dummy>"), c1.Name());
  CPPUNIT_ASSERT( c1.IsClass() );
  CPPUNIT_ASSERT( c1.IsTemplateInstance() );

  Scope s1 = Scope::ByName("mmm::template<int,float,dummy>");
  CPPUNIT_ASSERT( s1 );
  CPPUNIT_ASSERT_EQUAL(std::string("mmm::template<int,float,dummy>"), s1.Name(S|Q|F));
  CPPUNIT_ASSERT_EQUAL(std::string("template<int,float,dummy>"), s1.Name());
  CPPUNIT_ASSERT( s1.IsClass() );
  CPPUNIT_ASSERT( s1.IsTemplateInstance() );
  
  CPPUNIT_ASSERT_EQUAL( 3, (int)c1.TemplateArgumentSize() );
  CPPUNIT_ASSERT( c1.TemplateArgumentAt(0) );
  CPPUNIT_ASSERT( c1.TemplateArgumentAt(1) );
  CPPUNIT_ASSERT( ! c1.TemplateArgumentAt(2) );

  CPPUNIT_ASSERT_EQUAL( string("int"), c1.TemplateArgumentAt(0).Name() );
  CPPUNIT_ASSERT_EQUAL( string("float"), c1.TemplateArgumentAt(1).Name() );
  CPPUNIT_ASSERT_EQUAL( string("dummy"), c1.TemplateArgumentAt(2).Name() );
 
}


void ReflexUnitTest::member() {

  Member m1 = Member(0);
  CPPUNIT_ASSERT( ! m1 );

  Member m2 = Member();
  CPPUNIT_ASSERT( ! m2 );

}

// Class registration on cppunit framework
CPPUNIT_TEST_SUITE_REGISTRATION(ReflexUnitTest);

// CppUnit test-driver common for all the cppunit test classes 
#include<CppUnit_testdriver.cpp>


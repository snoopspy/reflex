// @(#)root/reflex:$Name:$:$Id:$
// Author: Stefan Roiser 2004

// CppUnit include file
#include "cppunit/extensions/HelperMacros.h"

// Seal include files
#include "Reflex/Reflex.h"

// Standard C++ include files
#include <iostream>
#ifdef _WIN32
  #include<windows.h>
#else
  #include<dlfcn.h>
#endif

using namespace std;
using namespace ROOT::Reflex;
enum Visibility { Public, Protected, Private }; 

void generate_class_decl( const Type & cl,
                          const string & indent ) {

  // ... base class declarations
  if ( cl.BaseSize()) {
    for (size_t b = 0; b < cl.BaseSize(); ++b) 
      generate_class_decl(cl.BaseAt(b).ToType(), indent);
  }

  cout << indent << "class " << cl.Name();

  // ... bases
  if (cl.BaseSize() != 0 ) {

    cout << " : " ;

    for ( size_t b = 0; b < cl.BaseSize(); b++ ) {

      Base ba = cl.BaseAt(b);

      if ( ba.IsVirtual() )   cout << "virtual ";
      if ( ba.IsPublic() )    cout << "public ";
      if ( ba.IsProtected() ) cout << "protected ";
      if ( ba.IsPrivate() )   cout << "private ";

      cout << ba.ToType().Name(SCOPED);

      if ( b != cl.BaseSize()-1 ) cout << ", ";
    }
  }

  cout << " {" << endl;

  Visibility vis = Private;

  // ... function members
  for ( size_t f = 0; f < cl.FunctionMemberSize(); f++ ) {

    Member fm = cl.FunctionMemberAt(f);

    if ( fm.IsPublic() && vis != Public ) {
      cout << indent << "public:" << endl;  
      vis = Public;
    }
    else if ( fm.IsProtected() && vis != Protected ) {
      cout << indent << "protected:" << endl;  
      vis = Protected;
    }
    else if ( fm.IsPrivate()   && vis != Private ) {
      cout << indent << "private:" << endl;  
      vis = Private;
    }

    Type ft = fm.TypeOf();

    cout << indent + "  ";

    if ( ! fm.IsConstructor() && !fm.IsDestructor() ) 
      cout << ft.ReturnType().Name(SCOPED) << " ";

    if (  fm.IsOperator() ) cout << "operator ";
    cout << fm.Name() << " (";

    if ( ft.FunctionParameterSize() ) {
      for ( size_t p = 0 ; p < ft.FunctionParameterSize(); p++ ) {
        cout << ft.FunctionParameterAt(p).Name(SCOPED|QUALIFIED);

        if ( fm.FunctionParameterNameAt(p).length() ) 
          cout << " " << fm.FunctionParameterNameAt(p);

        if ( fm.FunctionParameterDefaultAt(p).length() ) 
          cout << " = " << fm.FunctionParameterDefaultAt(p);

        if ( p != ft.FunctionParameterSize()-1 ) cout << ", ";
      }
    }
    cout << ");" << endl;
  }

  // ... data members
  for ( size_t d = 0; d < cl.DataMemberSize(); d++ ) {
    Member dm = cl.DataMemberAt(d);

    if ( dm.IsPublic() && vis != Public ) {
      cout << indent << "public:" << endl;  
      vis = Public; 
    }
    else if ( dm.IsProtected() && vis != Protected ) {
      cout << indent << "protected:" << endl;  
      vis = Protected; 
    }
    else if ( dm.IsPrivate()   && vis != Private ) {
      cout << indent << "private:" << endl;  
      vis = Private;
    }
    cout << indent + "  " << dm.TypeOf().Name(SCOPED) 
         << " " << dm.Name() << ";"  << endl;
  }
  cout << indent << "};" << endl;
}

void generate_class(const Type & ty) {

  std::string indent = "";
  Scope sc = ty.DeclaringScope();

  // ... declaring scope
  if ( ! sc.IsTopScope() ) {
    if (sc.IsNamespace())  cout << "namespace ";
    else if (sc.IsClass()) cout << "class ";

    cout << sc.Name() << " {" << endl;
    indent += "  ";
  }

  generate_class_decl(ty, indent);

  if ( ! sc.IsTopScope() ) {
    cout << "}" << endl;
    if (sc.IsClass()) cout << ";";
  }
}





using namespace ROOT::Reflex;

/**
 * test_Reflex_simple2.cpp
 * testing Reflex with a simple test dictionary
 */

class ReflexSimple2Test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE( ReflexSimple2Test );
  CPPUNIT_TEST( loadLibrary );
  CPPUNIT_TEST( fooBarZot );
  CPPUNIT_TEST( testBaseClasses );
  CPPUNIT_TEST( testDataMembers );
  CPPUNIT_TEST( testFunctionMembers );
  CPPUNIT_TEST( testFreeFunctions );
  CPPUNIT_TEST( testDiamond );
  CPPUNIT_TEST_SUITE_END();

public:

  void setUp() {}

  void loadLibrary();
  void fooBarZot();
  void testBaseClasses();
  void testDataMembers();
  void testFunctionMembers();
  void testFreeFunctions();
  void testDiamond();

  void tearDown() {}

}; // class ReflexSimple2Test


// loading the dictionary library
void ReflexSimple2Test::loadLibrary() {
  //Reflex::accessArtificialMembers() = true;
  void* libInstance = 0;  
#if defined (_WIN32)
  libInstance = LoadLibrary("test_Reflex2Rflx.dll");
#else
  libInstance = dlopen("libtest_Reflex2Rflx.so", RTLD_LAZY);
#endif
  CPPUNIT_ASSERT(libInstance);
}

void ReflexSimple2Test::fooBarZot() {

  // get meta information for class foo
  Type t = Type::ByName("zot::foo");
  // generate declarations for foo
  if (t) generate_class(t);


  // get meta information of type Foo
  Type fooType = Type::ByName("zot::foo");
  CPPUNIT_ASSERT(fooType);

  // check if the type is valid
  if (fooType) {

    // 
    // Introspection
    //

    // get the name of the foo type (i.e. "Foo")
    std::string fooName = fooType.Name();
    CPPUNIT_ASSERT_EQUAL(std::string("foo"), fooName);

    // get number of base classes (i.e. 1)
    size_t fooBases = fooType.BaseSize();
    CPPUNIT_ASSERT_EQUAL(size_t(1), fooBases);
    // get first base class information
    Base fooBase = fooType.BaseAt(0);
    CPPUNIT_ASSERT(fooBase);
    // get name of first base class (i.e. "FooBase")
    std::string fooBaseName = fooBase.Name();
    CPPUNIT_ASSERT_EQUAL(std::string("foo_base"), fooBaseName);
    // check virtual inheritance (i.e. true)
    bool inheritsVirtual = fooBase.IsVirtual();
    CPPUNIT_ASSERT_EQUAL(inheritsVirtual, true);
    // check if publically inherited (i.e. true)
    bool inheritsPublic = fooBase.IsPublic();
    CPPUNIT_ASSERT_EQUAL(inheritsPublic, true);

    // get number of members (i.e. 12)
    fooType.UpdateMembers();
    size_t fooMembers = fooType.MemberSize();
    CPPUNIT_ASSERT_EQUAL(size_t(12), fooMembers);

    // get number of data members (i.e. 1)
    size_t fooDataMembers = fooType.DataMemberSize();
    CPPUNIT_ASSERT_EQUAL(size_t(1), fooDataMembers);
    // retrieve data member "fBar"
    Member dm = fooType.DataMemberByName("fBar");
    CPPUNIT_ASSERT(dm);
    // retrieve the type of this data member
    Type dmType = dm.TypeOf();
    CPPUNIT_ASSERT(dmType);
    // name of type of the data member (i.e. "int")
    std::string dmTypeName = dmType.Name();
    CPPUNIT_ASSERT_EQUAL(std::string("int"), dmTypeName);
    
    // get the function member "bar"
    Member fm = fooType.FunctionMemberByName("bar");
    CPPUNIT_ASSERT(fm);
    // name of the function member (i.e. "bar")
    std::string fmName = fm.Name();
    CPPUNIT_ASSERT_EQUAL(std::string("bar"),fmName);
    // name of type of the function member (i.e. "int (void)")
    std::string fmTypeName = fm.TypeOf().Name();
    CPPUNIT_ASSERT_EQUAL(std::string("int (void)"),fmTypeName);
    // name of return type of function member (i.e. "int")
    std::string fmReturnTypeName = fm.TypeOf().ReturnType().Name();
    CPPUNIT_ASSERT_EQUAL(std::string("int"), fmReturnTypeName);

    //
    // Interaction
    //

    // update the information for inherited members of class foo
    fooType.UpdateMembers();

    // construct an object of type Foo
    Object fooObj = fooType.Construct();
    CPPUNIT_ASSERT(fooObj);
    
    // get the value of the data member (i.e. 4711)
    int val = Object_Cast<int>(fooObj.Get("fBar"));
    CPPUNIT_ASSERT_EQUAL(4711, val);

    // set the data member to 4712
    fooObj.Set("fBar",++val);
    // get the data member again (i.e. 4712)
    val = Object_Cast<int>(fooObj.Get("fBar"));
    CPPUNIT_ASSERT_EQUAL(4712, val);

    // call function setBar with value 4713
    fooObj.Invoke("set_bar",Type::ByName("void (int)"), ++val);
    // call operator ++ to increase fBar by one
    fooObj.Invoke("operator++");
    // call bar getter and cast the output to int (i.e. 4714)
    val = Object_Cast<int>(fooObj.Invoke("bar"));
    CPPUNIT_ASSERT_EQUAL(4714, val);
    
    // delete the Foo object
    fooObj.Destruct();
    CPPUNIT_ASSERT( ! fooObj.Address() );
    CPPUNIT_ASSERT( ! fooObj );
  }

}

// testing base classes
void ReflexSimple2Test::testBaseClasses() {  
  Type t1 = Type::ByName("ClassH");
  Type t2 = Type::ByName("ClassB");
  CPPUNIT_ASSERT(t1);
  CPPUNIT_ASSERT(t2);
  CPPUNIT_ASSERT(t1.HasBase(t2));
}

// testing data members
void ReflexSimple2Test::testDataMembers() {

  Type t1;
  Object o1;

  t1 = Type::ByName("ClassH");
  CPPUNIT_ASSERT(t1);
  o1 = t1.Construct();
  CPPUNIT_ASSERT(o1);
  CPPUNIT_ASSERT_EQUAL(int(t1.DataMemberSize()), 1);
  CPPUNIT_ASSERT_EQUAL(std::string("ClassH::fH"),t1.DataMemberAt(0).Name(S));
  t1.UpdateMembers();
  CPPUNIT_ASSERT_EQUAL(int(t1.DataMemberSize()), 9);
  CPPUNIT_ASSERT_EQUAL(std::string("ClassH::fH"),t1.DataMemberAt(0).Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("ClassG::fG"),t1.DataMemberAt(1).Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("ClassF::fF"),t1.DataMemberAt(2).Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("ClassD::fD"),t1.DataMemberAt(3).Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("ClassB::fB"),t1.DataMemberAt(4).Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("ClassA::fA"),t1.DataMemberAt(5).Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("ClassM::fM"),t1.DataMemberAt(6).Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("ClassE::fE"),t1.DataMemberAt(7).Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("ClassC::fC"),t1.DataMemberAt(8).Name(S));

  Member m1;
  char val;
  int ii;

  m1 = t1.DataMemberAt(0);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('h',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('i',val);
  
  m1 = t1.DataMemberAt(1);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('g',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('h',val);
  
  m1 = t1.DataMemberAt(2);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('f',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('g',val);
  
  m1 = t1.DataMemberAt(3);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('d',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('e',val);
  
  m1 = t1.DataMemberAt(4);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('b',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('c',val);
    
  m1 = t1.DataMemberAt(5);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('a',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('b',val);
  
  m1 = t1.DataMemberAt(6);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('m',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('n',val);
  
  m1 = t1.DataMemberAt(7);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('e',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('f',val);
  
  m1 = t1.DataMemberAt(8);
  CPPUNIT_ASSERT(m1);
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('c',val);
  ++val;
  m1.Set(o1, (void*)&(ii=(int)val));
  val = (char)*(int*)m1.Get(o1).Address();
  CPPUNIT_ASSERT_EQUAL('d',val);
}

void ReflexSimple2Test::testFunctionMembers() {

  Type t;
  Scope s;
  Object o;
  Member m;
  
  t = Type::ByName("ClassH");
  CPPUNIT_ASSERT(t);
  
  o = t.Construct();
  CPPUNIT_ASSERT(o);
  
  CPPUNIT_ASSERT_EQUAL(49,int(t.FunctionMemberSize()));
  
  m = t.MemberByName("h");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT(m.DeclaringType());
  CPPUNIT_ASSERT_EQUAL(std::string("ClassH"), m.DeclaringType().Name());
  CPPUNIT_ASSERT(m.DeclaringScope());
  CPPUNIT_ASSERT_EQUAL(std::string("ClassH"), m.DeclaringScope().Name());
  CPPUNIT_ASSERT(m.DeclaringType() == (Type)m.DeclaringScope());
  CPPUNIT_ASSERT_EQUAL('h',(char)*(int*)m.Invoke(o).Address());

  m = t.MemberByName("g");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL('g',(char)*(int*)m.Invoke(o).Address());

  m = t.MemberByName("f");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL('f',(char)*(int*)m.Invoke(o).Address());

  m = t.MemberByName("d");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL('d',(char)*(int*)m.Invoke(o).Address());

  m = t.MemberByName("b");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL('b',(char)*(int*)m.Invoke(o).Address());
  
  m = t.MemberByName("a");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL('a',(char)*(int*)m.Invoke(o).Address());
  
  m = t.MemberByName("m");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL('m',(char)*(int*)m.Invoke(o).Address());

  m = t.MemberByName("e");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL('e',(char)*(int*)m.Invoke(o).Address());

  m = t.MemberByName("c");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL('c',(char)*(int*)m.Invoke(o).Address());

}

void ReflexSimple2Test::testFreeFunctions() {
  Scope s;
  Member m;
  Type t;
  std::vector<void*> vec;

  s = Scope::ByName("Functions");
  CPPUNIT_ASSERT(s);
  CPPUNIT_ASSERT_EQUAL(4,int(s.FunctionMemberSize()));

  int i = 1;
  vec.push_back((void*)&i);
  m = s.FunctionMemberAt(0);
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL(std::string("function4"),m.Name());
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name());
  CPPUNIT_ASSERT_EQUAL(11, *(int*)m.Invoke(Object(), vec).Address());

  float f = 1.0;
  vec.push_back((void*)&f);
  m = s.FunctionMemberAt(1);
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL(std::string("function3"),m.Name());
  CPPUNIT_ASSERT_EQUAL(std::string("double* (int, float)"),m.TypeOf().Name());
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0,*(double*)m.Invoke(Object(), vec).Address(),0);
                       
  m = s.FunctionMemberAt(2);
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL(std::string("function2"),m.Name());
  CPPUNIT_ASSERT_EQUAL(std::string("int (void)"),m.TypeOf().Name());
  CPPUNIT_ASSERT_EQUAL(999,*(int*)m.Invoke(Object(), std::vector<void*>()).Address());
                       
  m = s.FunctionMemberAt(3);
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL(std::string("function1"),m.Name());
  CPPUNIT_ASSERT_EQUAL(std::string("void (void)"),m.TypeOf().Name());
  Object ro = m.Invoke(Object(), std::vector<void*>());
  CPPUNIT_ASSERT(!ro);
                       
  t = Type::ByName("ClassAAA");
  CPPUNIT_ASSERT(t);
  CPPUNIT_ASSERT_EQUAL(3,int(t.MemberSize()));
  CPPUNIT_ASSERT_EQUAL(3,int(t.FunctionMemberSize()));
  CPPUNIT_ASSERT_EQUAL(0,int(t.DataMemberSize()));
  m = t.MemberByName("function6");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL(std::string("function6"),m.Name());
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name());

  s = t.DeclaringScope();
  CPPUNIT_ASSERT(s);
  CPPUNIT_ASSERT_EQUAL(0,int(s.DataMemberSize()));
  CPPUNIT_ASSERT_EQUAL(7,int(s.FunctionMemberSize()));
  m = s.MemberByName("function5");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL(std::string("function5"),m.Name());
  CPPUNIT_ASSERT_EQUAL(std::string("function5"),m.Name(SCOPED));
  CPPUNIT_ASSERT_EQUAL(std::string("int (MYINT)"),m.TypeOf().Name());
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(FINAL));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(SCOPED|FINAL));

  t = Type::ByName("ClassBBB");
  CPPUNIT_ASSERT(t);
  CPPUNIT_ASSERT_EQUAL(3, int(t.MemberSize()));
  m = t.MemberByName("meth");
  CPPUNIT_ASSERT(m);
  CPPUNIT_ASSERT_EQUAL(std::string("ClassBBB::meth"),m.Name(SCOPED));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name());
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(SCOPED));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(FINAL));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(QUALIFIED));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(SCOPED | FINAL));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(SCOPED | QUALIFIED));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(SCOPED | QUALIFIED | FINAL));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(S));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(F));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(Q));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(S | F));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(S | Q));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(S | Q | F));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(SCOPED | S));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(FINAL | F));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(QUALIFIED | Q));
  CPPUNIT_ASSERT_EQUAL(std::string("int (int)"),m.TypeOf().Name(SCOPED | QUALIFIED | FINAL | S | Q | F));

}


void ReflexSimple2Test::testDiamond() {
  Type b = Type::ByName("Bla::Base");
  Type d = Type::ByName("Bla::Diamond");
  Type l = Type::ByName("Bla::Left");
  Type r = Type::ByName("Bla::Right");

  CPPUNIT_ASSERT(b);
  CPPUNIT_ASSERT(d);
  CPPUNIT_ASSERT(l);
  CPPUNIT_ASSERT(r);

  Type s = Type::ByName("void (void)");
  CPPUNIT_ASSERT(s);
  
  std::vector<void*> values;

  Member m = b.MemberAt(0);
  CPPUNIT_ASSERT(m);
  
  Object o = d.Construct(s,values);
  CPPUNIT_ASSERT(o);
  CPPUNIT_ASSERT(*(int*)m.Get(o).Address());

  o = l.Construct(s,values);
  CPPUNIT_ASSERT_EQUAL(std::string("Base"),l.BaseAt(0).Name());
  CPPUNIT_ASSERT_EQUAL(std::string("public virtual Base"), l.BaseAt(0).Name(Q));
  CPPUNIT_ASSERT_EQUAL(99,*(int*)m.Get(o).Address());
  l.UpdateMembers();
  CPPUNIT_ASSERT_EQUAL(99,*(int*)m.Get(o).Address());
}

// Class registration on cppunit framework
CPPUNIT_TEST_SUITE_REGISTRATION(ReflexSimple2Test);

// CppUnit test-driver common for all the cppunit test classes 
#include<CppUnit_testdriver.cpp>


#include <iostream>
#include "Reflex/Reflex.h"
#include "myobj.h"

void test()
{
  using namespace ROOT::Reflex;
  
  Type t = Type::ByName("MyObj");
  if ( t ) {
    if ( t.IsClass()) std::cout << "We found a class type" << std::endl;
    if (t.TypeType() == CLASS) std::cout << "This is still a class" << std::endl;
  }
  
  for (Member_Iterator mi = t.Member_Begin(); mi != t.Member_End(); ++mi) {
    Member m = *mi;
    switch (m.MemberType()) {
      case DATAMEMBER     : std::cout << "Datamember: " << m.Name() << " at offset " << m.Offset() << std::endl; break;
      case FUNCTIONMEMBER : std::cout << "Functionmember: " << m.Name() << " has " << m.FunctionParameterSize() << " parameters " << std::endl; break;
      default             : std::cout << "This should never happen" << std::endl; break;
  }
}
  Object o = t.Construct();
  //o.Destruct();
  
  Member dm = t.DataMemberAt(0);
  std::cout << "Data member " << dm.Name() << " is of type " << dm.TypeOf().Name() << std::endl;
  int i = Object_Cast<int>(dm.Get(o));
  ++i;
  dm.Set(o,&i);

  Member fm = t.FunctionMemberAt(0);
  if (fm.TypeOf().ReturnType().Name() != "void" && fm.FunctionParameterSize() == 0) Object o = fm.Invoke(o);
  
  Scope s = Scope::ByName("MyObj");
  if ( s.DeclaringScope().IsTopScope()) {
    std::cout << "Scope " << s.Name() << " is part of the top scope and has " 
      << s.SubScopeSize() << " sub scopes " << std::endl;
  }
  
  PropertyList p = s.Properties();
  if (p.HasProperty("Author")) std::cout << "The author of class " << s.Name() << " is " << p.PropertyAsString("Author") << std::endl;
}

int main()
{
  std::cout << "hello world" << std::endl;
  test();
  return 0;
}

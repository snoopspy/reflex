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
  o.Destruct();
}

int main()
{
  std::cout << "hello world" << std::endl;
  test();
  return 0;
}

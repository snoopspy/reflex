#include <iostream>
#include "myobj.h"

MyObj::MyObj()
{
  std::cout << "MyObj::MyObj  " << (void*)this << std::endl;
}

MyObj::~MyObj()
{
  std::cout << "MyObj::~MyObj " << (void*)this << std::endl;
}

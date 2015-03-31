#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>

namespace sc {
  class person
  {
  public:
    person();
    ~person();

    std::string name;
    int age;
  };
}

#endif // __PERSON_H__

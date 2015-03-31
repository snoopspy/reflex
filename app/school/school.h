#ifndef __SCHOOL_H__
#define __SCHOOL_H__

#include <list>
#include "teacher.h"
#include "student.h"

namespace sc {
  class school {
  public:
    school();
    ~school();

    std::list<std::string> teachers;
    std::list<std::string> students;
  };
}

#endif // __SCHOOL_H__

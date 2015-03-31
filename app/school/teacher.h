#ifndef __TEACHER_H__
#define __TEACHER_H__

#include "person.h"

namespace school {
  class teacher : public person {
  public:
    teacher();
    ~teacher();

    int id;
    std::string subject;
  };
}

#endif // __TEACHER_H__

#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "person.h"

namespace school {
  class student : public person {
  public:
    student();
    ~student();

    int grade;
    int group;
    int no;
    int teacher_id;
  };
}

#endif // __STUDENT_H__

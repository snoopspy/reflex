#include "Reflex/Builder/DictSelection.h"

int m_foo;

enum XYZ { X, Y, Z };

int foosq (int i) { return i*i; }

namespace ROOT {
  namespace Reflex {
    namespace Selection {

      void * m_foo;

      int foosq(int);

      enum XYZ {};

      class ClassA {
        TRANSIENT fA;
      };
    }
  }
}

#include <vector>
#include <utility>

namespace ns {

  int m_foo2;

  enum ABC { A, B, C };

  int fooadd (int i) { return i+i; }

  class TestSelectionClass {
  private:
    int fI;
    float fF;
    int foo(bool b, char c) { if (b) return c; }
    std::vector<std::pair<int,float> > fV;
  };


  template < typename T0, typename T1, typename T2 = float >
    class TestTemplatedSelectionClass {
    private:
    int fI;
  };

  class AutoSelectClass {};

  class NoSelfAutoSelection {
  private:
    AutoSelectClass m_c;
  };

}



namespace ROOT {
  namespace Reflex {
    namespace Selection {

      namespace ns {

        void * m_foo2;

        enum ABC {};

        int fooadd(int);

        class NoSelfAutoSelection {
          NO_SELF_AUTOSELECT m_whatever;
          AUTOSELECT m_c;
        };

        class TestSelectionClass {
          TRANSIENT  fI;
          AUTOSELECT fV;
        };

        template < typename T0, typename T1, typename T2 = float > class TestTemplatedSelectionClass {
          ::ns::TestTemplatedSelectionClass<T0,T1,T2>      fInstance;
          TEMPLATE_DEFAULTS<NODEFAULT,NODEFAULT,float> fDefaults;
        };
      }

    }
  }
}


namespace {

  struct _Instantiations {

    ROOT::Reflex::Selection::ns::TestTemplatedSelectionClass<int,int>      fI4;
    ROOT::Reflex::Selection::ns::TestTemplatedSelectionClass<float,float>  fI5;
    ROOT::Reflex::Selection::ns::TestTemplatedSelectionClass<int,int,bool> fI6;
    ROOT::Reflex::Selection::ns::TestTemplatedSelectionClass<int,int,char> fI7;

  };

}

// -*- mode: C++ -*-

#ifndef TAB_COMPLEX_H_INCLUDED_
#define TAB_COMPLEX_H_INCLUDED_

#include <ostream>
#include "complex.h"

class tab_complex {
public:
  tab_complex();
  friend std::ostream& operator<<(std::ostream&, const tab_complex&);
  
private:
  complex _tab_c[10];
};

std::ostream& operator<<(std::ostream&, const tab_complex&);

#endif

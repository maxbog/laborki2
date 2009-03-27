#include "tab_complex.h"

tab_complex::tab_complex() {
  for(int i = 0; i < 10; ++i) {
    _tab_c[i]=complex(i,i);
  }
}

std::ostream& operator <<(std::ostream& os, const tab_complex& tc) {
  for(int t = 0; t < 10; ++t) {
    for(int i = 0; i < 4; ++i) {
      complex::fun_wsk_t fun = tc._tab_c[t].tab_wsk_fun[i] ;
      os << (tc._tab_c[t].*fun)() << std::endl;
    }
  }
  return os;
}

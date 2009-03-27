#include <cmath>

#include "complex.h"

complex::complex()
  : _im(0), _re(0) {
  init_tab();
}

complex::complex(const complex& inna)
  : _im(inna._im), _re(inna._re) {
  init_tab();
}

complex::complex(double re, double im)
  : _im(im), _re(re) {
  init_tab();
}

double complex::fun1() const {
  return _re;
}

double complex::fun2() const {
  return _im;
}

double complex::fun3() const {
  return _re * _re + _im * _im;
}

double complex::fun4() const {
  return sqrt(_re * _re + _im * _im);
}


void complex::init_tab() {
  tab_wsk_fun[0] = &complex::fun1;
  tab_wsk_fun[1] = &complex::fun2;
  tab_wsk_fun[2] = &complex::fun3;
  tab_wsk_fun[3] = &complex::fun4;
}

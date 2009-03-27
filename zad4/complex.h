// -*- mode: C++ -*-
#ifndef COMPLEX_H_INCLUDED_
#define COMPLEX_H_INCLUDED_

class complex {
public:
  complex();
  complex(const complex&);
  complex(double re, double im);

  double fun1() const;
  double fun2() const;
  double fun3() const;
  double fun4() const;

  typedef double(complex::*fun_wsk_t)() const;
  
  fun_wsk_t tab_wsk_fun[4];
private:
  void init_tab();
  
  double _im;
  double _re;
};

#endif

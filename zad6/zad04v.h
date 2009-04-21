// -*- mode: C++ -*-

#ifndef ZAD04V_H_INCLUDED_
#define ZAD04V_H_INCLUDED_

#include <iostream>

class vect {
public:
  vect();
  vect(const vect& rhs);
  vect(double* tab, unsigned dl);
  vect(unsigned dl);
  ~vect();

  vect& operator =(const vect& rhs);
  double& operator [](unsigned index);
  double operator [](unsigned index) const;

  unsigned get_size();
  void set_size(unsigned size);

  void dodaj(double nowy);

  friend bool operator ==(const vect& lhs, const vect& rhs);
  friend bool operator !=(const vect& lhs, const vect& rhs);

  friend std::istream& operator >>(std::istream& in, vect& v);
  friend std::ostream& operator <<(std::ostream& out, const vect& v);  
protected:
  unsigned dlugosc;
  double* dane;
};

bool operator ==(const vect& lhs, const vect& rhs);
bool operator !=(const vect& lhs, const vect& rhs);

std::istream& operator >>(std::istream& in, vect& v);
std::ostream& operator <<(std::ostream& out, const vect& v);

#endif

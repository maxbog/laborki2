// -*- mode: C++ -*-

#ifndef ZAD04SV_H_INCLUDED_
#define ZAD04SV_H_INCLUDED_

#include "zad04v.h"

template <typename T>
class proxy;
template <typename T>
class constproxy;

class svect : public vect {
public:
  svect();
  svect(const vect& rhs);
  svect(double* tab, unsigned dl);
  svect(unsigned dl);

  proxy<double> operator [](unsigned index);
  constproxy<double> operator [](unsigned index) const;

  vect& operator =(const vect& rhs);

  void dodaj(double nowy);

  friend std::istream& operator >>(std::istream& in, svect& v);
  
  friend class proxy<double>;
  friend class constproxy<double>;
private:
  void sort();
};

std::istream& operator >>(std::istream& in, svect& v);

template <typename T>
class proxy {
public:
  proxy(svect* v, unsigned el)
    :vect(v),elem(el),wczytane(false) {
  }
  
  operator T() {
    if(wczytane) {
      return wcz_wart;
    } else {
      return vect->dane[elem];
    }
  }
    
  proxy<T>& operator =(const T& rhs) {
    vect->dane[elem] = rhs;
    wczytane = true;
    wcz_wart = rhs;
    vect->sort();
    return *this; 
  }
  
private:
  svect* vect;
  unsigned elem;
  bool wczytane;
  double wcz_wart;
};

template <typename T>
class constproxy {
public:
  constproxy(const svect* v, unsigned el)
    :vect(v),elem(el) {
  }
  
  operator T() {
    return vect->dane[elem];
  }
  
private:
  const svect* vect;
  unsigned elem;
};



#endif

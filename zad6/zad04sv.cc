#include "zad04sv.h"
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <sstream>

svect::svect()
  : vect() {
}

svect::svect(const vect& rhs)
  : vect(rhs) {
  sort();
}

svect::svect(double* tab, unsigned dl)
  : vect(tab,dl) {
  sort();
}

svect::svect(unsigned dl)
  : vect(dl) {
}

vect& svect::operator =(const vect& rhs) {
  vect::operator =(rhs);
  sort();
  return *this;
}


proxy<double> svect::operator [](unsigned index) {
  if(index >= dlugosc) {
    throw std::out_of_range("Indeks poza tablica!");
  }
  sort(); // jest to niestety konieczne, gdyz c++ nie rozroznia operatora [] i []=
  return proxy<double>(this,index);
}

constproxy<double> svect::operator [](unsigned index) const {
  if(index >= dlugosc) {
    throw std::out_of_range("Indeks poza tablica!");
  }
  return constproxy<double>(this,index);
}

void svect::dodaj(double nowy) {
  vect::dodaj(nowy);
  sort();
}

int double_cmp(const void* elem1, const void* elem2) {
  double e1 = *((double*)elem1);
  double e2 = *((double*)elem2);

  if(std::fabs(e1-e2) < std::numeric_limits<double>::epsilon()) {
    return 0;
  } else if(e1 < e2) {
    return -1;
  } else {
    return 1;
  }
}

void svect::sort() {
  if(!dane) {
    return;
  }

  qsort(dane,dlugosc,sizeof(double),double_cmp);
}


std::istream& operator >>(std::istream& in, svect& v) {
  std::string line;
  unsigned dl;
  getline(in,line);
  line.erase(0,1);
  line.erase(line.length()-1,1);
  std::istringstream iss(line);
  iss >> dl;
  v.set_size(dl);
  for(unsigned i=0;i<dl;++i) {
    iss >> v.dane[i];
  }
  v.sort();
  return in;
}

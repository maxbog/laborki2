#include "zad04v.h"
#include <cstdlib>
#include <stdexcept>
#include <cctype>
#include <cstring>
#include <string>
#include <sstream>

vect::vect()
  : dlugosc(0), dane(0) {
}

vect::vect(const vect& rhs)
  : dlugosc(rhs.dlugosc) {
  dane = new double[dlugosc];
  std::memcpy(dane, rhs.dane, dlugosc * sizeof(double));
}

vect::vect(double* tab, unsigned dl)
  : dlugosc(dl) {
  dane = new double[dlugosc];
  std::memcpy(dane, tab, dlugosc * sizeof(double));
}

vect::vect(unsigned dl)
  : dlugosc(dl) {
  dane = new double[dlugosc];
  for(unsigned i = 0; i < dlugosc; ++i) {
    dane[i] = 0;
  }
}

vect::~vect() {
  if(dane) {
    delete [] dane;
  }
}

vect& vect::operator =(const vect& rhs) {
  if(dane) {
    delete [] dane;
  }

  dlugosc = rhs.dlugosc;
  dane = new double[dlugosc];
  std::memcpy(dane, rhs.dane, dlugosc * sizeof(double));
  
  return *this;
}

double& vect::operator [](unsigned index) {
  if(index >= dlugosc) {
    throw std::out_of_range("Indeks poza tablica!");
  }
  return dane[index];
}

double vect::operator [](unsigned index) const {
  if(index >= dlugosc) {
    throw std::out_of_range("Indeks poza tablica!");
  }
  return dane[index];
}

unsigned vect::get_size() {
  return dlugosc;
}

void vect::set_size(unsigned size) {
  double* nowe_dane = new double[size];
  if(dane) {
    std::memcpy(nowe_dane, dane, std::min(size, dlugosc) * sizeof(double));
    delete [] dane;
  }
  
  for(unsigned i = dlugosc; i < size; ++i) {
    nowe_dane[i]=0;
  }
  
  dane = nowe_dane;
  dlugosc = size;
}

void vect::dodaj(double nowy) {
  double* nowe_dane = new double[dlugosc+1];
  if(dane) {
    std::memcpy(nowe_dane, dane, dlugosc * sizeof(double));
    delete [] dane;
  }
  dane = nowe_dane;
  dane[dlugosc++] = nowy;
}
  
bool operator ==(const vect& lhs, const vect& rhs) {
  if(&lhs == &rhs) {
    return true;
  }
  
  if(lhs.dlugosc != rhs.dlugosc) {
    return false;
  }

  for(unsigned i = 0; i < lhs.dlugosc; ++i) {
    if(lhs[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

bool operator !=(const vect& lhs, const vect& rhs) {
  return !(lhs == rhs);
}

std::istream& operator >>(std::istream& in, vect& v) {
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
  return in;
}

std::ostream& operator <<(std::ostream& out, const vect& v) {
  out << '[';
  out << v.dlugosc;
  for(unsigned i = 0; i < v.dlugosc; ++i) {
    out << ' ' << v[i];
  }
  out << ']';
  return out;
}

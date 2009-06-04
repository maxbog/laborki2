// -*- mode: C++ -*-

#ifndef TOWAR_H_INCLUDED_
#define TOWAR_H_INCLUDED_

#include "wektor.h"

#include <string>
#include <iostream>

class towar {
public:
  towar();
  towar(const std::string& nazwa);
  towar(const towar& rhs);

  const std::string& nazwa() const;
  std::string& nazwa();

  const wektor<double>& ceny() const;
  wektor<double>& ceny();

  const wektor<std::string>& sklepy() const ;
  wektor<std::string>& sklepy();

  friend std::istream& operator >>(std::istream& in, towar& tow);
  friend std::ostream& operator <<(std::ostream& out, const towar& tow);
  bool operator ==(const towar& rhs);

  static towar PUSTY;
private:
  std::string _nazwa;
  wektor<double> _ceny;
  wektor<std::string> _sklepy; 
};

std::istream& operator >>(std::istream& in, towar& tow);
std::ostream& operator <<(std::ostream& out, const towar& tow);

#endif

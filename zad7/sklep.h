// -*- mode: C++ -*-

#ifndef SKLEP_H_INCLUDED_
#define SKLEP_H_INCLUDED_

#include "wektor.h"
#include <string>
#include <iostream>

class sklep {
public:
  sklep();
  sklep(const sklep& rhs);
  sklep(const std::string& nazwa);

  const std::string& nazwa() const;
  std::string& nazwa();

  const wektor<std::string>& adresy() const;
  wektor<std::string>& adresy();

  friend std::istream& operator >>(std::istream& in, sklep& skl);
  friend std::ostream& operator <<(std::ostream& out, const sklep& skl);
  bool operator ==(const sklep& rhs);

  static sklep PUSTY;
  
private:
  std::string _nazwa;
  wektor<std::string> _adresy;
};

std::istream& operator >>(std::istream& in, sklep& skl);
std::ostream& operator <<(std::ostream& out, const sklep& skl);


#endif

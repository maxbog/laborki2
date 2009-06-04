#include "sklep.h"
#include "baza_sklepow.h"

using namespace std;

sklep::sklep()
  : _nazwa("SKLEP_BEZ_NAZWY"), _adresy(0) {
  
}

sklep::sklep(const sklep& rhs)
  : _nazwa(rhs._nazwa), _adresy(rhs._adresy) {
  
}

sklep::sklep(const std::string& nazwa)
  : _nazwa(nazwa), _adresy() {
}

const std::string& sklep::nazwa() const {
  return _nazwa;
}

std::string& sklep::nazwa() {
  return _nazwa;
}

const wektor<std::string>& sklep::adresy() const {
  return _adresy;
}

wektor<std::string>& sklep::adresy() {
  return _adresy;
}

bool sklep::operator ==(const sklep& rhs) {
  if(this == &rhs) {
    return true;
  }
  return _nazwa == rhs._nazwa && _adresy == rhs._adresy;
}
  
std::istream& operator >>(std::istream& in, sklep& skl) {
  in >> skl._nazwa;
  string adres;
  in >> adres;
  skl._adresy.dodaj(adres);
  return in;
}

std::ostream& operator <<(std::ostream& out, const sklep& skl) {
  for(unsigned i = 0; i < skl._adresy.ilosc(); ++i) {
    out << skl._nazwa << " " << skl._adresy[i] << std::endl;
  }
  return out;
}

sklep sklep::PUSTY;

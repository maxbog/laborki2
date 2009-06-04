#include "towar.h"
#include "baza_towarow.h"
#include "baza_sklepow.h"
#include "sklep.h"

using namespace std;

towar::towar()
  : _nazwa("TOWAR_BEZ_NAZWY"), _sklepy() {
}

towar::towar(const std::string& nazwa)
  : _nazwa(nazwa), _sklepy() {
}

towar::towar(const towar& rhs) 
  : _nazwa(rhs._nazwa), _ceny(rhs._ceny), _sklepy(rhs._sklepy) {
}

const std::string& towar::nazwa() const {
  return _nazwa;
}

std::string& towar::nazwa() {
  return _nazwa;
}

const wektor<double>& towar::ceny() const {
  return _ceny;
}

wektor<double>& towar::ceny() {
  return _ceny;
}

const wektor<std::string>& towar::sklepy() const {
  return _sklepy;
}

wektor<std::string>& towar::sklepy() {
  return _sklepy;
}

bool towar::operator ==(const towar& rhs) {
  if(this == &rhs) {
    return true ;
  }
  
  return _nazwa == rhs._nazwa && _sklepy == rhs._sklepy && _ceny == rhs._ceny;
}

std::istream& operator >>(std::istream& in, towar& tow) {
  in >> tow._nazwa;
  string skl;
  double cena;
  in >> skl >> cena;
  tow._sklepy.dodaj(skl);
  tow._ceny.dodaj(cena);
  return in;
}

std::ostream& operator <<(std::ostream& out, const towar& tow) {
  for(unsigned i = 0; i < tow._sklepy.ilosc(); ++i) {
    cout << tow._nazwa << " " << tow._ceny[i] << " " << tow._sklepy[i] << endl;
  }
  return out;
}

towar towar::PUSTY;

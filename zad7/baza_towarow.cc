#include "baza_towarow.h"

baza_towarow::baza_towarow()
  : _dane() {
}

const towar& baza_towarow::znajdz_po_nazwie(const std::string& nazwa) const {
  for(unsigned i = 0; i < _dane.ilosc(); ++i) {
    if(_dane[i].nazwa() == nazwa) {
      return _dane[i];
    }
  }
  return towar::PUSTY;
}

towar& baza_towarow::znajdz_po_nazwie(const std::string& nazwa) {
  for(unsigned i = 0; i < _dane.ilosc(); ++i) {
    if(_dane[i].nazwa() == nazwa) {
      return _dane[i];
    }
  }
  return towar::PUSTY;
}
wektor<towar> baza_towarow::znajdz_po_cenie(double cena_min,double cena_max) {
  wektor<towar> wynik;
  for(unsigned i = 0; i < _dane.ilosc(); ++i) {
    for(unsigned j = 0; j < _dane[i].ceny().ilosc(); ++j) {
      if(_dane[i].ceny()[j] >= cena_min && _dane[i].ceny()[j] <= cena_max) {
	wynik.dodaj(_dane[i]);
	break;
      }
    }
  }
  return wynik;
}

void baza_towarow::dodaj(const towar& tow) {
  towar& znaleziony = znajdz_po_nazwie(tow.nazwa());
  if(znaleziony == towar::PUSTY) {
    _dane.dodaj(tow);
  } else {
    znaleziony.ceny().dodaj(tow.ceny()[0]);
    znaleziony.sklepy().dodaj(tow.sklepy()[0]);
  }
}

const wektor<towar>& baza_towarow::wszystkie() const {
  return _dane;
}
wektor<towar>& baza_towarow::wszystkie() {
  return _dane;
}

baza_towarow& baza_towarow::singleton() {
  if(!_singleton) {
    _singleton = new baza_towarow;
  }
  return *_singleton;
}

baza_towarow* baza_towarow::_singleton = 0;

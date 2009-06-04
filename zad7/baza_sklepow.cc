#include "baza_sklepow.h"

#include <vector>
#include <algorithm>

using namespace std;

baza_sklepow::baza_sklepow()
  : _dane() {  
}

sklep& baza_sklepow::znajdz_po_nazwie(const string& nazwa) {
  for(unsigned i = 0; i < _dane.ilosc(); ++i) {
    if(_dane[i].nazwa() == nazwa) {
      return _dane[i];
    }
  }
  return sklep::PUSTY;
}

const sklep& baza_sklepow::znajdz_po_nazwie(const string& nazwa) const {
  for(unsigned i = 0; i < _dane.ilosc(); ++i) {
    if(_dane[i].nazwa() == nazwa) {
      return _dane[i];
    }
  }
  return sklep::PUSTY;
}

void baza_sklepow::dodaj(const sklep& skl) {
  sklep& znaleziony = znajdz_po_nazwie(skl.nazwa());
  cout << "1:" << skl;
  cout << "2:" << znaleziony;
  cout << "4:" << _dane;
  if(znaleziony == sklep::PUSTY) {
    _dane.dodaj(skl);
  } else {
    cout << "3:" << skl.adresy()[0] << endl;
    znaleziony.adresy().dodaj(skl.adresy()[0]);
  }
}

baza_sklepow& baza_sklepow::singleton() {
  if(!_singleton) {
    _singleton = new baza_sklepow;
  }
  return *_singleton;
}

const wektor<sklep>& baza_sklepow::wszystkie() const {
  return _dane;
}

wektor<sklep>& baza_sklepow::wszystkie() {
  return _dane;
}


baza_sklepow* baza_sklepow::_singleton = 0;

// -*- mode: C++ -*-

#ifndef BAZA_TOWAROW_H_INCLUDED_
#define BAZA_TOWAROW_H_INCLUDED_

#include "wektor.h"
#include "towar.h"

class baza_towarow {
public:
  const towar& znajdz_po_nazwie(const std::string& nazwa) const;
  towar& znajdz_po_nazwie(const std::string& nazwa);  
  wektor<towar> znajdz_po_cenie(double cena_min,double cena_max);
  void dodaj(const towar& tow);
  
  const wektor<towar>& wszystkie() const;
  wektor<towar>& wszystkie();

  static baza_towarow& singleton();
private:
  baza_towarow();
  wektor<towar> _dane;
  static baza_towarow* _singleton;
};

#endif

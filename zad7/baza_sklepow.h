// -*- mode: C++ -*-

#ifndef BAZA_SKLEPOW_H_INCLUDED_
#define BAZA_SKLEPOW_H_INCLUDED_

#include "wektor.h"
#include "sklep.h"
#include <iostream>
#include <string>

class baza_sklepow {
public:
  sklep& znajdz_po_nazwie(const std::string& nazwa);
  const sklep& znajdz_po_nazwie(const std::string& nazwa) const;

  void dodaj(const sklep& skl);

  const wektor<sklep>& wszystkie() const;
  wektor<sklep>& wszystkie();

  static baza_sklepow& singleton();
  
private:
  baza_sklepow();
  wektor<sklep> _dane;
  static baza_sklepow* _singleton;
};

#endif

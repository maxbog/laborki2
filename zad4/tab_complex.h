// -*- mode: C++ -*-
/**
 * @file tab_complex.h
 * @author Maksymilian Boguń
 * @date 29-3-2009
 */
#ifndef TAB_COMPLEX_H_INCLUDED_
#define TAB_COMPLEX_H_INCLUDED_

#include <ostream>
#include "complex.h"

/**
 * Klasa reprezentuje tablicę 10 liczb zespolonych.
 */
class tab_complex {
public:
  /**
   * Konstruktor domyślny. Wypełnia tablicę przykładowymi liczbami zespolonymi.
   */
  tab_complex();
  
  friend std::ostream& operator<<(std::ostream&, const tab_complex&);
  
private:
  complex _tab_c[10];
};

/**
 * Standardowy operator wypisania tabliczy liczb zespolonych do strumienia.
 * Wypisuje wszystkie liczby i rezultaty wywołania funkcji fun1-fun4 po kolei.
 *
 * @param os Strumień, na który zostanie wypisana tablicz liczb.
 * @param tc Tablica liczb, która zostanie wypisana.
 * @return Strumień po wypisaniu tablicy liczb.
 */
std::ostream& operator<<(std::ostream& os, const tab_complex& tc);

#endif

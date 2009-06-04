// -*- mode: C++ -*-

#ifndef WEKTOR_H_INCLUDED_
#define WEKTOR_H_INCLUDED_

#include <cstring>
#include <stdexcept>
#include <iostream>


template <typename T>
class wektor;
template <typename T>
std::istream& operator >>(std::istream& in, wektor<T>& wekt);
template <typename T>
std::ostream& operator <<(std::ostream& out, const wektor<T>& wekt);

/**
 * Klasa reprezentuje wektor obiektów dowolnego typu. Jedynym wymaganiem dla typu jest obecność operatora =, operatora == i konstruktora kopiującego.
 * Wektor jest automatycznie powiększany, gdy zabraknie miejsca na nowe elementy.
 */
template <typename T>
class wektor {
public:
  /**
   * Konstruktor domyślny. Tworzy wektor o rozmiarze określonym przez stałą.
   */
  wektor()
    : _rozmiar(_powiekszenie), _zapelnione(0) {

    _dane = new T[_rozmiar];
  }

  /**
   * Konstruktor tworzący wektor o określonym rozmiarze.
   * Obiekty są konstruowane używająk konstruktora domyślnego.
   *
   * @param rozmiar Rozmiar nowo stworzonego wektora.
   */
  wektor(unsigned rozmiar)
    : _dane(0), _rozmiar(rozmiar), _zapelnione(0) {
    
    if(_rozmiar > 0) {
      _dane = new T[_rozmiar];
    }
  }

  /**
   * Konstruktor kopiujący. Tworzy "głęboką" kopię wektora - wszystkie dane są kopiowane jako obszar pamięci.
   *
   * @param rhs Wektor, który zostanie skopiowany.
   */
  wektor(const wektor<T>& rhs)
    : _dane(0), _rozmiar(rhs._zapelnione), _zapelnione(rhs._zapelnione) {

    if(_zapelnione > 0) {
      _dane = new T[_zapelnione];
      std::memcpy(_dane, rhs._dane, _zapelnione*sizeof(T));
    }
  }

  /**
   * Destruktor. Usuwa dane z pamięci.
   */
  ~wektor() {
    if(_dane) {
      delete [] _dane;
      _dane = 0;
    }
  }

  
  /**
   * Dodaje nowy element na koniec wektora.
   *
   * @param nowy Element, który zostanie dodany.
   */
  void dodaj(const T& nowy) {
    if(_zapelnione == _rozmiar) {
      powieksz();
    }
    _dane[_zapelnione++] = nowy;
  }

  /**
   * Wstawia nowy element przed podaną pozycją.
   *
   * @param nowy Element, który zostanie wstawiony.
   * @param gdzie Indeks elementu, przed który nowy element zostanie wstawiony.
   * @throw std::out_of_range Rzucany, gdy element o takim indeksie nie występuje w wektorze.
   */
  void dodaj(const T& nowy, unsigned gdzie) {
    if(gdzie >= _zapelnione) {
      throw std::out_of_range("Wektor nie ma takiego elementu!");
    }
    if(_zapelnione == _rozmiar) {
      powieksz();
    }
    
    for(unsigned i = gdzie; i + 1 < _zapelnione; ++i) {
      _dane[i+1] = _dane[i];
    }
    _dane[gdzie] = nowy;
    ++_zapelnione;
  }

  /**
   * Usuwa podany element z wektora.
   *
   * @param gdzie Element, który zostanie usunięty.
   * @throw std::out_of_range Rzucany, gdy element o takim indeksie nie występuje w wektorze.
   */
  void usun(unsigned gdzie) {
    if(gdzie >= _zapelnione) {
      throw std::out_of_range("Wektor nie ma takiego elementu!");
    }

    for(unsigned i = gdzie; i + 1 < _zapelnione; ++i) {
      _dane[i] = _dane[i+1];
    }
    --_zapelnione;
  }

  /**
   * Zwraca ilość elementów w wektorze.
   *
   * @return Ilość elementu w wektorze.
   */
  unsigned ilosc() const {
    return _zapelnione;
  }

  /**
   * Czyści wektor z wszystkich elementów. Długość wektora ustawiana jest na 0.
   */
  void oproznij() {
    if(_dane) {
      delete [] _dane;
    }
    _rozmiar = _zapelnione = 0;
  }

  /**
   * Zmienia rozmiar wektora. Nie oznacza to, że nagle pojawią się w nim nowe obiekty.
   *
   * @param nowy_rozmiar Nowy rozmiar wektora.
   */
  void zmien_rozmiar(unsigned nowy_rozmiar) {
    if(nowy_rozmiar == 0) {
      delete [] _dane;
      _dane = 0;
      _rozmiar = _zapelnione = 0;
    }

    T* nowe_dane = new T[nowy_rozmiar];
    if(_rozmiar > 0) {
      std::memcpy(nowe_dane, _dane, std::min(_rozmiar, nowy_rozmiar)*sizeof(T));
    }
    delete [] _dane;
    _dane = 0;
    _dane = nowe_dane;
    _rozmiar = nowy_rozmiar;
    _zapelnione = std::min(nowy_rozmiar, _zapelnione);
  }

  /**
   * Standardowy operator przypisania.
   * Wykonuje głęboką kopię wektora, obiekty kopiowane są jako obszar pamięci.
   *
   * @param rhs Wektor, który zostanie przypisany.
   * @return Ten wektor po przypisaniu.
   */
  wektor<T>& operator =(const wektor<T>& rhs) {
    if(_dane) {
      delete [] _dane;
    }

    if(rhs._rozmiar == 0) {
      _dane = 0;
      _rozmiar = _zapelnione = 0;
    }

    _dane = new T[rhs._rozmiar];
    _rozmiar = rhs._rozmiar;
    _zapelnione = rhs._zapelnione;
    std::memcpy(_dane, rhs._dane,_zapelnione*sizeof(T));    
    
    return *this;
  }

  /**
   * Standardowy operator dostępu do danych.
   * Umożliwia modyfikację danych.
   *
   * @param poz Indeks elementu w wektorze, który zostanie zwrócony.
   * @throw std::out_of_range Rzucany, gdy element  o podanym indeksie nie znajduje się w wektorze.
   * @return Element o indeksie poz
   */
  T& operator[](unsigned poz) {
    if(poz >= _zapelnione) {
      throw std::out_of_range("Wektor nie ma takiego elementu");
    }
    return _dane[poz];
  }

  /**
   * Standardowy operator dostępu do danych.
   * Uniemożliwia modyfikację danych.
   *
   * @param poz Indeks elementu w wektorze, który zostanie zwrócony.
   * @throw std::out_of_range Rzucany, gdy element  o podanym indeksie nie znajduje się w wektorze.
   * @return Element o indeksie poz
   */
  const T& operator[](unsigned poz) const{
    if(poz >= _zapelnione) {
      throw std::out_of_range("Wektor nie ma takiego elementu");
    }
    return _dane[poz];
  }

  /**
   * Standardowy operator ==.
   * Równa musi być ilość elementów i same elemtenty.
   *
   * @param wekt Porównywany wektor
   * @return true, jeśli wektory są takie same, w przeciwnym wypadku false.
   */
  bool operator ==(const wektor<T>& rhs) const {
    if(this == &rhs) {
      return true;
    }
    if(_zapelnione != rhs._zapelnione) {
      return false;
    }

    for(unsigned i = 0; i < _zapelnione; ++i) {
      if(_dane[i] != rhs._dane[i]) {
	return false;
      }
    }
    return true;
  }

  /**
   * Wyszukuje element w wektorze i zwraca jego indeks. Jesli element nie zostanie znaleziony, zwraca -1.
   *
   * @param wzor Element do znalezienia
   * @return Indeks znalezionego elementu, lub -1, gdy elementu nie ma w tablicy.
   */
  int znajdz(const T& wzor) {
    for(unsigned i = 0;i < _zapelnione; ++i) {
      if(_dane[i] == wzor)
	return i;
    }
    return -1;
  }

  friend std::istream& operator >> <>(std::istream& in, wektor<T>& wekt);
  friend std::ostream& operator << <>(std::ostream& out, const wektor<T>& wekt);
  
private:
  void powieksz() {
    unsigned nowy_rozmiar = _rozmiar + _powiekszenie;
    T* nowe_dane = new T[nowy_rozmiar];
    if(_rozmiar > 0) {
      std::memcpy(nowe_dane,_dane,_rozmiar*sizeof(T));
      delete [] _dane;
    }
    _dane = nowe_dane;
    _rozmiar = nowy_rozmiar;
  }
  
  T* _dane;
  unsigned _rozmiar;
  unsigned _zapelnione;
  static const unsigned _powiekszenie = 10;
};

/**
 * Standardowy operator wypisania na strumień. Elementy wektora są wypisywane po kolei, oddzielone są znakiem nowej linii.
 *
 * @param out Strumień, na który zostanie wypisany wektor.
 * @param wekt Wektor, który zostanie wypisany
 * @return Strumień po wypisaniu na nim wektora.
 */
template <typename T>
std::ostream& operator <<(std::ostream& out, const wektor<T>& wekt) {
  for(unsigned i = 0; i < wekt.ilosc(); ++i) {
    out << wekt[i] << std::endl;
  }
  return out;
}

/**
 * Standardowy operator wczytania ze strumienia. Elementy wektora są wczytywane po kolei.
 *
 * @param out Strumień, z którego zostanie wczytany wektor
 * @param wekt Wektor, który zostanie wczytany
 * @return Strumień po wczytaniu z niego wektora.
 */
template <typename T>
std::istream& operator >>(std::istream& in, wektor<T>& wekt) {
  while(!in.eof()) {
    T temp;
    in >> temp;
    wekt.dodaj(temp);
  }
  return in;
}

#endif

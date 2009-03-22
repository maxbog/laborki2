/**
 * @file macierz.cc
 * @author Maksymilian Boguń
 * @date 8-3-2009
 */

#include <cstring>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>
#include <iostream>

#include "macierz.h"

macierz::macierz()
    : _wiersze(0), _kolumny(0), _dane(0) {
}

macierz::macierz(const macierz& inna)
    : _wiersze(inna._wiersze), _kolumny(inna._kolumny) {

    _dane = new double[_wiersze * _kolumny];
    std::memcpy(_dane, inna._dane, _wiersze * _kolumny * sizeof(double));
}

macierz::macierz(unsigned wiersze, unsigned kolumny)
    : _wiersze(wiersze), _kolumny(kolumny) {
    _dane = new double[_wiersze * _kolumny];
}

macierz::~macierz() {
    if(_dane) {
        delete [] _dane;
    }
}

macierz& macierz::operator =(const macierz& rhs) {
    if(this == &rhs) {
        return *this;
    }
  
    _wiersze = rhs._wiersze;
    _kolumny = rhs._kolumny;

    delete [] _dane;
    _dane = new double[rhs._wiersze * rhs._kolumny];
    std::memcpy(_dane, rhs._dane, _wiersze * _kolumny * sizeof(double));
  
    return *this;
}

macierz macierz::operator +(const macierz& rhs) const {
    if(_kolumny != rhs._kolumny) {
        throw size_error("Liczba kolumn się nie zgadza!");
    }
    if(_wiersze != rhs._wiersze) {
        throw size_error("Liczba wierszy się nie zgadza!");
    }

    macierz wynik(*this);

    return wynik += rhs;
}

macierz macierz::operator -(const macierz& rhs) const {
    if(_kolumny != rhs._kolumny) {
        throw size_error("Liczba kolumn się nie zgadza!");
    }
    if(_wiersze != rhs._wiersze) {
        throw size_error("Liczba wierszy się nie zgadza!");
    }

    macierz wynik(*this);

    return wynik -= rhs;  
}

macierz macierz::operator +() const {
    return *this;
}

macierz macierz::operator -() const {
    macierz wynik(_wiersze, _kolumny);
  
    for(unsigned i = 0; i < _wiersze * _kolumny; ++i) {
        wynik._dane[i] = -_dane[i];
    }

    return wynik;
}

macierz macierz::operator *(double rhs) const {
    macierz wynik(*this);
    return wynik *= rhs;
}

macierz macierz::operator *(const macierz& rhs) const {
    if(_wiersze != rhs._kolumny) {
        throw size_error("Macierze nie mogą być przemnożone: nieodpowiednie wymiary");
    }
    
    macierz wynik(_wiersze, rhs._kolumny);

    // Standardowy algorytm mnożenia macierzy
    for(unsigned w = 0; w < wynik._wiersze; ++w) {
        for(unsigned k = 0; k < wynik._kolumny; ++k) {
            double suma = 0.;
            for(unsigned i = 0; i < _kolumny; ++i) {
                suma += (*this)(w,i) * rhs(i,k);
            }
            wynik(w,k) = suma;
        }
    }

    return wynik;
}

macierz& macierz::operator +=(const macierz& rhs) {
    if(_kolumny != rhs._kolumny) {
        throw size_error("Liczba kolumn się nie zgadza!");
    }
    if(_wiersze != rhs._wiersze) {
        throw size_error("Liczba wierszy się nie zgadza!");
    }
  
    for(unsigned i = 0; i < _wiersze * _kolumny; ++i) {
        _dane[i] += rhs._dane[i];
    }

    return *this;
}

macierz& macierz::operator -=(const macierz& rhs) {
    if(_kolumny != rhs._kolumny) {
        throw size_error("Liczba kolumn się nie zgadza!");
    }
    if(_wiersze != rhs._wiersze) {
        throw size_error("Liczba wierszy się nie zgadza!");
    }
    
    for(unsigned i = 0; i < _wiersze * _kolumny; ++i) {
        _dane[i] -= rhs._dane[i];
    }

    return *this;
}

macierz& macierz::operator *=(double rhs) {
    for(unsigned i = 0; i < _wiersze * _kolumny; ++i) {
        _dane[i] *= rhs;
    }

    return *this;
}

macierz& macierz::operator *=(const macierz& rhs) {
    macierz tmp = (*this) * rhs;
    operator =(tmp);
  
    return *this;
}

bool macierz::operator ==(const macierz& rhs) const {
    if(this == &rhs) {
        return true;
    }

    if(_wiersze != rhs._wiersze || _kolumny != rhs._kolumny) {
        return false;
    }

    return 0 == std::memcmp(_dane, rhs._dane, _wiersze * _kolumny * sizeof(double));
}

bool macierz::operator !=(const macierz& rhs) const {
    return !operator ==(rhs);
}

const_macierz_wiersz macierz::operator [](unsigned wiersz) const {
    if(wiersz >= _wiersze) {
        throw std::out_of_range("Taki wiersz nie istnieje!");
    }
    return const_macierz_wiersz(this, wiersz);
}

macierz_wiersz macierz::operator [](unsigned wiersz) {
    if(wiersz >= _wiersze) {
        throw std::out_of_range("Taki wiersz nie istnieje!");
    }
    return macierz_wiersz(this, wiersz);
}
const double& macierz::operator ()(unsigned wiersz, unsigned kolumna) const {
    if(wiersz >= _wiersze) {
        throw std::out_of_range("Taki wiersz nie istnieje!");
    }
    if(kolumna >= _kolumny) {
        throw std::out_of_range("Taka kolumna nie istnieje!");
    }
    return _dane[wiersz * _kolumny + kolumna];
}
 
double& macierz::operator ()(unsigned wiersz, unsigned kolumna) {
    if(wiersz >= _wiersze) {
        throw std::out_of_range("Taki wiersz nie istnieje!");
    }
    
    if(kolumna >= _kolumny) {
        throw std::out_of_range("Taka kolumna nie istnieje!");
    }
    return _dane[wiersz * _kolumny + kolumna];
}

double macierz::wyznacznik() const {
    if(_wiersze != _kolumny) {
        throw size_error("Macierz nie jest kwadratowa!");
    }

    if(_kolumny == 1) {
        return _dane[0];
    }
  
    double wyzn = 1.;
    macierz tmp(*this);
  
    // Metoda eliminacji Gaussa
    for(unsigned w = 0; w < _wiersze; ++w) {
    
        unsigned niez = tmp.znajdz_niezerowy(w, w);
        if(niez == _kolumny) {
            return 0.;
        }    
        tmp.zamien_wiersze(w, niez);
    
        wyzn *= tmp(w,w);
        for(unsigned i = w + 1; i < _wiersze; ++i) {
            double stosunek = tmp(i,w) / tmp(w,w);
            for(unsigned k = w; k < _kolumny; ++k) {
                tmp(i,k) -= tmp(w,k)*stosunek;
            }
        }
    }
  
    return wyzn;
}

macierz macierz::odwroc() const {
    if(_kolumny == 0 || _wiersze == 0) {
        throw size_error("Któryś z wymiarów jest zerowy!");
    }
    
    if(_wiersze != _kolumny) {
        throw size_error("Macierz nie jest kwadratowa!");
    }
  
    double wyzn = wyznacznik();

    
    if(std::fabs(wyzn) < std::numeric_limits<double>::epsilon()) {
        throw std::runtime_error("Zerowy wyznacznik!");
    }
  
    macierz wynik(_wiersze, _kolumny);

    // A^-1 = A^D / det A
    for(unsigned w = 0; w < _wiersze; ++w) {
        for(unsigned k = 0; k < _kolumny; ++k) {
            wynik(w,k) = ((w + k) % 2 ? -1 : 1) * dopelnienie(w,k) / wyzn;
        }
    }
  
    return wynik.transponuj();
}

macierz macierz::transponuj() const {
    if(_kolumny == 0 || _wiersze == 0) {
        throw size_error("Któryś z wymiarów jest zerowy!");
    }
    
    macierz wynik(_kolumny, _wiersze);
  
    for(unsigned w = 0; w < _wiersze; ++w) {
        for(unsigned k = 0; k < _kolumny; ++k) {
            wynik(k,w) = (*this)(w,k);
        }
    }
  
    return wynik;
}

double macierz::max_element() const {
    if(_kolumny == 0 || _wiersze == 0) {
        throw size_error("Któryś z wymiarów jest zerowy!");
    }
    
    double max = std::numeric_limits<double>::min();
    for(unsigned i = 0; i < _wiersze * _kolumny; ++i) {
        if(max < _dane[i]) {
            max = _dane[i];
        }
    }
  
    return max;
  
    // albo po prostu:
    // *std::max_element(_dane, _dane + _wiersze * _kolumny);
}

double macierz::min_element() const {
    if(_kolumny == 0 || _wiersze == 0) {
        throw size_error("Któryś z wymiarów jest zerowy!");
    }
    
    double min = std::numeric_limits<double>::max();
    for(unsigned i = 0; i < _wiersze * _kolumny; ++i) {
        if(min > _dane[i]) {
            min = _dane[i];
        }
    }

    return min;
  
    // albo po prostu:
    // return *std::min_element(_dane, _dane + _wiersze * _kolumny);
}

bool macierz::symetryczna() const {
    if(_kolumny == 0 || _wiersze == 0) {
        throw size_error("Któryś z wymiarów jest zerowy!");
    }

    return operator==(transponuj());
}

unsigned macierz::kolumny() const {
    return _kolumny;
}

unsigned macierz::wiersze() const {
    return _wiersze;
}

macierz macierz::stworz_zerowa(unsigned wiersze, unsigned kolumny) {
    macierz wynik(wiersze, kolumny);
    for(unsigned i = 0; i < wiersze * kolumny; ++i) {
        wynik._dane[i] = 0.;
    }
    return wynik;

    // ewentualnie mozna uzyc:
    // std::memset(wynik._dane, 0, _wiersze * _kolumny * sizeof(double));
    // ale to zalezy od implementacji liczb double
}

macierz macierz::stworz_zerowa(const macierz& wzor) {
    return stworz_zerowa(wzor.wiersze(),wzor.kolumny());
}

macierz macierz::stworz_jedynkowa(unsigned wiersze, unsigned kolumny) {
    macierz wynik(wiersze, kolumny);
    for(unsigned i = 0; i < wiersze * kolumny; ++i) {
        wynik._dane[i] = 1.;
    }
    return wynik;
}

macierz macierz::stworz_jedynkowa(const macierz& wzor) {
    return stworz_jedynkowa(wzor.wiersze(), wzor.kolumny());
}
  
macierz macierz::stworz_identyczna(unsigned wiersze, unsigned kolumny) {
    macierz wynik = stworz_zerowa(wiersze, kolumny);
    for(unsigned i = 0; i < std::min(wiersze, kolumny); ++i) {
        wynik(i,i) = 1.;
    }
    return wynik;
}

macierz macierz::stworz_identyczna(const macierz& wzor) {
    return stworz_identyczna(wzor.wiersze(), wzor.kolumny());
}
  
macierz macierz::stworz_losowa(unsigned wiersze, unsigned kolumny) {
    macierz wynik(wiersze, kolumny);
  
    srand(time(0));
    for(unsigned i = 0; i < wiersze * kolumny; ++i) {
        wynik._dane[i] = (double)rand()/((double)RAND_MAX+1.);
    }

    return wynik;
}

macierz macierz::stworz_losowa(const macierz& wzor) {
    return stworz_losowa(wzor.wiersze(), wzor.kolumny());
}

// Zamienia dwa wiersze ze sobą
void macierz::zamien_wiersze(unsigned w1, unsigned w2) {
    for(unsigned i = 0; i < _kolumny; ++i) {
        std::swap((*this)(w1,i), (*this)(w2,i));
    }
}

// Szuka pierwszego niezerowego elementu w podanej kolumnie, zaczynając od kolumny `poczatek`
unsigned macierz::znajdz_niezerowy(unsigned kolumna, unsigned poczatek) const {
    for(unsigned i = poczatek; i < _kolumny; ++i) {
        if(std::abs((*this)(i, kolumna)) > std::numeric_limits<double>::epsilon()) {
            return i;
        }
    }
    return _kolumny;
}

// Liczy dopełnienie algebraiczne dla elementu (wiersz, kolumna)
double macierz::dopelnienie(unsigned wiersz, unsigned kolumna) const {
    assert(_kolumny == _wiersze);
  
    if(_kolumny == 1) {
        return _dane[0];
    }

    // tworzy macierz z usunietyni jedna kolumna i jednym wierszem
    macierz mniejsza(_wiersze - 1, _kolumny - 1);
    unsigned n_w = 0, n_k = 0;
    for(unsigned w = 0; w < _wiersze; ++w) {
        if(w == wiersz) {
            continue;
        }
    
        n_k = 0;
        for(unsigned k = 0; k < _kolumny; ++k) {
            if(k == kolumna) {
                continue;
            }

            mniejsza(n_w,n_k) = (*this)(w,k);
      
            ++n_k;
        }
        ++n_w;
    }

    return mniejsza.wyznacznik();  
}


macierz_wiersz::macierz_wiersz(macierz* m, unsigned wiersz)
    : _macierz(m), _wiersz(wiersz) {
}

const double& macierz_wiersz::operator [](unsigned kolumna) const {
    return (*_macierz)(_wiersz, kolumna);
}

double& macierz_wiersz::operator [](unsigned kolumna) {
    return (*_macierz)(_wiersz, kolumna);
}


const_macierz_wiersz::const_macierz_wiersz(const macierz* m, unsigned wiersz)
    : _macierz(m), _wiersz(wiersz) {
}

const double& const_macierz_wiersz::operator [](unsigned kolumna) const {
    return (*_macierz)(_wiersz, kolumna);
}

size_error::size_error(const std::string& what)
    : std::logic_error(what) {
}

std::istream& operator >>(std::istream& is, macierz& m) {
    unsigned wiersze, kolumny;

    is >> wiersze >> kolumny;

    m = macierz(wiersze, kolumny);
    for(unsigned i = 0; i < wiersze * kolumny; ++i) {
        is >> m._dane[i];
    }

    return is;
}

std::ostream& operator <<(std::ostream& os, const macierz& m) {
    os << m._wiersze << " " << m._kolumny << std::endl;
    for(unsigned w = 0; w < m._wiersze; ++w) {
        for(unsigned k = 0; k < m._kolumny; ++k) {
            os <<  m(w,k) << " ";
        }
        os << std::endl;
    }

    return os;
}

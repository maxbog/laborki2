/**
 * @file zad2.cc
 * @author Maksymilian Boguń
 * @date 9-3-2009
 */

#include "zad2.h"

using std::istream;
using std::ostream;

ciag::ciag() {
    ++_ile;
    _dane = new char[1];
    _dane[0] = '\0';
}

ciag::ciag(const char* cstr) {
    _dane = new char[strlen(cstr)+1];
    strcpy(_dane, cstr);
    ++_ile;
}

ciag::ciag(const ciag& inny) {
    _dane = new char[inny.dl()+1];
    strcpy(_dane, inny._dane);
    ++_ile;
}

ciag::~ciag() {
    --_ile;
    if(_dane) {
        delete [] _dane;
    }
}

unsigned ciag::dl() const {
    return strlen(_dane);
}

ciag& ciag::operator=(const ciag& inny) {
    if(_dane) {
        delete [] _dane;
    }
    _dane = new char[inny.dl() + 1];
    strcpy(_dane, inny._dane);
    return *this;
}

ciag& ciag::operator+=(const ciag& inny) {
    char* stare_dane = _dane;
    _dane = new char[dl() + inny.dl() + 1];
    if(stare_dane) {
        strcpy(_dane, stare_dane);
        delete [] stare_dane;
    }
  
    char* end = _dane;
    while(*end++)
        ;
    strcpy(end-1, inny._dane);

    return *this;
}

ciag::operator const char*() const {
    return _dane;
}

unsigned ciag::ile() {
    return _ile;
}
 
unsigned ciag::strlen(const char* str) {
    unsigned dlugosc = 0;
    while(*str++)
        ++dlugosc;
    return dlugosc;
}

char* ciag::strcpy(char* to, const char* from) {
    char* ptr = to;
    while((*to++ = *from++))
        ;
    return ptr;
}
 

ciag operator+(const ciag& str1, const ciag& str2) {
    ciag tmp(str1);
    return tmp += str2;
}

istream& operator>>(istream& is, ciag& cg) {
    char bufor[512];
    is >> bufor;
    cg._dane = new char[ciag::strlen(bufor)+1];
    ciag::strcpy(cg._dane, bufor);
    return is;
}

ostream& operator<<(ostream& os, const ciag& cg) {
    os << cg._dane;
    return os;
}

unsigned ciag::_ile = 0; 

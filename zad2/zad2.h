// -*- mode: C++ -*-
/**
 * @file zad2.h
 * @author Maksymilian Boguń
 * @date 9-3-2009
 */

#include <iostream>

/**
 * Reprezentuje ciąg znaków.
 * Brak ograniczeń co do długości, poza wielkością pamięci :)
 * 
 */
class ciag {
public:
    /**
     * Konstruktor domyślny.
     * Tworzy ciąg o długości 0.
     * 
     */
    ciag();
    /** 
     * Konstruktor konwertujący z ciągu znaków C.
     * Dane są kopiowane, oryginalny ciąg pozostaje nienaruszony.
     * 
     * @param cstr Ciag znakowy języka C.
     */
    ciag(const char* cstr);
    /** 
     * Konstruktor kopiujący.
     * Tworzy głęboką kopię ciągu - wszystkie dane są kopiowane.
     * 
     * @param inny Ciąg, który zostanie skopiowany
     */
    ciag(const ciag& inny);
    /** 
     * Destruktor.
     * Zwalnia pamięć używaną przez ciąg znaków.
     * 
     */
    ~ciag();

    /**
     * Zwraca długość ciagu znaków.
     *
     * @return Długość ciągu znaków. 
     */
    unsigned dl() const;

    /** 
     * Operator przypisania.
     * Standardowy operator przypisania, tworzy głęboką kopię ciągu.
     * 
     * @param inny Ciąg do skopiowania.
     * 
     * @return Ten ciąg.
     */
    ciag& operator =(const ciag& inny);
    /** 
     * Operator konkatenacji.
     * Dodaje na koniec tego ciągu znaków inny, podany w parametrze.
     * Oryginalny ciąg zostanie nienaruszony.
     * 
     * @param inny Ciąg znaków, jaki zostanie dodany.
     * 
     * @return Ten ciąg.
     */
    ciag& operator +=(const ciag& inny);
    /** 
     * Operator rzutowania na ciąg znaków C.
     * Nie istnieje możliwość modyfikacji zwracanego ciągu.
     * 
     * @return Reprezentacja tego ciągu jako ciagu znaków języka C.
     */
    operator const char*() const;

    /** 
     * Zwraca ilość istniejących obiektów typu ciag.
     *  
     * @return Ilość istniejących obiektów typu ciąg.
     */
    static unsigned ile();

    friend ciag operator+(const ciag& str1, const ciag& str2);
    friend std::istream& operator>>(std::istream& is, ciag& cg);
    friend std::ostream& operator<<(std::ostream& is, const ciag& cg);
  
private:
    char* _dane;
    static unsigned _ile;
    static unsigned strlen(const char* str);
    static char* strcpy(char* to, const char* from);
  
};

/** 
 * Operator konkatenacji dwóch ciągów.
 * Wynikiem jest ciąg składający się z dwóch ciągów podanych w parametrach, jeden za drugim.
 * Operator NIE jest przemienny!
 * 
 * @param str1 Pierwszy ciąg do konkatenacji.
 * @param str2 Drugi ciąg do konkatenacji.
 * 
 * @return Wynikowy ciąg znaków.
 */
ciag operator+(const ciag& str1, const ciag& str2);
/** 
 * Standardowy operator wczytywania ciągu znaków ze strumienia.
 * Zachowuje się podobnie, jak operator dla ciągu języka C, tzn. każdy biały znak
 * przerywa wczytywanie.
 * 
 * @param is Strumień, z którego zostanie wczytany ciąg.
 * @param cg Ciąg, który zostanie wczytany.
 * 
 * @return Strumień po wczytaniu z niego ciągu.
 */
std::istream& operator>>(std::istream& is, ciag& cg);
/** 
 * Standardowy operator wypisania ciągu znaków na strumień.
 * Zachowuje się identycznie jak operator dla ciągu języka C.
 * 
 * @param os Strumień, na który zostanie wypisany ciąg znaków.
 * @param cg Ciąg znaków do wypisania.
 * 
 * @return Strumień po wypisaniu na niego ciągu znaków.
 */
std::ostream& operator<<(std::ostream& os, const ciag& cg);

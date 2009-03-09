// -*- mode: C++ -*-
/**
 * @file zad2.h
 * @author Maksymilian Bogu�
 * @date 9-3-2009
 */

#include <iostream>

/**
 * Reprezentuje ci�g znak�w.
 * Brak ogranicze� co do d�ugo�ci, poza wielko�ci� pami�ci :)
 * 
 */
class ciag {
public:
    /**
     * Konstruktor domy�lny.
     * Tworzy ci�g o d�ugo�ci 0.
     * 
     */
    ciag();
    /** 
     * Konstruktor konwertuj�cy z ci�gu znak�w C.
     * Dane s� kopiowane, oryginalny ci�g pozostaje nienaruszony.
     * 
     * @param cstr Ciag znakowy j�zyka C.
     */
    ciag(const char* cstr);
    /** 
     * Konstruktor kopiuj�cy.
     * Tworzy g��bok� kopi� ci�gu - wszystkie dane s� kopiowane.
     * 
     * @param inny Ci�g, kt�ry zostanie skopiowany
     */
    ciag(const ciag& inny);
    /** 
     * Destruktor.
     * Zwalnia pami�� u�ywan� przez ci�g znak�w.
     * 
     */
    ~ciag();

    /**
     * Zwraca d�ugo�� ciagu znak�w.
     *
     * @return D�ugo�� ci�gu znak�w. 
     */
    unsigned dl() const;

    /** 
     * Operator przypisania.
     * Standardowy operator przypisania, tworzy g��bok� kopi� ci�gu.
     * 
     * @param inny Ci�g do skopiowania.
     * 
     * @return Ten ci�g.
     */
    ciag& operator =(const ciag& inny);
    /** 
     * Operator konkatenacji.
     * Dodaje na koniec tego ci�gu znak�w inny, podany w parametrze.
     * Oryginalny ci�g zostanie nienaruszony.
     * 
     * @param inny Ci�g znak�w, jaki zostanie dodany.
     * 
     * @return Ten ci�g.
     */
    ciag& operator +=(const ciag& inny);
    /** 
     * Operator rzutowania na ci�g znak�w C.
     * Nie istnieje mo�liwo�� modyfikacji zwracanego ci�gu.
     * 
     * @return Reprezentacja tego ci�gu jako ciagu znak�w j�zyka C.
     */
    operator const char*() const;

    /** 
     * Zwraca ilo�� istniej�cych obiekt�w typu ciag.
     *  
     * @return Ilo�� istniej�cych obiekt�w typu ci�g.
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
 * Operator konkatenacji dw�ch ci�g�w.
 * Wynikiem jest ci�g sk�adaj�cy si� z dw�ch ci�g�w podanych w parametrach, jeden za drugim.
 * Operator NIE jest przemienny!
 * 
 * @param str1 Pierwszy ci�g do konkatenacji.
 * @param str2 Drugi ci�g do konkatenacji.
 * 
 * @return Wynikowy ci�g znak�w.
 */
ciag operator+(const ciag& str1, const ciag& str2);
/** 
 * Standardowy operator wczytywania ci�gu znak�w ze strumienia.
 * Zachowuje si� podobnie, jak operator dla ci�gu j�zyka C, tzn. ka�dy bia�y znak
 * przerywa wczytywanie.
 * 
 * @param is Strumie�, z kt�rego zostanie wczytany ci�g.
 * @param cg Ci�g, kt�ry zostanie wczytany.
 * 
 * @return Strumie� po wczytaniu z niego ci�gu.
 */
std::istream& operator>>(std::istream& is, ciag& cg);
/** 
 * Standardowy operator wypisania ci�gu znak�w na strumie�.
 * Zachowuje si� identycznie jak operator dla ci�gu j�zyka C.
 * 
 * @param os Strumie�, na kt�ry zostanie wypisany ci�g znak�w.
 * @param cg Ci�g znak�w do wypisania.
 * 
 * @return Strumie� po wypisaniu na niego ci�gu znak�w.
 */
std::ostream& operator<<(std::ostream& os, const ciag& cg);

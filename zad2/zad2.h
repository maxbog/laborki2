// -*- mode: C++ -*-
/**
 * @file zad2.h
 * @author Maksymilian Boguñ
 * @date 9-3-2009
 */

#include <iostream>

/**
 * Reprezentuje ci±g znaków.
 * Brak ograniczeñ co do d³ugo¶ci, poza wielko¶ci± pamiêci :)
 * 
 */
class ciag {
public:
    /**
     * Konstruktor domy¶lny.
     * Tworzy ci±g o d³ugo¶ci 0.
     * 
     */
    ciag();
    /** 
     * Konstruktor konwertuj±cy z ci±gu znaków C.
     * Dane s± kopiowane, oryginalny ci±g pozostaje nienaruszony.
     * 
     * @param cstr Ciag znakowy jêzyka C.
     */
    ciag(const char* cstr);
    /** 
     * Konstruktor kopiuj±cy.
     * Tworzy g³êbok± kopiê ci±gu - wszystkie dane s± kopiowane.
     * 
     * @param inny Ci±g, który zostanie skopiowany
     */
    ciag(const ciag& inny);
    /** 
     * Destruktor.
     * Zwalnia pamiêæ u¿ywan± przez ci±g znaków.
     * 
     */
    ~ciag();

    /**
     * Zwraca d³ugo¶æ ciagu znaków.
     *
     * @return D³ugo¶æ ci±gu znaków. 
     */
    unsigned dl() const;

    /** 
     * Operator przypisania.
     * Standardowy operator przypisania, tworzy g³êbok± kopiê ci±gu.
     * 
     * @param inny Ci±g do skopiowania.
     * 
     * @return Ten ci±g.
     */
    ciag& operator =(const ciag& inny);
    /** 
     * Operator konkatenacji.
     * Dodaje na koniec tego ci±gu znaków inny, podany w parametrze.
     * Oryginalny ci±g zostanie nienaruszony.
     * 
     * @param inny Ci±g znaków, jaki zostanie dodany.
     * 
     * @return Ten ci±g.
     */
    ciag& operator +=(const ciag& inny);
    /** 
     * Operator rzutowania na ci±g znaków C.
     * Nie istnieje mo¿liwo¶æ modyfikacji zwracanego ci±gu.
     * 
     * @return Reprezentacja tego ci±gu jako ciagu znaków jêzyka C.
     */
    operator const char*() const;

    /** 
     * Zwraca ilo¶æ istniej±cych obiektów typu ciag.
     *  
     * @return Ilo¶æ istniej±cych obiektów typu ci±g.
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
 * Operator konkatenacji dwóch ci±gów.
 * Wynikiem jest ci±g sk³adaj±cy siê z dwóch ci±gów podanych w parametrach, jeden za drugim.
 * Operator NIE jest przemienny!
 * 
 * @param str1 Pierwszy ci±g do konkatenacji.
 * @param str2 Drugi ci±g do konkatenacji.
 * 
 * @return Wynikowy ci±g znaków.
 */
ciag operator+(const ciag& str1, const ciag& str2);
/** 
 * Standardowy operator wczytywania ci±gu znaków ze strumienia.
 * Zachowuje siê podobnie, jak operator dla ci±gu jêzyka C, tzn. ka¿dy bia³y znak
 * przerywa wczytywanie.
 * 
 * @param is Strumieñ, z którego zostanie wczytany ci±g.
 * @param cg Ci±g, który zostanie wczytany.
 * 
 * @return Strumieñ po wczytaniu z niego ci±gu.
 */
std::istream& operator>>(std::istream& is, ciag& cg);
/** 
 * Standardowy operator wypisania ci±gu znaków na strumieñ.
 * Zachowuje siê identycznie jak operator dla ci±gu jêzyka C.
 * 
 * @param os Strumieñ, na który zostanie wypisany ci±g znaków.
 * @param cg Ci±g znaków do wypisania.
 * 
 * @return Strumieñ po wypisaniu na niego ci±gu znaków.
 */
std::ostream& operator<<(std::ostream& os, const ciag& cg);

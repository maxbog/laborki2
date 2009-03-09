// -*- mode: C++ -*-
/**
 * @file macierz.h
 * @author Maksymilian Boguń
 * @date 8-3-2009
 */
#ifndef MACIERZ_H_INCLUDED_
#define MACIERZ_H_INCLUDED_

#include <iostream>
#include <stdexcept>

class macierz_wiersz;
class const_macierz_wiersz;

/**
 * Opisuje macierz liczb rzeczywistych o zadanych rozmiarach. Posiada podstawowe
 * funkcje macierzowe, jak dodawanie, odejmowanie, mnożenie, liczenie wyznaczników,
 * czy macierzy odwrotnych.
 */
class macierz {
public:
    /** 
     * Konstruktor domyślny.
     * Tworzy "macierz" o rozmiarach 0x0. 
     */
    macierz();    
    /**
     * Konstuktor kopiujący.
     * Tworzy głęboką kopię, wszystkie dane są kopiowane.
     *
     * @param inna Macierz oryginalna, która zostanie skopiowana.
     */
    macierz(const macierz& inna);
    /**
     * Konstruktor tworzący macierz o zadanych rozmiarach.
     *
     * @param wiersze Ilość wierszy w macierzy.
     * @param kolumny Ilość kolumn w macierzy.
     */
    macierz(unsigned wiersze, unsigned kolumny);
    /**
     * Destruktor.
     * Zwalnia pamięć zarezerwowaną przez klasę.
     */
    ~macierz();

    /**
     * Operator przypisania.
     * Tworzy głęboką kopię oryginalnej macierzy. Obydwie reprezentują
     * te same dane, ale są one w dwóch kopiach. Rozmiary macierzy nie muszą się zgadzać,
     * macierz przyjmie wymiary macierzy przypisywanej.
     *
     * @param rhs Macierz przypisywana.
     *
     * @return Ta macierz.
     */
    macierz& operator =(const macierz& rhs);
    /** 
     * Sumuje dwie macierze.
     * Wymiary macierzy muszą się zgadać. Jest to proste sumowanie
     * każdego elementu z osobna.
     * 
     * @param rhs Druga macierz, która zostanie zsumowana.
     * 
     * @return Macierz będąca sumą dwóch innych.
     *
     * @throw size_error Rzucany, gdy wymiary macierzy się nie zgadzają.
     */
    macierz operator +(const macierz& rhs) const;
    /** 
     * Odejmuje dwie macierze.
     * Wymiary macierzy muszą się zgadać. Jest to proste odejmowanie
     * każdego elementu z osobna.
     * 
     * @param rhs Druga macierz, która zostanie odjęta od tej.
     * 
     * @return Macierz będąca różnicą dwóch innych.
     *
     * @throw size_error Rzucany, gdy wymiary macierzy się nie zgadzają.
     */
    macierz operator -(const macierz& rhs) const;
    /** 
     * Unarny operator "+".
     * W praktyce nie robi nic, zwraca tą macierz.
     * 
     * @return Zwraca tą macierz.
     */
    macierz operator +() const;
    /** 
     * Unarny operator "-".
     * Zwraca zanegowaną macierz. Jest to prosta negacja każdego '
     * z elementów z osobna.
     * 
     * @return Zanegowana macierz.
     */
    macierz operator -() const;
    /** 
     * Iloczym macierzy przez liczbę.
     * Prosty iloczyn każdego z elementów macierzy przez daną liczbę.
     * 
     * @param rhs Liczba, przez którą macierz zostanie pomnożona.
     * 
     * @return Macierz przemnożona przez liczbę.
     */
    macierz operator *(double rhs) const;
    /** 
     * Iloczyn dwóch macierzy.
     * Standardowo zdefiniowany iloczyn. Odpowiednie wymiary muszą się zgadzać.
     * 
     * @param rhs macierz, przez którą zostanie pomnożona ta macierz.
     * 
     * @return Wynik mnożenia macierzy.
     *
     * @throw size_error Rzucany, gdy wymagane wymiary się nie zgadzają.
     */
    macierz operator *(const macierz& rhs) const;
    /** 
     * Operator "+=".
     * Standardowy operator skrócający zapis A = A + B.
     * Wymiary macierzy muszą się zgdzać.
     * 
     * @param rhs Macierz, która zostanie dodana do tej.
     * 
     * @return Ta macierz po dodaniu innej.
     *
     * @throw size_error Rzucany, gdy wymiary macierzy się nie zgadzają.
     *
     * @see operator+()
     */
    macierz& operator +=(const macierz& rhs);    
    /** 
     * Operator "-=".
     * Standardowy operator skrócający zapis A = A - B.
     * Wymiary macierzy muszą się zgdzać.
     * 
     * @param rhs Macierz, która zostanie odjęta od tej.
     * 
     * @return Ta macierz po odjęciu innej.
     *
     * @throw size_error Rzucany, gdy wymiary macierzy się nie zgadzają.
     *
     * @see operator-()
     */
    macierz& operator -=(const macierz& rhs);    
    /** 
     * Operator "*=" mnożenia przez liczbę.
     * Standardowy operator skrócający zapis A = A * b.
     * 
     * @param rhs Liczba, która zostanie pomnożona przez tą.
     * 
     * @return Ta macierz po przemnożeniu przez liczbę.
     *
     * @see operator*(double)
     */
    macierz& operator *=(double rhs);
    /** 
     * Operator "*=" mnożenia przez macierz.
     * Standardowy operator skracający zapis A = A * B.
     * Odpowiednie wymiary macierzy muszą się zgadzać.
     * 
     * @param rhs Macierz, przez którą zostanie przemnożona ta macierz.
     * 
     * @return Ta macierz po przemnożeniu przez inną.
     *
     * @throw size_error Rzucany, gdy wymagane wymiary się nie zgadzają.
     *
     * @see operator*(const macierz&)
     */
    macierz& operator *=(const macierz& rhs);
    
    /** 
     * Operator porównania dwóch macierzy.
     * Macierze są identyczne, gdy mają te same wymiary
     * i odpowiadające elementy są równe.
     * 
     * @param rhs Macierz, która zostanie porównana z tą.
     * 
     * @return true, gdy macierze są identyczne, w przeciwnym przypadku false.
     */
    bool operator ==(const macierz& rhs) const;
    /** 
     * Operator zaprzeczenia porównania dwóch macierzy.
     * Macierze nie są identyczne, gdy mają różne wymiary
     * lub odpowiadające elementy są różne.
     * 
     * @param rhs Macierz, która zostanie porównana z tą.
     * 
     * @return true, gdy macierze są różne, w przeciwnym przypadku false.
     */
    bool operator !=(const macierz& rhs) const;

    /** 
     * Operator dostępu do wybranego wiersza macierzy.
     * Zwraca obiekt reprezentujący konkretny wiersz tej macierzy.
     * Umożliwia odczyt elementów macierzy, ale nie zapis.
     * Nie powinien być wykorzystywany oddzielnie, ale w parach, np.:
     * @code
     * A[4][3]
     * @endcode
     * 
     * @param wiersz Wybrany wiersz macierzy.
     * 
     * @return Obiekt reprezentujący wiersz macierzy.
     *
     * @throw out_of_range Rzucany, gdy wybrany wiersz nie istnieje w danej macierzy.
     *
     * @see const_macierz_wiersz::operator[]
     */
    const_macierz_wiersz operator [](unsigned wiersz) const;
    /** 
     * Operator dostępu do wybranego wiersza macierzy.
     * Zwraca obiekt reprezentujący konkretny wiersz tej macierzy.
     * Umożliwia zarówno odczyt, ajk i zapis elementów macierzy.
     * Nie powinien być wykorzystywany oddzielnie, ale w parach, np.:
     * @code
     * A[4][3]
     * @endcode
     * 
     * @param wiersz Wybrany wiersz macierzy.
     * 
     * @return Obiekt reprezentujący wiersz macierzy.
     *
     * @throw out_of_range Rzucany, gdy wybrany wiersz nie istnieje w danej macierzy.
     *
     * @see macierz_wiersz::operator[]
     */
    macierz_wiersz operator [](unsigned wiersz);
    /** 
     * Operator dostępu do elementu macierzy.
     * Umożliwia odczyt elementu, ale nie zapis.
     *
     * @param wiersz Wybrany wiersz macierzy.
     * @param kolumna Wybrana kolumna macierzy.
     * 
     * @return Element znajdujący się w wybranym miejscu macierzy.
     *
     * @throw out_of_range Rzucany, gdy wybrane wiersz, albo kolumna nie istnieją w macierzy.
     */
    const double& operator ()(unsigned wiersz, unsigned kolumna) const;
    /** 
     * Operator dostępu do elementu macierzy.
     * Umożliwia zarówno odczyt, jak i zapis elementu macierzy.
     *
     * @param wiersz Wybrany wiersz macierzy.
     * @param kolumna Wybrana kolumna macierzy.
     * 
     * @return Element znajdujący się w wybranym miejscu macierzy.
     *
     * @throw out_of_range Rzucany, gdy wybrane wiersz, albo kolumna nie istnieją w macierzy.
     */
    double& operator ()(unsigned wiersz, unsigned kolumna);
  
    friend std::istream& operator >>(std::istream& is, macierz& m);
    friend std::ostream& operator <<(std::ostream& os, const macierz& m);

    friend class macierz_wiersz;
    friend class const_macierz_wiersz;

    /** 
     * Oblicza wyznacznik macierzy.
     * Wyznacznik obliczany jest metodą eliminacji Gaussa,
     * więc działa nawet dla dużych rozmiarów macierzy.
     * 
     * @return Obliczony wyznacznik.
     *
     * @throw size_error Rzucany, gdy macierz nie jest kwadratowa, lub jeden z wymiarów jest zerowy.
     */
    double wyznacznik() const;
    /** 
     * Oblicza macierz odwrotna do tej.
     * Funkcja działa dla dużych zormiarów macierzy, gdyż korzysta z metody
     * eliminacji Gaussa.
     * 
     * @return Macierz odwrotna do tej.
     *
     * @throw size_error Rzucany, gdy macierz nie jest kwadratowa, lub jeden z wymiarów jest zerowy.
     * @throw runtime_error Rzucany, gdy wyznacznik macierzy jest równy 0.
     */
    macierz odwroc() const;
    /** 
     * Oblicza macierz transponowaną do tej.
     * 
     * @return Macierz transponowana do tej.
     *
     * @throw size_error Rzucany, jeśli macierz ma któryś wymiar zerowy.
     */
    macierz transponuj() const;
    /** 
     * Znajduje największy element w macierzy. 
     * 
     * @return Największy element macierzy.
     *
     * @throw size_error Rzucany, jeśli macierz ma któryś rozmiar zerowy.
     */
    double max_element() const;
    /** 
     * Znajduje najmniejszy element w macierzy. 
     * 
     * @return Najmniejszy element macierzy
     *
     * @throw size_error Rzucany, jeśli macierz ma któryś rozmiar zerowy..
     */
    double min_element() const;
    /** 
     * Stwierdza, czy macierz jest symetryczna.
     * Macierz jest symetryczna, gdy jest równa macierzy transponowanej do niej.
     * 
     * @return true, jeśli macierz jest symetryczna, w przeciwnym przypadku false.
     *
     * @throw size_error Rzucany, jeśli macierz ma któryś rozmiar zerowy.
     */
    bool symetryczna() const;

    /** 
     * Zwraca ilość kolumn macierzy 
     * 
     * @return Ilość kolumn macierzy.
     */
    unsigned kolumny() const;
    /** 
     * Zwraca ilość wierszy macierzy
     * 
     * @return Ilość wierszy macierzy.
     */
    unsigned wiersze() const;

    /** 
     * Tworzy macierz zerową, tzw. wypełnioną samymi zerami, o zadanych rozmiarach.
     * 
     * @param wiersze Ilość wierszy nowej macierzy
     * @param kolumny Ilość kolumn nowej macierzy.
     * 
     * @return Nowa macierz zerowa.
     */
    static macierz stworz_zerowa(unsigned wiersze, unsigned kolumny);
    /** 
     * Tworzy macierz zerową, tzw. wypełnioną samymi zerami, na podstawie innej macierzy.
     * Wymiar nowej macierzy będzie równy wymiarowi macierzy-wzoru.
     * 
     * @param wzor Macierz brana za wzór.
     * 
     * @return Nowa macierz zerowa.
     */
    static macierz stworz_zerowa(const macierz& wzor);

    /** 
     * Tworzy macierz jedynkową, tzw. wypełnioną samymi zerami, o zadanych rozmiarach.
     * 
     * @param wiersze Ilość wierszy nowej macierzy
     * @param kolumny Ilość kolumn nowej macierzy.
     * 
     * @return Nowa macierz jedynkowa.
     */
    static macierz stworz_jedynkowa(unsigned wiersze, unsigned kolumny);
    /** 
     * Tworzy macierz jedynkową, tzw. wypełnioną samymi jedynkami, na podstawie innej macierzy.
     * Wymiar nowej macierzy będzie równy wymiarowi macierzy-wzoru.
     * 
     * @param wzor Macierz brana za wzór.
     * 
     * @return Nowa macierz jedynkowa.
     */
    static macierz stworz_jedynkowa(const macierz& wzor);

    /** 
     * Tworzy macierz identyczną, tzw. wypełnioną samymi zerami
     * z jedynkami na przekątnej, na podstawie innej macierzy.
     * 
     * @param wiersze Ilość wierszy nowej macierzy
     * @param kolumny Ilość kolumn nowej macierzy.
     * 
     * @return Nowa macierz identyczna.
     */
    static macierz stworz_identyczna(unsigned wiersze, unsigned kolumny);
    /** 
     * Tworzy macierz jedynkową, tzw. wypełnioną samymi zerami
     * z jedynkami na przekątnej, o zadanych rozmiarach.
     * Wymiar nowej macierzy będzie równy wymiarowi macierzy-wzoru.
     * 
     * @param wzor Macierz brana za wzór.
     * 
     * @return Nowa macierz identyczna.
     */
    static macierz stworz_identyczna(const macierz& wzor);

    /** 
     * Tworzy macierz losową, tzw. wypełnioną losowymi danymi, na podstawie innej macierzy.
     * Dane losowane są z przedziału [0,1).
     * 
     * @param wiersze Ilość wierszy nowej macierzy
     * @param kolumny Ilość kolumn nowej macierzy.
     * 
     * @return Nowa macierz losowa.
     */
    static macierz stworz_losowa(unsigned wiersze, unsigned kolumny);
    /** 
     * Tworzy macierz losową, tzw. wypełnioną losowymi danymi, na podstawie innej macierzy.
     * Dane losowane są z przedziału [0,1).
     * Wymiar nowej macierzy będzie równy wymiarowi macierzy-wzoru.
     * 
     * @param wzor Macierz brana za wzór.
     * 
     * @return Nowa macierz losowa.
     */
    static macierz stworz_losowa(const macierz& wzor);
  
private:
    unsigned _wiersze, _kolumny;
    double* _dane;

    void zamien_wiersze(unsigned w1, unsigned w2);
    unsigned znajdz_niezerowy(unsigned koluna, unsigned poczatek) const;
    double dopelnienie(unsigned wiersz, unsigned kolumna) const;
};

/**
 * Reprezentuje jeden wiersz konkretnej macierzy. Umożliwia zarówno
 * odczyt, jak i zapis każdej komórki macierzy.
 * Obiekty tej klasy nie powinny być w żaden sposób tworzone przez programistę.
 * Klasa stworzona tylko po to, aby umożliwić następujący zapis:
 * @code
 * macierz[wiersz][kolumna]
 * @endcode
 *
 * @see const_macierz_wiersz 
 */
class macierz_wiersz {
public:
    /** 
     * Zwraca element znajdujący się w reprezentowanym wierszu i podanej kolumnie.
     * Umożliwia odczyt, ale nie zapis.
     * Wiersz macierzy jest ustalony przy próbie dostępu do elementu z klasy macierz.
     *
     * @see macierz::operator[]
     * 
     * @param kolumna Kolumna, w której znajduje się szukany element.
     * 
     * @return Szukany element.
     *
     * @throw out_of_range Rzucany, gdy podana kolumna nie istnieje w macierzy.
     */
    const double& operator [](unsigned kolumna) const;    
    /** 
     * Zwraca element znajdujący się w reprezentowanym wierszu i podanej kolumnie.
     * Umożliwia zarówno odczyt, jak i zapis.
     * Wiersz macierzy jest ustalony przy próbie dostępu do elementu z klasy macierz.
     *
     * @see macierz::operator[]
     * 
     * @param kolumna Kolumna, w której znajduje się szukany element.
     * 
     * @return Szukany element.
     *
     * @throw out_of_range Rzucany, gdy podana kolumna nie istnieje w macierzy.
     */
    double& operator [](unsigned kolumna);

    friend class macierz;
private:
    macierz_wiersz(macierz* m, unsigned wiersz);
    macierz* _macierz;
    unsigned _wiersz;
};

/**
 * Reprezentuje jeden wiersz konkretnej stałej macierzy. Umożliwia
 * odczyt każdej komórki macierzy, ale nie umożliwia zapisu.
 * Obiekty tej klasy nie powinny w żaden sposób być tworzone przez programistę.
 * Klasa stworzona tylko po to, aby umożliwić następujący zapis:
 * @code
 * macierz[wiersz][kolumna]
 * @endcode
 *
 * @see macierz_wiersz
 */
class const_macierz_wiersz {
public:
    /** 
     * Zwraca element znajdujący się w reprezentowanym wierszu i podanej kolumnie.
     * Umożliwia odczyt, ale nie zapis.
     * Wiersz macierzy jest ustalony przy próbie dostępu do elementu z klasy macierz.
     *
     * @see macierz::operator[]
     * 
     * @param kolumna Kolumna, w której znajduje się szukany element.
     * 
     * @return Szukany element.
     *
     * @throw out_of_range Rzucany, gdy podana kolumna lub wiersz nie istnieją w macierzy.
     */
    const double& operator [](unsigned kolumna) const;

    friend class macierz;
private:
    const_macierz_wiersz(const macierz* m, unsigned wiersz);
    const macierz* _macierz;
    unsigned _wiersz;
};

/**
 * Wyjątek rzucany, gdy wymiary macierzy się w jakiś sposób nie zgadzają.
 */
class size_error : public std::logic_error {
public:
    /** 
     * Konstruktor przekazujący wiadomość łapiącemu wyjątek.
     * 
     * @param what Wiadomość do przekazania łapiącemu wyjątek.
     */
    size_error(const std::string& what);
};

/** 
 * Przeciążony operator >> dla macierzy.
 * Wczytuje macierz ze strumienia.
 * Format wczytywanych danych wygląda następująco:
 * @code
 * <ilość wierszy> <ilość kolumn>
 * <wiersz 1>
 * <wiersz 2>
 * ...
 * @endcode
 * gdzie &lt;wiersz n&gt; to lista elementów wiersza n-tego.
 * 
 * @param is Strumień wejściowy, z którego zostanie wczytana macierz.
 * @param m Macierz, która zostanie wczytana.
 * 
 * @return Strumieć po wczytaniu z niego macierzy.
 *
 * @see operator<<(std::ostream&, const macierz&)
 */
std::istream& operator >>(std::istream& is, macierz& m);
/** 
 * Przeciążony operator << dla macierzy.
 * Wypisuje zawartość macierzy do strumienia.
 * Format wypisywanych dzych wygląda następująco:
 * @code
 * <ilość wierszy> <ilość kolumn>
 * <wiersz 1>
 * <wiersz 2>
 * ...
 * @endcode
 * gdzie &lt;wiersz n&gt; lista elementów wiersza n-tego.
 * 
 * @param os Strumień wyjściowy, do którego zostanie wypisana zawartość macierzy.
 * @param m Macierz, która zostanie wypisana.
 * 
 * @return Strumień po wypisaniu do niego macierzy.
 *
 * @see operator>>(std::istream&, macierz&)
 */
std::ostream& operator <<(std::ostream& os, const macierz& m);

#endif

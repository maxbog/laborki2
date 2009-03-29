// -*- mode: C++ -*-
/**
 * @file complex.h
 * @author Maksymilian Boguń
 * @date 29-3-2009
 */
#ifndef COMPLEX_H_INCLUDED_
#define COMPLEX_H_INCLUDED_

/**
 * Prosta klasa reprezentująca liczby zespolone w postaci pary liczb (część rzeczywista i urojona).
 */
class complex {
public:
  /**
   * Konstruktor domyślny. Tworzy liczbę (0,0).
   */
  complex();
  /**
   * Konstruktor kopiujący. Kopiuje liczbę zespoloną, tworząc głęboką kopię.
   *
   * @param inna Liczba zespolona, która zostanie skopiowana.
   */
  complex(const complex& inna);
  /**
   * Konstruktor tworzący liczbę o zadanej części rzeczywistej i urojonej.
   *
   * @param re Część rzeczywista nowej liczby zespolonej.
   * @param im Część urojona nowej liczby zespolonej.
   */
  complex(double re, double im);

  /**
   * Zwraca część rzeczywistą tej liczby zespolonej.
   *
   * @return Część rzeczywista tej liczby.
   */
  double fun1() const;
  /**
   * Zwraca część urojoną tej liczby zespolonej.
   *
   * @return Część urojona tej liczby.
   */
  double fun2() const;
  /**
   * Zwraca kwadrat modułu tej liczby zespolonej.
   *
   * @return Kwadrat modułu tej liczby zespolonej.
   */
  double fun3() const;
  /**
   * Zwraca moduł tej liczby zespolonej.
   *
   * @return Moduł tej liczby zespolonej.
   */
  double fun4() const;

  typedef double(complex::*fun_wsk_t)() const;

  /**
   * Tablica czterech wskaźników do funkcji fun1-fun4.
   */
  fun_wsk_t tab_wsk_fun[4];
private:
  void init_tab();
  
  double _im;
  double _re;
};

#endif

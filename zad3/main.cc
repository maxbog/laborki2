/**
 * @file main.cc
 * @author Maksymilian Boguń
 * @date 8-3-2009
 */

#include <iostream>
#include <sstream>
#include "macierz.h"

using namespace std;

/**
 * Funkcja wejściowa programu.
 */
int main() {
    macierz A(2,2), B = macierz::stworz_losowa(50,50), C = macierz::stworz_losowa(4,4), D = macierz::stworz_losowa(4,4);

    A(0,0) = 4; A(0,1) = 9; A(1,0) = 43; A(1,1) = 15;
    C += D * 7.3;

    macierz S(2,2);
    S(0,0) = 1;
    S(0,1) = 34;
    S(1,0) = 34;
    S(1,1) = 9.2;
    
    cout << "Macierz A: " << endl << A << endl;
    cout << "Wyznacznik: " << A.wyznacznik() << endl;
    cout << "Najmniejszy i największy element: " << S.min_element() << " " << S.max_element() << endl;
    cout << "Macierz A transponowana:" << endl << A.transponuj() << endl;
    cout << "Odwracanie macierzy B, moze to zajac kilka sekund" << endl;
    cout << "Macierz B odwrocona: " << endl << B.odwroc() << endl;
    macierz B1 = B * macierz::stworz_identyczna(50,50);
    cout << "Macierze B i B1 rowne?: " << (B == B1) << endl;
    cout << "Macierz C:" << endl << C << endl;
    cout << "Macierz C odwrocona:" << C.odwroc() << endl;
    cout << "Macierz S:" << endl << S << endl;
    cout << "Czy symetryczna?: " << S.symetryczna() << endl;

    macierz Z(2,2);
    Z(0,0) = 2;
    Z(0,1) = 1;
    Z(1,0) = 4;
    Z(1,1) = 2;
    cout << "Macierz Z:" << endl << Z << endl;
    try {
      cout << "Proba odwrocenia macierzy Z" << endl;
      cout << Z.odwroc() << endl;
    } catch(runtime_error r) {
      cout << "Blad: " << r.what() << endl;
    }

    try {
      cout << "Proba wypisania elementu (4,51) macierzy B" << endl;
      cout << B[4][51] << endl;
    } catch (out_of_range o) {
      cout << "Blad: " << o.what() << endl;
    }

    macierz A1,A2;
    stringstream ss;
    ss << "3 3 0.842566 0.0119543 0.157427 0.637154 0.725044 0.230494 0.19684 0.499382 0.536919" << endl; // A1
    ss << "3 3 0.132354 0.721144 0.0757989 0.528302 0.571889 0.757425 0.89333 0.811718 0.50731" << endl; //A2
    ss >> A1 >> A2;
    cout << A1*A2;
    cout << "Wynik jest prawidlowy, sprawdzone przy uzyciu Mathematica :)" << endl;

    macierz K;
    cout << "Wprowadz macierz: ";
    cin >> K;
    cout << K << K * macierz::stworz_jedynkowa(K);
    
    return 0;
}

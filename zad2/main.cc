/**
 * @file main.cc
 * @author Maksymilian Boguń
 * @date 9-3-2009
 */

#include <iostream>
#include <cstring>

#include "zad2.h"

using std::cout;
using std::endl;
using std::cin;

/**
 * Funkcja wejściowa programu.
 */
int main() {
    ciag A("_ciag_A_");
    cout << 1 << endl;
    ciag B;
    B = "_ciag_B_";
    B += A;
    cout << "istnieja: " << ciag::ile() << " ciagi" << endl;
    ciag C;
    cout << "Podaj ciag C: ";
    cin >> C;
    ciag D;
    D = A + B + "_cos_";
    cout << "istnieja: " << ciag::ile() << " ciagi" << endl;
    A += "_dodaje_zwykly_ciag_";
    C += A;
    cout << A << endl << B << endl << C << endl << D << endl;
    cout << "dlugosc A " << A.dl() << endl;
    cout << "dlugosc B " << B.dl() << endl;
    cout << "dlugosc C " << C.dl() << endl;
    cout << "dlugosc D " << D.dl() << endl;
    {
        ciag ZZ;
        cout << "powstal ciag lokalny i istnieja " << ciag::ile()
             << " ciagi" << endl;
    }
    cout << "a teraz znowu sa: " << A.ile() << " ciagi" << endl;
    cout << "dziala operator konwersji i funkcja C strlen "
         << strlen(A) << endl;
    cout << "dziala operator konwersji i funkcja C strlen "
         << strlen(B) << endl;
    cout << "dziala operator konwersji i funkcja C strlen "
         << strlen(C) << endl;
    cout << "dziala operator konwersji i funkcja C strlen "
         << strlen(D) << endl;
    return 0;
}

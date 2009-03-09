/**
 * @file main.cc
 * @author Maksymilian Boguń
 * @date 8-3-2009
 */

#include <iostream>
#include "macierz.h"

using namespace std;

/**
 * Funkcja wejściowa programu.
 */
int main() {
    macierz A(2,2), B = macierz::stworz_losowa(50,50), C = macierz::stworz_losowa(4,4), D = macierz::stworz_losowa(4,4);

    A(0,0) = 4; A(0,1) = 9; A(1,0) = 43; A(1,1) = 15;
    C += D * 7.3;
    
    cout << A << endl;
    cout << A.wyznacznik() << endl;
    cout << A.transponuj() << endl;
    cout << B.odwroc() << endl;
    cout << D << endl;
    cout << D.odwroc() << endl;
    
    return 0;
}

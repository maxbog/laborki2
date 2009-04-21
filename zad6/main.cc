/*
Zadanie Czwarte - Cwiczenie z dziedziczenia
*/
#include <iostream>
#include "zad04v.h"
#include "zad04sv.h"
using namespace std;
int main()
{
//test klasy vect
      int i;
      vect v1(10);
      for (i=0; i<v1.get_size(); i++) v1[i] = i;
      vect v2(v1), v3;
      v3 = v2;
      v3[2] = 5.5;
      cout << "v1 = " << v1 << endl << "v2 = " << v2
           << endl << "v3 = " << v3 << endl;
      if (v1 == v2) cout << "v1 == v2" << endl;
      if (v1 != v3) cout << "v1 != v3" << endl;
      v1.set_size(15);
      v1.dodaj(34.56);
      cout << "podaj v2 = ";
      cin >> v2;
      cout << "v1 = " << v1 << endl << "v2 = " << v2 << endl;
//test klasy svect
      svect sv1(10);
      for (i=0; i<sv1.get_size(); i++) sv1[i] = i;
      svect sv2(sv1);
      svect sv3(v1);
      cout << "sv1 = " << sv1 << endl << "sv2 = " << sv2
           << endl << "sv3 = " << sv3 << endl;
      if (sv1 == sv2) cout << "sv1 == sv2" << endl;
      if (sv1 != sv3) cout << "sv1 != sv3" << endl;
      v1[0] = sv1[7] = sv2[3] = sv3[4] = 4.5;
      cout << "v1 = " << v1 << endl << "sv1 = " << sv1 << endl
           << "sv2 = " << sv2 << endl << "sv3 = " << sv3 << endl;
      sv3 = v2;
      sv1.set_size(20);
      sv1.dodaj(-12.45);
      cout <<"podaj sv2 = ";
      cin >> sv2;
      cout << "sv1 = " << sv1 << endl << "sv2 = " << sv2
           << endl << "sv3 = " << sv3 << endl;
      return 0;
}

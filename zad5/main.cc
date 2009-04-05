/**
 * @file main.cc
 * @author Maksymilian Boguń
 * @date 2.4.2009
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * Pokazuje na ekranie pomoc, gdy użytkownik źle wywoła program.
 */
void pokaz_pomoc() {
  cout << "Wywoluj program tak:" << endl;
  cout << "zmien [nazwa_pliku] [przed_zmiana] [po_zmianie]"<<endl;
}

/**
 * Wyciąga z nazwy pliku jego rozszerzenie.
 *
 * @param cale Pełna nazwa pliku, razem z rozszerzeniem.
 *
 * @return Rozszerzenie pliku, razem z kropką.
 */
string rozszerzenie(const string& cale) {
  size_t kropka = cale.find_last_of('.');
  if(kropka != string::npos) {
    return cale.substr(kropka);
  }
  return cale;
}

/**
 * Odcina rozszerzenie od nazwy pliku.
 *
 * @param cale Pełna nazwa pliku, razem z rozszerzeniem.
 *
 * @return Nazwa pliku bez rozszerzenia i bez kropki.
 */
string utnij_rozszerzenie(const string& cale) {
  size_t kropka = cale.find_last_of('.');
  if(kropka != string::npos) {
    return cale.substr(0,kropka);
  }
  return "";
}

/**
 * Podmienia w danym łańcuchu znaków wszystkie wystąpienia wyznaczonego łańcucha na inny.
 * Zmienia oryginalny łańcuch znaków!
 *
 * @param str String, w którym zostaną zamienione wszystkie wystąpienia przed_zamiana.
 * @param przed_zamiana String, który zostanie zamieniony.
 * @param po_zamianie String, jakim zostanie zastąpiony string przed_zamiana.
 */
void podmien(string& str, const string& przed_zamiana, const string& po_zamianie) {
  int pos = 0;
  int roznica = po_zamianie.length() - przed_zamiana.length();
  while((pos = str.find(przed_zamiana,pos)) != (int)string::npos) {
    str.replace(pos, przed_zamiana.length(),po_zamianie);
    pos += roznica;
  }
}

/**
 * Funkcja wejściowa.
 *
 * @param argc Liczba argumentów programu.
 * @param argv Wszystkie argumenty programu.
 */
int main(int argc, char **argv) {
  if(argc != 4) {
    pokaz_pomoc();
    return 0;
  }

  string nazwa_pliku(argv[1]);
  string nazwa_bez_rozsz = utnij_rozszerzenie(nazwa_pliku);
  string rozsz = rozszerzenie(nazwa_pliku);
  string nowa_nazwa = nazwa_bez_rozsz + "_nowy" + rozsz;
  
  string przed_zamiana(argv[2]);
  string po_zamianie(argv[3]);

  ifstream in(nazwa_pliku.c_str());
  if(!in.is_open()) {
    cout << "Plik: '" << nazwa_pliku << "' nie istnieje!" << endl;
    return 0;
  }
  
  ofstream out(nowa_nazwa.c_str());
  if(!out.is_open()) {
    cout << "Wystapil blad przy tworzeniu pliku '" << nowa_nazwa << "'!"<<endl;
  }  
  
  string tmp;
  // wczytujemy po jednej linii i w każdej zamieniamy co mamy zamienić
  while(!in.eof()) {
    getline(in,tmp);
    podmien(tmp,przed_zamiana, po_zamianie);
    out << tmp << endl;
  }

  // Może być, ale niekoniecznie:
  // in.close();
  // out.close();
  
  return 0;
}

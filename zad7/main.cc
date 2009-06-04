#include "wektor.h"
#include "baza_sklepow.h"
#include "baza_towarow.h"
#include "sklep.h"
#include "towar.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void pokaz_zestawienie() {
  cout << "Zestawienie towarów:\n\n";
  wektor<towar>& towary = baza_towarow::singleton().wszystkie();
  for(unsigned i = 0; i < towary.ilosc(); ++i) {
    wektor<std::string>& sklepy = towary[i].sklepy();
    if(sklepy.ilosc() == 0) {
      cout << towary[i].nazwa() <<  endl;
    } else {
      for(unsigned j = 0; j < sklepy.ilosc(); ++j) {
	sklep skl = baza_sklepow::singleton().znajdz_po_nazwie(sklepy[j]);
	if(skl.adresy().ilosc() == 0) {
	  cout << towary[i].nazwa() << " " << towary[i].ceny()[j] << " " << skl.nazwa() << endl;
	} else {
	  for(unsigned k = 0; k < skl.adresy().ilosc(); ++k) {
	    cout << towary[i].nazwa() << " " << towary[i].ceny()[j] << " " << skl.nazwa() << " " << skl.adresy()[k] << endl;
	  }
	}
      }
    }
  }
}

void zapisz_baze() {
  std::string plik_sklepy;
  std::string plik_towary;

  cout << "Podaj nazwe pliku z towarami (domyslnie towary.dat): ";
  cin >> plik_towary;
  cout << "Podaj nazwe pliku ze sklepami (domyslnie sklepy.dat): ";
  cin >> plik_sklepy;
  
  if(plik_towary == "") {
    plik_towary = "towary.dat";
  }

  if(plik_sklepy == "") {
    plik_sklepy = "sklepy.dat";
  }

  ofstream str_towary(plik_towary.c_str());
  ofstream str_sklepy(plik_sklepy.c_str());

  if(!str_towary.is_open() | !str_sklepy.is_open()) {
    cout << "\nBlad podczas zapisu danych!\n";
    return;
  }

  str_towary << baza_towarow::singleton().wszystkie();
  str_sklepy << baza_sklepow::singleton().wszystkie();

  str_towary.close();
  str_sklepy.close();
  cout << "\nZapis powiodl sie!\n";
}

void wczytaj_baze() {
  std::string plik_sklepy;
  std::string plik_towary;

  cout << "Podaj nazwe pliku z towarami (domyslnie towary.dat): ";
  cin >> plik_towary;
  cout << "Podaj nazwe pliku ze sklepami (domyslnie sklepy.dat): ";
  cin >> plik_sklepy;
  
  if(plik_towary == "-") {
    plik_towary = "towary.dat";
  }

  if(plik_sklepy == "-") {
    plik_sklepy = "sklepy.dat";
  }

  ifstream str_towary(plik_towary.c_str());
  ifstream str_sklepy(plik_sklepy.c_str());

  if(!str_towary.is_open() | !str_sklepy.is_open()) {
    cout << "\nBlad podczas wczytytwania danych!\n";
    return;
  }

  while(!str_sklepy.eof()) {
    sklep skl;
    str_sklepy >> skl;
    if(!str_sklepy.fail()) {
      baza_sklepow::singleton().dodaj(skl);
    }
  }
  while(!str_towary.eof()) {
    towar tow;
    str_towary >> tow;
    if(!str_sklepy.fail()) {
      baza_towarow::singleton().dodaj(tow);
    }
  }

  str_towary.close();
  str_sklepy.close();
  cout << "\nWczytywanie powiodlo sie!\n";
}


void pokaz_wszystkie_towary() {
  cout << "Wszystkie towary:\n";
  wektor<towar>& towary = baza_towarow::singleton().wszystkie();
  for(unsigned i = 0; i < towary.ilosc(); ++i) {
    cout << i << " - " << towary[i].nazwa() << endl;
  }
}

void pokaz_info_o_towarze(const towar& t) {
  cout << "Informacje o towarze:\n";
  cout << "Nazwa:" << t.nazwa() << endl;
  cout << "Sklepy:\n";
  for(unsigned i = 0; i < t.sklepy().ilosc(); ++i) {
    sklep skl = baza_sklepow::singleton().znajdz_po_nazwie(t.sklepy()[i]);
    cout << "  Nazwa: " << skl.nazwa() << endl;
    cout << "  Cena w sklepie: " << t.ceny()[i] << endl;
    cout << "------------" << endl;
  }
}

void wyszukaj_towar_po_nazwie() {
  std::string nazwa;
  cout << "Podaj nazwe towaru do wyszukania: ";
  cin >> nazwa;
  towar tow = baza_towarow::singleton().znajdz_po_nazwie(nazwa);
  if(tow == towar::PUSTY) {
    cout << "Brak takiego towaru w bazie!\n";
  } else {
    pokaz_info_o_towarze(tow);
  }
}

void wyszukaj_towar_po_cenie() {
  double cena_min, cena_max;
  cout << "Podaj minimalną cenę: ";
  cin >> cena_min;
  while(cena_min < 0.) {
    cout << "Cena nie moze byc ujemna!\n";
    cout << "Podaj minimalną cene: ";
    cin >> cena_min;
  }

  cout << "Podaj maksymalna cenę: ";
  cin >> cena_max;
  while(cena_max < 0. || cena_max <= cena_min) {
    cout << "Cena maksymalnanie moze byc ujemna i musi byc wieksza od minimalnej!\n";
    cout << "Podaj maksymalna cene: ";
    cin >> cena_max;
  }

  wektor<towar> znalezione = baza_towarow::singleton().znajdz_po_cenie(cena_min,cena_max);
  cout << "Znalezione towary:\n";
  cout << znalezione;  
}

int podaj_numer_towaru() {
  int numer;
  cout << "Podaj numer towaru: ";
  cin >> numer;
  while((numer < 0 || numer >= (int)baza_towarow::singleton().wszystkie().ilosc()) && numer != -1) {
    cout << "Nie ma takiego towaru. Sprobuj jeszcze raz: ";
    cin >> numer;
  }

  return numer;
}

void pokaz_towar() {
  int numer = podaj_numer_towaru();
  if(numer == -1) {
    return;
  }

  towar tow = baza_towarow::singleton().wszystkie()[(unsigned)numer];
  pokaz_info_o_towarze(tow);  
}

void zmien_nazwe_towaru(towar& tow) {
  cout << "Podaj nowa nazwe: ";
  cin >>  tow.nazwa();
}

void dodaj_towar_do_sklepu(towar& tow) {
  cout << "Podaj nazwe sklepu: ";
  string nazwa;
  cin >> nazwa;
  sklep skl = baza_sklepow::singleton().znajdz_po_nazwie(nazwa);
  while (skl == sklep::PUSTY || tow.sklepy().znajdz(nazwa) != -1) {
    cout << "Taki sklep nie istnieje lub towar jest juz w tym sklepie!\n";
    cout << "Podaj nazwe sklepu: ";
    cin >> nazwa;
    skl = baza_sklepow::singleton().znajdz_po_nazwie(nazwa);
  }
  double cena;
  cout << "Podaj cene: ";
  cin >> cena;
  while(cena < 0.) {
    cout << "Cena nie moze byc ujemna!\n";
    cout << "Podaj cene: ";
    cin >> cena;
  }
  tow.sklepy().dodaj(nazwa);
  tow.ceny().dodaj(cena);
}

void modyfikuj_cene_w_sklepie(towar& tow) {
  cout << "Podaj nazwe sklepu: ";
  string nazwa;
  cin >> nazwa;
  while(tow.sklepy().znajdz(nazwa) == -1) {
    cout << "Towaru nie ma w tym sklepie!\n";
    cout << "Podaj nazwe sklepu: ";
    cin >> nazwa;
  }
  double cena;
  cout << "Podaj cene: ";
  cin >> cena;
  while(cena < 0.) {
    cout << "Cena nie moze byc ujemna!\n";
    cout << "Podaj cene: ";
    cin >> cena;
  }
  unsigned indeks = (unsigned)tow.sklepy().znajdz(nazwa);
  tow.ceny()[indeks] = cena;
}

void usun_towar_ze_sklepu(towar& tow) {
  cout << "Podaj nazwe sklepu: ";
  string nazwa;
  cin >> nazwa;
  int indeks;
  while((indeks = tow.sklepy().znajdz(nazwa)) == -1) {
    cout << "Towaru nie ma w tym sklepie!\n";
    cout << "Podaj nazwe sklepu: ";
    cin >> nazwa;
  }
  tow.sklepy().usun((unsigned)indeks);
  tow.ceny().usun((unsigned)indeks);
}

void modyfikuj_towar() {
  int numer = podaj_numer_towaru();
  if(numer == -1) {
    return;
  }

  towar& tow = baza_towarow::singleton().wszystkie()[(unsigned)numer];

  while(true) {
    pokaz_info_o_towarze(tow);
    cout << "Co chcesz zmienic::\n";
    cout << "1 - Zmien nazwe\n";
    cout << "2 - Dodaj towar do sklepu\n";
    cout << "3 - Modyfikuj cene w sklepie\n";
    cout << "4 - Usun towar ze sklepu\n";
    cout << "p - Powrot\n";
    cout << "\nWybierz: ";
    char wybor;
    
    cin >> wybor;
    switch(wybor) {
    case '1':
      zmien_nazwe_towaru(tow);
      break;
    case '2':
      dodaj_towar_do_sklepu(tow);
      break;
    case '3':
      modyfikuj_cene_w_sklepie(tow);
      break;
    case '4':
      usun_towar_ze_sklepu(tow);
      break;
    case 'p':
    case 'P':
      return;
    default:
      cout << "\nNie ma takiej opcji! Sprobuj jeszcze raz!\n\n";
      break;
    }
  }
}

void dodaj_towar() {
  towar nowy;
  cout << "Podaj nazwe nowego towaru: ";
  cin >> nowy.nazwa();
  baza_towarow::singleton().wszystkie().dodaj(nowy);
}

void usun_towar() {
  unsigned numer = podaj_numer_towaru();
  baza_towarow::singleton().wszystkie().usun(numer);
}

void pokaz_towary() {
  while(true) {
    cout << "Menu towarow:\n";
    cout << "1 - Pokaz wszystkie towary\n";
    cout << "2 - Wyszukaj po nazwie\n";
    cout << "3 - Wyszukaj po cenie\n";
    cout << "4 - Pokaz towar\n";
    cout << "5 - Modyfikuj towar\n";
    cout << "6 - Dodaj towar\n";
    cout << "7 - Usun towar\n";
    cout << "p - Powrot\n";
    cout << "\nWybierz: ";
    char wybor;
    
    cin >> wybor;
    switch(wybor) {
    case '1':
      pokaz_wszystkie_towary();
      break;
    case '2':
      wyszukaj_towar_po_nazwie();
      break;
    case '3':
      wyszukaj_towar_po_cenie();
    case '4':
      pokaz_towar();
      break;
    case '5':
      modyfikuj_towar();
      break;
    case '6':
      dodaj_towar();
      break;
    case '7':
      usun_towar();
    case 'p':
    case 'P':
      return;
    default:
      cout << "\nNie ma takiej opcji! Sprobuj jeszcze raz!\n\n";
      break;
    }
  }
}


void pokaz_wszystkie_sklepy() {
  cout << "Wszystkie sklepy:\n";
  wektor<sklep>& sklepy = baza_sklepow::singleton().wszystkie();
  for(unsigned i = 0; i < sklepy.ilosc(); ++i) {
    cout << i << " - " << sklepy[i].nazwa() << endl;
  }
}


void pokaz_info_o_sklepie(const sklep& s) {
  cout << "Informacje o sklepie:\n";
  cout << "Nazwa:" << s.nazwa() << endl;
  cout << "Adresy:\n";
  for(unsigned i = 0; i < s.adresy().ilosc(); ++i) {
    cout << "  " << i << " - " << s.adresy()[i] << endl;
  }
  cout << "------------" << endl;
}

void wyszukaj_sklep_po_nazwie() {
  std::string nazwa;
  cout << "Podaj nazwe sklepu do wyszukania: ";
  cin >> nazwa;
  sklep skl = baza_sklepow::singleton().znajdz_po_nazwie(nazwa);
  if(skl == sklep::PUSTY) {
    cout << "Brak takiego sklepu w bazie!\n";
  } else {
    pokaz_info_o_sklepie(skl);
  }
}

int podaj_numer_sklepu() {
  int numer;
  cout << "Podaj numer sklepu: ";
  cin >> numer;
  while((numer < 0 || numer >= (int)baza_sklepow::singleton().wszystkie().ilosc()) && numer != -1) {
    cout << "Nie ma takiego sklepu. Sprobuj jeszcze raz: ";
    cin >> numer;
  }

  return numer;
}

void pokaz_sklep() {
  int numer = podaj_numer_sklepu();
  if(numer == -1) {
    return;
  }

  pokaz_info_o_sklepie(baza_sklepow::singleton().wszystkie()[(unsigned)numer]);
}

void dodaj_sklep() {
  sklep nowy;
  cout << "Podaj nazwe nowego sklepu: ";
  cin >> nowy.nazwa();
  baza_sklepow::singleton().wszystkie().dodaj(nowy);
}

void usun_sklep() {
  unsigned numer = podaj_numer_sklepu();
  baza_sklepow::singleton().wszystkie().usun(numer);
}

void zmien_nazwe_sklepu(sklep& skl) {
  cout << "Podaj nowa nazwe: ";
  cin >> skl.nazwa();
}

void dodaj_adres(sklep& skl) {
  string adres;
  cout << "Podaj nowy adres: ";
  cin >> adres;
  while(skl.adresy().znajdz(adres) != -1) {
    cout << "Ten sklep ma już taki adres!\n";
    cout << "Podaj nowy adres: ";
    cin >> adres;
  }
  skl.adresy().dodaj(adres);
}

void modyfikuj_adres(sklep& skl) {
  int numer;
  cout << "Podaj numer adresu: ";
  cin >> numer;
  while((numer < 0 || numer >= (int)skl.adresy().ilosc()) && numer != -1) {
    cout << "Zly numer adresu!\n";
    cout << "Podaj numer adresu: ";
    cin >> numer;
  }
  if(numer == -1) {
    return;
  }

  string adres;
  cout << "Podaj adres po modyfikacji: ";
  cin >> adres;
  skl.adresy()[(unsigned)numer] = adres;
}

void usun_adres(sklep& skl) {
  int numer;
  cout << "Podaj numer adresu: ";
  cin >> numer;
  while((numer < 0 || numer >= (int)skl.adresy().ilosc()) && numer != -1) {
    cout << "Zly numer adresu!\n";
    cout << "Podaj numer adresu: ";
    cin >> numer;
  }
  if(numer == -1) {
    return;
  }

  skl.adresy().usun((unsigned)numer);  
}


void modyfikuj_sklep() {
  int numer = podaj_numer_sklepu();
  if(numer == -1) {
    return;
  }

  sklep& skl = baza_sklepow::singleton().wszystkie()[(unsigned)numer];

  while(true) {
    pokaz_info_o_sklepie(skl);
    cout << "Co chcesz zmienic::\n";
    cout << "1 - Zmien nazwe\n";
    cout << "2 - Dodaj adres\n";
    cout << "3 - Modyfikuj adres\n";
    cout << "4 - Usun adres\n";
    cout << "p - Powrot\n";
    cout << "\nWybierz: ";
    char wybor;
    
    cin >> wybor;
    switch(wybor) {
    case '1':
      zmien_nazwe_sklepu(skl);
      break;
    case '2':
      dodaj_adres(skl);
      break;
    case '3':
      modyfikuj_adres(skl);
      break;
    case '4':
      usun_adres(skl);
      break;
    case 'p':
    case 'P':
      return;
    default:
      cout << "\nNie ma takiej opcji! Sprobuj jeszcze raz!\n\n";
      break;
    }
  }
}


void pokaz_sklepy() {
  while(true) {
    cout << "Menu sklepow:\n";
    cout << "1 - Pokaz wszystkie sklepy\n";
    cout << "2 - Wyszukaj po nazwie\n";
    cout << "3 - Pokaz sklep\n";
    cout << "4 - Modyfikuj sklep\n";
    cout << "5 - Dodaj sklep\n";
    cout << "6 - Usun sklep\n";
    cout << "p - Powrot\n";
    cout << "\nWybierz: ";
    char wybor;
    
    cin >> wybor;
    switch(wybor) {
    case '1':
      pokaz_wszystkie_sklepy();
      break;
    case '2':
      wyszukaj_sklep_po_nazwie();
      break;
    case '3':
      pokaz_sklep();
      break;
    case '4':
      modyfikuj_sklep();
      break;
    case '5':
      dodaj_sklep();
      break;
    case '6':
      usun_sklep();
    case 'p':
    case 'P':
      return;
    default:
      cout << "\nNie ma takiej opcji! Sprobuj jeszcze raz!\n\n";
      break;
    }
  }
}

void menu_glowne() {
  while(true) {
    cout << "Menu glowne:\n";
    cout << "1 - Wczytaj baze z pliku\n";
    cout << "2 - Zapisz baze do pliku\n";
    cout << "3 - Pokaz sklepy\n";
    cout << "4 - Pokaz towary\n";
    cout << "5 - Pokaz zestawienie\n";
    cout << "x - Wyjdz\n";
    cout << "\nWybierz: ";
    char wybor;
    
    cin >> wybor;
    switch(wybor) {
    case '1':
      wczytaj_baze();
      break;
    case '2':
      zapisz_baze();
      break;
    case '3':
      pokaz_sklepy();
      break;
    case '4':
      pokaz_towary();
      break;
    case '5':
      pokaz_zestawienie();
      break;
    case 'x':
    case 'X':
      return;
    default:
      cout << "\nNie ma takiej opcji! Sprobuj jeszcze raz!\n\n";
      break;
    }
  }
}

int main() {
  menu_glowne();
}


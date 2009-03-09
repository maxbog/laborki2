#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class K {
public:
  K() : stalo(0), zmienno(0.0), znak('a'), PI(3.14) {
    cout << "Dziala konstruktor domyslny" << endl;
  }

  K(int _stalo, double _zmienno, char _znak) : stalo(_stalo), zmienno(_zmienno), znak(_znak), PI(3.14) {
    cout << "Dziala konstruktor z argumentami" << endl;
  }

  K(const K& orig) : stalo(orig.stalo), zmienno(orig.zmienno), znak(orig.znak), PI(3.14) {
    cout << "Dziala konstruktor kopiujacy" << endl;
  }

  ~K() {
    cout << "Dziala destruktor" << endl;
  }

  int get_stalo() const {
    return stalo;
  }

  double get_zmienno() const {
    return zmienno;
  }

  char get_znak() const {
    return znak;
  }

  double get_PI() const {
    return PI;
  }

  void set_stalo(int _stalo) {
    stalo = _stalo;
  }

  void set_zmienno(double _zmienno) {
    zmienno = _zmienno;
  }

  void set_znak(char _znak) {
    znak = _znak;
  }

  void wypisz() const {
    cout << "n = " << stalo << " z = " << zmienno << " c = " << znak << " pi = " << PI << endl;
  }

private:
  int stalo;
  double zmienno;
  char znak;
  const double PI;
};

void fun1(K obiekt) {
  cout << "Poczatek funkcji fun1" << endl;
  obiekt.wypisz();
  cout << "Koniec funkcji fun1" << endl;
}

K fun2() {
  cout << "Poczatek funkcji fun2" << endl;
  int n;
  double z;
  char c;
  
  cout << "Podaj n, z, c: ";
  cin >> n >> z >> c;

  K obiekt;
  obiekt.set_stalo(n);
  obiekt.set_zmienno(z);
  obiekt.set_znak(c);

  cout << "Koniec funkcji fun2" << endl;
  return obiekt;
}

int main() {
  K k1;
  K k2( 1 , 1.5 , 'b');
  K k3(k2);
  K *wk = new K;
  
  wk->set_stalo(2);
  wk->set_zmienno(1.5);
  wk->set_znak('c');
  
  cout << "wywolanie funkcji fun1(fun2())" << endl;
  fun1(fun2());
  
  cout << "Obiekt k1 wypisz!:" << endl;
  k1.wypisz();
  
  cout << "Obiekt k2 wypisz!:" << endl;
  k2.wypisz();
  
  cout << "Obiekt k3 wypisz!:" << endl;
  k3.wypisz();
  
  cout << "Obiekt dynamiczny dostep przez wskaznik wypisz!:" << endl;
  wk->wypisz();
  
  cout << "Obiekt dynamiczny dostep jak obiektu wypisz!:" << endl;
  (*wk).wypisz();
  
  int a;
  cin >> a;
  delete wk;
  
  return 0;         
} 

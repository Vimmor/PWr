#ifndef TABLICA_HH
#define TABLICA_HH
using namespace std;

template <typename T>
class Tablica{
	 T *tab;
	 int rozmiar;
public:
	T operator [](int licz) const {
		return tab[licz];
	 }
	T& operator [](int licz) {
		return tab[licz];
	}
	 void wypelnij(int);
	 void wypisz();
};

#endif
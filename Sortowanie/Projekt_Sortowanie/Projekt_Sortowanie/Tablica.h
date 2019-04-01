#ifndef TABLICA_HH
#define TABLICA_HH

template <typename T>
class Tablica{
	 T *tab;
	 T *pom;
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
	 void kopiuj();
	 void zapisz(Tablica<T> t);

	 void quick(int poczatek, int koniec);
	 void merge(int poczatek,int srodek,int koniec);
	 void merge_sort(int poczatek, int koniec);
	 Tablica<T>(int rozmiar);
	 ~Tablica<T>();
};

template<typename T>
Tablica<T>::Tablica(int rozmiar) {
	this->rozmiar = rozmiar;
	this->wypelnij(rozmiar);
}
template<typename T>
Tablica<T>::~Tablica<T>(){}
#endif
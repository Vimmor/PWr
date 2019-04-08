#ifndef TABLICA_HH
#define TABLICA_HH

template <typename T>
class Tablica {
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
	void kopiuj(T*,T*);
	void zapisz();
	void zwolnij_pamiec();
	void odwroc(T*);
	T* getTab();
	T * getPom();
	int getRozmiar();

	void quick_sort(int, int);
	void heap_sort(T*, T*);
	void sortowanie_wstawianie(int);
	void introspective_sort(int*, int*, int);
	int partycjonowanie(int, int);
	void merge(int, int, int);
	void merge_sort(int, int);
	void shell_sort();

	void test(double);
	void sortowanie_odwrotna_kolejnosc();
	void sortowanie_losowe();
	void menu();

};
#endif
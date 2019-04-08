#include "pch.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include "Tablica.h"
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

template <typename T>
void Tablica<T>::wypelnij(int rozmiar){
		tab = new int[rozmiar];
		this->rozmiar = rozmiar;
		srand(time(NULL));
		for (int i = 0; i < rozmiar; i++) {
			tab[i] = rand()%10000+1;
		} 
		pom = new int[rozmiar];
		kopiuj(pom,tab);
}

template <typename T>
void Tablica<T>::wypisz(){
		for (int i = 0;i<rozmiar; i++) {
			cout << tab[i] << " ";
		}
		cout << "\n"<<endl;
		for (int i = 0; i <rozmiar; i++) {
			cout << pom[i] << " ";
		}
}

template <typename T>
void Tablica<T>::kopiuj(T *tab,T *tab2){
	for (int i = 0; i < rozmiar; i++) {
		tab[i] = tab2[i];
	}
}

template <typename T>
void Tablica<T>::zapisz() {
	fstream plik;
	plik.open("Wynik_sortowania.txt", ios_base::app); //dopisywanie danych na koniec pliku
	plik << "Kolejna tablica:" << endl;
	for (int i =0; i < rozmiar; i++) {
		plik << tab[i]<< " ";
	}
	plik << endl;
	plik.close();
}

template<typename T>
void Tablica<T>::zwolnij_pamiec() {
	delete[] tab;
	delete[] pom;
}

/*Funkcja odwracajaca tablice, uzywana w przypadku
gdy liczby sa w odwrotnej kolejnosci*/
template<typename T>
void Tablica<T>::odwroc(T *tab) {
	T *tymczasowa = new T[rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		tymczasowa[i] = tab[i];
	}
	for(int i=0;i<rozmiar;i++){
		tab[i] = tymczasowa[rozmiar - 1 - i];
	}
}

template<typename T>
T* Tablica<T>::getTab() {
	return tab;
}

template<typename T>
T* Tablica<T>::getPom() {
	return pom;
}

template<typename T>
int Tablica<T>::getRozmiar() {
	return rozmiar;
}

template<typename T>
int Tablica<T>::partycjonowanie(int poczatek,int koniec) {
	int piwot = pom[koniec];
	int k = poczatek, pom1;
	
	for (int i = poczatek; i < koniec; i++) {
		if (pom[i] <= piwot) {
			pom1 = pom[i];
			pom[i] = pom[k];
			pom[k] = pom1;
			k++;
		}
	}
	pom[koniec] = pom[k];
	pom[k] = piwot;
	return k;
}

template<typename T>
void Tablica<T>::quick_sort(int poczatek, int koniec) {
	if (poczatek < koniec) {
		int piwot = partycjonowanie(poczatek, koniec);
		quick_sort(poczatek, piwot - 1);
		quick_sort(piwot + 1, koniec);
	}
}

template<typename T>
void Tablica<T>::heap_sort(T *lewy,T *prawy) {
	make_heap(lewy,prawy);
	sort_heap(lewy,prawy);
}

template<typename T>
void Tablica<T>::sortowanie_wstawianie(int n){
	int pom2, k;
	for (int i = 1; i < n; i++) {
		pom2 = pom[i];
		k = i - 1;

		while (k >= 0 && pom[k] > pom2) {
			pom[k + 1] = pom[k];
			k--;
		}
		pom[k+1] = pom2;
	}
}

template<typename T>
void Tablica<T>::introspective_sort(int *poczatek,int *koniec,int glebokosc) {
	if ((koniec - poczatek) < 16)
		sortowanie_wstawianie(rozmiar);
	else if (glebokosc == 0)
		heap_sort(poczatek, koniec + 1);
	else{
		int piwot = partycjonowanie(0,rozmiar-1);
		introspective_sort(poczatek,pom + piwot, glebokosc - 1);
		introspective_sort(pom + piwot + 1, koniec, glebokosc - 1);
	}
}

template<typename T>
void Tablica<T>::merge(int poczatek, int srodkowy, int koniec) {
	int i = poczatek, j = srodkowy + 1, k = 0;
	int *pom2 = new int[koniec-poczatek];

	while (i <= srodkowy && j <= koniec) {
		if(pom[j] < pom[i]) {
			pom2[k] = pom[j];
			j++;
		}
		else{
			pom2[k] = pom[i];
			i++;
		}	
		k++;
	}
	if (i <= srodkowy) {
		while (i <= srodkowy) {
			pom2[k] = pom[i];
			i++;
			k++;
		}
	}
	else {
		while (j <= koniec) {
			pom2[k] = pom[j];
			j++;
			k++;
		}
	}
	for (int i = 0; i <= koniec-poczatek; i++) {
		pom[poczatek + i] = pom2[i];
	}
}

template<typename T>
void Tablica<T>::merge_sort(int poczatek, int koniec){
	int srodkowy;
	if (poczatek!=koniec) {
		srodkowy = (poczatek + koniec) / 2;
		merge_sort(poczatek, srodkowy);
		merge_sort(srodkowy+1, koniec);
		merge(poczatek, srodkowy, koniec);
	}
}

template<typename T>
void Tablica<T>::shell_sort(){
	int odstep = rozmiar / 2;
	while (odstep >= 1) {
		for (int i = odstep; i < rozmiar; i++) {
			int tymczasowy = pom[i];
			int j;
			for (j = i; j >= odstep && pom[j - odstep] > tymczasowy; j -= odstep)
				pom[j] = pom[j - odstep];
			pom[j] = tymczasowy;
		}
		odstep /= 2;
	}
}
template<typename T>
void Tablica<T>::test(double ilosc) {
	int x = (rozmiar*ilosc)/100;
	clock_t t;
	double czas, wynik = 0;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		quick_sort(0,x-1);
		kopiuj(tab, pom);
		t = clock();
		quick_sort(0, rozmiar - 1);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		//zapisz();
		zwolnij_pamiec();
	}
	cout << "Czasy sortowania poszczegolnych algorytmow to:\nSortowanie szybkie:" << wynik << endl;
	wynik = 0;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		merge_sort(0, x - 1);
		kopiuj(tab, pom);
		t = clock();
		merge_sort(0, rozmiar - 1);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		//zapisz();
		zwolnij_pamiec();
	}
	cout << "Sortowanie przez Scalanie:" << wynik << endl;
	wynik = 0;
	int glebokosc = log(rozmiar) * 2;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		introspective_sort(pom,pom+x,glebokosc);
		kopiuj(tab, pom);
		t = clock();
		introspective_sort(pom,pom+rozmiar,glebokosc);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		//zapisz();
		zwolnij_pamiec();
	}
	cout << "Sortowanie Introspektywne (Introsort):" << wynik << endl;
}

template<typename T>
void Tablica<T>::sortowanie_odwrotna_kolejnosc() {
	clock_t t;
	double czas,wynik=0;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		quick_sort(0, rozmiar - 1);
		odwroc(pom);
		t = clock();
		quick_sort(0, rozmiar - 1);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		zwolnij_pamiec();
	}
	wynik = 0;
	cout << "Czasy sortowania poszczegolnych algorytmow to:\nSortowanie szybkie:" << wynik << endl;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		merge_sort(0, rozmiar - 1);
		odwroc(pom);
		t = clock();
		merge_sort(0, rozmiar - 1);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		zwolnij_pamiec();
	}
	cout << "Sortowanie przez Scalanie:" << wynik << endl;
	wynik = 0;
	int glebokosc = log(rozmiar) * 2;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		introspective_sort(pom,pom+rozmiar,glebokosc);
		odwroc(pom);
		t = clock();
		introspective_sort(pom,pom+rozmiar,glebokosc);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		zwolnij_pamiec();
	}
	cout << "Sortowanie Introspektywne (Introsort):" << wynik << endl;
}

template<typename T>
void Tablica<T>::sortowanie_losowe() {
	clock_t t;
	double czas,wynik=0;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		t = clock();
		quick_sort(0, rozmiar - 1);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		zwolnij_pamiec();
	}
	cout << "Czasy sortowania poszczegolnych algorytmow to:\nSortowanie szybkie:" << wynik << endl;
	wynik = 0;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		t = clock();
		merge_sort(0, rozmiar - 1);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		zwolnij_pamiec();
	}
	cout << "Sortowanie przez scalanie:"<< wynik << endl;
	wynik = 0;
	int glebokosc = log(rozmiar) * 2;
	for (int i = 0; i < 100; i++) {
		wypelnij(rozmiar);
		t = clock();
		introspective_sort(pom, pom + rozmiar, glebokosc);
		czas = (clock() - t) / (double)CLOCKS_PER_SEC;
		wynik += czas;
		zwolnij_pamiec();
	}
	cout << "Sortowanie Introspektywne (Introsort)"<< wynik << endl;
	wynik = 0;

}

template<typename T>
void Tablica<T>::menu() {
	int wybor;
	cout << "Witaj w programie do sortowania elementow calkowitoliczbowych\n";
	do {
		cout << "1. Podaj rozmiar tablic do posortowania (10000,50000,100000,500000,1000000)\n2. 25% poczatkowych elementow posortowanych\n3. 50% poczatkowych elementow posortowanych\n4. 75% poczatkowych elementow posortowanych\n5. 95% poczatkowych elementow posortowanych\n6. 99% poczatkowych elementow posortowanych\n7. 99,7% poczatkowych elementow posortowanych\n8. Wszystkie elementy juz posortowane, ale w odwrotnej kolejnosci\n9. Wszystkie elementy losowe.\n0. Zakoncz dzialanie programu\n";
		cin >> wybor;
		switch (wybor) {
		case 1: {
			int ilosc;
			cout << "Podaj rozmiar:";
			cin >> ilosc;
			wypelnij(ilosc);
			break;
		}
		case 2: {
			test(25);
			break;
		}
		case 3: {
			test(50);
			break;
		}
		case 4: {
			test(75);
			break;
		}
		case 5: {
			test(95);
			break;
		}
		case 6: {
			test(99);
			break;
		}
		case 7: {
			test(99.7);
			break;
		}
		case 8: {
			sortowanie_odwrotna_kolejnosc();
			break;
		}
		case 9: {
			sortowanie_losowe();
			break;
		}
		case 0: break;
		}
	} while (wybor != 0);
}
template class Tablica<int>;
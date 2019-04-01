#include "pch.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include "Tablica.h"
#include <algorithm>
using namespace std;

template <typename T>
void Tablica<T>::wypelnij(int rozmiar){
		this->rozmiar = rozmiar;
	    tab = new T[rozmiar]; 
		srand(time(NULL));
		for (int i = 0; i < this->rozmiar; i++) {
			tab[i] = rand()%5000;
		}
	}

template <typename T>
void Tablica<T>::wypisz(){
		for (int i = 0;i<this->rozmiar; i++) {
			cout << tab[i] << " ";
		}
		cout << "\n"<<endl;
}

template <typename T>
void Tablica<T>::kopiuj(){
	pom = new T[this->rozmiar];
	for (int i = 0; i < this->rozmiar; i++) {
		pom[i] = this->tab[i];
	}
}

template <typename T>
void Tablica<T>::zapisz(Tablica<T> t) {
	fstream plik;
	plik.open("Wynik.txt", ios_base::app); //dopisywanie danych na koniec pliku
	plik << "Kolejna tablica:" << endl;
	for (int i = 0; i < t.rozmiar; i++) {
		plik << t.tab[i]<< " ";
	}
	plik << endl;
	plik.close();
}

template<typename T>
void Tablica<T>::quick(int poczatek, int koniec) {
	if (koniec <= poczatek)
		return;
	int i = poczatek - 1, j = koniec + 1;
	int piwot = this->pom[(poczatek + koniec) / 2];

	while (1) {
		while (piwot > this->pom[++i]);
		while (piwot < this->pom[--j]);
		if (i <= j)
			swap(pom[i], pom[j]);
		else
			break;
	}
	if (j > poczatek)
		quick(poczatek, j);
	if (i < koniec)
			quick(i, koniec);
}

template<typename T>
void Tablica<T>::merge(int poczatek, int srodek, int koniec) {
	this->kopiuj();
	int k = srodek + 1, j = poczatek;

	for (int i = poczatek; i <= koniec; i++) {
		if (j <= srodek) {
			if (k <= koniec) {
				if (pom[k] < pom[j])
					tab[i] = pom[k++];
				else
					tab[i] = pom[j++];
			}
			else
				tab[i] = pom[j++];
		}
		else
			tab[i] = pom[k++];
	}
}
template<typename T>
void Tablica<T>::merge_sort(int poczatek, int koniec){
	int srodek = (poczatek + koniec) / 2;
	if (tab[poczatek] != tab[koniec]) {
		merge_sort(poczatek, srodek);
		merge_sort(srodek + 1, koniec);
	}
	merge(poczatek, srodek, koniec);
}
template class Tablica<int>;
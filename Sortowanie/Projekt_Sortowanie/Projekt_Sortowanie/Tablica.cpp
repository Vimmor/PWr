#include "pch.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Tablica.h"
using namespace std;

template <typename T>
void Tablica<T>::wypelnij(int rozmiar) {
		this->rozmiar = rozmiar;
	    tab = new T[rozmiar];
		srand(time(NULL));
		for (int i = 0; i < this->rozmiar; i++) {
			tab[i] = rand()%5000;
		}
		this->wypisz();
	}

template <typename T>
void Tablica<T>::wypisz() {
		for (int i = 0; i < this->rozmiar; i++) {
			cout << this->tab[i] << " ";
		}
	}

template class Tablica<int>;
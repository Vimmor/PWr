#include "pch.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Tablica.h"
using namespace std;

void Tablica::wypelnij(int rozmiar) {
		this->rozmiar = rozmiar;
	    tab = new int[rozmiar];
		srand(time(NULL));
		for (int i = 0; i < this->rozmiar; i++) {
			tab[i] = rand()%5000;
		}
		this->wypisz();
	}
void Tablica::wypisz() {
		for (int i = 0; i < this->rozmiar; i++) {
			cout << this->tab[i] << " ";
		}
	}

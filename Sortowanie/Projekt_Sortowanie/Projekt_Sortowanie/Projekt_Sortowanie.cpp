#include "pch.h"
#include <iostream>
#include "Tablica.h"
#include <cmath>
#include <ctime>
int main() {
	Tablica<int> t;
	clock_t time;
	double wynik;
	t.wypelnij(100);
	t.quick_sort(0, 99);
	t.wypisz();
	t.zwolnij_pamiec();
	std::cout << std::endl;
	t.wypelnij(100);
	t.wypisz();
	time = std::clock();
	wynik = (std::clock() - time) / (double)CLOCKS_PER_SEC;
	std::cout << wynik;
	return 0;
}


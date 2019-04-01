#include "pch.h"
#include <iostream>
#include "Tablica.h"
int main() {
	Tablica<int> t(100);
	t.wypisz();
	t.merge_sort(0,99);
	t.wypisz();	
	return 0;
}


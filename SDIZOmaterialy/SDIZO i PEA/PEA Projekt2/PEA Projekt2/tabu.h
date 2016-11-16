#pragma once
#include "sasiad.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

class tabu
{

private:

	int *Tabtabu;		//tablica tabu
	int taburozmiar;	//rozmiar tablicy
	sasiad *perm;		//wskaünik na obiekt permutacja
		
public:

	tabu(sasiad* p , int roz);
	bool tabulist( int zad1, int zad2 );	//funkcja sprawdzenia listy tabu
	void algorytmtabu();					//algorytm tabu search
	~tabu(void);
};
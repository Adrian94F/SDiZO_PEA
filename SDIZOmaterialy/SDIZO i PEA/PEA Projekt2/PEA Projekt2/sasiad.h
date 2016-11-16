#pragma once
#include "zadanie.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>

class sasiad
{

public:

	zadanie **zadania;	//przechowuje posortowane wska�niki na zadania
	int liczbazadan;	//przechowuje lioczb� zada�
	int *permutacja;	//przechowuje aktualnie najlepsz� permutacj�
	int najczas;		//przechowuje najlepszy czas
	int *pomiar;		//przechowuje aktualnie wylosowane rozwiazanie sasiednie
	int *tmp;           //dodatkowa tymczasowa permutacja

	sasiad( zadanie** zad, int l_zad );
	
	void losuj();						//losuje dwa rozwiazania sasiednie
	void ustaw(int zad_1 , int zad_2);	//ustawia konkretnee rozwi�zanie s�siednie
	int obliczopoz();					//oblicza op�nienie permutacji
	int najlepszy();					//zwraca czas najleposzego rozwi�zania
	void akceptuj();					//za aktualnie najlepsz� permutacj� podstawia pomomiar
	void nieakceptuj();					//przywraca poprzedni stan w pomiar
	int* permut();						//zwraca aktualna permutacje
	~sasiad(void);
};

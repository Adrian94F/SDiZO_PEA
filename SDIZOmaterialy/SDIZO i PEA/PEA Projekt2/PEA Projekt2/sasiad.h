#pragma once
#include "zadanie.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>

class sasiad
{

public:

	zadanie **zadania;	//przechowuje posortowane wskaŸniki na zadania
	int liczbazadan;	//przechowuje lioczbê zadañ
	int *permutacja;	//przechowuje aktualnie najlepsz¹ permutacjê
	int najczas;		//przechowuje najlepszy czas
	int *pomiar;		//przechowuje aktualnie wylosowane rozwiazanie sasiednie
	int *tmp;           //dodatkowa tymczasowa permutacja

	sasiad( zadanie** zad, int l_zad );
	
	void losuj();						//losuje dwa rozwiazania sasiednie
	void ustaw(int zad_1 , int zad_2);	//ustawia konkretnee rozwi¹zanie s¹siednie
	int obliczopoz();					//oblicza opóŸnienie permutacji
	int najlepszy();					//zwraca czas najleposzego rozwi¹zania
	void akceptuj();					//za aktualnie najlepsz¹ permutacjê podstawia pomomiar
	void nieakceptuj();					//przywraca poprzedni stan w pomiar
	int* permut();						//zwraca aktualna permutacje
	~sasiad(void);
};

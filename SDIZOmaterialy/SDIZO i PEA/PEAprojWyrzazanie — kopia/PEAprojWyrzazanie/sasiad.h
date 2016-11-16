#pragma once
#include "zadanie.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>

class sasiad
{
private:
	zadanie **zadania;			//zawiera posortowane wska�niki na zadania
	int liczba;					//przechowuje lioczb� zada�
	int *permutacja;			//zawiera aktualna, najlepsz� permutacj�
	int najlepszy;				//przechowuje najlepszy czas
	int *pomiar;				//zawiera aktualne, wylosowane rozwiazanie sasiednie
public:
	sasiad( zadanie** zad, int l_zad );	
	
	void losuj();						//losuje dwa rozwiazania sasiednie
	int obliczopoz();					//oblicza op�nienie permutacji
	int najczas();						//zwraca czas najleposzego rozwi�zania
	void akceptuj();					//za aktualnie najlepsz� permutacj� podstawia pom1
	void nieakceptuj();					//nie akceptuje (przywraca poprzedni stan)
	int* permut();						//zwraca aktualna permutacje
	~sasiad(void);
};

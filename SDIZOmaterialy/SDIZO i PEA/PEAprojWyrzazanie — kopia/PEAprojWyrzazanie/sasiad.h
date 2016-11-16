#pragma once
#include "zadanie.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>

class sasiad
{
private:
	zadanie **zadania;			//zawiera posortowane wskaŸniki na zadania
	int liczba;					//przechowuje lioczbê zadañ
	int *permutacja;			//zawiera aktualna, najlepsz¹ permutacjê
	int najlepszy;				//przechowuje najlepszy czas
	int *pomiar;				//zawiera aktualne, wylosowane rozwiazanie sasiednie
public:
	sasiad( zadanie** zad, int l_zad );	
	
	void losuj();						//losuje dwa rozwiazania sasiednie
	int obliczopoz();					//oblicza opóŸnienie permutacji
	int najczas();						//zwraca czas najleposzego rozwi¹zania
	void akceptuj();					//za aktualnie najlepsz¹ permutacjê podstawia pom1
	void nieakceptuj();					//nie akceptuje (przywraca poprzedni stan)
	int* permut();						//zwraca aktualna permutacje
	~sasiad(void);
};

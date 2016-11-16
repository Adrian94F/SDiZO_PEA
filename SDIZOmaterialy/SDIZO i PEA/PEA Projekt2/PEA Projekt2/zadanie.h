#pragma once

class zadanie
{

private:

	int info;
	int oczekiwanie;
	int wykonanie;
	int priorytet;

public:

	zadanie( int _id, int oczeki, int wykon, int priory );
	int koniec( int rozpoczecie );		//czas potrzebny do wykonania
	int prioryt();						//zwraca priorytet
	int informa();						//zwraca info
	int opoznienie( int rozpoczecie );	//zwraca opóŸnienie
	~zadanie(void);
};

#pragma once

class zadanie
{
private:
	int info;
	int zakonczenie;
	int wykonanie;
	int priorytet;

public:
	zadanie( int _info, int _zakonczenie, int _wykonanie, int _priorytet );
	
	int get_koniec( int rozpoczecie );		//czas konieczny do wykonania
	int get_priorytet();					//zwraca priorytet
	int get_info();							//zwraca informacje o id
	int get_opoznienie( int rozpoczecie );	//zwraca opoünienie

	~zadanie(void);
};

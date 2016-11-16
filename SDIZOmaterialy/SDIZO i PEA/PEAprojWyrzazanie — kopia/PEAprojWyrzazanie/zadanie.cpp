#include "zadanie.h"

zadanie::zadanie( int _info, int _zakonczenie, int _wykonanie, int _priorytet )
{
	this -> info = _info;
	this -> wykonanie = _wykonanie;
	this -> zakonczenie = _zakonczenie;
	this -> priorytet = _priorytet;
}

int zadanie::get_opoznienie( int czas_rozpoczecia )
{
	return (czas_rozpoczecia + this->wykonanie - this->zakonczenie)*this->priorytet;
}

int zadanie::get_priorytet()
{
	return this -> priorytet;
}

int zadanie::get_koniec( int czas_rozpoczecia )
{
	return czas_rozpoczecia + this->wykonanie;
}

int zadanie::get_info()
{
	return this -> info;
}

zadanie::~zadanie(void)
{
}

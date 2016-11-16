#include "zadanie.h"

zadanie::zadanie( int inf, int oczekiwanezak, int wykonaniezad, int priorytetzad )
{
	this->info = inf;
	this->wykonanie = wykonaniezad;
	this->oczekiwanie = oczekiwanezak;
	this->priorytet = priorytetzad;
}

int zadanie::opoznienie( int rozpoczecie )
{
	return (rozpoczecie + this->wykonanie - this->oczekiwanie)*this->priorytet;
}

int zadanie::prioryt()
{
	return this->priorytet;
}

int zadanie::koniec( int rozpoczecie )
{
	return rozpoczecie + this->wykonanie;
}

int zadanie::informa()
{
	return this->info;
}

zadanie::~zadanie(void)
{
}

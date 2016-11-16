#pragma once
#include "zadanie.h"

class wezel
{
private:
	int liczba_zadan;
	int *permutacja;
	wezel **nastepniki;
	wezel *poprzednik;
public:
	wezel(int liczba_zadan, wezel* poprzednik);
	~wezel(void);
};

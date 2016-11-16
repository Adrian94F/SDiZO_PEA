#pragma once
#include "sasiad.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

class wyzarzanie
{
private:
	int czasmax;	//temperatura pocz�tkowa
	int czasmin;	//temperatura zako�czenia
	int czas;		//aktualna temperatura
	float a;
	sasiad* perm;	//wska�nik na obekt permutacja
	
public:
	wyzarzanie(sasiad* p, int _tmax, int _tmin, double _a);
	float akcept( int sn, int ss );		//funkcja akceptujaca
	int temp();							//funkcja zmniejszajaca temperature
	float losuj();						//losuje liczb� na przedziale [0,1)
	void wyzarz();						//funkcja wyzarzania o wyzarzania
	~wyzarzanie(void);
};

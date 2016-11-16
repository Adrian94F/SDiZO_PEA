#pragma once
#include "sasiad.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

class wyzarzanie
{

private:

	int tmax;		//temperatura pocz�tkowa
	int tmin;		//temperatura zako�czenia
	int t;			//aktualna temperatura
	float a;
	sasiad* perm;	//wska�nik na obiekt permutacja
	
public:

	wyzarzanie(sasiad* p, int _tmax, int _tmin, double _a);
	float akcept( int sn, int ss );			//funkcja akceptowalno�ci 
	int temp();								//zwraca zmiejszona temperatur� 
	float random();							//losuje liczb� z zakresu [0,1) 
	void algorytm();						//algorytm  wy�arzania
	~wyzarzanie(void);
};

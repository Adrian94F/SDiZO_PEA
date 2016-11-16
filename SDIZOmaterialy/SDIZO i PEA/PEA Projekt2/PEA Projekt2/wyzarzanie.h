#pragma once
#include "sasiad.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

class wyzarzanie
{

private:

	int tmax;		//temperatura pocz¹tkowa
	int tmin;		//temperatura zakoñczenia
	int t;			//aktualna temperatura
	float a;
	sasiad* perm;	//wskaŸnik na obiekt permutacja
	
public:

	wyzarzanie(sasiad* p, int _tmax, int _tmin, double _a);
	float akcept( int sn, int ss );			//funkcja akceptowalnoœci 
	int temp();								//zwraca zmiejszona temperaturê 
	float random();							//losuje liczbê z zakresu [0,1) 
	void algorytm();						//algorytm  wy¿arzania
	~wyzarzanie(void);
};

#include "wyzarzanie.h"

wyzarzanie::wyzarzanie(sasiad* p, int _tmax, int _tmin, double _a)
{
	this -> perm = p;
	this -> czasmax = _tmax;
	this -> czasmin = _tmin;
	this -> czas = czasmax;
	a = _a;
}

float wyzarzanie::akcept( int sn, int ss )
{
	double pom = exp((-1)*((double)sn-(double)ss)/czas);
	return pom;
}

int wyzarzanie::temp()
{
	return (int)(czas*a);
}

float wyzarzanie::losuj()
{
	float pom = (float)(rand()%100);
	pom /= 100;
	return pom;
}

void wyzarzanie::wyzarz()
{
	int i = 0;
	czas = czasmax;
	while( czas > czasmin )
	{
		this -> perm -> losuj();
		int pom = this -> perm -> obliczopoz();
		if( this -> perm -> najczas() > pom )
			this -> perm -> akceptuj();
		else if( losuj() < akcept(pom, this -> perm -> najczas()) )
			this -> perm -> akceptuj();
		else
			this -> perm -> nieakceptuj();
		czas = temp();
		i++;
	}
	//std::cout << "Liczba iteracji = " << i << "\t";
}

wyzarzanie::~wyzarzanie(void)
{
	if( this -> perm != 0 )
	{
		delete this -> perm;
		this -> perm = 0;
	}
}

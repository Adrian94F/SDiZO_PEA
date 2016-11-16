#include "wyzarzanie.h"

wyzarzanie::wyzarzanie(sasiad* p, int czasmax, int czasmin, double A)
{
	this->perm = p;
	this->tmax = czasmax;
	this->tmin = czasmin;
	this->t = tmax;
	a = A;
}

float wyzarzanie::akcept( int sn, int ss )
{
	double pom = exp((-1)*((double)sn-(double)ss)/t);
	return pom;
}

int wyzarzanie::temp()
{
	return (int)(t*a);
}

float wyzarzanie::random()
{
	float pom = (float)(rand()%100);
	pom /= 100;
	return pom;
}

void wyzarzanie::algorytm()
{
	int i = 0;
	t = tmax;
	while( t>tmin )
	{
		this->perm->losuj();
		int pom = this->perm->obliczopoz();
		if( this->perm->najlepszy() > pom )
			this->perm->akceptuj();

		else if( random()< akcept(pom, this->perm->najlepszy()) )
			this->perm->akceptuj();

		else
			this->perm->nieakceptuj();

		t = temp();
		i++;
	}
}

wyzarzanie::~wyzarzanie(void)
{
	if( this->perm != 0 )
	{
		delete this->perm;
		this->perm = 0;
	}
}

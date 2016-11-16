#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>
#include "zadanie.h"
#include "sasiad.h"
#include "wyzarzanie.h"

using namespace std;

int zmienna = 10000000;
double czas;

void wyswietl( int* t, int n )
{
	for( int i = 0 ; i<n ; i++ )
	cout << t[i] << ", ";
	cout << endl;
}

void wczytaj( int* p, int* w, int* t, int n, ifstream& plik)
{
	if( plik )
	{
		for( int i = 0 ; i<n ; i++ )
			plik >> p[i];
		for( int i = 0 ; i<n ; i++ )
			plik >> w[i];
		for( int i = 0 ; i<n ; i++ )
			plik >> t[i];
	}
	else
		cerr << "Blad!"<< endl;
}

int algorytm(int* p, int* w, int* t,int n, double alfa)
{
	zadanie** z = new zadanie*[n];
	for( int i = 0 ; i<n ; i++ )
	{
		z[i] = new zadanie(i,t[i],p[i],w[i]);
	}
	sasiad* s = new sasiad(z,n);

	wyzarzanie* wyz = new wyzarzanie(s,1000000,0,alfa);

	//algorytm
	LARGE_INTEGER start;
	LARGE_INTEGER koniec;
	LARGE_INTEGER freq;
	double dstart, dkoniec, df;
	double pom = 0;
	int pom1 = INT_MAX;
	for( int i = 0 ; i<10 ; i++ )
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		wyz->wyzarz();
		QueryPerformanceCounter(&koniec);
		dstart = start.LowPart;
		dkoniec = koniec.LowPart;
		df = freq.LowPart;
		dstart /= df;
		dkoniec /= df;
		pom += dkoniec-dstart;
		int time = s->najczas();
		if( pom1 > time )
			pom1 = time;
	}
	czas = pom/10;

	//koniec algorytmu
	if( wyz != 0 ){
		delete wyz;
		wyz = 0;
	}
	return pom1;
}

void main(void)
{
	ofstream wynik("wt40wynik2.txt");
	int* przetwarzanie;		//czasy przetwarzania
	int* kolejka;			//priorytety
	int* oczekiwanie;		//oczekiwany czas zakoñczenia
	int n = 40;				//liczba zadañ
	przetwarzanie = new int[n];
	kolejka = new int[n];
	oczekiwanie = new int[n];
	int pom;
	ifstream plik("wt40.txt");
	for( int i = 0 ; i<125 ; i++ )
	{
		wczytaj(przetwarzanie,kolejka,oczekiwanie,n,plik);

		pom = algorytm(przetwarzanie,kolejka,oczekiwanie,n,0.5);
		wynik << "0.5\t" << czas << "\t" << pom << "\t";

		pom = algorytm(przetwarzanie,kolejka,oczekiwanie,n,0.8);
		wynik << "0.8\t" << czas << "\t" << pom << "\t";

		pom = algorytm(przetwarzanie,kolejka,oczekiwanie,n,0.9999);
		wynik << "0.9999\t" << czas << "\t" << pom << "\t" << endl;
	}
}

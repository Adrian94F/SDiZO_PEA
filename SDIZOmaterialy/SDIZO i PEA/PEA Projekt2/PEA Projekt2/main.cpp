#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>
#include "zadanie.h"
#include "sasiad.h"
#include "wyzarzanie.h"
#include "tabu.h"

using namespace std;

int zmienna = 1000000;
double czas;

void wyswietl( int* t, int n )
{
	for( int i = 0 ; i<n ; i++ )
	{
		cout << t[i] << ", ";
	}
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

int f(int* p, int* w, int* t,int n, int roz)
{
	zadanie** z = new zadanie*[n];
	for( int i = 0 ; i<n ; i++ )
	{
		z[i] = new zadanie(i,t[i],p[i],w[i]);
	}
	sasiad* s = new sasiad(z,n);

	tabu* tabusearch = new tabu(s,roz); //pocz¹tek algorytm
	
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
		tabusearch->algorytmtabu();
		QueryPerformanceCounter(&koniec);
		dstart = start.LowPart;
		dkoniec = koniec.LowPart;
		df = freq.LowPart;
		dstart /= df;
		dkoniec /= df;
		pom += dkoniec-dstart;
		int time = s->najlepszy();
		if( pom1 > time )
			pom1 = time;
	}
	czas = pom/10;

	//koniec algorytmu
	
	if( tabusearch != 0 ){
		delete tabusearch;
		tabusearch = 0;
	}
	return pom1;
}

void main(void)
{
	ofstream wynik("40wynik2.txt");
	int* przetwarzanie;		//czasy przetwarzania
	int* priorytety;		
	int* tkoniec;			//oczekiwany czas zakoñczenia
	int n = 40;				//liczba zadañ
	przetwarzanie = new int[n];
	priorytety = new int[n];
	tkoniec = new int[n];
	int pom;
	ifstream plik("wt40.txt");
	if( !plik.is_open() )
		cerr << "Pusty" << endl;
	for( int i = 0 ; i<125 ; i++ )
	{
		wczytaj(przetwarzanie,priorytety,tkoniec,n,plik);

		pom = f(przetwarzanie,priorytety,tkoniec,n,5);
		wynik << "5\t" << czas << "\t" << pom << "\t";

		pom = f(przetwarzanie,priorytety,tkoniec,n,10);
		wynik << "10\t" << czas << "\t" << pom << "\t";

		pom = f(przetwarzanie,priorytety,tkoniec,n,20);
		wynik << "20\t" << czas << "\t" << pom << "\t" << endl;
	}
}

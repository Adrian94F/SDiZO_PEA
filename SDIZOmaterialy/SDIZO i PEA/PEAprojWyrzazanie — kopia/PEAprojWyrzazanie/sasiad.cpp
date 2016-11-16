#include "sasiad.h"

sasiad::sasiad( zadanie** zad, int lzad )
{
	LARGE_INTEGER timer;
	QueryPerformanceCounter(&timer);
	srand( timer.LowPart );
	this -> zadania = zad;
	this -> liczba = lzad;

	//tworzymy tablic� przechowuj�c� zadania
	this -> pomiar = new int[this -> liczba];

	//ustawiamy pocz�tkow� permutacj� na posortowan� od 0 do n-1
	for( int i = 0 ; i < this -> liczba ; i++ )
		this -> pomiar[i] = i;

	//tworzenie tablicy przechowuj�cej aktualn� permutacj�
	this->permutacja = new int[this -> liczba];
	int pom;

	//losowanie permutacji
	for( int i = 0 ; i < this -> liczba ; i++ )
	{
		do
		{
			pom = rand() % this -> liczba;
		}while(this -> pomiar[pom] == -1);
		this -> permutacja[i] = pom;
		this -> pomiar[pom] = -1;
	}
	for( int i = 0 ; i < this -> liczba ; i++ )
		this -> pomiar[i] = this -> permutacja[i];
	this -> najlepszy = this -> obliczopoz();
}

int* sasiad::permut()
{
	return this -> permutacja;
}

void sasiad::losuj()
{
	int pom[2];	//przechowuje indeksy zada�, kt�re nale�y zamieni�
	int rob;
	for( int i = 0 ; i < 2 ; i++ )
		pom[i] = -1;

	//losowanie punkt�w bez powt�rze�
	for( int i = 0 ; i < 2 ; i++ )
	{
		do
		{
			rob = rand() % this -> liczba;
		}while( rob == pom[0] || rob == pom[1] );
		pom[i] = rob;
	}

	//zamiana zada� miejscami
	this -> pomiar[pom[0]] = this -> permutacja[pom[1]];
	this -> pomiar[pom[1]] = this -> permutacja[pom[0]];
}

int sasiad::obliczopoz()
{
	int time = 0;	//odmierza czas
	int op = 0;		//zlicza opo�nienie
	int pomp;

	for( int i = 0 ; i<this->liczba ; i++ )
	{
		pomp = this -> zadania[pomiar[i]] -> get_opoznienie(time);
		if( pomp < 0 )
			pomp = 0;
		op += pomp;
		time = this -> zadania[pomiar[i]] -> get_koniec(time);
	}
	if( op < 0 )
		op = 0;
	return op;
}

int sasiad::najczas()
{
	return this -> najlepszy;
}

void sasiad::akceptuj()
{
	this -> najlepszy = this -> obliczopoz();
	for( int i = 0 ; i < this -> liczba ; i++ )
		this -> permutacja[i] = this -> pomiar[i];
}

void sasiad::nieakceptuj()
{
	for( int i = 0 ; i < this -> liczba ; i++ )
		this -> pomiar[i] = this -> permutacja[i];
}

sasiad::~sasiad(void)
{
	if( this -> zadania != 0 )
	{
		if( zadania[0] != 0 )
		{
			for( int i = 0 ; i < this -> liczba ; i++ )
			{
				delete this -> zadania[i];
				this -> zadania[i] = 0;
			}
		}
		delete[] this -> zadania;
		this -> zadania = 0;
	}
	if( this -> permutacja != 0 )
	{
		delete[] this -> permutacja;
		this -> permutacja = 0;
	}
	delete[] this -> pomiar;
}

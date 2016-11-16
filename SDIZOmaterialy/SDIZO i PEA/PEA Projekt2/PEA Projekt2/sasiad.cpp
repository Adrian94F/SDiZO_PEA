#include "sasiad.h"

sasiad::sasiad( zadanie** zad, int liczzad )
{
	LARGE_INTEGER timer;
	QueryPerformanceCounter(&timer);
	srand( timer.LowPart );
	this->zadania = zad;
	this->liczbazadan = liczzad;
	
	this->pomiar = new int[this->liczbazadan];		//tworzymy tablic� przechowuj�c� zadania
	
	for( int i = 0 ; i<this->liczbazadan ; i++ )	//ustawiamy pocz�tkow� permutacj� na posortowan� od 0 do n-1
		this->pomiar[i] = i;
	
	this->permutacja = new int[this->liczbazadan];	//tworzenie tablicy przechowuj�cej aktualn� permutacj�
	int pom;
	
	for( int i = 0 ; i<this->liczbazadan ; i++ )	//losowanie permutacji
	{
		do
		{
			pom = rand()%this->liczbazadan;
		}while(this->pomiar[pom] == -1);

		this->permutacja[i] = pom;
		this->pomiar[pom] = -1;
	}
	for( int i = 0 ; i<this->liczbazadan ; i++ )
		this->pomiar[i] = this->permutacja[i];

	this->najczas = this->obliczopoz();
}

int* sasiad::permut()
{
	return this->permutacja;
}

void sasiad::losuj()
{
	int pom[2];					//przechowuje indeksy zada�, kt�re nale�y zamieni�
	int rob;
	for( int i = 0 ; i<2 ; i++ )
		pom[i] = -1;
	
	for( int i = 0 ; i<2 ; i++ )//losowanie punkt�w bez powt�rze�
	{
		do
		{
			rob = rand()%this->liczbazadan;
		}while( rob==pom[0] || rob==pom[1] );
		pom[i] = rob;
	}
	//zamiana zada� miejscami
	this->pomiar[pom[0]] = this->permutacja[pom[1]];
	this->pomiar[pom[1]] = this->permutacja[pom[0]];
}

void sasiad::ustaw(int zad_1 , int zad_2)
{
	int pom[2];	//przechowuje indeksy zada�, kt�re nale�y zamieni�
	pom[0]=zad_1;
	pom[1]=zad_2;
	int rob;

	//zamiana zada� miejscami
	this->pomiar[pom[0]] = this->permutacja[pom[1]];
	this->pomiar[pom[1]] = this->permutacja[pom[0]];
}

int sasiad::obliczopoz()
{
	int t = 0;	//odmierza kolejny czasy
	int op = 0;	//zlicza sumaryczne op�nienie
	int pomp;

	for( int i = 0 ; i<this->liczbazadan ; i++ )
	{
		pomp = this -> zadania[pomiar[i]] -> opoznienie(t);
		if( pomp < 0 )
			pomp = 0;

		op += pomp;
		t = this -> zadania[pomiar[i]] -> koniec(t);
	}
	if( op<0 )
		op = 0;

	return op;
}

int sasiad::najlepszy()
{
	return this->najczas;
}

void sasiad::akceptuj()
{
	this->najczas = this->obliczopoz();


	for( int i = 0 ; i<this->liczbazadan ; i++ )
		this->permutacja[i] = this->pomiar[i];
}

void sasiad::nieakceptuj()
{
	for( int i = 0 ; i<this->liczbazadan ; i++ )
		this->pomiar[i] = this->permutacja[i];
}

sasiad::~sasiad(void)
{
	if( this->zadania != 0 )
	{
		if( zadania[0] != 0 )
		{
			for( int i = 0 ; i<this->liczbazadan ; i++ )
			{
				delete this->zadania[i];
				this->zadania[i] = 0;
			}
		}
		delete[] this->zadania;
		this->zadania = 0;
	}
	if( this->permutacja != 0 )
	{
		delete[] this->permutacja;
		this->permutacja = 0;
	}
	delete[] this->pomiar;
}

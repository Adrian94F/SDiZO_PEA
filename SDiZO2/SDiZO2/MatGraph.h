#ifndef MATGRAPH_H_
#define MATGRAPH_H_
#include "Node.h"

class MatGraph
{
	int w = 0, k = 0; // liczba wierzho³ków i krawêdzi  macierzy incydencji
	signed int ** A = NULL; // macierz incydencji
	signed int * wagi = NULL; // wagi krawêdzi

public:
	MatGraph() {};	 // konstruktor
	MatGraph(int, int); // konstruktor z liczb¹ wierzcho³ków i zagêszczeniem (w %) do automatycznej generacji
	MatGraph(int); // konstruktor z liczb¹ wierzcho³ków
	~MatGraph() // destruktor
	{ 
		usunMacierz(); 
	}

	void pokazMacierz();
	void usunMacierz();
	void dodajKrawedz(int, int, int);
	bool czyJestKrawedzPomiedzy(int, vector<int>);
	bool czyJestKrawedz(int, int);

	void odczyt(string);
	void zapis(string);

	string prim();
};

#endif
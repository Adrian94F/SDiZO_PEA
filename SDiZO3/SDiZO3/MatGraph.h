#pragma once
#include <iostream>
class MatGraph
{
private:
	int liczbaWierzcholkow;
	int** macierz;
public:
	MatGraph(int liczbaWierzcholkow);
	~MatGraph();
	void setLiczbaWierzcholkow(int liczbaWierzcholkow);
	void setMacierz(int** macierz);
	int getLiczbaWierzcholkow();
	int** getMacierz();
	bool dodajKrawedz(int begin, int end, int weight);
	void wyswietl();
};


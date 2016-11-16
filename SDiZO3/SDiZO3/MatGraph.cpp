#include "stdafx.h"
#include "MatGraph.h"


MatGraph::MatGraph(int liczbaWierzcholkow) // konstruktor
{
	this->liczbaWierzcholkow = liczbaWierzcholkow;
	macierz = new int*[liczbaWierzcholkow];

	for (int i = 0; i < liczbaWierzcholkow; i++)
		macierz[i] = new int[liczbaWierzcholkow];

	for (int i = 0; i < liczbaWierzcholkow; i++)
		for (int j = 0; j < liczbaWierzcholkow; j++)
			macierz[i][j] = 0;
}

MatGraph::~MatGraph() // destrukor
{
	for (int i = 0; i < liczbaWierzcholkow; i++)
		delete[] macierz[i];
	delete[] macierz;
}

void MatGraph::setLiczbaWierzcholkow(int liczbaWierzcholkow) // seter liczby wierzcho³ków
{
	this->liczbaWierzcholkow = liczbaWierzcholkow;
}

void MatGraph::setMacierz(int** macierz) //seter macierzy
{
	this->macierz = macierz;
}

int MatGraph::getLiczbaWierzcholkow() // geter liczby wierzcholkow
{
	return liczbaWierzcholkow;
}

int** MatGraph::getMacierz() // geter macierzy
{
	return macierz;
}

bool MatGraph::dodajKrawedz(int begin, int end, int weight) // dodawanie krawedzi
{
	if (begin >= liczbaWierzcholkow || end >= liczbaWierzcholkow)
		return false;

	if (macierz[begin][end] != 0)
		return false;

	macierz[begin][end] = weight;
	return true;
}

void MatGraph::wyswietl() // wyswietlanie macierzy
{
	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		for (int j = 0; j < liczbaWierzcholkow; j++)
		{
			cout.width(2);
			cout << macierz[i][j];
			cout << " ";
		}
		cout << endl << endl;
	}
}
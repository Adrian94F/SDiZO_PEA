#ifndef HEADER
#define HEADER
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
using namespace std;

/* Reprezentuje krawędź grafu */
class Edge
{
public:
	int source;
	int dest;
	int weight;
	Edge::Edge(int source, int dest, int weight)
	{
		this->source = source;
		this->dest = dest;
		this->weight = weight;
	}
};

/* Służy do mierzenia czasu */
class MyTimer {
	LARGE_INTEGER start, stop, lpFrequency;
	long double time, freq;
public:
	void Start();
	long double End();
	string Convert(long double time);
};

void PlecakGenerate(vector<int> &sizes, vector<int> &values, int totalsize, int itemsnum);								// generowanie plecaka - nieużywane
void PlecakLoad(ifstream &file, vector<int> &sizes, vector<int> &values, int &totalsize, int &itemsnum);					// wczytanie problemu plecakowego z pliku
void PlecakDisplay(vector<int> sizes, vector<int> values, int totalsize, int itemsnum);
void PlecakDisplaySolution(unsigned long long &wynik, vector<int> sizes, vector<int> values, int totalsize, int itemsnum);						// wyświetlanie wyniku algorytmu plecakowego
void PlecakDisplaySolution(vector<short>wynik, vector<int> sizes, vector<int> values, int totalsize, int itemsnum);
unsigned long long int PlecakBrute(vector<int> sizes, vector<int> values, int totalsize, int itemsnum);										// algorytm zupełny plecaka
vector<short> PlecakDynamic(vector<int> sizes, vector<int> values, int totalsize, int itemsnum);
vector<short> PlecakFPTAS(vector<int> sizes, vector<int> values, int totalsize, int itemsnum, float ε);
void PlecakTest(bool extended, bool dynamicorfptas);	// tryb testu dla plecaka
#endif
#pragma once
#include "Knapsack.h"
#include "MatGraph.h"
class Handle
{
private:
	MatGraph* macierzGraph;
	Knapsack* knapsack;
	double PCFreq; // Przechowuje czestotliwosc taktowania procesora.
	__int64 counterStart; // Przechowuje czas rozpoczecia pomiaru.
	void startCounter();
	double getCounter();
	void intSwap(int& a, int& b);
	void doubleSwap(double& a, double& b);
	unsigned long long factorial(int n);
	void permutuj(int* choice, int** permutationsTable, int begin, int end, unsigned long long& permutationCounter);
	void plecakWyswietlWyniki(bool* bestChoice, int bestWeight, int bestValue);
	void grafWyswietlWyniki(int* bestChoice, int bestDistance);
public:
	Handle();
	~Handle();
	void setMacierzGraph(MatGraph* macierzGraph);
	void setKnapsack(Knapsack* knapsack);
	MatGraph* getMacierzGraph();
	Knapsack* getKnapsack();
	bool stworzZPliku(char problem, string filePath);
	bool zbudujGraf(string filePath);
	bool stworzGraf(int vertices);
	bool wygenerujGraf();
	bool dodajKrawedz(int begin, int end, int weight);
	void usunGraf();
	bool zbudujPlecak(string filePath);
	bool stworzPlecak(int liczbaPrzedmiotow, int rozmiarPlecaka);
	bool wygenerujPlecak();
	bool dodajPrzedmiot(int index, int weight, int value);
	void usunPlecak();
	void plecakZupelny(bool debug);
	void plecakZachlanny(bool debug);
	void plecakZachlannyWartoscDoWagi(bool debug);
	void plecakDynamiczny(bool debug);
	void grafZupelny(bool debug);
	void grafZachlanny(bool debug);
	void grafLokalny(bool debug);
	double testPlecak(char algorytm, int liczbaPrzedmiotow, int rozmiarPlecaka);
	double testGraf(char algorytm, int liczbaMiast);
};


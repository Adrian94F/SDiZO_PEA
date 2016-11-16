#pragma once

#include "Knapsack.h"
#include "MatrixGraph.h"

#include <string>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <cmath>
#include <climits>

class CMyHandle
{
private:
	CMatrixGraph* matrixGraph;
	CKnapsack* knapsack;

	double PCFreq; // Przechowuje czestotliwosc taktowania procesora.
	__int64 counterStart; // Przechowuje czas rozpoczecia pomiaru.

	// Uruchomienie pomiaru czasu.
	void startCounter();

	/* Zakonczenie pomiaru czasu.
	Zwraca czas pomiaru podany w ms. */
	double getCounter();

	void intSwap(int& a, int& b);
	void doubleSwap(double& a, double& b);

	unsigned long long factorial(int n);

	void permute(int* choice, int** permutationsTable, int begin, int end, unsigned long long& permutationCounter);

	void knapsackPrintResults(bool* bestChoice, int bestWeight, int bestValue);
	void graphPrintResults(int* bestChoice, int bestDistance);

public:
	CMyHandle();
	~CMyHandle();

	void setMatrixGraph(CMatrixGraph* matrixGraph);
	void setKnapsack(CKnapsack* knapsack);

	CMatrixGraph* getMatrixGraph();
	CKnapsack* getKnapsack();

	bool buildFromFile(char problem, std::string filePath);

	bool buildGraph(std::string filePath);
	bool createGraph(int vertices);
	bool generateGraph();
	bool addEdge(int begin, int end, int weight);
	void delGraph();
	
	bool buildKnapsack(std::string filePath);
	bool createKnapsack(int numberOfElements, int backpackSize);
	bool generateKnapsack();
	bool addItem(int index, int weight, int value);
	void delKnapsack();

	void knapsackBruteForce(bool debug);
	void knapsackGreedyValue(bool debug);
	void knapsackGreddyValueToWeight(bool debug);
	void knapsackDynamic(bool debug);

	void graphBruteForce(bool debug);
	void graphGreedy(bool debug);
	void graphLocalSearch(bool debug);

	double testKnapsack(char algorithm, int numberOfElements, int backpackSize);
	double testGraph(char algorithm, int numberOfCities);
};


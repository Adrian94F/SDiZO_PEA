#pragma once

#include "Knapsack.h"
#include "Node.h"

#include <string>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>

struct compareNodes
{
	bool operator ()(const CNode*& node1, CNode*& node2)
	{
		if (node1->getBound() >= node2->getBound())
			return true;
		else
			return false;
	}
};

class CMyHandle
{
private:
	CKnapsack* knapsack;

	double PCFreq; // Przechowuje czestotliwosc taktowania procesora.
	__int64 counterStart; // Przechowuje czas rozpoczecia pomiaru.

	// Uruchomienie pomiaru czasu.
	void startCounter();

	/* Zakonczenie pomiaru czasu.
	Zwraca czas pomiaru podany w ms. */
	double getCounter();

	// Zamiana zmiennych typu int.
	void itemSwap(item& a, item& b);

	// Zamiana zmiennych typu double.
	void doubleSwap(double& a, double& b);

	/* Wyswietlanie wynikow dzialania algorytmu rozwiazujacego problem plecakowy.
	Parametry:
	- bool* bestChoice - wskaznik na tablice zawierajaca informacje, ktore przedmioty zostaly wlozone do plecaka
	- int bestWeight - waga przedmiotow w plecaku
	- int bestValue - wartosc przedmiotow w plecaku*/
	void printResults(bool* bestChoice, int bestWeight, int bestValue, item* items, double time);

public:
	CMyHandle();
	~CMyHandle();

	void setKnapsack(CKnapsack* knapsack);

	CKnapsack* getKnapsack();
	
	// Tworzenie obiektu klasy CKnapsack na podstawie danych z pliku 'filePath'
	bool build(std::string filePath, int backpackSize, double error);

	// Tworzenie obiektu klasy CKnapsack o numerze elementow 'numberOfElements' i rozmiarze plecaka 'backpackSize'
	bool create(int numberOfElements, int backpackSize, double error);

	// Wypelnianie obiektu klasy CKnapsack przedmiotami o wadze z przedzialu 1-rozmiar_plecaka i wartosci z przedzialu 1-99. 
	bool generate();

	// Dodawanie przedmiotu o nr 'index', wadze 'weight' i wartosci 'value'.
	bool addItem(int index, item item);

	// Usuwanie obiektu klasy CKnapsack.
	void del();

	/* Uruchomienie algorytmu BF dla problemu plecakowego.
	Wyswietlanie wynikow na podstawie parametru 'debug'.*/
	void bruteForce(bool debug);

	/* Uruchomienie algorytmu Branch & Bound metod¹ przeszukiwania wszerz dla problemu plecakowego.
	Wyswietlanie wynikow na podstawie parametru 'debug'.*/
	void branchAndBoundBFS(bool debug);

	/* Uruchomienie algorytmu Branch & Bound metod¹ przeszukiwania best-first dla problemu plecakowego.
	Wyswietlanie wynikow na podstawie parametru 'debug'.*/
	void branchAndBoundBestFirst(bool debug);

	/* Uruchomienie algorytmu dynamicznego dla problemu plecakowego.
	Wyswietlanie wynikow na podstawie parametru 'debug'.*/
	void dynamic(bool debug);

	/* Uruchomienie algorytmu aproksymacyjnego FPTAS dla problemu plecakowego.
	Wyswietlanie wynikow na podstawie parametru 'debug'.*/
	void FPTAS(bool debug);

	void calculateBound(CNode* node, CKnapsack* knapsack, item* items);

	/* Uruchomienie 100 testow algorytmu rozwiazujacego problem plecakowy.
	Parametry:
	- char algorithm - kod algorytmu
	- int numberOfElements - liczba elementow ktore mozna wlozyc do plecaka
	- int backpackSize - rozmiar plecaka*/
	double test(char algorithm, int numberOfElements, int backpackSize, double error);
};


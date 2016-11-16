#include "stdafx.h"
#include "Handle.h"
#include <string>
#include <Windows.h>
#include <ctime>
#include <cmath>
#include <climits>
#include <fstream>

Handle::Handle() // konstruktor
{
	macierzGraph = NULL;
	knapsack = NULL;

	PCFreq = 0.0;
	counterStart = 0;
}

Handle::~Handle() // desstruktor
{
	if (macierzGraph != NULL)
		delete macierzGraph;
	if (knapsack != NULL)
		delete knapsack;
}

void Handle::startCounter() // uruchomienie pomiaru czasu
{
	LARGE_INTEGER largeInteger;
	if (!QueryPerformanceFrequency(&largeInteger))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(largeInteger.QuadPart) / 1000.0;

	QueryPerformanceCounter(&largeInteger);
	counterStart = largeInteger.QuadPart;
}

double Handle::getCounter() // koniec pomiaru czasu - zwraca czas w ms
{
	LARGE_INTEGER largeInteger;
	QueryPerformanceCounter(&largeInteger);
	return double(largeInteger.QuadPart - counterStart) / PCFreq;
}

void Handle::intSwap(int& a, int& b) // zamiana intów
{
	int temp = a;
	a = b;
	b = temp;
}

void Handle::doubleSwap(double& a, double& b) // zamiana doubli
{
	double temp = a;
	a = b;
	b = temp;
}

unsigned long long Handle::factorial(int n) // silnia
{
	unsigned long long total = 1;
	for (int i = 1; i <= n; i++)
		total *= i;

	return total;
}

void Handle::permutuj(int* choice, int** permutationTable, int begin, int end, unsigned long long& permutationCounter) // permutacja
{
	if (begin == end)
	{
		for (int i = 0; i <= end; i++)
			permutationTable[permutationCounter][i] = choice[i];

		permutationCounter++;
	}
	else
		for (int j = begin; j <= end; j++)
		{
			intSwap(choice[begin], choice[j]);
			permutuj(choice, permutationTable, begin + 1, end, permutationCounter);
			intSwap(choice[begin], choice[j]);
		}
}

void Handle::setMacierzGraph(MatGraph* macierzGraph) // seter macierzy
{
	this->macierzGraph = macierzGraph;
}

void Handle::setKnapsack(Knapsack* knapsack) // seter plecaka
{
	this->knapsack = knapsack;
}

MatGraph* Handle::getMacierzGraph() // geter macierzy
{
	return macierzGraph;
}

Knapsack* Handle::getKnapsack() // geter plecaka
{
	return knapsack;
}

bool Handle::stworzZPliku(char problem, string filePath) // poœrednik w tworzeniu z pliku
{
	switch (problem)
	{
	case '1':
		return zbudujPlecak(filePath);

	case '2':
		return zbudujGraf(filePath);

	default:
		return false;
	}
}

bool Handle::zbudujGraf(string filePath)	// kreator tworzenia grafu z pliku
											// pobiera liczbe wierzcholkow
											// dalej umieszczone s¹ wagi krawêdzi 
											// (i - poczatek, j - koniec)
{
	int vertices, weight;

	fstream input(filePath, std::ios::in);

	if (input.good())
	{
		input >> vertices;

		if (!stworzGraf(vertices))
			return false;

		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
				if (i != j)
				{
					input >> weight;
					if (!dodajKrawedz(i, j, weight))
					{
						usunGraf();
						return false;
					}
				}
		return true;
	}

	return false;
}

bool Handle::stworzGraf(int vertices) // kreator nowego grafu
{
	if (vertices < 2)
		return false;

	usunGraf();
	macierzGraph = new MatGraph(vertices);

	return true;
}

bool Handle::wygenerujGraf() // generator losowy nowego grafu
{
	int vertices = macierzGraph->getLiczbaWierzcholkow();

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			if (i != j)
				if (!dodajKrawedz(i, j, 1 + rand() % 98))
					return false;

	return true;
}

bool Handle::dodajKrawedz(int begin, int end, int weight) // dodawanie krawedzi do grafu
{
	if (begin < 0 || end < 0 || weight < 1 || begin == end)
		return false;

	return macierzGraph->dodajKrawedz(begin, end, weight);
}

void Handle::usunGraf() // usuwanie grafu
{
	if (macierzGraph != NULL)
	{
		delete macierzGraph;
		macierzGraph = NULL;
	}
}

bool Handle::zbudujPlecak(string filePath)	// kreator tworzenia plecaka z pliku
											// pobiera rozmiar plecaka, potem liczbê przedmiotów
											// nastêpnie w parach wagê (rozmiar) i wartoœæ
{
	int rozmiarPlecaka, liczbaPrzedmiotow, weight, value;

	std::fstream input(filePath, std::ios::in);

	if (input.good())
	{
		input >> rozmiarPlecaka >> liczbaPrzedmiotow;

		if (!stworzPlecak(liczbaPrzedmiotow, rozmiarPlecaka))
			return false;

		for (int i = 0; i < liczbaPrzedmiotow; i++)
		{
			input >> weight >> value;
			if (!dodajPrzedmiot(i, weight, value))
			{
				usunPlecak();
				return false;
			}
		}

		return true;
	}

	return false;
}

bool Handle::stworzPlecak(int liczbaPrzedmiotow, int rozmiarPlecaka) // kreator nowego plecaka
{
	if (liczbaPrzedmiotow < 1 || rozmiarPlecaka < 2)
		return false;

	usunPlecak();
	knapsack = new Knapsack(liczbaPrzedmiotow, rozmiarPlecaka);

	return true;
}

bool Handle::wygenerujPlecak() // generator losowy nowego plecaka
{
	int rozmiarPlecaka = knapsack->getRozmiarPlecaka();
	int liczbaPrzedmiotow = knapsack->getLiczbaPrzedmiotow();
	int wagaPrzedmiotow = 0, weight;

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		weight = 1 + rand() % (rozmiarPlecaka - 1);
		wagaPrzedmiotow += weight;

		if (!dodajPrzedmiot(i, weight, 1 + rand() % 100))
			return false;
	}

	while (rozmiarPlecaka * 125 / 100 > wagaPrzedmiotow)
	{
		knapsack->getWagi()[rand() % liczbaPrzedmiotow] += 1;
		wagaPrzedmiotow++;
	}

	return true;
}

bool Handle::dodajPrzedmiot(int index, int weight, int value) // dodawanie przedmiotu
{
	if (index < 0 || weight < 1 || value < 1)
		return false;

	return knapsack->dodajPrzedmiot(index, weight, value);
}

void Handle::usunPlecak() // usuwanie plecaka
{
	if (knapsack != NULL)
	{
		delete knapsack;
		knapsack = NULL;
	}
}

void Handle::plecakZupelny(bool debug) // przeglad zupelny plecaka
{
	int liczbaPrzedmiotow = knapsack->getLiczbaPrzedmiotow();
	int rozmiarPlecaka = knapsack->getRozmiarPlecaka();
	int j, tempWeight, tempValue, bestValue = 0, bestWeight = 0;
	double iterations = pow(2, liczbaPrzedmiotow);

	bool* choice = new bool[liczbaPrzedmiotow];
	bool* bestChoice = new bool[liczbaPrzedmiotow];

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		choice[i] = false;
	}

	for (double i = 0; i < iterations; i++)
	{
		j = liczbaPrzedmiotow - 1;
		tempWeight = 0;
		tempValue = 0;

		while (choice[j] && j > 0)
		{
			choice[j] = false;
			j--;
		}

		choice[j] = true;
		for (int k = 0; k < liczbaPrzedmiotow; k++)
		{
			if (choice[k])
			{
				tempWeight += knapsack->getWagi()[k];
				tempValue += knapsack->getWartosci()[k];
			}
		}
		if (tempValue > bestValue && tempWeight <= rozmiarPlecaka)
		{
			bestWeight = tempWeight;
			bestValue = tempValue;

			for (int k = 0; k < liczbaPrzedmiotow; k++)
				bestChoice[k] = choice[k];
		}
	}

	if (debug)
		plecakWyswietlWyniki(bestChoice, bestWeight, bestValue);

	delete[] choice;
	delete[] bestChoice;
}

void Handle::plecakZachlanny(bool debug) // algorytm zach³anny dla plecaka
{
	int liczbaPrzedmiotow = knapsack->getLiczbaPrzedmiotow();
	int rozmiarPlecaka = knapsack->getRozmiarPlecaka();
	int j, tempWeight = 0, tempValue = 0;

	bool* bestChoice = new bool[liczbaPrzedmiotow];

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		bestChoice[i] = false;
		j = i;
		while (j > 0 && knapsack->getWartosci()[j - 1] < knapsack->getWartosci()[j])
		{
			intSwap(knapsack->getWartosci()[j - 1], knapsack->getWartosci()[j]);
			intSwap(knapsack->getWagi()[j - 1], knapsack->getWagi()[j]);
			j--;
		}
	}

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		if (tempWeight + knapsack->getWagi()[i] < rozmiarPlecaka)
		{
			tempWeight += knapsack->getWagi()[i];
			tempValue += knapsack->getWartosci()[i];
			bestChoice[i] = true;
		}
	}

	if (debug)
		plecakWyswietlWyniki(bestChoice, tempWeight, tempValue);

	delete[] bestChoice;
}

void Handle::plecakZachlannyWartoscDoWagi(bool debug) // algorytm zach³anny dla plecaka (kryt. stos. wart. do wagi)
{
	int liczbaPrzedmiotow = knapsack->getLiczbaPrzedmiotow();
	int rozmiarPlecaka = knapsack->getRozmiarPlecaka();
	int j, tempWeight = 0, tempValue = 0;

	bool* bestChoice = new bool[liczbaPrzedmiotow];
	double* valueToWeight = new double[liczbaPrzedmiotow];

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		bestChoice[i] = false;
		valueToWeight[i] = (double)knapsack->getWartosci()[i] / (double)knapsack->getWagi()[i];
	}

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		j = i;
		while (j > 0 && valueToWeight[j - 1] < valueToWeight[j])
		{
			intSwap(knapsack->getWartosci()[j - 1], knapsack->getWartosci()[j]);
			intSwap(knapsack->getWagi()[j - 1], knapsack->getWagi()[j]);
			doubleSwap(valueToWeight[j - 1], valueToWeight[j]);
			j--;
		}
	}

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		if (tempWeight + knapsack->getWagi()[i] < rozmiarPlecaka)
		{
			tempWeight += knapsack->getWagi()[i];
			tempValue += knapsack->getWartosci()[i];
			bestChoice[i] = true;
		}
	}

	if (debug)
		plecakWyswietlWyniki(bestChoice, tempWeight, tempValue);

	delete[] bestChoice;
}

void Handle::plecakDynamiczny(bool debug) // algorytm dynamiczny dla plecaka
{
	int liczbaPrzedmiotow = knapsack->getLiczbaPrzedmiotow();
	int rozmiarPlecaka = knapsack->getRozmiarPlecaka();
	int capacity = rozmiarPlecaka;
	int elements = liczbaPrzedmiotow;
	int bestWeight = 0;

	bool* bestChoice = new bool[liczbaPrzedmiotow];
	int** table = new int*[liczbaPrzedmiotow + 1];

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		table[i] = new int[rozmiarPlecaka + 1];
		bestChoice[i] = false;
	}
	table[liczbaPrzedmiotow] = new int[rozmiarPlecaka + 1];

	for (int i = 0; i <= liczbaPrzedmiotow; i++)
		for (int j = 0; j <= rozmiarPlecaka; j++)
			table[i][j] = 0;

	for (int i = 1; i <= liczbaPrzedmiotow; i++)
		for (int j = 0; j <= rozmiarPlecaka; j++)
			if (j < knapsack->getWagi()[i - 1])
				table[i][j] = table[i - 1][j];
			else
				table[i][j] = max(table[i - 1][j], knapsack->getWartosci()[i - 1] + table[i - 1][j - knapsack->getWagi()[i - 1]]);

	while (capacity > 0 && elements > 0)
	{
		if (table[elements][capacity] != table[elements - 1][capacity])
		{
			bestChoice[elements - 1] = true;
			capacity -= knapsack->getWagi()[elements - 1];
		}
		elements--;
	}

	for (int i = 0; i < liczbaPrzedmiotow; i++)
		if (bestChoice[i])
			bestWeight += knapsack->getWagi()[i];

	if (debug)
		plecakWyswietlWyniki(bestChoice, bestWeight, table[liczbaPrzedmiotow][rozmiarPlecaka]);

	delete[] bestChoice;

	for (int i = 0; i <= liczbaPrzedmiotow; i++)
		delete[] table[i];

	delete[] table;
}

void Handle::plecakWyswietlWyniki(bool* bestChoice, int bestWeight, int bestValue) // wyswietlanie wyników dla plecaka
{
	knapsack->wyswietl();
	cout << "c: ";
	for (int i = 0; i < knapsack->getLiczbaPrzedmiotow(); i++)
	{
		cout.width(3);
		cout << bestChoice[i];
		cout << " ";
	}

	cout << endl;
	cout << "LACZNA WAGA: " << bestWeight << endl;
	cout << "LACZNA WARTOSC: " << bestValue << endl;
	cout << endl;
	system("PAUSE");
}

void Handle::grafZupelny(bool debug) // tworzenie grafu zupenego
{
	int liczbaMiast = macierzGraph->getLiczbaWierzcholkow();
	unsigned long long numberOfPermutations = factorial(liczbaMiast);
	unsigned long long bestPermutation;
	unsigned long long permutationCounter = 0;
	int tempDistance, bestDistance = INT_MAX;

	int* choice = new int[liczbaMiast];
	int** permutations = new int*[numberOfPermutations];
	for (unsigned long long i = 0; i < numberOfPermutations; i++)
		permutations[i] = new int[liczbaMiast];

	for (int i = 0; i < liczbaMiast; i++)
		choice[i] = i;

	permutuj(choice, permutations, 0, liczbaMiast - 1, permutationCounter);

	for (unsigned long long i = 0; i < numberOfPermutations; i++)
	{
		tempDistance = 0;
		for (int j = 1; j < liczbaMiast; j++)
			tempDistance += macierzGraph->getMacierz()[permutations[i][j - 1]][permutations[i][j]];

		if (tempDistance < bestDistance)
		{
			bestDistance = tempDistance;
			bestPermutation = i;
		}
	}

	if (debug)
		grafWyswietlWyniki(permutations[bestPermutation], bestDistance);

	for (unsigned long long i = 0; i < numberOfPermutations; i++)
		delete[] permutations[i];

	delete[] permutations;
	delete[] choice;
}

void Handle::grafZachlanny(bool debug) // algorytm zachlanny dla grafu
{
	int liczbaMiast = macierzGraph->getLiczbaWierzcholkow();
	int tempDistance, bestDistance = 0, tempCity;

	bool* visited = new bool[liczbaMiast];
	int* bestChoice = new int[liczbaMiast];

	for (int i = 0; i < liczbaMiast; i++)
	{
		visited[i] = false;
	}

	bestChoice[0] = rand() % liczbaMiast;
	visited[bestChoice[0]] = true;

	for (int i = 1; i < liczbaMiast; i++)
	{
		tempDistance = INT_MAX;
		for (int j = 0; j < liczbaMiast; j++)
			if (!visited[j])
				if (macierzGraph->getMacierz()[bestChoice[i - 1]][j] < tempDistance)
				{
					tempCity = j;
					tempDistance = macierzGraph->getMacierz()[bestChoice[i - 1]][j];
				}

		visited[tempCity] = true;
		bestChoice[i] = tempCity;
		bestDistance += tempDistance;
	}

	if (debug)
		grafWyswietlWyniki(bestChoice, bestDistance);

	delete[] visited;
	delete[] bestChoice;
}

void Handle::grafLokalny(bool debug) // algorytm przeszukiwania lokalnego dla grafu
{
	int liczbaMiast = macierzGraph->getLiczbaWierzcholkow();
	int tempDistance, bestDistance = 0;
	int index;
	bool check;

	int* bestChoice = new int[liczbaMiast];
	int* permutation = new int[liczbaMiast];

	for (int i = 0; i < liczbaMiast; i++)
		permutation[i] = i;

	for (int i = 0; i < liczbaMiast; i++)
	{
		index = i + rand() % (liczbaMiast - i);
		intSwap(permutation[0], permutation[index]);
	}

	for (int i = 0; i < liczbaMiast; i++)
		bestChoice[i] = permutation[i];

	for (int i = 1; i < liczbaMiast; i++)
		bestDistance += macierzGraph->getMacierz()[permutation[i - 1]][permutation[i]];

	do
	{
		check = false;

		for (int i = 0; i < liczbaMiast - 2; i++)
			for (int j = i + 2; j < liczbaMiast; j++)
			{
				tempDistance = 0;
				intSwap(permutation[i], permutation[j]);

				for (int k = 1; k < liczbaMiast; k++)
					tempDistance += macierzGraph->getMacierz()[permutation[k - 1]][permutation[k]];

				if (tempDistance < bestDistance)
				{
					check = true;
					bestDistance = tempDistance;
					for (int k = 0; k < liczbaMiast; k++)
						bestChoice[k] = permutation[k];
				}

				intSwap(permutation[i], permutation[j]);
			}
	} while (check);

	if (debug)
		grafWyswietlWyniki(bestChoice, bestDistance);

	delete[] bestChoice;
	delete[] permutation;
}

void Handle::grafWyswietlWyniki(int* bestChoice, int bestDistance) // wyœwietlenie wyników dla grafu
{
	macierzGraph->wyswietl();
	cout << endl;

	cout << "NAJKROTSZA SCIEZKA: ";
	for (int i = 0; i < macierzGraph->getLiczbaWierzcholkow(); i++)
		cout << bestChoice[i] << " ";

	cout << endl;
	cout << endl;

	cout << "LACZNA DLUGOSC SCIEZKI: ";
	cout << bestDistance;

	cout << endl;
	cout << endl;

	system("PAUSE");
}

double Handle::testPlecak(char algorytm, int numberOfElemets, int rozmiarPlecaka) // testowanie plecaka (po 100 testów)
{
	double result = 0;

	for (int i = 0; i < 100; i++)
	{
		stworzPlecak(numberOfElemets, rozmiarPlecaka);
		wygenerujPlecak();

		switch (algorytm)
		{
		case '1':
			startCounter();
			plecakZupelny(false);
			result = getCounter();
			break;

		case '2':
			startCounter();
			plecakZachlanny(false);
			result = getCounter();
			break;

		case '3':
			startCounter();
			plecakZachlannyWartoscDoWagi(false);
			result = getCounter();
			break;

		case '4':
			startCounter();
			plecakDynamiczny(false);
			result = getCounter();
			break;

		default:
			return 0;
		}
	}

	return result / 100;
}

double Handle::testGraf(char algorytm, int liczbaMiast) // testowanie grafu (po 100 testów)
{
	double result = 0;

	for (int i = 0; i < 100; i++)
	{
		stworzGraf(liczbaMiast);
		wygenerujGraf();

		switch (algorytm)
		{
		case '1':
			startCounter();
			grafZupelny(false);
			result += getCounter();
			break;

		case '2':
			startCounter();
			grafZachlanny(false);
			result += getCounter();
			break;

		case '3':
			startCounter();
			grafLokalny(false);
			result += getCounter();
			break;

		default:
			return 0;
		}
	}
	return result / 100;
}


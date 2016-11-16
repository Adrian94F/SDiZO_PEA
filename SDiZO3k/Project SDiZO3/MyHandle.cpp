#include "stdafx.h"
#include "MyHandle.h"


CMyHandle::CMyHandle()
{
	matrixGraph = NULL;
	knapsack = NULL;

	PCFreq = 0.0;
	counterStart = 0;
}

CMyHandle::~CMyHandle()
{
	if (matrixGraph != NULL)
		delete matrixGraph;
	if (knapsack != NULL)
		delete knapsack;
}

// Uruchomienie pomiaru czasu.
void CMyHandle::startCounter()
{
	LARGE_INTEGER largeInteger;
	if (!QueryPerformanceFrequency(&largeInteger))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(largeInteger.QuadPart) / 1000.0;

	QueryPerformanceCounter(&largeInteger);
	counterStart = largeInteger.QuadPart;
}

/* Zakonczenie pomiaru czasu.
Zwraca czas pomiaru podany w ms.*/
double CMyHandle::getCounter()
{
	LARGE_INTEGER largeInteger;
	QueryPerformanceCounter(&largeInteger);
	return double(largeInteger.QuadPart - counterStart) / PCFreq;
}

void CMyHandle::intSwap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void CMyHandle::doubleSwap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}

unsigned long long CMyHandle::factorial(int n)
{
	unsigned long long total = 1;
	for (int i = 1; i <= n; i++)
		total *= i;

	return total;
}

void CMyHandle::permute(int* choice, int** permutationTable, int begin, int end, unsigned long long& permutationCounter)
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
			permute(choice, permutationTable, begin+1, end, permutationCounter);
			intSwap(choice[begin], choice[j]);
		}
}

void CMyHandle::setMatrixGraph(CMatrixGraph* matrixGraph)
{
	this->matrixGraph = matrixGraph;
}

void CMyHandle::setKnapsack(CKnapsack* knapsack)
{
	this->knapsack = knapsack;
}

CMatrixGraph* CMyHandle::getMatrixGraph()
{
	return matrixGraph;
}

CKnapsack* CMyHandle::getKnapsack()
{
	return knapsack;
}

bool CMyHandle::buildFromFile(char problem, std::string filePath)
{
	switch (problem)
	{
	case '1':
		return buildKnapsack(filePath);

	case '2':
		return buildGraph(filePath);

	default:
		return false;
	}
}

bool CMyHandle::buildGraph(std::string filePath)
{
	int vertices, weight;

	std::fstream input(filePath, std::ios::in);

	if (input.good())
	{
		input >> vertices;

		if (!createGraph(vertices))
			return false;

		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
				if (i != j)
				{
					input >> weight;
					if (!addEdge(i, j, weight))
					{
						delGraph();
						return false;
					}
				}
		return true;
	}

	return false;
}

bool CMyHandle::createGraph(int vertices)
{
	if (vertices < 2)
		return false;

	delGraph();
	matrixGraph = new CMatrixGraph(vertices);

	return true;
}

bool CMyHandle::generateGraph()
{
	int vertices = matrixGraph->getNumberOfVertices();

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			if (i != j)
				if (!addEdge(i, j, 1 + rand()%98))
					return false;

	return true;
}

bool CMyHandle::addEdge(int begin, int end, int weight)
{
	if (begin < 0 || end < 0 || weight < 1 || begin == end)
		return false;
	
	return matrixGraph->addEdge(begin, end, weight);
}

void CMyHandle::delGraph()
{
	if (matrixGraph != NULL)
	{
		delete matrixGraph;
		matrixGraph = NULL;
	}
}

bool CMyHandle::buildKnapsack(std::string filePath)
{
	int backpackSize, numberOfElements, weight, value;

	std::fstream input(filePath, std::ios::in);

	if (input.good())
	{
		input >> backpackSize >> numberOfElements;

		if (!createKnapsack(numberOfElements, backpackSize))
			return false;

		for (int i = 0; i < numberOfElements; i++)
		{
			input >> weight >> value;
			if (!addItem(i, weight, value))
			{
				delKnapsack();
				return false;
			}
		}

		return true;
	}

	return false;
}

bool CMyHandle::createKnapsack(int numberOfElements, int backpackSize)
{
	if (numberOfElements < 1 || backpackSize < 2)
		return false;

	delKnapsack();
	knapsack = new CKnapsack(numberOfElements, backpackSize);

	return true;
}

bool CMyHandle::generateKnapsack()
{
	int backpackSize = knapsack->getBackpackSize();
	int numberOfElements = knapsack->getNumberOfElements();
	int weightOfElements = 0, weight;

	for (int i = 0; i < numberOfElements; i++)
	{
		weight = 1 + rand() % (backpackSize-1);
		weightOfElements += weight;

		if (!addItem(i, weight, 1 + rand()%100))
			return false;
	}

	while (backpackSize * 125 / 100 > weightOfElements)
	{
		knapsack->getWeights()[rand()%numberOfElements] += 1;
		weightOfElements++;
	}

	return true;
}

bool CMyHandle::addItem(int index, int weight, int value)
{
	if (index < 0 || weight < 1 || value < 1)
		return false;

	return knapsack->addItem(index, weight, value);
}

void CMyHandle::delKnapsack()
{
	if (knapsack != NULL)
	{
		delete knapsack;
		knapsack = NULL;
	}
}

void CMyHandle::knapsackBruteForce(bool debug)
{
	int numberOfElements = knapsack->getNumberOfElements();
	int backpackSize = knapsack->getBackpackSize();
	int j, tempWeight, tempValue, bestValue = 0, bestWeight =0;
	double iterations = pow(2, numberOfElements);

	bool* choice = new bool[numberOfElements];
	bool* bestChoice = new bool[numberOfElements];

	for (int i = 0; i < numberOfElements; i++)
	{
		choice[i] = false;
	}

	for (double i = 0; i < iterations; i++)
	{
		j = numberOfElements -1;
		tempWeight = 0;
		tempValue = 0;

		while (choice[j] && j > 0)
		{
			choice[j] = false;
			j--;
		}

		choice[j] = true;
		for (int k = 0; k < numberOfElements; k++)
		{
			if (choice[k])
			{
				tempWeight += knapsack->getWeights()[k];
				tempValue += knapsack->getValues()[k];
			}
		}
		if (tempValue > bestValue && tempWeight <= backpackSize)
		{
			bestWeight = tempWeight;
			bestValue = tempValue;
			
			for (int k = 0; k < numberOfElements; k++)
				bestChoice[k] = choice[k];
		}
	}

	if (debug)
		knapsackPrintResults(bestChoice, bestWeight, bestValue);

	delete[] choice;
	delete[] bestChoice;
}

void CMyHandle::knapsackGreedyValue(bool debug)
{
	int numberOfElements = knapsack->getNumberOfElements();
	int backpackSize = knapsack->getBackpackSize();
	int j, tempWeight = 0, tempValue = 0;

	bool* bestChoice = new bool[numberOfElements];

	for (int i = 0; i < numberOfElements; i++)
	{
		bestChoice[i] = false;
		j = i;
		while (j > 0 && knapsack->getValues()[j - 1] < knapsack->getValues()[j])
		{
			intSwap(knapsack->getValues()[j - 1], knapsack->getValues()[j]);
			intSwap(knapsack->getWeights()[j - 1], knapsack->getWeights()[j]);
			j--;
		}
	}

	for (int i = 0; i < numberOfElements; i++)
	{
		if (tempWeight + knapsack->getWeights()[i] < backpackSize)
		{
			tempWeight += knapsack->getWeights()[i];
			tempValue += knapsack->getValues()[i];
			bestChoice[i] = true;
		}
	}

	if (debug)
		knapsackPrintResults(bestChoice, tempWeight, tempValue);

	delete[] bestChoice;
}

void CMyHandle::knapsackGreddyValueToWeight(bool debug)
{
	int numberOfElements = knapsack->getNumberOfElements();
	int backpackSize = knapsack->getBackpackSize();
	int j, tempWeight = 0, tempValue = 0;

	bool* bestChoice = new bool[numberOfElements];
	double* valueToWeight = new double[numberOfElements];

	for (int i = 0; i < numberOfElements; i++)
	{
		bestChoice[i] = false;
		valueToWeight[i] = (double)knapsack->getValues()[i] / (double)knapsack->getWeights()[i];
	}

	for (int i = 0; i < numberOfElements; i++)
	{
		j = i;
		while (j > 0 && valueToWeight[j - 1] < valueToWeight[j])
		{
			intSwap(knapsack->getValues()[j - 1], knapsack->getValues()[j]);
			intSwap(knapsack->getWeights()[j - 1], knapsack->getWeights()[j]);
			doubleSwap(valueToWeight[j - 1], valueToWeight[j]);
			j--;
		}
	}

	for (int i = 0; i < numberOfElements; i++)
	{
		if (tempWeight + knapsack->getWeights()[i] < backpackSize)
		{
			tempWeight += knapsack->getWeights()[i];
			tempValue += knapsack->getValues()[i];
			bestChoice[i] = true;
		}
	}

	if (debug)
		knapsackPrintResults(bestChoice, tempWeight, tempValue);

	delete[] bestChoice;
}

void CMyHandle::knapsackDynamic(bool debug)
{
	int numberOfElements = knapsack->getNumberOfElements();
	int backpackSize = knapsack->getBackpackSize();
	int capacity = backpackSize;
	int elements = numberOfElements;
	int bestWeight = 0;

	bool* bestChoice = new bool[numberOfElements];
	int** table = new int*[numberOfElements+1];

	for (int i = 0; i < numberOfElements; i++)
	{
		table[i] = new int[backpackSize + 1];
		bestChoice[i] = false;
	}
	table[numberOfElements] = new int[backpackSize + 1];

	for (int i = 0; i <= numberOfElements; i++)
		for (int j = 0; j <= backpackSize; j++)
			table[i][j] = 0;

	for (int i = 1; i <= numberOfElements; i++)
		for (int j = 0; j <= backpackSize; j++)
			if (j < knapsack->getWeights()[i-1])
				table[i][j] = table[i - 1][j];
			else
				table[i][j] = max(table[i - 1][j], knapsack->getValues()[i-1] + table[i - 1][j - knapsack->getWeights()[i-1]]);

	while (capacity > 0 && elements > 0)
	{
		if (table[elements][capacity] != table[elements - 1][capacity])
		{
			bestChoice[elements-1] = true;
			capacity -= knapsack->getWeights()[elements-1];
		}
		elements--;
	}

	for (int i = 0; i < numberOfElements; i++)
		if (bestChoice[i])
			bestWeight += knapsack->getWeights()[i];

	if (debug)
		knapsackPrintResults(bestChoice, bestWeight, table[numberOfElements][backpackSize]);

	delete[] bestChoice;

	for (int i = 0; i <= numberOfElements; i++)
		delete[] table[i];

	delete[] table;
}

void CMyHandle::knapsackPrintResults(bool* bestChoice, int bestWeight, int bestValue)
{
	knapsack->print();
	std::cout << "c: ";
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		std::cout.width(3);
		std::cout << bestChoice[i];
		std::cout << " ";
	}

	std::cout << std::endl;
	std::cout << "LACZNA WAGA: " << bestWeight << std::endl;
	std::cout << "LACZNA WARTOSC: " << bestValue << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CMyHandle::graphBruteForce(bool debug)
{
	int numberOfCities = matrixGraph->getNumberOfVertices();
	unsigned long long numberOfPermutations = factorial(numberOfCities);
	unsigned long long bestPermutation;
	unsigned long long permutationCounter = 0;
	int tempDistance, bestDistance = INT_MAX;

	int* choice = new int[numberOfCities];
	int** permutations = new int*[numberOfPermutations];
	for (unsigned long long i = 0; i < numberOfPermutations; i++)
		permutations[i] = new int[numberOfCities];

	for (int i = 0; i < numberOfCities; i++)
		choice[i] = i;

	permute(choice, permutations, 0, numberOfCities - 1, permutationCounter);

	for (unsigned long long i = 0; i < numberOfPermutations; i++)
	{
		tempDistance = 0;
		for (int j = 1; j < numberOfCities; j++)
			tempDistance += matrixGraph->getMatrix()[permutations[i][j - 1]][permutations[i][j]];

		if (tempDistance < bestDistance)
		{
			bestDistance = tempDistance;
			bestPermutation = i;
		}
	}

	if (debug)
		graphPrintResults(permutations[bestPermutation], bestDistance);

	for (unsigned long long i = 0; i < numberOfPermutations; i++)
		delete[] permutations[i];

	delete[] permutations;
	delete[] choice;
}

void CMyHandle::graphGreedy(bool debug)
{
	int numberOfCities = matrixGraph->getNumberOfVertices();
	int tempDistance, bestDistance = 0, tempCity;

	bool* visited = new bool[numberOfCities];
	int* bestChoice = new int[numberOfCities];

	for (int i = 0; i < numberOfCities; i++)
	{
		visited[i] = false;
	}

	bestChoice[0] = rand() % numberOfCities;
	visited[bestChoice[0]] = true;

	for (int i = 1; i < numberOfCities; i++)
	{
		tempDistance = INT_MAX;
		for (int j = 0; j < numberOfCities;j++)
			if (!visited[j])
				if (matrixGraph->getMatrix()[bestChoice[i-1]][j] < tempDistance)
				{
					tempCity = j;
					tempDistance = matrixGraph->getMatrix()[bestChoice[i - 1]][j];
				}

		visited[tempCity] = true;
		bestChoice[i] = tempCity;
		bestDistance += tempDistance;
	}

	if (debug)
		graphPrintResults(bestChoice, bestDistance);

	delete[] visited;
	delete[] bestChoice;
}

void CMyHandle::graphLocalSearch(bool debug)
{
	int numberOfCities = matrixGraph->getNumberOfVertices();
	int tempDistance, bestDistance=0;
	int index;
	bool check;

	int* bestChoice = new int[numberOfCities];
	int* permutation = new int[numberOfCities];

	for (int i = 0; i < numberOfCities; i++)
		permutation[i] = i;

	for (int i = 0; i < numberOfCities; i++)
	{
		index = i + rand()%(numberOfCities - i);
		intSwap(permutation[0], permutation[index]);
	}

	for (int i = 0; i < numberOfCities; i++)
		bestChoice[i] = permutation[i];

	for (int i = 1; i < numberOfCities; i++)
		bestDistance += matrixGraph->getMatrix()[permutation[i - 1]][permutation[i]];

	do
	{
		check = false;

		for (int i = 0; i < numberOfCities - 2; i++)
			for (int j = i + 2; j < numberOfCities; j++)
			{
				tempDistance = 0;
				intSwap(permutation[i], permutation[j]);

				for (int k = 1; k < numberOfCities; k++)
					tempDistance += matrixGraph->getMatrix()[permutation[k - 1]][permutation[k]];

				if (tempDistance < bestDistance)
				{
					check = true;
					bestDistance = tempDistance;
					for (int k = 0; k < numberOfCities; k++)
						bestChoice[k] = permutation[k];
				}

				intSwap(permutation[i], permutation[j]);
			}
	} while (check);

	if (debug)
		graphPrintResults(bestChoice, bestDistance);

	delete[] bestChoice;
	delete[] permutation;
}

void CMyHandle::graphPrintResults(int* bestChoice, int bestDistance)
{
	matrixGraph->print();
	std::cout << std::endl;

	std::cout << "NAJKROTSZA SCIEZKA: ";
	for (int i = 0; i < matrixGraph->getNumberOfVertices(); i++)
		std::cout << bestChoice[i] << " ";

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "LACZNA DLUGOSC SCIEZKI: ";
	std::cout << bestDistance;
	
	std::cout << std::endl;
	std::cout << std::endl;

	system("PAUSE");
}

double CMyHandle::testKnapsack(char algorithm, int numberOfElemets, int backpackSize)
{
	double result = 0;

	for (int i = 0; i < 100; i++)
	{
		createKnapsack(numberOfElemets, backpackSize);
		generateKnapsack();

		switch (algorithm)
		{
		case '1':
			startCounter();
			knapsackBruteForce(false);
			result += getCounter();
			break;
			
		case '2':
			startCounter();
			knapsackGreedyValue(false);
			result += getCounter();
			break;

		case '3':
			startCounter();
			knapsackGreddyValueToWeight(false);
			result += getCounter();
			break;

		case '4':
			startCounter();
			knapsackDynamic(false);
			result += getCounter();
			break;

		default:
			return 0;
		}
	}

	return result/100;
}

double CMyHandle::testGraph(char algorithm, int numberOfCities)
{
	double result = 0;

	for (int i = 0; i < 100; i++)
	{
		createGraph(numberOfCities);
		generateGraph();

		switch (algorithm)
		{
		case '1':
			startCounter();
			graphBruteForce(false);
			result += getCounter();
			break;

		case '2':
			startCounter();
			graphGreedy(false);
			result += getCounter();
			break;

		case '3':
			startCounter();
			graphLocalSearch(false);
			result += getCounter();
			break;

		default:
			return 0;
		}
	}
	return result/100;
}


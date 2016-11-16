#include "stdafx.h"
#include "MyHandle.h"


CMyHandle::CMyHandle()
{
	knapsack = NULL;
	PCFreq = 0.0;
	counterStart = 0;
}

CMyHandle::~CMyHandle()
{
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

// Zamiana zmiennych typu int.
void CMyHandle::itemSwap(item& a, item& b)
{
	item temp = a;
	a = b;
	b = temp;
}

// Zamiana zmiennych typu double.
void CMyHandle::doubleSwap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}

void CMyHandle::setKnapsack(CKnapsack* knapsack)
{
	this->knapsack = knapsack;
}

CKnapsack* CMyHandle::getKnapsack()
{
	return knapsack;
}

// Tworzenie obiektu klasy CKnapsack na podstawie danych z pliku 'filePath'
bool CMyHandle::build(std::string filePath, int backpackSize, double error)
{
	int numberOfElements;
	item item;

	// Tworzeni strumienia.
	std::fstream input(filePath, std::ios::in);

	if (input.good())
	{
		input >> numberOfElements;

		// Tworzenie obiektu.
		if (!create(numberOfElements, backpackSize, error))
			return false;

		for (int i = 0; i < numberOfElements; i++)
		{
			// Dodawanie przedmiotow.
			input >> item.weight >> item.value;
			if (!addItem(i, item))
			{
				del();
				return false;
			}
		}
		return true;
	}
	return false;
}

// Tworzenie obiektu klasy CKnapsack o numerze elementow 'numberOfElements' i rozmiarze plecaka 'backpackSize'
bool CMyHandle::create(int numberOfElements, int backpackSize, double error)
{
	if (numberOfElements < 1 || backpackSize < 2)
		return false;

	del();
	knapsack = new CKnapsack(numberOfElements, backpackSize, error);

	return true;
}

// Wypelnianie obiektu klasy CKnapsack przedmiotami o wadze z przedzialu 1-rozmiar_plecaka i wartosci z przedzialu 1-99.
bool CMyHandle::generate()
{
	int weightOfElements = 0;
	item item;

	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		// Generowanie wagi.
		item.weight = 1 + rand() % (knapsack->getBackpackSize()-1);
		item.value = 1 + rand() % 100;
		weightOfElements += item.weight;

		// Dodawnie przedmiotu.
		if (!addItem(i, item))
			return false;
	}

	while (knapsack->getBackpackSize() * 125 / 100 > weightOfElements)
	{
		knapsack->getItems()[rand()%knapsack->getNumberOfElements()].weight += 1;
		weightOfElements++;
	}

	return true;
}

// Dodawanie przedmiotu o nr 'index', wadze 'weight' i wartosci 'value'.
bool CMyHandle::addItem(int index, item item)
{
	if (index < 0 || item.weight < 1 || item.value < 1)
		return false;

	return knapsack->addItem(index, item);
}

// Usuwanie obiektu klasy CKnapsack.
void CMyHandle::del()
{
	if (knapsack != NULL)
	{
		delete knapsack;
		knapsack = NULL;
	}
}

/* Uruchomienie algorytmu BF dla problemu plecakowego.
Wyswietlanie wynikow na podstawie parametru 'debug'.*/
void CMyHandle::bruteForce(bool debug)
{
	if (debug)
		startCounter();

	int j;
	int tempWeight;
	int tempValue;
	int bestValue = 0;
	int bestWeight = 0;
	double iterations = pow(2, knapsack->getNumberOfElements());
	double time;

	// Generowanie tablic dynamicznych.
	bool* b_items = new bool[knapsack->getNumberOfElements()];
	bool* bestItems = new bool[knapsack->getNumberOfElements()];

	// Inicjalizacja tablicy wybranych elementow.
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		b_items[i] = false;
	}

	for (double i = 0; i < iterations-1; i++)
	{
		j = knapsack->getNumberOfElements() -1;
		tempWeight = 0;
		tempValue = 0;

		while (b_items[j] && j > 0)
		{
			b_items[j] = false;
			j--;
		}

		b_items[j] = true;

		/*for (int z = 0; z < knapsack->getNumberOfElements(); z++)
		{
			std::cout << b_items[z] << " ";
		}
		std::cout << std::endl;*/

		for (int k = 0; k < knapsack->getNumberOfElements(); k++)
		{
			if (b_items[k])
			{
				tempWeight += knapsack->getItems()[k].weight;
				tempValue += knapsack->getItems()[k].value;
			}
		}
		if (tempValue > bestValue && tempWeight <= knapsack->getBackpackSize())
		{
			bestWeight = tempWeight;
			bestValue = tempValue;
			
			for (int k = 0; k < knapsack->getNumberOfElements(); k++)
				bestItems[k] = b_items[k];
		}
	}

	// Wypisanie wyniku.
	if (debug)
	{
		time = getCounter();
		printResults(bestItems, bestWeight, bestValue, knapsack->getItems(), time);
	}

	// Usuniecie tablic dynamicznych.
	delete[] b_items;
	delete[] bestItems;
}

void CMyHandle::branchAndBoundBFS(bool debug)
{
	double time;
	if (debug)
		startCounter();

	int j = 0;
	int bestValue;
	int bestWeight;

	// Generowanie tablic dynamicznych.
	bool* bestItems = new bool[knapsack->getNumberOfElements()];
	item* items = new item[knapsack->getNumberOfElements()];
	double* valueToWeight = new double[knapsack->getNumberOfElements()];

	CNode* parentNode;
	CNode* childNode0;
	CNode* childNode1;
	std::queue<CNode*> myQueue;

	// Inicjalizacja tablic.
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		bestItems[i] = false;
		items[i] = knapsack->getItems()[i];
		valueToWeight[i] = (double)items[i].value / (double)items[i].weight;
	}

	// Sortowanie tablic wedlug kryterium stosunku wartosci do wagi.
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		j = i;
		while (j > 0 && valueToWeight[j - 1] < valueToWeight[j])
		{
			itemSwap(items[j - 1], items[j]);
			doubleSwap(valueToWeight[j - 1], valueToWeight[j]);
			j--;
		}
	}

	parentNode = new CNode(knapsack->getNumberOfElements());
	calculateBound(parentNode, knapsack, items);
	myQueue.push(parentNode);

	//knapsack->print();
	//parentNode->print(knapsack->getNumberOfElements());

	bestValue = parentNode->getValue();
	bestWeight = parentNode->getWeight();

	while (!myQueue.empty())
	{
		parentNode = myQueue.front();
		myQueue.pop();

		childNode1 = new CNode(parentNode, knapsack->getNumberOfElements());
		childNode0 = new CNode(parentNode, knapsack->getNumberOfElements());

		childNode1->setItem(true, childNode1->getLevel());
		childNode1->setValue(childNode1->getValue() + items[childNode1->getLevel()].value);
		childNode1->setWeight(childNode1->getWeight() + items[childNode1->getLevel()].weight);
		if (childNode1->getLevel() < knapsack->getNumberOfElements())
		{
			childNode1->addLevel();
			childNode0->addLevel();
		}

		calculateBound(childNode1, knapsack, items);
		calculateBound(childNode0, knapsack, items);

		//childNode1->print(knapsack->getNumberOfElements());

		if (childNode1->getValue() > bestValue && childNode1->getWeight() <= knapsack->getBackpackSize())
		{
			bestValue = childNode1->getValue();
			bestWeight = childNode1->getWeight();
			for (int i = 0; i < knapsack->getNumberOfElements(); i++)
				bestItems[i] = childNode1->getItems()[i];
		}

		if (childNode1->getBound() > bestValue)
			myQueue.push(childNode1);
		else
			delete childNode1;

		//childNode0->print(knapsack->getNumberOfElements());

		if (childNode0->getValue() > bestValue)
		{
			bestValue = childNode0->getValue();
			bestWeight = childNode0->getWeight();
			for (int i = 0; i < knapsack->getNumberOfElements(); i++)
				bestItems[i] = childNode0->getItems()[i];
		}

		if (childNode0->getBound() > bestValue)
			myQueue.push(childNode0);
		else
			delete childNode0;

		delete parentNode;
	}

	// Wypisanie wyniku.
	if (debug)
	{
		time = getCounter();
		printResults(bestItems, bestWeight, bestValue, items, time);
	}

	// Usuniecie tablic dynamicznych.
	delete[] bestItems;
	delete[] items;
	delete[] valueToWeight;

	while (!myQueue.empty())
	{
		parentNode =  myQueue.front();
		myQueue.pop();
		delete parentNode;
	}
}

void CMyHandle::branchAndBoundBestFirst(bool debug)
{
	double time;
	if (debug)
		startCounter();

	int j = 0;
	int bestValue;
	int bestWeight;

	// Generowanie tablic dynamicznych.
	bool* bestItems = new bool[knapsack->getNumberOfElements()];
	item* items = new item[knapsack->getNumberOfElements()];
	double* valueToWeight = new double[knapsack->getNumberOfElements()];

	CNode* parentNode;
	CNode* childNode0;
	CNode* childNode1;
	std::priority_queue<CNode*, std::vector<CNode*>, Comparator> myPriorityQueue;

	// Inicjalizacja tablic.
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		bestItems[i] = false;
		items[i] = knapsack->getItems()[i];
		valueToWeight[i] = (double)items[i].value / (double)items[i].weight;
	}

	// Sortowanie tablic wedlug kryterium stosunku wartosci do wagi.
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		j = i;
		while (j > 0 && valueToWeight[j - 1] < valueToWeight[j])
		{
			itemSwap(items[j - 1], items[j]);
			doubleSwap(valueToWeight[j - 1], valueToWeight[j]);
			j--;
		}
	}

	//knapsack->print();

	parentNode = new CNode(knapsack->getNumberOfElements());
	calculateBound(parentNode, knapsack, items);
	//parentNode->print(knapsack->getNumberOfElements());

	myPriorityQueue.push(parentNode);

	bestValue = parentNode->getValue();
	bestWeight = parentNode->getWeight();

	while (!myPriorityQueue.empty())
	{
		parentNode = myPriorityQueue.top();
		myPriorityQueue.pop();

		if (parentNode->getBound() > bestValue)
		{
			childNode1 = new CNode(parentNode, knapsack->getNumberOfElements());
			childNode0 = new CNode(parentNode, knapsack->getNumberOfElements());

			childNode1->setItem(true, childNode1->getLevel());
			childNode1->setValue(childNode1->getValue() + items[childNode1->getLevel()].value);
			childNode1->setWeight(childNode1->getWeight() + items[childNode1->getLevel()].weight);
			if (childNode1->getLevel() < knapsack->getNumberOfElements())
			{
				childNode1->addLevel();
				childNode0->addLevel();
			}

			calculateBound(childNode1, knapsack, items);
			calculateBound(childNode0, knapsack, items);

			//childNode1->print(knapsack->getNumberOfElements());

			if (childNode1->getValue() > bestValue && childNode1->getWeight() <= knapsack->getBackpackSize())
			{
				bestValue = childNode1->getValue();
				bestWeight = childNode1->getWeight();
				for (int i = 0; i < knapsack->getNumberOfElements(); i++)
					bestItems[i] = childNode1->getItems()[i];
			}

			if (childNode1->getBound() > bestValue)
				myPriorityQueue.push(childNode1);
			else
				delete childNode1;

			//childNode0->print(knapsack->getNumberOfElements());

			if (childNode0->getValue() > bestValue)
			{
				bestValue = childNode0->getValue();
				bestWeight = childNode0->getWeight();
				for (int i = 0; i < knapsack->getNumberOfElements(); i++)
					bestItems[i] = childNode0->getItems()[i];
			}

			if (childNode0->getBound() > bestValue)
				myPriorityQueue.push(childNode0);
			else
				delete childNode0;
		}
		delete parentNode;
	}

	// Wypisanie wyniku.
	if (debug)
	{
		time = getCounter();
		printResults(bestItems, bestWeight, bestValue, items, time);
	}

	// Usuniecie tablic dynamicznych.
	delete[] bestItems;
	delete[] items;
	delete[] valueToWeight;

	while (!myPriorityQueue.empty())
	{
		parentNode = myPriorityQueue.top();
		myPriorityQueue.pop();
		delete parentNode;
	}
}

void CMyHandle::dynamic(bool debug)
{
	double time;
	if (debug)
		startCounter();

	int elements = knapsack->getNumberOfElements();
	int capacity = knapsack->getBackpackSize();
	int bestWeight = 0;

	// Generowanie tablic dynamicznych.
	item* items = new item[knapsack->getNumberOfElements()];
	bool* bestChoice = new bool[knapsack->getNumberOfElements()];
	int** table = new int*[knapsack->getNumberOfElements() + 1];

	// Inicjalizacja tablic dynamicznych.
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		items[i] = knapsack->getItems()[i];
		table[i] = new int[knapsack->getBackpackSize() + 1];
		bestChoice[i] = false;
	}
	table[knapsack->getNumberOfElements()] = new int[knapsack->getBackpackSize() + 1];

	for (int i = 0; i <= knapsack->getNumberOfElements(); i++)
		for (int j = 0; j <= knapsack->getBackpackSize(); j++)
			table[i][j] = 0;

	// Wypelnianie tablicy dwuwymiarowej.
	for (int i = 1; i <= knapsack->getNumberOfElements(); i++)
		for (int j = 0; j <= knapsack->getBackpackSize(); j++)
			if (j < items[i - 1].weight)
				table[i][j] = table[i - 1][j];
			else
				table[i][j] = max(table[i - 1][j], items[i - 1].value + table[i - 1][j - items[i - 1].weight]);

	// Odczyt wybranych przedmiotow na podstawie tablicy dwuwymiarowej.
	while (capacity > 0 && elements > 0)
	{
		if (table[elements][capacity] != table[elements - 1][capacity])
		{
			bestChoice[elements - 1] = true;
			capacity -= items[elements - 1].weight;
		}
		elements--;
	}

	// Wyliczenie wagi plecaka.
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
		if (bestChoice[i])
			bestWeight += items[i].weight;

	// Wypisanie wyniku.
	if (debug)
	{
		time = getCounter();
		printResults(bestChoice, bestWeight, table[knapsack->getNumberOfElements()][knapsack->getBackpackSize()], items, time);
	}

	// Usuniecie tablic dynamicznych.
	delete[] bestChoice;
	delete[] items;

	for (int i = 0; i <= knapsack->getNumberOfElements(); i++)
		delete[] table[i];

	delete[] table;
}

void CMyHandle::FPTAS(bool debug)
{
	double time = 0;
	if (debug)
		startCounter();

	int bestValue = 0;
	int bestWeight = 0;
	int maxValue = 0;
	double scale;
	int bestValue2 = 0;

	// Generowanie tablic dynamicznych.
	item* items = new item[knapsack->getNumberOfElements()];
	bool* bestChoice = new bool[knapsack->getNumberOfElements()];
	int** table = new int*[knapsack->getNumberOfElements() + 1];

	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		items[i] = knapsack->getItems()[i];
		bestChoice[i] = false;
	}

	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
		if (maxValue < items[i].value)
			maxValue = items[i].value;

	scale = (knapsack->getError() * maxValue) / (double)knapsack->getNumberOfElements();

	maxValue = (double)maxValue / scale;

	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		items[i].value = (double)items[i].value / scale;
		table[i] = new int[knapsack->getNumberOfElements() * maxValue + 1];
	}
	table[knapsack->getNumberOfElements()] = new int[knapsack->getNumberOfElements() * maxValue + 1];

	for (int i = 0; i <= knapsack->getNumberOfElements(); i++)
		table[i][0] = 0;
	for (int i = 1; i <= knapsack->getNumberOfElements() * maxValue; i++)
		table[0][i] = INT_MAX;

	for (int i = 1; i <= (knapsack->getNumberOfElements() * maxValue); i++)
	{
		for (int j = 1; j <= knapsack->getNumberOfElements(); j++)
		{
			if (i < items[j - 1].value)
				table[j][i] = table[j - 1][i];
			else if (table[j - 1][i - items[j - 1].value] == INT_MAX)
				table[j][i] = table[j - 1][i];
			else
				table[j][i] = min(table[j - 1][i], table[j - 1][i - items[j - 1].value] + items[j - 1].weight);
		}
		if (table[knapsack->getNumberOfElements()][i] <= knapsack->getBackpackSize())
		{
			bestValue = i;
		}
	}

	/*for (int j = 0; j <= knapsack->getNumberOfElements(); j++)
	{
		for (int i = 0; i <= (knapsack->getNumberOfElements() * maxValue); i++)
		{
			std::cout << table[j][i] << " ";
		}
		std::cout << std::endl;
	}*/

	bestValue2 = bestValue;

	for (int k = knapsack->getNumberOfElements(); k > 0; k--)
	{
		if (bestValue2 - items[k - 1].value >= 0)
		{
			if (table[k][bestValue2] == table[k - 1][bestValue2 - items[k - 1].value] + items[k - 1].weight)
			{
				bestChoice[k - 1] = true;
				bestValue2 = bestValue2 - items[k - 1].value;
			}
		}
	}

	// Wyliczenie wagi plecaka.
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
		if (bestChoice[i])
			bestWeight += items[i].weight;

	if (debug)
	{
		time = getCounter();
		printResults(bestChoice, bestWeight, bestValue*scale, knapsack->getItems(), time);
	}

	delete[] items;
	delete[] bestChoice;
	
	for (int i = 0; i < knapsack->getNumberOfElements() + 1; i++)
		delete[] table[i];
	delete[] table;
}

void CMyHandle::calculateBound(CNode* node, CKnapsack* knapsack, item* items)
{
	int totalWeight;
	int bound;
	int i = node->getLevel();

	if (node->getWeight() > knapsack->getBackpackSize())
	{
		node->setBound(0);
		return;
	}

	totalWeight = node->getWeight();
	bound = node->getValue();

	while(i < knapsack->getNumberOfElements() && totalWeight < knapsack->getBackpackSize())
	{
		totalWeight += items[i].weight;
		i++;
	}

	for (int j = node->getLevel(); j < i; j++)
	{
		bound += items[j].value;
	}

	if(totalWeight > knapsack->getBackpackSize())
		bound -= (totalWeight - knapsack->getBackpackSize()) * (items[i-1].value / items[i-1].weight);

	node->setBound(bound);
}

/* Wyswietlanie wynikow dzialania algorytmu rozwiazujacego problem plecakowy.
Parametry:
- bool* bestChoice - wskaznik na tablice zawierajaca informacje, ktore przedmioty zostaly wlozone do plecaka
- int bestWeight - waga przedmiotow w plecaku
- int bestValue - wartosc przedmiotow w plecaku*/
void CMyHandle::printResults(bool* bestItems, int bestWeight, int bestValue, item* items, double time)
{
	std::cout << "LICZBA ELEMENTOW: " << knapsack->getNumberOfElements() << std::endl;
	std::cout << "ROZMIAR PLECAKA: " << knapsack->getBackpackSize() << std::endl;
	std::cout << std::endl;
	std::cout << "TABLICA WAG(w) I WARTOSCI(v):" << std::endl;

	std::cout << "i: ";
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		std::cout.width(3);
		std::cout << i;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "w: ";
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		std::cout.width(3);
		std::cout << items[i].weight;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "v: ";
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		std::cout.width(3);
		std::cout << items[i].value;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "c: ";
	for (int i = 0; i < knapsack->getNumberOfElements(); i++)
	{
		std::cout.width(3);
		std::cout << bestItems[i];
		std::cout << " ";
	}

	std::cout << std::endl;
	std::cout << "LACZNA WAGA: " << bestWeight << std::endl;
	std::cout << "LACZNA WARTOSC: " << bestValue << std::endl;
	std::cout << "CZAS WYKONANIA: " << time << " ms" << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

/* Uruchomienie 100 testow algorytmu rozwiazujacego problem plecakowy.
Parametry:
- char algorithm - kod algorytmu
- int numberOfElements - liczba elementow ktore mozna wlozyc do plecaka
- int backpackSize - rozmiar plecaka*/
double CMyHandle::test(char algorithm, int numberOfElemets, int backpackSize, double error)
{
	double result = 0;

	for (int i = 0; i < 100; i++)
	{
		create(numberOfElemets, backpackSize, error);
		generate();

		switch (algorithm)
		{
		case '1':
			startCounter();
			bruteForce(false);
			result += getCounter();
			break;
			
		case '2':
			startCounter();
			branchAndBoundBFS(false);
			result += getCounter();
			break;

		case '3':
			startCounter();
			branchAndBoundBestFirst(false);
			result += getCounter();
			break;

		case '4':
			startCounter();
			dynamic(false);
			result += getCounter();
			break;

		case '5':
			startCounter();
			FPTAS(false);
			result += getCounter();
			break;

		default:
			return 0;
		}
	}
	return result/100;
}
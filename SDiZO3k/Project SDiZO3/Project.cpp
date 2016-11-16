#include "stdafx.h"
#include "Project.h"


CProject::CProject()
{
	handle = new CMyHandle();
}

CProject::~CProject()
{
	delete handle;
}

void CProject::title()
{
	system("CLS");

	std::cout << "PROJEKT SDiZO 3" << std::endl;
	std::cout << std::endl;
	std::cout << "Piotr Kowalski" << std::endl;
	std::cout << "Nr indeksu: 209902" << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << std::endl;
}

void CProject::problemName(char problem)
{
	std::cout << "WYBRANY PROBLEM: ";

	switch (problem)
	{
	case '1':
		std::cout << "DYSKRETNY PROBLEM PECAKOWY" << std::endl;
		break;

	case '2':
		std::cout << "PROBLEM KOMIWOJAZERA" << std::endl;
		break;

	default:
		return;
	}
}

void CProject::algorithmName(char problem, char algorithm)
{
	std::cout << "WYBRANY ALGORYTM: ";

	switch (algorithm)
	{
	case '1':
		std::cout << "PRZEGLAD ZUPELNY" << std::endl;
		break;

	case '2':
		if (problem == '1')
			std::cout << "ZACHLANNY - KRYTERIUM WARTOSCI" << std::endl;
		if (problem == '2')
			std::cout << "ZACHLANNY" << std::endl;
		break;

	case '3':
		if (problem == '1')
			std::cout << "ZACHLANNY - KRYTERIUM STOSUNKU WARTOSCI DO WAGI" << std::endl;
		if (problem == '2')
			std::cout << "PRZESZUKIWANIE LOKALNE" << std::endl;
		break;

	case '4':
		if (problem == '1')
			std::cout << "DYNAMICZNY" << std::endl;
		else
			return;

	default:
		return;
	}
}

void CProject::error()
{
	title();
	std::cout << "BLAD !" << std::endl;
	std::cout << "NIE WYKONANO POLECENIA." << std::endl;
	std::cout << "SPRAWDZ DANE WEJSCIOWE I SPROBUJ PONOWNIE." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CProject::wrongOption()
{
	title();
	std::cout << "PODANA OPCJA NIE ISTNIEJE!" << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CProject::pointerEmpty()
{
	title();
	std::cout << "OBIEKT NIE ZOSTAL UTWORZONY." << std::endl;
	std::cout << "ABY MOC WYKONAC PROCEDURE UTWORZ OBIEKT." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CProject::buildFromFile(char problem)
{
	std::string filePath;

	title();
	problemName(problem);

	std::cout << "SCIEZKA DO PLIKU: ";
	std::cin >> filePath;
	std::cout << std::endl;
	std::cout << "BUDOWA OBIEKTU ROZPOCZETA..." << std::endl;
	std::cout << std::endl;

	if (handle->buildFromFile(problem, filePath))
		std::cout << "OBIEKT ZBUDOWANY POMYSLNIE." << std::endl;
	else
		std::cout << "BUDOWA OBIEKTU NIE POWIODLA SIE." << std::endl;

	std::cout << std::endl;
	system("PAUSE");
}

void CProject::runAlgorithm(char problem, char algorithm)
{
	title();
	problemName(problem);
	algorithmName(problem, algorithm);

	if (problem == '1')
	{
		switch (algorithm)
		{
		case '1':
			handle->knapsackBruteForce(true);
			break;

		case '2':
			handle->knapsackGreedyValue(true);
			break;

		case '3':
			handle->knapsackGreddyValueToWeight(true);
			break;

		case'4':
			handle->knapsackDynamic(true);
			break;

		default:
			return;
		}
	}

	if (problem == '2')
	{
		switch (algorithm)
		{
		case'1':
			handle->graphBruteForce(true);
			break;

		case'2':
			handle->graphGreedy(true);
			break;

		case'3':
			handle->graphLocalSearch(true);
			break;

		default:
			return;
		}
	}
}

void CProject::display(char problem)
{
	title();
	problemName(problem);

	switch (problem)
	{
	case '1':
		handle->getKnapsack()->print();
		std::cout << std::endl;
		system("PAUSE");
		break;

	case '2':
		handle->getMatrixGraph()->print();
		std::cout << std::endl;
		system("PAUSE");
		break;

	default:
		error();
		break;
	}
}

void CProject::graphFromScratch(char problem)
{
	int vertices, weight;

	title();
	problemName(problem);

	std::cout << "LICZBA WIERZCHOLKOW: ";
	std::cin >> vertices;
	std::cout << std::endl;

	if (!handle->createGraph(vertices))
	{
		error();
		return;
	}

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
		{
			title();
			problemName(problem);
			if (i != j)
			{
				std::cout << "PODAJ ODLEGLOSC MIEDZY MIASTAMI NR " << i + 1 << " I " << j + 1 << ": ";
				std::cin >> weight;
				std::cout << std::endl;


				if (!handle->addEdge(i, j, weight))
				{
					error();
					handle->delGraph();
					return;
				}
			}
		}

	title();
	problemName(problem);

	std::cout << "BUDOWA GRAFU ZAKONCZONA." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CProject::graphRandom(char problem)
{
	int vertices;

	title();
	problemName(problem);

	std::cout << "LICZBA WIERZCHOLKOW: ";
	std::cin >> vertices;
	std::cout << std::endl;

	if (!handle->createGraph(vertices))
	{
		error();
		return;
	}

	if (!handle->generateGraph())
	{
		handle->delGraph();
		error();
		return;
	}

	title();
	problemName(problem);

	std::cout << "BUDOWA GRAFU ZAKONCZONA." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CProject::knapsackFromScratch(char problem)
{
	int numberOfElements, backpackSize, weight, value;

	title();
	problemName(problem);

	std::cout << "LICZBA ELEMENTOW: ";
	std::cin >> numberOfElements;
	std::cout << "ROZMIAR PLECAKA: ";
	std::cin >> backpackSize;

	if (!handle->createKnapsack(numberOfElements, backpackSize))
	{
		error();
		return;
	}

	for (int i = 0; i < numberOfElements; i++)
	{
		title();
		problemName(problem);

		std::cout << "WAGA PRZEDMIOTU NR " << i + 1 << " : ";
		std::cin >> weight;
		std::cout << "WARTOSC PRZEDMIOTU NR " << i + 1 << " : ";
		std::cin >> value;

		if (!handle->addItem(i, weight, value))
		{
			error();
			handle->delKnapsack();
			return;
		}
	}

	title();
	problemName(problem);

	std::cout << "BUDOWA OBIEKTU ZAKONCZONA" << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CProject::knapsackRandom(char problem)
{
	int numberOfElements, backpackSize;

	title();
	problemName(problem);

	std::cout << "LICZBA ELEMENTOW: ";
	std::cin >> numberOfElements;
	std::cout << "ROZMIAR PLECAKA: ";
	std::cin >> backpackSize;

	if (!handle->createKnapsack(numberOfElements, backpackSize))
	{
		error();
		return;
	}
	
	if (!handle->generateKnapsack())
	{
		error();
		handle->delKnapsack();
		return;
	}

	title();
	problemName(problem);

	std::cout << "BUDOWA OBIEKTU ZAKONCZONA." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CProject::endMenu()
{
	title();
	std::cout << "PROGRAM ZAKONCZY SWOJE DZIALANIE" << std::endl;
	std::cout << "DZIEKUJEMY ZA WSPOLPRACE!" << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

void CProject::problemMenu()
{
	while (true)
	{
		title();
		std::cout << "WYBIERZ PROBLEM:" << std::endl;
		std::cout << "1. DYSKRETNY PROBLEM PLECAKOWY" << std::endl;
		std::cout << "2. PROBLEM KOMIWOJAZERA" << std::endl;
		std::cout << "3. POWROT" << std::endl;
		std::cout << "WYBRANA OPCJA: ";
		std::cin >> str_option;

		c_option = str_option.front();
		
		switch (c_option)
		{
		case '1':
			debugMenu(c_option);
			break;

		case '2':
			debugMenu(c_option);
			break;

		case '3':
			return;

		default:
			wrongOption();
		}
	}
}

void CProject::debugMenu(char problem)
{
	while (true)
	{
		title();
		problemName(problem);

		bool objectCreated = (problem == '1' && handle->getKnapsack() != NULL || problem == '2' && handle->getMatrixGraph() != NULL);

		std::cout << "WYBIERZ OPCJE:" << std::endl;
		std::cout << "1. ZBUDUJ OBIEKT Z PLIKU" << std::endl;
		std::cout << "2. ZBUDUJ OBIEKT Z KONSOLI" << std::endl;
		std::cout << "3. WYGENERUJ LOSOWY OBIEKT" << std::endl;

		if (objectCreated)
		{
			std::cout << "4. WYSWIETL OBIEKT" << std::endl;
			std::cout << "5. PRZEGLAD ZUPELNY" << std::endl;

			if (problem == '1')
			{
				std::cout << "6. ALGORYTM ZACHLANNY - KRYTERIUM WARTOSCI" << std::endl;
				std::cout << "7. ALGORYTM ZACHLANNY - KRYTERIUM STOSUNKU WARTOSCI DO WAGI" << std::endl;
				std::cout << "8. ALGORYTM DYNAMICZY" << std::endl;
			}
			if (problem == '2')
			{
				std::cout << "6. ALGORYTM ZACHLANNY" << std::endl;
				std::cout << "7. PRZESZUKIWANIE LOKALNE" << std::endl;
			}
		}

		std::cout << "0. POWROT" << std::endl;
		std::cout << "WYBRANA OPCJA: ";
		std::cin >> str_option;

		c_option = str_option.front();

		switch (c_option)
		{
		case '1':
			buildFromFile(problem);
			break;

		case '2':
			if (problem == '1')
				knapsackFromScratch(problem);
			if (problem == '2')
				graphFromScratch(problem);
			break;

		case '3':
			if (problem == '1')
				knapsackRandom(problem);
			if (problem == '2')
				graphRandom(problem);
			break;

		case '4':
			if (objectCreated)
				display(problem);
			else
				pointerEmpty();
			break;

		case '5':
			if (objectCreated)
				runAlgorithm(problem, '1');
			else
				pointerEmpty();
			break;

		case '6':
			if (objectCreated)
				runAlgorithm(problem, '2');
			else
				pointerEmpty();
			break;

		case '7':
			if (objectCreated)
				runAlgorithm(problem, '3');
			else
				pointerEmpty();
			break;

		case '8':
			if (objectCreated)
				runAlgorithm(problem, '4');
			else
				pointerEmpty();
			break;

		case '0':
			return;

		default:
			wrongOption();
		}
	}
}

void CProject::timeTestMenu()
{
	int backpackSize[3];
	int numberOfElements[5];
	int numberOfCities[5];

	for (int i = 0; i < 5; i++)
	{
		title();

		std::cout << "PODAJ LICZBE PRZEDMIOTOW DLA TESTU NR: " << i + 1 << ": ";
		std::cin >> numberOfElements[i];
		std::cout << std::endl;
		std::cout << "PODAJ LICZBE MIAST DLA TESTU NR: " << i + 1 << ": ";
		std::cin >> numberOfCities[i];
	}

	for (int i = 0; i < 3; i++)
	{
		title();

		std::cout << "PODAJ ROZMIAR PLECAKA NR: " << i + 1 << ": ";
		std::cin >> backpackSize[i];
	}

	title();

	for (int i = 0; i < 5; i++)
	{
		std::cout << "TEST NR: " << i + 1 << std::endl;
		runTests(numberOfElements[i], backpackSize, numberOfCities[i]);
	}

	system("PAUSE");
}

void CProject::runTests(int numberOfElements, int* backpackSize, int numberOfCities)
{
	std::cout << "DYSKRETNY PROBLEM PLECAKOWY" << std::endl;
	std::cout << "LICZBA ELEMENTOW: " << numberOfElements << std::endl;
	
	for (int i = 0; i < 3; i++)
	{
		std::cout << "   ROZMIAR PLECAKA: " << backpackSize[i] << std::endl;
		std::cout << "   PRZEGLAD ZUPELNY: " << handle->testKnapsack('1', numberOfElements, backpackSize[i]) << std::endl;
		std::cout << "   AlGORYTM ZACHLANNY - KRYTERIUM WARTOSCI: " << handle->testKnapsack('2', numberOfElements, backpackSize[i]) << std::endl;
		std::cout << "   ALGORYTM ZACHLANNY - KRYTERIUM STOSUNKU WARTOSCI DO WAGI: " << handle->testKnapsack('3', numberOfElements, backpackSize[i]) << std::endl;
		std::cout << "   ALGORYTM DYNAMICZNY: " << handle->testKnapsack('4', numberOfElements, backpackSize[i]) << std::endl;
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "PROBLEM KOMIWOJAZERA" << std::endl;
	std::cout << "LICZBA MIAST: " << numberOfCities << std::endl;
	std::cout << "   PRZEGLAD ZUPELNY: " << handle->testGraph('1', numberOfCities) << std::endl;
	std::cout << "   ALGORYTM ZACHLANNY: " << handle->testGraph('2', numberOfCities) << std::endl;
	std::cout << "   PRZESZUKIWANIE LOKALNE: " << handle->testGraph('3', numberOfCities) << std::endl;
	std::cout << std::endl;
}

void CProject::start()
{
	while (true)
	{
		title();
		std::cout << "WYBIERZ OPCJE: " << std::endl;
		std::cout << "1. TESTUJ CZAS OPERACJI" << std::endl;
		std::cout << "2. TESTUJ POPRAWNOSC" << std::endl;
		std::cout << "3. ZAKONCZ PROGRAM" << std::endl;
		std::cout << "WYBRANA OPCJA: ";
		std::cin >> str_option;

		c_option = str_option.front();

		switch (c_option)
		{
		case '1':
			timeTestMenu();
			break;

		case '2':
			problemMenu();
			break;

		case '3':
			endMenu();
			return;

		default:
			wrongOption();
		}
	}
}
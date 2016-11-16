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

// Generowanie naglowka.
void CProject::title()
{
	system("CLS");

	std::cout << "PEA LAB 3" << std::endl;
	std::cout << "=====================================================" << std::endl;
	std::cout << std::endl;
}

// Wyswietlanie nazwy algorytmu na podstawie parametru 'algorithm'.
void CProject::algorithmName(char algorithm)
{
	std::cout << "WYBRANY ALGORYTM: ";

	switch (algorithm)
	{
	case '1':
		std::cout << "PRZEGLAD ZUPELNY" << std::endl;
		break;

	case '2':
		std::cout << "FPTAS" << std::endl;
		break;

	default:
		return;
	}
}

// Wyswietlanie komunikatu o nieznanym bledzie.
void CProject::showError()
{
	title();
	std::cout << "BLAD !" << std::endl;
	std::cout << "NIE WYKONANO POLECENIA." << std::endl;
	std::cout << "SPRAWDZ DANE WEJSCIOWE I SPROBUJ PONOWNIE." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

// Wyswietlanie komunikatu o wprowadzeniu nieprawnego nr opcji.
void CProject::wrongOption()
{
	title();
	std::cout << "PODANA OPCJA NIE ISTNIEJE!" << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

// Wyswietlenie komunikatu o probie wykonania operacji na nieutworzonej strukturze.
void CProject::pointerEmpty()
{
	title();
	std::cout << "OBIEKT NIE ZOSTAL UTWORZONY." << std::endl;
	std::cout << "ABY MOC WYKONAC PROCEDURE UTWORZ OBIEKT." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

// Tworzenie obiektu klasy CKnapsack.
void CProject::buildFromFile()
{
	int backpackSize;
	double error;
	std::string filePath;

	title();

	std::cout << "ROZMIAR PLECAKA: ";
	std::cin >> backpackSize;
	std::cout << "DOPUSZCZALNY BLAD (DLA FPTAS): ";
	std::cin >> error;
	std::cout << "SCIEZKA DO PLIKU: ";
	std::cin >> filePath;
	std::cout << std::endl;
	std::cout << "BUDOWA OBIEKTU ROZPOCZETA..." << std::endl;
	std::cout << std::endl;

	// Uruchomienie funkcji pobierajacej dane z pliku.
	if (handle->build(filePath, backpackSize, error))
		std::cout << "OBIEKT ZBUDOWANY POMYSLNIE." << std::endl;
	else
		std::cout << "BUDOWA OBIEKTU NIE POWIODLA SIE." << std::endl;

	std::cout << std::endl;
	system("PAUSE");
}

// Uruchomienie odpowiedniego algorytmu na podstawie wartoœci parametru 'algorithm'.
void CProject::runAlgorithm(char algorithm)
{
	title();
	algorithmName(algorithm);

	switch (algorithm)
	{
	case '1':
		handle->bruteForce(true);
		break;
	case '2':
		handle->FPTAS(true);
		break;

	default:
		return;
	}
}

// Wyswietlenie obiektu klasy CKnapsack.
void CProject::display()
{
	title();

	handle->getKnapsack()->print();
	std::cout << std::endl;
	system("PAUSE");
}

// Utworzenie obiektu klasy CKnapsack z konsoli.
void CProject::buildFromScratch()
{
	int numberOfElements, backpackSize;
	double error;
	::item item;

	title();

	std::cout << "LICZBA ELEMENTOW: ";
	std::cin >> numberOfElements;
	std::cout << "ROZMIAR PLECAKA: ";
	std::cin >> backpackSize;
	std::cout << "DOPUSZCZALNY BLAD (DLA FPTAS): ";
	std::cin >> error;

	// UTworzenie obiektu.
	if (!handle->create(numberOfElements, backpackSize, error))
	{
		showError();
		return;
	}

	for (int i = 0; i < numberOfElements; i++)
	{
		title();

		std::cout << "WAGA PRZEDMIOTU NR " << i + 1 << " : ";
		std::cin >> item.weight;
		std::cout << "WARTOSC PRZEDMIOTU NR " << i + 1 << " : ";
		std::cin >> item.value;

		// Dodawanie przedmiotow.
		if (!handle->addItem(i, item))
		{
			showError();
			handle->del();
			return;
		}
	}

	title();

	std::cout << "BUDOWA OBIEKTU ZAKONCZONA" << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

// Wygenerowanie losowego obiektu klasy CKnapsack.
void CProject::buildRandom()
{
	int numberOfElements, backpackSize;
	double error;

	title();

	std::cout << "LICZBA ELEMENTOW: ";
	std::cin >> numberOfElements;
	std::cout << "ROZMIAR PLECAKA: ";
	std::cin >> backpackSize;
	std::cout << "DOPUSZCZALNY BLAD (DLA FPTAS): ";
	std::cin >> error;

	// Utworzenie obiektu.
	if (!handle->create(numberOfElements, backpackSize, error))
	{
		showError();
		return;
	}
	
	// Generowanie przedmiotow.
	if (!handle->generate())
	{
		showError();
		handle->del();
		return;
	}

	title();

	std::cout << "BUDOWA OBIEKTU ZAKONCZONA." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

// Wyswietlenie opcji sprawdzajacych poprawnosc.
void CProject::debugMenu()
{
	bool objectCreated;

	while (true)
	{
		objectCreated = (handle->getKnapsack() != NULL);

		title();

		std::cout << "WYBIERZ OPCJE:" << std::endl;
		std::cout << "1. ZBUDUJ OBIEKT Z PLIKU" << std::endl;
		std::cout << "2. ZBUDUJ OBIEKT Z KONSOLI" << std::endl;
		std::cout << "3. WYGENERUJ LOSOWY OBIEKT" << std::endl;

		if (objectCreated)
		{
			std::cout << "4. WYSWIETL OBIEKT" << std::endl;
			std::cout << "5. PRZEGLAD ZUPELNY" << std::endl;
			std::cout << "6. ALGORYTM APROKSYMACYJNY FPTAS" << std::endl;
		}

		std::cout << "0. POWROT" << std::endl;
		std::cout << "WYBRANA OPCJA: ";
		std::cin >> str_option;

		c_option = str_option.front();

		switch (c_option)
		{
		case '1':
			buildFromFile();
			break;

		case '2':
			buildFromScratch();
			break;

		case '3':
			buildRandom();
			break;

		case '4':
			if (objectCreated)
				display();
			else
				pointerEmpty();
			break;

		case '5':
			if (objectCreated)
				runAlgorithm('1');
			else
				pointerEmpty();
			break;

		case '6':
			if (objectCreated)
				runAlgorithm('2');
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

// Wyswietlenie dialogu przeprowadzania testow.
void CProject::timeTestMenu()
{
	std::ofstream output;
	output.open("wyniki.txt");

	int backpackSize[5];
	int numberOfElements[10];
	double error;

	title();
	std::cout << "PODAJ DOPUSZCZALNY BLAD (DOT. FPTAS): ";
	std::cin >> error;
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
	{
		std::cout << "PODAJ LICZBE PRZEDMIOTOW DLA TESTU NR: " << i + 1 << ": ";
		std::cin >> numberOfElements[i];
	}

	std::cout << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << "PODAJ ROZMIAR PLECAKA NR: " << i + 1 << ": ";
		std::cin >> backpackSize[i];
	}

	title();

	std::cout << "TRWA PRZEPROWADZANIE TESTOW." << std::endl;
	std::cout << "PROSZE CZEKAC..." << std::endl << std::endl;

	for (int i = 0; i < 10; i++)
	{
		output << "TEST NR: " << i + 1 << std::endl;
		runTests(numberOfElements[i], backpackSize, error, output);
	}

	std::cout << "WYNIKI TESTOW ZAPISANO W PLIKU: \"wyniki.txt\"." << std::endl;
	std::cout << std::endl;
	system("PAUSE");
}

// Uruchomienie zestawu testow.
void CProject::runTests(int numberOfElements, int* backpackSize, double error, std::ofstream &output)
{
	output << "LICZBA ELEMENTOW: " << numberOfElements << std::endl;

	for (int i = 0; i < 3; i++)
	{
		output << "   ROZMIAR PLECAKA: " << backpackSize[i] << std::endl;
		//output << "   PRZEGLAD ZUPELNY: " << handle->test('1', numberOfElements, backpackSize[i]) << std::endl;
		output << "   APROKSYMACYJNY FPTAS: " << handle->test('2', numberOfElements, backpackSize[i], error) << std::endl;
		output << std::endl;
	}
}

// Wyswietlenie menu poczatkowego.
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
			debugMenu();
			break;

		case '3':
			return;

		default:
			wrongOption();
		}
	}
}
#include "stdafx.h"
#include "Proj3.h"


Proj3::Proj3() // konstruktor
{
	handle = new Handle();
}

Proj3::~Proj3() // destruktor
{
	delete handle;
}

void Proj3::start() // wyświetlanie menu głównego
{
	while (true)
	{
		title();
		cout << "Wybierz opcję: \n"
			"1. Testuj czas\n"
			"2. Testuj poprawność\n"
			"0. Wyjście\n"
			"  ---> ";
		cin >> str_option;

		c_option = str_option.front();

		switch (c_option)
		{
		case '1':
			timeTestMenu();
			break;

		case '2':
			problemMenu();
			break;

		case '0':
			endMenu();
			return;

		default:
			wrongOption();
		}
	}
}

void Proj3::timeTestMenu() // menu testów czasowych
{
	int rozmiarPlecaka[3];
	int liczbaPrzedmiotow[5];
	int liczbaMiast[5];

	for (int i = 0; i < 5; i++)
	{
		title();

		cout << "Podaj liczbę przedmiotów dla testu nr " << i + 1 << ": ";
		cin >> liczbaPrzedmiotow[i];
		cout << "Podaj liczbę miast dla testu nr " << i + 1 << ": ";
		cin >> liczbaMiast[i];
	}

	for (int i = 0; i < 3; i++)
	{
		title();

		cout << "Podaj rozmiar plecaka nr " << i + 1 << ": ";
		cin >> rozmiarPlecaka[i];
	}

	title();

	for (int i = 0; i < 5; i++)
	{
		cout << "Test nr " << i + 1 << endl;
		runTests(liczbaPrzedmiotow[i], rozmiarPlecaka, liczbaMiast[i]);
	}

	system("PAUSE");
}

void Proj3::runTests(int liczbaPrzedmiotow, int* rozmiarPlecaka, int liczbaMiast) // ekran testów
{
	cout << "Dyskretny problem plecakowy:\n"
		"Liczba elementów: " << liczbaPrzedmiotow << endl;

	for (int i = 0; i < 3; i++)
	{
		cout << "   Rozmiar plecaka: " << rozmiarPlecaka[i] << endl;
		cout << "      Przegląd zupełny: " << handle->testPlecak('1', liczbaPrzedmiotow, rozmiarPlecaka[i]) << endl;
		cout << "      Algorytm zachłanny - kryterium wartości: " << handle->testPlecak('2', liczbaPrzedmiotow, rozmiarPlecaka[i]) << endl;
		cout << "      Algorytm zachłanny - kryterium stosunku wartości do wagi: " << handle->testPlecak('3', liczbaPrzedmiotow, rozmiarPlecaka[i]) << endl;
		cout << "      Algorytm dynamiczny: " << handle->testPlecak('4', liczbaPrzedmiotow, rozmiarPlecaka[i]) << endl;
	}
	cout << "Problem komiwojażera" << endl;
	cout << "Liczba miast: " << liczbaMiast << endl;
	cout << "    Przegląd zupełny: " << handle->testGraf('1', liczbaMiast) << endl;
	cout << "    Algorytm zachłanny: " << handle->testGraf('2', liczbaMiast) << endl;
	cout << "    Przeszukiwanie lokalne: " << handle->testGraf('3', liczbaMiast) << endl;
	cout << endl;
}

void Proj3::title() //nagłówek
{
	system("CLS");

	cout << "#-------------------------------#\n"
		"|        PROJEKT SDiZO 3        |\n"
		"|       Adrian Frydmański       |\n"
		"|             209865            |\n"
		"#-------------------------------#\n";
}

void Proj3::problemName(char problem) // wybór
{
	cout << "Wybrano ";

	switch (problem)
	{
	case '1':
		cout << "dyskretny problem plecakowy\n";
		break;

	case '2':
		cout << "problem komiwojażera\n";
		break;

	default:
		return;
	}
}

void Proj3::debugMenu(char problem) //menu ręcznych testów
{
	while (true)
	{
		title();
		problemName(problem);

		bool objectCreated = (problem == '1' && handle->getKnapsack() != NULL || problem == '2' && handle->getMacierzGraph() != NULL);

		cout << "Co chcesz zrobić?\n"
			"1. Stwórz obiekt z pliku\n"
			"2. Stwórz obiekt manualnie\n"
			"3. Wygeneruj losowy obiekt\n";

		if (objectCreated)
		{
			cout << "4. Wyświetl obiekt\n"
				"5. Przegląd zupełny\n";

			if (problem == '1')
			{
				cout << "6. Algorytm zachłanny - kryterium wartości\n"
					"7. Algorytm zachłanny - kryterium stosunku wartości do wagi\n"
					"8. Algorytm dynamiczny\n";
			}
			if (problem == '2')
			{
				cout << "6. Algorytm zachłanny\n"
					"7. Przeszukiwanie lokalne\n";
			}
		}

		cout << "0. Wróć\n"
			"---> ";
		cin >> str_option;

		c_option = str_option.front();

		switch (c_option)
		{
		case '1':
			stworzZPliku(problem);
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

void Proj3::algorytmName(char problem, char algorytm) // ekran wybranego algorytmu
{
	cout << "Algorytm: ";

	switch (algorytm)
	{
	case '1':
		cout << "przegląd zupełny\n";
		break;

	case '2':
		if (problem == '1')
			cout << "zachłanny - kryterium wartości\n";
		if (problem == '2')
			cout << "zachłanny\n";
		break;

	case '3':
		if (problem == '1')
			cout << "zachłanny - kryterium stosunku wartości do wagi\n";
		if (problem == '2')
			cout << "przeszukiwanie lokalne\n";
		break;

	case '4':
		if (problem == '1')
			cout << "dynamiczny\n";
		else
			return;

	default:
		return;
	}
}

void Proj3::error() // komunikat błędu
{
	title();
	cout << "Błąd bardzo krytyczny!\n";
	system("PAUSE");
}

void Proj3::wrongOption() // komunikat źle wybranej opcji
{
	title();
	cout << "Zabłądziłeś, nie tędy droga.\nWybierz inną opcję.";
	system("PAUSE");
}

void Proj3::pointerEmpty() //komunikat o braku obiektu
{
	title();
	cout << "Obiekt nie został utworzony.\nPrzed wykonaniem procedury zainicjuj obiekt.";
	system("PAUSE");
}

void Proj3::stworzZPliku(char problem) // ekran czytania z pliku
{
	string name;

	title();
	problemName(problem);
	cout << "Podaj nazwę pliku: ";
	cin >> name;
	cout << "Konstrukcja rozpoczęta...\n";
	if (handle->stworzZPliku(problem, name))
		cout << "Obiekt został utworzony.\n";
	else
		cout << "Wystąpił błąd w budowie obiektu\n";
	system("PAUSE");
}

void Proj3::runAlgorithm(char problem, char algorytm) // uruchamiacz algorytmu
{
	title();
	problemName(problem);
	algorytmName(problem, algorytm);

	if (problem == '1')
	{
		switch (algorytm)
		{
		case '1':
			handle->plecakZupelny(true);
			break;

		case '2':
			handle->plecakZachlanny(true);
			break;

		case '3':
			handle->plecakZachlannyWartoscDoWagi(true);
			break;

		case'4':
			handle->plecakDynamiczny(true);
			break;

		default:
			return;
		}
	}

	if (problem == '2')
	{
		switch (algorytm)
		{
		case'1':
			handle->grafZupelny(true);
			break;

		case'2':
			handle->grafZachlanny(true);
			break;

		case'3':
			handle->grafLokalny(true);
			break;

		default:
			return;
		}
	}
}

void Proj3::display(char problem) // wyświetlanie wyniku
{
	title();
	problemName(problem);

	switch (problem)
	{
	case '1':
		handle->getKnapsack()->wyswietl();
		cout << endl;
		system("PAUSE");
		break;

	case '2':
		handle->getMacierzGraph()->wyswietl();
		cout << endl;
		system("PAUSE");
		break;

	default:
		error();
		break;
	}
}

void Proj3::graphFromScratch(char problem) //ręczny generator grafu
{
	int vertices, weight;

	title();
	problemName(problem);

	cout << "Podaj liczbę wierzchołków: ";
	cin >> vertices;

	if (!handle->stworzGraf(vertices))
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
				cout << "Podaj odległość między miastami nr " << i + 1 << " i " << j + 1 << ": ";
				cin >> weight;
				cout << endl;


				if (!handle->dodajKrawedz(i, j, weight))
				{
					error();
					handle->usunGraf();
					return;
				}
			}
		}

	title();
	problemName(problem);

	cout << "Zbudowano graf.\n";
	system("PAUSE");
}

void Proj3::graphRandom(char problem) // losowy generator grafu
{
	int vertices;

	title();
	problemName(problem);

	cout << "Podaj liczbę wierzchołków: ";
	cin >> vertices;
	cout << endl;

	if (!handle->stworzGraf(vertices))
	{
		error();
		return;
	}

	if (!handle->wygenerujGraf())
	{
		handle->usunGraf();
		error();
		return;
	}

	title();
	problemName(problem);

	cout << "Zbudowano graf.\n";
	system("PAUSE");
}

void Proj3::knapsackFromScratch(char problem) // ręczny generator plecaka
{
	int liczbaPrzedmiotow, rozmiarPlecaka, weight, value;

	title();
	problemName(problem);

	cout << "Podaj liczbę elementów: ";
	cin >> liczbaPrzedmiotow;
	cout << "Podaj rozmiar plecaka: ";
	cin >> rozmiarPlecaka;

	if (!handle->stworzPlecak(liczbaPrzedmiotow, rozmiarPlecaka))
	{
		error();
		return;
	}

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		title();
		problemName(problem);

		cout << "Waga przedmiotu nr " << i + 1 << ": ";
		cin >> weight;
		cout << "Wartość przedmiotu nr " << i + 1 << ": ";
		cin >> value;

		if (!handle->dodajPrzedmiot(i, weight, value))
		{
			error();
			handle->usunPlecak();
			return;
		}
	}

	title();
	problemName(problem);

	cout << "Zbudowano plecak i przedmioty.\n";
	system("PAUSE");
}

void Proj3::knapsackRandom(char problem) //losowy generator plecaka
{
	int liczbaPrzedmiotow, rozmiarPlecaka;

	title();
	problemName(problem);

	cout << "Podaj liczbę elementów: ";
	cin >> liczbaPrzedmiotow;
	cout << "Podaj rozmiar plecaka: ";
	cin >> rozmiarPlecaka;

	if (!handle->stworzPlecak(liczbaPrzedmiotow, rozmiarPlecaka))
	{
		error();
		return;
	}

	if (!handle->wygenerujPlecak())
	{
		error();
		handle->usunPlecak();
		return;
	}

	title();
	problemName(problem);

	cout << "Zbudowano plecak i przedmioty.\n";
	system("PAUSE");
}

void Proj3::endMenu() //komunikat na zakończenie
{
	title();
	cout << "Dziękuję, do widzenia\n";
	system("PAUSE");
}

void Proj3::problemMenu() // ekran wyboru problemu
{
	while (true)
	{
		title();
		cout << "Wybierz problem do rozwiązania:\n"
			"1. Dyskretny problem plecakowy\n"\
			"2. Problem komiwojażera\n"
			"0. Wróć\n"
			"---> ";
		cin >> str_option;

		c_option = str_option.front();

		switch (c_option)
		{
		case '1':
			debugMenu(c_option);
			break;

		case '2':
			debugMenu(c_option);
			break;

		case '0':
			return;

		default:
			wrongOption();
		}
	}
}
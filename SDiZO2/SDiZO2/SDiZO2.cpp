// Adrian Frydmañski - 209865

#include "stdafx.h"
#include "Timer.cpp"
#include "MatGraph.h"

////////////////////////
//  globalne zmienne  //
////////////////////////

int n = 20;														// licza elementów w obiektach
Timer timer;													// timer
long long int t = 0;											// zmienna przechowuj¹ca czas
string frames[] = { "#------------------------------------#\n|                                    |\n",
"|                                    |\n#------------------------------------#\n|                                    |\n",
"|                                    |\n#------------------------------------#\n" };
string headers[] = { "|          SDiZO - projekt II        |\n|     Adrian Frydmanski - 209865     |\n",
"|    Wybrana operacja:               |\n|       Wyznaczanie minimalnego      |\n|       drzewa rozpinajacego         |\n",
"|    Wybrana operacja:               |\n|       Wyznaczanie najkrotszej      |\n|       sciezki w grafie             |\n",
"|    Wybrana operacja:               |\n|       Wyznaczanie maksymalnego     |\n|       przeplywu                    |\n" };
string options[] = { "|  Wybierz problem do rozpatrzenia:  |\n|    [1] Wyznaczenie minimalnego     |\n|        drzewa rozpinajacego        |\n|    [2] Wyznaczenie najkrotszej     |\n|        sciezki w grafie            |\n|    [3] Wyznaczenie maksymalnego    |\n|        przeplywu                   |\n|    [4] Wygeneruj graf              |\n|    [5] Wczytaj z pliku             |\n|    [6] Zapisz do pliku             |\n|    [7] Koniec                      |\n",
"|  Wybierz algorytm:                 |\n|    [1] Prima                       |\n|    [2] Kruskala                    |\n|    [3] Wroc                        |\n", // dla drzewa rozpinajacego
"|  Wybierz algorytm:                 |\n|    [1] Dijkstry                    |\n|    [2] Forda-Bellmana              |\n|    [3] Wroc                        |\n" }; //dla najkrotszej sciezki

string showTime(long long time, int n)								// podanie czasu w sekundach, a nie w taktach procesora
{
	LARGE_INTEGER lpFrequency;
	QueryPerformanceFrequency(&lpFrequency);
	long double freq = lpFrequency.QuadPart, ld_time = time;
	ld_time = ld_time / freq * 1000;
	string space = "";												// do poprawnego wyœwietlania wyników
	for (int i = log10(ld_time + 1); i < 10; i++)
		space += " ";
	string s = " " +
		to_string(ld_time) +
		" ms" + space + "|  " +
		to_string(ld_time / n) +
		" ms";
	return s;
}

void showMenu(int header, int level) {
	/*
	int option = header == 0 && level == 0 ? 0 : 1;
	option = level == 1 ? 2 : option;
	cout << frames[0] << headers[header] << frames[1] << options[option] << frames[2];
	*/
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	MatGraph * g = new MatGraph(5, 100);
	g->pokazMacierz();
	cout << endl << g->prim() << endl;
	system("pause");
	g->zapis("graf");
	return 0;

	//MatGraph * g = new MatGraph();
	g->odczyt("graf");
	g->pokazMacierz();
	
	cout << endl << g->prim() << endl;
	system("pause");
	return 0;














	int menu = -1;
	int n;
	bool loop = true;
	while (loop)
	{
		switch (menu)
		{
		case 1://///////////////////////////////////////////////////////////////////////////////// minimalne drzewo rozpinaj¹ce
		{
			system("cls");
			showMenu(menu, 0);
			cin >> menu;
			switch (menu)
			{
			case 1:	// prima
			{
				system("cls");
				showMenu(1, 1);
				cin >> n;				
			}
			case 2: // kruskala
			{
				break;
			}
			case 3: // wyjœcie
			{
				menu = -1;
				break;
			}
			}
			break;
		}
		case 2://///////////////////////////////////////////////////////////////////////////////// najkrotsza sciezka w grafie
		{
			break;
		}
		case 3://///////////////////////////////////////////////////////////////////////////////// maksymalny przep³yw
		{
			break;
		}
		case 4://///////////////////////////////////////////////////////////////////////////////// generowanie grafu
		{
			break;
		}
		case 5://///////////////////////////////////////////////////////////////////////////////// wczytaj z pliku
		{
			break;
		}
		case 6://///////////////////////////////////////////////////////////////////////////////// zapisz do pliku
		{
			break;
		}
		case 7://///////////////////////////////////////////////////////////////////////////////// wyjdŸ
		{
			return 0;
		}
		default://///////////////////////////////////////////////////////////////////////////////// poka¿ menu g³ówne
		{
			system("cls");
			showMenu(0, 0);
			cin >> menu;
			break;
		}
		}

	}
	return 0;
}


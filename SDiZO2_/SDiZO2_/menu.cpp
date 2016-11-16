#include "stdafx.h"

void menu(GrafLista *graflista, GrafMacierz *grafmacierz)
{
	int decision = 0, poczatek;
	string name = "";
	ifstream file;
	bool loop = true;
	long double time1 = 0, time2 = 0;
	MyTimer timer;
	int size, gestosc;

	while (loop)
	{
		system("cls");
		cout <<
			"#------------------------------------#\n"
			"|                                    |\n"
			"|         SDiZO - projekt II         |\n"
			"|     Adrian Frydmanski - 209865     |\n"
			"|                                    |\n"
			"#------------------------------------#\n"
			"|                                    |\n"
			"| Wybierz problem do rozpatrzenia:   |\n"
			"|  [1] - wygeneruj graf losowo       |\n"
			"|  [2] - wczytaj graf z pliku        |\n"
			"|  [3] - wy�wietl graf               |\n"
			"|  [4] - algorytm Prima              |\n"
			"|  [5] - algorytm Kruskala           |\n"
			"|  [6] - algorytm Dijkstry           |\n"
			"|  [7] - algorytm Forda-Bellmana     |\n"
			"|  [8] - autotestowanie              |\n"
			"|  [0] - wyjd�                       |\n"
			"|                                    |\n"
			"#------------------------------------#\n"
			"|                             wyb�r: | ";

		cin >> decision;
		cout <<
			"#------------------------------------#\n";
		switch (decision)
		{
		case 1:
			cout <<
				"|                                    |\n"
				"| Podaj liczb� wierzcho�k�w          | ";
			cin >> size;
			cout <<
				"|  i g�sto�� w %:                    | ";
			cin >> gestosc;
			do
			{
				cout <<
					"|                                    |\n"
					"| Skierowany?                        |\n"
					"|  [0] - tak                         |\n"
					"|  [1] - nie                         |\n"
					"|                                    |\n"
					"#------------------------------------#\n"
					"|                             wyb�r: | ";
				cin >> decision;
				cout <<
					"#------------------------------------#\n";
			} while (decision != 0 && decision != 1);
			graflista->generuj(size, gestosc, decision);
			grafmacierz->CopyGrafLista(graflista);
			break;
		case 2:
			cout <<
				"|                                    |\n"
				"| Podaj nazw� pliku:                 | ";
			cin >> name;

			file.open(name.c_str());
			if (file.good())
			{
				do{
					cout <<
						"|                                    |\n"
						"| Czy ma by� nieskierowany?          |\n"
						"|  [0] - nie, ju� jest nieskierowany |\n"
						"|        lub nie chc� by by�         |\n"
						"|  [1] - tak, zr�b go nieskierowanym |\n"
						"|                                    |\n"
						"#------------------------------------#\n"
						"|                             wyb�r: | ";
					cin >> decision;
					cout <<
						"#------------------------------------#\n";
				} while (decision != 0 && decision != 1);
				graflista->Load(&file, decision);
				grafmacierz->CopyGrafLista(graflista);
				file.close();
			}
			else
				cout <<
					"|                                    |\n"
					"| Nie mo�na odnale�� pliku!          |\n"
					"|                                    |\n"
					"#------------------------------------#\n";
			break;

		case 3:
			cout << endl;
			graflista->wyswietl();
			cout << endl;
			grafmacierz->wyswietl();
			cout << endl;
			break;
		case 4:
			MST(Prim, graflista, grafmacierz, &timer);
			break;
		case 5:
			MST(Kruskal, graflista, grafmacierz, &timer);
			break;
		case 6:
			ShortestPath(Dijkstra, graflista, grafmacierz, &timer);
			break;
		case 7:
			ShortestPath(FordBellman, graflista, grafmacierz, &timer);
			break;
		case 8:
			autotest(graflista, grafmacierz, &timer);
			break;
		case 0:
			cout << endl << endl <<
				"#------------------------------------#\n"
				"|                                    |\n"
				"|            � E G N A J             |\n"
				"|                                    |\n"
				"#------------------------------------#\n";
			loop = false;
			break;
		}
		system("pause");
	}
}
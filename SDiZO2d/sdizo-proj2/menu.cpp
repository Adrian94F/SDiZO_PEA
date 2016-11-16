#include "header.h"

void menu(ListGraph *listgraph, MatrixGraph *matrixgraph)
{
	cout <<
		"***************************\n"
		"*                         *\n"
		"*   Dawid Gracek 209929   *\n"
		"*   SDIZO - Projekt NR2   *\n"
		"*        G R A F Y        *\n"
		"*                         *\n"
		"***************************\n\n\n";
	int decision = 0, source;
	string name = "";
	ifstream file;
	bool loop = true;
	long double time1 = 0, time2 = 0;
	MyTimer timer;
	int size, density;

	while (loop)
	{
		cout <<
			"[1] - wygeneruj graf losowo\n"
			"[2] - wczytaj graf z pliku\n"
			"[3] - wy�wietl graf w reprezentacji macierzowej i listowej\n"
			"[4] - wykonaj algorytm Prima i wy�wietl zwr�cone kraw�dzie\n"
			"[5] - wykonaj algorytm Kruskala i wy�wietl zwr�cone kraw�dzie\n"
			"[6] - wykonaj algorytm Dijkstry i wy�wietl zwr�cone odleg�o�ci\n"
			"[7] - wykonaj algorytm Forda-Bellmana i wy�wietl zwr�cone odleg�o�ci\n"
			"[0] - wyjd�\n"
			"Wyb�r: ";

		cin >> decision;
		switch (decision)
		{
		case 1:
			cout << "Podaj wielko�� grafu i jego g�sto�� w %: ";
			cin >> size >> density;
			do
			{
				cout << "Czy ma by� nieskierowany?\n[0] - nie\n[1] - tak\n";
				cin >> decision;
			} while (decision != 0 && decision != 1);
			listgraph->Generate(size, density, decision);
			matrixgraph->CopyListGraph(listgraph);
			cout << "G�sto�� grafu: " << matrixgraph->Density() << "%" << endl;
			break;
		case 2:
			cout << "podaj nazw� pliku: ";
			cin >> name;

			file.open(name.c_str());
			if (file.good())
			{
				do{
					cout << "Czy zrobi� ten graf nieskierowanym?\n[0] - nie, jest ju� nieskierowany lub nie chc� aby by�.\n[1] - tak, przer�b go na nieskierowany.\n";
					cin >> decision;
				} while (decision != 0 && decision != 1);
				listgraph->Load(&file, decision);
				matrixgraph->CopyListGraph(listgraph);
				cout << "G�sto�� grafu: " << matrixgraph->Density() << "%" << endl;
				file.close();
			}
			else
				cout << "Nie mo�na odnale�� pliku!\n\n";
			break;

		case 3:
			cout << endl;
			listgraph->Display();
			cout << endl;
			matrixgraph->Display();
			cout << endl;
			break;
		case 4:
			MST(Prim, listgraph, matrixgraph, &timer);
			break;
		case 5:
			MST(Kruskal, listgraph, matrixgraph, &timer);
			break;
		case 6:
			ShortestPath(Dijkstra, listgraph, matrixgraph, &timer);
			break;
		case 7:
			ShortestPath(FordBellman, listgraph, matrixgraph, &timer);
			break;
		case 0:
			loop = false;
			break;
		}
	}
}
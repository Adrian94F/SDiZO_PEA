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
			"[3] - wyœwietl graf w reprezentacji macierzowej i listowej\n"
			"[4] - wykonaj algorytm Prima i wyœwietl zwrócone krawêdzie\n"
			"[5] - wykonaj algorytm Kruskala i wyœwietl zwrócone krawêdzie\n"
			"[6] - wykonaj algorytm Dijkstry i wyœwietl zwrócone odleg³oœci\n"
			"[7] - wykonaj algorytm Forda-Bellmana i wyœwietl zwrócone odleg³oœci\n"
			"[0] - wyjdŸ\n"
			"Wybór: ";

		cin >> decision;
		switch (decision)
		{
		case 1:
			cout << "Podaj wielkoœæ grafu i jego gêstoœæ w %: ";
			cin >> size >> density;
			do
			{
				cout << "Czy ma byæ nieskierowany?\n[0] - nie\n[1] - tak\n";
				cin >> decision;
			} while (decision != 0 && decision != 1);
			listgraph->Generate(size, density, decision);
			matrixgraph->CopyListGraph(listgraph);
			cout << "Gêstoœæ grafu: " << matrixgraph->Density() << "%" << endl;
			break;
		case 2:
			cout << "podaj nazwê pliku: ";
			cin >> name;

			file.open(name.c_str());
			if (file.good())
			{
				do{
					cout << "Czy zrobiæ ten graf nieskierowanym?\n[0] - nie, jest ju¿ nieskierowany lub nie chcê aby by³.\n[1] - tak, przerób go na nieskierowany.\n";
					cin >> decision;
				} while (decision != 0 && decision != 1);
				listgraph->Load(&file, decision);
				matrixgraph->CopyListGraph(listgraph);
				cout << "Gêstoœæ grafu: " << matrixgraph->Density() << "%" << endl;
				file.close();
			}
			else
				cout << "Nie mo¿na odnaleŸæ pliku!\n\n";
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
#include "header.h"

void MST(vector<Edge>(*func)(Graph* G), ListGraph *listgraph, MatrixGraph* matrixgraph, MyTimer *timer)
{
	int decision, size, density, avg_density = 0;
	long double time1, time2;
	do
	{
		cout << "Czy chcesz w�aczy� tryb testu? (100 powt�rze� bez wypisywania)\n[1] - tak\n[0] - nie\n";
		cin >> decision;
	} while (decision != 1 && decision != 0);

	if (decision == 0)
	{
		if (!listgraph->get_size() > 0 || !matrixgraph->get_size() > 0)
			return;
		func(listgraph);
		func(matrixgraph);
		DisplayEdge(func(listgraph));
	}
	else
	{
		time1 = 0;
		time2 = 0;
		cout << "Podaj wielko�� grafu i jego g�sto�� w %: ";
		cin >> size >> density;
		for (int i = 0; i < 100; i++)
		{
			listgraph->Generate(size, density, true);
			matrixgraph->CopyListGraph(listgraph);
			avg_density += matrixgraph->Density();
			timer->Start();
			func(listgraph);
			time1 += timer->End();
			timer->Start();
			func(matrixgraph);
			time2 += timer->End();
		}
		avg_density /= 100;
		time1 /= 100;
		time2 /= 100;
		cout << "\nG�sto�� grafu: " << avg_density << "%" << endl;
		cout << "�redni czas dla reprezentacji listowej: " << time1 << " ms" << endl;
		cout << "�redni czas dla reprezentacji macierzowej: " << time2 << " ms" << endl;
	}
	cout << endl; cout << endl;
}
void ShortestPath(vector<int>(*func)(Graph* G, int source, int dest), ListGraph *listgraph, MatrixGraph* matrixgraph, MyTimer *timer)
{
	int decision, size, density, source, dest, avg_density = 0;
	long double time1, time2;
	do
	{
		cout << "Czy chcesz w�aczy� tryb testu? (100 powt�rze� bez wypisywania)\n[1] - tak\n[0] - nie\n";
		cin >> decision;
	} while (decision != 1 && decision != 0);

	cout << "Podaj pocz�tek i koniec mierzonej odleg�o�ci: ";
	cin >> source >> dest;

	if (decision == 0)
	{
		if (!listgraph->get_size() > 0 || !matrixgraph->get_size() > 0)
			return;
		func(listgraph, source, dest);
		func(matrixgraph, source, dest);
		DisplayVec(func(listgraph, source, dest), dest);
		cout << endl; cout << endl;
	}
	else
	{
		cout << "Podaj wielko�� grafu i jego g�sto�� w %: ";
		cin >> size >> density;

		time1 = 0;
		time2 = 0;
		for (int i = 0; i < 100; i++)
		{
			listgraph->Generate(size, density, false);
			matrixgraph->CopyListGraph(listgraph);
			avg_density += matrixgraph->Density();

			timer->Start();
			func(listgraph, source, dest);
			time1 += timer->End();
			timer->Start();
			func(matrixgraph, source, dest);
			time2 += timer->End();
		}
		time1 /= 100;
		time2 /= 100;
		avg_density /= 100;
		cout << "\n�rednia g�sto�� grafu: " << avg_density << "%" << endl;
		cout << "�redni czas dla reprezentacji listowej: " << time1 << " ms" << endl;
		cout << "�redni czas dla reprezentacji macierzowej: " << time2 << " ms" << endl;
	}
	cout << endl; cout << endl;
}
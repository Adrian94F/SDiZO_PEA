#include "stdafx.h"

void autotest(GrafLista *graflista, GrafMacierz* grafmacierz, MyTimer *timer)
{
	cout << 
		"|                                    |\n"
		"| W wynikach œrednie czasy operacji  |\n"
		"| dla 100 powtórzeñ:                 |\n"
		"|                                    |\n";
	int gestosci[] = { 25, 50, 75, 99 };
	int gest = 4;
	int rozmiary[] = { 10, 20, 30, 40, 50 };
	int rozm = 5;
	int size, gestosc;
	long double time1, time2;
	for (int i = 0; i < rozm; i++)
	{
		cout << "|  testy dla " << rozmiary[i] << " wierzcholkow:        |\n";
		for (int j = 0; j < gest; j++)
		{
			cout << "|   gêstoœæ grafu: " << gestosci[j] << "%               |\n";
			cout << "|      minimalne drzewo rozpinaj¹ce: |\n";
			cout << "|         Prim:                      |\n";

			time1 = 0;
			time2 = 0;
			size = rozmiary[i];
			gestosc = gestosci[j];
			for (int k = 0; k < 100; k++)
			{
				graflista->generuj(size, gestosc, true);
				grafmacierz->CopyGrafLista(graflista);
				timer->Start();
				Prim(graflista);
				time1 += timer->End();
				timer->Start();
				Prim(grafmacierz);
				time2 += timer->End();
			}
			time1 /= 100;
			time2 /= 100;
			cout << "|            lista: " << setw(13) << time1 << " ms |" << endl;
			cout << "|            macierz: " << setw(11) << time2 << " ms |" << endl;

			cout << "|         Kruskal:                   |\n";

			time1 = 0;
			time2 = 0;
			size = rozmiary[i];
			gestosc = gestosci[j];
			for (int k = 0; k < 100; k++)
			{
				graflista->generuj(size, gestosc, true);
				grafmacierz->CopyGrafLista(graflista);
				timer->Start();
				Kruskal(graflista);
				time1 += timer->End();
				timer->Start();
				Kruskal(grafmacierz);
				time2 += timer->End();
			}
			time1 /= 100;
			time2 /= 100;
			cout << "|            lista: " << setw(13) << time1 << " ms |" << endl;
			cout << "|            macierz: " << setw(11) << time2 << " ms |" << endl;

			cout << "|      najkrótsza œcie¿ka w grafie:  |\n";
			cout << "|         Djikstra:                  |\n";

			time1 = 0;
			time2 = 0;
			size = rozmiary[i];
			gestosc = gestosci[j];
			for (int k = 0; k < 100; k++)
			{
				graflista->generuj(size, gestosc, false);
				grafmacierz->CopyGrafLista(graflista);

				timer->Start();
				Dijkstra(graflista, rand() % rozmiary[i], rand() % rozmiary[i]);
				time1 += timer->End();
				timer->Start();
				Dijkstra(grafmacierz, rand() % rozmiary[i], rand() % rozmiary[i]);
				time2 += timer->End();
			}
			time1 /= 100;
			time2 /= 100;
			cout << "|            lista: " << setw(13) << time1 << " ms |" << endl;
			cout << "|            macierz: " << setw(11) << time2 << " ms |" << endl;

			cout << "|        Ford-Bellman:               |\n";
			
			time1 = 0;
			time2 = 0;
			size = rozmiary[i];
			gestosc = gestosci[j];
			for (int k = 0; k < 100; k++)
			{
				graflista->generuj(size, gestosc, false);
				grafmacierz->CopyGrafLista(graflista);

				timer->Start();
				FordBellman(graflista, rand() % rozmiary[i], rand() % rozmiary[i]);
				time1 += timer->End();
				timer->Start();
				FordBellman(grafmacierz, rand() % rozmiary[i], rand() % rozmiary[i]);
				time2 += timer->End();
			}
			time1 /= 100;
			time2 /= 100;
			cout << "|            lista: " << setw(13) << time1 << " ms |" << endl;
			cout << "|            macierz: " << setw(11) << time2 << " ms |" << endl;

			cout << "|                                    |\n";
		}
	}
	cout <<
		"#------------------------------------#\n";
}

void MST(vector<Krawedz>(*func)(Graf* G), GrafLista *graflista, GrafMacierz* grafmacierz, MyTimer *timer)
{
	int decision, size, gestosc, avg_gestosc = 0;
	long double time1, time2;
	do
	{
		cout << 
			"|                                    |\n"
			"| Test dla 100 powtorzen?            |\n"
			"|  [0] - nie                         |\n"
			"|  [1] - tak                         |\n"
			"|                                    |\n"
			"#------------------------------------#\n"
			"|                             wybór: | ";
		cin >> decision;
		cout <<
			"#------------------------------------#\n";
	} while (decision != 1 && decision != 0);

	if (decision == 0)
	{
		if (!graflista->getRozmiar() > 0 || !grafmacierz->getRozmiar() > 0)
			return;
		wyswietlKrawedz(func(graflista));
		wyswietlKrawedz(func(grafmacierz));
	}
	else
	{
		time1 = 0;
		time2 = 0;
		cout <<
			"|                                    |\n"
			"| Podaj liczbê wierzcho³ków          | ";
		cin >> size;
		cout <<
			"|  i gêstoœæ w %:                    | ";
		cin >> gestosc;
		for (int i = 0; i < 100; i++)
		{
			graflista->generuj(size, gestosc, true);
			grafmacierz->CopyGrafLista(graflista);
			avg_gestosc += grafmacierz->gestosc();
			timer->Start();
			func(graflista);
			time1 += timer->End();
			timer->Start();
			func(grafmacierz);
			time2 += timer->End();
		}
		avg_gestosc /= 100;
		time1 /= 100;
		time2 /= 100;
		cout <<
			"|                                    |\n"
			"| Œredni czas dla listy:             |\n" 
			"| " << setw(32) << time1 << "ms |\n"
			"| Œredni czas dla macierzy:          |\n"
			"| " << setw(32) << time2 << "ms |\n" 
			"|                                    |\n"
			"#------------------------------------#\n" 
			<< endl;
	}
	cout << endl; cout << endl;
}
void ShortestPath(vector<int>(*func)(Graf* G, int poczatek, int koniec), GrafLista *graflista, GrafMacierz* grafmacierz, MyTimer *timer)
{
	int decision, size, gestosc, poczatek, koniec, avg_gestosc = 0;
	long double time1, time2;
	do
	{
		cout <<
			"|                                    |\n"
			"| Czy chcesz w³¹czyæ testowanie?     |\n"
			"|  (100 powtórzeñ bez wypisywania)   |\n"
			"|  [0] - nie                         |\n"
			"|  [1] - tak                         |\n"
			"|                                    |\n"
			"#------------------------------------#\n"
			"|                             wybór: | ";
		cin >> decision;
		cout <<
			"#------------------------------------#\n";
	} while (decision != 1 && decision != 0);

	cout <<
		"|                                    |\n"
		"| Podaj pocz¹tek œcie¿ki:            | ";
	cin >> poczatek;
	cout << 
		"|  i jej koniec:                     | "; 
	cin>> koniec;
	cout <<
		"|                                    |\n"
		"#------------------------------------#\n";
	if (decision == 0)
	{
		if (!graflista->getRozmiar() > 0 || !grafmacierz->getRozmiar() > 0)
			return;
		wyswietlVec(func(graflista, poczatek, koniec), koniec);
		cout << '*';
		wyswietlVec(func(grafmacierz, poczatek, koniec), koniec);
		cout << endl; cout << endl;
	}
	else
	{
		cout <<
			"|                                    |\n"
			"| Podaj liczbê wierzcho³ków          | ";
		cin >> size;
		cout <<
			"|  i gêstoœæ w %:                    | ";
		cin >> gestosc;

		time1 = 0;
		time2 = 0;
		for (int i = 0; i < 100; i++)
		{
			graflista->generuj(size, gestosc, false);
			grafmacierz->CopyGrafLista(graflista);
			avg_gestosc += grafmacierz->gestosc();

			timer->Start();
			func(graflista, poczatek, koniec);
			time1 += timer->End();
			timer->Start();
			func(grafmacierz, poczatek, koniec);
			time2 += timer->End();
		}
		time1 /= 100;
		time2 /= 100;
		avg_gestosc /= 100;
		cout <<
			"|                                    |\n"
			"| Œredni czas dla listy:             |\n"
			"| " << setw(32) << time1 << "ms |\n"
			"| Œredni czas dla macierzy:          |\n"
			"| " << setw(32) << time2 << "ms |\n"
			"|                                    |\n"
			"#------------------------------------#\n"
			<< endl;
	}
	cout << endl; cout << endl;
}
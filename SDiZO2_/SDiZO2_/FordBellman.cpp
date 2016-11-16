#include "stdafx.h"

vector<int> FordBellman(Graf* G, int poczatek, int koniec)
{
	int n = G->getRozmiar();
	vector<int> odleglosc(n);
	for (int i = 0; i < n; i++)
	{
		if (i == poczatek)
			odleglosc[i] = 0;
		else
			odleglosc[i] = -1;
	}
	vector<Krawedz> edges = G->krawedzie();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < edges.size(); j++)
			if (odleglosc[edges[j].poczatek] != -1 && (odleglosc[edges[j].koniec] == -1 || odleglosc[edges[j].poczatek] + edges[j].waga < odleglosc[edges[j].koniec]))
				odleglosc[edges[j].koniec] = odleglosc[edges[j].poczatek] + edges[j].waga;
	return odleglosc;
}
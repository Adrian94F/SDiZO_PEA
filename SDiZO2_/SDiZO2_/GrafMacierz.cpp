#include "stdafx.h"

void GrafMacierz::generuj(int size, int gestosc, bool mst)
{
	int licznik = 0;
	odwiedzone.resize(size);
	wierzcholki.resize(size);

	while (licznik != size)
	{
		licznik = 0;
		for (int i = 0; i < size; i++)
		{
			odwiedzone[i] = false;
			wierzcholki[i].clear();
			wierzcholki[i].resize(size, 0);
		}

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (wierzcholki[i][j] == 0 && rand() % 101 <= gestosc)
				{
					wierzcholki[i][j] = rand();
					if (mst)
						wierzcholki[j][i] = wierzcholki[i][j];
				}
		DFS(0);
		for (int i = 0; i < size; i++)
			if (odwiedzone[i] == true)
				licznik++;
	}
}

void GrafMacierz::CopyGrafLista(GrafLista *graflista)
{
	wierzcholki.clear();
	wierzcholki.resize(graflista->get_wierzcholki().size());
	for (int i = 0; i < graflista->get_wierzcholki().size(); i++)
	{
		wierzcholki[i].clear();
		wierzcholki[i].resize(graflista->get_wierzcholki().size());
		for (int j = 0; j < graflista->get_wierzcholki()[i].size(); j++)
			wierzcholki[i][graflista->get_wierzcholki()[i][j].second] = graflista->get_wierzcholki()[i][j].first;
	}
}

void GrafMacierz::wyswietl()
{
	cout << "GrafMacierz: \n";
	for (int i = 0; i < wierzcholki.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < wierzcholki[i].size(); j++)
			cout << " " << wierzcholki[i][j];
		cout << "\n";
	}
}

int GrafMacierz::gestosc()
{
	if (wierzcholki.size()>0)
	{
		int procent = 0;
		for (int i = 0; i < wierzcholki.size(); i++)
			for (int j = 0; j < wierzcholki.size(); j++)
				if (wierzcholki[i][j] == NULL)
					procent++;
		return 100 - procent * 100 / (wierzcholki.size()*wierzcholki.size());
	}
	else
		return 0;
}

int GrafMacierz::getRozmiar()
{
	return wierzcholki.size();
}

int GrafMacierz::wagaKrawedzi(int wierzcholek1, int wierzcholek2)
{
	return wierzcholki[wierzcholek1][wierzcholek2];
}

vector<pair<int, int>> GrafMacierz::krawedzieWierzcholka(int nrWierzcholka)
{
	vector<pair<int, int>> temp;
	for (int i = 0; i < wierzcholki[nrWierzcholka].size(); i++)
	{
		if (wierzcholki[nrWierzcholka][i] != NULL)
			temp.push_back(make_pair(wierzcholki[nrWierzcholka][i], i));
	}
	return temp;
}

void GrafMacierz::DFS(int wierzcholek)
{
	odwiedzone[wierzcholek] = true;
	for (int i = 0; i < wierzcholki.size(); i++) //petla po wierzcho³kach
		if ((wierzcholki[wierzcholek][i] >0) && !odwiedzone[i]) // jeœli wierzch. >0 i nieodwiedzony...
			DFS(i);
}

vector<Krawedz> GrafMacierz::krawedzie()
{
	vector<Krawedz> temp;
	for (int i = 0; i < wierzcholki.size(); i++)
		for (int j = 0; j < wierzcholki.size(); j++)
			if (wierzcholki[i][j] != NULL)
				temp.push_back(Krawedz(i, j, wierzcholki[i][j]));
	return temp;
}
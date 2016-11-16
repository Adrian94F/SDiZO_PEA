#include "stdafx.h"

void GrafLista::generuj(int size, int density, bool mst)
{
	GrafLista graf2;
	int count = 0;
	while (count != size)
	{
		count = 0;
		wierzcholki.clear();
		wierzcholki.resize(size);
		graf2.wierzcholki.clear();
		graf2.wierzcholki.resize(size);

		for (int i = 0; i < size; i++)
		{
			if (mst)
			{
				for (int j = i + 1; j < size; j++)
				{
					if (i != j && rand() % 101 <= (mst ? density / 2 : density))
					{
						wierzcholki[i].push_back(make_pair(rand(), j));
						wierzcholki[j].push_back(make_pair(wierzcholki[i][wierzcholki[i].size() - 1].first, i));
					}
				}
			}
			else
			{
				for (int j = 0; j < size; j++)
				{
					if (i != j && rand() % 101 <= (mst ? density / 2 : density))
					{
						wierzcholki[i].push_back(make_pair(rand(), j));
						graf2.wierzcholki[i].push_back(make_pair(wierzcholki[i][wierzcholki[i].size() - 1].first, j));
						graf2.wierzcholki[j].push_back(make_pair(wierzcholki[i][wierzcholki[i].size() - 1].first, i));
					}
				}
			}
		}
		if (mst)
		{
			odwiedzone.clear();
			odwiedzone.resize(size, false);
			DFS(0);
			for (int i = 0; i < size; i++)
			{
				if (odwiedzone[i] == true)
					count++;
			}
		}
		else
		{
			graf2.odwiedzone.clear();
			graf2.odwiedzone.resize(size, false);
			graf2.DFS(0);
			for (int i = 0; i < size; i++)
			{
				if (graf2.odwiedzone[i] == true)
					count++;
			}
		}
	}
}
void GrafLista::wyswietl()
{
	cout << "GrafLista: \n";
	for (int i = 0; i < wierzcholki.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < wierzcholki[i].size(); j++)
		{
			cout << wierzcholki[i][j].first << ": " << wierzcholki[i][j].second << ", ";
		}
		cout << "\n";
	}
}

void GrafLista::Load(ifstream *file, bool make_undirected)
{
	GrafLista graf2;
	wierzcholki.clear();
	int edges, size, temp, source, dest, weight;
	*file >> edges;
	*file >> size;
	wierzcholki.resize(size);
	graf2.wierzcholki.resize(size);
	for (int i = 0; i < edges; i++)
	{
		*file >> source;			//odczytanie pocz¹tku krawêdzi...
		*file >> dest;				// ...koñca...
		*file >> weight;			// ...i wagi
		wierzcholki[source].push_back(make_pair(weight, dest)); //dodajemy
		if (make_undirected)
		{
			wierzcholki[dest].push_back(make_pair(weight, source)); // jesli nieskoerowany, to tez dodajemy do docelowego
		}
		else
		{
			graf2.wierzcholki[source].push_back(make_pair(weight, dest));
			graf2.wierzcholki[dest].push_back(make_pair(weight, source));
		}
	}
	int count = 0;
	if (make_undirected)
	{
		odwiedzone.clear();
		odwiedzone.resize(size, false);
		DFS(0);
		for (int i = 0; i < size; i++)
		{
			if (odwiedzone[i] == true)
				count++;
		}
	}
	else
	{
		graf2.odwiedzone.clear();
		graf2.odwiedzone.resize(size, false);
		graf2.DFS(0);
		for (int i = 0; i < size; i++)
		{
			if (graf2.odwiedzone[i] == true)
				count++;
		}
	}
	if (count != size)
		cout << "\n         Graf jest niespójny!!!\n";
}


int GrafLista::wagaKrawedzi(int node1_index, int node2_index)
{
	for (int i = 0; i < wierzcholki[node1_index].size(); i++)
	{
		if (wierzcholki[node1_index][i].second == node2_index)
			return wierzcholki[node1_index][i].first;
	}
	return NULL;
}
int GrafLista::getRozmiar()
{
	return wierzcholki.size();
}

vector<Krawedz> GrafLista::krawedzie()
{
	vector<Krawedz> temp;

	for (int i = 0; i < wierzcholki.size(); i++)
	{
		for (int j = 0; j < wierzcholki[i].size(); j++)
			temp.push_back(Krawedz(i, wierzcholki[i][j].second, wierzcholki[i][j].first));
	}
	return temp;
}

vector<pair<int, int>> GrafLista::krawedzieWierzcholka(int node_index)
{
	vector<pair<int, int>> temp;
	for (int i = 0; i < wierzcholki[node_index].size(); i++)
	{
		temp.push_back(make_pair(wierzcholki[node_index][i].first, wierzcholki[node_index][i].second));
	}
	return temp;
}

void GrafLista::DFS(int wierzcholek)
{
	odwiedzone[wierzcholek] = true;
	for (int i = 0; i < wierzcholki[wierzcholek].size(); i++) // pêtla po wierzcho³kach
		if (!odwiedzone[wierzcholki[wierzcholek][i].second])
			DFS(wierzcholki[wierzcholek][i].second);
}

vector<vector<pair<int, int>>> GrafLista::get_wierzcholki()
{
	return wierzcholki;
}
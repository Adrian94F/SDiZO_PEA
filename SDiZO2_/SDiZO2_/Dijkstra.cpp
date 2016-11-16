#include "stdafx.h"

vector<int> Dijkstra(Graf* G, int poczatek, int koniec)
{
	int n = G->getRozmiar();
	vector<int> rozmiar(n);
	for (int i = 0; i < n; i++)
		rozmiar[i] = -1;
	priority_queue<pair<int, int> > q;
	q.push(make_pair(0, poczatek));
	while (!q.empty())
	{
		pair<int, int> x = q.top();
		q.pop();
		if (!(rozmiar[x.second] == -1))
			continue;
		rozmiar[x.second] = -x.first;
		if (x.second == koniec)
			break;
		vector<pair<int, int> > sasiedzi = G->krawedzieWierzcholka(x.second);
		for (int i = 0; i < sasiedzi.size(); i++)
		{
			pair<int, int> y = sasiedzi[i];
			if (rozmiar[y.second] == -1)
				q.push(make_pair(x.first - y.first, y.second));
		}
	}
	return rozmiar;
}
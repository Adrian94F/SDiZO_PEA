#include "stdafx.h"

vector<Krawedz> Prim(Graf* G)
{
	int n = G->getRozmiar();
	int poczatek = 0;
	vector<Krawedz> MST;
	priority_queue<Krawedz, vector<Krawedz>, porownajKrawedzie> q;
	vector<bool> odwiedzone;
	odwiedzone.resize(n);
	odwiedzone[poczatek] = true;
	vector<pair<int, int> > tmp = G->krawedzieWierzcholka(poczatek);
	for (int i = 0; i < tmp.size(); i++)
	{
		Krawedz e = Krawedz(poczatek, tmp[i].second, tmp[i].first);
		q.push(e);
	}
	while (--n)
	{
		while (!q.empty() && odwiedzone[q.top().koniec])
			q.pop();
		if (q.empty())
			break;
		Krawedz x = q.top();
		MST.push_back(x);
		odwiedzone[x.koniec] = true;
		tmp = G->krawedzieWierzcholka(x.koniec);
		for (int i = 0; i < tmp.size(); i++)
			if (!odwiedzone[tmp[i].second])
			{
				Krawedz e = Krawedz(x.koniec, tmp[i].second, tmp[i].first);
				q.push(e);
			}
	}
	return MST;
}
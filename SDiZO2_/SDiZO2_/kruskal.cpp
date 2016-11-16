#include "stdafx.h"

Set::Set(int n)
{
	zawartosc.resize(n);
	for (int i = 0; i < n; i++)
		zawartosc[i] = i;
}

void Set::zlacz(int x, int y)
{
	int parentx = this->znajdz(x);
	int parenty = this->znajdz(y);
	zawartosc[parenty] = parentx;
}

int Set::znajdz(int x)
{
	int rodzic;
	if (zawartosc[x] != x)
	{
		rodzic = this->znajdz(zawartosc[x]);
		zawartosc[x] = rodzic;
	}
	else
		rodzic = x;
	return rodzic;
}

porownajKrawedzie::porownajKrawedzie(bool rev)
{
	odwrotne = rev;
}

bool porownajKrawedzie::operator() (const Krawedz& x, const Krawedz& y) const
{
	if (x.waga == y.waga)
		if (x.poczatek == y.poczatek)
			if (odwrotne) 
				return x.koniec > y.koniec;
			else 
				return x.koniec < y.koniec;
		else
			if (odwrotne) 
				return x.poczatek > y.poczatek;
			else 
				return x.poczatek < y.poczatek;
	else
		if (odwrotne) 
			return x.waga > y.waga;
		else 
			return x.waga < y.waga;
}

vector<Krawedz> Kruskal(Graf* G)
{
	vector<Krawedz> MST;
	vector<Krawedz> krawedzie = G->krawedzie();
	Set wierzcholki(G->getRozmiar());
	sort(krawedzie.begin(), krawedzie.end(), porownajKrawedzie(false));
	for (int i = 0; i < krawedzie.size(); i++)
	{
		Krawedz e = krawedzie[i];
		if (wierzcholki.znajdz(e.poczatek) != wierzcholki.znajdz(e.koniec))
		{
			MST.push_back(e);
			wierzcholki.zlacz(e.poczatek, e.koniec);
		}
	}
	return MST;
}
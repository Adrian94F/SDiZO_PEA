#include <vector>
#include <iostream>
#include <time.h>
#include <queue>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

class Krawedz // krawêdŸ grafu
{
public:
	int poczatek;
	int koniec;
	int waga;
	Krawedz(int poczatek, int koniec, int waga);
};

class Graf // graf - ogólnie
{
public:
	vector<bool> odwiedzone;
	virtual void generuj(int size, int gestosc, bool mst) = 0; // generator grafu - je¿eli mst jest true, to graf zostanie wygenerowany jako nieskierowany.
	virtual void wyswietl() = 0;
	virtual int wagaKrawedzi(int wierzcholek1, int wierzcholek2) = 0; // zwraca wage krawedzi
	virtual vector<pair<int, int>> krawedzieWierzcholka(int nrWierzcholka) = 0; // zwraca pary {waga, sasiad} dla danego wierzcholka
	virtual vector<Krawedz> krawedzie() = 0; // wszystkie krawedzie
	virtual int getRozmiar() = 0;
	virtual void DFS(int wierzcholek) = 0; // sprawdzanie spojnosci dla nieskierowanego
};

class GrafLista : public Graf // implementacja listowa
{
	vector<vector<pair<int, int>>> wierzcholki;
public:
	void generuj(int size, int gestosc, bool mst);
	void wyswietl();
	int wagaKrawedzi(int wierzcholek1, int wierzcholek2);
	vector<pair<int, int>> krawedzieWierzcholka(int nrWierzcholka);
	vector<Krawedz> krawedzie();
	int getRozmiar();
	void DFS(int wierzcholek);
	vector<vector<pair<int, int>>> get_wierzcholki();
	void Load(ifstream *file, bool make_undirected);
};

class GrafMacierz : public Graf // implementacja macierzowa
{
	vector<vector<int>> wierzcholki;
public:
	void generuj(int size, int gestosc, bool mst);
	void wyswietl();
	void DFS(int wierzcholek);
	void CopyGrafLista(GrafLista *graflista); // skopiowanie grafu z macierzy do listy
	int wagaKrawedzi(int wierzcholek1, int wierzcholek2); // jesli nie ma, 0
	int gestosc();
	int getRozmiar();
	vector<pair<int, int>> krawedzieWierzcholka(int nrWierzcholka);
	vector<Krawedz> krawedzie();
};

class Set // zbiory wierzcholkow - do Kruskala
{
	vector<int> zawartosc;
public:
	Set(int n);
	int znajdz(int x);
	void zlacz(int x, int y); // ³¹czy 2 zbiory z 2 wierzcho³ków
};

class MyTimer // licznik czasu
{
	LARGE_INTEGER start, stop, lpFrequency;
	long double time, freq;
public:
	void Start();
	long double End();
};

class porownajKrawedzie // porównywacz krawêdzi
{
	bool odwrotne = true;
public:
	porownajKrawedzie(bool rev = true);
	bool operator() (const Krawedz& x, const Krawedz& y) const;
};

vector<Krawedz> Kruskal(Graf* G);
vector<Krawedz> Prim(Graf* G);
vector<int> Dijkstra(Graf* G, int poczatek, int koniec);
vector<int> FordBellman(Graf* G, int poczatek, int koniec);

void wyswietlVec(vector<int>input, int koniec);
void wyswietlKrawedz(vector<Krawedz> input);
void DFS(int wierzcholek);
void menu(GrafLista *graflista, GrafMacierz *grafmacierz);
void autotest(GrafLista *graflista, GrafMacierz* grafmacierz, MyTimer *timer);
void MST(vector<Krawedz>(*func)(Graf* G), GrafLista *graflista, GrafMacierz* grafmacierz, MyTimer *timer); // szukanie minimalnego drzewa rozpinajacego
void ShortestPath(vector<int>(*func)(Graf* G, int poczatek, int koniec), GrafLista *graflista, GrafMacierz* grafmacierz, MyTimer *timer); // szukanie najkrotszej sciezki

#include <vector>
#include <iostream>
#include <time.h>
#include <queue>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

/* Reprezentuje kraw�d� grafu */
class Edge
{
public:
	int source;
	int dest;
	int weight;
	Edge(int source, int dest, int weight);
};
/* Reprezentuje graf */
class Graph{
public:
	vector<bool> visited;
	/*
	Metoda generuj�ca graf. Je�eli mst jest true, to graf zostanie wygenerowany jako nieskierowany.
	*/
	virtual void Generate(int size, int density, bool mst)=0;
	virtual void Display() = 0;
	/*
	Metoda zwracaj�ca wag� istniej�cej kraw�dzi. Je�eli nie istnieje to zwraca 0.
	*/
	virtual int DoesEdgeExist(int node1_index, int node2_index)=0;
	/*
	Metoda zwracaj�ca kraw�dzie wierzcho�ka (waga, cel).
	*/
	virtual vector<pair<int, int>> EdgesOf(int node_index)=0;
	/*
	Metoda zwracaj�ca wszystkie kraw�dzie grafu(�r�d�o, cel, waga).
	*/
	virtual vector<Edge> Edges()=0;
	virtual int get_size() = 0;
	/*
	Metoda sprawdzaj�ca sp�jno�� grafu nieskierowanego.
	*/
	virtual void DFS(int node) = 0;
};
/* Reprezentacja listowa grafu */
class ListGraph : public Graph{
	vector<vector<pair<int, int>>> nodes;
public:
	void Generate(int size, int density, bool mst);
	void Display();
	int DoesEdgeExist(int node1_index, int node2_index);
	vector<pair<int, int>> EdgesOf(int node_index);
	vector<Edge> Edges();
	int get_size();
	void DFS(int node);
	vector<vector<pair<int, int>>> get_nodes();
	void Load(ifstream *file, bool make_undirected);
};
/* Reprezentacja macierzowa grafu */
class MatrixGraph : public Graph{
	vector<vector<int>> nodes;
public:
	/* OBSOLETE */
	void Generate(int size, int density, bool mst);
	
	void Display();
	void DFS(int node);
	/* Tworzy graf na podstawie grafu w reprezentacji listowej */
	void CopyListGraph(ListGraph *listgraph);

	int DoesEdgeExist(int node1_index, int node2_index);
	/* Metoda zwracaj�ca rzeczywist� g�sto�� grafu */
	int Density();
	int get_size();

	vector<pair<int, int>> EdgesOf(int node_index);
	vector<Edge> Edges();
};
/*
Zbiory po��czonych wierzcho�k�w.
Klasa potrzebna do algorymtu Kruskala
*/
class Set
{
	vector<int> contents;
public:
	/* Konstruktor jednoparametrowy */
	Set(int n);
	/* Zwraca reprezentanta zbioru wierzcho�ka */
	int find(int x);
	/* ��czy 2 zbiory z 2 wierzcho�k�w*/
	void unite(int x, int y);
};
/* S�u�y do mierzenia czasu */
class MyTimer{
	LARGE_INTEGER start, stop, lpFrequency;
	long double time, freq;
public:
	void Start();
	long double End();
};
/* Klasa komparatora kraw�dzi */
class compareEdges
{
	bool reverse = true;
public:
	compareEdges(bool rev = true);
	bool operator() (const Edge& x, const Edge& y) const;
};
/// Algorytmy ///
vector<Edge> Kruskal(Graph* G);
vector<Edge> Prim(Graph* G);
vector<int> Dijkstra(Graph* G, int source, int dest);
vector<int> FordBellman(Graph* G, int source, int dest);

/// Funkcje ////
void DisplayVec(vector<int>input, int dest);
void DisplayEdge(vector<Edge> input);
void DFS(int node);
void menu(ListGraph *listgraph, MatrixGraph *matrixgraph);
/*
Funkcja wywo�uj�ca algorytm znajdowania minimalnego drzewa spinaj�cego 
*/
void MST(vector<Edge>(*func)(Graph* G), ListGraph *listgraph, MatrixGraph* matrixgraph, MyTimer *timer);

/*
Funkcja wywo�uj�ca algorytm znajdowania najkr�tszej �cie�ki w grafie
*/
void ShortestPath(vector<int>(*func)(Graph* G, int source, int dest), ListGraph *listgraph, MatrixGraph* matrixgraph, MyTimer *timer);
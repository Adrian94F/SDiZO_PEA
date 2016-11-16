#ifndef HEADER
#define HEADER
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include <queue>
#include <limits>
#include <boost\smart_ptr.hpp>
#include <stack>
#include <thread>
#include <GL\freeglut.h>
#include <random>

using namespace std;

typedef float float3[3];

/* Reprezentuje krawêdŸ grafu */
class Edge
{
public:
	int source;
	int dest;
	float weight;
	Edge(int source, int dest, float weight);
};
/* Reprezentuje przedmiot listy */
class Item								//klasa Item reprezentuj¹ca element listy
{
public:
	float value;
	Item* next;
	Item();								//konstruktor bezparametrowy
};
/* Reprezentacja macierzowa grafu */
class MatrixGraph {
	vector<bool> visited;																			// tablica odwiedzonych
protected:
	vector<vector<float>> nodes;																	// wierzcho³ki grafu
public:

	void Generate(int N);																			// generacja grafu
	void Load(ifstream &file);																		// wczytanie grafu z pliku
	void LoadTSP(ifstream &file);																		// wczytanie grafu z pliku
	void LoadATSP(ifstream &file);																		// wczytanie grafu z pliku
	void Display();																					// wyœwietlenie grafu
	//void DFS(int node, MyList *wynik);																// DFS na grafie
	float DoesEdgeExist(int node1_index, int node2_index);											// zwraca czy krawêdŸ pomiêdzy wierzcho³kami istnieje
	/* Metoda zwracaj¹ca rzeczywist¹ gêstoœæ grafu */
	int Density();
	int GetSize();																					// zwraca d³ugoœæ boku macierzy
	vector<Edge> EdgesOf(int node_index);															// zwraca krawêdzie danego wierzcho³ka
	vector<Edge> Edges();																			// zwraca wszystkie krawêdzie w grafie
	float CheckMaxNodeValue();
	vector<vector<float>> GetNodes();
	void DisplayMatrix();
	float GetValueOf(unsigned char node1, unsigned char node2);
};
/* S³u¿y do mierzenia czasu */
class MyTimer {
	LARGE_INTEGER start, stop, lpFrequency;
	long double time, freq;
public:
	void Start();
	long double End();
};
typedef boost::shared_ptr<vector<pair<unsigned char, unsigned char>>> EdgePtr;
class BnbMatrix {
	vector<vector<float>> nodes;
	EdgePtr edges;
	vector<float> minrow;
	vector<float> mincol;
	vector<unsigned char> rowid;
	vector<unsigned char> colid;
	pair<unsigned char, unsigned char> minpos;
	float limit;
	float number;
	void Reduce();
	void FindZero();
	void CutOut();
	void InsertInf();
	void InsertInfRev();
public:
	BnbMatrix(MatrixGraph _graph);
	BnbMatrix(BnbMatrix &matrix, bool cutout, float _number);
	unsigned char size;
	pair<unsigned char, unsigned char> GetMinPos();
	vector<vector<float>> GetNodes();
	vector<unsigned char> GetRowID();
	vector<unsigned char> GetColID();
	float GetLimit();
	pair<unsigned char, unsigned char> EdgeOf(unsigned char x, unsigned char y);
	EdgePtr GetEdges();
	float GetNumber();
	void Clean();
};
typedef pair<float, BnbMatrix*> P;
struct Order
{
	bool operator()(P const& a, P const& b) const
	{
		return a.first > b.first;
	}
};
void KomiwojazerLoad(ifstream &file, MatrixGraph &graph, string extension);						// wczytanie problemu komiwoja¿era z pliku

int *KomiwojazerBrute(MatrixGraph graph);														// algorytm zupe³ny 
int *KomiwojazerSimulatedAnnealing(MatrixGraph graph, double Tmin, double Tmax, double a);		// algorytm symulowanego wy¿arzania
vector<unsigned char> KomiwojazerBranchAndBound(MatrixGraph graph);									// algorytm zupe³ny 
vector<unsigned char> KomiwojazerTabuSearch(MatrixGraph graph, unsigned tau);
vector<unsigned char> KomiwojazerGenetic(MatrixGraph graph, unsigned populationsize, unsigned crossChance, unsigned mutationChance, bool debug);


vector<unsigned char> KomiwojazerInvert(vector<unsigned char> perm, unsigned char x, unsigned char y);
unsigned int CheckMin(vector<vector<float>> matrix, vector<unsigned char> perm);
bool CheckPairInTabu(queue<pair<unsigned char, unsigned char>> fifo, unsigned char x, unsigned char y);
void KomiwojazerTest(long double &timer, MatrixGraph graph);									// tryb testu dla komiwoja¿era
float KomiwojazerGetWeight(int komi[], MatrixGraph graph);
float KomiwojazerGetWeight(vector<unsigned char>komi, MatrixGraph graph);
void KomiwojazerDisplayEdges(int komi[], MatrixGraph graph);									// wyœwietlanie wyniku algorytmu komiwoja¿era
void KomiwojazerDisplayEdges(vector<unsigned char>komi, MatrixGraph graph);
void KomiwojazerBBRandomTest(int n, int m[], int o); //test na potrzeby labów
float GetValueOfBeing(vector<unsigned char> being, MatrixGraph graph);

void GLdisplay(int argc, char **argv, MatrixGraph graph, vector <unsigned char> path, string n);

#endif
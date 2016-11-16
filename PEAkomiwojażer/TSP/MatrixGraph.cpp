#include "Header.h"
/**
Klasa reprezentuj¹ca pojedyncz¹ krawêdŸ.
@param source sk¹d
@param dest dok¹d
@param weight waga
**/
Edge::Edge(int source, int dest, float weight)
{
	this->source = source;
	this->dest = dest;
	this->weight = weight;
}
vector<vector<float>> MatrixGraph::GetNodes()
{
	return nodes;
}
void MatrixGraph::Display()
{
	cout << "MatrixGraph: \n";
	for (auto i = 0; i < nodes.size(); i++)
	{
		cout << i << ": ";
		for (auto j = 0; j < nodes[i].size(); j++)
		{
			cout << " " << nodes[i][j];
		}
		cout << "\n";
	}
}
void MatrixGraph::Load(ifstream &file)
{
	int size;
	float weight;
	file >> size;
	nodes.clear();
	nodes.resize(size);
	visited.resize(size, false);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			file >> weight;
			if (i == j)
				nodes[i].push_back(FLT_MAX);
			else
				nodes[i].push_back(weight);
		}
	}
}
void MatrixGraph::LoadTSP(ifstream &file)
{
	int size = 0, i = 0;
	string read = "";
	vector <pair<float, float>> cities;
	pair <float, float> coord;
	float weight = 0;
	//czytaj nag³ówek
	while (read.compare("NODE_COORD_SECTION") != 0)
	{
		file >> read;
		if (read.compare("DIMENSION:") == 0)
		{
			file >> size;
			nodes.clear();
			nodes.resize(size);
			visited.resize(size, false);
		}
		else if (read.compare("DIMENSION") == 0)
		{
			file >> read; // wczytanie ':'
			file >> size;
			nodes.clear();
			nodes.resize(size);
			visited.resize(size, false);
		}
	}
	//czytaj koordynaty miast
	while (i < size)
	{
		file >> i;
		file >> coord.first;
		file >> coord.second;
		cities.push_back(coord);
	}
	//zamieñ koordynaty miast na macierz
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j)
			{
				weight = sqrt(pow(cities[i].first - cities[j].first, 2) + pow(cities[i].second - cities[j].second, 2));		// z Pitagorasa, rzecz jasna
			}
			else
				weight = FLT_MAX;
			nodes[i].push_back(weight);
		}
	}
}
void MatrixGraph::LoadATSP(ifstream &file)
{
	int size;
	float weight;
	file >> size;
	nodes.clear();
	nodes.resize(size);
	visited.resize(size, false);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			file >> weight;
			nodes[i].push_back(weight);
		}
	}
}
void MatrixGraph::Generate(int N)
{
	nodes.clear();
	nodes.resize(N);
	visited.resize(N, false);
	for (auto i = 0; i < N; i++)
	{
		for (auto j = 0; j < N; j++)
		{
			nodes[j].push_back((float)(rand() % 100 + 1));
		}
	}
}
float MatrixGraph::DoesEdgeExist(int node1_index, int node2_index)
{
	return nodes[node1_index][node2_index];
}
int MatrixGraph::Density()
{
	if (nodes.size() > 0)
	{
		int percentage = 0;
		for (auto i = 0; i < nodes.size(); i++)
		{
			for (auto j = 0; j < nodes.size(); j++)
				if (nodes[i][j] == NULL)
					percentage++;
		}
		return 100 - percentage * 100 / ((int)nodes.size()*(int)nodes.size());
	}
	else
		return 0;
}
int MatrixGraph::GetSize()
{
	return (int)nodes.size();
}
/*
void MatrixGraph::DFS(int node, MyList *wynik)
{
	visited[node] = true;

	for (auto i = 0; i < nodes.size(); i++)
		if ((nodes[node][i] > 0) && !visited[i])
			DFS(i, wynik);
		else
			wynik->AddAtEnd(i);
}
*/
vector<Edge> MatrixGraph::EdgesOf(int node_index)
{
	vector<Edge> temp;
	for (auto i = 0; i < nodes[node_index].size(); i++)
	{
		if (nodes[node_index][i] != NULL)
			temp.push_back(Edge(node_index, i, nodes[node_index][i]));
	}
	return temp;
}

float MatrixGraph::GetValueOf(unsigned char node1, unsigned char node2)
{
	return nodes[node1][node2];
}

vector<Edge> MatrixGraph::Edges()
{
	vector<Edge> temp;
	for (auto i = 0; i < nodes.size(); i++)
	{
		for (auto j = 0; j < nodes.size(); j++)
		{
			if (nodes[i][j] != NULL)
				temp.push_back(Edge(i, j, nodes[i][j]));
		}
	}
	return temp;
}
float MatrixGraph::CheckMaxNodeValue()
{
	float max = 0;
	for (auto i = 0; i < nodes.size(); i++)
	{
		for (auto j = 0; j < nodes.size(); j++)
			max = nodes[i][j]>max ? nodes[i][j] : max;
	}
	return max;
}
void MatrixGraph::DisplayMatrix()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes.size(); j++)
			cout << " " << nodes[i][j];
		cout << "\n";
	}
}
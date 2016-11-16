#include "header.h"

void ListGraph::Generate(int size, int density, bool mst)
{
	ListGraph graph2;
	int count = 0;
	while (count != size)
	{
		count = 0;
		nodes.clear();
		nodes.resize(size);
		graph2.nodes.clear();
		graph2.nodes.resize(size);

		for (int i = 0; i < size; i++)
		{
			if (mst)
			{
				for (int j = i + 1; j < size; j++)
				{
					if (i != j && rand() % 101 <= (mst ? density / 2 : density))
					{
						nodes[i].push_back(make_pair(rand(), j));
						nodes[j].push_back(make_pair(nodes[i][nodes[i].size() - 1].first, i));
					}
				}
			}
			else
			{
				for (int j = 0; j < size; j++)
				{
					if (i != j && rand() % 101 <= (mst ? density / 2 : density))
					{
						nodes[i].push_back(make_pair(rand(), j));
						graph2.nodes[i].push_back(make_pair(nodes[i][nodes[i].size() - 1].first, j));
						graph2.nodes[j].push_back(make_pair(nodes[i][nodes[i].size() - 1].first, i));
					}
				}
			}
		}
		if (mst)
		{
			visited.clear();
			visited.resize(size, false);
			DFS(0);
			for (int i = 0; i < size; i++)
			{
				if (visited[i] == true)
					count++;
			}
		}
		else
		{
			graph2.visited.clear();
			graph2.visited.resize(size, false);
			graph2.DFS(0);
			for (int i = 0; i < size; i++)
			{
				if (graph2.visited[i] == true)
					count++;
			}
		}
	}
}
void ListGraph::Load(ifstream *file, bool make_undirected)
{
	ListGraph graph2;
	nodes.clear();
	int edges, size, temp, source, dest, weight;
	*file >> edges;
	*file >> size;
	nodes.resize(size);
	graph2.nodes.resize(size);
	for (int i = 0; i < edges; i++)
	{
		*file >> source;			//odczytanie wartoœci z pliku
		*file >> dest;
		*file >> weight;
		nodes[source].push_back(make_pair(weight, dest));
		if (make_undirected)
		{
			nodes[dest].push_back(make_pair(weight, source));
		}
		else
		{
			graph2.nodes[source].push_back(make_pair(weight, dest));
			graph2.nodes[dest].push_back(make_pair(weight, source));
		}
	}
	int count = 0;
	if (make_undirected)
	{
		visited.clear();
		visited.resize(size, false);
		DFS(0);
		for (int i = 0; i < size; i++)
		{
			if (visited[i] == true)
				count++;
		}
	}
	else
	{
		graph2.visited.clear();
		graph2.visited.resize(size, false);
		graph2.DFS(0);
		for (int i = 0; i < size; i++)
		{
			if (graph2.visited[i] == true)
				count++;
		}
	}
	if (count != size)
		cout << "\n         Graf jest niespójny!!!\n";
}
void ListGraph::Display()
{
	cout << "ListGraph: \n";
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < nodes[i].size(); j++)
		{
			cout << nodes[i][j].first << " " << nodes[i][j].second << " ";
		}
		cout << "\n";
	}
}

int ListGraph::DoesEdgeExist(int node1_index, int node2_index)
{
	for (int i = 0; i < nodes[node1_index].size(); i++)
	{
		if (nodes[node1_index][i].second == node2_index)
			return nodes[node1_index][i].first;
	}
	return NULL;
}
int ListGraph::get_size()
{
	return nodes.size();
}

vector<pair<int, int>> ListGraph::EdgesOf(int node_index)
{
	vector<pair<int, int>> temp;
	for (int i = 0; i < nodes[node_index].size(); i++)
	{
		temp.push_back(make_pair(nodes[node_index][i].first, nodes[node_index][i].second));
	}
	return temp;
}
vector<Edge> ListGraph::Edges()
{
	vector<Edge> temp;

	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes[i].size(); j++)
			temp.push_back(Edge(i, nodes[i][j].second, nodes[i][j].first));
	}
	return temp;
}
vector<vector<pair<int, int>>> ListGraph::get_nodes()
{
	return nodes;
}
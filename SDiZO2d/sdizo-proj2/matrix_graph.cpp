#include "header.h"
/**
Klasa reprezentuj¹ca pojedyncz¹ krawêdŸ.
@param source sk¹d
@param dest dok¹d
@param weight waga
**/
Edge::Edge(int source, int dest, int weight)
{
	this->source = source;
	this->dest = dest;
	this->weight = weight;
}
/* OBSOLETE */
void MatrixGraph::Generate(int size, int density, bool mst)
{
	int count = 0;
	visited.resize(size);
	nodes.resize(size);

	while (count != size)
	{
		count = 0;
		for (int i = 0; i < size; i++)
		{
			visited[i] = false;
			nodes[i].clear();
			nodes[i].resize(size, 0);
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (nodes[i][j] == 0 && rand() % 101 <= density)
				{
					nodes[i][j] = rand();
					if (mst)
						nodes[j][i] = nodes[i][j];
				}
			}
		}
		DFS(0);
		for (int i = 0; i < size; i++)
		{
			if (visited[i] == true)
				count++;
		}
	}
}
void MatrixGraph::Display()
{
	cout << "MatrixGraph: \n";
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < nodes[i].size(); j++)
		{
			cout << " " << nodes[i][j];
		}
		cout << "\n";
	}
}
void MatrixGraph::CopyListGraph(ListGraph *listgraph)
{
	nodes.clear();
	nodes.resize(listgraph->get_nodes().size());
	for (int i = 0; i < listgraph->get_nodes().size(); i++)
	{
		nodes[i].clear();
		nodes[i].resize(listgraph->get_nodes().size());

		for (int j = 0; j < listgraph->get_nodes()[i].size(); j++)
		{
			nodes[i][listgraph->get_nodes()[i][j].second] = listgraph->get_nodes()[i][j].first;
		}
	}
}

int MatrixGraph::DoesEdgeExist(int node1_index, int node2_index)
{
	return nodes[node1_index][node2_index];
}
int MatrixGraph::Density()
{
	if (nodes.size()>0)
	{
		int percentage = 0;
		for (int i = 0; i < nodes.size(); i++)
		{
			for (int j = 0; j < nodes.size(); j++)
			if (nodes[i][j] == NULL)
				percentage++;
		}
		return 100 - percentage * 100 / (nodes.size()*nodes.size());
	}
	else
		return 0;
}
int MatrixGraph::get_size()
{
	return nodes.size();
}

vector<pair<int, int>> MatrixGraph::EdgesOf(int node_index)
{
	vector<pair<int, int>> temp;
	for (int i = 0; i < nodes[node_index].size(); i++)
	{
		if (nodes[node_index][i] != NULL)
			temp.push_back(make_pair(nodes[node_index][i], i));
	}
	return temp;
}
vector<Edge> MatrixGraph::Edges()
{
	vector<Edge> temp;
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes.size(); j++)
		{
			if (nodes[i][j] != NULL)
				temp.push_back(Edge(i, j, nodes[i][j]));
		}
	}
	return temp;
}

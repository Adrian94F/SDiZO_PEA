#include "header.h"

vector<int> FordBellman(Graph* G, int source, int dest)
{
	int n = G->get_size();
	vector<int> distance(n);
	for (int i = 0; i < n; i++)
	{
		if (i == source)
		{
			distance[i] = 0;
		}
		else
		{
			distance[i] = -1;
		}
	}
	vector<Edge> edges = G->Edges();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < edges.size(); j++)
		{
			if (distance[edges[j].source] != -1 && (distance[edges[j].dest] == -1 || distance[edges[j].source] + edges[j].weight < distance[edges[j].dest]))
			{
				distance[edges[j].dest] = distance[edges[j].source] + edges[j].weight;
			}
		}
	}
	return distance;
}
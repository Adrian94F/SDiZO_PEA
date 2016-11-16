#include "header.h"

vector<Edge> Prim(Graph* G)
{
	int n = G->get_size();
	int source = 0;
	vector<Edge> MST;
	priority_queue<Edge, vector<Edge>, compareEdges> q;
	vector<bool> visited;
	visited.resize(n);
	visited[source] = true;
	vector<pair<int, int> > tmp = G->EdgesOf(source);
	for (int i = 0; i < tmp.size(); i++)
	{
		Edge e = Edge(source, tmp[i].second, tmp[i].first);
		q.push(e);
	}
	while (--n)
	{
		while (!q.empty() && visited[q.top().dest])
			q.pop();
	
		if (q.empty())
		{
			break;
		}
		Edge x = q.top();
		MST.push_back(x);
		visited[x.dest] = true;
		tmp = G->EdgesOf(x.dest);
		for (int i = 0; i < tmp.size(); i++)
		{
			if (!visited[tmp[i].second])
			{
				Edge e = Edge(x.dest, tmp[i].second, tmp[i].first);
				q.push(e);
			}
		}
	}
	return MST;
}
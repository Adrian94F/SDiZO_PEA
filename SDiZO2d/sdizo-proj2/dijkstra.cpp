#include "header.h"

vector<int> Dijkstra(Graph* G, int source, int dest)
{
	int n = G->get_size();
	vector<int> distance(n);
	for (int i = 0; i < n; i++)
	{
		distance[i] = -1;
	}
	priority_queue<pair<int, int> > q;
	q.push(make_pair(0, source));
	while (!q.empty())
	{
		pair<int, int> x = q.top();
		q.pop();
		if (!(distance[x.second] == -1))
		{
			continue;
		}
		distance[x.second] = -x.first;
		if (x.second == dest)
			break;
		vector<pair<int, int> > neighbors = G->EdgesOf(x.second);
		for (int i = 0; i < neighbors.size(); i++)
		{
			pair<int, int> y = neighbors[i];
			if (distance[y.second] == -1)
			{
				q.push(make_pair(x.first - y.first, y.second));
			}
		}
	}
	return distance;
}
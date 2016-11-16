#include "header.h"

Set::Set(int n)
{
	contents.resize(n);
	for (int i = 0; i < n; i++)
	{
		contents[i] = i;
	}
}
int Set::find(int x)
{
	int parent;
	if (contents[x] != x)
	{
		parent = this->find(contents[x]);
		contents[x] = parent;
	}
	else
	{
		parent = x;
	}
	return parent;
}
void Set::unite(int x, int y)
{
	int parentx = this->find(x);
	int parenty = this->find(y);
	contents[parenty] = parentx;
}
compareEdges::compareEdges(bool rev)
{
	reverse = rev;
}
bool compareEdges::operator() (const Edge& x, const Edge& y) const
{
	if (x.weight == y.weight)
	{
		if (x.source == y.source)
		{
			if (reverse) return x.dest > y.dest;
			else return x.dest < y.dest;
		}
		else
		{
			if (reverse) return x.source > y.source;
			else return x.source < y.source;
		}
	}
	else
	{
		if (reverse) return x.weight > y.weight;
		else return x.weight < y.weight;
	}
}

vector<Edge> Kruskal(Graph* G)
{
	vector<Edge> MST;
	vector<Edge> edges = G->Edges();
	Set nodes(G->get_size());
	sort(edges.begin(), edges.end(), compareEdges(false));
	for (int i = 0; i < edges.size(); i++)
	{
		Edge e = edges[i];
		if (nodes.find(e.source) != nodes.find(e.dest))
		{
			MST.push_back(e);
			nodes.unite(e.source, e.dest);
		}
	}
	return MST;
}
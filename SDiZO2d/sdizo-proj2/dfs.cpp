#include "header.h"

void MatrixGraph::DFS(int node)
{
	visited[node] = true;

	for (int i = 0; i < nodes.size(); i++)
	if ((nodes[node][i] >0) && !visited[i])
		DFS(i);
}
void ListGraph::DFS(int node)
{
	visited[node] = true;

	for (int i = 0; i < nodes[node].size(); i++)
	if (!visited[nodes[node][i].second])
		DFS(nodes[node][i].second);
}
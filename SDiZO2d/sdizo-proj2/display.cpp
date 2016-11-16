#include "header.h"

void DisplayVec(vector<int> input, int dest)
{
	cout << input[dest] << " ";
}
void DisplayEdge(vector<Edge> input)
{
	cout << "  Src:   Dst:   Wt:" << endl;
	for (int i = 0; i < input.size(); i++)
		cout << setw(6) << input[i].source << " " << setw(6) << input[i].dest << " " << setw(6) << input[i].weight << endl;
}
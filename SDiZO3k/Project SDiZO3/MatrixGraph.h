#pragma once

#include <iostream>

class CMatrixGraph
{
private:
	int numberOfVertices;
	int** matrix;

public:
	CMatrixGraph(int numberOfVertices);
	~CMatrixGraph();

	void setNumberOfVertices(int numberOfVertices);
	void setMatrix(int** matrix);

	int getNumberOfVertices();
	int** getMatrix();

	bool addEdge(int begin, int end, int weight);
	void print();
};


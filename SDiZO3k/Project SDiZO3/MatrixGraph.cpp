#include "stdafx.h"
#include "MatrixGraph.h"


CMatrixGraph::CMatrixGraph(int numberOfVertices)
{
	this->numberOfVertices = numberOfVertices;
	matrix = new int*[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++)
		matrix[i] = new int[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++)
		for (int j = 0; j < numberOfVertices; j++)
			matrix[i][j] = 0;
}

CMatrixGraph::~CMatrixGraph()
{
	for (int i = 0; i < numberOfVertices; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void CMatrixGraph::setNumberOfVertices(int numberOfVertices)
{
	this->numberOfVertices = numberOfVertices;
}

void CMatrixGraph::setMatrix(int** matrix)
{
	this->matrix = matrix;
}

int CMatrixGraph::getNumberOfVertices()
{
	return numberOfVertices;
}

int** CMatrixGraph::getMatrix()
{
	return matrix;
}

bool CMatrixGraph::addEdge(int begin, int end, int weight)
{
	if (begin >= numberOfVertices || end >= numberOfVertices)
		return false;

	if (matrix[begin][end] != 0)
		return false;

	matrix[begin][end] = weight;
	return true;
}

void CMatrixGraph::print()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		for (int j = 0; j < numberOfVertices; j++)
		{
			std::cout.width(2);
			std::cout << matrix[i][j];
			std::cout << " ";
		}
		std::cout << std::endl << std::endl;
	}
}

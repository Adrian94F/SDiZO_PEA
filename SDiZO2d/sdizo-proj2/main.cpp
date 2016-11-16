#include "header.h"

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	ListGraph listgraph;
	MatrixGraph matrixgraph;
	menu(&listgraph, &matrixgraph);
	system("pause");
	return 0;
}
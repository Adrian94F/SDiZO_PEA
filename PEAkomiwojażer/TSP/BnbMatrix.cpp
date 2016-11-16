#include "Header.h"

BnbMatrix::BnbMatrix(MatrixGraph graph)
{
	edges = EdgePtr(new vector<pair<unsigned char, unsigned char>>);
	nodes = graph.GetNodes();
	size = (unsigned char)nodes.size();
	minrow.resize(size, FLT_MAX);
	mincol.resize(size, FLT_MAX);
	rowid.resize(size);
	colid.resize(size);
	number = 0;
	for (auto i = 0; i < size; i++)
	{
		rowid[i] = i;
		colid[i] = i;
	}
	limit = 0;
	minpos = { 0,0 };
	Reduce();
	FindZero();
}
BnbMatrix::BnbMatrix(BnbMatrix &matrix, bool cutout, float _number)
{
	nodes = matrix.GetNodes(); // wypenienie macierzy z macierzy rodzica (wierzcho³ki)
	size = (unsigned char)nodes.size(); // liczba wierzcho³ków
	minrow.resize(size, FLT_MAX); // tablica z minimalnymi wartoœciami wierszy
	mincol.resize(size, FLT_MAX); // i kolumn
	rowid = matrix.GetRowID(); // po usuniêciu zmieniaj¹ siê indeksy, rowid przechowuje oryginalne indeksy wierszy
	colid = matrix.GetColID(); // coldi - kolumn
	limit = matrix.GetLimit(); // granica
	minpos = matrix.GetMinPos(); // znaleziona komórka z maksylnym minimum

	number = _number; // numer macierzy
	if (cutout) // czy wycinaæ kolumnê, czy nie?
	{
		CutOut(); // obetnij
		edges = EdgePtr(new vector<pair<unsigned char, unsigned char>>); //wskaŸnik na nowe rozwai¹zanie
		edges->resize(matrix.edges->size()); // zwiêksz do wielkoœci poprzedniego rozwiazania 
		for (auto i = 0; i < edges->size(); i++) // i przepisz
			(*edges)[i] = (*matrix.edges)[i];
		edges->push_back(pair<unsigned char, unsigned char>(minpos.first, minpos.second)); // komórkê znalezion¹ dodaj do rozwi¹zania
	}
	else
	{
		InsertInf(); // ustaw nieskoñczonoœæ
		edges = matrix.edges; 
	}
	Reduce(); // redukuj macierz
	FindZero(); // znajdŸ pozycjê 0, dla którego minimum kolumny i wiersza jest najwy¿sze
	if (nodes.size() == 1) // jesli wielkoœæ macierzy = 1 syn nie bêdzie stworzony, wiêc dodaj pozycjê zera do rozwi¹zañ ju¿ teraz.
		edges->push_back(pair<unsigned char, unsigned char>(minpos.first, minpos.second));
}
vector<unsigned char> BnbMatrix::GetRowID()
{
	return rowid;
}
vector<unsigned char> BnbMatrix::GetColID()
{
	return colid;
}
void BnbMatrix::FindZero()
{
	double tmp_min_row_val, tmp_min_col_val, tmp_min = 0;
	for (auto i = 0; i < size; i++)				// wiersz
		for (auto j = 0; j < size; j++)			// kolumna
		{
			tmp_min_row_val = FLT_MAX;
			tmp_min_col_val = FLT_MAX;
			if (nodes[i][j] == 0)							// je¿eli komórka jest 0
			{
				for (auto k = 0; k < size; k++)
				{
					if (k != j && nodes[i][k] < tmp_min_row_val) // je¿eli droga jest mniejsza od min_row
						tmp_min_row_val = nodes[i][k];			 // nadpisz min_row
					if (k != i && nodes[k][j] < tmp_min_col_val)
						tmp_min_col_val = nodes[k][j];			 // nadpisz min_col
				}
				if (tmp_min_col_val + tmp_min_row_val >= tmp_min)
				{
					tmp_min = tmp_min_col_val + tmp_min_row_val;
					minpos.first = rowid[i];
					minpos.second = colid[j];
				}
			}
		}
}
void BnbMatrix::Reduce() {
	// znalezienie min w wierszach, odjêcie minimów od wierszy
	// znalezienie kolumn w wierzach, odjêcie minimów od kolumn
	////////////////////////////////////////////////////////////
	//  sprawdzanie minimów po wierszach
	for (auto i = 0; i < size; i++)				// wiersz
		for (auto j = 0; j < size; j++)			// kolumna
			if (minrow[i] > nodes[i][j])
				minrow[i] = nodes[i][j];

	// odejmowanie minimów od wierszy
	for (auto i = 0; i < size; i++)				// wiersz
	{
		for (auto j = 0; j < size; j++)			// kolumna
		{
			if (nodes[i][j] != FLT_MAX)
				nodes[i][j] -= minrow[i];
			if (nodes[i][j] < 0.0)					// je?eli poni?ej 0, to INF
				nodes[i][j] = FLT_MAX;
		}
		limit += minrow[i];
	}
	// sprawdzanie minimów po kolumnach
	for (auto i = 0; i < size; i++)				//kolumna
		for (auto j = 0; j < size; j++)			//wiersz
			if (mincol[i] >nodes[j][i])
				mincol[i] = nodes[j][i];

	// odejmowanie minimów od kolumn
	for (auto i = 0; i < size; i++)				// kolumna
	{
		for (auto j = 0; j < size; j++)			// wiersz
		{
			if (nodes[j][i] != FLT_MAX)
				nodes[j][i] -= mincol[i];
			if (nodes[j][i] < 0)					// je?eli poni?ej 0, to INF
				nodes[j][i] = FLT_MAX;
		}
		limit += mincol[i];
	}
}
void BnbMatrix::CutOut()
{
	pair<unsigned char, unsigned char> pos = EdgeOf(minpos.first, minpos.second);
	nodes.erase(nodes.begin() + pos.first);
	rowid.erase(rowid.begin() + pos.first);
	colid.erase(colid.begin() + pos.second);
	minrow.erase(minrow.begin() + pos.first);
	mincol.erase(mincol.begin() + pos.second);
	size--;
	for (auto i = 0; i < size; i++)
		nodes[i].erase(nodes[i].begin() + pos.second);
	InsertInfRev();
}
void BnbMatrix::InsertInf()
{
	pair<unsigned char, unsigned char> infpos = { EdgeOf(minpos.first, minpos.second) };
	nodes[infpos.first][infpos.second] = numeric_limits<float>::infinity();
}
void BnbMatrix::InsertInfRev() // wstawia w przeciwny wierz i kolumnê inf (nie <i, j>, a <j, i>)
{
	pair<unsigned char, unsigned char> infpos = { EdgeOf(minpos.second, minpos.first) };
	if (infpos.first == UCHAR_MAX && infpos.second == UCHAR_MAX)
		return;
	else
		nodes[infpos.first][infpos.second] = numeric_limits<float>::infinity();
}
void BnbMatrix::Clean()
{
	minrow.clear();
	minrow.shrink_to_fit();
	mincol.clear();
	mincol.shrink_to_fit();
}
pair<unsigned char, unsigned char> BnbMatrix::EdgeOf(unsigned char x, unsigned char y)
{
	bool x_exists = false, y_exists = false;
	unsigned char xx, yy;
	for (auto i = 0; i < size; i++)
	{
		if (!x_exists && rowid[i] == x)
		{
			x_exists = true;
			xx = i;
		}
		if (!y_exists && colid[i] == y)
		{
			y_exists = true;
			yy = i;
		}
	}
	if (x_exists && y_exists)
		return pair<unsigned char, unsigned char>(xx, yy);
	else
		return pair<unsigned char, unsigned char>(UCHAR_MAX, UCHAR_MAX);
}
pair<unsigned char, unsigned char> BnbMatrix::GetMinPos() {
	return minpos;
}
vector<vector<float>>BnbMatrix::GetNodes()
{
	return nodes;
}
float BnbMatrix::GetLimit()
{
	return limit;
}
float BnbMatrix::GetNumber()
{
	return number;
}
EdgePtr BnbMatrix::GetEdges() {
	return edges;
}
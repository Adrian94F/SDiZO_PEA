//Adrian Frydmañski - 209865

#include "stdafx.h"
#include "Heap.h"

////////////////////////////////
// konstruktor
////////////////////////////////
Heap::Heap()
{
	length = 0;												// d³ugoœæ tablicy
	table = NULL;											// tablica z kopcem
}

////////////////////////////////
// zwraca indeks rodzica
////////////////////////////////
int Heap::parent(int v)
{
	return (v - 1) / 2;
}

////////////////////////////////
// zwraca indeks lewego dziecka
////////////////////////////////
int Heap::leftSon(int v)
{
	return 2 * v + 1;
}

////////////////////////////////
// zwraca indeks prawego dziecka 
////////////////////////////////
int Heap::rightSon(int v)
{
	return 2 * v + 2;
}

////////////////////////////////
// wypisuje wierzcho³ek kopca, o ile istnieje
////////////////////////////////
void Heap::top()
{
	if (table != NULL)										// jeœli kopiec istnieje
		cout << table[0] << "\n";
}

////////////////////////////////
// wstawia podana wartosc do kopca  
////////////////////////////////
void Heap::add(int x)
{
	int * tmp = new int[++length];							// utworzenie nowej o wiêkszej d³ugoœci
	tmp[length - 1] = x;									// dodanie na koniec nowej wartoœci
	for (int i = 0; i < length - 1; i++)					// przekopiowanie starych wartoœci do nowej tablicy
		tmp[i] = table[i];
	delete[] table;											// usuniêcie starej tablicy
	table = tmp;											// wskazanie na now¹, w³aœciw¹ tablicê
	repairFromBottom();										// napraw od do³u
}

////////////////////////////////
// naprawia kopiec od do³u
////////////////////////////////
void Heap::repairFromBottom()
{ 
	int v = length - 1;											// naprawa od do³u - bo dodaliœmy element na koñcu:
	while (v != 1 && table[parent(v)] < table[v])			// przywrócenie porz¹dku w kopcu
	{
		swap(table[parent(v)], table[v]);					// póki potomek jest wiekszy od rodzica, zamieniamy ich	
		v = parent(v);										// po zamianie przechodzimy do rodzica, który jest potomkiem kogo innego
	}
}

////////////////////////////////
// naprawia kopiec od góry
////////////////////////////////
void Heap::repairFromTop()
{
	int i = 0, j;
	do
	{
		if (rightSon(i) < length - 1)
			j = (table[rightSon(i)] > table[leftSon(i)] ? rightSon(i) : leftSon(i));
		else if (leftSon(i) < length - 1)
			j = leftSon(i);
		else
			break;
		if (table[i] < table[j])
			swap(table[i], table[j]);
		i = j;
	} while (true);
}

////////////////////////////////
// usuwa wierzcholek kopca
////////////////////////////////
void Heap::del()
{
	swap(table[0], table[length - 1]);
	if (length == 0)										// je¿eli kopiec jest niepusty, bo co z pstego usuwaæ?
		return;
	table[0] = table[--length];								// wstaw ostatni element do wierzcholka i zmniejsz d³ugoœæ
	int * tmp = new int[length];							// utworzenie nowej, krótszej tablicy
	for (int i = 0; i < length; i++)						// przekopiowanie elementów oprócz ostatniego
	{
		tmp[i] = table[i];
	}
	delete[] table;											// usuniêcie starej tablicy
	table = tmp;											// wskazanie na now¹, w³aœciw¹ tablicê
	repairFromTop();										// napraw od góry
}




////////////////////////////////
// wyswietl
////////////////////////////////
void Heap::display()
{
	if (length == 0)
		return;
	int i = 0, level = 0;
	Heap * tmp = new Heap();
	string space = "", offshoot = "root: ";
	while (true)
	{
		space = "";
		for (int j = 0; j < level; j++)
			space += "      |";
		space += offshoot;
		if (tmp->find(rightSon(i)) == -1 ? true : false)
		{
			cout << space << table[i] << endl;
			tmp->add(i);
		}
		if (rightSon(i) < length && (tmp->find(rightSon(i)) == -1 ? true : false))
		{
			i = rightSon(i);
			level++;
			offshoot = "---r--";
		}
		else if (leftSon(i) < length && (tmp->find(leftSon(i)) == -1 ? true : false))
		{
			i = leftSon(i);
			level++;
			offshoot = "---l--";
		}
		else if (i > 0)
		{
			i = parent(i);
			level--;
		}
		else if (tmp->length >= length)
			break;
	}
}

////////////////////////////////
// wyszukaj
////////////////////////////////
int Heap::find(int a) 
{
	for (int i = 0; i < length; i++)
		if (a == table[i])
			return i;
	return -1;
}

////////////////////////////////
// otwórz
////////////////////////////////
void Heap::open(string s)
{
	s += ".txt";
	ifstream file;
	file.open(s.c_str());
	file >> length;
	table = new int[length];
	for (int i = 0; i < length; i++)
		file >> table[i];
	file.close();
}

////////////////////////////////
// zapisz
////////////////////////////////
void Heap::save(string s)
{
	s += ".txt";
	ofstream file;
	file.open(s.c_str(), ios::app);
	file << length << endl;
	for (int i = 0; i < length; i++)
		file << table[i] << endl;
	file.close();
}
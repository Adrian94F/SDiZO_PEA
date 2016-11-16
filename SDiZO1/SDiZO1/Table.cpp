//Adrian Frydma�ski - 209865

#include "stdafx.h"
#include "Table.h"

////////////////////////////////
// konstruktor
////////////////////////////////
Table::Table()
{
	length = 0;
	table = NULL;
}

////////////////////////////////
// dodawanie na pocz�tek
////////////////////////////////
int Table::addBefore(int n)
{
	length++;								//zwi�kszenie d�ugo�ci tablicy
	int * temp = new int[length];			//utworzenie nowej o wi�kszej d�ugo�ci
	temp[0] = n;							//dodanie na pocz�tku nowej warto�ci
	for (int i = 1; i < length; i++)		//przekopiowanie starych warto�ci do nowej tablicy
		temp[i] = table[i - 1];
	delete[] table;							//usuni�cie starej tablicy
	table = temp;							//wskazanie na now�, w�a�ciw� tablic�
	return n;
}

////////////////////////////////
// dodawanie na koniec
////////////////////////////////
int Table::addAfter(int n)
{
	length++;								//zwi�kszenie d�ugo�ci tablicy
	int * temp = new int[length];			//utworzenie nowej o wi�kszej d�ugo�ci
	temp[length - 1] = n;					//dodanie na koniec nowej warto�ci
	for (int i = 0; i < length - 1; i++)//przekopiowanie starych warto�ci do nowej tablicy
		temp[i] = table[i];
	delete[] table;							//usuni�cie starej tablicy
	table = temp;							//wskazanie na now�, w�a�ciw� tablic�
	return n;
}

////////////////////////////////
// dodawanie w losowym miejscu
////////////////////////////////
int Table::addRand(int n)
{
	int r = rand() / RAND_MAX * length;		//wylosowanie lossowej pozycji
	length++;								//zwi�kszenie d�ugo�ci tablicy
	int * temp = new int[length];			//utworzenie nowej o wi�kszej d�ugo�ci
	temp[r] = n;							//wstawienie nowej warto�ci na wylosowanej pozycji
	for (int i = 0; i < r; i++)				//przekopiowanie starych warto�ci do nowej tablicy
		temp[i] = table[i];
	for (int i = r + 1; i < length; i++)	//przekopiowanie starych warto�ci do nowej tablicy
		temp[i] = table[i - 1];
	delete[] table;							//usuni�cie starej tablicy
	table = temp;							//wskazanie na now�, w�a�ciw� tablic�
	return n;
}

////////////////////////////////
// usuwanie pierwszego elementu
////////////////////////////////
void Table::delBefore()
{
	length--;								//zmniejszenie d�ugo�ci
	int * temp = new int[length];			//utworzenie nowej, kr�tszej tablicy
	for (int i = 0; i < length; i++)		//przekopiowanie element�w opr�cz pierwszego
	{
		temp[i] = table[i + 1];
	}
	delete[] table;							//usuni�cie starej tablicy
	table = temp;							//wskazanie na now�, w�a�ciw� tablic�
}

////////////////////////////////
// usuwanie ostatniego elementu
////////////////////////////////
void Table::delAfter()
{
	length--;								//zmniejszenie d�ugo�ci
	int * temp = new int[length];			//utworzenie nowej, kr�tszej tablicy
	for (int i = 0; i < length; i++)		//przekopiowanie element�w opr�cz ostatniego
	{
		temp[i] = table[i];
	}
	delete[] table;							//usuni�cie starej tablicy
	table = temp;							//wskazanie na now�, w�a�ciw� tablic�
}

////////////////////////////////
// usuwanie losowego elementu
////////////////////////////////
void Table::delRand()
{
	length--;								//zmniejszenie d�ugo�ci
	int r = rand() / RAND_MAX * length;		//wylosowanie pozycji w zakrezie d�ugo�ci tablicy
	int * temp = new int[length];			//utworzenie nowej tablicy
	for (int j = 0; j < r; j++)				//przekopiowanie element�w przed usuni�tym
		temp[j] = table[j];
	for (int j = r; j < length; j++)		//przekopiowanie element�w za usuni�tym
		temp[j] = table[j + 1];
	delete[] table;							//usuni�cie starej tablicy
	table = temp;							//wskazanie na now�, w�a�ciw� tablic�
}

////////////////////////////////
// wyswietl
////////////////////////////////
void Table::display()
{
	for (int i = 0; i < length; i++)		//leci po ca�ej tablicy i wy�wietla
	{
		cout << i << ": " << table[i] << ", 	";
	}
}

////////////////////////////////
// szukaj
////////////////////////////////
int Table::find(int k)
{
	for (int i = 0; i < length; i++)		//leci po ca�ej tablicy
		if (table[i] == k)
			return i;
	return NULL;
}

////////////////////////////////
// otw�rz
////////////////////////////////
void Table::open(string s)
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
void Table::save(string s)
{
	s += ".txt";
	ofstream file;
	file.open(s.c_str(), ios::app);
	file << length << endl;
	for (int i = 0; i < length; i++)
		file << table[i] << endl;
	file.close();
}
//Adrian Frydmañski - 209865

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
// dodawanie na pocz¹tek
////////////////////////////////
int Table::addBefore(int n)
{
	length++;								//zwiêkszenie d³ugoœci tablicy
	int * temp = new int[length];			//utworzenie nowej o wiêkszej d³ugoœci
	temp[0] = n;							//dodanie na pocz¹tku nowej wartoœci
	for (int i = 1; i < length; i++)		//przekopiowanie starych wartoœci do nowej tablicy
		temp[i] = table[i - 1];
	delete[] table;							//usuniêcie starej tablicy
	table = temp;							//wskazanie na now¹, w³aœciw¹ tablicê
	return n;
}

////////////////////////////////
// dodawanie na koniec
////////////////////////////////
int Table::addAfter(int n)
{
	length++;								//zwiêkszenie d³ugoœci tablicy
	int * temp = new int[length];			//utworzenie nowej o wiêkszej d³ugoœci
	temp[length - 1] = n;					//dodanie na koniec nowej wartoœci
	for (int i = 0; i < length - 1; i++)//przekopiowanie starych wartoœci do nowej tablicy
		temp[i] = table[i];
	delete[] table;							//usuniêcie starej tablicy
	table = temp;							//wskazanie na now¹, w³aœciw¹ tablicê
	return n;
}

////////////////////////////////
// dodawanie w losowym miejscu
////////////////////////////////
int Table::addRand(int n)
{
	int r = rand() / RAND_MAX * length;		//wylosowanie lossowej pozycji
	length++;								//zwiêkszenie d³ugoœci tablicy
	int * temp = new int[length];			//utworzenie nowej o wiêkszej d³ugoœci
	temp[r] = n;							//wstawienie nowej wartoœci na wylosowanej pozycji
	for (int i = 0; i < r; i++)				//przekopiowanie starych wartoœci do nowej tablicy
		temp[i] = table[i];
	for (int i = r + 1; i < length; i++)	//przekopiowanie starych wartoœci do nowej tablicy
		temp[i] = table[i - 1];
	delete[] table;							//usuniêcie starej tablicy
	table = temp;							//wskazanie na now¹, w³aœciw¹ tablicê
	return n;
}

////////////////////////////////
// usuwanie pierwszego elementu
////////////////////////////////
void Table::delBefore()
{
	length--;								//zmniejszenie d³ugoœci
	int * temp = new int[length];			//utworzenie nowej, krótszej tablicy
	for (int i = 0; i < length; i++)		//przekopiowanie elementów oprócz pierwszego
	{
		temp[i] = table[i + 1];
	}
	delete[] table;							//usuniêcie starej tablicy
	table = temp;							//wskazanie na now¹, w³aœciw¹ tablicê
}

////////////////////////////////
// usuwanie ostatniego elementu
////////////////////////////////
void Table::delAfter()
{
	length--;								//zmniejszenie d³ugoœci
	int * temp = new int[length];			//utworzenie nowej, krótszej tablicy
	for (int i = 0; i < length; i++)		//przekopiowanie elementów oprócz ostatniego
	{
		temp[i] = table[i];
	}
	delete[] table;							//usuniêcie starej tablicy
	table = temp;							//wskazanie na now¹, w³aœciw¹ tablicê
}

////////////////////////////////
// usuwanie losowego elementu
////////////////////////////////
void Table::delRand()
{
	length--;								//zmniejszenie d³ugoœci
	int r = rand() / RAND_MAX * length;		//wylosowanie pozycji w zakrezie d³ugoœci tablicy
	int * temp = new int[length];			//utworzenie nowej tablicy
	for (int j = 0; j < r; j++)				//przekopiowanie elementów przed usuniêtym
		temp[j] = table[j];
	for (int j = r; j < length; j++)		//przekopiowanie elementów za usuniêtym
		temp[j] = table[j + 1];
	delete[] table;							//usuniêcie starej tablicy
	table = temp;							//wskazanie na now¹, w³aœciw¹ tablicê
}

////////////////////////////////
// wyswietl
////////////////////////////////
void Table::display()
{
	for (int i = 0; i < length; i++)		//leci po ca³ej tablicy i wyœwietla
	{
		cout << i << ": " << table[i] << ", 	";
	}
}

////////////////////////////////
// szukaj
////////////////////////////////
int Table::find(int k)
{
	for (int i = 0; i < length; i++)		//leci po ca³ej tablicy
		if (table[i] == k)
			return i;
	return NULL;
}

////////////////////////////////
// otwórz
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
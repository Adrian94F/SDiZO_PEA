#include "Header.h"

MyList::MyList() {};				// kostruktor domy�lny - bezparametrowy

void MyList::AddAtStart(int value)		//dodanie warto�ci na pocz�tek listy
{
	Item *item = new Item;		//utworzenie nowej kom�rki listy
	item->value = value;		//zapisanie danej warto�ci do nowej kom�rki
	item->next = head;			//ustawienie wska�nika next na star� g�ow� listy
	this->head = item;			//ustawienie g�owy listy na now� kom�rk�
}
void MyList::AddAtEnd(int value)		//dodanie warto�ci na koniec listy
{
	if (head == NULL)
		AddAtStart(value);			//dodawanie na pocz�tek listy, je�eli nie posiada ona jeszcze �adnego elementu
	else
	{
		Item *item = head;			//stworzenie kopii wska�nika g�owy
		while (item->next != NULL)
			item = item->next;		//przej�cie po ca�ej li�cie do ostatniego elementu

		item->next = new Item;		//wskazanie ostatniemu elementowi na nowy ostatni element
		item->next->value = value;  //przypisanie nowemu elementowi danej warto�ci
	}
}
void MyList::AddAtRnd(int value)
{
	if (head != NULL && Length() > 0)	//sprawdzanie, czy lista nie jest pusta
	{
		Item *item = head;				//utworzenie kopii wska�nika g�owy
		int p;							//utworzenie zmiennej opisuj�cej pozycj� na kt�r� doda� nowy element
		if (Length() == 0)
			p = 0;
		else
			p = rand() % Length();		//losowanie pozycji w kt�r� zostanie dodana warto��

		if (p == Length() - 1)			//
			AddAtEnd(value);			//je�eli pozycja jest ko�cem listy, to dodanie na koniec
		else
		{								/* wsadzanie nowego elementu pomi�dzy ju� istniej�ce */
			for (int i = 0; i < p; i++)
				item = item->next;		//             nowy
			Item *temp = new Item;		// [poprzedni]  \/  [nast�pny]			:: wsadzamy nowy element pomi�dzy 2 inne
			temp->next = item->next;	// [poprzedni] [nowy] -> [nast�pny]		:: wskazujemy nowemu elementowi nast�pny element po nim,
										//		|					/ \			:: a stary dalej na niego wskazuje
			item->next = temp;			//		|------------------- |			:: wskazujemy poprzedniemu elementowi nowy element
			temp->value = value;		//										:: ustawiamy wartosc item'owi
		}								// [poprzedni] -> [nowy] -> [nastepny]	
	}									//										
	else
		AddAtStart(value);				//je�eli lista jest pusta, to dodanie na pocz�tek
}

void MyList::DelAtStart()				//usuwanie z pocz�tku listy
{
	Item *item = head;			//utworzenie kopii wska�nika g�owy
	if (item != NULL)
	{
		head = head->next;		//ustawienie g�owy na nast�pny element
		delete item;			//usuni�cie starej g�owy
	}
}
void MyList::DelAtEnd()							//usuwanie z ko�ca listy
{
	Item *item = head;					//utworzenie kopii wska�nika g�owy
	while (item->next->next != NULL)
	{
		item = item->next;				//przej�cie do ostatniego elementu
	}
	delete item->next;					//usuni�cie ostatniego elementu
	item->next = NULL;					//zmiana wska�nika przedostatniego elementu na NULL, �eby nie wskazywa� nic dalej
}
void MyList::DelAtRnd()								//usuwanie z losowej pozycji listy
{
	Item *item = head;						//utworzenie kopii wska�nika g�owy
	int length = Length();					//pobranie d�ugo�ci listy
	if (length == 1)
		DelAtStart();						//je�eli w li�cie znajduje si� 1 element, to dodanie na pocz�tek
	else
	{
		int p = rand() % length;			//losowanie pozycji
		for (int i = 0; i < p - 1; i++)
			item = item->next;				//przej�cie do danej pozycji

		Item *temp = item->next;			//           usuwany			::kopia wska�nika usuwanego elementu
		item->next = temp->next;			//[poprzedni]  /\  [nast�pny]	::wskazanie poprzedniemu na nast�pny
		delete temp;						//[poprzedni] -> [nast�pny]		::usuni�cie temp(zadanego)
	}
}
Item MyList::At(int index)
{
	Item *item = head;
	for (int i = 0; i < index; i++)
	{
		item = item->next;
	}
	return *item;
}
Item* MyList::Search(int value)
{
	Item *item = head;								//kopia wska�nika g�owy
	while (item != nullptr && item->value != value)
		item = item->next;							//przej�cie po li�cie szukaj�c danego elementu
	return item;									//zwr�cenie elementu(je�eli nie znaleziono zwr�ci NULL)
}
int MyList::Length()								//pobranie d�ugo�ci listy
{
	int i = 0;
	Item * temp = head;						//ustawienie kopii wska�nika g�owy
	if (temp != NULL)
	{
		for (i = 1; temp->next != NULL; i++)
			temp = temp->next;				//przej�cie po li�cie zliczaj�c elementy
	}
	return i;
}
int MyList::Sum()
{
	int suma = 0;
	for (int i = 0; i < Length(); i++)
	{
		suma += At(i).value;
	}
	return suma;
}

void MyList::Display()								//wy�wietlanie listy po 6 kom�rek w wierszu
{
	Item *item = head;						//kopia wska�nika g�owy
	for (int i = 0; item != nullptr; i++)
	{
		if (i % 5 == 0)
			cout << endl;
		cout << setw(5) << i << ": " << setw(5) << item->value << " |";
		item = item->next;
	}
	cout << endl;
}
void MyList::Save()					//zapisanie listy do pliku
{
	string name;					//nazwa pliku
	int size = Length();			//d�ugo�� listy
	cout << "podaj nazwe pliku: ";
	cin >> name;

	ofstream file;
	file.open(name);
	file << size << " ";
	Item *item = head;				//kopia wska�nika g�owy
	for (int i = 0; i < size; i++)
	{
		file << item->value << " ";
		item = item->next;			//przej�cie po li�cie i zapisanie wszystkich element�w do pliku
	}
	file.close();
}
void MyList::Clean()						//czyszczenie listy
{
	if (head != NULL)
	{
		int length = Length();

		for (int i = 0; i < length; i++)
			DelAtStart();
	}
}

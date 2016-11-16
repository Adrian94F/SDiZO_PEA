#include "Header.h"

MyList::MyList() {};				// kostruktor domyœlny - bezparametrowy

void MyList::AddAtStart(int value)		//dodanie wartoœci na pocz¹tek listy
{
	Item *item = new Item;		//utworzenie nowej komórki listy
	item->value = value;		//zapisanie danej wartoœci do nowej komórki
	item->next = head;			//ustawienie wskaŸnika next na star¹ g³owê listy
	this->head = item;			//ustawienie g³owy listy na now¹ komórkê
}
void MyList::AddAtEnd(int value)		//dodanie wartoœci na koniec listy
{
	if (head == NULL)
		AddAtStart(value);			//dodawanie na pocz¹tek listy, je¿eli nie posiada ona jeszcze ¿adnego elementu
	else
	{
		Item *item = head;			//stworzenie kopii wskaŸnika g³owy
		while (item->next != NULL)
			item = item->next;		//przejœcie po ca³ej liœcie do ostatniego elementu

		item->next = new Item;		//wskazanie ostatniemu elementowi na nowy ostatni element
		item->next->value = value;  //przypisanie nowemu elementowi danej wartoœci
	}
}
void MyList::AddAtRnd(int value)
{
	if (head != NULL && Length() > 0)	//sprawdzanie, czy lista nie jest pusta
	{
		Item *item = head;				//utworzenie kopii wskaŸnika g³owy
		int p;							//utworzenie zmiennej opisuj¹cej pozycjê na któr¹ dodaæ nowy element
		if (Length() == 0)
			p = 0;
		else
			p = rand() % Length();		//losowanie pozycji w któr¹ zostanie dodana wartoœæ

		if (p == Length() - 1)			//
			AddAtEnd(value);			//je¿eli pozycja jest koñcem listy, to dodanie na koniec
		else
		{								/* wsadzanie nowego elementu pomiêdzy ju¿ istniej¹ce */
			for (int i = 0; i < p; i++)
				item = item->next;		//             nowy
			Item *temp = new Item;		// [poprzedni]  \/  [nastêpny]			:: wsadzamy nowy element pomiêdzy 2 inne
			temp->next = item->next;	// [poprzedni] [nowy] -> [nastêpny]		:: wskazujemy nowemu elementowi nastêpny element po nim,
										//		|					/ \			:: a stary dalej na niego wskazuje
			item->next = temp;			//		|------------------- |			:: wskazujemy poprzedniemu elementowi nowy element
			temp->value = value;		//										:: ustawiamy wartosc item'owi
		}								// [poprzedni] -> [nowy] -> [nastepny]	
	}									//										
	else
		AddAtStart(value);				//je¿eli lista jest pusta, to dodanie na pocz¹tek
}

void MyList::DelAtStart()				//usuwanie z pocz¹tku listy
{
	Item *item = head;			//utworzenie kopii wskaŸnika g³owy
	if (item != NULL)
	{
		head = head->next;		//ustawienie g³owy na nastêpny element
		delete item;			//usuniêcie starej g³owy
	}
}
void MyList::DelAtEnd()							//usuwanie z koñca listy
{
	Item *item = head;					//utworzenie kopii wskaŸnika g³owy
	while (item->next->next != NULL)
	{
		item = item->next;				//przejœcie do ostatniego elementu
	}
	delete item->next;					//usuniêcie ostatniego elementu
	item->next = NULL;					//zmiana wskaŸnika przedostatniego elementu na NULL, ¿eby nie wskazywa³ nic dalej
}
void MyList::DelAtRnd()								//usuwanie z losowej pozycji listy
{
	Item *item = head;						//utworzenie kopii wskaŸnika g³owy
	int length = Length();					//pobranie d³ugoœci listy
	if (length == 1)
		DelAtStart();						//je¿eli w liœcie znajduje siê 1 element, to dodanie na pocz¹tek
	else
	{
		int p = rand() % length;			//losowanie pozycji
		for (int i = 0; i < p - 1; i++)
			item = item->next;				//przejœcie do danej pozycji

		Item *temp = item->next;			//           usuwany			::kopia wskaŸnika usuwanego elementu
		item->next = temp->next;			//[poprzedni]  /\  [nastêpny]	::wskazanie poprzedniemu na nastêpny
		delete temp;						//[poprzedni] -> [nastêpny]		::usuniêcie temp(zadanego)
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
	Item *item = head;								//kopia wskaŸnika g³owy
	while (item != nullptr && item->value != value)
		item = item->next;							//przejœcie po liœcie szukaj¹c danego elementu
	return item;									//zwrócenie elementu(je¿eli nie znaleziono zwróci NULL)
}
int MyList::Length()								//pobranie d³ugoœci listy
{
	int i = 0;
	Item * temp = head;						//ustawienie kopii wskaŸnika g³owy
	if (temp != NULL)
	{
		for (i = 1; temp->next != NULL; i++)
			temp = temp->next;				//przejœcie po liœcie zliczaj¹c elementy
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

void MyList::Display()								//wyœwietlanie listy po 6 komórek w wierszu
{
	Item *item = head;						//kopia wskaŸnika g³owy
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
	int size = Length();			//d³ugoœæ listy
	cout << "podaj nazwe pliku: ";
	cin >> name;

	ofstream file;
	file.open(name);
	file << size << " ";
	Item *item = head;				//kopia wskaŸnika g³owy
	for (int i = 0; i < size; i++)
	{
		file << item->value << " ";
		item = item->next;			//przejœcie po liœcie i zapisanie wszystkich elementów do pliku
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

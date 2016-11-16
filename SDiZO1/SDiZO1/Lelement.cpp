//Adrian Frydma�ski - 209865

#include "stdafx.h"
#include "Lelement.h"

////////////////////////////////
//konstruktor
////////////////////////////////
Lelement::Lelement() 
{
	data = 0;
	next = NULL;
}

////////////////////////////////
// wy�wietl dany element
////////////////////////////////
void Lelement::displayElement()
{
	cout << "[" << to_string(this->data) << "]";
}

////////////////////////////////
// wy�wietlanie listy:
////////////////////////////////
void Lelement::display(Lelement* head)
{
	while (head != NULL)								//przej�cie po wszystkich elementach listy
	{
		cout << "[" << head->data << "], ";
		head = head->next;
	}
	cout << '\n';
}

////////////////////////////////
// dodanie elemtu na pocz�tku
////////////////////////////////
void Lelement::addBefore(int k, Lelement *& head)
{
	Lelement * tmp = new Lelement();					//tworzymy tymczasowy
	tmp->data = k;										//nadajemy mu warto��
	tmp->next = head;									//zapisujemy adres poprzedniej g�owy
	head = tmp;											//g�ow� ustanawiamy nowy obiekt
}

////////////////////////////////
// dodanie elemtu na ko�cu
////////////////////////////////
void Lelement::addAfter(int k, Lelement *& head)
{
	if (head != NULL)
	{
		Lelement * tmp = head;
		while (tmp->next != NULL)						//idziemy na koniec listy
		{
			tmp = tmp->next;
		}
		Lelement * newElement = new Lelement();			//tworzymy nowy element
		tmp->next = newElement;							//ustawiamy wskazanie na nowy element
		newElement->data = k;							//ustawiamy warto�� nowego elementu
														//wska�nika na NULL w nowym nie trzeba, 
														//bo jest ustanawiany w konstruktorze
	}
	else Lelement::addBefore(k, *& head);				//je�li g�owa nullem, post�pujemy, jak przy dodawaniu przed
}

////////////////////////////////
// dodanie elementu losowo
////////////////////////////////
void Lelement::addRand(int k, Lelement *& head, int length)
{
	if (head != NULL)
	{
		Lelement * tmp = head;							//tworzymy wska�nik tymczasowy
		int n = 0;
		if (length>0)									//tylko dla g�ugo�ci wi�kszej od 0, by unikn�� dzelenia przez 0
			n = rand() % length;						//losowa nie wi�ksza ni� d�ugo�� listy
		for (int i = 0; i < n; i++)						//idziemy do odpowiedniego miejsca listy
		{
			tmp = tmp->next;
		}
		Lelement * newElement = new Lelement();			//tworzymy nowy element
		newElement->data = k;							//przypisujemy mu dane
		newElement->next = tmp->next;					//wskazujemy nowy na nast�pny po aktualnym
		tmp->next = newElement;							//aktualnemu ustawiamy wska�nik na nowy
	}
	else Lelement::addBefore(k, *& head);				//je�li g�owa nullem, post�pujemy, jak przy dodawaniu przed
}

////////////////////////////////
// usuni�cie pierwszego elementu
////////////////////////////////
void Lelement::delBefore(Lelement *& head)
{
	Lelement * tmp = head;
	if (tmp != NULL)									//je�li g�owa istnieje
	{
		head = head->next;								//wska�nik na head ustawiamy na nast�pny element
		delete tmp;										//usuwany stary head spod tempa
	}

}

////////////////////////////////
// usuni�cie ostatniego elementu
////////////////////////////////
void Lelement::delAfter(Lelement *& head)
{
	Lelement * tmp = head;
	if (tmp->next != NULL)								//je�li nast�pny za g�ow� istnieje
	{
		while (tmp->next->next != NULL)					//idziemy prawie na koniec listy
		{
			tmp = tmp->next;							//wska�nik na tmp ustawiamy na nast�pny element
		}
		delete tmp->next;								//usuwany ostatni element, na kt�ry wskazuje "next" przedostatniego
		tmp->next = NULL;								//i ustawiamy "next'a" na NULL
	}
	else Lelement::delBefore(*&head);					//je�li nie, post�pujemmy jak w w usuwaniu z przodu
	
}

////////////////////////////////
// usuni�cie elementu losowo
////////////////////////////////
void Lelement::delRand(Lelement *& head, int length)
{
	Lelement * tmp = head;								//tworzymy tymczasowy wska�nik
	int n = 0;
	if (length == 1)
		Lelement::delBefore(*&head);					//losowa nie wi�ksza ni� d�ugo�� listy
	else
	{
		n = rand() % (length - 1);
		for (int i = 0; i < n - 1; i++)					//idziemy do odpowiedniego miejsca listy
		{
			tmp = tmp->next;							//wska�nik na tmp ustawiamy na nast�pny element
		}
		Lelement * tmp2 = tmp->next;					//drugi tymczasowy wska�nik
		tmp->next = tmp2->next;							//wska�nik na nast�pny po tymczasowym ustawiamy ma nast�pny po drugim tymczasowym
		delete tmp2;									//usuwany element spod 2. tymczasowego wska�nika
	}
}

////////////////////////////////
// wyszukiwanie
////////////////////////////////
Lelement * Lelement::find(int k, Lelement * head)
{
	if (head != NULL)
		while (head->data != k && head->next != NULL)	//przejd� po li�cie p�ki nie znajdzie si� w�a�ciwy element
		{
			head = head->next;							//wska�nik ustawiamy na nast�pny element
		}
	return (head->data == k ? head : NULL);				//zwracamy znaleziony, albo null
}

////////////////////////////////
// otw�rz
////////////////////////////////
void Lelement::open(string s, Lelement *& head)
{
	s += ".txt";
	ifstream file;
	file.open(s.c_str());
	int length, a;
	file >> length;
	for (int i = 0; i < length; i++)
	{
		file >> a;
		Lelement::addAfter(a, *&head);
	}
	file.close();
}

////////////////////////////////
// zapisz
////////////////////////////////
void Lelement::save(string s, Lelement *& head)
{
	s += ".txt";
	Lelement * tmp = head;
	ofstream file;
	file.open(s.c_str(), ios::app);
	int l = 0;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		l++;
	}
	file << l << endl;;
	tmp = head;
	for (int i = 0; i < l; i++)
	{
		file << tmp->data << endl;
		tmp = tmp->next;
	}
	file.close();
}
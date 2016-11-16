//Adrian Frydmañski - 209865

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
// wyœwietl dany element
////////////////////////////////
void Lelement::displayElement()
{
	cout << "[" << to_string(this->data) << "]";
}

////////////////////////////////
// wyœwietlanie listy:
////////////////////////////////
void Lelement::display(Lelement* head)
{
	while (head != NULL)								//przejœcie po wszystkich elementach listy
	{
		cout << "[" << head->data << "], ";
		head = head->next;
	}
	cout << '\n';
}

////////////////////////////////
// dodanie elemtu na pocz¹tku
////////////////////////////////
void Lelement::addBefore(int k, Lelement *& head)
{
	Lelement * tmp = new Lelement();					//tworzymy tymczasowy
	tmp->data = k;										//nadajemy mu wartoœæ
	tmp->next = head;									//zapisujemy adres poprzedniej g³owy
	head = tmp;											//g³ow¹ ustanawiamy nowy obiekt
}

////////////////////////////////
// dodanie elemtu na koñcu
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
		newElement->data = k;							//ustawiamy wartoœæ nowego elementu
														//wskaŸnika na NULL w nowym nie trzeba, 
														//bo jest ustanawiany w konstruktorze
	}
	else Lelement::addBefore(k, *& head);				//jeœli g³owa nullem, postêpujemy, jak przy dodawaniu przed
}

////////////////////////////////
// dodanie elementu losowo
////////////////////////////////
void Lelement::addRand(int k, Lelement *& head, int length)
{
	if (head != NULL)
	{
		Lelement * tmp = head;							//tworzymy wskaŸnik tymczasowy
		int n = 0;
		if (length>0)									//tylko dla g³ugoœci wiêkszej od 0, by unikn¹æ dzelenia przez 0
			n = rand() % length;						//losowa nie wiêksza ni¿ d³ugoœæ listy
		for (int i = 0; i < n; i++)						//idziemy do odpowiedniego miejsca listy
		{
			tmp = tmp->next;
		}
		Lelement * newElement = new Lelement();			//tworzymy nowy element
		newElement->data = k;							//przypisujemy mu dane
		newElement->next = tmp->next;					//wskazujemy nowy na nastêpny po aktualnym
		tmp->next = newElement;							//aktualnemu ustawiamy wskaŸnik na nowy
	}
	else Lelement::addBefore(k, *& head);				//jeœli g³owa nullem, postêpujemy, jak przy dodawaniu przed
}

////////////////////////////////
// usuniêcie pierwszego elementu
////////////////////////////////
void Lelement::delBefore(Lelement *& head)
{
	Lelement * tmp = head;
	if (tmp != NULL)									//jeœli g³owa istnieje
	{
		head = head->next;								//wskaŸnik na head ustawiamy na nastêpny element
		delete tmp;										//usuwany stary head spod tempa
	}

}

////////////////////////////////
// usuniêcie ostatniego elementu
////////////////////////////////
void Lelement::delAfter(Lelement *& head)
{
	Lelement * tmp = head;
	if (tmp->next != NULL)								//jeœli nastêpny za g³ow¹ istnieje
	{
		while (tmp->next->next != NULL)					//idziemy prawie na koniec listy
		{
			tmp = tmp->next;							//wskaŸnik na tmp ustawiamy na nastêpny element
		}
		delete tmp->next;								//usuwany ostatni element, na który wskazuje "next" przedostatniego
		tmp->next = NULL;								//i ustawiamy "next'a" na NULL
	}
	else Lelement::delBefore(*&head);					//jeœli nie, postêpujemmy jak w w usuwaniu z przodu
	
}

////////////////////////////////
// usuniêcie elementu losowo
////////////////////////////////
void Lelement::delRand(Lelement *& head, int length)
{
	Lelement * tmp = head;								//tworzymy tymczasowy wskaŸnik
	int n = 0;
	if (length == 1)
		Lelement::delBefore(*&head);					//losowa nie wiêksza ni¿ d³ugoœæ listy
	else
	{
		n = rand() % (length - 1);
		for (int i = 0; i < n - 1; i++)					//idziemy do odpowiedniego miejsca listy
		{
			tmp = tmp->next;							//wskaŸnik na tmp ustawiamy na nastêpny element
		}
		Lelement * tmp2 = tmp->next;					//drugi tymczasowy wskaŸnik
		tmp->next = tmp2->next;							//wskaŸnik na nastêpny po tymczasowym ustawiamy ma nastêpny po drugim tymczasowym
		delete tmp2;									//usuwany element spod 2. tymczasowego wskaŸnika
	}
}

////////////////////////////////
// wyszukiwanie
////////////////////////////////
Lelement * Lelement::find(int k, Lelement * head)
{
	if (head != NULL)
		while (head->data != k && head->next != NULL)	//przejdŸ po liœcie póki nie znajdzie siê w³aœciwy element
		{
			head = head->next;							//wskaŸnik ustawiamy na nastêpny element
		}
	return (head->data == k ? head : NULL);				//zwracamy znaleziony, albo null
}

////////////////////////////////
// otwórz
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
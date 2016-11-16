#include "stdafx.h"
#include "Knapsack.h"

Knapsack::Knapsack(int liczbaPrzedmiotow, int rozmiarPlecaka) // konstruktor
{
	this->liczbaPrzedmiotow = liczbaPrzedmiotow;
	this->rozmiarPlecaka = rozmiarPlecaka;

	wagi = new int[liczbaPrzedmiotow];
	wartosci = new int[liczbaPrzedmiotow];

	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		wagi[i] = 0;
		wartosci[i] = 0;
	}
}

Knapsack::~Knapsack() // destruktor
{
	delete[] wagi;
	delete[] wartosci;
}

void Knapsack::setLiczbaPrzedmiotow(int liczbaPrzedmiotow) //seter liczby przedmitów
{
	this->liczbaPrzedmiotow = liczbaPrzedmiotow;
}

void Knapsack::setRozmiarPlecaka(int rozmiarPlecaka) // seter rozmiaru plecaka
{
	this->rozmiarPlecaka = rozmiarPlecaka;
}

void Knapsack::setWagi(int* wagi) // seter wag
{
	this->wagi = wagi;
}

void Knapsack::setWartosci(int* wartosci) // seter wartosci
{
	this->wartosci = wartosci;
}

int Knapsack::getLiczbaPrzedmiotow() // geter lczby przedmiotów
{
	return liczbaPrzedmiotow;
}

int Knapsack::getRozmiarPlecaka() // geter rozmiaru plecaka
{
	return rozmiarPlecaka;
}

int* Knapsack::getWagi() // geter wag
{
	return wagi;
}

int* Knapsack::getWartosci() // geter wartosci
{
	return wartosci;
}

bool Knapsack::dodajPrzedmiot(int index, int weight, int value) // dodawanie przedmiotu
{
	if (index >= liczbaPrzedmiotow)
		return false;

	if (wagi[index] != 0 || wartosci[index] != 0)
		return false;

	wagi[index] = weight;
	wartosci[index] = value;

	return true;
}

void Knapsack::wyswietl() // wyswietlanie plecaka
{
	cout << "LICZBA ELEMENTOW: " << liczbaPrzedmiotow << endl;
	cout << "ROZMIAR PLECAKA: " << rozmiarPlecaka << endl;
	cout << endl;
	cout << "TABLICA WAG(w) I WARTOSCI(v):" << endl;

	cout << "i: ";
	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		cout.width(3);
		cout << i;
		cout << " ";
	}
	cout << endl;

	cout << "w: ";
	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		cout.width(3);
		cout << wagi[i];
		cout << " ";
	}
	cout << endl;

	cout << "v: ";
	for (int i = 0; i < liczbaPrzedmiotow; i++)
	{
		cout.width(3);
		cout << wartosci[i];
		cout << " ";
	}
	cout << endl;
}

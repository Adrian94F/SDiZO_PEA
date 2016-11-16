#include "stdafx.h"
#include "Knapsack.h"

CKnapsack::CKnapsack(int numberOfElements, int backpackSize, double error)
{
	this->numberOfElements = numberOfElements;
	this->backpackSize = backpackSize;
	this->error = error;
	this->items = new item[numberOfElements];

	for (int i = 0; i < numberOfElements; i++)
	{
		items[i].value = 0;
		items[i].weight = 0;
	}
}

CKnapsack::~CKnapsack()
{
	delete[] items;
}

void CKnapsack::setNumberOfElements(int numberOfElements)
{
	this->numberOfElements = numberOfElements;
}

void CKnapsack::setBackpackSize(int backpackSize)
{
	this->backpackSize = backpackSize;
}

void CKnapsack::setError(double error)
{
	this->error = error;
}

void CKnapsack::setItems(item* items)
{
	this->items = items;
}

int CKnapsack::getNumberOfElements()
{
	return numberOfElements;
}

int CKnapsack::getBackpackSize()
{
	return backpackSize;
}

double CKnapsack::getError()
{
	return error;
}

item* CKnapsack::getItems()
{
	return items;
}

/* Dodawanie wagi oraz wartosci przedmiotu o nr 'index' odpowiednio do tabel weights oraz values.
Zwraca true, jesli wykonanie funkcji powiodlo sie lub false, gdy wystapil blad. */
bool CKnapsack::addItem(int index, item item)
{
	if (index >= numberOfElements)
		return false;

	if (this->items[index].weight != 0 || items[index].value != 0)
		return false;
	
	this->items[index].weight = item.weight;
	this->items[index].value = item.value;

	return true;
}

// Drukowanie tabel oraz pol klasy z opisami.
void CKnapsack::print()
{
	std::cout << "LICZBA ELEMENTOW: " << numberOfElements << std::endl;
	std::cout << "ROZMIAR PLECAKA: " << backpackSize << std::endl;
	std::cout << std::endl;
	std::cout << "TABLICA WAG(w) I WARTOSCI(v):" << std::endl;

	std::cout << "i: ";
	for (int i = 0; i < numberOfElements; i++)
	{
		std::cout.width(3);
		std::cout << i;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "w: ";
	for (int i = 0; i < numberOfElements; i++)
	{
		std::cout.width(3);
		std::cout << items[i].weight;
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "v: ";
	for (int i = 0; i < numberOfElements; i++)
	{
		std::cout.width(3);
		std::cout << items[i].value;
		std::cout << " ";
	}
	std::cout << std::endl;
}

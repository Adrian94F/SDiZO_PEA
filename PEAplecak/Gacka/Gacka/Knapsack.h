#pragma once

#include <iostream>

struct item
{
	int weight;
	int value;
};

class CKnapsack
{
private:
	int numberOfElements;
	int backpackSize;
	double error;
	item* items;

public:
	CKnapsack(int numberOfElements, int backpackSize, double error);
	~CKnapsack();

	void setNumberOfElements(int numberOfElements);
	void setBackpackSize(int backpackSize);
	void setError(double error);
	void setItems(item* items);

	int getNumberOfElements();
	int getBackpackSize();
	double getError();
	item* getItems();

	/* Dodawanie wagi oraz wartosci przedmiotu o nr 'index' odpowiednio do tabel weights oraz values.
	Zwraca true, jesli wykonanie funkcji powiodlo sie lub false, gdy wystapil blad. */
	bool addItem(int index, item item);

	// Drukowanie tabel oraz pol klasy z opisami.
	void print();
};


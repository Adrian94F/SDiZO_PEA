#pragma once
#include <iostream>
class Knapsack
{
private:
	int liczbaPrzedmiotow;
	int rozmiarPlecaka;
	int* wagi;
	int* wartosci;
public:
	Knapsack(int liczbaPrzedmiotow, int rozmiarPlecaka);
	~Knapsack();
	void setLiczbaPrzedmiotow(int liczbaPrzedmiotow);
	void setRozmiarPlecaka(int rozmiarPlecaka);
	void setWagi(int* wagi);
	void setWartosci(int* wartosci);
	int getLiczbaPrzedmiotow();
	int getRozmiarPlecaka();
	int* getWagi();
	int* getWartosci();
	bool dodajPrzedmiot(int index, int weight, int value);
	void wyswietl();
};
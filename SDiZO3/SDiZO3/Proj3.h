#pragma once

#include "handle.h"

#include <iostream>
#include <string>

class Proj3
{
private:
	Handle* handle;
	string str_option;
	char c_option;

	void title();
	void problemName(char problem);
	void algorytmName(char problem, char algorytm);

	void error();
	void wrongOption();
	void pointerEmpty();

	void stworzZPliku(char problem);
	void runAlgorithm(char problem, char algorytm);
	void display(char problem);

	void graphFromScratch(char problem);
	void graphRandom(char problem);

	void knapsackFromScratch(char problem);
	void knapsackRandom(char problem);

	void endMenu();
	void problemMenu();
	void debugMenu(char problem);
	void timeTestMenu();
	void runTests(int liczbaPrzedmiotow, int* rozmiarPlecaka, int liczbaMiast);

public:
	Proj3();
	~Proj3();

	void start();
};
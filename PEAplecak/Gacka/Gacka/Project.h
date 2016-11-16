#pragma once

#include "MyHandle.h"

#include <iostream>
#include <fstream>
#include <string>

class CProject
{
private:
	CMyHandle* handle;
	std::string str_option;
	char c_option;

	// Generowanie naglowka.
	void title();

	// Wyswietlanie nazwy algorytmu na podstawie wartoœci parametru 'algorithm'.
	void algorithmName(char algorithm);

	// Wyswietlanie komunikatu o nieznanym bledzie.
	void showError();

	// Wyswietlanie komunikatu o wprowadzeniu nieprawnego nr opcji.
	void wrongOption();

	// Wyswietlenie komunikatu o probie wykonania operacji na nieutworzonej strukturze.
	void pointerEmpty();

	// Tworzenie obiektu klasu CKnapsack z pliku.
	void buildFromFile();

	// Uruchomienie odpowiedniego algorytmu na podstawie parametru 'algorithm'.
	void runAlgorithm(char algorithm);

	// Wyswietlenie obiektu klasy CKnapsack.
	void display();

	// Utworzenie obiektu klasy CKnapsack z konsoli.
	void buildFromScratch();

	// Wygenerowanie losowego obiektu klasy CKnapsack.
	void buildRandom();

	// Wyswietlenie wiadomosci pozegnalnej.
	void endMenu();

	// Wyswietlenie opcji sprawdzajacych poprawnosc.
	void debugMenu();

	// Wyswietlenie dialogu przeprowadzania testow.
	void timeTestMenu();

	// Uruchomienie zestawu testow.
	void runTests(int numberOfElements, int* backpackSize, double error, std::ofstream &output);

public:
	CProject();
	~CProject();

	// Wyswietlenie menu poczatkowego.
	void start();
};


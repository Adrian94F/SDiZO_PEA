#pragma once

#include "MyHandle.h"

#include <iostream>
#include <string>

class CProject
{
private:
	CMyHandle* handle;
	std::string str_option;
	char c_option;

	void title();
	void problemName(char problem);
	void algorithmName(char problem, char algorithm);

	void error();
	void wrongOption();
	void pointerEmpty();

	void buildFromFile(char problem);
	void runAlgorithm(char problem, char algorithm);
	void display(char problem);

	void graphFromScratch(char problem);
	void graphRandom(char problem);

	void knapsackFromScratch(char problem);
	void knapsackRandom(char problem);

	void endMenu();
	void problemMenu();
	void debugMenu(char problem);
	void timeTestMenu();
	void runTests(int numberOfElements, int* backpackSize, int numberOfCities);

public:
	CProject();
	~CProject();

	void start();
};


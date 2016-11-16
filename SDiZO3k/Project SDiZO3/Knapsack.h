#pragma once

#include <iostream>

class CKnapsack
{
private:
	int numberOfElements;
	int backpackSize;
	int* weights;
	int* values;

public:
	CKnapsack(int numberOfElements, int backpackSize);
	~CKnapsack();

	void setNumberOfElements(int numberOfElements);
	void setBackpackSize(int backpackSize);
	void setWeights(int* weights);
	void setValues(int* values);

	int getNumberOfElements();
	int getBackpackSize();
	int* getWeights();
	int* getValues();

	bool addItem(int index, int weight, int value);
	void print();
};


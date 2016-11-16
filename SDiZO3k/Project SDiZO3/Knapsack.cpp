#include "stdafx.h"
#include "Knapsack.h"

CKnapsack::CKnapsack(int numberOfElements, int backpackSize)
{
	this->numberOfElements = numberOfElements;
	this->backpackSize = backpackSize;

	weights = new int[numberOfElements];
	values = new int[numberOfElements];

	for (int i = 0; i < numberOfElements; i++)
	{
		weights[i] = 0;
		values[i] = 0;
	}
}

CKnapsack::~CKnapsack()
{
	delete[] weights;
	delete[] values;
}

void CKnapsack::setNumberOfElements(int numberOfElements)
{
	this->numberOfElements = numberOfElements;
}

void CKnapsack::setBackpackSize(int backpackSize)
{
	this->backpackSize = backpackSize;
}

void CKnapsack::setWeights(int* weights)
{
	this->weights = weights;
}

void CKnapsack::setValues(int* values)
{
	this->values = values;
}

int CKnapsack::getNumberOfElements()
{
	return numberOfElements;
}

int CKnapsack::getBackpackSize()
{
	return backpackSize;
}

int* CKnapsack::getWeights()
{
	return weights;
}

int* CKnapsack::getValues()
{
	return values;
}

bool CKnapsack::addItem(int index, int weight, int value)
{
	if (index >= numberOfElements)
		return false;

	if (weights[index] != 0 || values[index] != 0)
		return false;
	
	weights[index] = weight;
	values[index] = value;

	return true;
}

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
		std::cout << weights[i];
		std::cout << " ";
	}
	std::cout << std::endl;

	std::cout << "v: ";
	for (int i = 0; i < numberOfElements; i++)
	{
		std::cout.width(3);
		std::cout << values[i];
		std::cout << " ";
	}
	std::cout << std::endl;
}

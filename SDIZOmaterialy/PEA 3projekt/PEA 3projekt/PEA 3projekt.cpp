// PEA 3projekt.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <climits>
#include <algorithm>
#include <Windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

__int64 t1;
__int64 t2;
__int64 frequency;

int** cityMatrix;
int cityCount;

vector<int*>* population;
vector<int*>* parents;
vector<int*>* children;

int iterationNumber;
int populationSize;
int parentsPopulationSize;
int childrenPairCount;
double mutationProbability;

int swapsInMutation;

int bestSolution;
double initializationTime;
double choosingBeginningPopulationTime;
double mainLoopTime;
double finalizationTime;

#pragma region basic functions

void measureFrequency()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
}

void startTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&t1);
}

double stopTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&t2);
	return (double)(t2 - t1) / frequency;
}

double getRandomDouble()
{
	return (double)rand() / (double)RAND_MAX;
}

void readATSP(string filename)
{
	ifstream stream;
	stream.open(filename, ios::in);
	stream.seekg(0);

	string line;
	do
	{
		getline(stream, line);
		int i = line.find(':');
		string name, value;
		if (i > 0)
		{
			name = line.substr(0, i);
			value = line.substr(i + 1);

			if (!name.compare("DIMENSION"))
			{
				cityCount = atoi(value.c_str());
			}
		}
	}
	while (line.compare("EDGE_WEIGHT_SECTION"));

	cityMatrix = new int*[cityCount];
	for (int i = 0; i < cityCount; ++i)
	{
		cityMatrix[i] = new int[cityCount];
		for (int j = 0; j < cityCount; ++j)
		{
			stream >> cityMatrix[i][j];
		}
	}

	stream.close();
}

void generateRandomPermutation(int* cityPermutation, int cityCount)
{
	for (int i = 0; i < cityCount; ++i)
	{
		cityPermutation[i] = i;
	}
	for (int i = 0; i < cityCount; i++)
	{
		int r = rand() % (cityCount - i);
		int item = cityPermutation[i];
		cityPermutation[i] = cityPermutation[i + r];
		cityPermutation[i + r] = item;
	}
}

unsigned int calculateCMax(int* cityPermutation)
{
	unsigned int sum = 0;
	for (int i = 0; i < cityCount - 1; ++i)
	{
		sum += cityMatrix[cityPermutation[i]][cityPermutation[i + 1]];
	}
	sum += cityMatrix[cityPermutation[cityCount -1]][cityPermutation[0]];
	unsigned int ret = (UINT_MAX - sum);
	return ret;
}

void coutPermutation(int* cityPermutation, int cityCount)
{
	cout << "< ";
	for (int i = 0; i < cityCount; i++)
	{
		cout << cityPermutation[i] << " ";
	}
	cout << ">\n";
}

void swap(int*& permutation, int idx1, int idx2)
{
	int temp = permutation[idx1];
	permutation[idx1] = permutation[idx2];
	permutation[idx2] = temp;
}

#pragma endregion

#pragma region main functions

void initialize()
{
	population = new vector<int*>();
	population->reserve(populationSize);	
	parents = new vector<int*>();
	parents->reserve(parentsPopulationSize);
	children = new vector<int*>();
	children->reserve(childrenPairCount * 2);

	bestSolution = INT_MAX;
}

void chooseBeginningPopulation()
{
	for (int i = 0; i < populationSize; ++i)
	{
		int* permutation = new int[cityCount];
		generateRandomPermutation(permutation, cityCount);
		population->push_back(permutation);
	}
}

void chooseParents()
{
	parents->clear();

	unsigned long long permutationSum = 0;
	unsigned int* permutationValues = new unsigned int[populationSize];
	unsigned long long currentValue = 0;
	unsigned long long lastValue = 0;

	//Wyliczenie sumy wszytkich funkji przystosowania
	for(int i = 0; i < populationSize; i++)
	{
		permutationValues[i] = calculateCMax(population->at(i));
		permutationSum += permutationValues[i];		
	}

	unsigned long long r;
		
	//Odszukanie funkcji celu odpowiadajacej wylosowanej wartosci
	for(int i = 0; i < parentsPopulationSize; i++)
	{
		r = getRandomDouble() * permutationSum;
		currentValue = 0;
		lastValue = 0;

		for(int i = 0; i < populationSize; i++)
		{
			currentValue += permutationValues[i];

			if (lastValue <= r && r <= currentValue)
			{
				parents->push_back(population->at(i));
				break;
			}
			lastValue += permutationValues[i];
		}
	}

	delete [] permutationValues;
}

void mutate(int* child)
{
	for (int i = 0; i < swapsInMutation; ++i)
	{
		swap(child, rand() % cityCount, rand() % cityCount);
	}
}

void tryMutate(int* permutation)
{
	if (getRandomDouble() < mutationProbability) mutate(permutation);
}

void cross()
{
	int* parent1 = parents->at(rand() % parentsPopulationSize);
	int* parent2 = parents->at(rand() % parentsPopulationSize);

	int* child1 = new int[cityCount];
	int* child2 = new int[cityCount];

	for(int i = 0; i < cityCount; i++)
	{
		child1[i] = parent1[i];
		child2[i] = parent2[i];
	}

	int crossPoint1 = rand() % cityCount;
	int crossPoint2 = rand() % cityCount;

	if (crossPoint1 > crossPoint2)
	{
		int temp = crossPoint2;
		crossPoint2 = crossPoint1;
		crossPoint1 = temp;
	}
	
	for (int i = crossPoint1; i <= crossPoint2; ++i)
	{
		int temp = child1[i];
		child1[i] = child2[i];
		child2[i] = temp;
	}

	for (int i = crossPoint1; i <= crossPoint2; ++i)
	{
		for (int j = 0; j < crossPoint1; j++)
		{
			if (child1[j] == child1[i]) child1[j] = child2[i];
			if (child2[j] == child2[i]) child2[j] = child1[i];
		}
	}

	tryMutate(child1);
	tryMutate(child2);

	children->push_back(child1);
	children->push_back(child2);
}

bool permutationComparator (int* i, int* j) 
{ 
	return calculateCMax(i) < calculateCMax(j); 
}

void chooseNewPopulation()
{
	vector<int*>* newPopulation = new vector<int*>();
	newPopulation->reserve(populationSize);

	sort(population->begin(), population->end(), permutationComparator);
	sort(children->begin(), children->end(), permutationComparator);

	for(int i = 0; i < populationSize; i++)
	{
		//Jesli nie ma juz osobnikow w population
		if(children->empty() && !population->empty())
		{
			newPopulation->push_back(population->back());
			population->pop_back();
			continue;
		}

		//Jesli nie ma juz dzieci
		if(!children->empty() && population->empty())
		{
			newPopulation->push_back(children->back());
			children->pop_back();
			continue;
		}

		//Wybor korzystniejszego
		if(population->back() > children->back())
		{
			newPopulation->push_back(population->back());
			population->pop_back();
		}
		else
		{
			newPopulation->push_back(children->back());
			children->pop_back();
		}
	}

	while(!population->empty())
	{
		delete[] population->back();
		population->pop_back();
	}
	while(!children->empty())
	{
		delete[] children->back();
		children->pop_back();
	}

	delete population;

	population = newPopulation;
}

unsigned int getBestSpecimen()
{
	unsigned int ret = calculateCMax(population->front());
	unsigned int r2 = (UINT_MAX - ret);
	return r2;
}

void finalize()
{
	while(!population->empty())
	{
		delete[] population->back();
		population->pop_back();
	}

	parents->clear();
	population->clear();

	delete parents;
	delete population;
}

#pragma endregion

void GeneticAlgorithm()
{
	
	startTimer();

	initialize();	
	chooseBeginningPopulation();
	startTimer();
	for (int i = 0; i < iterationNumber; ++i)
	{
		chooseParents();
	    // cross robi po jednej parze dzieci
		for(int i = 0; i < childrenPairCount; i++)
		{
			// tu nie ma mutate() bo cross ju¿ robi mutate()
			cross();
		}
		chooseNewPopulation();

		int tmpbest = getBestSpecimen();
		if(tmpbest < bestSolution)
		{
			bestSolution = tmpbest;
		}
	}

	finalize();
	mainLoopTime = stopTimer();
}

int main (int argc, char** argv)
{
	bool debug = true;
	char* filename;
	int n;

	if (!debug)
	{
		if (argc < 7)
		{
			cout << "Call program like this: Genetic.exe [f_tests] [n] [i] [ps] [pps] [cpc] [mp]\n"
				 << "   f_tests - file containing filenames of test files (without .atsp),\n"
				 << "   n - number of times, each test will be run,\n"
				 << "   i - number of iterations of singular test-run,\n"
				 << "   ps - size of specimens population,\n"
				 << "   pps - size of parents population (how much of them will be chosen to breed in one iteration),\n"
				 << "   cpc - count of children pairs (how much of them will be born in one iteration),\n"
				 << "   mp - 0..1 number defining mutation probability of particular child in one iteration.\n";
			return -1;
		}	
		
		filename = argv[1];
		n = atoi(argv[2]);
		iterationNumber = atoi(argv[3]);
		populationSize = atoi(argv[4]);
		parentsPopulationSize = atoi(argv[5]);	
		childrenPairCount = atoi(argv[6]);
		mutationProbability = atoi(argv[7]);
	}
	else
	{
		filename = "tests.txt";
		n = 10;
		iterationNumber = 100;
		populationSize = 100;
		parentsPopulationSize = 50;
		childrenPairCount = 10;
		mutationProbability = 0.05;
	}

	srand(time(0));
	measureFrequency();

	ifstream input = ifstream();
	input.open(filename, ios::in);
	
	string line;
	do
	{
		getline(input, line);
		line.append("rbg403.atsp");
		string outFilename = string(line);
		outFilename.append("aaa.out");

		ofstream output = ofstream();
		output.open(outFilename, ios::out | ios::app);
		output << "iterationNumber,populationSize,parentsPopulationSize,childrenPairCount,mutationProbability,"
			<< "bestSolution,mainLoopTime" << endl;
		output.close();

		cityMatrix = 0;
		cityCount = 0;
		cout << "Reading file " << line << "...\n";
		readATSP(line);
		cout << "File read successfully.\n\n";
		swapsInMutation = (cityCount + 1) / 2; // + 1 daje sufit, jeœli nieparzysta.
		for (int i = 0; i < n; ++i)
		{		
			cout << "Starting algorithm for instance " << line << " for the " << i << ". time.\n";
			GeneticAlgorithm();
			cout << "Algorithm finished!\n";
			
			output.open(outFilename, ios::out | ios::app);
			output << iterationNumber << ',' << populationSize << ',' << parentsPopulationSize << ',' << childrenPairCount << ','
				<< fixed << mutationProbability << ',' << bestSolution << ','<< mainLoopTime << endl;
			output.close();
			cout << "Results written to file.\n";
		}

		for (int i = 0; i < cityCount; ++i)
		{
			delete[] cityMatrix[i];
		}
		delete[] cityMatrix;

		cout << endl;
	}
	while (!input.eof());

	input.close();

	cout << "Finished!";

	if (debug)
	{
		cout << " Press any key...\n";
		getch();
	}

	return 0;
}


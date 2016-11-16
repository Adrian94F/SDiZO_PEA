#pragma once

#include <iostream>

class CNode
{
	int value;
	int weight;
	int bound;
	int level;
	bool* items;

public:
	CNode();
	CNode(int numberOfElements);
	CNode(int value, int weight, int bound, int level, bool* items);
	CNode(CNode* node, int numberOfElements);
	~CNode();

	void setValue(int value);
	void setWeight(int weight);
	void setBound(int bound);
	void setLevel(int level);
	void setItems(bool* items);
	void setItem(bool item, int position);

	int getValue();
	int getWeight();
	int getBound() const;
	int getLevel();
	bool* getItems();

	void addLevel();
	void print(int numberOfElements);
};

struct Comparator
{
	bool operator()(const CNode* node1, const CNode* node2)
	{
		return (node1->getBound() < node2->getBound());
	}
};


#include "stdafx.h"
#include "Node.h"

CNode::CNode()
{
	this->value = 0;
	this->weight = 0;
	this->bound = 0;
	this->level = 0;
	this->items = NULL;
}

CNode::CNode(int numberOfElements)
{
	this->value = 0;
	this->weight = 0;
	this->bound = 0;
	this->level = 0;
	this->items = new bool[numberOfElements];
	for (int i = 0; i < numberOfElements; i++)
		items[i] = false;
}

CNode::CNode(int value, int weight, int bound, int level, bool* items)
{
	this->value = value;
	this->weight = weight;
	this->bound = bound;
	this->level = level;
	this->items = items;
}

CNode::CNode(CNode* node, int numberOfElements)
{
	this->value = node->value;
	this->weight = node->weight;
	this->bound = node->bound;
	this->level = node->level;
	this->items = new bool[numberOfElements];
	for (int i = 0; i < numberOfElements; i++)
		items[i] = node->getItems()[i];
}

CNode::~CNode()
{
	if (items != NULL)
		delete[] items;
}

void CNode::setValue(int value)
{
	this->value = value;
}

void CNode::setWeight(int weight)
{
	this->weight = weight;
}

void CNode::setBound(int bound)
{
	this->bound = bound;
}

void CNode::setLevel(int level)
{
	this->level = level;
}

void CNode::setItems(bool* items)
{
	this->items = items;
}

void CNode::setItem(bool item, int position)
{
	this->items[position] = item;
}

int CNode::getValue()
{
	return value;
}

int CNode::getWeight()
{
	return weight;
}

int CNode::getLevel()
{
	return level;
}

bool * CNode::getItems()
{
	return items;
}

int CNode::getBound() const
{
	return bound;
}

void CNode::addLevel()
{
	level++;
}

void CNode::print(int numberOfElements)
{
	std::cout << "Value: " << value << std::endl;
	std::cout << "Weight: " << weight << std::endl;
	std::cout << "Items: ";
	for (int i = 0; i < numberOfElements; i++)
		std::cout << items[i] << " ";
	std::cout << std::endl;
	std::cout << "Bound: " << bound << std::endl;
	std::cout << std::endl;
}
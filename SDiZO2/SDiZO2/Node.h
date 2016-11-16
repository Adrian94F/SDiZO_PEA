#ifndef NODE_H_
#define NODE_H_
#include <vector>

class Node
{
public:
	std::vector < Node * > next;
	std::vector < Node * > prev;
	std::vector < int > wagiN;
	std::vector < int > wagiP;
	Node();
	~Node();
};

#endif
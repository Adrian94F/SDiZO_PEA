//Adrian Frydmañski - 209865

#ifndef HEAP_H_
#define HEAP_H_

class Heap{
	int * table;
	int length;

public:
	Heap();
	~Heap() {}
	int parent(int);
	int leftSon(int);
	int rightSon(int);
	void top();
	int find(int);
	void add(int);
	void del();
	void display();
	void display(string, string, int);
	void repairFromBottom();
	void repairFromTop();
	void open(string);
	void save(string);
};

#endif
//Adrian Frydmañski - 209865

#ifndef TABLE_H_
#define TABLE_H_

class Table{
	int * table;
public:
	int length;
	Table();
	~Table() {}
	int find(int);
	int addBefore(int);
	int addAfter(int);
	int addRand(int);
	void delBefore();
	void delAfter();
	void delRand();
	void delAll();
	void display();
	void open(string);
	void save(string);
};

#endif
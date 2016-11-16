//Adrian Frydmañski - 209865

#ifndef Lelement_H_
#define Lelement_H_

class Lelement {
public:
	int data;
	Lelement * next;
	Lelement();
	void displayElement();
	static void display(Lelement* );
	static void addBefore(int, Lelement *& );
	static void addAfter(int, Lelement *& );
	static void addRand(int, Lelement *&, int );
	static void delBefore(Lelement *& );
	static void delAfter(Lelement *& );
	static void delRand(Lelement *&, int);
	static Lelement * find(int, Lelement * );
	void open(string, Lelement *& );
	void save(string, Lelement *& );
};

#endif
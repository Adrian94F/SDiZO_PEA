// RPQ_nowe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <ctime>
#include <list>

using namespace std;
int const iloscZadan=15;
int z=0;
int wynik=0;
int UB=10000000;
int LB=0;
class zadanie{
	public:
	int r;
	int p;
	int q;

};
zadanie tab[iloscZadan];


void dumpList(list<int> l)
{
	for(list<int>::iterator iterator=l.begin(); iterator != l.end();iterator++)
		cout << *iterator << " ";
	cout << endl;
}

void permutacje(list<int> &wybrane, list<int> &pozostale)
{
	//cout << "wybrane = ";
	//dumpList(wybrane);
	//cout << "pozostale = ";
	//dumpList(pozostale);
	//cout << endl;
	wynik=0;
	z=0;

	for(list<int>::iterator iterator=wybrane.begin(); iterator != wybrane.end();iterator++)
	{
    //*myIntVectorIterator
		if(z<tab[*iterator].r){
			z=tab[*iterator].r;
		}
		z+=tab[*iterator].p;
		if(wynik<z+tab[*iterator].q)
			wynik=z+tab[*iterator].q;
		
	}
	LB=wynik;
	for(list<int>::iterator iterator=pozostale.begin(); iterator != pozostale.end();iterator++)
		LB=LB+tab[*iterator].p;
	if(UB<wynik || LB>UB){
		//wynik=10000000;
		//z=0;
		return;
	}
	if(wybrane.size()==iloscZadan){
	cout<<"wynik:"<<wynik<<endl;
		if(wynik<UB){
			UB=wynik;
		}
	}
	/*
	for(myIntVectorIterator = myIntVector.begin();myIntVectorIterator != myIntVector.end();myIntVectorIterator++)
	{
		wybrane.push_back(*myIntVectorIterator);
	}
	for(iterator = wybrane.begin(); iterator != wybrane.end();iterator++)
{
    *myIntVectorIterator
    //Should output 1 4 8
}
	*/
	
	for(list<int>::iterator wybrany=pozostale.begin(); wybrany != pozostale.end();wybrany++) {
		wybrane.push_back(*wybrany);
	
		list<int> nowePozostale;
		for(list<int>::iterator iterator=pozostale.begin(); iterator != pozostale.end();iterator++)
			if (iterator != wybrany)
				nowePozostale.push_back(*iterator);

		permutacje(wybrane, nowePozostale);

		wybrane.pop_back();
	}
}




int _tmain(int argc, _TCHAR* argv[])
{
	
	srand (time(NULL));

for (int i=0;i<iloscZadan;i++){

		//cout<<"zadanie: "<<i+1<<endl;
		//cin>>tab[i].r;
		//cin>>tab[i].p;
		//cin>>tab[i].q;

		tab[i].r=rand()%99+1;
		tab[i].p=rand()%99+1;
		tab[i].q=rand()%99+1;
		cout<<"zadanie: "<<tab[i].r<<" "<<tab[i].p<<" "<<tab[i].q<<" "<<endl;
}
	clock_t start = clock();
	list<int> elementy;
	for (int i = 0; i <iloscZadan; i++)
		elementy.push_back(i);
	//cout << "element = ";
	//dumpList(elementy);
	//cout << endl << endl;

	list<int> wybrane;

	permutacje(wybrane, elementy);
	int czas;
	cout<<"NAJLEPSZY WYNIK TO:"<<UB<<endl;
	czas=clock()-start;
	cout<<"Czas wykonywania:"<< clock()-start<<endl;
	cout<<"Czas wykonywania: "<<(int)czas/60000<<" minut "<<czas/1000%60<<" sekund";
	int d2;
	cin>>d2;

	return 0;


}






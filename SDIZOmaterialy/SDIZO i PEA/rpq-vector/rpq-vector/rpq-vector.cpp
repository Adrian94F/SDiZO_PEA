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

void dumpList(vector<int> l)
{
	for (unsigned int i = 0; i < l.size(); i++)
		cout << l[i] << " ";
	cout << endl;
}


void permutacje(vector<int> &wybrane, vector<int> &pozostale)
{
	//cout << "wybrane = ";
	//dumpList(wybrane);
	//cout << "pozostale = ";
	//dumpList(pozostale);
	//cout << endl;
	wynik=0;
	z=0;

	for(int i=0; i < wybrane.size(); i++){
		if(z<tab[wybrane[i]].r){
			z=tab[wybrane[i]].r;
		}
		z+=tab[wybrane[i]].p;
		if(wynik<z+tab[wybrane[i]].q)
			wynik=z+tab[wybrane[i]].q;
		//LB=z;
	}
	LB=wynik;
	for (int i=0; i<pozostale.size(); i++)
		LB=LB+tab[pozostale[i]].p;
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
	*/
	for (unsigned int i = 0; i < pozostale.size(); i++) {
		wybrane.push_back(pozostale[i]);

		vector<int> nowePozostale(pozostale.begin(), pozostale.end());
		nowePozostale.erase(nowePozostale.begin() + i);

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
		cout<<"zadanie: "<<" "<<tab[i].r<<" "<<tab[i].p<<" "<<tab[i].q<<endl;
}
	clock_t start = clock();
	vector<int> elementy(iloscZadan);
	for (int i = 0; i < elementy.size(); i++)
		elementy[i] = i;

	//cout << "element = ";
	//dumpList(elementy);
	//cout << endl << endl;


	vector<int> wybrane;

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






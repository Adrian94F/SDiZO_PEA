// LPT algorytm aproksymacyjny.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <iostream>

const int iloscZadan=10;
int tab[iloscZadan];

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	for(int i=0; i<iloscZadan; i++){
		cout<<"podaj czas zadania "<<i<<endl;
		cin>>tab[i];
	}


	int d;
	cin>>d;

	return 0;
}


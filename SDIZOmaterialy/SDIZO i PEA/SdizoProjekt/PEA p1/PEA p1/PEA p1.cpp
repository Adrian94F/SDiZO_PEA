// dupa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
using namespace std;

    const	int wierzcholki=9;
	const	int krawedzie=18;
            int nieskonczonosc=9;
class Wierzcholek{
	int numer;

};
class Krawedz
{
	int skad;
	int dokad;
	int waga;
public:
	Krawedz(){
		skad=0;
		dokad=0;
		waga=0;
	}
	Krawedz(int nskad, int ndokad, int nwaga){
		skad=nskad;
		dokad=ndokad;
		waga=nwaga;
	}
	friend ostream & operator<< (ostream &wyjscie, const Krawedz &s){
		return wyjscie<<"["<<s.skad<<" , "<<s.dokad<<" , "<<s.waga<<"]";
 }

};
class GrafMac{

		   Krawedz graf[wierzcholki];
	public:
			GrafMac(){
				int rand1;
				int waga;
				int licznik;
				
				for(int i=1; i<wierzcholki+1;){
						rand1=rand()%i;
						if(rand1!=i){
							waga=rand()%10+1;
							graf[i-1]=Krawedz(i,rand1,waga);
							i++;
				}
			}
		}
	void wyswietl(){
		for (int i=0; i<wierzcholki; i++)
		{
			cout<<graf[i]<<endl;
		}
	}

/*
void dodajkrawedz(int wiersz, int kolumna, int waga){
	if(kolumna!=wiersz && wiersz>=0 && kolumna>=0 && wiersz<n && kolumna<n){
	graf[wiersz][kolumna]=waga;
	graf[kolumna][wiersz]=waga;
	}
	else{
		cout<<"error!!!"<<endl;
	}
}

*/
};
int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL));
	GrafMac *dupa= new GrafMac();
	dupa->wyswietl();

	delete dupa;
system("Pause");
	return 0;
}
// dupa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

    const	int n=5;
            int nieskonczonosc=9;
class Krawedz
{
	int skad;
	int dokad;
	int waga;
	
	/*
	int indeks=0;
	Krawedz(int nskad, int ndokad, int nwaga){
		skad=nskad;
		dokad=ndokad;
		waga=nwaga;
		indeks++;
	}
	*/
};
class GrafMac{
      	//int n=5;
      	/*
		int **graf = new int*[n];
		for(int i=0; i<n ; i++){
        graf[i] = new int[n]; 
        }
        */
       int graf[n][n];
public:
		GrafMac(int n){
			
		}
void wypelni(){
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			graf[i][j]=nieskonczonosc;
		}
	}
}
void wyswietl(){
	for (int i=0; i<n; i++)
	{
		cout<<endl;
		for (int j=0; j<n; j++)
		{
		cout<<graf[i][j]<<";";
		}
	}
}
int* Prim(){
     //--------------------------------
     int kopiagraf[n][n];
     for(int i=0; i<n; i++){
             for(int j=0; j<n; j++){
                   kopiagraf[i][j]=graf[i][j];
                   }
             }
     //-----------------------
	int* wynik=new int[n-1];
	int min=nieskonczonosc;
	bool* wiersze= new bool[n];
	int minkolumna=0;
	int minwiersz=0;
	wiersze[0]=true;
	for(int i=1; i<n;i++){
		wiersze[i]=false;
	}
	for(int licznik=0; licznik<n-1 ; licznik++){
		for(int i=0 ; i<n ; i++){
			if (wiersze[i]){
				for(int j=0; j<n ; j++){
				if(min>kopiagraf[i][j]){
					min=kopiagraf[i][j];
					minkolumna=j;
					minwiersz=i;
					}
				}
			}
		}
		kopiagraf[minwiersz][minkolumna]=nieskonczonosc;
    	kopiagraf[minkolumna][minwiersz]=nieskonczonosc;
		wynik[licznik]=min;
		min=nieskonczonosc;
		wiersze[minkolumna]=true;
	}
	delete []wiersze;
return wynik;			
}
void dodajkrawedz(int wiersz, int kolumna, int waga){
	if(kolumna!=wiersz && wiersz>=0 && kolumna>=0 && wiersz<n && kolumna<n){
	graf[wiersz][kolumna]=waga;
	graf[kolumna][wiersz]=waga;
	}
	else{
		cout<<"error!!!"<<endl;
	}
}
};

int _tmain(int argc, _TCHAR* argv[])
{
	GrafMac g(n);
int* tab= new int [n-1];
g.wypelni();
g.dodajkrawedz(0,1,2);
g.dodajkrawedz(0,2,3);
g.dodajkrawedz(1,2,1);
g.dodajkrawedz(1,3,4);
g.dodajkrawedz(2,3,2);
g.dodajkrawedz(2,4,4);
g.dodajkrawedz(3,4,3);
tab=g.Prim();
for (int i=0; i<n-1; i++){
	cout<<tab[i]<<" ;";
	}
cout<<endl;
g.wyswietl();
delete []tab;
system("Pause");
	return 0;
}


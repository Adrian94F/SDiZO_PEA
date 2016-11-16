// dupa2.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
using namespace std;

    const	int n=5;
            int nieskonczonosc=9;

class Krawedz
{
public:
	int skad;
	int dokad;
	//int indeks=0;
	int waga;
	Krawedz(){
	 skad=0;
	 dokad=0;
	 waga=0;

		}
	void wyswietl(){
	cout<<"skad:  "<<skad<<endl;
	cout<<"dokad: "<<dokad<<endl;
	cout<<"waga:  "<<waga<<endl;
	cout<<endl;
	cout<<endl;
	}
	Krawedz(int nskad, int ndokad, int nwaga){
		skad=nskad;
		dokad=ndokad;
		waga=nwaga;
		//indeks++;
	}
		Krawedz* operator =(Krawedz innaKrawedz){
            skad=innaKrawedz.skad;
			dokad=innaKrawedz.dokad;
			waga=innaKrawedz.waga;
			return this;
    }
	
};
//-----------------------------------------------------------------------------
//---------------------------LISTA---------------------------------------------
//-----------------------------------------------------------------------------
class wezel{
public:
	wezel* nastepny;
	Krawedz krawedz;

	wezel(wezel*wezel, Krawedz nkrawedz)
	{
		nastepny=wezel;
		krawedz=nkrawedz;
	}
};

class lista{
public:
	wezel* wezel_1;
	lista(){
	wezel_1=NULL;
	}
	
	void wyswietl(){
		for (wezel* wsk=wezel_1 ; wsk!=NULL ; wsk=wsk->nastepny){
		wsk->krawedz.wyswietl();
		}
	}

	~lista(){
		wezel* wsk=wezel_1;
		wezel* nastepny;

		while (wsk!=NULL) {
			nastepny = wsk->nastepny;
			delete wsk;
			wsk = nastepny;
		}
	}
//---------------------------------------------------------------------------------------
	void sortowanie ()
{
     //int temp;
     for (wezel* wsk=wezel_1 ; wsk!=NULL ; wsk=wsk->nastepny)
     {
		 for (wezel* wsk=wezel_1 ; wsk->nastepny!=NULL ; wsk=wsk->nastepny)
         if (wsk->krawedz.waga > wsk->nastepny->krawedz.waga)
         zamien (wsk->krawedz.waga , wsk->nastepny->krawedz.waga);
	 }
     
}
	void zamien (int & a, int& b)
	{
     int temp=a;
     a=b;
     b=temp;
     }
//---------------------------------------------------------------------------------------
	void usun (int indeks){
		if(indeks==0){
			wezel* nowy_wezel_1=wezel_1->nastepny;
			delete wezel_1;
			wezel_1=nowy_wezel_1;
			return;
		}

		wezel* wsk=wezel_1;
		for( int i=0; i<indeks - 1; i++){
			wsk=wsk->nastepny;
		}

		wezel* nowy_nastepny = wsk->nastepny->nastepny;
		delete wsk->nastepny;
		wsk->nastepny = nowy_nastepny;
	}

	void dodaj(Krawedz krawedz){

    wezel *nowy_wezel = new wezel(wezel_1,krawedz);
    wezel_1 = nowy_wezel;
}
};
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
class GrafMac{

		int graf[n][n];
public:
		lista listaKrawedzi;
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
int Kruskal(lista listakra){
	listakra.sortowanie();
	int max=0;
	for (wezel*wsk=listakra.wezel_1 ; wsk->nastepny!=NULL ; wsk=wsk->nastepny){
		if(max<wsk->krawedz.skad){
			max=wsk->krawedz.skad;
		}
		if(max<wsk->krawedz.dokad){
			max=wsk->krawedz.dokad;
		}
	}
	int* kolory = new int[max];

	for(int i=0 ; i<max ; i++){
		kolory[i] =i;
	}
 
}
void dodajkrawedz(int wiersz, int kolumna, int waga){
	Krawedz nowakrawedz(wiersz,kolumna,waga);
	if(kolumna!=wiersz && wiersz>=0 && kolumna>=0 && wiersz<n && kolumna<n){
	graf[wiersz][kolumna]=waga;
	graf[kolumna][wiersz]=waga;
	listaKrawedzi.dodaj(nowakrawedz);
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
g.listaKrawedzi.wyswietl();
cout<<"--------------------------------------"<<endl;
g.listaKrawedzi.sortowanie();
g.listaKrawedzi.wyswietl();
//tab=g.Kruskal();
//for (int i=0; i<n-1; i++){
//	cout<<tab[i]<<" ;";
//	}
cout<<endl;
g.wyswietl();
delete []tab;
system("Pause");
	return 0;
}
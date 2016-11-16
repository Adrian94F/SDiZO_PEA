// Graf listowy algorytmy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


class Krawedz
{
public:
	int skad;
	int dokad;
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
	void dodajkrawedz(int wiersz, int kolumna, int waga){
	Krawedz nowakrawedz(wiersz,kolumna,waga);
}
};

int _tmain(int argc, _TCHAR* argv[])
{


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


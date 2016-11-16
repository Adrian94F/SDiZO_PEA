// dupa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <math.h>
using namespace std;

class Kopiec{
protected:
	 int *tablica;
	 int koniec;
	 void przywracanie_wlasnosci_kopca(int liczba, int *nowa_tablica){

	 }

public:     Kopiec(int iloscLiczb){
        tablica = new int [iloscLiczb];
        koniec=iloscLiczb;
        //srand ((int) time(NULL));
        for (int i=0; i<iloscLiczb;i++){
			tablica[i]=(koniec-i)*2;
        }
	}
	void dodaj(int liczba){
         koniec++;
        int *nowa_tablica= new int [koniec];
        for(int i=0; i<koniec-1; i++){
            nowa_tablica[i]=tablica[i];
        }
		nowa_tablica[koniec-1]=liczba;
		bool zamiana= false;
		int indeks=koniec-1;
		do {
			zamiana= false;
			if (liczba>nowa_tablica[(int)((indeks)/2)])
			{
				liczba=nowa_tablica[(int)((indeks)/2)];
				nowa_tablica[(int)((indeks)/2)]=nowa_tablica[indeks];
				nowa_tablica[indeks]=liczba;
				indeks=(int)((indeks)/2);
				zamiana=true;
			}
		}
		while (zamiana);
        delete[] tablica;
        tablica=nowa_tablica;
       // delete[] nowa_tablica;
       
    }
	void wyswietl(){
        for (int i=0; i<koniec ;i++){
            cout<<i+1<<". "<<tablica[i]<<endl;
        }

	}
	void wyszukaj (int liczba){
        for(int i=0; i<koniec; i++)
        if (liczba==tablica[i])
        cout<<tablica[i]<<" jest na: "<<i+1<<" pozycji"<<endl;
	}
	 void usun (int pozycja){
        koniec--;
        int *nowa_tablica= new int [koniec];
        for(int i=0; i<pozycja; i++){
            nowa_tablica[i]=tablica[i];
        }
        nowa_tablica[pozycja]= tablica[koniec-1];  

        for(int i=pozycja+1 ; i<koniec; i++){
            nowa_tablica[i]=tablica[i];
        }

        delete[] tablica;
        tablica=nowa_tablica;
       // delete[] nowa_tablica;
       
       
    }
   
};

class Tablica{
    int *tablica;
    int koniec;
public:     Tablica(int iloscLiczb){
        tablica = new int [iloscLiczb];
        koniec=iloscLiczb;
        //srand ((int) time(NULL));
        for (int i=0; i<iloscLiczb;i++){
            tablica[i]=i;
        }

    }
     void wyswietl(){
        for (int i=0; i<koniec ;i++){
            cout<<i+1<<". "<<tablica[i]<<endl;
        }
    }
     void dodaj(int liczba, int pozycja){
         koniec++;
        int *nowa_tablica= new int [koniec];
        for(int i=0; i<pozycja; i++){
            nowa_tablica[i]=tablica[i];
        }
       
            nowa_tablica[pozycja]=liczba;
           
        for(int i=pozycja ; i<koniec-1; i++){
            nowa_tablica[i+1]=tablica[i];
        }
        delete[] tablica;
        tablica=nowa_tablica;
       // delete[] nowa_tablica;
       
    }
    void usun (int pozycja){
        koniec--;
        int *nowa_tablica= new int [koniec];
        for(int i=0; i<pozycja; i++){
            nowa_tablica[i]=tablica[i];
        }
           
        for(int i=pozycja+1 ; i<koniec+1; i++){
            nowa_tablica[i-1]=tablica[i];
        }
        delete[] tablica;
        tablica=nowa_tablica;
       // delete[] nowa_tablica;
       
       
    }
   
    void wyszukaj (int liczba){
        for(int i=0; i<koniec; i++)
        if (liczba==tablica[i])
        cout<<tablica[i]<<" jest na: "<<i+1<<" pozycji"<<endl;
    }

};

int main()
{
    Kopiec *t = new Kopiec(12);
    t->dodaj(13);
	t->dodaj(15);
	t->dodaj(17);
	t->usun(3);
	t->wyswietl();
    delete t;
    system("PAUSE");
    return 0;
}



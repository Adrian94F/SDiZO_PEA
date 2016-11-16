// dupa2.cpp : Defines the entry point for the console application.
//
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
	 void zamien_rodzica(int indeks,int tablica[]){
	//liczba=nowa_tablica[(int)((indeks)/2)-1];
	 int liczba= tablica[indeks];
	 tablica[(int)((indeks)/2)-1]=tablica[indeks-1];
	 tablica[indeks-1]=liczba;
	 indeks=(int)((indeks)/2);

	 }
	 void przywracanie_wlasnosci_kopca(int indeks, int nowa_tablica[]){
		 indeks++;   //problen z numeracja indeksu
		 bool zamiana;
		 int liczba=nowa_tablica[indeks-1];
		do {
			liczba=nowa_tablica[indeks-1];
			zamiana= false;
			if (indeks > 1 && liczba>nowa_tablica[(int)((indeks)/2)-1])
			{
				liczba=nowa_tablica[(int)((indeks)/2)-1];
				nowa_tablica[(int)((indeks)/2)-1]=nowa_tablica[indeks-1];
				nowa_tablica[indeks-1]=liczba;
				indeks=(int)((indeks)/2);

				zamiana=true;
			}
			if (!zamiana && indeks*2-1<koniec){
				if (liczba<nowa_tablica[(indeks-1)*2+1] || liczba<nowa_tablica[(indeks-1)*2+2]){
					zamiana=true;
					if (nowa_tablica[(indeks-1)*2+1]<nowa_tablica[(indeks-1)*2+2] ){
						liczba=nowa_tablica[(indeks-1)*2+2];
						nowa_tablica[(indeks-1)*2+2]=nowa_tablica[indeks-1];
						nowa_tablica[indeks-1]=liczba;
						indeks=(indeks*2+1);
					}
					else
					{
						liczba=nowa_tablica[(indeks-1)*2+1];
						nowa_tablica[(indeks-1)*2+1]=nowa_tablica[indeks-1];
						nowa_tablica[indeks-1]=liczba;
						indeks=(indeks*2);
					}
				}
			}
			
		}
		while (zamiana);
	 }

public:     Kopiec(int iloscLiczb){
        tablica = new int [iloscLiczb];
        koniec=iloscLiczb;
        srand ((int) time(NULL));

		 for (int i=0; i<iloscLiczb;i++){
			 int a=rand()%1000;
			tablica[i]=a;
		 }

        for (int i=0; i<iloscLiczb;i++){
			tablica[i]=(i+1)*2;
  if(i!=0){
	przywracanie_wlasnosci_kopca(i,tablica);
         }
        }
	}
	void dodaj(int liczba){
         koniec++;
        int *nowa_tablica= new int [koniec];
        for(int i=0; i<koniec-1; i++){
            nowa_tablica[i]=tablica[i];
        }
		nowa_tablica[koniec-1]=liczba;
	
		przywracanie_wlasnosci_kopca(koniec-1,nowa_tablica);
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
        nowa_tablica[pozycja]= tablica[koniec];  

        for(int i=pozycja+1 ; i<koniec; i++){
            nowa_tablica[i]=tablica[i];
        }

		przywracanie_wlasnosci_kopca(pozycja,nowa_tablica);

        delete[] tablica;
        tablica=nowa_tablica;
       // delete[] nowa_tablica;
       
       
    }
   
};

int main()
{
	clock_t start , finish;
	double duration;
	int milion=1000000;
	start=clock();
    Kopiec *t = new Kopiec(50*milion);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;
	start=clock();
    t->dodaj(25);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;
	start=clock();
    t->usun(0);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;
	start=clock();
	t->wyszukaj(17);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;

    delete t;
    system("PAUSE");
    return 0;
}

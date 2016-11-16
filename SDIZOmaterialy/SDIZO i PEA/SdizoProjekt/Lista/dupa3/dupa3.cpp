// dupa3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;


class wezel{
public:
	wezel* nastepny;
	int liczba;
	wezel(wezel*wezel, int liczbaa){
		nastepny=wezel;
		liczba=liczbaa;
	}
};

class lista{
	wezel* wezel_1;
public:
	lista(){
	wezel_1=NULL;
	}
	void wyswietl(){
		for (wezel* wsk=wezel_1 ; wsk!=NULL ; wsk=wsk->nastepny){
		cout<<wsk->liczba<<endl;
		}
	}
	void wyszukaj (int liczba){
		int licznik=0;
		for (wezel* wsk=wezel_1 ; wsk!=NULL ; wsk=wsk->nastepny){
		if(liczba== wsk->liczba ){
			//cout<<"liczba znajduje sie na: "<<licznik+1<<"miejscu"<<endl;
			}
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

	void dodaj(int liczba){

    wezel *nowy_wezel = new wezel(wezel_1,liczba);
    wezel_1 = nowy_wezel;
}
};



int main()
{
	clock_t start , finish;
	double duration;
	int milion=1000000;
	start=clock();
	lista* t = new lista();
		srand((int)time(NULL));
	for(int i=0;i<milion;i++){
		int a=rand()%1000;
	 t->dodaj(a);
	}
	
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;
	start=clock();
    t->dodaj(25);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;
	start=clock();
    t->usun(50000);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;
	start=clock();
	t->wyszukaj(500);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;

	delete t;
	system("Pause");
	return 0;
}


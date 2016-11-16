// RPQ.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>


using namespace std;
int const iloscZadan=10;
class zadanie{
	public:
	int r;
	int p;
	int q;

};

int _tmain(int argc, _TCHAR* argv[])
{

	srand (time(NULL));
	zadanie tab[iloscZadan], tab2[iloscZadan];
	
	int sortowanie[iloscZadan];
	for(int i=0; i<iloscZadan ;i++)
		sortowanie[i]=i;

	float max=0;
	float najmniejszymax=100000;//nieskonczonosc
	int z=0,r,starez,zmin=100000,zmax=0;
	int wskaznik;
	int licznik=0;
	bool jestmin=false;
	int suma=0;

	//generowanie zadañ
	//----------------------------------------------------
	for (int i=0;i<iloscZadan;i++){
/*
		cout<<"zadanie: "<<i+1<<endl;
		cin>>tab[i].r;
		cin>>tab[i].p;
		cin>>tab[i].q;
	*/
		tab[i].r=rand()%99+1;
		tab[i].p=rand()%99+1;
		tab[i].q=rand()%99+1;

	cout<<tab[i].r<<" "<<tab[i].p<<" "<<tab[i].q<<" "<<endl;

	//----------------------------------------------------------------
		
		}
			//z=tab[0].r+tab[0].p;
			//starez=z;
			for(int j=0; j<iloscZadan;j++){

				for(int i=0; i<iloscZadan;i++){
					//z=tab[i].r+tab[i].p;
					r=tab[i].r;
					if (r<=zmin && r>zmax){
						zmin=r;
						z=tab[i].r+tab[i].p;
						wskaznik=i;
						jestmin=true;
					}

				}
			if (jestmin){
				jestmin=false;
				if(z<tab[wskaznik].r){
					z=tab[wskaznik].r;
				}
				zmax=zmin;

					suma+=z;
					zmin=1000000;
				}
			}
				cout<<"Warotsc wejsciowa: "<<suma<<endl;

				najmniejszymax=suma;

	sort (sortowanie,sortowanie+iloscZadan);
	 do {
		 	licznik++;  

			for(int i=0; i<iloscZadan ;i++){

				tab2[i]=tab[sortowanie[i]];
			}



			//max=tab2[0].r+tab2[0].p+tab2[0].q;
			z=tab2[0].r+tab2[0].p;
			if (iloscZadan==1)
			{
				cout << max << endl;
				cin>>tab2[0].q;
				return 0;
			}


				max=0;
			for (int i=1;i<iloscZadan;i++){
				if(z<tab2[i].r){
					z=tab2[i].r;
				}
				z+=tab2[i].p;

				if(max<z+tab2[i].q)
					max=z+tab2[i].q;

				if(najmniejszymax<=max){
					break;
				}
			}

			if (najmniejszymax>max)
				najmniejszymax=max;
			cout<<licznik<<" max= "<<max<<endl;
			//------------wypisywanie kolejnosci--------

			for (int i=0; i<iloscZadan;i++){
				cout<<sortowanie[i]<<";";
			
			}
			cout<<endl;

			//------------------------------------------


	} while ( std::next_permutation(sortowanie,sortowanie+iloscZadan) );
	 cout<<"Optymalny max: "<<najmniejszymax<<endl;

	cin>>tab[0].q;
	return 0;
}




// RPQ.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>


using namespace std;
int const iloscZadan=11;
class zadanie{
	public:
	int r;
	int p;
	int q;

};
void BandB(zadanie tab[iloscZadan]){



}

int _tmain(int argc, _TCHAR* argv[])
{

	srand (time(NULL));
	zadanie tab[iloscZadan], tab2[iloscZadan];
	
	int sortowanie[iloscZadan];
	for(int i=0; i<iloscZadan ;i++)
		sortowanie[i]=i;

	float max=0;
	float LB;
	float UB=100000;//nieskonczonosc
	int z=0,r,zmin=100000,zmax=0;
	int wskaznik;
	int licznik=0;
	bool jestmin=false;
	int suma=0;
	//int licznik_rek=iloscZadan;
	//generowanie zadañ
	//----------------------------------------------------
	for (int i=0;i<iloscZadan;i++){

		cout<<"zadanie: "<<i+1<<endl;
		cin>>tab[i].r;
		cin>>tab[i].p;
		cin>>tab[i].q;

	//	tab[i].r=rand()%99+1;
	//	tab[i].p=rand()%99+1;
	//	tab[i].q=rand()%99+1;

	cout<<tab[i].r<<" "<<tab[i].p<<" "<<tab[i].q<<" "<<endl;

	//----------------------------------------------------------------
		
		}
			z=tab[0].r+tab[0].p;

	sort (sortowanie,sortowanie+iloscZadan);
	 do {

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
					max+=z+tab2[i].q;
				LB=max;
				for(int j=i;j<iloscZadan;j++ ){
					LB+=tab2[j].p;
					if(UB<LB){
						break;
					}
				}
				LB+=tab2[iloscZadan-1].q;
									
				if(UB<LB){
					break;
				}

				if(UB<=max){
					break;
				}
			}

			if (UB>max)
				UB=max;
			licznik++;  
			cout<<licznik<<" max= "<<max<<endl;

			cout<<"UB "<<UB<<endl;
			cout<<"LB "<<LB<<endl;
			//------------wypisywanie kolejnosci--------

			for (int i=0; i<iloscZadan;i++){
				cout<<sortowanie[i]<<";";
			
			}
			cout<<endl;

			//------------------------------------------


	} while (next_permutation(sortowanie,sortowanie+iloscZadan) );
	 cout<<"Optymalny max: "<<UB<<endl;

	cin>>tab[0].q;
	return 0;
}






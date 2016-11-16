// RPQ.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>


using namespace std;
int const iloscZadan=3;
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

	float max;
	float najmniejszymax=100000;//nieskonczonosc
	float z,noweZ,stareZ;
	int licznik=0;
	int bufor;
	int tablicaWykonanychKombinacji[iloscZadan][iloscZadan];
	/*
	for(int i=0; i<iloscZadan ;i++){
		for(int j=0; j<iloscZadan ;j++){
			tablicaWykonanychKombinacji[i][j]=-1;
		}
	}
	*/
	int liczniktab=0;
	bool powtorka=false;
	//generowanie zadañ
	//----------------------------------------------------
	for (int i=0;i<iloscZadan;i++){
/*
		cout<<"zadanie: "<<i+1<<endl;
		cin>>tab[i].r;
		cin>>tab[i].p;
		cin>>tab[i].q;
	*/
		tab[i].r=rand()%9+1;
		tab[i].p=rand()%9+1;
		tab[i].q=rand()%9+1;

	//cout<<tab[i].r<<" "<<tab[i].p<<" "<<tab[i].q<<" "<<endl;

	//----------------------------------------------------------------
		
		}

	sort (sortowanie,sortowanie+iloscZadan);
	 do {
		 	licznik++;  

			for(int i=0; i<iloscZadan ;i++){

				tab2[i]=tab[sortowanie[i]];
			}
			
			max=tab2[0].r+tab2[0].p+tab2[0].q;
			z=tab2[0].r+tab2[0].p;
			noweZ=z;
			if (iloscZadan==1)
			{
				cout << max << endl;
				cin>>tab2[0].q;
				return 0;
			}

			for (int i=1;i<iloscZadan;i++){
					stareZ=z;
						if(z<tab2[i].r){
						z=tab2[i].r;
					}
					z+=tab2[i].p;
				
					for (int j=i; j<iloscZadan;++j){
						if(noweZ<tab2[j].r){
							noweZ=tab2[j].r;
						}
						noweZ=stareZ+tab2[j].p;
						if (noweZ<z){
								bufor=sortowanie[j];
								tab2[sortowanie[j]]=tab2[sortowanie[i]];
								sortowanie[j]=sortowanie[i];
								tab2[sortowanie[i]]=tab2[bufor];
								sortowanie[i]=bufor;
								for(int l=0; l<liczniktab ;l++){
									for(int k=0; k<iloscZadan ;k++){
										if(tablicaWykonanychKombinacji[l][k]!=sortowanie[k])
											powtorka=true;
									}
								}
								if(!powtorka)
									z=noweZ;

							}
						}
				for (int k=0;k<iloscZadan;k++){
					tablicaWykonanychKombinacji[liczniktab][k]=sortowanie[k];
					liczniktab++;
				}
				if(max<z+tab2[i].q)
					max=z+tab2[i].q;
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
			powtorka=false;

	} while ( std::next_permutation(sortowanie,sortowanie+iloscZadan) );
	 cout<<"Optymalny max: "<<najmniejszymax<<endl;

	cin>>tab[0].q;
	return 0;
}


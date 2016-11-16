#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <cstdlib>           
#include <windows.h>        

using namespace std;

double czestotliwoscPC = 0.0;
__int64 CounterStart = 0;

void StartCounter(){
        
    LARGE_INTEGER li;    
    if(!QueryPerformanceFrequency(&li))
	std::cout << "QueryPerformanceFrequency failed!\n";

    czestotliwoscPC = double(li.QuadPart)/1000.0;		 

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/czestotliwoscPC;
}




struct Wezel{
	int wartosc;		
	int kolor;			
	
	Wezel *ojciec;		
	Wezel *lewy;		
	Wezel *prawy;		
  
	Wezel(){
		ojciec = lewy = prawy = NULL;       
		
	}
};

class DrzewoRB{

private:
	Wezel *lisc;	      	
	Wezel *korzen;        

public:

	 
	void zwolnij(Wezel *wezel);

	Wezel* nastepca(Wezel *wezel);
	Wezel* minimum(Wezel *wezel);
	 
	int wstaw(int wartosc);                       
	void zrownowaz(Wezel *wezel);                 
      
	void usun(int wartosc);                      
	void napraw(Wezel *wezel);                   
	
	void rotacja_prawo(Wezel *wezel);          
	void rotacja_lewo(Wezel *wezel);            

	Wezel* szukaj(Wezel *tmp,int wartosc);                  
	Wezel* szukaj_iter(int wartosc);                        
	void Szukaj(int wartosc);                              
    
	void wyswietl(Wezel * wezel);
	void Wyswietl();     

	DrzewoRB(){
             
		this->lisc = new Wezel();              
		this->korzen = lisc;             
	}
   
	~DrzewoRB(){
               
		zwolnij(this->korzen);  
		delete(this->lisc);       
	}
};

void DrzewoRB::zwolnij(Wezel *wezel){
	if(wezel != lisc){

		zwolnij(wezel->lewy);          
		zwolnij(wezel->prawy);       
		delete(wezel);             
	}
}

int DrzewoRB::wstaw(int wartosc){
    Wezel *y = lisc;            
    Wezel *tmp = korzen;        
    
    while ( tmp != lisc ){
        y = tmp;
		if ( wartosc < tmp->wartosc ){
				tmp = tmp->lewy;
		}
		else if (wartosc> tmp->wartosc){
				tmp = tmp->prawy;
		}
        else
            return -1;
    }
    
    Wezel *nowy = new Wezel;
	nowy->ojciec = y;

    if ( y == lisc ){
		nowy->wartosc = wartosc;
        korzen = nowy;
		
	}
    else
    {        
		if ( wartosc < y->wartosc){
			nowy->wartosc = wartosc;   
            y->lewy = nowy;
		}
        else if(wartosc > y->wartosc){
			nowy->wartosc = wartosc;
            y->prawy = nowy; 
		}
    }    
	
	nowy->lewy =  lisc;
	nowy->prawy = lisc;

	nowy->kolor = 1;
	
	zrownowaz(nowy);

    return 0;

}

void DrzewoRB::zrownowaz(Wezel *wezel){

	Wezel *tmp;
	
	while((wezel->ojciec->kolor == 1)&&(wezel != korzen)){
		
		if(wezel->ojciec == wezel->ojciec->ojciec->lewy){

			tmp = wezel->ojciec->ojciec->prawy;

			if(tmp->kolor == 1){

				wezel->ojciec->kolor = 0;
				tmp->kolor = 0;
				wezel->ojciec->ojciec->kolor = 1;
				wezel = wezel->ojciec->ojciec; 
			}
			else 
				{
				if(wezel == wezel->ojciec->prawy){

					wezel = wezel->ojciec;
					rotacja_lewo(wezel);
				}
			
				wezel->ojciec->kolor = 0;
				wezel->ojciec->ojciec->kolor = 1;
				rotacja_prawo(wezel->ojciec->ojciec); 

			}
			
		}
		else
		{
			tmp = wezel->ojciec->ojciec->lewy;

			if(tmp->kolor == 1){
				wezel->ojciec->kolor = 0;
				tmp->kolor = 0;
				wezel->ojciec->ojciec->kolor = 1;
				wezel = wezel->ojciec->ojciec;
			}
			else 
				{
				if(wezel == wezel->ojciec->lewy)
				{
					wezel = wezel->ojciec;
					rotacja_prawo(wezel);
				}
			
				wezel->ojciec->kolor = 0;
				wezel->ojciec->ojciec->kolor = 1;
				rotacja_lewo(wezel->ojciec->ojciec);
			}
		}
	}
	
	korzen->kolor = 0;
	tmp = NULL;
	
}

void DrzewoRB::rotacja_lewo(Wezel *wezel){
	Wezel *tmp ;
	tmp = wezel->prawy; 

	wezel->prawy = tmp->lewy;
	tmp->lewy->ojciec = wezel;
	tmp->ojciec = wezel->ojciec;

	if(wezel->ojciec == lisc){
		korzen = tmp;
	}
	else if(wezel == wezel->ojciec->lewy){
		wezel->ojciec->lewy = tmp;
	}
	else
	{
		wezel->ojciec->prawy = tmp;
	}
   
	tmp->lewy = wezel;         
	wezel->ojciec = tmp;
}

void DrzewoRB::rotacja_prawo(Wezel *wezel){
    
	Wezel *tmp ;
	tmp = wezel->lewy;	

	wezel->lewy = tmp->prawy;
	tmp->prawy->ojciec = wezel;
	tmp->ojciec = wezel->ojciec;

	if(wezel->ojciec == lisc){
		korzen = tmp;
	}
	else if(wezel == wezel->ojciec->prawy){
		wezel->ojciec->prawy = tmp;
	}
	else
	{
		wezel->ojciec->lewy= tmp;
	}

	tmp->prawy = wezel;
	wezel->ojciec = tmp;
}

Wezel* DrzewoRB::minimum(Wezel *wezel){
       
	while(wezel->lewy != lisc){
		wezel = wezel->lewy;
	}

	return wezel;
}

Wezel* DrzewoRB::nastepca(Wezel *wezel){

	if(wezel->prawy != lisc){
		return minimum(wezel->prawy);
	}

	Wezel * tmp ;
	tmp = wezel->ojciec;

	while((wezel == tmp->prawy) && (tmp != lisc)){
		wezel = tmp;           
		tmp = tmp->ojciec;      
	}
	
	return tmp;
}

void DrzewoRB::usun(int wartosc){
	Wezel *wezel;
	
	wezel = szukaj(korzen,wartosc);
	Wezel *y;
	Wezel *tmp;

	if(wezel->lewy == lisc || wezel->prawy == lisc){
		y = wezel;
	}
	else
	{
		y = nastepca(wezel); 
	}

	if(y->lewy != lisc){
		tmp = y->lewy;
	}
	else
	{
		tmp = y->prawy;
	}

	tmp->ojciec = y->ojciec;
	if(y->ojciec == lisc){
		korzen = tmp;
	}
	else
	{
		if(y == y->ojciec->lewy){
			y->ojciec->lewy = tmp;
		}
		else
		{
			y->ojciec->prawy = tmp;         
		}
	}

	if(y != wezel){
		wezel->wartosc = y->wartosc;               
	}
	

	if(y->kolor == 0){
		napraw(tmp);
	}
}

void DrzewoRB::napraw(Wezel *wezel){
	Wezel *tmp;

	while((wezel != korzen) && (wezel->kolor == 0)){

		if(wezel == wezel->ojciec->lewy) {

			tmp = wezel->ojciec->prawy;
			if(tmp->kolor == 1) {
				tmp->kolor = 0;
				wezel->ojciec->kolor = 1;
				rotacja_lewo(wezel->ojciec);
				tmp = wezel->ojciec->prawy;
			}
			if((tmp->lewy->kolor == 0) && (tmp->prawy->kolor == 0)) //jesli lewy syna tymczasowego jest czarny i prawy czarny
			{
				tmp->kolor = 1;        // tymczasowego kolorujemy na czerwono
				wezel = wezel->ojciec; // za wezle przypisujemy jego ojca
			}
			else if(tmp->prawy->kolor = 0) // albo jesli tylko prawy jest czarny
			{
				tmp->lewy->kolor = 0;   // za lewgo czarny
				tmp->kolor = 1;         // tymczasowego na czerwono
				rotacja_prawo(tmp);        // naprawiamy poprzez rotacje w prao tymczaswoego
				tmp = wezel->ojciec->prawy;              // za tymczasowego przypisujemy prawego syna ojca wezla
			}

			tmp->kolor = wezel->ojciec->kolor;              // za tymczasowego kolor przypisujme kolor jego ojca
			wezel->ojciec->kolor = 0;                        //kolor ojca na czarno
			tmp->prawy->kolor = 0;                            // tymczasowego prawego syna an czarno
			rotacja_lewo(wezel->ojciec);                   // wykonumeyrotacje w lewo ojca wezla
			wezel = korzen;                                   // za wezle przypisujemy korzen

		}
		else // w pzeciwnym wypadku wykoujemy analogicznie tylko ze z zamina prawego z lewym
		{
			tmp = wezel->ojciec->lewy;
			if(tmp->kolor == 1)
			{
				tmp->kolor = 0;
				wezel->ojciec->kolor = 1;
				rotacja_prawo(wezel->ojciec);
				tmp = wezel->ojciec->lewy;
			}
			if((tmp->prawy->kolor == 0) && (tmp->lewy->kolor == 0))
			{
				tmp->kolor = 1;
				wezel = wezel->ojciec;
			}
			else if(tmp->lewy->kolor = 0)
			{
				tmp->prawy->kolor = 0;
				tmp->kolor = 1;
				rotacja_lewo(tmp);
				tmp = wezel->ojciec->lewy;
			}

			tmp->kolor = wezel->ojciec->kolor;
			wezel->ojciec->kolor = 0;
			tmp->lewy->kolor = 0;
			rotacja_prawo(wezel->ojciec);
			wezel = korzen;
		}

	}
	wezel->kolor = 0;

}

void DrzewoRB::wyswietl(Wezel *w){
	if(w != lisc){
		wyswietl(w->lewy);
		std::cout << w->wartosc << " ";
		wyswietl(w->prawy);

	}
}

void DrzewoRB::Wyswietl(){
	wyswietl(korzen);
}

void DrzewoRB::Szukaj(int wartosc){
	szukaj(korzen,wartosc);
}

Wezel* DrzewoRB::szukaj(Wezel *tmp,int wartosc){
	//Wezel *tmp =
	if(tmp == lisc || wartosc == tmp->wartosc)  // jest tymczasowa ( zaczynam od korzenia jest liscie lub jest ronwa wartosc )
	{
		return tmp;  
	}
	else if(wartosc < tmp->wartosc)  //jesli mniejsza 
	{
		tmp = tmp->lewy;
		return szukaj(tmp,wartosc); // wywolujemy funkjce od lewgo syna 
	}
	else // lub wywyolujemy od prawego
	{
		tmp = tmp->prawy;
		return szukaj(tmp,wartosc); 
	}

}
////////////////////////////////////////////////////////////////////////////////////////
// FUNKCJA szukaj iteracyjnie /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
Wezel* DrzewoRB::szukaj_iter(int wartosc)
{
       //szuka wartosci podanej
	Wezel *tmp = korzen;         //utworzenie tymczasowej i przypisaniej jej korzenia
	while(tmp != lisc && wartosc != tmp->wartosc) // dopoki tymcasowa nei bedzie lisciem i wartosc bedzie rozna od wartoci tymczasowej
	{
              //przeszukiwanie, i porónywanie wartosci z wezlami
		if(wartosc < tmp->wartosc) // jesli mniejsz to idziemy w lewo
		{
			tmp = korzen->lewy;
		}
		else  // w przeciwnym wypadku w prawo
		{
			tmp = tmp->prawy;
		}
	}

	return tmp;
}
////////////////////////////////////////////////////////////////////////////////////////


/**************************************************************************************/
///////// MAIN - TESTOWANIE DRZEWA CZERWONO-CZARNEGO ////////////////////////////////////
/***********************************************************************************/
int _tmain(int argc, _TCHAR* argv[])
{

	DrzewoRB drzewo;
	clock_t start, finish;
	int milion=1000000;
	double duration;
	int ile_liczb=25*milion;
	srand((unsigned int)time(NULL));
	
   // std::cin >> ile_liczb;
	start=clock();
	srand ((int)time(NULL));
	for(int i = 0; i < ile_liczb; i ++)
	{
		int a=rand()%1000;
			drzewo.wstaw(a);	
	}
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;


	start=clock();
	drzewo.usun(500);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;

	start=clock();
	drzewo.wstaw(500);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;
	
	start=clock();
	drzewo.Szukaj(500);
	finish=clock();
	duration= (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"czas " <<duration<<endl;	

	//StartCounter();
	//drzewo.wstaw(ile_liczb);
    //cout << GetCounter() <<"\n";
	
	system("PAUSE");
	return 0;
}
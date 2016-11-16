#include "tabu.h"

tabu::tabu(sasiad* p  , int roz)
{
	this->perm = p;

	this->taburozmiar = roz;
	this->Tabtabu = new int[this->taburozmiar];
	
	for(int j = 0 ;j<taburozmiar;j++ )
		this->Tabtabu[j]=-1;

}

bool tabu::tabulist( int zadanie1, int zadanie2 )
{
	int pom1=-1 , pom2=-1;
	for(int j = 0 ;j<taburozmiar;j=j+2 )
	{
		pom1=this->Tabtabu[j];
		pom2=this->Tabtabu[j+1];
		if(pom1==zadanie1 && pom2==zadanie2)
			return false;
	}
	return true;
}

void tabu::algorytmtabu()
{
	int i = 0;
	int czas = -1;		 //najlepszy czas przy przeszukiwaniu sasiedztwa
	int naj1 =-1;		 //najlepsze pierwsze zadanie do zamiany
	int naj2 =-1;		 // najlepsze drugie zadanie do zamiany
	while( i < 10 )
	{
		
		for(int j = 0 ; j < this->perm->liczbazadan ; j++)
		{
			for(int k = j+1 ; k < this->perm->liczbazadan ; k++)
			{
				if(this->tabulist(k ,j)==true)
				{
					this->perm->ustaw(j,k);			
					if(czas==-1 || czas> this->perm->obliczopoz())
					{
						czas=this->perm->obliczopoz(); //ustawienie nowego najlepszego czasu oraz rozwi¹zañ
						naj1=j;
						naj2=k;
					}
					this->perm->nieakceptuj();
				}
			}
		}
		this->perm->ustaw(naj1,naj2);
		for(int j = this->taburozmiar-1 ; j >1 ; j--)
		{
			this->Tabtabu[j]=this->Tabtabu[j-2];	
		}
		this->Tabtabu[0]=this->perm->pomiar[naj2];
		this->Tabtabu[1]=this->perm->pomiar[naj1];

		int pom = this->perm->obliczopoz();

		if( this->perm->najlepszy() > pom )
		{
			this->perm->akceptuj();
			i=0;
		}
			
		else
		{
			this->perm->nieakceptuj();
			i++;
		}
		
	}

}

tabu::~tabu(void)
{
	if( this->perm != 0 )
	{
		delete this->perm;
		this->perm = 0;
	}
	delete this->Tabtabu;
}

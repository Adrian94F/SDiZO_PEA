#include "stdafx.h"
#include "MatGraph.h"

MatGraph::MatGraph(int wierzcholki, int gestosc)
{
	A = new signed int *[wierzcholki];
	w = wierzcholki;
	int w1, w2, waga;
	wagi = new signed int[0];
	int kMax = wierzcholki*(wierzcholki - 1) / 2;
	int krawedzie = (float)(gestosc*kMax) / 100.0;
	if (krawedzie < w)
		krawedzie = w;
	cout << "w: " << w << "\nkMax: " << kMax << "\nkrawedzie: " << krawedzie;
	for (int i = 0; i < w; i++)
	{
		A[i] = new signed int[k]; // wiersze tablicy (k = 0)
	}
	int i = 0;
	while (i < krawedzie) //dodanie odpowiedniej liczby kraw�dzi
	{
		int j, waga;
		do
		{
			j = i;
			while (j == i)
				j = rand() % w;
			waga = 0;
			while (waga == 0)
				waga = rand() % 10;
			if (k == 0) 
				dodajKrawedz(i%w, j, waga);
		} while (czyJestKrawedz(i%w, j));
		dodajKrawedz(i%w, j, waga);
		i++;

	}	
	cout << "\nk: " << k << endl;
}

MatGraph::MatGraph(int wierzcholki)
{
	A = new signed int *[wierzcholki];
	w = wierzcholki;
	wagi = new signed int[0];
	for (int i = 0; i < w; i++)
		A[i] = new signed int[k]; // wiersze tablicy - wierzcholki
}

void MatGraph::pokazMacierz()
{
	int komorka = 4;
	cout << setw(komorka) << "w\\k";
	for (int i = 0; i < k; i++) 
		cout << setw(komorka) << i;
	cout << endl;
	for (int i = 0; i < w; i++)
	{
		cout << setw(komorka) << i;
		for (int j = 0; j < k; j++) 
			cout << setw(komorka) << A[i][j];
		cout << endl;
	}
	cout << setw(komorka) << "wagi";
	for (int i = 0; i < k; i++)
		cout << setw(komorka) << wagi[i];
	cout << endl;
}

void MatGraph::usunMacierz()
{
	for (int i = 0; i < w; i++) 
		delete[] A[i];
	delete[] A;
}

void MatGraph::dodajKrawedz(int poczatek, int koniec, int waga)
{
	signed int ** A1 = new signed int *[w];
	int * wagi1 = new signed int[k+1];

	for (int i = 0; i < w; i++)
		A1[i] = new signed int[k+1];	// wiersze tablicy

	for (int i = 0; i < w; i++)			// kopiowanie macierzy
		for (int j = 0; j < k; j++)
			A1[i][j] = A[i][j];
	for (int i = 0; i < w; i++)
		A1[i][k] = 0;
	for (int i = 0; i < k; i++)			//zerowanie wag
		wagi1[i] = wagi[i];
	// dodanie nowej kraw�dzi z now� wag�
	A1[poczatek][k] = 1;
	A1[koniec][k] = -1;
	wagi1[k] = waga;

	//usun stara macierz, je�li istnia�a
	usunMacierz();
	//przypisz nowe
	k++;
	A = A1;
	wagi = wagi1;
}

void MatGraph::zapis(string nazwa)
{
	nazwa += ".txt";
	ofstream file;
	file.open(nazwa.c_str(), ios::out);
	file << k << " " << w << '\n';
	for (int i = 0; i < k; i++)
	{
		int poczatek = 0, koniec = 0;
		for (int j = 0; j < w; j++)
		{
			if (A[j][i] == 1)
				poczatek = j;
			else if (A[j][i] == -1)
				koniec = j;
		}
		file << poczatek << " " << koniec << " " << wagi[i] << endl;
	}
	file.close();
}

void MatGraph::odczyt(string nazwa)
{
	nazwa += ".txt";
	usunMacierz();
	int kraw = 0;
	w = 0;
	ifstream file;
	int poczatek, koniec, waga;
	file.open(nazwa.c_str());
	file >> kraw >> w;

	A = new signed int *[w];
	wagi = new signed int[0];
	for (int i = 0; i < w; i++)
		A[i] = new signed int[k]; // wiersze tablicy - wierzcholki

	for (int i = 0; i < kraw; i++)
	{
		file >> poczatek >> koniec >> waga;
		dodajKrawedz(poczatek, koniec, waga);
	}
	file.close();
}

bool MatGraph::czyJestKrawedzPomiedzy(int j, vector <int> wierzcholki)
{
	bool jest1 = false, jest2 = false;
	int w_[2];
	for (int l = 0; l < w; l++)
	{
		if (A[l][j] == 1) // je�li krawedz laczy sie z danym wierzcholkiem...
		{
			w_[0] = l;
		}
		if (A[l][j] == -1) // je�li krawedz laczy sie z danym wierzcholkiem...
		{
			w_[1] = l;
		}
	}
	for (int m = 0; m < wierzcholki.size(); m++) // sprawdza, czy dany wierzcholek jest ju�
		if (wierzcholki[m] == w_[0])
			jest1 = true;
		else if (wierzcholki[m] == w_[1])
			jest2 = true;
	return (jest1 && jest2);
}

bool MatGraph::czyJestKrawedz(int w1, int w2)
{
	for (int i = 0; i < k; i++)
		if (A[w1][i] == -A[w2][i]) //czy mi�dzy dwoma wierzcho�kami jest ju� kraw�d�?
			return true;
	return false;
}

string MatGraph::prim()
{
	vector <int> wierzcholki; //indeksy wierzcho�k�w w drzewie
	vector <int> krawedzie; //indeksy kraw�dzi drzewa
	int najkrotszaStart = 0, najkrotszaStop = 0, najkrotszaWaga, najkrotsza; // najkr�tsza �cie�ka
	wierzcholki.push_back(0);
	while (wierzcholki.size() < w) //r�b, p�ki nie b�dzie wszystkich wierzcho�k�w
	{
		najkrotszaWaga = INT_MAX; //najkrotsza jest maksymalna, bo sprawdzamy za kazdym razem wszystkie
		for (int i = 0; i < wierzcholki.size(); i++) // sprawdzamy wszystkie wierzcho�ki
		{
			for (int j = 0; j < k; j++) // przechodzimy po kraw�dziach, poni�ej sprawdzamy, czy nale�� do tego wierzcho�ka
			{
				// jesli dana krawedz laczy dwa wierzcholki, kt�re ju� mamy, pomijamy j�
				if (!czyJestKrawedzPomiedzy(j, wierzcholki))
				{
					if (wagi[j] <= najkrotszaWaga) // je�li znaleziona kr�tsza, od najkr�tszej...
					{
						najkrotszaWaga = wagi[j]; // nowa najkrotsza waga
						najkrotszaStart = wierzcholki[i]; // nowy wierzcho�ek poczatkowy
						// potrzebujemy wierzcho�ka ko�cowego
						for (int l = 0; l < w; l++)
						{
							if (A[l][j] != 0 && A[l][j] != najkrotszaStart) // je�li krawedz laczy sie z danym wierzcholkiem i jest on r�ny od pocz�tkowego
							{
								najkrotszaStop = l; //koncowy wierzcholek
								najkrotsza = j; // indeks najkrotszej krawedzi
							}
						}
						
					}
				}
			}
		}
		//sprawdzili�my wszystkie wierzcho�ki, mamy najkrotsza krawedz i dodatkowy wierzcho�ek
		wierzcholki.push_back(najkrotszaStop); //dodajemy wierzcholek
		krawedzie.push_back(najkrotsza); //dodajemy krawedz
		//na najmniejsze drzewo rozpinajace sklada� si� b�dzie zbi�r kraw�dzi mi�dzy wierzcho�kami
	}
	string s = "Minimalne drzewo rozpinajace sklada sie z krawedzi o indeksach:";
	for (int i = 0; i < krawedzie.size(); i++)
	{
		s += ' ';
		s += to_string(krawedzie[i]);
	}
	s += '.';
	return s;
}
#include "Header.h"

unsigned long long int PlecakBrute(vector<int> sizes, vector<int> values, int totalsize, int itemsnum)
{
	MyTimer timer;
	timer.Start();
	long long int max = 0, wynik_index = 0;
	for (int i = 0; i < ((long long)1 << itemsnum); i++)
	{
		int j = i, k = 0, s = 0, r = 0;
		while (j > 0)
		{
			if (j & 1)
			{
				s += values[k];
				r += sizes[k];
			}
			j >>= 1; k++;
		}
		if (r <= totalsize && s > max)
		{
			max = s;
			wynik_index = i;
		}
	}
	return wynik_index;
}
vector<short> PlecakDynamic(vector<int> sizes, vector<int> values, int totalsize, int itemsnum)
{
	vector<vector<int>>p(itemsnum + 1, vector<int>(totalsize + 1, 0)); // tabela
	vector<short> wynik; // rozwiązanie

	// wypełnianie tabeli
	for (auto i = 1; i <= itemsnum; i++)
	{
		for (auto j = 1; j <= totalsize; j++)
		{
			if (j >= sizes[i - 1] && p[i - 1][j] < p[i - 1][j - sizes[i - 1]] + values[i - 1])
			{
				p[i][j] = p[i - 1][j - sizes[i - 1]] + values[i - 1];
			}
			else
			{
				p[i][j] = p[i - 1][j];
			}
		}
	}
	// odczyt rozwiązania
	for (auto i = itemsnum, j = totalsize; i >= 1 && j > 0; i--)
	{
		if (p[i][j] != p[i - 1][j])
		{
			j = j - sizes[i - 1];
			wynik.push_back(i - 1);
		}
	}
	// zwrócenie rozwiązania
	return wynik;
}
vector<short> PlecakFPTAS(vector<int> sizes, vector<int> values, int totalsize, int itemsnum, float epsilon)
{
	int bestValue = 0;
	int maxValue = 0;
	double scale;
	int size = sizes.size();

	vector <bool> bestChoice(size);
	vector <vector <int>> table(size+1);

	for (int i = 0; i < size; i++)
	{
		bestChoice[i] = false;
	}

	for (int i = 0; i < size; i++)
		if (maxValue < values[i])
			maxValue = values[i];

	scale = (epsilon * maxValue) / (double)size;

	maxValue = (double)maxValue / scale;

	for (int i = 0; i < size; i++)
	{
		values[i] = floor((double)values[i] / scale);
		table[i].resize(size * maxValue + 1);
	}
	table[size].resize(size * maxValue + 1);

	for (int i = 0; i <= size; i++)
		table[i][0] = 0;
	for (int i = 1; i <= size * maxValue; i++)
		table[0][i] = INT_MAX;

	/*for (int k = 1; k < size; k++)
		for (int y = 0; y < size * maxValue; y++)
			table[k][y] = min(table[k - 1][y], table[k - 1][y - values[k]] + sizes[k]);

	int y = 0;
	do
	{
		++y;
		for (int k = 1; k <= size; k++)
		{
			if (y - values[k] < 0 || table[k - 1][y - values[k]] == INT_MAX)
				table[k][y] = table[k - 1][y];
			else table[k][y] = min(table[k - 1][y], table[k - 1][y - values[k]] + sizes[k]);
			if (table[size][y] <= totalsize)
				bestValue = y;
		}
	} while (y < size * maxValue);*/

	for (int i = 1; i <= (size * maxValue); i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (i < values[j - 1])
				table[j][i] = table[j - 1][i];
			else if (table[j - 1][i - values[j - 1]] == INT_MAX)
				table[j][i] = table[j - 1][i];
			else
				table[j][i] = table[j - 1][i] < table[j - 1][i - values[j - 1]] + sizes[j - 1] ? table[j - 1][i] : table[j - 1][i - values[j - 1]] + sizes[j - 1];
		}
		if (table[size][i] <= totalsize)
		{
			bestValue = i;
		}
	}

	for (int k = size-1; k >= 0; k--)
	{
		if (bestValue - values[k] >= 0)
		{
			if (table[k+1][bestValue] == table[k][bestValue - values[k]] + sizes[k])
			{
				bestChoice[k] = true;
				bestValue = bestValue - values[k];
			}
			cout << k << ": " << bestChoice[k] << ", ";
		}
	}
	cout << '\n';

	vector<short> wynik; // rozwiązanie
	wynik.resize(0);
	for (int i = 0; i < size; i++)
		if (bestChoice[i])
			wynik.push_back(i);
	for (int i = 0; i < wynik.size(); i++)
		cout << wynik[i] << " ";
	cout << '\n';

	// zwrócenie rozwiązania
	return wynik;
}
void PlecakLoad(ifstream &file, vector<int> &sizes, vector<int> &values, int &totalsize, int &itemsnum) //wczytanie listy z pliku
{
	int size, weight;
	sizes.resize(0);							//wyczyszczenie starej listy
	values.resize(0);							//wyczyszczenie starej listy
	file >> itemsnum;

	while (!file.eof())
	{
		file >> size;						// pobranie rozmiaru
		file >> weight;						// pobranie wartości
		sizes.push_back(size);				//dodanie pobranych wartości na koniec listy
		values.push_back(weight);
	}
	cout << "Proszę podać wielkość plecaka: ";
	cin >> totalsize;
	file.close();
	cout << "\nWczytano (" << itemsnum << ") elementów\n";
}
void PlecakDisplay(vector<int> sizes, vector<int> values, int totalsize, int itemsnum)
{
	cout << "\nLista rzeczy do upakowania w plecaku o pojemności (" << totalsize << "):\n"
		<< setw(13) << "(rozmiar) " << "(wartość)" << endl;
	for (int i = 0; i < itemsnum; i++)
	{
		cout << setw(10) << sizes[i] << " ";
		cout << setw(10) << values[i] << endl;
	}
}
void PlecakDisplaySolution(unsigned long long &wynik, vector<int> sizes, vector<int> values, int totalsize, int itemsnum)
{
	int sumar = 0, sumaw = 0;
	cout << "Lista najcenniejszych rzeczy możliwych\ndo upakowania w plecaku o pojemności (" << totalsize << "):\n"
		<< setw(13) << "(rozmiar) " << "(wartość)" << endl;

	for (int i = 0; i < itemsnum; i++)
	{
		if (wynik & (unsigned long long)1)
		{
			cout << setw(10) << sizes[i] << " ";
			cout << setw(10) << values[i] << endl;
			sumar += sizes[i];
			sumaw += values[i];
		}
		wynik >>= (unsigned long long)1;
	}
	cout << "SUMA:\n" << setw(10) << sumar << " " << setw(10) << sumaw << endl;
}
void PlecakDisplaySolution(vector<short> wynik, vector<int> sizes, vector<int> values, int totalsize, int itemsnum)
{
	int sumar = 0, sumaw = 0;
	cout << "Mając (" << itemsnum << ") rzeczy, do plecaka o pojemności (" << totalsize << ") najlepiej zapakować:\n"
		<< setw(13) << "(rozmiar) " << "(wartość)" << endl;

	for (unsigned i = 0; i < wynik.size(); i++)
	{
		cout << setw(10) << sizes[wynik[i]] << " ";
		cout << setw(10) << values[wynik[i]] << endl;
		sumar += sizes[wynik[i]];
		sumaw += values[wynik[i]];
	}
	cout << "SUMA:\n" << setw(10) << sumar << " " << setw(10) << sumaw << endl;
}
void PlecakGenerate(vector<int> &sizes, vector<int> &values, int totalsize, int itemsnum)
{

	unsigned suma = 0;
	while (suma < totalsize * 1.25)	// suma wszystkich wartosci elementow musi byc wieksza od calkowitej wielkosci plecaka * 25%
	{
		sizes.resize(0);
		values.resize(0);
		suma = 0;
		for (int i = 0; i < itemsnum; i++)
		{
			sizes.push_back(rand() % totalsize + 1);			//dodanie wartości na koniec listy
			values.push_back(rand() % totalsize + 1);
		}
		for (auto i = 0; i < itemsnum; i++)
			suma += values[i];
	}
}
void PlecakTest(bool extended, bool dynamicorfptas)
{
	vector<int>sizes, values;
	int totalsize, itemsnum;
	unsigned long long score;
	vector<short> c_score;
	long double time;
	MyTimer timer;

	float ε;
	if (!dynamicorfptas)
	{
		cout << "Podaj wartość epsilon [0,1]: ";
		cin >> ε;
	}

	for (auto i =50; i <= 600; i += 50)	// iteracja po wielkosci plecaka
	{
		if (extended)
		{
			for (auto j = 75; j <= 900; j += 75)	// iteracja po liczbie elementow
			{
				totalsize = j;
				itemsnum = i;
				time = 0;
				for (auto k = 0; k < 100; k++)
				{
					PlecakGenerate(sizes, values, totalsize, itemsnum);				// generacja instancji
					if (dynamicorfptas)													// dynamiczny
					{
						timer.Start();													// wlaczenie zegara
						PlecakDynamic(sizes, values, totalsize, itemsnum);	// odpalenie algorytmu dla plecaka i zapisanie wyniku.
						time += timer.End();											// dodanie uplynietego czasu do zmiennej
					}
					else																// FPTAS
					{
						timer.Start();													// wlaczenie zegara
						PlecakFPTAS(sizes, values, totalsize, itemsnum, ε);	// odpalenie algorytmu dla plecaka i zapisanie wyniku.
						time += timer.End();											// dodanie uplynietego czasu do zmiennej
					}
				}
				time /= 100;														// policzenie sredniego czasu
																					// wynik
				cout << "V: " << setw(8) << totalsize << ", n: " << setw(8) << itemsnum << " - " << setw(16) << timer.Convert(time) << endl;
			}
			cout << '\n';
		}
		else
		{
			totalsize = 1.5*i; // sztywny rozmiar
			itemsnum = i;
			time = 0;
			for (auto k = 0; k < 100; k++)
			{
				PlecakGenerate(sizes, values, totalsize, itemsnum);				// generacja instancji
				if (dynamicorfptas)													// dynamiczny
				{
					timer.Start();													// wlaczenie zegara
					PlecakDynamic(sizes, values, totalsize, itemsnum);	//odpalenie algorytmu dla plecaka i zapisanie wyniku.
					time += timer.End();											// dodanie uplynietego czasu do zmiennej
				}
				else																// FPTAS
				{
					timer.Start();													// wlaczenie zegara
					PlecakFPTAS(sizes, values, totalsize, itemsnum, ε);	// odpalenie algorytmu dla plecaka i zapisanie wyniku.
					time += timer.End();											// dodanie uplynietego czasu do zmiennej
				}
			}
			time /= 100;														// policzenie sredniego czasu
																				// wyświetlenie wyniku
			cout << "Średni czas dla plecaka o pojemności " << totalsize << " z " << itemsnum << " przedmiotami: " << timer.Convert(time) << endl;
		}
	}
}
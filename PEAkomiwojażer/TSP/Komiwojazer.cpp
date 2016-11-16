#include "Header.h"

int* KomiwojazerBrute(MatrixGraph graph)
{
	int graph_size = graph.GetSize();
	int *values = new int[graph_size];
	int *best = new int[graph_size + 1];
	double weight = 0, wynik = 999999999;
	unsigned long long perm = 1;
	for (int i = 1; i <= graph_size; i++)
		perm *= i;

	for (int i = 0; i < graph_size; i++)
	{
		values[i] = i;	// tymczasowe rozwi�zanie
		best[i] = i; // najlepsze rozwi�zanie
	}
	for (int i = 0; i < perm; i++)
	{
		weight = 0;
		next_permutation(values, values + graph_size);	// permutacja tymczasowego rozwi�zania
		for (int j = 0; j < graph_size - 1; j++)
		{
			//printf("%d:%d=%f ", values[j], values[j+1], graph.EdgesOf(values[j]).at(values[j+1]).weight);
			if (graph.EdgesOf(values[j]).at(values[j + 1]).weight > 0)
				weight += graph.EdgesOf(values[j]).at(values[j + 1]).weight;
		}
		weight += graph.EdgesOf(values[graph_size - 1]).at(values[0]).weight; // dodanie wagi powrotu do 0;
		//printf("\n");
		if (weight < wynik)
		{
			wynik = weight;
			memcpy(best, values, sizeof(int)*graph_size);
		}
	}
	best[graph_size] = best[0];
	return best;
}

int* KomiwojazerSimulatedAnnealing(MatrixGraph graph, double Tmin, double Tmax, double a)
{
	// Tmin - temperatura zako�czenia
	// Tmax - temperatura pocz�tkowa
	double T = Tmax;												//aktualna temperatura
	pair <int*, int*> values;										//miasta
	pair <float, float> weights;									//czas
	values.first = new int[graph.GetSize() + 1];
	values.second = new int[graph.GetSize() + 1];
	unsigned long long perm = 1;
	for (int i = 1; i <= (graph.GetSize() < 66 ? graph.GetSize() : 65); i++)
		perm *= i;
	perm = rand() % perm;

	//losowe rozwi�zanie A
	for (int i = 0; i < graph.GetSize(); i++)
	{
		values.first[i] = values.second[i] = i;
	}
	for (int i = 0; i < perm; i++)
		next_permutation(values.first, values.first + graph.GetSize());

	int i = 0; //liczba iteracji
	while (T > Tmin)
	{
		//rozwi�zanie B stworzone przez zamian� dw�ch element�w w A
		pair <int, int> dozamiany;
		dozamiany.first = rand() % graph.GetSize();
		dozamiany.second = rand() % graph.GetSize();

		while (dozamiany.first == dozamiany.second)				//indeksy maj� by� inne
			dozamiany.second = rand() % graph.GetSize();

		//cout << i << ": zamiana: " << dozamiany.first << " i " << dozamiany.second << "; ";

		swap(values.second[dozamiany.first], values.second[dozamiany.second]);

		//liczenie czas�w tras
		weights.first = weights.second = 0;						// zerowanie wag
		for (int j = 0; j < graph.GetSize() - 1; j++)
		{
			if (graph.EdgesOf(values.first[j]).at(values.first[j + 1]).weight > 0)
				weights.first += graph.EdgesOf(values.first[j]).at(values.first[j + 1]).weight;
			if (graph.EdgesOf(values.second[j]).at(values.second[j + 1]).weight > 0)
				weights.second += graph.EdgesOf(values.second[j]).at(values.second[j + 1]).weight;
		}

		double P = exp((float)(weights.first - weights.second) / T);

		//cout << "wagi: " << weights.first << ", " << weights.second << "; P: " << P << " ";

		if (weights.second < weights.first)
		{
			for (int i = 0; i < graph.GetSize(); i++)
			{
				values.first[i] = values.second[i];
			}
			weights.first = weights.second;
			//cout << "2nd\n";
		}
		else if ((float)rand() / RAND_MAX < P)
		{
			for (int i = 0; i < graph.GetSize(); i++)
			{
				values.first[i] = values.second[i];
			}
			weights.first = weights.second;
			//cout << "2nd\n";
		}
		//else
			//cout << "1st\n";
		i++;
		T = a * T;
	}
	values.first[graph.GetSize()] = values.first[0];
	return values.first;
}

vector<unsigned char> KomiwojazerBranchAndBound(MatrixGraph graph)
{
	BnbMatrix* matrix = new BnbMatrix(graph);		// rodzic
	BnbMatrix* child1;								// lewy syn (z kraw�dzi�)
	BnbMatrix* child2;								// prawy syn (bez kraw�dzi)
	vector<unsigned char> solution;					// rozwi�zanie ostateczne
	EdgePtr edges;									// wska�nik na rozwi�zanie przechowywane w danej macierzy
	float matrixcount = 1;							// numer rodzica
	priority_queue <P, vector<P>, Order> limits;	// kolejka priorytetowa granic macierzy
	bool goodsolution = false;						// czy dobre rozwi�zanie?
	while (true)									// bo rekurencj� zamieniono na iteracje
	{
		if (matrix->size == 1 && matrix->GetLimit() < FLT_MAX && matrix->GetNodes()[0][0] == 0) // sprawdzenie, czy juz nie znaleziono rozwi�zania - je�li granica macierzy mneijsza od nieskonczono�ci i zawarto�� macierzy = 0, to mozna rozpatrywa�, czy to jest dobre rozwi�zanie
		{
			goodsolution = true; // zak�adamy, ze dobre, �eby potem ewentualnie zmieni�

			edges = matrix->GetEdges(); // przypisanie danego rozwi�znia

			solution.push_back(0);
			for (int j = 1; j <= edges->size(); j++) // generaowanie rozwi�zania, szukanie cyklu Hamiltona
			{
				for (int k = 0; k < edges->size(); k++)
				{
					if (edges->at(k).first == solution[j - 1]) // je�li nie ma drowi wychodz�cej z wierzcho�ka, do kt�rego weszli�my, rozwi�zanie b��dne
					{
						solution.push_back(edges->at(k).second);
						break;
					}
				}
				if (solution.size() <= j)
				{
					goodsolution = false;
					break;
				}
			}
			if (goodsolution) // je�eli do tej pory by�o ok...
			{
				for (int k = 1; k < edges->size(); k++)	// czy dobre rozwi�zanie?
				{
					if (k < solution.size() - 1 && solution[k] == 0) // je�eli rozwiazanie, kt�re sprawdzam jest mniejsze od pe�nego rozwi�zania, to z�e; je�li napotka 0 na wcze�neijszej pozycji, to znaczy, ze za ma�y cykl - tej macierzy ju� nie pami�tamy, bo jest do dupy (resize)
					{
						goodsolution = false;
						edges->resize(0);
						break;
					}
				}
				unsigned char node;
				for (int k = 0; k < solution.size(); k++)
				{
					if (goodsolution) // je�eli do tej pory by�o ok...
					{
						if (solution[k] != 0) // sprawdza, czy wierzczho�ek nie jest 0
						{
							node = 0;
							for (int j = 0; j < solution.size(); j++) // poszukiwanie wierzcho�ka w rozwi�zaniu
							{
								if (solution[k] == solution[j])
									node++;
								if (node > 1) // je�li wyst�pi� wi�cej, ni� raz, to rozwi�zanie b��dne
								{
									goodsolution = false;
									break;
								}

							}
						}
					}
					else
						break;
				}
			}
			if (goodsolution) // je�eli do tej pory by�o ok, to znaczy, ze dobre rozwi�zanie
			{
				while (!limits.empty()) // czyszczenie kolejki priorytetowej
				{
					delete limits.top().second; // usu� wska�nik na macierz
					limits.pop(); // zdejmij element z kolejki priorytetowej
				}
				return solution; // zwr�c poprawny wynik
			}
			else // je�li rozwi�zanie z�e, to rozwi�zanie zn�w wielko�ci 0, �eby od nowa pushbackowa�
				solution.resize(0);
		}
		if (matrix->size > 1) // je�li wielko�� macierzy > 1 (je�li mozna jeszcze zredukowa�)
		{
			matrixcount++; //zwi�ksz licznik ��czny wszystkich macierzy 
			child1 = new BnbMatrix(*matrix, true, matrixcount); // utworzenie lewego syna z usun�tym wierszem i kolumn� (matrixcount m�wi, kt�ry wiersz i kolumna, matrix to wka�nik na rodzica)
			child1->Clean(); // usuwazawarto�� minimalnych warto�ci wierszy i kolumn
			limits.push(make_pair(child1->GetLimit(), child1));	// dodaj lewego syna do kolejki priorytetowej

			matrixcount++; // znalogicznie dla prawego syna
			child2 = new BnbMatrix(*matrix, false, matrixcount); // prawy nie wykre�la wiersza i kolumny, a bierze niesko�czono�� 
			child2->Clean();
			limits.push(make_pair(child2->GetLimit(), child2));
		}
		if (matrix->GetNumber() > 0) // je�li numer macierzy wi�kszy od 0
		{
			delete limits.top().second; // usuwa wska�nik na nastepn� macierz z kolejki priorytetowej (bo 0 macierz nie by�a w kolejce priorytetowej)
			limits.pop(); // zdejmujemy warto�� z kolejki, bo b�dzie teraz rozpatrywana
		}

		matrix = limits.top().second; // nast�pna macierz bierze wska�nik z kolejki priorytetowej
	}
	return vector<unsigned char>(1, 0); // zwr�cenie wektora d�ugo�ci 1 o warto�ci 0, �eby Visual si� nei czepia�
}

vector<unsigned char> KomiwojazerTabuSearch(MatrixGraph graph, unsigned tau)
{
	srand((unsigned)time(NULL));
	vector<unsigned char> solution(graph.GetSize()), perm(graph.GetSize());
	double bestMin = 0;
	queue<pair<unsigned char, unsigned char>> fifo;
	vector<vector<float>> nodes = graph.GetNodes();
	// stworzenie pierwszego rozwi�zania

	solution[0] = 0;
	for (auto i = 0; i < nodes.size() - 1; i++)
	{
		solution[i + 1] = i + 1;
		bestMin += nodes[i][i + 1];
	}
	bestMin += nodes[nodes.size() - 1][0];
	perm = solution;

	/////////////////////////////////////////////

	unsigned char x, y;
	unsigned int foo;
	for (unsigned i = 0; i < tau; i++)
	{
		do {
			x = rand() % (unsigned char)nodes.size();
			y = rand() % (unsigned char)nodes.size();
		} while (x >= y && !CheckPairInTabu(fifo, x, y));
		fifo.push(pair<unsigned char, unsigned char>(x, y));
		if (fifo.size() > nodes.size())
			fifo.pop();
		perm = KomiwojazerInvert(perm, x, y);
		foo = CheckMin(nodes, perm);
		if (foo < bestMin)
		{
			bestMin = foo;
			solution = perm;
		}
	}
	solution.push_back(solution[0]);
	return solution;
}

vector<unsigned char> KomiwojazerGenetic(MatrixGraph graph, unsigned populationsize, unsigned crossChance, unsigned mutationChance, bool debug)
{
	srand((unsigned)time(NULL));
	typedef chrono::high_resolution_clock myclock;
	myclock::time_point beginning = myclock::now();
	myclock::duration d = myclock::now() - beginning;
	__int64 seed = d.count();
	mt19937_64 generator(seed);

	struct Triplet
	{
		float begin, end;
		int index;
	};

	unsigned size = graph.GetSize();								// d�ugo�� rozwi�zania
	unsigned n = populationsize;									// wielko�� populacji
	vector<unsigned> tochoose;										// wektor pomocniczy do tworzenia osobnika
	vector<unsigned char> solution;									// rozwi�zanie
	vector<vector<unsigned char>> env(n);							// �rodowisko
	vector<unsigned char> being(size, 0);							// osobnik
	vector<unsigned char> child1(size, 0);
	vector<unsigned char> child2(size, 0);
	vector<pair<unsigned, unsigned>>odwzorowania;
	vector<float>prob(n, 0);
	uniform_int_distribution<int> przedzial(0, size - 1);
	uniform_int_distribution<unsigned> przedzial2(1, 100);
	unsigned chance;
	unsigned a, b;
	bool mainloop = true;
	float bestCost = 0;
	unsigned odwzorowaniaSize = 0;
	unsigned krzyzowania = 0, mutacje = 0, generacje = 0;
	vector<Triplet>circle(n);

	// generacja pocz�tkowego �rodowiska
	for (unsigned i = 0; i < n; i++)
	{
		tochoose.resize(size);
		for (unsigned j = 0; j < size; j++)
			tochoose[j] = j;

		for (unsigned j = 0; j < size; j++)
		{
			auto index = rand() % tochoose.size();
			being[j] = tochoose[index];
			tochoose.erase(tochoose.begin() + index);
		}
		env[i] = being;
	}

	vector<float> survFuncVal(n, 0);									// waga
	float sum = 0;
	//  cz�ciowe obliczenie prawdopodobie�stwa. Suma wag osobnik�w
	for (unsigned i = 0; i < n; i++)
	{
		survFuncVal[i] = 1 / GetValueOfBeing(env[i], graph);
		sum += 1 / survFuncVal[i];
	}

	/* **************************************************** */
	/* *********************  EWOLUCJA  ******************* */
	/* **************************************************** */
	for (unsigned e = 0; e <= max(200, populationsize); e++)
	{
		// tworzenie pseudoko�a z kt�rego b�d� losowane osobniki do mutacji
		circle[0].begin = 0;
		circle[0].end = 1 / survFuncVal[0];
		circle[0].index = 0;

		for (unsigned i = 1; i < n; i++)
		{
			circle[i].begin = circle[i - 1].end + FLT_MIN;
			circle[i].end = circle[i - 1].end + 1 / survFuncVal[i];		// poprzednie.begin+FLT_MIN, poprzednie.end + 1/wartosc
			circle[i].index = i;
		}
		// losowanie osobnik�w do mutacji
		uniform_real_distribution<float> dis(0.0, sum);
		float first = dis(generator);
		float second = dis(generator);
		pair<unsigned, unsigned>chosen(0, 0);
		// sprawdzenie, kt�re to osobniki
		for (unsigned i = 0; i < n; i++)
		{
			if (first >= circle[i].begin && first <= circle[i].end)
				chosen.first = circle[i].index;
			if (second >= circle[i].begin && second <= circle[i].end)
				chosen.second = circle[i].index;
		}

		/* **************************************************** */
		/* *******************  KRZY�OWANIE  ****************** */
		/* **************************************************** */
		chance = przedzial2(generator);
		if (chance <= crossChance)
		{
			krzyzowania++;
			// losowo wybranie przedzia�u

			do {
				a = przedzial(generator);
				b = przedzial(generator);

				if (a > b)
					swap(a, b);
			} while (b - a + 1 == size);
			// wytypowanie odwzorowa�
			odwzorowania.resize(b - a + 1);
			odwzorowaniaSize = odwzorowania.size();
			for (unsigned i = 0; i < odwzorowaniaSize; i++)
			{
				odwzorowania[i].first = env[chosen.first][i + a];
				odwzorowania[i].second = env[chosen.second][i + a];
			}

			// zamiana wybranych fragment�w
			for (unsigned i = a; i <= b; i++)
			{
				child2[i] = env[chosen.first][i];
				child1[i] = env[chosen.second][i];
			}

			bool loop = true;
			// wype�nienie lewej cz�ci potomk�w
			for (unsigned i = 0; i < a; i++)
			{
				// child1
				unsigned toSwap = env[chosen.first][i];
				while (loop)
				{
					for (unsigned j = 0; j < odwzorowaniaSize; j++)
					{
						if (toSwap == odwzorowania[j].second && toSwap != odwzorowania[j].first)
						{
							toSwap = odwzorowania[j].first;
							break;
						}
						if (j == odwzorowaniaSize - 1)
							loop = false;
					}
				}
				child1[i] = toSwap;
				// child2
				loop = true;
				toSwap = env[chosen.second][i];
				while (loop)
				{
					for (unsigned j = 0; j < odwzorowaniaSize; j++)
					{
						if (toSwap == odwzorowania[j].first && toSwap != odwzorowania[j].second)
						{
							toSwap = odwzorowania[j].second;
							break;
						}
						if (j == odwzorowaniaSize - 1)
							loop = false;
					}
				}
				child2[i] = toSwap;
				loop = true;
			}
			// wype�nienie prawej cz�ci potomk�w
			for (unsigned i = b + 1; i < size; i++)
			{
				// child1
				unsigned toSwap = env[chosen.first][i];
				while (loop)
				{
					for (unsigned j = 0; j < odwzorowaniaSize; j++)
					{
						if (toSwap == odwzorowania[j].second && toSwap != odwzorowania[j].first)
						{
							toSwap = odwzorowania[j].first;
							break;
						}
						if (j == odwzorowaniaSize - 1)
							loop = false;
					}
				}
				child1[i] = toSwap;
				// child2
				loop = true;
				toSwap = env[chosen.second][i];
				while (loop)
				{
					for (unsigned j = 0; j < odwzorowaniaSize; j++)
					{
						if (toSwap == odwzorowania[j].first && toSwap != odwzorowania[j].second)
						{
							toSwap = odwzorowania[j].second;
							break;
						}
						if (j == odwzorowaniaSize - 1)
							loop = false;
					}
				}
				child2[i] = toSwap;
				loop = true;
			}
		}
		else
		{
			child1 = env[chosen.first];
			child2 = env[chosen.second];
		}

		// MUTACJA
		chance = przedzial2(generator);
		if (chance <= mutationChance)
		{
			mutacje++;
			a = przedzial(generator);
			b = przedzial(generator);
			if (a > b)
				swap(a, b);
			reverse(child1.begin() + a, child1.begin() + b); //invert

			a = przedzial(generator);
			b = przedzial(generator);
			if (a > b)
				swap(a, b);
			reverse(child2.begin() + a, child2.begin() + b); //invert
		}
		// zamiana najgorszych dw�ch osobnik�w na stworzonych dw�ch potomk�w i aktualizacja ich wag oraz sumy wag
		int tempindex = distance(survFuncVal.begin(), min_element(survFuncVal.begin(), survFuncVal.end())); // wyszukanie indeksu najgorszego osobnika
		env[tempindex] = child1;											// nadpisanie najgorszego osobnika nowym
		sum -= 1 / survFuncVal[tempindex];
		survFuncVal[tempindex] = 1 / GetValueOfBeing(env[tempindex], graph);
		sum += 1 / survFuncVal[tempindex];

		tempindex = distance(survFuncVal.begin(), min_element(survFuncVal.begin(), survFuncVal.end())); // wyszukanie indeksu najgorszego osobnika
		env[tempindex] = child2;											// nadpisanie najgorszego osobnika nowym
		sum -= 1 / survFuncVal[tempindex];
		survFuncVal[tempindex] = 1 / GetValueOfBeing(env[tempindex], graph);
		sum += 1 / survFuncVal[tempindex];

		float temp = *(max_element(survFuncVal.begin(), survFuncVal.end()));
		if (bestCost < temp)
		{
			generacje++;
			bestCost = temp;
			e = 0;
		}
	}
	// generacja rozwi�zania ( osobnik o najmniejszej wadze )
	solution = env[distance(survFuncVal.begin(), max_element(survFuncVal.begin(), survFuncVal.end()))];
	solution.push_back(solution[0]);
	if (debug)
		cout << "\nKrzy�owania: " << krzyzowania << " Mutacje: " << mutacje << " Generacje: " << generacje << endl;
	return solution;
}

unsigned int CheckMin(vector<vector<float>> matrix, vector<unsigned char> perm)
{
	unsigned foo = 0;
	for (auto i = 0; i < matrix.size() - 1; i++)
		foo += (unsigned)matrix[perm[i]][perm[i + 1]];
	if (perm[matrix.size() - 1] == 0)
		return INT_MAX;
	foo += (unsigned)matrix[perm[matrix.size() - 1]][perm[0]];
	return foo;
}
bool CheckPairInTabu(queue<pair<unsigned char, unsigned char>> fifo, unsigned char x, unsigned char y)
{
	pair<unsigned char, unsigned char> para(x, y);
	while (!fifo.empty())
	{
		if (fifo.front() == para)
			return true;
		else
			fifo.pop();
	}
	return false;
}
vector<unsigned char> KomiwojazerInvert(vector<unsigned char> perm, unsigned char x, unsigned char y)
{
	for (auto i = 0; i <= (y - x) / 2; i++)
		swap(perm[x + i], perm[y - i]);
	return perm;
}
void KomiwojazerLoad(ifstream &file, MatrixGraph &graph, string extension)
{
	if (file.good())
	{
		if (extension == "tsp")
			graph.LoadTSP(file);
		else if (extension == "atsp")
			graph.LoadATSP(file);
		else
			graph.Load(file);
		file.close();
	}
	else
		cout << "\nPodano niew�a�ciw� �cie�k� do pliku.\n";
}

void KomiwojazerDisplayEdges(int komi[], MatrixGraph graph)
{
	for (int i = 0; i <= graph.GetSize(); i++)
		cout << komi[i] << " ";
}

float KomiwojazerGetWeight(int komi[], MatrixGraph graph)
{
	float weight = 0;
	for (int i = 0; i < graph.GetSize(); i++)
		weight += graph.EdgesOf(komi[i]).at(komi[i + 1]).weight;
	return weight;
}

void KomiwojazerDisplayEdges(vector<unsigned char> komi, MatrixGraph graph)
{
	for (int i = 0; i <= graph.GetSize(); i++)
		cout << (int)komi[i] << " ";
}

float KomiwojazerGetWeight(vector<unsigned char> komi, MatrixGraph graph)
{
	float weight = 0;
	for (int i = 0; i < graph.GetSize(); i++)
		weight += graph.EdgesOf(komi[i]).at(komi[i + 1]).weight;
	return weight;
}

void KomiwojazerTest(MyTimer &timer, MatrixGraph graph)
{
	long double time;
	for (int k = 1; k <= 3; k++)
	{
		time = 0;
		for (int i = 0; i < 100; i++)
		{
			graph.Generate(k * 3);		// generacja dr�g mi�dzy miastami
			timer.Start();
			KomiwojazerBrute(graph);	// wykonanie algorytmu dla komiwojazera
			time += timer.End();
		}
		time /= 100;
		cout << "�redni czas dla (" << k * 3 << ") miast: " << time << " ms" << endl;
	}
}

void KomiwojazerBBRandomTest(int n, int m[], int o)//n - liczba graf�w, m[] - lista rozmiar�w graf�w, o - liczba iteracji
{
	cout << "Test losowych instancji\n liczba graf�w: " << n << "\n liczba iteracji: " << o << endl;
	MyTimer timer;
	long double time;
	for (int i = 0; i < n; i++)
	{
		cout << "Graf " << setw(3) << m[i] << "-wierzcho�kowy ";
		MatrixGraph g;
		time = 0;
		for (int j = 0; j < o; j++)
		{
			g.Generate(m[i]);
			timer.Start();
			KomiwojazerBranchAndBound(g);
			time += timer.End();
			if (j % 4 == 0)
				cout << '.';
		}
		time /= o;
		cout << "\n wykonano �rednio w czasie " << time << " ms\n";
	}
}

float GetValueOfBeing(vector<unsigned char> being, MatrixGraph graph)
{
	float sum = 0;
	for (auto i = 0; i < being.size() - 1; i++)
	{
		sum += graph.GetValueOf(being[i], being[i + 1]);

	}
	sum += graph.GetValueOf(being[being.size() - 1], being[0]);
	return sum;
}
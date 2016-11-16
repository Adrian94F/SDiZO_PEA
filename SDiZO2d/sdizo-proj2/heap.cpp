class Heap
{
	MyArray heap;

	void RepairDown()									// naprawa kopca w dół
	{
		int i = 0, pos;									// zaczynam od korzenia
		do
		{
			if (2 * i + 2 < heap.GetLength() - 1)		//sprawdzam, czy prawy syn istnieje
				pos = (*heap.Get(2 * i + 2) > *heap.Get(2 * i + 1) ? 2 * i + 2 : 2 * i + 1); // wybieram większego syna
			else if (2 * i + 1 < heap.GetLength() - 1)	//sprawdzam, czy lewy syn istnieje, jeżeli prawy nie.
				pos = 2 * i + 1;						//wybieram lewego syna.
			else
				break;									//jeżeli nie ma synów, to znaczy, że doszedłem do liścia. Kończę naprawę.
				 
				 if (*heap.Get(i) < *heap.Get(pos))		// porównanie większego syna z ojcem.
					swap(*heap.Get(i), *heap.Get(pos)); //zamiana, jeżeli ojciec mniejszy od syna.
				i = pos;								// ojciec = syn
		} while (true);
	}
	void RepairUp()										//naprawa kopca w górę
	{
		int i = heap.GetLength() - 1;					// zaczynam od liścia.
		while (*heap.Get(i) > *heap.Get((i - 1) / 2) && heap.GetLength()>1) 
		{
			swap(*heap.Get(i), *heap.Get((i - 1) / 2)); //zamieniam syna z ojcem, jeżeli syn większy od ojca.
			i = (i - 1) / 2;							// syn = ojciec
		}
	}

public:
	Heap(){}
	void Push(int value)					// dodawanie elementu do kopca
	{
		heap.AddAtEnd(value);				//dodanie na koniec tablicy
		RepairUp();							//naprawa w górę
	}
	void Generate()							// generuje n elementowy kopiec o wartościach losowych.
	{
		bool ans;
		string name;
		int count;
		
		cout << "podaj liczbę elementów: ";
		cin >> count;

		Clean();							//czyszczenie kopca

		for (int i = 0; i < count; i++)
			Push(rand() % RAND_MAX);		//dodawanie losowych wartości
		cout << "czy zapisać do pliku ?"
			 <<"[1] - tak [0] - nie\nwybór: ";
		cin >> ans;
		if (ans)
			Save();							//ewentualne zapisanie do pliku
	}
	void Load()								// odczytuje kopiec w postaci tablicy z pliku
	{
		int length, temp;
		string name;
		cout << "podaj nazwę pliku: ";
		cin >> name;

		Clean();							//czyszczenie kopca

		ifstream file;
		file.open(name.c_str());
		file >> length;	
		for (int i = 0; i < length; i++)
		{
			file >> temp;					//odczytanie wartości z pliku
			Push(temp);						//dodanie do kopca i naprawienie go
		}			

		file.close();
		cout << "\nWczytano (" << length << ") elementów\n";
	}
	void Remove()							// usuwanie korzenia
	{
		swap(*heap.Get(0), *heap.Get(heap.GetLength() - 1));	//zamiana liścia z korzeniem
		heap.DelAtEnd();										// odcięcie liścia, w którym jest wartość korzenia.
		RepairDown();											//naprawa w dół
	}
	void Display()							// metoda rysująca drzewo w konsoli
	{
		int i = 0, lev = 0; 
		MyArray temp = MyArray(heap.GetLength()); 
		string space = "", branch="__"; 
		
		while (true)
		{
			space = "";
			for (int j = 0; j < lev; j++)
				space += "  |";
			space += branch;
			if (!temp.Exists(i))
			{
				cout << space << *heap.Get(i) << endl;
				temp.AddAtEnd(i);
			}

			if (2 * i + 2 < heap.GetLength() && !temp.Exists(2 * i + 2))
			{
				i = 2 * i + 2;
				lev++;
				branch = "--";
			}
			else if (2 * i + 1 < heap.GetLength() && !temp.Exists(2 * i + 1))
			{
				i = 2 * i + 1;
				lev++;
				branch = "__";
			}
			else if (i > 0)
			{
				i = (i - 1) / 2;
				lev--;
			}
			else if (temp.GetLength() >= heap.GetLength())
				break;
		}
	}
	void Save()								// zapisuje kopiec w postaci tablicy do pliku
	{
		heap.Save();
	}
	void Clean()							//czyści kopiec
	{
		heap.Dispose();
		heap = MyArray();
	}
	int GetCount()							// zwraca liczbę elementów kopca
	{
		return heap.GetLength();
	}
	int* Search(int value)			//zwraca wskaźnik na komórkę kopca w tablicy
	{
		return &*heap.Search(value);
	}
};
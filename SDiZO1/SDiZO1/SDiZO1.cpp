//Adrian Frydmañski - 209865

#include "stdafx.h"
#include "Lelement.h"
#include "Table.h"
#include "Heap.h"
#include "Timer.cpp"

////////////////////////
//  globalne zmienne  //
////////////////////////

int n = 20;														// licza elementów w obiektach
Timer timer;													// timer
long long int time = 0;											// zmienna przechowuj¹ca czas
Table table;													// tablica
Lelement* head = NULL;											// pierwszy cz³on listy
Heap heap;														// kopiec
string frames[] = { "#------------------------------------#\n|                                    |\n",
"|                                    |\n#------------------------------------#\n|                                    |\n",
"|                                    |\n#------------------------------------#\n" };
string headers[] = { "|          SDiZO - projekt I         |\n|     Adrian Frydmanski - 209865     |\n",
"|    Wybrana struktura:              |\n|       Tablica                      |\n",
"|    Wybrana struktura:              |\n|       Lista jednokierunkowa        |\n",
"|    Wybrana struktura:              |\n|       Kopiec binarny               |\n" };
string options[] = { "|  Wybierz strukture, na ktorej      |\n|  bedziesz operowal:                |\n|    [1] Tablica                     |\n|    [2] Lista jednokierunkowa       |\n|    [3] Kopiec binarny              |\n|    [4] Wyswietl wszystkie          |\n|    [5] Autostatystyka              |\n|    [6] Koniec                      |\n",
"|  Wybierz operacje do               |\n|  automatycznego testowania         |\n|  struktury:                        |\n|    [1] Dodaj n elementow           |\n|    [2] Usun n elementow            |\n|    [3] Wyszukaj n elementow        |\n|    [4] Wyswietl strukture          |\n|    [5] Odczytaj z pliku            |\n|    [6] Zapisz do pliku             |\n|    [7] Wroc                        |\n",
"|  Podaj liczbe elementow            |\n|  do przetworzenia                  |\n"};

string showTime(long long time, int n)								// podanie czasu w sekundach, a nie w taktach procesora
{
	LARGE_INTEGER lpFrequency;
	QueryPerformanceFrequency(&lpFrequency);
	long double freq = lpFrequency.QuadPart, ld_time = time;
	ld_time = ld_time / freq * 1000;
	string space = "";												// do poprawnego wyœwietlania wyników
	for (int i = log10(ld_time + 1); i < 10; i++)
		space += " ";
	string s = " " +
		to_string(ld_time) +
		" ms" + space + "|  " +
		to_string(ld_time / n) +
		" ms";
	return s;
}

void showMenu(int header, int level) {
	int option = header == 0 && level == 0 ? 0 : 1;
	option = level == 1 ? 2 : option;
	cout << frames[0] << headers[header] << frames[1] << options[option] << frames[2];
}

string autostatystyka()
{
	//////////////////////////////////////////////////////////////////
	//																//
	//    wypelniamy dana strukture odpowiednia liczba elementow	//
	//    i mierzymy czasy dodawania, usuwania i wyszukiwania		//
	//    na pe³nej strukturze										//
	//																//
	//////////////////////////////////////////////////////////////////


	string result = "";																	// wynikowy string
	string separator = "-----------------------------+-----------------------+-------------------------";
	int pomiary[] = {0, 50, 100, 500, 1000, 5000, 10000, 50000, 100000 };
	for (int k = 1; k < 9; k++)
	{
		n = pomiary[k];
		cout << "pomiar dla " << n << " elementow:\n";
		result += (
			" Wyniki pomiarow dla " +
			to_string(n) +
			"-elementowych struktur danych:\n" +
			separator +
			"\n  typ struktury/operacja     |  czas dzialania       |  srednio na 1 element");

		//////////////////////////////////////////////////
		//												//
		//  wype³nij tablicê pocz¹tkowymi n liczbami /  //
		//  / dodaj brakujace do nastepnej wartoœci     //
		//												//
		//////////////////////////////////////////////////
		int m = n - pomiary[k - 1];
		for (int j = 0; j < m; j++)
		{
			table.addBefore(rand());													//dope³niaj tablicê
			Lelement::addBefore(rand(), *&head);										//dope³niaj listê
			heap.add(rand());															//dope³niaj kopiec
		}
		cout << "   wypelniono [t";


		///////////////
		//           //
		//  tablica  //
		//           //
		///////////////
		//cout << "Tablica dynamiczna:";
		result += '\n' + separator + "\n  Tablica dynamiczna         |\n" + separator;

		////////////////////////////////
		// dodaj na pocz¹tku tablicy
		////////////////////////////////	
		time = 0;
		for (int i = 0; i < 100; i++)
		{
			timer.Start();
			table.addBefore(rand());
			time += timer.End();
			table.delBefore();															//usun z powrotem
		}
		result += "\n    dodaj na poczatku        | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// dodaj na koñcu tablicy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			table.addAfter(rand());
			time += timer.End();
			table.delBefore();															//usun z powrotem
		}
		result += "\n    dodaj na koncu           | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// dodaj losowo w tablicy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			table.addRand(rand());
			time += timer.End();
			table.delBefore();															//usun z powrotem
		}
		result += "\n    dodaj losowo             | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// usuñ na pocz¹tku tablicy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < n; i++)
		{
			timer.Start();
			table.delBefore();
			time += timer.End();
			table.addBefore(rand());													//dodaj z powrotem
		}
		result += "\n    usun z poczatku          | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// usuñ na koñcu tablicy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			table.delAfter();
			time += timer.End();
			table.addBefore(rand());													//dodaj z powrotem
		}
		result += "\n    usun z konca             | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// usuñ losowo z tablicy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			table.delRand();
			time += timer.End();
			table.addBefore(rand());													//dodaj z powrotem
		}
		result += "\n    usun losowo              | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// wyszukaj
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			table.find(rand());
			time += timer.End();
		}
		result += "\n    wyszukaj                 | " + showTime(time, n);
		cout << ".][l";

		/////////////
		//         //
		//  lista  //
		//         //
		/////////////
		//cout << "Lista jednokierunkowa";
		result += '\n' + separator + "\n  Lista jednokierunkowa      |\n" + separator;

		////////////////////////////////
		// dodaj na pocz¹tku listy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			Lelement::addBefore(rand(), *&head);
			time += timer.End();
			Lelement::delBefore(*&head);												//usuñ z powrotem
		}
		result += "\n    dodaj na poczatku        | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// dodaj na koñcu listy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			Lelement::addAfter(rand(), *&head);
			time += timer.End();
			Lelement::delBefore(*&head);												//usuñ z powrotem
		}
		result += "\n    dodaj na koncu           | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// dodaj losowo w liœcie
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			Lelement::addRand(rand(), *&head, n);
			time += timer.End();
			Lelement::delBefore(*&head);												//usuñ z powrotem
		}
		result += "\n    dodaj losowo             | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// usuñ z pocz¹tku listy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			Lelement::delBefore(*&head);
			time += timer.End();
			Lelement::addBefore(rand(), *&head);										//dodaj z powrotem
		}
		result += "\n    usun z poczatku          | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// usuñ na koñcu listy
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			Lelement::delAfter(*&head);
			time += timer.End();
			Lelement::addBefore(rand(), *&head);										//dodaj z powrotem
		}
		result += "\n    usun z konca             | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// usuñ losowo w liœcie
		////////////////////////////////
		time = 0;
		for (int i = 1000; i > 0; i--)
		{
			timer.Start();
			Lelement::delRand(*&head, n);
			time += timer.End();
			Lelement::addBefore(rand(), *&head);										//dodaj z powrotem
		}
		result += "\n    usun losowo              | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// wyszukaj
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			Lelement::find(rand(), *&head);
			time += timer.End();
		}
		result += "\n    wyszukaj                 | " + showTime(time, n);
		cout << ".][k";

		//////////////////////
		//                  //
		//  kopiec binarny  //
		//                  //
		//////////////////////
		//cout << "Kopiec binarny:";
		result += '\n' + separator + "\n  Kopiec binarny             |\n" + separator;

		////////////////////////////////
		//dodaj do kopca
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			heap.add(rand());
			time += timer.End();
			heap.del();																	//usuñ z powrotem
		}
		result += "\n    dodaj                    | " + showTime(time, n);
		cout << ".";

		////////////////////////////////
		// usuñ z kopca
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			heap.del();
			time += timer.End();
			heap.add(rand());															//dodaj z powrotem
		}
		result += "\n    usun                     | " +
			showTime(time, n);
		cout << ".";

		////////////////////////////////
		// wyszukaj
		////////////////////////////////
		time = 0;
		for (int i = 0; i < 1000; i++)
		{
			timer.Start();
			heap.find(rand());
			time += timer.End();
		}
		result += "\n    wyszukaj                 | " + 
			showTime(time, n) +
			'\n' + separator + '\n' + separator + '\n';
		cout << ".]\n";

	}
	system("cls");
	return result;
}

int main()
{
	int menu = -1;
	int n;
	bool loop = true;
	while (loop)
	{
		switch (menu)
		{
		case 1://///////////////////////////////////////////////////////////////////////////////// tablica
		{
			system("cls");
			showMenu(menu, 0);
			cin >> menu;
			switch (menu)
			{
			case 1:																				//dodaj
			{
				system("cls");
				showMenu(1, 1);
				cin >> n;																		//podaj liczbe elementow do przetworzenia
				time = 0; 
				for (int i = 0; i < n; i++)														//dodaj przed
				{
					timer.Start();
					table.addBefore(rand());
					time += timer.End();
				}
				cout << "\nCzas  dodawania (calosc | srednio 1 element):\n\nz przodu: " << showTime(time, n) << '\n';
				time = 0;
				for (int i = 0; i < n; i++)														//dodaj po
				{
					timer.Start();
					table.addAfter(rand());
					time += timer.End();
				}
				cout << "z tylu:   " << showTime(time, n) << '\n';
				time = 0;
				for (int i = 0; i < n; i++)														//dodaj losowo
				{
					timer.Start();
					table.addRand(rand());
					time += timer.End();
				}
				cout << "losowo:   " << showTime(time, n) << '\n';
				system("pause");
				menu = 1;
				break;
			}
			case 2:																				//usun
			{
				system("cls");
				showMenu(1, 1);
				cin >> n;																		//podaj liczbe elementow do przetworzenia
				if (n > table.length)
					n = table.length;
				time = 0;
				for (int i = 0; i < n; i++)														//usun przed
				{
					timer.Start();
					table.delBefore();
					time += timer.End();
				}
				cout << "\nCzas  usuwania (calosc | srednio 1 element):\n\nz przodu: " << showTime(time, n) << '\n';
				time = 0;
				for (int i = 0; i < n; i++)														//usun po
				{
					timer.Start();
					table.delAfter();
					time += timer.End();
				}
				cout << "z tylu:   " << showTime(time, n) << '\n';
				time = 0;
				for (int i = 0; i < n; i++)														//usun losowo
				{
					timer.Start();
					table.delRand();
					time += timer.End();
				}
				cout << "losowo:   " << showTime(time, n) << '\n';
				system("pause");
				menu = 1;
				break;
			}
			case 3:																				//wyszukaj
			{
				system("cls");
				showMenu(1, 1);
				cin >> n;																		//podaj liczbe elementow do przetworzenia
				time = 0;
				for (int i = 0; i < n; i++)														//wyszukaj
				{
					timer.Start();
					cout << table.find(rand())<<' ';
					time += timer.End();
				}
				cout << "\nWyszukiwanie (calosc | srednio 1 element):\n\nczas: " << showTime(time, n) << '\n';
				system("pause");
				menu = 1;
				break;
			}
			case 4:																				//wyswietl
			{
				system("cls");
				table.display();
				system("pause");
				menu = 1;
				break;
			}
			case 5:																				//odczytaj
			{
				string name;
				cout << "podaj nazwe pliku:";
				cin >> name;
				table.open(name);
				system("pause");
				system("cls");
				menu = 1;
				break;
			}
			case 6:																				//zapisz
			{
				string name;
				cout << "podaj nazwe pliku:";
				cin >> name;
				table.save(name);
				system("pause");
				system("cls");
				menu = 1;
				break;
			}
			case 7:																				//wroc
			{
				menu = -1;
				break;
			}
			default:
			{
				menu = 1;
				break;
			}
			}
			break;
		}
		case 2://///////////////////////////////////////////////////////////////////////////////// lista
		{
			system("cls");
			showMenu(menu, 0);
			cin >> menu;
			switch (menu)
			{
			case 1:																				//dodaj
			{
				system("cls");
				showMenu(2, 1);
				cin >> n;																		//podaj liczbe elementow do przetworzenia
				time = 0;
				for (int i = 0; i < n; i++)														//dodaj przed
				{
					timer.Start();
					Lelement::addBefore(rand(), *&head);
					time += timer.End();
				}
				cout << "\nCzas  dodawania (calosc | srednio 1 element):\n\nz przodu: " << showTime(time, n) << '\n';
				time = 0;
				for (int i = 0; i < n; i++)														//dodaj po
				{
					timer.Start();
					Lelement::addAfter(rand(), *&head);
					time += timer.End();
				}
				cout << "z tylu:   " << showTime(time, n) << '\n';
				time = 0;
				for (int i = 0; i < n; i++)														//dodaj losowo
				{
					timer.Start();
					Lelement::addRand(rand(), *&head, i);
					time += timer.End();
				}
				cout << "losowo:   " << showTime(time, n) << '\n';
				system("pause");
				menu = 2;
				break;
			}
			case 2://usun
			{
				system("cls");
				showMenu(2, 1);
				cin >> n;																		//podaj liczbe elementow do przetworzenia
				time = 0;
				for (int i = 0; i < n; i++)														//usun przed
				{
					timer.Start();
					Lelement::addBefore(rand(), *&head);
					time += timer.End();
				}
				cout << "\nCzas  usuwania (calosc | srednio 1 element):\n\nz przodu: " << showTime(time, n) << '\n';
				time = 0;
				for (int i = 0; i < n; i++)														//usun po
				{
					timer.Start();
					Lelement::addAfter(rand(), *&head);
					time += timer.End();
				}
				cout << "z tylu:   " << showTime(time, n) << '\n';
				time = 0;
				for (int i = n; i > 0; i--)														//usun losowo
				{
					timer.Start();
					Lelement::delRand(*&head, i);
					time += timer.End();
				}
				cout << "losowo:   " << showTime(time, n) << '\n';
				system("pause");
				menu = 2;
				break;
			}
			case 3://wyszukaj
			{
				system("cls");
				showMenu(2, 1);
				cin >> n;																		//podaj liczbe elementow do przetworzenia
				time = 0;
				for (int i = 0; i < n; i++)														//wyszukaj
				{
					timer.Start();
					Lelement::find(rand(), *&head);
					time += timer.End();
				}
				cout << "\nWyszukiwanie (calosc | srednio 1 element):\n\nczas: " << showTime(time, n) << '\n';
				system("pause");
				menu = 2;
				break;
			}
			case 4:																				//wyswietl
			{
				system("cls");
				Lelement::display(*&head);
				system("pause");
				menu = 2;
				break;
			}
			case 5:																				//odczytaj
			{
				string name;
				cout << "podaj nazwe pliku:";
				cin >> name;
				head->open(name, *&head);
				system("pause");
				system("cls");
				menu = 2;
				break;
			}
			case 6:																				//zapisz
			{
				string name;
				cout << "podaj nazwe pliku:";
				cin >> name;
				head->save(name, *&head);
				system("pause");
				system("cls");
				menu = 2;
				break;
			}
			case 7:																				//wroc
			{
				menu = -1;
				break;
			}
			default:
			{
				menu = 2;
				break;
			}
			}
			break;
		}
		case 3://///////////////////////////////////////////////////////////////////////////////// kopiec binarny
		{
			system("cls");
			showMenu(menu, 0);
			cin >> menu;
			switch (menu)
			{
			case 1:																				//dodaj
			{
				system("cls");
				showMenu(3, 1);
				cin >> n;
				time = 0;
				for (int i = 0; i < n; i++)														//dodaj
				{
					timer.Start();
					heap.add(rand());
					time += timer.End();
				}
				cout << "\nCzas dodawania (calosc | srednio 1 element):\n\njako ostatni: " << showTime(time, n) << '\n';
				system("pause");
				menu = 3;
				break;
			}
			case 2:																				//usun
			{
				system("cls");
				showMenu(3, 1);
				cin >> n;
				time = 0;
				for (int i = 0; i < n; i++)														//usun
				{
					timer.Start();
					heap.del();
					time += timer.End();
				}
				cout << "\nCzas usuwania (calosc | srednio 1 element):\n\nwstawiajac do korzenia: " << showTime(time, n) << '\n';
				system("pause");
				menu = 3;
				break;
			}
			case 3:																				//wyszukaj
			{
				system("cls");
				showMenu(3, 1);
				cin >> n;
				time = 0;
				for (int i = 0; i < n; i++)														//wyszukaj
				{
					timer.Start();
					heap.find(rand());
					time += timer.End();
				}
				cout << "\nWyszukiwanie (calosc | srednio 1 element):\n\nczas: " << showTime(time, n) << '\n';
				system("pause");
				menu = 3;
				break;
			}
			case 4:																				//wyswietl
			{
				system("cls");
				heap.display();
				system("pause");
				menu = 3;
				break;
			}
			case 5:																				//odczytaj
			{
				string name;
				cout << "podaj nazwe pliku:";
				cin >> name;
				system("pause");
				menu = 3;
				break;
			}
			case 6:																				//zapisz
			{
				string name;
				cout << "podaj nazwe pliku:";
				cin >> name;
				system("pause");
				menu = 3;
				break;
			}
			case 7:																				//wroc
			{
				menu = -1;
				break;
			}
			default:
			{
				menu = 3;
				break;
			}
			}
			break;
		}
		case 4://///////////////////////////////////////////////////////////////////////////////// wyswietl wszystkie
		{
			menu = 1;
			break;
		}
		case 5://///////////////////////////////////////////////////////////////////////////////// autostatystyka
		{
			system("cls");
			string s = autostatystyka();
			//cout << s;
			ofstream file;
			file.open("autostatystyka.txt", ios::app);
			file << s;
			file.close();
			system("notepad.exe autostatystyka.txt");
			menu = 0;
			break;
		}
		case 6://///////////////////////////////////////////////////////////////////////////////// wyjdŸ
		{
			return 0;
		}
		default://///////////////////////////////////////////////////////////////////////////////// poka¿ menu g³ówne
		{
			system("cls");
			showMenu(0, 0);
			cin >> menu;
			break;
		}
		}
		
	}
	return 0;
}
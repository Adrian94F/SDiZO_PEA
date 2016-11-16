#include "Header.h"

void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}
void color(int c)
{
	HANDLE hCmdOut;
	hCmdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCmdOut, c);
}
void frame(int x0, int y0, int x, int y, int margin, int c, string msg)
{
	color(c);
	vector <string> strings;
	size_t i = 0;
	while (i != string::npos)
	{
		i = msg.find_first_of('\n');
		if (i == string::npos)
			strings.push_back(msg);
		else
		{
			strings.push_back(msg.substr(0, i));
			msg = msg.substr(i + 1, msg.length() - 1);
		}
	}
	for (int i = 0; i < y; i++)//petla po wysokoœci
	{
		gotoxy(x0, y0 + i);
		for (int j = 0; j <= x; j++)//petla po dlugosci
		{
			cout << " ";
		}
	}
	for (int i = 0; i < strings.size(); i++)
	{
		gotoxy(x0, y0 + i);
		for (int j = 0; j < margin; j++)
			cout << " ";
		cout << strings[i];
	}
	color(15);
	gotoxy(0, 0);
}
string input(int x0, int y0, int x, int inputcolor)
{
	gotoxy(x0, y0);
	color(inputcolor);
	for (int i = 0; i <= x; i++)
		cout << " ";
	gotoxy(x0 + 1, y0);
	string str;
	cin >> str;
	cin.ignore();
	color(15);
	return str;
}
char menu(string msg, int size)
{
	int tx0 = 15, ty0 = 1, tx = 45, ty = 8, tmargin = 5, tcolor = 47;
	int fx0 = 18, fy0 = 10, fx = 38, framecolor = 27, margin = 2;
	int ix0 = 50, iy0 = 11 + size, ix = 6, inputcolor = 79;
	string titlemsg = "\nProjektowanie efektywnych algorytmów\n\n           \"Komiwoja¿er\"                 \n\n     Adrian Frydmañski (209865)          \n     Dawid  Gracek     (209929)          \n ";
	frame(tx0, ty0, tx, ty, tmargin, tcolor, titlemsg);
	frame(fx0, fy0, fx, size, margin, framecolor, msg);
	return input(ix0, iy0, ix, inputcolor)[0];
}
int input(string msg, int size)
{
	int fx0 = 18, fy0 = 5, fx = 38, framecolor = 27, margin = 2;
	int ix0 = 50, iy0 = 6 + size, ix = 6, inputcolor = 79;
	frame(fx0, fy0, fx, size, margin, framecolor, msg);
	int value;
	value = atoi(input(ix0, iy0, ix, inputcolor).c_str());
	return value;
}
void window(int x0, int y0, int x, int y, string title, string msg, string btn)
{
	frame(x0, y0, x, 1, 1, 0x9F, title);
	frame(x0, y0 + 1, x, y + 4, 2, 0xCF, "\n" + msg);
	int btnx0 = (x - (int)btn.length()) / 2 + x0 + 1;
	frame(btnx0, y0 + 3 + y, (int)btn.length() - 1, 1, 0, 0x9F, btn);
	while (_getch() != 13);
}
string getextension(string name)
{
	size_t found = name.find_last_of(".");
	return name.substr(found + 1);
}
int main(int argc, char **argv)
{
	char key = 'm';
	srand(time(NULL)); //inicjacja randa
	setlocale(LC_ALL, ""); //w³¹czenie polskich znaków
	string menuMsg = "\nWybierz, co chcesz zrobiæ:\n ----------------------------------\n  1. wczytaj miasta\n  2. poka¿ graf\n  3. przegl¹d zupe³ny\n ---(projekt)----------------------\n  4. sylumowane wy¿arzanie\n  5. tabu search\n  6. algorytm genetyczny\n ---(laboratorium)-----------------\n  7. metoda podzia³ów i ogarniczeñ\n  0. wyjdŸ\n ";
	int menuSize = 14;
	bool test = false;

	int totalsize = 0, itemsnum = 0, score = 0, *komi = nullptr;
	MyTimer timer;
	//MyList sizes, values;
	MatrixGraph graph;
	ifstream file;
	string name = "", filename = "\nPodaj nazwê pliku:\n";
	string file_name[10] = { "tsp4.txt" ,"k.txt", "tsp10.txt", "burma14.tsp", "gr17.txt", "fri26_d.txt", "bays29.txt", "dantzig42.txt", "att48.txt", "pr76.tsp" };
	const int mSize = 7;
	int m[mSize] = { 4,8,12,16,20,24,28 };
	long double times[4] = { 0,0,0,0 };
	unsigned gaParams[4] = { 0,0,0,0 };
	float weights[4] = { 0,0,0,0 };
	vector<unsigned char> solution;

	while (key != 27)
	{
		system("cls");
		key = menu(menuMsg, menuSize);
		system("cls");
		switch (key)
		{
		case '1':																	//wczytaj miasta
			frame(5, 1, (int)filename.length() + 4, 3, 2, 0x61, filename);
			name = input(5, 5, 16, 79);
			file.open(name.c_str());
			if (file.is_open())
			{
				KomiwojazerLoad(file, graph, getextension(name));					// wczytaj problem komiwoja¿era z pliku
				file.close();
			}
			else
				window(8, 3, 25, 1, "Uwaga!", "Nie znaleziono pliku!", "[OK]");
			break;

		case '2':																	//poka¿ graf
			//graph.DisplayMatrix();
			//window(8, 3, 55, 1, "Uwaga!", "Zamkniêcie okna grafu powoduje zamkniêcie programu.", "[OK]");
			GLdisplay(argc, argv, graph, solution, name);
			break;

		case '3':																	//przegl¹d zupe³ny
			solution.clear();
			key = menu("\nWybierz, co chcesz zrobiæ:\n  1. licz dla wczytanego grafu\n  2. licz dla losowych instancji\n  0. powrót\n ", 6);
			system("cls");
			switch (key)
			{
			case '0': break;
			case '1':
				komi = KomiwojazerBrute(graph);
				KomiwojazerDisplayEdges(komi, graph);
				cout << "Koszt: " << KomiwojazerGetWeight(komi, graph);
				break;
			case '2':
				cout << "Czas wykonania dla:\n";
				for (int i = 0; i < 5; i++)
				{
					int n = 2 * (i + 1);
					graph.Generate(n);
					timer.Start();
					KomiwojazerBrute(graph);
					times[0] = timer.End();
					cout << ' ' << setw(2) << n << " wierzcho³ków: " << times[0] << " ms\n";
				}
				break;
			}
			for (int i = 0; i <= graph.GetSize(); i++)
				solution.push_back(komi[i]);
			while (_getch() != 13);
			break;

		case '4':																	//symulowane wy¿arzanie
			solution.clear();
			//testy dla kilku parametrów alfa
			cout << name << '\n';
			for (int i = 0; i < 4; i++)
				times[i] = 0;
			for (int i = 0; i < 10; i++)
			{
				timer.Start();
				komi = KomiwojazerSimulatedAnnealing(graph, 0.001, 10000, 0.9);
				times[0] += timer.End();
				weights[0] += KomiwojazerGetWeight(komi, graph);
				cout << ".";
				timer.Start();
				komi = KomiwojazerSimulatedAnnealing(graph, 0.001, 10000, 0.95);
				times[1] += timer.End();
				weights[1] += KomiwojazerGetWeight(komi, graph);
				cout << ".";
				timer.Start();
				komi = KomiwojazerSimulatedAnnealing(graph, 0.001, 10000, 0.995);
				times[2] += timer.End();
				weights[2] += KomiwojazerGetWeight(komi, graph);
				cout << ".";
				timer.Start();
				komi = KomiwojazerSimulatedAnnealing(graph, 0.001, 10000, 0.999);
				times[3] += timer.End();
				weights[3] += KomiwojazerGetWeight(komi, graph);
				cout << ".\n";
			}
			times[0] /= 10;
			times[1] /= 10;
			times[2] /= 10;
			times[3] /= 10;
			weights[0] /= 10;
			cout << " 0,9:\nkoszt: " << weights[0];
			cout << "\nczas: " << times[0] << "ms";
			cout << "\n 0,95:\n";

			weights[1] /= 10;
			cout << "koszt: " << weights[1];
			cout << "\nczas: " << times[1] << "ms";
			cout << "\n 0,995:\n";

			weights[2] /= 10;
			cout << "koszt: " << weights[2];
			cout << "\nczas: " << times[2] << "ms";
			cout << "\n 0,999:\n";

			weights[3] /= 10;
			cout << "koszt: " << weights[3];
			cout << "\nczas: " << times[3] << "ms";
			solution.clear();
			for (int i = 0; i <= graph.GetSize(); i++)
				solution.push_back(komi[i]);
			while (_getch() != 13);
			break;

		case '7':																	//metoda podzia³u i ograniczeñ
			solution.clear();
			key = menu("\nWybierz, co chcesz zrobiæ:\n  1. licz dla wczytanego grafu\n  2. licz dla losowych instancji\n  3. licz dla przyk³adowych plików\n  0. powrót\n ", 7);
			system("cls");
			switch (key)
			{
			case '1':
				times[0] = 0;
				timer.Start();
				solution = KomiwojazerBranchAndBound(graph);
				times[0] = timer.End();
				KomiwojazerDisplayEdges(solution, graph);
				cout << "\nKoszt: " << KomiwojazerGetWeight(solution, graph);
				cout << "\nCzas: " << times[0] << " ms";
				break;
			case '2':
				KomiwojazerBBRandomTest(mSize, m, 100);
				break;
			case '3':
				cout << "********** Tryb Testowania dla Branch & Bound **********\n";
				for (auto n = 0; n < 10; n++)
				{
					file.open(file_name[n].c_str());
					if (file.is_open())
					{
						KomiwojazerLoad(file, graph, getextension(file_name[n]));
						times[0] = 0;
						for (auto i = 0; i < 10; i++)
						{
							timer.Start();
							solution = KomiwojazerBranchAndBound(graph);
							times[0] += timer.End();
						}
						times[0] /= 10;
						cout << file_name[n] << " :::::::::::\n Œcie¿ka: ";
						KomiwojazerDisplayEdges(solution, graph);
						cout << "\n  Koszt: " << KomiwojazerGetWeight(solution, graph);
						cout << "\n  Czas: " << times[0] << " ms\n";
					}
					else
					{
						window(8, 3, 25, 1, "Uwaga!", "Nie znaleziono pliku!", "[OK]");
						break;
					}
				}
				cout << "\nGotowe";
				break;
			case '0':
				break;
			}

			while (_getch() != 13);
			break;
		case '5':																	//tabu search
			solution.clear();
			key = menu("\nWybierz, co chcesz zrobiæ:\n  1. licz dla wczytanego grafu\n  2. licz dla przyk³adowych plików\n  0. powrót\n ", 6);
			system("cls");
			switch (key)
			{
			case '1':
				times[0] = 0;
				timer.Start();
				solution = KomiwojazerTabuSearch(graph, graph.GetSize()*graph.GetSize() * 100);
				times[0] = timer.End();
				KomiwojazerDisplayEdges(solution, graph);
				cout << "\nKoszt: " << KomiwojazerGetWeight(solution, graph);
				cout << "\nCzas: " << times[0] << " ms";
				break;
			case '2':
				cout << "********** Tryb Testowania dla tabu search **********\n";
				for (auto n = 0; n < 10; n++)
				{
					file.open(file_name[n].c_str());
					if (file.is_open())

					{
						KomiwojazerLoad(file, graph, getextension(file_name[n]));
						times[0] = 0;
						for (auto i = 0; i < 10; i++)
						{
							timer.Start();
							solution = KomiwojazerTabuSearch(graph, graph.GetSize()*graph.GetSize() * 100);
							times[0] += timer.End();
						}
						times[0] /= 10;
						cout << file_name[n] << " :::::::::::\n Œcie¿ka: ";
						KomiwojazerDisplayEdges(solution, graph);
						cout << "\n  Koszt: " << KomiwojazerGetWeight(solution, graph);
						cout << "\n  Czas: " << times[0] << " ms\n";
					}
					else
					{
						window(8, 3, 25, 1, "Uwaga!", "Nie znaleziono pliku!", "[OK]");
						break;
					}
				}
				cout << "\nGotowe";
				break;
			case '0':
				break;
			}
			while (_getch() != 13);
			break;
		case '6':																	//algorytm genetycznny
			solution.clear();
			key = menu("\nWybierz, co chcesz zrobiæ:\n  1. licz dla wczytanego grafu\n  2. testy\n  0. powrót\n ", 6);
			system("cls");
			switch (key)
			{
			case '1':
				times[0] = 0;
				gaParams[0] = input("\nPodaj wielkoœæ populacji\n", 3);
				gaParams[1] = input("\nPodaj prawdopodobieñstwo krzy¿owania\n", 3);
				gaParams[2] = input("\nPodaj prawdopodobieñstwo mutacji\n", 3);
				gaParams[3] = input("\nPodaj optimum\n", 3);
				timer.Start();
				system("cls");
				solution = KomiwojazerGenetic(graph, gaParams[0], gaParams[1], gaParams[2], true);
				times[0] = timer.End();
				
				KomiwojazerDisplayEdges(solution, graph);
				cout << "\nKoszt: " << KomiwojazerGetWeight(solution, graph) << "\nB³¹d: " << (((KomiwojazerGetWeight(solution, graph) - (gaParams[3]))) / gaParams[3]) * 100 << "%\nCzas: " << times[0] << " ms";
				break;
			case '2':
				key = menu("\nWybierz, co chcesz zrobiæ:\n  1. szeroki zakres (wczytany graf)\n  2. test dla wielu plików\n  0. powrót\n ", 6);
				system("cls");
				switch (key)
				{
				case '1':
				{
					gaParams[3] = input("\nPodaj optimum\n", 3);
					int populacje[] = { 10,100,1000,10000 };
					int krzyzowania[] = { 20,40,60,80,100 };
					int mutacje[] = { 0,5,10,15,20,25,30,35,40,45,50 };
					float best = FLT_MAX;
					for (int i = 0; i < 4; i++)							//pêtla po populacjach
					{
						cout << "\nPopulacja: " << populacje[i] << "\n--------------------------------\n";
						for (int k = 0; k < 4; k++)								//pêtla po procencie krzy¿owania
						{
							for (int m = 0; m < 11; m++)							// pêtla po procencie mutacji
							{
								times[0] = 0;
								times[1] = 0;
								times[2] = 0;
								for (auto j = 0; j < 10; j++)
								{
									timer.Start();
									solution = KomiwojazerGenetic(graph, populacje[i], krzyzowania[k], mutacje[m], false);
									times[0] += timer.End();
									times[1] += KomiwojazerGetWeight(solution, graph);
									times[2] += ((KomiwojazerGetWeight(solution, graph) - (gaParams[3])) / gaParams[3]) * 100;
									if (times[1] < best)
										best = times[1];
								}

								times[0] /= 10;		//œredni czas
								times[1] /= 10;
								times[2] /= 10;
								/*timer.Start();
								solution = KomiwojazerGenetic(graph, i, j);
								times[0] = timer.End();*/
								cout << "Krzy¿.: " << setw(3) << krzyzowania[k] << "% - " << "Mut.: " << setw(3) << mutacje[m] << "% koszt: " << setprecision(2) << fixed << times[1] << " b³¹d: " << setprecision(2) << fixed << setw(6) << times[2] << "% czas: " << setprecision(2) << fixed << setw(6) << times[0] << " ms\n";
							}
							cout << endl;
						}
						cout << "*** Best: " << best << endl;
					}
				}
				break;
				case '2':
				{
					for (auto n = 0; n < 10; n++)
					{
						file.open(file_name[n].c_str());
						int koszty[10] = { 200,16,212,30,2085,937,2020,699,10628,108159 };
						if (file.is_open())
						{
							KomiwojazerLoad(file, graph, getextension(file_name[n]));
							times[0] = 0;
							for (auto i = 0; i < 10; i++)					//10 powtórzeñ
							{
								timer.Start();
								solution = KomiwojazerGenetic(graph, 1000, 60, 30, false);
								times[0] += timer.End();
							}
							times[0] /= 10;
							cout << "Plik: " << file_name[n] << ",\n  œcie¿ka: ";
							KomiwojazerDisplayEdges(solution, graph);
							cout << "\n   koszt: " << setw(6) << KomiwojazerGetWeight(solution, graph) << "  B³¹d: " << setprecision(2) << fixed << (((KomiwojazerGetWeight(solution, graph) - (koszty[n]))) / koszty[n]) * 100 << "%, czas: " << setprecision(2) << fixed << times[0] << " ms\n";
						}
						else
						{
							window(8, 3, 25, 1, "Uwaga!", "Nie znaleziono pliku!", "[OK]");
							break;
						}
					}
					cout << "\nGOTOWE!\n";
				}
				break;
				case '3':
				{
					for (auto n = 5; n < 7; n++)
					{
						file.open(file_name[n].c_str());
						int koszty[10] = { 200,16,212,33,2085,937,2020,699,10628,108159 };
						int populacje[] = { 5,50,500,5000 };
						int krzyzowania[] = { 20,40,60,80,100 };
						int mutacje[] = { 0,10,20,30,40,50 };
						float best = FLT_MAX;
						if (file.is_open())
						{
							KomiwojazerLoad(file, graph, getextension(file_name[n]));
							cout << "Plik: " << file_name[n] << endl;

							for (int i = 0; i < 4; i++)							//pêtla po populacjach
							{
								cout << "\nPopulacja: " << populacje[i] << "\n--------------------------------\n";
								for (int k = 0; k < 5; k++)								//pêtla po procencie krzy¿owania
								{
									for (int m = 0; m < 6; m++)							// pêtla po procencie mutacji
									{
										times[0] = 0;
										for (auto j = 0; j < 10; j++)
										{
											timer.Start();
											solution = KomiwojazerGenetic(graph, populacje[i], krzyzowania[k], mutacje[m], false);
											times[0] += timer.End();
											if (KomiwojazerGetWeight(solution, graph) < best)
												best = KomiwojazerGetWeight(solution, graph);
										}

										times[0] /= 10;		//œredni czas
															/*timer.Start();
															solution = KomiwojazerGenetic(graph, i, j);
															times[0] = timer.End();*/
										cout << "Krzy¿owania: " << setw(6) << krzyzowania[k] << "% - " << "Mutacje: " << setw(6) << mutacje[m] << "% - koszt: " << setw(6) << KomiwojazerGetWeight(solution, graph) << "  B³¹d: " << setprecision(2) << fixed << (((KomiwojazerGetWeight(solution, graph) - (koszty[n]))) / koszty[n]) * 100 << "%, czas: " << setprecision(2) << fixed << times[0] << " ms\n";
									}
									cout << endl;
								}
								cout << "*** Best: " << best << endl;
							}
						}
						else
						{
							window(8, 3, 25, 1, "Uwaga!", "Nie znaleziono pliku!", "[OK]");
							break;
						}
					}
					cout << "\nGOTOWE!\n";
				}
				break;
				}
			case '0':
				break;
			}
			while (_getch() != 13);
			break;
		case '8':																	//algorytm mierzwixowy
			solution.clear();
			window(8, 3, 33, 1, "Proszê, iæ stont!", "Ten ficzer jeszcze nie dzia³a.", "[Dobrze, rozumiem]");
			break;
		case '0':																	//wyjdŸ
			return 0;
		default:																	//gdzie z paluchami?!
			window(8, 3, 42, 1, "Zb³¹dzi³eœ, m³ody padawanie...", "Wybierz inny numer z przedzia³u 0 - 7.", "[OK]");
			break;
		}

	}
	return 0;
}
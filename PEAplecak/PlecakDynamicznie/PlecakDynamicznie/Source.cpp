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
	for (int i = 0; i < y; i++)//petla po wysokości
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
	string titlemsg = "\nProjektowanie efektywnych algorytmów\n\n         \"Problem plecakowy\"             \n\n     Adrian Frydmański (209865)          \n     Dawid Gracek (209929)               \n ";
	frame(tx0, ty0, tx, ty, tmargin, tcolor, titlemsg);
	frame(fx0, fy0, fx, size, margin, framecolor, msg);
	return input(ix0, iy0, ix, inputcolor)[0];
}
void window(int x0, int y0, int x, int y, string title, string msg, string btn)
{
	frame(x0, y0, x, 1, 1, 0x9F, title);
	frame(x0, y0 + 1, x, y + 4, 2, 0xCF, "\n" + msg);
	int btnx0 = (x - btn.length()) / 2 + x0 + 1;
	frame(btnx0, y0 + 3 + y, btn.length() - 1, 1, 0, 0x9F, btn);
	while (_getch() != 13);
}
string getextension(string name)
{
	size_t found = name.find_last_of(".");
	return name.substr(found + 1);
}
void main()
{
	char key = 'm';
	srand(time(NULL)); //inicjacja randa
	setlocale(LC_ALL, ""); //włączenie polskich znaków
	string menuMsg = "\nWybierz, co chcesz zrobić:\n  1. wczytaj listę rzeczy\n  2. pokaż listę rzeczy\n  3. przegląd zupełny\n  4. programowanie dynamiczne\n  5. FPTAS\n  0. wyjdź\n ";
	int menuSize = 9;
	int testmode = 2;
	int totalsize = 0, itemsnum = 0;
	unsigned long long score = 0;
	vector<short>c_score;
	MyTimer timer;
	vector<int> sizes, values;
	ifstream file;
	string name = "", filename = "\nPodaj nazwę pliku:\n";
	double speed = 0;

	while (key != 27)
	{
		system("cls");
		key = menu(menuMsg, menuSize);
		system("cls");
		switch (key)
		{
		case '1':																	//wczytaj listę rzeczy
			frame(5, 1, filename.length() + 4, 3, 2, 0x61, filename);
			name = input(5, 5, 16, 79);
			file.open(name.c_str());
			if (file.good())
			{
				PlecakLoad(file, sizes, values, totalsize, itemsnum);
				file.close();
			}
			else
				window(8, 3, 25, 1, "Uwaga!", "Nie znaleziono pliku!", "[OK]");
			while (_getch() != 13);
			break;

		case '2':
			PlecakDisplay(sizes, values, totalsize, itemsnum);
			while (_getch() != 13);
			break;

		case '3':																	// przegląd zupełny
			timer.Start();
			score = PlecakBrute(sizes, values, totalsize, itemsnum);
			speed = timer.End();

			PlecakDisplaySolution(score, sizes, values, totalsize, itemsnum);		// pokaż listę rzeczy
			cout << "czas: " << timer.Convert(speed) << endl;
			while (_getch() != 13);
			break;

		case '4':																	// programowanie dynamiczne
			key = menu("\nWybierz, co chcesz zrobić:\n  1. testuj dla wczytanego plecaka\n  2. testuj dla losowych instancji\n  3. testuj więcej losowych\n  0. wyjdź\n", 7);
			system("cls");
			switch (key)
			{
			case '1': 
				timer.Start();
				c_score = PlecakDynamic(sizes, values, totalsize, itemsnum);
				speed = timer.End();
				PlecakDisplaySolution(c_score, sizes, values, totalsize, itemsnum);		// pokaż listę rzeczy
				cout << "czas: " << timer.Convert(speed) << endl;
				break;
			case '2': 
				PlecakTest(false, true); 
				cout << "\nGotowe";
				break;
			case '3':
				PlecakTest(true, true);
				cout << "\nGotowe";
				break;
			case '0': break;
			}
			
			while (_getch() != 13);
			break;

		case '5':																	// FPTAS
			float ε;
			key = menu("\nWybierz, co chcesz zrobić:\n  1. testuj dla wczytanego plecaka\n  2. testuj dla losowych instancji\n  3. testuj więcej losowych\n  0. wyjdź\n", 7);
			system("cls");
			switch (key)
			{
			case '1':
				cout << "Podaj wartość epsilon [0,1]: ";
				cin >> ε;
				timer.Start();
				c_score = PlecakFPTAS(sizes, values, totalsize, itemsnum, ε);
				speed = timer.End();
				PlecakDisplaySolution(c_score, sizes, values, totalsize, itemsnum);		// pokaż listę rzeczy
				cout << "czas: " << timer.Convert(speed) << endl;
				break;
			case '2':
				PlecakTest(false, false);
				cout << "\nGotowe";
				break;
			case '3':
				PlecakTest(true, false);
				cout << "\nGotowe";
				break;
			case '0': break;
			}

			while (_getch() != 13);
			break;
		case '0':																	// wyjdź
			return;

		default:																	// gdzie z paluchami bezdomna pokrako?!
			window(8, 3, 42, 1, "Zbłądziłeś, młody padawanie...", "Wybierz inny numer z przedziału 0 - 5.", "[OK]");
			break;
		}

	}

}
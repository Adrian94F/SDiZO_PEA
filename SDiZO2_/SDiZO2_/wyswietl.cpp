#include "stdafx.h"

void wyswietlVec(vector<int> input, int koniec)
{
	cout << input[koniec] << " ";
}
void wyswietlKrawedz(vector<Krawedz> input)
{
	cout <<
		"|                                    |\n"
		"| Poczatek:      Koniec:      Waga:  |\n" 
		"| ---------------------------------  |\n";
	for (int i = 0; i < input.size(); i++)
		cout << 
		"| " << setw(9) << input[i].poczatek << "    " << setw(9) << input[i].koniec << "  " << setw(9) << input[i].waga << "  |\n";
	cout <<
		"|                                    |\n"
		"#------------------------------------#\n";
}
#include "stdafx.h"

int main()
{
	setlocale(LC_ALL, ""); // w³¹czenie polskich znaków
	srand(time(NULL));
	GrafLista graflista;
	GrafMacierz grafmacierz;
	menu(&graflista, &grafmacierz);
	return 0;
}
#include "stdafx.h"

int main()
{
	setlocale(LC_ALL, ""); // w��czenie polskich znak�w
	srand(time(NULL));
	GrafLista graflista;
	GrafMacierz grafmacierz;
	menu(&graflista, &grafmacierz);
	return 0;
}
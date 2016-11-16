// Adrian Frydmañski 209865
#include "stdafx.h"
#include "Proj3.h"


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	setlocale(LC_ALL, ""); // w³¹czenie polskich znaków
	Proj3* proj = new Proj3();
	proj->start();
	delete proj;

	return 0;
}


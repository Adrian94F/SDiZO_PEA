// Adrian Frydma�ski 209865
#include "stdafx.h"
#include "Proj3.h"


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	setlocale(LC_ALL, ""); // w��czenie polskich znak�w
	Proj3* proj = new Proj3();
	proj->start();
	delete proj;

	return 0;
}


// Project SDiZO3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Project.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	CProject* project = new CProject();
	project->start();
	delete project;

	return 0;
}


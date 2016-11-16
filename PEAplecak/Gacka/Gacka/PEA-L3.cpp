// PEA-L3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Project.h"

int main()
{
	srand(time(NULL));

	CProject* project = new CProject();
	project->start();
	delete project;

	return 0;
}
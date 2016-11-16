#ifndef TIMER_H_
#define TIMER_H_
#include <Windows.h>

class Timer{
	LARGE_INTEGER start, stop;
public:
	void Start();
	long long End();
};

#endif
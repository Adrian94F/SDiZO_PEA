//Adrian Frydmañski - 209865

#include "stdafx.h"
#include <Windows.h>

class Timer{
	LARGE_INTEGER start, stop;
public:
	void Start()
	{
		DWORD oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&start);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
	}

	long long End()
	{
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&stop);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		return (stop.QuadPart - start.QuadPart);
	}	
};
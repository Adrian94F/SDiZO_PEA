#include "Header.h"

void MyTimer::Start()								// metoda w³¹czaj¹ca zegar
	{
		DWORD oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&start);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
	}
long double MyTimer::End()							// metoda wy³¹czaj¹ca zegar, zwracaj¹ca czas wykonanej operacji w ms.
	{
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		
		QueryPerformanceFrequency(&lpFrequency);
		QueryPerformanceCounter(&stop);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		time = stop.QuadPart - start.QuadPart;	//liczba cykli zegara
		freq = lpFrequency.QuadPart;			//czêstotliwoœæ zegara CPU
		return 1000*time/freq;					//liczba cykli zegara*1000/czêstotliwoœæ zegara = czas operacji w ms.
	}


#include "Header.h"

void MyTimer::Start()								// metoda włączająca zegar
	{
		DWORD oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&start);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
	}
long double MyTimer::End()							// metoda wyłączająca zegar, zwracająca czas wykonanej operacji w ms.
	{
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		
		QueryPerformanceFrequency(&lpFrequency);
		QueryPerformanceCounter(&stop);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		time = stop.QuadPart - start.QuadPart;	//liczba cykli zegara
		freq = lpFrequency.QuadPart;			//częstotliwość zegara CPU
		return 1000*time/freq;					//liczba cykli zegara*1000/częstotliwość zegara = czas operacji w ms.
	}


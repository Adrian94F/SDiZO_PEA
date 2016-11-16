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
	return 1000 * time / freq;					//liczba cykli zegara*1000/czêstotliwoœæ zegara = czas operacji w ms.
}
string MyTimer::Convert(long double time)
{
	string unit;
	unit = " ms";
		if (time / 1000 > 1)
		{
			unit = " s";
			time /= 1000;
			if (time / 60 > 1)
			{
				unit = " min";
				time /= 60;
				if (time / 60 > 1)
				{
					unit = " h";
					time /= 60;
					if (time / 24 > 1)
					{
						unit = " days";
						time /= 24;
					}
				}
			}
		}
	return to_string(time) + " " + unit;
}

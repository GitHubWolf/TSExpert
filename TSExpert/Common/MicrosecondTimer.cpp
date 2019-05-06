#include "StdAfx.h"

DWORD64 XGetTickCount(void)
{
	DWORD64 nTick = -1;
	DWORD64 xFrequency;

	QueryPerformanceFrequency( (LARGE_INTEGER *)&xFrequency );
	QueryPerformanceCounter( (LARGE_INTEGER *)&nTick );
	nTick = (DWORD64)(1000000 * (double)(nTick) / (double)(xFrequency));

	return nTick;
}
/*
    Lidy - A small C library for sparse matrices managing 
    Copyright (C) 2006 - Nicolas LERME

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <stdio.h>
#include "timer.h"


pSTimer CreateTimer()
{
	pSTimer Timer = (pSTimer)malloc(sizeof(struct STimer));

	if( !Timer )
		return NULL;

	Timer->m_StartTime   = 0.0;
	Timer->m_CurrentTime = 0.0;

	return Timer;
}

void InitTimer( pSTimer Timer )
{
	if( !Timer )
		return;

	Timer->m_StartTime   = 0.0;
	Timer->m_CurrentTime = 0.0;

	#ifndef _WIN32
		gettimeofday(&Timer->m_AbsoluteTime, NULL);
	#else
		QueryPerformanceFrequency(&Timer->m_TicksPerSecond);
		QueryPerformanceCounter(&Timer->m_AbsoluteTime);
	#endif
}

double GetElapsedTime( pSTimer Timer )
{
	double ElapsedTime;

	if( !Timer )
	{
		fprintf(stderr, "error: timer is NULL\n");
		return -1.0;
	}

	#ifndef _WIN32
		gettimeofday(&Timer->m_NewTime, NULL);
		ElapsedTime           = (Timer->m_NewTime.tv_usec - Timer->m_AbsoluteTime.tv_usec) / 1000000. + Timer->m_NewTime.tv_sec - Timer->m_AbsoluteTime.tv_sec;
	#else
		QueryPerformanceCounter(&Timer->m_NewTime);
		elapsedTime = ((double)Timer->m_NewTime.QuadPart - (double)Timer->m_AbsoluteTime.QuadPart) / (double)Timer->m_TicksPerSecond.QuadPart;
	#endif

	Timer->m_AbsoluteTime = Timer->m_NewTime;
	Timer->m_CurrentTime += ElapsedTime;

	return ElapsedTime;
}

double GetTime( pSTimer Timer )
{
	if( !Timer )
	{
		fprintf(stderr, "error: timer is NULL\n");
		return -1.0;
	}

	return Timer->m_CurrentTime;
}

void DeleteTimer( pSTimer Timer )
{
	if( Timer )
	{
		free(Timer);
		Timer = NULL;
	}
}

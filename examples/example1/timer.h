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

#ifndef __TIMER__H__
#define __TIMER__H__

#include <stdlib.h>
#ifndef _WIN32
	#include <sys/time.h>
#else
	#include <windows.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

/* Tiny structure allowing to time one or several instructions */
struct STimer
{
	double  m_StartTime, m_CurrentTime;
	#ifndef _WIN32
		struct timeval m_AbsoluteTime, m_NewTime;
	#else
		LARGE_INTEGER m_AbsoluteTime, m_NewTime, m_TicksPerSecond;
	#endif
};

typedef struct STimer * pSTimer;


/* This function allocates & creates a new timer */
pSTimer CreateTimer();

/* This function initialise a timer */
void InitTimer( pSTimer Timer );

/* This function retrieves a time elasped since the last of 'InitTimer' */
double GetElapsedTime( pSTimer Timer );

/* This function retrieves the current time contained in Timer */
double GetTime( pSTimer Timer );

/* This function destruct a timer */
void DeleteTimer( pSTimer Timer );

#ifdef __cplusplus
} //extern "C"
#endif

#endif //__TIMER__H__

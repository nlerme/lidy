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

#ifndef __SIMPLE_MATRIX_H__
#define __SIMPLE_MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include "lidy.h"


typedef struct _SSimpleMatrix
{
	int NbRows, NbCols;
	Real **Data;
} *SSimpleMatrix;


SSimpleMatrix CreateSimpleMatrix( const int NbRows, const int NbCols );
void DeleteSimpleMatrix( SSimpleMatrix *Matrix );
void DisplaySimpleMatrix( const SSimpleMatrix Matrix );
SSimpleMatrix MultiplySimpleMatrices( const SSimpleMatrix Matrix1, const SSimpleMatrix Matrix2 );

#endif //__SIMPLE_MATRIX_H__

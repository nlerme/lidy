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
#include "cell.h"


pSCell Lidy_CreateCell( Real Value, unsigned int RowIndex, unsigned int ColumnIndex, pSCell pNextRow, pSCell pNextColumn )
{
	pSCell Cell=NULL;


	if( !(Cell = (pSCell)malloc(sizeof(struct SCell))) )
		return NULL;

	Cell->m_Value       = Value;
	Cell->m_RowIndex    = RowIndex;
	Cell->m_ColumnIndex = ColumnIndex;
	Cell->m_pNextRow    = pNextRow;
	Cell->m_pNextColumn = pNextColumn;

	return Cell;
}

void Lidy_DisplayCellValue( pSCell Cell )
{
	if( Cell )
		printf("%f", Cell->m_Value);
}

void Lidy_DeleteCell( pSCell Cell )
{
	if( Cell )
	{
		Cell->m_pNextRow    = NULL;
		Cell->m_pNextColumn = NULL;
		free(Cell), Cell = NULL;
	}
}

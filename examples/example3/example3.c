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

#include <stdio.h>
#include <stdlib.h>
#include "lidy.h"


int main( int argc, char ** argv )
{
	/* Variables declaration */
	pSSparseMatrix SM1, SM2, SM3;
	unsigned int RowIndex, ColumnIndex;
	pSCell Cell;


	/* Init the random number generator */
	Lidy_InitRandom();

	/* Creation of sparse matrices */
	if( !(SM1 = Lidy_CreateSparseMatrix(6, 4)) )
	{
		fprintf(stderr, "Unable to create the first sparse matrix\n");
		return EXIT_FAILURE;
	}

	Lidy_SetValue(SM1, 1.5, 0, 1);
	Lidy_SetValue(SM1,   3, 0, 2);
	Lidy_SetValue(SM1,   3, 0, 3);
	Lidy_SetValue(SM1,  -2, 1, 0);
	Lidy_SetValue(SM1, -20, 1, 1);
	Lidy_SetValue(SM1, 5.3, 2, 2);
	Lidy_SetValue(SM1,  -4, 5, 2);
	Lidy_SetValue(SM1,  14, 5, 3);

	if( !(SM2 = Lidy_CreateSparseMatrix(6, 4)) )
	{
		fprintf(stderr, "Unable to create the second sparse matrix\n");
		return EXIT_FAILURE;
	}

	Lidy_SetValue(SM2,     3, 2, 1);
	Lidy_SetValue(SM2,   -10, 2, 3);
	Lidy_SetValue(SM2, -3.75, 0, 3);
	Lidy_SetValue(SM2,  7.12, 5, 1);

	/* Substract wo different sparse matrices */
	SM3 = Lidy_SubstractSparseMatrices(SM1, SM2);

	/* Display sparse matrices */
	printf("Sparse Matrix A\n");
	printf("---------------\n");
	Lidy_DisplaySparseMatrix(SM1);

	printf("\nSparse Matrix B\n");
	printf("---------------\n");
	Lidy_DisplaySparseMatrix(SM2);

	printf("\nSparseMatrix C = A - B\n");
	printf("----------------------\n");
	Lidy_DisplaySparseMatrix(SM3);

	/* Get a random cell in a sparse matrix */
	RowIndex    = (int)Lidy_Random(0, 6);
	ColumnIndex = (int)Lidy_Random(0, 4);
	Cell        = Lidy_GetCell(SM3, RowIndex, ColumnIndex);
	printf("\nRandom cell\n");
	printf("-----------\n");
	printf("C(%d, %d) = %.2f\n", RowIndex, ColumnIndex, Cell->m_Value);

	/* Destruction of sparse matrices */
	Lidy_DeleteSparseMatrix(SM1);
	Lidy_DeleteSparseMatrix(SM2);
	Lidy_DeleteSparseMatrix(SM3);

	/* Destruction of the cell */
	Lidy_DeleteCell(Cell);

	return EXIT_SUCCESS;
}

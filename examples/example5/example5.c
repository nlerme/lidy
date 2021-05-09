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
	unsigned int RowIndex, ColumnIndex, i;
	pSSparseMatrix SM1, SM2, SM3, SM4;


	/* Init the random number generator */
	Lidy_InitRandom();

	/* Creation of sparse matrices */
	if( !(SM1 = Lidy_CreateSparseMatrix(2, 4)) )
	{
		fprintf(stderr, "Unable to create the first sparse matrix\n");
		return EXIT_FAILURE;
	}

	Lidy_SetValue(SM1,  2, 0, 2);
	Lidy_SetValue(SM1,  3, 1, 0);
	Lidy_SetValue(SM1,  4, 1, 1);
	Lidy_SetValue(SM1,  1, 1, 3);

	if( !(SM2 = Lidy_CreateSparseMatrix(4, 3)) )
	{
		fprintf(stderr, "Unable to create the second sparse matrix\n");
		return EXIT_FAILURE;
	}

	Lidy_SetValue(SM2,  5, 0, 1);
	Lidy_SetValue(SM2, -2, 1, 0);
	Lidy_SetValue(SM2, -1, 1, 2);
	Lidy_SetValue(SM2,  4, 2, 0);
	Lidy_SetValue(SM2,  2, 2, 1);
	Lidy_SetValue(SM2,  1, 3, 1);
	Lidy_SetValue(SM2,  3, 3, 2);

	/* Multiply two different sparse matrices */
	SM3 = Lidy_MultiplySparseMatrices(SM1, SM2);

	/* Transpose a sparse matrix */
	SM4 = Lidy_TransposeSparseMatrix(SM3);

	/* Display sparse matrices */
	printf("Sparse Matrix A\n");
	printf("---------------\n");
	Lidy_DisplaySparseMatrix(SM1);

	printf("\nSparse Matrix B\n");
	printf("---------------\n");
	Lidy_DisplaySparseMatrix(SM2);

	printf("\nSparseMatrix C = A * B\n");
	printf("----------------------\n");
	Lidy_DisplaySparseMatrix(SM3);

	printf("\nSparseMatrix D = Transpose(C)\n");
	printf("-----------------------------\n");
	Lidy_DisplaySparseMatrix(SM4);

	/* Generate two random numbers in order to delete a whole row and a whole column */
	RowIndex    = Lidy_Random(0, 4);
	ColumnIndex = Lidy_Random(0, 3);

	printf("\n--> Clearing row %d and column %d in B\n", RowIndex, ColumnIndex);

	
	for( i=0; i<3; i++ )
		Lidy_DeleteCellInSparseMatrix(SM2, RowIndex, i);

	for( i=0; i<4; i++ )
		Lidy_DeleteCellInSparseMatrix(SM2, i, ColumnIndex);

	printf("\nSparse Matrix B\n");
	printf("---------------\n");
	Lidy_DisplaySparseMatrix(SM2);

	/* Destruction of sparse matrices */
	Lidy_DeleteSparseMatrix(SM1);
	Lidy_DeleteSparseMatrix(SM2);
	Lidy_DeleteSparseMatrix(SM3);
	Lidy_DeleteSparseMatrix(SM4);

	return EXIT_SUCCESS;
}

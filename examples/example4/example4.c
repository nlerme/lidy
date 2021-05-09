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
#include <time.h>
#include <stdlib.h>
#include "lidy.h"


int main( int argc, char ** argv )
{
	/* Variables declaration */
	pSSparseMatrix SM1, SM2, SM3, SM4;


	/* Creation of sparse matrices */
	if( !(SM1 = Lidy_CreateSparseMatrix(3, 3)) )
	{
		fprintf(stderr, "Unable to create the first sparse matrix\n");
		return EXIT_FAILURE;
	}

	Lidy_SetValue(SM1, -1, 0, 0);
	Lidy_SetValue(SM1, -7, 0, 1);
	Lidy_SetValue(SM1, 8, 2, 2);
	Lidy_SetValue(SM1,  20, 1, 2);
	Lidy_SetValue(SM1,  -4, 1, 1);
	Lidy_SetValue(SM1,  2, 0, 3);
	Lidy_SetValue(SM1,  3, 2, 0);

	if( !(SM2 = Lidy_CreateSparseMatrix(3, 3)) )
	{
		fprintf(stderr, "Unable to create the second sparse matrix\n");
		return EXIT_FAILURE;
	}

	Lidy_SetValue(SM2,  2, 0, 0);
	Lidy_SetValue(SM2,  4, 0, 2);
	Lidy_SetValue(SM2, -3, 1, 1);
	Lidy_SetValue(SM2,  19, 2, 0);
	Lidy_SetValue(SM2,  -27, 2, 2);

	/* Mutliply two different sparse matrices (A * B) and (B * A) */
	SM3 = Lidy_MultiplySparseMatrices(SM1, SM2);
	SM4 = Lidy_MultiplySparseMatrices(SM2, SM1);

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

	printf("\nSparseMatrix D = B * A\n");
	printf("----------------------\n");
	Lidy_DisplaySparseMatrix(SM4);

	/* Destruction of sparse matrices */
	Lidy_DeleteSparseMatrix(SM1);
	Lidy_DeleteSparseMatrix(SM2);
	Lidy_DeleteSparseMatrix(SM3);
	Lidy_DeleteSparseMatrix(SM4);

	return EXIT_SUCCESS;
}

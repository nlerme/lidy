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

	/* Multiply a sparse matrix by a scalar */
	SM2 = Lidy_MultiplySparseMatrixByScalar(SM1, -2.0);

	/* Divide a sparse matrix by a scalar */
	SM3 = Lidy_DivideSparseMatrixByScalar(SM1, 1.28);

	/* Display sparse matrices */
	printf("Sparse Matrix A\n");
	printf("---------------\n");
	Lidy_DisplaySparseMatrix(SM1);

	printf("\nSparseMatrix B = A * (-2.0)\n");
	printf("----------------------\n");
	Lidy_DisplaySparseMatrix(SM2);

	printf("\nSparseMatrix C = A / (1.28)\n");
	printf("----------------------\n");
	Lidy_DisplaySparseMatrix(SM3);

	/* Destruction of sparse matrices */
	Lidy_DeleteSparseMatrix(SM1);
	Lidy_DeleteSparseMatrix(SM2);
	Lidy_DeleteSparseMatrix(SM3);

	return EXIT_SUCCESS;
}

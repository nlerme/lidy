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


	/* Creation of sparse matrices from XML files */
	if( !(SM1 = Lidy_LoadSparseMatrix("data/sparse_matrix1.xml")) )
	{
		fprintf(stderr, "Unable to load the first sparse matrix\n");
		return EXIT_FAILURE;
	}

	if( !(SM2 = Lidy_LoadSparseMatrix("data/sparse_matrix2.xml")) )
	{
		fprintf(stderr, "Unable to load the second sparse matrix\n");
		return EXIT_FAILURE;
	}

	/* Add two different sparse matrices */
	SM3 = Lidy_AddSparseMatrices(SM1, SM2);

	/* Display sparse matrices */
	printf("Sparse Matrix A\n");
	printf("---------------\n");
	Lidy_DisplaySparseMatrix(SM1);

	printf("\nSparse Matrix B\n");
	printf("---------------\n");
	Lidy_DisplaySparseMatrix(SM2);

	printf("\nSparseMatrix C = A + B\n");
	printf("----------------------\n");
	Lidy_DisplaySparseMatrix(SM3);
	printf("\n");

	/* Saving of the final sparse matrix into another XML file */
	if( Lidy_SaveSparseMatrix(SM3, "data/result.xml") )
		printf("--> The sparse matrix C has been saved into data/result.xml\n");
	else
		printf("--> The sparse matrix C hasn't been saved into data/result.xml\n");

	/* Destruction of sparse matrices */
	Lidy_DeleteSparseMatrix(SM1);
	Lidy_DeleteSparseMatrix(SM2);
	Lidy_DeleteSparseMatrix(SM3);

	return EXIT_SUCCESS;
}

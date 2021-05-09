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
#include <math.h>
#include "lidy.h"
#include "timer.h"
#include "simple_matrix.h"


#define MAX_NB_ROWS_FOR_DISPLAY 13

int main( int argc, char ** argv )
{
	pSTimer Timer=NULL;
	unsigned int Count, RowIndex, ColumnIndex, NbRows, NbCols;
	Real Time, SparsityFactor;
	register int j, i;


	/* We check if we have the right number of arguments */
	if( argc != 4 )
	{
		fprintf(stderr, "usage: %s nb_rows nb_cols sparsity_factor\n", argv[0]);
		fprintf(stderr, "\t* nb_rows  -> number of rows of the matrix (default 200)\n");
		fprintf(stderr, "\t* nb_cols  -> number of columns of the matrix (default 200)\n");
		fprintf(stderr, "\t* sparsity -> sparsity factor of the matrix, must be in [0:1] (default 0.1)\n");
		return EXIT_FAILURE;
	}

	/* We get the values of the arguments */
	NbRows         = atoi(argv[1]);
	NbCols         = atoi(argv[2]);
	SparsityFactor = atof(argv[3]);

	/* We check if the number of rows is > 0 */
	if( NbRows <= 0 )
	{
		fprintf(stderr, "error: the number of rows must be > 0\n");
		return EXIT_FAILURE;
	}

	/* We check if the number of columns is > 0 */
	if( NbCols <= 0 )
	{
		fprintf(stderr, "error: the number of columns must be > 0\n");
		return EXIT_FAILURE;
	}

	/* We check if the sparsity factor is in [0:1] */
	if( SparsityFactor < 0.0 || SparsityFactor > 1.0  )
	{
		fprintf(stderr, "error: sparsity factor must be in [0:1]\n");
		return EXIT_FAILURE;
	}

	/* We create the timer */
	if( !(Timer = CreateTimer()) )
	{
		fprintf(stderr, "Unable to create a timer\n");
		return EXIT_FAILURE;
	}

	/* We init the PRNG */
	Lidy_InitRandom();


	/******************** First, we do a full matrix multiplication **********************/
	SSimpleMatrix M1=NULL, M2=NULL;

	/* We create the full matrix */
	M1 = CreateSimpleMatrix(NbRows, NbCols);

	/* We fill randomly the matrix */
	Count = 0;

	while( ((float)Count/(NbRows*NbCols)) <= SparsityFactor )
	{
		RowIndex    = (int)Lidy_Random(0, NbRows);
		ColumnIndex = (int)Lidy_Random(0, NbCols);

		if( fabs(M1->Data[RowIndex][ColumnIndex]) < EPSILON )
		{
			M1->Data[RowIndex][ColumnIndex] = (Real)Lidy_Random(1.0, 1000.0);
			Count++;
		}
	}

	/* We init the timer */
	InitTimer(Timer);

	/* We multiply  by itself and store the result in M2 */
	M2 = MultiplySimpleMatrices(M1, M1);

	/* We get the time elapsed */
	Time = GetElapsedTime(Timer);

	/* We print some info */
	printf("############################################################################\n");
	printf("#                                                                          #\n");
	printf("# Full matrices                                                            #\n");
	printf("#                                                                          #\n");
	printf("############################################################################\n\n");

	if( NbCols <= MAX_NB_ROWS_FOR_DISPLAY )
	{
		DisplaySimpleMatrix(M1);
		printf("---------------------------\n");
		DisplaySimpleMatrix(M2);
	}

	printf("\n* Time execution -> %f\n\n\n", Time);


	/******************** Second, we do a sparse matrix multiplication *******************/
	pSSparseMatrix SM1=NULL, SM2=NULL;
	pSCell Cell=NULL;

	/* We create the sparse matrix */
	if( !(SM1 = Lidy_CreateSparseMatrix(NbRows, NbCols)) )
	{
		fprintf(stderr, "error: unable to create sparse matrix\n");
		return EXIT_FAILURE;
	}

	/* We fill the sparse matrix from the full matrix */
	Count = 0;

	for( j=0; j<NbRows; j++ )
		for( i=0; i<NbCols; i++ )
			if( fabs(M1->Data[j][i]) >= EPSILON )
				Lidy_SetValue(SM1, M1->Data[j][i], j, i);

	/* We init the timer */
	InitTimer(Timer);

	/* We multiply SM1 by itself and store the result in SM2 */
	SM2 = Lidy_MultiplySparseMatrices(SM1, SM1);

	/* We get the time elapsed */
	Time = GetElapsedTime(Timer);

	/* We print some info */
	printf("############################################################################\n");
	printf("#                                                                          #\n");
	printf("# Sparse matrices                                                          #\n");
	printf("#                                                                          #\n");
	printf("############################################################################\n\n");

	if( NbCols <= MAX_NB_ROWS_FOR_DISPLAY )
	{
		Lidy_DisplaySparseMatrix(SM1);
		printf("---------------------------\n");
		Lidy_DisplaySparseMatrix(SM2);
	}

	printf("\n* Time execution -> %f\n\n", Time);


	/************************** Third, we compare the matrices ***************************/
	Real L2;

	/* We compute the l2 norm between matrices */
	L2 = 0.0;

	for( j=0; j<NbRows; j++ )
	{
		for( i=0; i<NbCols; i++ )
		{
			Cell = Lidy_GetCell(SM2, j, i);
			L2 += fabs((Cell?Cell->m_Value:0.0) - M2->Data[j][i]);
		}
	}

	/* We print some info */
	printf("--------------------------------------------------\n");
	printf("L2 norm between matrices -> %f\n", L2);
	printf("--------------------------------------------------\n");


	/*************************** Fourth, we delete all objects ***************************/
	/* We delete the matrices */
	DeleteSimpleMatrix(&M1);
	DeleteSimpleMatrix(&M2);

	/* We delete sparse matrices */
	Lidy_DeleteSparseMatrix(SM1);
	Lidy_DeleteSparseMatrix(SM2);

	/* We destruct the timer */
	DeleteTimer(Timer);

	return EXIT_SUCCESS;
}

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

#include "simple_matrix.h"


SSimpleMatrix CreateSimpleMatrix( const int NbRows, const int NbCols )
{
	if( NbRows <= 0 || NbCols <= 0 )
	{
		fprintf(stderr, "error: number of rows and columns must be > 0\n");
		return NULL;
	}

	/***********************************************/
	SSimpleMatrix Out=NULL;
	register int j;


	if( !(Out = malloc(sizeof(*Out))) )
	{
		fprintf(stderr, "error: unable to allocate memory for a simple matrix\n");
		return NULL;
	}

	Out->NbRows = NbRows;
	Out->NbCols = NbCols;

	if( !(Out->Data = malloc(NbRows*sizeof(*Out->Data))) )
		fprintf(stderr, "error: unable to allocate memory for data of a simple matrix\n");
	else
	{
		for( j=0; j<NbRows; j++ )
			Out->Data[j] = calloc(NbCols,sizeof(Real));
	}

	/*(*Out)->Data*/

	return Out;
}

void DeleteSimpleMatrix( SSimpleMatrix *Matrix )
{
	if( !*Matrix )
		return;

	/***********************************************/
	register int j;


	if( (*Matrix)->Data )
	{
		for( j=0; j<(*Matrix)->NbRows; j++ )
			free((*Matrix)->Data[j]), (*Matrix)->Data[j]=NULL;
	}

	free((*Matrix)->Data), (*Matrix)->Data=NULL;
	free(*Matrix), Matrix=NULL;
}

void DisplaySimpleMatrix( const SSimpleMatrix Matrix )
{
	if( !Matrix || !Matrix->Data )
		return;

	/***********************************************/
	register int i, j;


	for( j=0; j<Matrix->NbRows; j++ )
	{
		for( i=0; i<Matrix->NbCols; i++ )
			printf("%f\t", Matrix->Data[j][i]);

		printf("\n");
	}
}

SSimpleMatrix MultiplySimpleMatrices( const SSimpleMatrix Matrix1, const SSimpleMatrix Matrix2 )
{
	if( !Matrix1 || !Matrix2 || !Matrix1->Data || !Matrix2->Data || Matrix1->NbCols != Matrix2->NbRows )
		return NULL;

	/***********************************************/
	SSimpleMatrix Out=NULL;
	register int i, j, k;
	Real Sum;


	if( !(Out = CreateSimpleMatrix(Matrix1->NbRows, Matrix2->NbCols)) )
		return NULL;

	for( j=0; j<Matrix1->NbRows; j++ )
	{
		for( i=0; i<Matrix2->NbCols; i++ )
		{
			Sum = 0.0;

			for( k=0; k<Matrix2->NbRows; k++ )
				Sum += Matrix1->Data[j][k] * Matrix2->Data[k][i];

			Out->Data[j][i] = Sum;
		}
	}

	return Out;
}

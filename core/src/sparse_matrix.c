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
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include "sparse_matrix.h"
#include "node.h"
#include "defines.h"


pSSparseMatrix Lidy_CreateSparseMatrix( unsigned int NbRows, unsigned int NbColumns )
{
	if( NbRows != 0 || NbColumns != 0 )
	{
		pSSparseMatrix Result = (pSSparseMatrix)malloc(sizeof(struct SSparseMatrix));

		if( Result )
		{
			Result->m_pRowsList    = Lidy_CreateLinkedList();
			Result->m_pColumnsList = Lidy_CreateLinkedList();
			Result->m_NbRows       = NbRows;
			Result->m_NbColumns    = NbColumns;
			return Result;
		}
	}

	return NULL;
}

unsigned int Lidy_GetCurrentNbRows( pSSparseMatrix SparseMatrix )
{
	return SparseMatrix && SparseMatrix->m_pRowsList ? SparseMatrix->m_pRowsList->m_NbNodes : -1;
}

unsigned int Lidy_GetCurrentNbColumns( pSSparseMatrix SparseMatrix )
{
	return SparseMatrix && SparseMatrix->m_pColumnsList ? SparseMatrix->m_pColumnsList->m_NbNodes : -1;
}

void Lidy_SetValue( pSSparseMatrix SparseMatrix, Real Value, unsigned int RowIndex, unsigned int ColumnIndex )
{
	unsigned int Index;
	pSCell CellToCreate, Cell = NULL, LastCell;
	pSNode LastNode, Node, NodeBuilt;
	Bool Insert, DoLinks;


	if( Value >= -EPSILON && Value <= EPSILON )
	{
		Lidy_DeleteCellInSparseMatrix(SparseMatrix, RowIndex, ColumnIndex);
		return;
	}

	if( ColumnIndex >= SparseMatrix->m_NbColumns || RowIndex >= SparseMatrix->m_NbRows || !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList )
		return;

	if( !SparseMatrix->m_pRowsList->m_pHead && !SparseMatrix->m_pColumnsList->m_pHead )
	{
		CellToCreate = Lidy_CreateCell(Value, RowIndex, ColumnIndex, NULL, NULL);

		if( !CellToCreate )
			return;

		Lidy_InsertNodeToTail(SparseMatrix->m_pColumnsList, CellToCreate);
		Lidy_InsertNodeToTail(SparseMatrix->m_pRowsList, CellToCreate);
	}
	else if( SparseMatrix->m_pRowsList->m_pHead && SparseMatrix->m_pColumnsList->m_pHead )
	{
		CellToCreate = Lidy_CreateCell(Value, RowIndex, ColumnIndex, NULL, NULL);

		if( !CellToCreate )
			return;

		Node     = SparseMatrix->m_pRowsList->m_pHead;
		LastNode = NULL;
		Insert   = TRUE;
		Index    = 0;

		/* Rows */
		while( Node )
		{
			Cell = Node->m_pCell;

			if( Cell )
			{
				if( Cell->m_RowIndex == RowIndex )
				{
					Insert = FALSE;
					break;
				}
				else if( Cell->m_RowIndex > RowIndex )
					break;

				Index++;
			}

			LastNode = Node;
			Node     = Node->m_pNextNode;
		}

		if( Insert )
		{
			NodeBuilt = Lidy_CreateNode(CellToCreate, NULL);

			if( !NodeBuilt )
				return;

			if( Index == 0 )
			{
				NodeBuilt->m_pNextNode             = Node;
				SparseMatrix->m_pRowsList->m_pHead = NodeBuilt;
			}
			else
			{
				NodeBuilt->m_pNextNode = LastNode->m_pNextNode;
				LastNode->m_pNextNode  = NodeBuilt;
			}
		}
		else
		{
			Index    = 0;
			DoLinks  = TRUE;
			LastCell = NULL;

			while( Cell )
			{
				if( Cell->m_ColumnIndex == ColumnIndex )
				{
					DoLinks = FALSE;
					break;
				}
				else if( Cell->m_ColumnIndex > ColumnIndex )
					break;

				Index++;

				LastCell = Cell;
				Cell     = Cell->m_pNextColumn;
			}

			if( DoLinks )
			{
				if( Index == 0)
				{
					CellToCreate->m_pNextColumn = Node->m_pCell;
					Node->m_pCell               = CellToCreate;
				}
				else
				{
					CellToCreate->m_pNextColumn = LastCell->m_pNextColumn;
					LastCell->m_pNextColumn     = CellToCreate;
				}
			}
			else
			{
				/* Easiest case */
				Cell->m_Value = Value;
				return;
			}
		}


		/* Columns */
		Node     = SparseMatrix->m_pColumnsList->m_pHead;
		LastNode = NULL;
		Insert   = TRUE;
		Index    = 0;

		while( Node )
		{
			Cell = Node->m_pCell;

			if( Cell )
			{
				if( Cell->m_ColumnIndex == ColumnIndex )
				{
					Insert = FALSE;
					break;
				}
				else if( Cell->m_ColumnIndex > ColumnIndex )
					break;

				Index++;
			}

			LastNode = Node;
			Node     = Node->m_pNextNode;
		}

		if( Insert )
		{
			NodeBuilt = Lidy_CreateNode(CellToCreate, NULL);

			if( !NodeBuilt )
				return;

			if( Index == 0 )
			{
				NodeBuilt->m_pNextNode                = Node;
				SparseMatrix->m_pColumnsList->m_pHead = NodeBuilt;
			}
			else
			{
				NodeBuilt->m_pNextNode = LastNode->m_pNextNode;
				LastNode->m_pNextNode  = NodeBuilt;
			}
		}
		else
		{
			Index    = 0;
			LastCell = NULL;
			DoLinks  = TRUE;

			while( Cell )
			{
				if( Cell->m_RowIndex == RowIndex )
				{
					DoLinks = FALSE;
					break;
				}
				if( Cell->m_RowIndex > RowIndex )
					break;

				Index++;

				LastCell = Cell;
				Cell     = Cell->m_pNextRow;
			}

			if( DoLinks )
			{
				if( Index == 0)
				{
					CellToCreate->m_pNextRow = Node->m_pCell;
					Node->m_pCell            = CellToCreate;
				}
				else
				{
					CellToCreate->m_pNextRow = LastCell->m_pNextRow;
					LastCell->m_pNextRow     = CellToCreate;
				}
			}
		}
	}
}

pSCell Lidy_GetCell( pSSparseMatrix SparseMatrix, unsigned int RowIndex, unsigned int ColumnIndex )
{
	pSNode Node = NULL;
	pSCell Cell = NULL, Result = NULL;


	if( ColumnIndex >= SparseMatrix->m_NbColumns || RowIndex >= SparseMatrix->m_NbRows || !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList )
		return NULL;

	Node   = SparseMatrix->m_pRowsList->m_pHead;
	Result = Lidy_CreateCell(0.0, 0, 0, NULL, NULL);

	while( Node )
	{
		Cell = Node->m_pCell;

		if( Cell )
		{
			if( Cell->m_RowIndex == RowIndex )
			{
				while( Cell )
				{
					if( Cell->m_ColumnIndex == ColumnIndex )
					{
						Result->m_Value = Cell->m_Value;
						break;
					}
					else if( Cell->m_ColumnIndex > ColumnIndex )
						break;

					Cell = Cell->m_pNextColumn;
				}

				break;
			}
			else if( Cell->m_RowIndex > RowIndex )
				break;
		}

		Node = Node->m_pNextNode;
	}

	return Result;
}

Bool Lidy_DeleteCellInSparseMatrix( pSSparseMatrix SparseMatrix, unsigned int RowIndex, unsigned int ColumnIndex )
{
	pSNode LastNode1 = NULL, LastNode2 = NULL, Node1 = NULL, Node2 = NULL;
	pSCell LastCell1 = NULL, LastCell2 = NULL, Cell = NULL;
	unsigned int Index1 = 0, Index2 = 0, Index3 = 0, Index4 = 0;
	Bool Ok;


	if( ColumnIndex >= SparseMatrix->m_NbColumns || RowIndex >= SparseMatrix->m_NbRows || !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList )
		return FALSE;

	Node1 = SparseMatrix->m_pRowsList->m_pHead;
	Ok    = FALSE;

	while( Node1 )
	{
		Cell = Node1->m_pCell;

		if( Cell )
		{
			if( Cell->m_RowIndex == RowIndex )
			{
				while( Cell )
				{
					if( Cell->m_ColumnIndex == ColumnIndex )
					{
						Ok = TRUE;
						break;
					}
					else if( Cell->m_ColumnIndex > ColumnIndex )
						break;

					Index2++;
					LastCell1 = Cell;
					Cell      = Cell->m_pNextColumn;
				}

				break;
			}
			else if( Cell->m_RowIndex > RowIndex )
				break;
		}

		Index1++;
		LastNode1 = Node1;
		Node1     = Node1->m_pNextNode;
	}

	if( !Ok )
		return FALSE;

	Node2 = SparseMatrix->m_pColumnsList->m_pHead;
	Ok    = FALSE;

	while( Node2 )
	{
		Cell = Node2->m_pCell;

		if( Cell )
		{
			if( Cell->m_ColumnIndex == ColumnIndex )
			{
				while( Cell )
				{	
					if( Cell->m_RowIndex == RowIndex )
					{
						Ok = TRUE;
						break;
					}
					else if( Cell->m_RowIndex > RowIndex )
						break;

					Index4++;
					LastCell2 = Cell;
					Cell      = Cell->m_pNextRow;
				}

				break;
			}
			else if( Cell->m_ColumnIndex > ColumnIndex )
				break;
		}

		Index3++;
		LastNode2 = Node2;
		Node2     = Node2->m_pNextNode;
	}

	if( !Ok )
		return FALSE;

	if( Index2 == 0 )
	{
		if( !Cell->m_pNextColumn )
		{
			if( Index1 == 0 )
				SparseMatrix->m_pRowsList->m_pHead = Node1->m_pNextNode;
			else
				LastNode1->m_pNextNode = Node1->m_pNextNode;

			Lidy_DeleteNode(Node1);
		}
		else
			Node1->m_pCell = Cell->m_pNextColumn;
	}
	else
		LastCell1->m_pNextColumn = Cell->m_pNextColumn;

	if( Index4 == 0 )
	{
		if( !Cell->m_pNextRow )
		{
			if( Index3 == 0 )
				SparseMatrix->m_pColumnsList->m_pHead = Node2->m_pNextNode;
			else
				LastNode2->m_pNextNode = Node2->m_pNextNode;

			Lidy_DeleteNode(Node2);
		}
		else
			Node2->m_pCell = Cell->m_pNextRow;
	}
	else
		LastCell2->m_pNextRow = Cell->m_pNextRow;

	Lidy_DeleteCell(Cell);

	return TRUE;
}

void Lidy_DisplaySparseMatrix( pSSparseMatrix SparseMatrix )
{
	pSNode Node = NULL;
	pSCell Cell = NULL, NullCell = NULL;
	unsigned int NbRows, NbColumns, i, j;
	int Row = -1, Col = -1;


	if( !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList )
		return;

	/* Browsing of the sparse matrix by using the rows list (it's also possible to use the columns list) */
	Node     = SparseMatrix->m_pRowsList->m_pHead;
	NullCell = Lidy_CreateCell(0.00, 0, 0, NULL, NULL);

	if( !NullCell )
		return;

	while( Node )
	{
		Cell = Node->m_pCell;

		if( Cell )
		{
			if( Row < (int)Cell->m_RowIndex )
			{
				NbRows    = Cell->m_RowIndex - Row - 1;
				NbColumns = SparseMatrix->m_NbColumns;

				for( i=0; i<NbRows; i++ )
				{
					for( j=0; j<NbColumns; j++ )
					{
						Lidy_DisplayCellValue(NullCell);

						if( j != (NbColumns - 1) )
							printf("\t");
					}

					printf("\n");
				}
			}

			Row = Cell->m_RowIndex;
			Col = -1;

			while( Cell )
			{
				if( Col < (int)Cell->m_ColumnIndex )
				{
					NbColumns = Cell->m_ColumnIndex - Col - 1;

					for( j=0; j<NbColumns; j++ )
					{
						Lidy_DisplayCellValue(NullCell);
						printf("\t");
					}
				}

				Col = Cell->m_ColumnIndex;
				Lidy_DisplayCellValue(Cell);

				if( Cell->m_ColumnIndex != (SparseMatrix->m_NbColumns - 1) )
					printf("\t");

				Cell = Cell->m_pNextColumn;
			}

			if( Col < (int)SparseMatrix->m_NbColumns )
			{
				NbColumns = SparseMatrix->m_NbColumns - Col - 1;

				for( j=0; j<NbColumns; j++ )
				{
					Lidy_DisplayCellValue(NullCell);

					if( j != (NbColumns - 1) )
						printf("\t");
				}
			}

			printf("\n");
		}

		Node = Node->m_pNextNode;
	}

	if( Row < (int)SparseMatrix->m_NbRows )
	{
		NbRows    = SparseMatrix->m_NbRows - Row - 1;
		NbColumns = SparseMatrix->m_NbColumns;

		for( i=0; i<NbRows; i++ )
		{
			for( j=0; j<NbColumns; j++ )
			{
				Lidy_DisplayCellValue(NullCell);

				if( j != (NbColumns - 1) )
					printf("\t");
			}

			printf("\n");
		}
	}

	Lidy_DeleteCell(NullCell);
}

pSSparseMatrix Lidy_MultiplySparseMatrices( pSSparseMatrix SparseMatrix1, pSSparseMatrix SparseMatrix2 )
{
	pSSparseMatrix Result = NULL;
	pSNode Node1 = NULL, Node2 = NULL;
	pSCell Cell1 = NULL, Cell2 = NULL;
	Real Value;
	unsigned int RowIndex = 0, ColumnIndex = 0;


	if( !SparseMatrix1 || !SparseMatrix1->m_pRowsList || !SparseMatrix1->m_pColumnsList || !SparseMatrix2 || !SparseMatrix2->m_pRowsList || !SparseMatrix2->m_pColumnsList || SparseMatrix1->m_NbColumns != SparseMatrix2->m_NbRows || !(Result = Lidy_CreateSparseMatrix(SparseMatrix1->m_NbRows, SparseMatrix2->m_NbColumns)) )
		return NULL;

	Node1 = SparseMatrix1->m_pRowsList->m_pHead;

	while( Node1 )
	{
		Node2 = SparseMatrix2->m_pColumnsList->m_pHead;

		while( Node2 )
		{
			Cell1 = Node1->m_pCell;
			Cell2 = Node2->m_pCell;
			Value = 0.0;

			while( Cell1 && Cell2 )
			{
				if( Cell1->m_ColumnIndex < Cell2->m_RowIndex )
					Cell1 = Cell1->m_pNextColumn;
				else if( Cell1->m_ColumnIndex > Cell2->m_RowIndex )
					Cell2 = Cell2->m_pNextRow;
				else
				{
					Value       += Cell1->m_Value * Cell2->m_Value;
					RowIndex     = Cell1->m_RowIndex;
					ColumnIndex  = Cell2->m_ColumnIndex;
					Cell1        = Cell1->m_pNextColumn;
					Cell2        = Cell2->m_pNextRow;
				}
			}

			if( Value < -EPSILON || Value > EPSILON )
				Lidy_SetValue(Result, Value, RowIndex, ColumnIndex);

			Node2 = Node2->m_pNextNode;
		}

		Node1 = Node1->m_pNextNode;
	}

	return Result;
}

pSSparseMatrix Lidy_MultiplySparseMatrixByScalar( pSSparseMatrix SparseMatrix, Real Value )
{
	pSSparseMatrix Result = NULL;
	pSNode Node           = NULL;
	pSCell Cell           = NULL;


	if( (Value >= -EPSILON && Value <= EPSILON) || !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList || !(Result = Lidy_CreateSparseMatrix(SparseMatrix->m_NbRows, SparseMatrix->m_NbColumns)) )
		return NULL;

	Node = SparseMatrix->m_pRowsList->m_pHead;

	while( Node )
	{
		Cell = Node->m_pCell;

		while( Cell )
		{
			Lidy_SetValue(Result, Cell->m_Value * Value, Cell->m_RowIndex, Cell->m_ColumnIndex);
			Cell = Cell->m_pNextColumn;
		}

		Node = Node->m_pNextNode;
	}

	return Result;
}

pSSparseMatrix Lidy_DivideSparseMatrixByScalar( pSSparseMatrix SparseMatrix, Real Value )
{
	pSSparseMatrix Result = NULL;
	pSNode Node           = NULL;
	pSCell Cell           = NULL;


	if( (Value >= -EPSILON && Value <= EPSILON) || !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList || !(Result = Lidy_CreateSparseMatrix(SparseMatrix->m_NbRows, SparseMatrix->m_NbColumns)) )
		return NULL;

	Node = SparseMatrix->m_pRowsList->m_pHead;

	while( Node )
	{
		Cell = Node->m_pCell;

		while( Cell )
		{
			Lidy_SetValue(Result, Cell->m_Value / Value, Cell->m_RowIndex, Cell->m_ColumnIndex);
			Cell = Cell->m_pNextColumn;
		}

		Node = Node->m_pNextNode;
	}

	return Result;
}

pSSparseMatrix Lidy_AddSparseMatrices( pSSparseMatrix SparseMatrix1, pSSparseMatrix SparseMatrix2 )
{
	pSSparseMatrix Result = NULL;
	pSNode Node1 = NULL, Node2 = NULL;
	pSCell Cell1 = NULL, Cell2 = NULL;
	Real Value;


	if( !SparseMatrix1 || !SparseMatrix1->m_pRowsList || !SparseMatrix1->m_pColumnsList || !SparseMatrix2 || !SparseMatrix2->m_pRowsList || !SparseMatrix2->m_pColumnsList || SparseMatrix1->m_NbRows != SparseMatrix2->m_NbRows || SparseMatrix1->m_NbColumns != SparseMatrix2->m_NbColumns || !(Result = Lidy_CreateSparseMatrix(SparseMatrix1->m_NbRows, SparseMatrix1->m_NbColumns)) )
		return NULL;

	Node1 = SparseMatrix1->m_pRowsList->m_pHead;
	Node2 = SparseMatrix2->m_pRowsList->m_pHead;

	while( Node1 || Node2 )
	{
		Cell1 = Node1 ? Node1->m_pCell : NULL;
		Cell2 = Node2 ? Node2->m_pCell : NULL;

		if( Cell1 && Cell2 )
		{
			if( Cell1->m_RowIndex > Cell2->m_RowIndex )
			{
				while( Cell2 )
				{
					Lidy_SetValue(Result, Cell2->m_Value, Cell2->m_RowIndex, Cell2->m_ColumnIndex);
					Cell2 = Cell2->m_pNextColumn;
				}

				Node2 = Node2->m_pNextNode;
			}
			else if( Cell1->m_RowIndex < Cell2->m_RowIndex )
			{
				while( Cell1 )
				{
					Lidy_SetValue(Result, Cell1->m_Value, Cell1->m_RowIndex, Cell1->m_ColumnIndex);
					Cell1 = Cell1->m_pNextColumn;
				}

				Node1 = Node1->m_pNextNode;
			}
			else
			{
				while( Cell1 || Cell2 )
				{
					if( !Cell1 || (Cell2 && Cell1->m_ColumnIndex > Cell2->m_ColumnIndex) )
					{
						Lidy_SetValue(Result, Cell2->m_Value, Cell2->m_RowIndex, Cell2->m_ColumnIndex);
						Cell2 = Cell2->m_pNextColumn;
					}
					else if( !Cell2 || (Cell1 && Cell1->m_ColumnIndex < Cell2->m_ColumnIndex) )
					{
						Lidy_SetValue(Result, Cell1->m_Value, Cell1->m_RowIndex, Cell1->m_ColumnIndex);
						Cell1 = Cell1->m_pNextColumn;
					}
					else
					{
						Value = Cell1->m_Value + Cell2->m_Value;

						if( Value < -EPSILON || Value > EPSILON )
							Lidy_SetValue(Result, Value, Cell1->m_RowIndex, Cell2->m_ColumnIndex);

						Cell1 = Cell1->m_pNextColumn;
						Cell2 = Cell2->m_pNextColumn;
					}
				}

				Node1 = Node1->m_pNextNode;
				Node2 = Node2->m_pNextNode;
			}
		}
		else
		{
			if( Node1 )
				Node1 = Node1->m_pNextNode;

			if( Node2 )
				Node2 = Node2->m_pNextNode;
		}
	}

	return Result;
}

pSSparseMatrix Lidy_SubstractSparseMatrices( pSSparseMatrix SparseMatrix1, pSSparseMatrix SparseMatrix2 )
{
	pSSparseMatrix Result = NULL;
	pSNode Node1 = NULL, Node2 = NULL;
	pSCell Cell1 = NULL, Cell2 = NULL;
	Real Value;


	if( !SparseMatrix1 || !SparseMatrix1->m_pRowsList || !SparseMatrix1->m_pColumnsList || !SparseMatrix2 || !SparseMatrix2->m_pRowsList || !SparseMatrix2->m_pColumnsList || SparseMatrix1->m_NbRows != SparseMatrix2->m_NbRows || SparseMatrix1->m_NbColumns != SparseMatrix2->m_NbColumns || !(Result = Lidy_CreateSparseMatrix(SparseMatrix1->m_NbRows, SparseMatrix1->m_NbColumns)) )
		return NULL;

	Node1 = SparseMatrix1->m_pRowsList->m_pHead;
	Node2 = SparseMatrix2->m_pRowsList->m_pHead;

	while( Node1 || Node2 )
	{
		Cell1 = Node1 ? Node1->m_pCell : NULL;
		Cell2 = Node2 ? Node2->m_pCell : NULL;

		if( Cell1 && Cell2 )
		{
			if( Cell1->m_RowIndex > Cell2->m_RowIndex )
			{
				while( Cell2 )
				{
					Lidy_SetValue(Result, -Cell2->m_Value, Cell2->m_RowIndex, Cell2->m_ColumnIndex);
					Cell2 = Cell2->m_pNextColumn;
				}

				Node2 = Node2->m_pNextNode;
			}
			else if( Cell1->m_RowIndex < Cell2->m_RowIndex )
			{
				while( Cell1 )
				{
					Lidy_SetValue(Result, Cell1->m_Value, Cell1->m_RowIndex, Cell1->m_ColumnIndex);
					Cell1 = Cell1->m_pNextColumn;
				}

				Node1 = Node1->m_pNextNode;
			}
			else
			{
				while( Cell1 || Cell2 )
				{
					if( !Cell1 || (Cell2 && Cell1->m_ColumnIndex > Cell2->m_ColumnIndex) )
					{
						Lidy_SetValue(Result, -Cell2->m_Value, Cell2->m_RowIndex, Cell2->m_ColumnIndex);
						Cell2 = Cell2->m_pNextColumn;
					}
					else if( !Cell2 || (Cell1 && Cell1->m_ColumnIndex < Cell2->m_ColumnIndex) )
					{
						Lidy_SetValue(Result, Cell1->m_Value, Cell1->m_RowIndex, Cell1->m_ColumnIndex);
						Cell1 = Cell1->m_pNextColumn;
					}
					else
					{
						Value = Cell1->m_Value - Cell2->m_Value;

						if( Value < -EPSILON || Value > EPSILON )
							Lidy_SetValue(Result, Value, Cell1->m_RowIndex, Cell2->m_ColumnIndex);

						Cell1 = Cell1->m_pNextColumn;
						Cell2 = Cell2->m_pNextColumn;
					}
				}

				Node1 = Node1->m_pNextNode;
				Node2 = Node2->m_pNextNode;
			}
		}
		else
		{
			if( Node1 )
				Node1 = Node1->m_pNextNode;

			if( Node2 )
				Node2 = Node2->m_pNextNode;
		}
	}

	return Result;
}

pSSparseMatrix Lidy_TransposeSparseMatrix( pSSparseMatrix SparseMatrix )
{
	pSSparseMatrix Result = NULL;
	pSNode Node           = NULL;
	pSCell Cell           = NULL;


	if( !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList || !(Result = Lidy_CreateSparseMatrix(SparseMatrix->m_NbColumns, SparseMatrix->m_NbRows)) )
		return NULL;

	Node = SparseMatrix->m_pRowsList->m_pHead;

	while( Node )
	{
		Cell = Node->m_pCell;

		while( Cell )
		{
			Lidy_SetValue(Result, Cell->m_Value, Cell->m_ColumnIndex, Cell->m_RowIndex);
			Cell = Cell->m_pNextColumn;
		}

		Node = Node->m_pNextNode;
	}

	return Result;
}

pSSparseMatrix Lidy_PowerSparseMatrix( pSSparseMatrix SparseMatrix, unsigned int N )
{
	unsigned int i;
	pSSparseMatrix Result = NULL, Tmp = NULL;

	if( !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList )
		return NULL;

	if( N == 0 )
		/* TODO */;
	else if( N == 1 )
		return SparseMatrix;
	else
	{
		Result = Lidy_MultiplySparseMatrices(SparseMatrix, SparseMatrix);

		for( i=1; i<(N - 1); i++ )
		{
			Tmp    = Result;
			Result = Lidy_MultiplySparseMatrices(Result, SparseMatrix);
			Lidy_DeleteSparseMatrix(Tmp);
		}
	}

	return Result;
}

pSSparseMatrix Lidy_LoadSparseMatrixFromXMLFile( const char * Filename )
{
	pSSparseMatrix SparseMatrix = NULL;
	xmlDocPtr Doc = NULL;
	xmlNodePtr XMLNode = NULL;
	xmlChar * NbRows = NULL, * NbColumns = NULL, * RowIndex = NULL, * ColumnIndex = NULL;
	xmlDtdPtr Dtd = NULL;
	xmlValidCtxtPtr Context = NULL;


	if( (Context = xmlNewValidCtxt()) )
	{
		if( (Dtd = xmlParseDTD(NULL, BAD_CAST DTD_FILENAME)) )
		{
			if( (Doc = xmlParseFile(Filename)) )
			{
				if( xmlValidateDtd(Context, Doc, Dtd) )
				{
					if( (XMLNode = xmlDocGetRootElement(Doc)) )
					{
						NbRows    = xmlGetProp(XMLNode, BAD_CAST "nbRows");
						NbColumns = xmlGetProp(XMLNode, BAD_CAST "nbColumns");

						if( NbRows && NbColumns )
						{
							SparseMatrix = Lidy_CreateSparseMatrix(atoi((char *)NbRows), atoi((char *)NbColumns));

							if( SparseMatrix )
							{
								XMLNode = XMLNode->xmlChildrenNode;

								while( XMLNode )
								{
									RowIndex    = xmlGetProp(XMLNode, BAD_CAST "rowIndex");
									ColumnIndex = xmlGetProp(XMLNode, BAD_CAST "columnIndex");

									if( RowIndex && ColumnIndex && XMLNode->children )
										Lidy_SetValue(SparseMatrix, atof((char *)XMLNode->children->content), atoi((char *)RowIndex), atoi((char *)ColumnIndex));

									xmlFree(RowIndex);
									xmlFree(ColumnIndex);

									XMLNode = XMLNode->next;
								}
							}

							xmlFree(NbRows);
							xmlFree(NbColumns);
						}

						xmlFreeNode(XMLNode);
					}

				}

				xmlFreeDoc(Doc);
			}

			xmlFreeDtd(Dtd);
		}

		xmlFreeValidCtxt(Context);
	}

	xmlCleanupParser();
	xmlMemoryDump();

	return SparseMatrix;
}

pSSparseMatrix Lidy_LoadSparseMatrix( const char * Filename )
{
	char * position = NULL, * extension = NULL;
	pSSparseMatrix Result = NULL;
	unsigned int i, j = 0, str_length, pos;


	if( (position = strrchr(Filename, '.')) && (pos = position - Filename) != 0 )
	{
		str_length = strlen(Filename);

		if( (str_length - pos - 1) != 0 )
		{
			extension = (char *)malloc((str_length - pos) * sizeof(char));

			for( i=(pos + 1); i<str_length; i++ )
				extension[j++] = Filename[i];

			extension[j] = '\0';

			if( strcmp(extension, "xml") == 0 )
				Result = Lidy_LoadSparseMatrixFromXMLFile(Filename);

			free(extension);
		}
	}

	return Result;
}

Bool Lidy_SaveSparseMatrixInXMLFile( pSSparseMatrix SparseMatrix, const char * Filename )
{
	pSNode Node = NULL;
	pSCell Cell = NULL;
	xmlDocPtr Doc = NULL;
	xmlNodePtr RootNode = NULL, ChildNode = NULL;
	char buffer[100];
	Bool Ok = FALSE;


	if( SparseMatrix && SparseMatrix->m_pRowsList && SparseMatrix->m_pColumnsList && (Doc = xmlNewDoc(BAD_CAST "1.0")) )
	{
		if( (RootNode = xmlNewNode(NULL, BAD_CAST "SparseMatrix")) )
		{
			sprintf(buffer, "%d", SparseMatrix->m_NbRows);

			if( xmlNewProp(RootNode, BAD_CAST "nbRows", BAD_CAST buffer) )
			{
				sprintf(buffer, "%d", SparseMatrix->m_NbColumns);

				if( xmlNewProp(RootNode, BAD_CAST "nbColumns", BAD_CAST buffer) )
				{
					xmlDocSetRootElement(Doc, RootNode);
					Node = SparseMatrix->m_pRowsList->m_pHead;

					while( Node )
					{
						Cell = Node->m_pCell;

						while( Cell )
						{
							sprintf(buffer, "%.2f", Cell->m_Value);
							ChildNode = xmlNewChild(RootNode, NULL, BAD_CAST "Cell", BAD_CAST buffer);

							sprintf(buffer, "%d", Cell->m_RowIndex);
							xmlNewProp(ChildNode, BAD_CAST "rowIndex", BAD_CAST buffer);

							sprintf(buffer, "%d", Cell->m_ColumnIndex);
							xmlNewProp(ChildNode, BAD_CAST "columnIndex", BAD_CAST buffer);

							Cell = Cell->m_pNextColumn;
						}

						Node = Node->m_pNextNode;
					}

					if( xmlSaveFormatFileEnc(Filename, Doc, XML_ENCODING, 1) )
						Ok = TRUE;
				}
			}
		}

		xmlFreeDoc(Doc);
	}

	xmlCleanupParser();
	xmlMemoryDump();

	return Ok;
}

Bool Lidy_SaveSparseMatrix( pSSparseMatrix SparseMatrix, const char * Filename )
{
	char * position = NULL, * extension = NULL;
	Bool Result = FALSE;
	unsigned int i, j = 0, str_length, pos;


	if( (position = strrchr(Filename, '.')) && (pos = position - Filename) != 0 )
	{
		str_length = strlen(Filename);

		if( (str_length - pos - 1) != 0 )
		{
			extension = (char *)malloc((str_length - pos) * sizeof(char));

			for( i=(pos + 1); i<str_length; i++ )
				extension[j++] = Filename[i];

			extension[j] = '\0';

			if( strcmp(extension, "xml") == 0 )
				Result = Lidy_SaveSparseMatrixInXMLFile(SparseMatrix, Filename);

			free(extension);
		}
	}

	return Result;
}

void Lidy_ClearSparseMatrix( pSSparseMatrix SparseMatrix )
{
	pSNode Node = NULL;
	pSCell Cell = NULL, Tmp = NULL;


	if( !SparseMatrix || !SparseMatrix->m_pRowsList || !SparseMatrix->m_pColumnsList )
		return;

	Node = SparseMatrix->m_pRowsList->m_pHead;

	while( Node )
	{
		Cell = Node->m_pCell;

		while( Cell )
		{
			Tmp  = Cell;
			Cell = Cell->m_pNextColumn;
			Lidy_DeleteCell(Tmp);
		}

		Node = Node->m_pNextNode;
	}

	/* Clearing of the two linked list associated to the sparse matrix */
	Lidy_ClearLinkedList(SparseMatrix->m_pRowsList);
	Lidy_ClearLinkedList(SparseMatrix->m_pColumnsList);
}

void Lidy_DeleteSparseMatrix( pSSparseMatrix SparseMatrix )
{
	Lidy_ClearSparseMatrix(SparseMatrix);

	if( SparseMatrix )
	{
		/* Destruction of the two linked list associated to the sparse matrix */
		Lidy_DeleteLinkedList(SparseMatrix->m_pRowsList);
		Lidy_DeleteLinkedList(SparseMatrix->m_pColumnsList);

		free(SparseMatrix);
		SparseMatrix = NULL;
	}
}

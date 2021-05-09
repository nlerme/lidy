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

#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "types.h"
#include "cell.h"
#include "linked_list.h"

/*!
 *  \class SSparseMatrix
 *  \brief The SSparseMatrix structure handle sparse matrices
 *  \author Nicolas LERME
 *  \version 1.1.0
 *  \date    2006
 *  \bug Nothing
 *  \warning Nothing
*/
struct SSparseMatrix
{
	pSLinkedList m_pRowsList;
	pSLinkedList m_pColumnsList;
	unsigned int m_NbRows;
	unsigned int m_NbColumns;
};

typedef struct SSparseMatrix * pSSparseMatrix;


/*!
 *  \fn pSSparseMatrix Lidy_CreateSparseMatrix( unsigned int NbRows, unsigned int NbColumns )
 *  \brief Create and allocate a new sparse matrix
 *  \param NbRows is the number of rows greater (It must be greater or equal to one)
 *  \param NbColumns is the number of columns different from zero (It must be greater or equal to one)
 *  \return Return the sparse matrix created if success, or else NULL
 */
pSSparseMatrix Lidy_CreateSparseMatrix( unsigned int NbRows, unsigned int NbColumns );


/*!
 *  \fn unsigned int Lidy_GetCurrentNbRows( pSSparseMatrix SparseMatrix )
 *  \brief Get the current number of rows in the sparse matrix (often different from the real number of rows)
 *  \param SparseMatrix is the sparse matrix where the current number of rows is obtained
 *  \return Return the current number of rows if success or else -1
 */
unsigned int Lidy_GetCurrentNbRows( pSSparseMatrix SparseMatrix );


/*!
 *  \fn unsigned int Lidy_GetCurrentNbColumns( pSSparseMatrix SparseMatrix )
 *  \brief Get the current number of columns in the sparse matrix (often different from the real number of columns)
 *  \param SparseMatrix is the sparse matrix where the current number of columns is obtained
 *  \return Return the current number of columns if success or else -1
 */
unsigned int Lidy_GetCurrentNbColumns( pSSparseMatrix SparseMatrix );


/*!
 *  \fn void Lidy_SetValue( pSSparseMatrix SparseMatrix, Real Value, unsigned int RowIndex, unsigned int ColumnIndex )
 *  \brief Set a floating-point value in a cell identified by a row index and a column index. The value is set only if the value 
           is not near from zero. Otherwise, it call 'DeleteCellInSparseMatrix' and delete the cell is possible.
 *  \param SparseMatrix is the sparse matrix where the value can be set
 *  \param Value is the floating-point value to set
 *  \param RowIndex represent the row index into the sparse matrix
 *  \param ColumnIndex represent the row index into the sparse matrix
 *  \return Nothing
 */
void Lidy_SetValue( pSSparseMatrix SparseMatrix, Real Value, unsigned int RowIndex, unsigned int ColumnIndex );

/*!
 *  \fn pSCell Lidy_GetCell( pSSparseMatrix SparseMatrix, unsigned int RowIndex, unsigned int ColumnIndex )
 *  \brief Get a whole cell in a sparse matrix identified by a row index and a column index
 *  \param SparseMatrix is the sparse matrix where the cell can be get
 *  \param RowIndex represent the row index into the sparse matrix
 *  \param ColumnIndex represent the row index into the sparse matrix
 *  \return Return the cell obtained if success or else NULL
 */
pSCell Lidy_GetCell( pSSparseMatrix SparseMatrix, unsigned int RowIndex, unsigned int ColumnIndex );


/*!
 *  \fn Bool Lidy_DeleteCellInSparseMatrix( pSSparseMatrix SparseMatrix, unsigned int RowIndex, unsigned int ColumnIndex )
 *  \brief Delete cell in a sparse matrix identified by a row index and a column index
 *  \param SparseMatrix is the sparse matrix where the cell is deleted
 *  \param RowIndex represent the row index into the sparse matrix
 *  \param ColumnIndex represent the row index into the sparse matrix
 *  \return Return true if success, or else false
 */
Bool Lidy_DeleteCellInSparseMatrix( pSSparseMatrix SparseMatrix, unsigned int RowIndex, unsigned int ColumnIndex );


/*!
 *  \fn void Lidy_DisplaySparseMatrix( pSSparseMatrix SparseMatrix )
 *  \brief Display a sparse matrix
 *  \param SparseMatrix is the sparse matrix to display
 *  \return Nothing
 */
void Lidy_DisplaySparseMatrix( pSSparseMatrix SparseMatrix );


/*!
 *  \fn pSSparseMatrix Lidy_MultiplySparseMatrices( pSSparseMatrix SparseMatrix1, pSSparseMatrix SparseMatrix2 )
 *  \brief Multiply two sparse matrices
 *  \param SparseMatrix1 represent the first sparse matrix
 *  \param SparseMatrix2 represent the second sparse matrix
 *  \return Return matrical multiplication between SparseMatrix1 and SparseMatrix2 if success, or else NULL
 */
pSSparseMatrix Lidy_MultiplySparseMatrices( pSSparseMatrix SparseMatrix1, pSSparseMatrix SparseMatrix2 );


/*!
 *  \fn pSSparseMatrix Lidy_MultiplySparseMatrixByScalar( pSSparseMatrix SparseMatrix, Real Value )
 *  \brief Multiply a sparse matrix by a scalar
 *  \param SparseMatrix represent the sparse matrix
 *  \param Value is the scalar value
 *  \return Return scalar multiplication between SparseMatrix and Value if success, or else NULL
 */
pSSparseMatrix Lidy_MultiplySparseMatrixByScalar( pSSparseMatrix SparseMatrix, Real Value );


/*!
 *  \fn pSSparseMatrix Lidy_DivideSparseMatrixByScalar( pSSparseMatrix SparseMatrix, Real Value )
 *  \brief Divide a sparse matrix by a scalar. The division is processed only if Value is not near from zero
 *  \param SparseMatrix represent the sparse matrix
 *  \param Value is the scalar value
 *  \return Return scalar division between SparseMatrix and Value if success, or else NULL
 */
pSSparseMatrix Lidy_DivideSparseMatrixByScalar( pSSparseMatrix SparseMatrix, Real Value );


/*!
 *  \fn pSSparseMatrix Lidy_AddSparseMatrices( pSSparseMatrix SparseMatrix1, struct SSparseMatrix * SparseMatrix2 )
 *  \brief Add two sparse matrices
 *  \param SparseMatrix1 represent the first sparse matrix
 *  \param SparseMatrix2 represent the second sparse matrix
 *  \return Return matrical addition between SparseMatrix1 and SparseMatrix2 if success, or else NULL
 */
pSSparseMatrix Lidy_AddSparseMatrices( pSSparseMatrix SparseMatrix1, pSSparseMatrix SparseMatrix2 );


/*!
 *  \fn pSSparseMatrix Lidy_SubstractSparseMatrices( pSSparseMatrix SparseMatrix1, pSSparseMatrix SparseMatrix2 )
 *  \brief Substract two sparse matrices
 *  \param SparseMatrix1 represent the first sparse matrix
 *  \param SparseMatrix2 represent the second sparse matrix
 *  \return Return matrical substraction between SparseMatrix1 and SparseMatrix2 if success, or else NULL
 */
pSSparseMatrix Lidy_SubstractSparseMatrices( pSSparseMatrix SparseMatrix1, pSSparseMatrix SparseMatrix2 );


/*!
 *  \fn pSSparseMatrix Lidy_TransposeSparseMatrix( pSSparseMatrix SparseMatrix )
 *  \brief Get the transposee of a sparse matrix
 *  \param SparseMatrix represent the sparse matrix to transpose
 *  \return Return the transposee of SparseMatrix if success, or else NULL
 */
pSSparseMatrix Lidy_TransposeSparseMatrix( pSSparseMatrix SparseMatrix );


/*!
 *  \fn pSSparseMatrix Lidy_PowerSparseMatrix( pSSparseMatrix SparseMatrix )
 *  \brief Get the n-power of a sparse matrix
 *  \param SparseMatrix represent the sparse matrix to power
 *  \param N is the power
 *  \return Return the n-powered SparseMatrix if success, or else NULL
 */
pSSparseMatrix Lidy_PowerSparseMatrix( pSSparseMatrix SparseMatrix, unsigned int N );


/*!
 *  \fn pSSparseMatrix Lidy_LoadSparseMatrixFromXMLFile( const char * Filename )
 *  \brief Load a file in XML format into a sparse matrix
 *  \param Filename is the name of the xml file where is stored the sparse matrix description
 *  \return Return true if the loading has succeeded, or else false
 */
pSSparseMatrix Lidy_LoadSparseMatrixFromXMLFile( const char * Filename );


/*!
 *  \fn pSSparseMatrix Lidy_LoadSparseMatrix( const char * Filename )
 *  \brief Load a file into a sparse matrix according to the extension of Filename. For instance, if the extension is 'xml', it call
           'LoadSparseMatrixInXMLFile'
 *  \param Filename is the name of the file where is stored the sparse matrix description
 *  \return Return true if the loading has succeeded, or else false
 */
pSSparseMatrix Lidy_LoadSparseMatrix( const char * Filename );


/*!
 *  \fn Bool Lidy_SaveSparseMatrixInXMLFile( pSSparseMatrix SparseMatrix, const char * Filename )
 *  \brief Save a sparse matrix into a XML file
 *  \param SparseMatrix is the sparse matrix to save
 *  \param Filename is the name of the xml file where the sparse matrix will be stored
 *  \return Return true if the saving has succeeded, or else false
 */
Bool Lidy_SaveSparseMatrixInXMLFile( pSSparseMatrix SparseMatrix, const char * Filename );


/*!
 *  \fn Bool Lidy_SaveSparseMatrix( pSSparseMatrix SparseMatrix, const char * Filename )
 *  \brief Save a sparse matrix into a file according the extension of Filename. For instance, if the extension is 'xml', it call
           'SaveSparseMatrixInXMLFile'
 *  \param SparseMatrix is the sparse matrix to save
 *  \param Filename is the name of the file where the sparse matrix will be stored
 *  \return Return true if the saving has succeeded, or else false
 */
Bool Lidy_SaveSparseMatrix( pSSparseMatrix SparseMatrix, const char * Filename );


/*!
 *  \fn void Lidy_ClearSparseMatrix( pSSparseMatrix SparseMatrix )
 *  \brief Clear a sparse matrix if SparseMatrix is not null
 *  \param SparseMatrix is the sparse matrix to clear
 *  \return Nothing
 */
void Lidy_ClearSparseMatrix( pSSparseMatrix SparseMatrix );


/*!
 *  \fn void Lidy_DeleteSparseMatrix( pSSparseMatrix SparseMatrix )
 *  \brief Delete a sparse matrix if SparseMatrix is not null
 *  \param SparseMatrix is the sparse matrix to delete
 *  \return Nothing
 */
void Lidy_DeleteSparseMatrix( pSSparseMatrix SparseMatrix );

#ifdef __cplusplus
} //extern "C"
#endif

#endif //__SPARSE_MATRIX_H__

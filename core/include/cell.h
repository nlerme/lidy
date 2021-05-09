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

#ifndef __CELL_H__
#define __CELL_H__

#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif

/*!
 *  \class SCell
 *  \brief The SCell structure handle sparse matrix cells
 *  \author Nicolas LERME
 *  \version 1.1.0
 *  \date    2006
 *  \bug Nothing
 *  \warning Nothing
*/
struct SCell
{
	Real m_Value;
	unsigned int m_RowIndex;
	unsigned int m_ColumnIndex;
	struct SCell * m_pNextRow;
	struct SCell * m_pNextColumn;
};

typedef struct SCell * pSCell;


/*!
 *  \fn pSCell Lidy_CreateCell( Real Value, unsigned int RowIndex, unsigned int ColumnIndex, pSCell pNextRow, pSCell pNextColumn )
 *  \brief Create and allocate a new cell
 *  \param Value is value of the cell
 *  \param RowIndex is the row index of the cell
 *  \param ColumnIndex is the column index of the cell
 *  \param pNextRow is the cell pointer linked to the next row cell
 *  \param pNextColumn is the cell pointer linked to the next column cell
 *  \return Return the cell created if success, or else NULL
 */
pSCell Lidy_CreateCell( Real Value, unsigned int RowIndex, unsigned int ColumnIndex, pSCell pNextRow, pSCell pNextColumn );


/*!
 *  \fn void Lidy_DisplayCellValue( pSCell Cell )
 *  \brief Display the value of a cell in a correct format if Cell is not null
 *  \param Cell is the cell with its own value to display
 *  \return Nothing
 */
void Lidy_DisplayCellValue( pSCell Cell );


/*!
 *  \fn void Lidy_DeleteCell( pSCell Cell )
 *  \brief Delete a cell if Cell is not null
 *  \param Cell is the cell to delete
 *  \return Nothing
 */
void Lidy_DeleteCell( pSCell Cell );

#ifdef __cplusplus
} //extern "C"
#endif

#endif //__CELL_H__

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

#ifndef __NODE_H__
#define __NODE_H__

#include "cell.h"

#ifdef __cplusplus
extern "C"{
#endif

/*!
 *  \class SNode
 *  \brief The SNode structure handle nodes into a linked list
 *  \author Nicolas LERME
 *  \version 1.1.0
 *  \date    2006
 *  \bug Nothing
 *  \warning Nothing
*/
struct SNode
{
	/* Information on the element */
	pSCell m_pCell;
	struct SNode * m_pNextNode;
};

typedef struct SNode * pSNode;


/*!
 *  \fn pSNode Lidy_CreateNode( pSCell Cell, pSNode pNextNode )
 *  \brief Create and allocate a new node with a cell
 *  \param Cell is the cell embedded in the new node
 *  \param pNextNode is a pointer on the next node
 *  \return Return the node created if success, or else NULL
 */
pSNode Lidy_CreateNode( pSCell Cell, pSNode pNextNode );


/*!
 *  \fn void Lidy_DeleteNode( pSNode Node )
 *  \brief Delete a node if Node is not null
 *  \param Node is the node to delete
 *  \return Nothing
 */
void Lidy_DeleteNode( pSNode Node );

#ifdef __cplusplus
} //extern "C"
#endif

#endif //__NODE_H__

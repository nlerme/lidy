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

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "types.h"
#include "node.h"
#include "cell.h"

#ifdef __cplusplus
extern "C"{
#endif

/*!
 *  \class SLinkedList
 *  \brief The SLinkedList structure handle simple linked lists
 *  \author Nicolas LERME
 *  \version 1.1.0
 *  \date    2006
 *  \bug Nothing
 *  \warning Nothing
*/
struct SLinkedList
{
	unsigned int m_NbNodes;
	pSNode m_pHead;
};

typedef struct SLinkedList * pSLinkedList;


/*!
 *  \fn struct pSLinkedList Lidy_CreateLinkedList()
 *  \brief Create and allocate a new linked list
 *  \return Return the linked list created, or else NULL
 */
pSLinkedList Lidy_CreateLinkedList();


/*!
 *  \fn Bool Lidy_InsertNodeToTail( pSLinkedList LinkedList, pSCell Cell )
 *  \brief Insert a node with a cell to the tail of a list
 *  \param LinkedList represent the list where the node is inserted
 *  \param Cell represent the cell to insert into the list
 *  \return Return true if the insertion has succeeded, or else false
 */
Bool Lidy_InsertNodeToTail( pSLinkedList LinkedList, pSCell Cell );


/*!
 *  \fn Bool Lidy_InsertNodeInPosition( pSLinkedList LinkedList, unsigned int Position, pSCell Cell )
 *  \brief Insert a node with a cell according a given position
 *  \param LinkedList is the list where the node is inserted
 *  \param Position is the position where the node is inserted into the list
 *  \param Cell is the cell to insert
 *  \return Return true if the insertion has succeeded, or else false
 */
Bool Lidy_InsertNodeInPosition( pSLinkedList LinkedList, unsigned int Position, pSCell Cell );


/*!
 *  \fn void Lidy_ClearLinkedList( pSLinkedList LinkedList )
 *  \brief Clear a linked list
 *  \param LinkedList is the list to clear
 *  \return Nothing
 */
void Lidy_ClearLinkedList( pSLinkedList LinkedList );


/*!
 *  \fn void Lidy_DeleteLinkedList( pSLinkedList LinkedList )
 *  \brief Delete a linked list
 *  \param LinkedList is the list to delete
 *  \return Nothing
 */
void Lidy_DeleteLinkedList( pSLinkedList LinkedList );

#ifdef __cplusplus
} //extern "C"
#endif

#endif //__LINKED_LIST_H__

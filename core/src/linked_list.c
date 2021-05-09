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
#include "linked_list.h"


pSLinkedList Lidy_CreateLinkedList()
{
	pSLinkedList LinkedList = (pSLinkedList)malloc(sizeof(struct SLinkedList));


	if( LinkedList )
	{
		LinkedList->m_pHead    = NULL;
		LinkedList->m_NbNodes  = 0;
		return LinkedList;
	}

	return NULL;
}

Bool Lidy_InsertNodeToTail( pSLinkedList LinkedList, pSCell Cell )
{
	pSNode Tail = NULL, Node = NULL;


	if( !LinkedList || !(Node = Lidy_CreateNode(Cell, NULL)) )
		return FALSE;

	if( !LinkedList->m_pHead )
		LinkedList->m_pHead = Node;	/* The first node is always contained into the head list */
	else
	{
		/* Otherwise, the next nodes are inserted to the tail */
		Tail = LinkedList->m_pHead;

		while( Tail->m_pNextNode )
			Tail = Tail->m_pNextNode;

		Tail->m_pNextNode = Node;
	}

	/* Increase the number of nodes */
	LinkedList->m_NbNodes++;

	return TRUE;
}

Bool Lidy_InsertNodeInPosition( pSLinkedList LinkedList, unsigned int Position, pSCell Cell )
{
	unsigned int i = 0;
	pSNode NodeToSearch = NULL, Node = NULL;


	if( !LinkedList || Position < 0 || Position > LinkedList->m_NbNodes || !(Node = Lidy_CreateNode(Cell, NULL)) )
		return FALSE;

	if( !LinkedList->m_pHead )
		LinkedList->m_pHead = Node;	/* The first node is always contained into the head list */
	else
	{
		NodeToSearch = LinkedList->m_pHead;

		if( Position == 0 )
		{
			Node->m_pNextNode   = NodeToSearch;
			LinkedList->m_pHead = Node;
		}
		else
		{
			while( NodeToSearch->m_pNextNode && i < (Position - 1) )
			{
				i++;
				NodeToSearch = NodeToSearch->m_pNextNode;
			}

			Node->m_pNextNode         = NodeToSearch->m_pNextNode;
			NodeToSearch->m_pNextNode = Node;
		}
	}

	LinkedList->m_NbNodes++;

	return TRUE;
}

void Lidy_ClearLinkedList( pSLinkedList LinkedList )
{
	pSNode Node = NULL, Tmp = NULL;


	if( !LinkedList || !(Node = LinkedList->m_pHead) )
		return;

	while( Node )
	{
		Tmp  = Node;
		Node = Node->m_pNextNode;
		Lidy_DeleteNode(Tmp);
	}

	LinkedList->m_NbNodes = 0;
	LinkedList->m_pHead   = NULL;
}

void Lidy_DeleteLinkedList( pSLinkedList LinkedList )
{
	Lidy_ClearLinkedList(LinkedList);

	if( LinkedList )
	{
		free(LinkedList);
		LinkedList = NULL;
	}
}

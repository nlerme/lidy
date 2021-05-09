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
#include "node.h"


pSNode Lidy_CreateNode( pSCell Cell, pSNode pNextNode )
{
	pSNode Node = (pSNode)malloc(sizeof(struct SNode));


	if( Node )
	{
		Node->m_pCell     = Cell;
		Node->m_pNextNode = pNextNode;
		return Node;
	}

	return NULL;
}

void Lidy_DeleteNode( pSNode Node )
{
	if( Node )
	{
		/* CAUTION : a node don't possess the responsability to destruct its Cell */
		Node->m_pCell     = NULL;
		Node->m_pNextNode = NULL;
		free(Node);
		Node = NULL;
	}
}

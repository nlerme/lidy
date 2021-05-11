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

#ifndef __TYPES_H__
#define __TYPES_H__

#ifdef __cplusplus
extern "C"{
#endif

/*
   Define a generic alias for real numbers. This little trick allow 
   to the user to change the datatype used into sparse matrices
*/
typedef float Real;


/* Define the Boolean datatype */
typedef enum
{
	B_TRUE = 1,
	B_FALSE = 0
} Bool;

#ifdef __cplusplus
} //extern "C"
#endif

#endif //__TYPES_H__

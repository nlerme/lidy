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

#ifndef __DEFINES_H__
#define __DEFINES_H__

#ifdef __cplusplus
extern "C"{
#endif

/* Define the Epsilon constant used for floating-point comparisons */
#define EPSILON 0.000001

/* Define the XML encoding format */
#define XML_ENCODING "ISO-8859-1"

/* Define the filename of the DTD */
#define DTD_FILENAME "../../core/src/lidy.dtd"

#ifdef __cplusplus
} //extern "C"
#endif

#endif //__DEFINES_H__

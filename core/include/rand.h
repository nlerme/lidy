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

#ifndef __RAND_H__
#define __RAND_H__

#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif

/*!
 *  \fn void Lidy_InitRandom()
 *  \brief Initialise the random-number generator
 *  \return Nothing
 */
void Lidy_InitRandom();


/*!
 *  \fn Real Lidy_Random( Real Min, Real Max )
 *  \brief Generate a real number at random between Min and Max
 *  \param Min represent the lower limit
 *  \param Max represent the upper limit
 *  \return The real number generated at random
 */
Real Lidy_Random( Real Min, Real Max );

#ifdef __cplusplus
} //extern "C"
#endif

#endif //__RAND_H__

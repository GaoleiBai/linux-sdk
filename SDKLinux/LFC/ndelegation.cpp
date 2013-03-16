/* 
* LFC Library - Linux toolkit
* 
* Copyright (C) 2012, 2013 Daniel Mosquera Villanueva 
* (milkatoffeecuco@gmail.com)
* This file is part of LFC Library.
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*
**/
#include "ndelegation.h"
#include <stdlib.h>

NDelegation::NDelegation()
{
	o = NULL;
	method = NULL;
}

NDelegation::NDelegation(const NObject *o, void *(NObject::*method)(void *param))
{
	this->o = (NObject *)o;
	this->method = method;
}

NDelegation::NDelegation(const NDelegation &delegation)
{
	o = delegation.o;
	method = delegation.method;
}

NDelegation::~NDelegation()
{
}

void *NDelegation::Execute(void *params)
{
	if (o == NULL || method == NULL) return NULL;
	return (o->*method)(params);
}


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
#include "windoweventkeymap.h"
#include "../xexception.h"
#include "../../Text/text.h"

WindowEventKeymap::WindowEventKeymap(XKeymapEvent *e)
{
	this->e = e;
}

WindowEventKeymap::~WindowEventKeymap()
{
}

WindowEventKeymap &WindowEventKeymap::operator =(const WindowEventKeymap &e)
{
	this->e = e.e;
	return *this;
}

bool WindowEventKeymap::KeyPressed(int i)
{
	if (i < 0 || i >= 256)
		throw new XException((Text)"Key index " + i + " doesn't exist", __FILE__, __LINE__, __func__);
		
	int byte_ix = i >> 3; 		// (i / 8)
	int bit_ix = i & 0x0007; 	// (i % 8)
	return e->key_vector[byte_ix] & (1 << bit_ix);
}


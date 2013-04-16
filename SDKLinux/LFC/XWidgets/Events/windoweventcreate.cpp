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
#include "windoweventcreate.h"

WindowEventCreate::WindowEventCreate(XCreateWindowEvent *e)
{
	this->e = e;
}

WindowEventCreate::~WindowEventCreate()
{
}

WindowEventCreate &WindowEventCreate::operator =(const WindowEventCreate &e)
{
	this->e = e.e;
	return *this;
}

NRectangle WindowEventCreate::Area()
{
	return NRectangle(e->x, e->y, e->width, e->height);
}

int WindowEventCreate::BorderWidth()
{
	return e->border_width;
}

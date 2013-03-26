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
#include "xexception.h"
#include "../Text/text.h"
#include <X11/Xlib.h>

XException::XException() : Exception()
{
}

XException::XException(const Text &description, const char *file, int line, const char *func) 
: Exception(description, file, line, func)
{
	 
}

XException::~XException()
{
}

void XException::CheckResult(int result)
{
	if (result == BadAlloc)
		throw new XException("X cannot allocate the resource.", __FILE__, __LINE__, __func__);
	else if (result == BadColor)
		throw new XException("The value for the color map does not match any colormap", __FILE__, __LINE__, __func__);
	else if (result == BadCursor)
		throw new XException("The value for the cursor does not name any known cursor", __FILE__, __LINE__, __func__);
	else if (result == BadMatch)
		throw new XException("The values does not match any required argument", __FILE__, __LINE__, __func__);
	else if (result == BadPixmap)
		throw new XException("The value of the pixmap argument does not match any known pixmap", __FILE__, __LINE__, __func__);
	else if (result == BadValue)
		throw new XException("Any value falls outside the reange required by any parameter", __FILE__, __LINE__, __func__);
	else if (result == BadWindow)
		throw new XException("The value in the window argument does not name any existing window", __FILE__, __LINE__, __func__);
	else if (result == BadDrawable)
		throw new XException("A value for a Drawable argument does not name a Window or a Pixmap", __FILE__, __LINE__, __func__);
}

void XException::CheckCairo(cairo_t *g)
{
	cairo_status_t s = cairo_status(g);
	if (s == CAIRO_STATUS_SUCCESS) return;
	throw new XException(cairo_status_to_string(s), __FILE__, __LINE__, __func__);
}


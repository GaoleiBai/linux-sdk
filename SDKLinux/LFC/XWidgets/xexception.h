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
#ifndef XEXCEPTION_H
#define XEXCEPTION_H

#include "../exception.h"
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

class XException : public Exception {

public:
	XException();
	XException(const Text &description, const char *file, int line, const char *func);
	virtual ~XException();
	
	static void CheckResult(int result);
	static void CheckCairo(cairo_t *g);
	static void CheckCairoPattern(cairo_pattern_t *p);

};

#endif // XEXCEPTION_H

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
#include "exception.h"
#include "LFC.h"
#include "Devices/stdout.h"

Exception::Exception()
{
	t = new Text("");
}

Exception::Exception(const Exception &e)
{
	t = new Text(e.t);
	StdOut::PrintLine(t);
}

Exception::Exception(const Text &p, const char *file, int line, const char *func)
{
	t = new Text((Text)p + " in " + file + " at " + line + " : " + func);
	StdOut::PrintLine(t);
}

Exception::~Exception()
{
	delete t;
}

Text Exception::ToText()
{
	return *t;
}


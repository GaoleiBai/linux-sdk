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
#include "Devices/stdout.h"
#include "Text/text.h"
#include "Devices/stderr.h"
#include <execinfo.h>

void Exception::DumpToStdErr(const Text &t)
{
	StdErr::Print("Exception caught: ");
	StdErr::Print(t);
	StdErr::PrintLine();
	
	void *addresses[1000];
	size_t numberOfFrames = backtrace(addresses, 1000);
	backtrace_symbols_fd(addresses, numberOfFrames, 2);
}

Exception::Exception()
{
	t = new Text("");
	DumpToStdErr(*t);
}

Exception::Exception(const Exception &e)
{
	t = new Text(e.t);
	DumpToStdErr(*t);
}

Exception::Exception(const Text &p, const char *file, int line, const char *func)
{
	t = new Text((Text)p + " in " + file + " at " + line + " : " + func);
	DumpToStdErr(*t);
}

Exception::~Exception()
{
	delete t;
}

Exception &Exception::operator =(const Exception &e)
{
	*t = *e.t;
	return *this;
}

Text Exception::ToText()
{
	return *t;
}


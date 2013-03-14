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
#include "stdout.h"
#include "stdio.h"
#include <stdlib.h>

StdOut *StdOut::defaultStdOut = NULL;

StdOut::StdOut()
{
	fd = 1;
}

void StdOut::Print(const Text &t)
{
	if (defaultStdOut == NULL) defaultStdOut = new StdOut();
	defaultStdOut->Write(t);
}

void StdOut::PrintLine(const Text &t)
{
	if (defaultStdOut == NULL) defaultStdOut = new StdOut();
	defaultStdOut->WriteLine(t);
}

void StdOut::PrintLine()
{
	if (defaultStdOut == NULL) defaultStdOut = new StdOut();
	defaultStdOut->WriteLine();
}
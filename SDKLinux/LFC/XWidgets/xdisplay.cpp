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
#include "xdisplay.h"
#include "xexception.h"
#include "../Text/text.h"

XDisplay *XDisplay::defaultXDisplay = NULL;

XDisplay::XDisplay()
{
	createdAsCopy = false;
	displayName = new Text("NULL");
	d = XOpenDisplay(NULL);
	if (d == NULL)
		throw new XException((Text)"Could not open display NULL", __FILE__, __LINE__, __func__);
}

XDisplay::XDisplay(Display *d)
{
	createdAsCopy = true;
	displayName = new Text(DisplayString(d));
	this->d = d;
}

XDisplay::XDisplay(const Text &t)
{
	char displayName[1000];
	((Text *)&t)->GetAnsiString(displayName, 1000);

	createdAsCopy = false;
	this->displayName = new Text(t);
	d = XOpenDisplay(displayName);
	if (d == NULL)
		throw new XException((Text)"Could not open display " + t, __FILE__, __LINE__, __func__);
}

XDisplay::~XDisplay()
{
	if (d == NULL) return;
	if (!createdAsCopy && XCloseDisplay(d) == BadGC)
		throw new XException((Text)"Invalid display parameter", __FILE__, __LINE__, __func__);
	delete displayName;
}

XDisplay &XDisplay::Default()
{
	if (defaultXDisplay == NULL) defaultXDisplay = new XDisplay();
	return *defaultXDisplay;
}


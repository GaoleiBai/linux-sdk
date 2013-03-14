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
#include "xwindow.h"
#include "xdisplay.h"

XWindow::XWindow()
{
	Display *d = XDisplay::Default().d;
	int screen = XDefaultScreen(d);
	Visual *v = DefaultVisual(d, screen);
	XSetWindowAttributes attrs;
	attrs.background_pixel = XWhitePixel(d, screen);
	attrs.border_pixel = XBlackPixel(d, screen);
	attrs.override_redirect = 0;
	int x = 10, y = 10, w = 100, h = 100, borderw = 3, depth = 32;
	XCreateWindow(
		d, XRootWindow(d, screen), x, y, w, h, borderw, depth, InputOutput, v, 
		CWBackPixel | CWBorderPixel | CWOverrideRedirect, &attrs);
}

XWindow::XWindow(const XDisplay &d)
{
}

XWindow::~XWindow()
{
}


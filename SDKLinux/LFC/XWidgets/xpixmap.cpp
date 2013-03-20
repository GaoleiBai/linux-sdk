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
#include "xpixmap.h"
#include "xwindow.h"
#include "xexception.h"

XPixmap::XPixmap(const XWindow &w, int width, int height, int colordepth)
{
	XWindow *ww = (XWindow *)&w;
	this->width = width;
	this->height = height;
	this->colordepth = colordepth;
	this->display = ww->HandlerDisplay();
	this->window = ww->HandlerWindow();
	this->pixmap = XCreatePixmap(this->display, this->window, width, height, colordepth);
	XException::CheckResult(this->pixmap);
}

XPixmap::~XPixmap()
{
	int res = XFreePixmap(display, pixmap);
	XException::CheckResult(res);
}

Pixmap XPixmap::Handler()
{
	return pixmap;
}

Display *XPixmap::HandlerDisplay()
{
	return display;
}

Window XPixmap::HandlerWindow()
{
	return window;
}

int XPixmap::Width()
{
	return width;
}

int XPixmap::Height()
{
	return height;
}

int XPixmap::ColorDepth()
{
	return colordepth;
}
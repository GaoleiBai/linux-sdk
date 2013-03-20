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
#ifndef XPIXMAP_H
#define XPIXMAP_H

#include "../n_object.h"
#include <X11/Xlib.h>

class XWindow;

class XPixmap : public NObject {
	Display *display;
	Window window;
	Pixmap pixmap;
	int width, height, colordepth;
	
public:
	XPixmap(const XWindow &w, int width, int height, int colordepth);
	virtual ~XPixmap();
	
	Pixmap Handler();
	Display *HandlerDisplay();
	Window HandlerWindow();
	
	int Width();
	int Height();
	int ColorDepth();

};

#endif // XPIXMAP_H

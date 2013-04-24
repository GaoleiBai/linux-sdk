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
#ifndef XDISPLAY_H
#define XDISPLAY_H

#include "../n_object.h"
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

class XDisplay : public NObject {
	friend class XWindow;
	
	static XDisplay *defaultXDisplay;
	
	bool createdAsCopy;
	Display *d;
	Text *displayName;
	int base_error;
	int base_event;
	
	XDisplay(Display *d);
	
public:
	XDisplay();
	XDisplay(const Text &displayName);
	virtual ~XDisplay();
	
	Text &Name();
	int XkbBaseError();
	int XkbBaseEvent();
	
	static XDisplay &Default();
	
};

#endif // XDISPLAY_H

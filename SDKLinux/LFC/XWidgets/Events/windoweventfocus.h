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
#ifndef FOCUSEVENT_H
#define FOCUSEVENT_H

#include "../../n_object.h"
#include <X11/Xlib.h>

class DateTime;
class NPoint;

class WindowEventFocus : public NObject {
	XFocusChangeEvent *e;
	
public:
	static const int NotifyModeNormal = 0;
	static const int NotifyModeGrab = 1;
	static const int NotifyModeUngrab = 2;
	static const int NotifyModeWhileGrabbed = 3;
	
	static const int NotifyDetailAncestor = 0;
	static const int NotifyDetailVirtual = 1;
	static const int NotifyDetailInferior = 2;
	static const int NotifyDetailNonLinear = 3;
	static const int NotifyDetailNonlinearVirrual = 4;
	static const int NotifyDetailPointer = 5;
	static const int NotifyDetailPointerRoot = 6;
	static const int NotifyDetailNONE = 7;
	
	WindowEventFocus(XFocusChangeEvent *e);
	virtual ~WindowEventFocus();
	
	WindowEventFocus &operator =(const WindowEventFocus &e);
	
	int NotifyMode();
	int NotifyDetail();
	
};

#endif // FOCUSEVENT_H

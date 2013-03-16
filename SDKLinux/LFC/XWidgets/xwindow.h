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
#ifndef XWINDOW_H
#define XWINDOW_H

#include "../ndelegation.h"
#include <X11/Xlib.h>
#include <X11/cursorfont.h>

class XDisplay;

class XWindow : public NObject {
	Window window;
	Window windowParent;
	Display *windowDisplay;
	int windowScreen;
	bool visible;
	
	NDelegation *dOnShowWindow;
	NDelegation *dOnDestroyWindow;
	NDelegation *dOnCreateWindow;
	NDelegation *dOnDraw;
	
	void init(const XDisplay &d);
	
public:
	XWindow();
	XWindow(const XDisplay &d);
	virtual ~XWindow();
	
	NDelegation &DelegationOnShowWindow();
	NDelegation &DelegationOnDestroyWindow();
	NDelegation &DelegationOnCreateWindow();
	NDelegation &DelegationOnDraw();
	
	void Run();
	int RunModal();
	
	void SetVisible(bool visible);
	bool IsVisible();
	
	static void RunExample();
	
};

#endif // XWINDOW_H

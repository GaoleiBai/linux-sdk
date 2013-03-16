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
#include "../Collections/collection.h"
#include <X11/Xlib.h>
#include <X11/cursorfont.h>

class XDisplay;
class Mutex;

class XWindow : public NObject {
	Window window;
	Window windowParent;
	Display *windowDisplay;
	int windowScreen;
	bool visible;
	
	Mutex *windowMutex;
	Collection<void *> *delegationsToExecute;
	
	NDelegation *dOnWindowDestroy;
	NDelegation *dOnWindowCreate;
	NDelegation *dOnWindowKeyPress;
	NDelegation *dOnWindowKeyRelease;
	NDelegation *dOnWindowKeymap;
	NDelegation *dOnWindowMouseDown;
	NDelegation *dOnWindowMouseUp;
	NDelegation *dOnWindowMouseMove;
	NDelegation *dOnWindowEnter;
	NDelegation *dOnWindowLeave;
	NDelegation *dOnWindowDraw;
	NDelegation *dOnWindowShow;
	NDelegation *dOnWindowMove;
	NDelegation *dOnWindowResize;
	NDelegation *dOnWindowFocus;
	NDelegation *dOnWindowPropertyChange;
	NDelegation *dOnWindowColormapChange;
	NDelegation *dOnWindowGrabButton;
	
	void init(const XDisplay &d);
	
public:
	XWindow();
	XWindow(const XDisplay &d);
	virtual ~XWindow();
	
	NDelegation &DelegationOnWindowDestroy();
	NDelegation &DelegationOnWindowCreate();
	NDelegation &DelegationOnWindowKeyPress();
	NDelegation &DelegationOnWindowKeyRelease();
	NDelegation &DelegationOnWindowKeymap();
	NDelegation &DelegationOnWindowMouseDown();
	NDelegation &DelegationOnWindowMouseUp();
	NDelegation &DelegationOnWindowMouseMove();
	NDelegation &DelegationOnWindowEnter();
	NDelegation &DelegationOnWindowLeave();
	NDelegation &DelegationOnWindowDraw();
	NDelegation &DelegationOnWindowShow();
	NDelegation &DelegationOnWindowMove();
	NDelegation &DelegationOnWindowResize();
	NDelegation &DelegationOnWindowFocus();
	NDelegation &DelegationOnWindowPropertyChange();
	NDelegation &DelegationOnWindowColormapChange();
	NDelegation &DelegationOnWindowGrabButton();
	
	void Run();
	int RunModal();
	void ExecuteDelegation(const NDelegation &d, void *params);
	
	void SetVisible(bool visible);
	bool IsVisible();
	
	static void RunExample();
	
};

#endif // XWINDOW_H

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

#include "../Delegations/ndelegationmanager.h"
#include "../Collections/collection.h"
#include <X11/Xlib.h>
#include <X11/cursorfont.h>

class XDisplay;
class Mutex;
class XWindowGraphics;
class DrawEvent;

class XWindow : public NObject {
	
protected:
	
	Window window;
	Window windowParent;
	Display *windowDisplay;
	Visual *windowVisual;
	int windowScreen;
	bool visible;
	int x, y, width, height, borderwidth, colordepth;
	
	Mutex *windowMutex;
	Collection<void *> *delegationsToExecute;
	
	NDelegationManager *dOnWindowDestroy;
	NDelegationManager *dOnWindowCreate;
	NDelegationManager *dOnWindowKeyPress;
	NDelegationManager *dOnWindowKeyRelease;
	NDelegationManager *dOnWindowKeymap;
	NDelegationManager *dOnWindowMouseDown;
	NDelegationManager *dOnWindowMouseUp;
	NDelegationManager *dOnWindowMouseMove;
	NDelegationManager *dOnWindowEnter;
	NDelegationManager *dOnWindowLeave;
	NDelegationManager *dOnWindowDraw;
	NDelegationManager *dOnWindowShow;
	NDelegationManager *dOnWindowMove;
	NDelegationManager *dOnWindowResize;
	NDelegationManager *dOnWindowFocus;
	NDelegationManager *dOnWindowPropertyChange;
	NDelegationManager *dOnWindowColormapChange;
	NDelegationManager *dOnWindowGrabButton;
	
	void init(const XDisplay &d);
	
public:
	XWindow();
	XWindow(const XDisplay &d);
	virtual ~XWindow();
	
	NDelegationManager &DelegationOnWindowDestroy();
	NDelegationManager &DelegationOnWindowCreate();
	NDelegationManager &DelegationOnWindowKeyPress();
	NDelegationManager &DelegationOnWindowKeyRelease();
	NDelegationManager &DelegationOnWindowKeymap();
	NDelegationManager &DelegationOnWindowMouseDown();
	NDelegationManager &DelegationOnWindowMouseUp();
	NDelegationManager &DelegationOnWindowMouseMove();
	NDelegationManager &DelegationOnWindowEnter();
	NDelegationManager &DelegationOnWindowLeave();
	NDelegationManager &DelegationOnWindowDraw();
	NDelegationManager &DelegationOnWindowShow();
	NDelegationManager &DelegationOnWindowMove();
	NDelegationManager &DelegationOnWindowResize();
	NDelegationManager &DelegationOnWindowFocus();
	NDelegationManager &DelegationOnWindowPropertyChange();
	NDelegationManager &DelegationOnWindowColormapChange();
	NDelegationManager &DelegationOnWindowGrabButton();
	
	Display *HandlerDisplay();
	Window HandlerWindow();
	Window HandlerParentWindow();
	Visual *HandlerVisual();
	int HandlerScreen();
	
	void Run();
	int RunModal();
	void ExecuteDelegation(const NDelegation &d, void *params);
	
	void SetVisible(bool visible);
	bool IsVisible();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	int GetBorderWidth();
	int GetColorDepth();
	
protected:

	virtual void OnCreate();
	virtual void OnDraw(DrawEvent *e);
	virtual void OnDestroy();

};

#endif // XWINDOW_H

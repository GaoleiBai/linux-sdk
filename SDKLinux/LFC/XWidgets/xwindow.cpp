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
#include "xexception.h"
#include "../Text/text.h"
#include "../Threading/mutex.h"
#include "../Threading/thread.h"
#include <string.h>

XWindow::XWindow()
{
	init(XDisplay::Default());
}

XWindow::XWindow(const XDisplay &d)
{
	init(d);
}

XWindow::~XWindow()
{
	SetVisible(false);
	
	int res = XDestroyWindow(windowDisplay, window);
	XException::CheckResult(res);
	
	DelegationOnWindowDestroy().Execute(NULL);
	
	delete dOnWindowDestroy;
	delete dOnWindowCreate;
	delete dOnWindowKeyPress;
	delete dOnWindowKeyRelease;
	delete dOnWindowMouseDown;
	delete dOnWindowMouseUp;
	delete dOnWindowMouseMove;
	delete dOnWindowEnter;
	delete dOnWindowLeave;
	delete dOnWindowDraw;
	delete dOnWindowShow;
	delete dOnWindowMove;
	delete dOnWindowResize;
	delete dOnWindowFocus;
	delete dOnWindowPropertyChange;
	delete dOnWindowColormapChange;
	delete dOnWindowGrabButton;
	
	delete windowMutex;
}

void XWindow::init(const XDisplay &d)
{
	windowMutex = new Mutex(true);
	windowDisplay = d.d;
	windowScreen = XDefaultScreen(windowDisplay);
	windowParent = XRootWindow(windowDisplay, windowScreen);
	
	// Creates delegates
	dOnWindowDestroy = new NDelegation();
	dOnWindowCreate = new NDelegation();
	dOnWindowKeyPress = new NDelegation();
	dOnWindowKeyRelease = new NDelegation();
	dOnWindowMouseDown = new NDelegation();
	dOnWindowMouseUp = new NDelegation();
	dOnWindowMouseMove = new NDelegation();
	dOnWindowEnter = new NDelegation();
	dOnWindowLeave = new NDelegation();
	dOnWindowDraw = new NDelegation();
	dOnWindowShow = new NDelegation();
	dOnWindowMove = new NDelegation();
	dOnWindowResize = new NDelegation();
	dOnWindowFocus = new NDelegation();
	dOnWindowPropertyChange = new NDelegation();
	dOnWindowColormapChange = new NDelegation();
	dOnWindowGrabButton = new NDelegation();
	
	Visual *v = DefaultVisual(windowDisplay, windowScreen);
	XSetWindowAttributes attrs;
	memset(&attrs, 0, sizeof(attrs));
	attrs.background_pixel = XWhitePixel(windowDisplay, windowScreen);
	attrs.border_pixel = XBlackPixel(windowDisplay, windowScreen);
	attrs.override_redirect = 0;
	int x = 0, y = 0, width = 400, height = 400, borderw = 1, depth = DefaultDepth(windowDisplay, windowScreen);

	// Create window
	window = XCreateWindow(
		windowDisplay, windowParent, x, y, width, height, borderw, depth, InputOutput, v, 
		CWBackPixel | CWBorderPixel | CWOverrideRedirect, &attrs);
	XException::CheckResult(window);
	DelegationOnWindowCreate().Execute(NULL);
	
	// Select events
	int res = XSelectInput(windowDisplay, window,
		KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | 
		EnterWindowMask | LeaveWindowMask | PointerMotionMask | ButtonMotionMask |
		KeymapStateMask | ExposureMask | VisibilityChangeMask | StructureNotifyMask |
		FocusChangeMask | PropertyChangeMask | ColormapChangeMask | OwnerGrabButtonMask);
	XException::CheckResult(res);				
	
	// Show window
	SetVisible(true);
}

NDelegation &XWindow::DelegationOnWindowDestroy()
{
	return *dOnWindowDestroy;
}

NDelegation &XWindow::DelegationOnWindowCreate()
{
	return *dOnWindowCreate;
}

NDelegation &XWindow::DelegationOnWindowKeyPress()
{
	return *dOnWindowKeyPress;
}

NDelegation &XWindow::DelegationOnWindowKeyRelease()
{
	return *dOnWindowKeyRelease;
}

NDelegation &XWindow::DelegationOnWindowMouseDown()
{
	return *dOnWindowMouseDown;
}

NDelegation &XWindow::DelegationOnWindowMouseUp()
{
	return *dOnWindowMouseUp;
}

NDelegation &XWindow::DelegationOnWindowMouseMove()
{
	return *dOnWindowMouseMove;
}

NDelegation &XWindow::DelegationOnWindowEnter()
{
	return *dOnWindowEnter;
}

NDelegation &XWindow::DelegationOnWindowLeave()
{
	return *dOnWindowLeave;
}

NDelegation &XWindow::DelegationOnWindowDraw()
{
	return *dOnWindowDraw;
}

NDelegation &XWindow::DelegationOnWindowShow()
{
	return *dOnWindowShow;
}

NDelegation &XWindow::DelegationOnWindowMove()
{
	return *dOnWindowMove;
}

NDelegation &XWindow::DelegationOnWindowResize()
{
	return *dOnWindowResize;
}

NDelegation &XWindow::DelegationOnWindowFocus()
{
	return *dOnWindowFocus;
}

NDelegation &XWindow::DelegationOnWindowPropertyChange()
{
	return *dOnWindowPropertyChange;
}

NDelegation &XWindow::DelegationOnWindowColormapChange()
{
	return *dOnWindowColormapChange;
}

NDelegation &XWindow::DelegationOnWindowGrabButton()
{
	return *dOnWindowGrabButton;
}

void XWindow::Run()
{
	
}

int XWindow::RunModal()
{
	XEvent event;
	do {
		// Gets the new event
		int res = XNextEvent(windowDisplay, &event);
		
		// Processes the events
		if (event.type == KeyPress)
			DelegationOnWindowKeyPress().Execute(NULL);
		else if (event.type == Expose) 
			DelegationOnWindowDraw().Execute(NULL);
		
		// Locks the collection of delegations
		windowMutex->Lock();
		for (int i=0; i<delegationsToExecute->Count(); i++) {
			// Retrieve delegation and parameters
			void **item = (void **)(*delegationsToExecute)[i];
			NDelegation *d = (NDelegation *)item[0];
			void *params = item[1];
			
			// Execute delegation
			try {
				d->Execute(params);
			} catch (Exception *e) {
				delete e;
			}
			
			// Deletes delegation and item array
			delete d;
			delete item;
		}
		
		// Clear delegations collection and unlocks the mutex
		delegationsToExecute->Clear();
		windowMutex->Unlock();
	} while (event.type != KeyPress);
}

void XWindow::ExecuteDelegation(const NDelegation &d, void *params)
{
	windowMutex->Lock();
	void **item = new void *[2];
	item[0] = new NDelegation(d);
	item[1] = params;
	delegationsToExecute->Add(item);
	windowMutex->Unlock();
}

void XWindow::SetVisible(bool visible)
{
	if (this->visible == visible) return;
	
	this->visible = visible;
	int res = visible ? 
		XMapWindow(windowDisplay, window) :
		XUnmapWindow(windowDisplay, window);
	XException::CheckResult(res);

	DelegationOnWindowShow().Execute(&visible);
}

bool XWindow::IsVisible()
{
	return visible;
}
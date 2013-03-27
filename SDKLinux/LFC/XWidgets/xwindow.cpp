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
#include "Graphics/xwindowgraphics.h"
#include "Events/keyevent.h"
#include "Events/buttonevent.h"
#include "Events/moveevent.h"
#include "Events/enterleaveevent.h"
#include "Events/focusevent.h"
#include "Events/keymapevent.h"
#include "Events/drawevent.h"
#include "Events/visibilityevent.h"
#include "Events/showevent.h"
#include "Events/createevent.h"
#include "Events/destroyevent.h"
#include "Events/windowmoveevent.h"
#include "Events/windowresizeevent.h"
#include "Events/keyboardmappingevent.h"
#include "Events/colormapevent.h"
#include <string.h>

XWindow::XWindow()
{
	Prepare();
	init(XDisplay::Default());
}

XWindow::XWindow(const XDisplay &d)
{
	Prepare();
	init(d);	
}

XWindow::~XWindow()
{
	Dispose();
	
	// Hide window
	SetVisible(false);

	// Destroy window graphics context
	delete gc;
	
	// Destroy window
	int res = XDestroyWindow(windowDisplay, window);
	XException::CheckResult(res);
	
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
	delete dOnWindowVisibilityChange;
	
	delete windowMutex;
}

void XWindow::init(const XDisplay &d)
{
	windowMutex = new Mutex(true);
	delegationsToExecute = new Collection<void *>();
	
	windowDisplay = d.d;
	windowScreen = XDefaultScreen(windowDisplay);
	windowParent = XRootWindow(windowDisplay, windowScreen);
	windowVisual = DefaultVisual(windowDisplay, windowScreen);
	x = 0; 
	y = 0;
	width = 400;
	height = 300;
	borderwidth = 1;
	colordepth = DefaultDepth(windowDisplay, windowScreen);
	visible = false;
	
	// Creates delegates
	dOnWindowKeyPress = new NDelegationManager();
	dOnWindowKeyRelease = new NDelegationManager();
	dOnWindowKeymap = new NDelegationManager();
	dOnWindowMouseDown = new NDelegationManager();
	dOnWindowMouseUp = new NDelegationManager();
	dOnWindowMouseMove = new NDelegationManager();
	dOnWindowEnter = new NDelegationManager();
	dOnWindowLeave = new NDelegationManager();
	dOnWindowDraw = new NDelegationManager();
	dOnWindowShow = new NDelegationManager();
	dOnWindowMove = new NDelegationManager();
	dOnWindowResize = new NDelegationManager();
	dOnWindowFocus = new NDelegationManager();
	dOnWindowPropertyChange = new NDelegationManager();
	dOnWindowColormapChange = new NDelegationManager();
	dOnWindowGrabButton = new NDelegationManager();
	dOnWindowVisibilityChange = new NDelegationManager();
	
	XSetWindowAttributes attrs;
	memset(&attrs, 0, sizeof(attrs));
	attrs.background_pixel = XWhitePixel(windowDisplay, windowScreen);
	attrs.border_pixel = XBlackPixel(windowDisplay, windowScreen);
	attrs.override_redirect = 0;

	// Create window
	window = XCreateWindow(
		windowDisplay, windowParent, x, y, width, height, borderwidth, colordepth, InputOutput, 
		windowVisual, CWBackPixel | CWBorderPixel | CWOverrideRedirect, &attrs);
	XException::CheckResult(window);
	
	// Select events
	int res = XSelectInput(windowDisplay, window,
		KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | 
		EnterWindowMask | LeaveWindowMask | PointerMotionMask | ButtonMotionMask |
		KeymapStateMask | ExposureMask | VisibilityChangeMask | StructureNotifyMask |
		FocusChangeMask | PropertyChangeMask | ColormapChangeMask | OwnerGrabButtonMask);
	XException::CheckResult(res);	
	
	// Create a graphics context
	gc = new XWindowGraphics(*this);
	
	// Show window
	SetVisible(true);
}

NDelegationManager &XWindow::DelegationOnWindowKeyPress()
{
	return *dOnWindowKeyPress;
}

NDelegationManager &XWindow::DelegationOnWindowKeyRelease()
{
	return *dOnWindowKeyRelease;
}

NDelegationManager &XWindow::DelegationOnWindowKeymap()
{
	return *dOnWindowKeymap;
}

NDelegationManager &XWindow::DelegationOnWindowMouseDown()
{
	return *dOnWindowMouseDown;
}

NDelegationManager &XWindow::DelegationOnWindowMouseUp()
{
	return *dOnWindowMouseUp;
}

NDelegationManager &XWindow::DelegationOnWindowMouseMove()
{
	return *dOnWindowMouseMove;
}

NDelegationManager &XWindow::DelegationOnWindowEnter()
{
	return *dOnWindowEnter;
}

NDelegationManager &XWindow::DelegationOnWindowLeave()
{
	return *dOnWindowLeave;
}

NDelegationManager &XWindow::DelegationOnWindowDraw()
{
	return *dOnWindowDraw;
}

NDelegationManager &XWindow::DelegationOnWindowShow()
{
	return *dOnWindowShow;
}

NDelegationManager &XWindow::DelegationOnWindowMove()
{
	return *dOnWindowMove;
}

NDelegationManager &XWindow::DelegationOnWindowResize()
{
	return *dOnWindowResize;
}

NDelegationManager &XWindow::DelegationOnWindowFocus()
{
	return *dOnWindowFocus;
}

NDelegationManager &XWindow::DelegationOnWindowPropertyChange()
{
	return *dOnWindowPropertyChange;
}

NDelegationManager &XWindow::DelegationOnWindowColormapChange()
{
	return *dOnWindowColormapChange;
}

NDelegationManager &XWindow::DelegationOnWindowGrabButton()
{
	return *dOnWindowGrabButton;
}

NDelegationManager &XWindow::DelegationOnWindowVisibilityChange()
{
	return *dOnWindowVisibilityChange;
}

Display *XWindow::HandlerDisplay()
{
	return windowDisplay;
}

Window XWindow::HandlerWindow()
{
	return window;
}

int XWindow::HandlerScreen()
{
	return windowScreen;
}

Visual *XWindow::HandlerVisual()
{
	return windowVisual;
}

void XWindow::Run()
{
	
}

int XWindow::RunModal()
{
	Prepare();
	
	// Trap XWindows "WM_DELETE_WINDOW" message
	Atom wmDeleteMessage = XInternAtom(windowDisplay, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(windowDisplay, window, &wmDeleteMessage, 1);
	
	XEvent event;
	do {
		// Gets the new event
		int res = XNextEvent(windowDisplay, &event);
		if (window != event.xany.window) continue;
		
		// Processes the events
		if (event.type == KeyPress) {
			KeyEvent e(&event.xkey);
			DelegationOnWindowKeyPress().Execute(&e);
		} else if (event.type == KeyRelease) {
			KeyEvent e(&event.xkey);
			DelegationOnWindowKeyRelease().Execute(&e);
		} else if (event.type == ButtonPress) {
			ButtonEvent e(&event.xbutton);
			DelegationOnWindowMouseDown().Execute(&e);
		} else if (event.type == ButtonRelease) {
			ButtonEvent e(&event.xbutton);
			DelegationOnWindowMouseUp().Execute(&e);
		} else if (event.type == MotionNotify) {
			MoveEvent e(&event.xmotion);
			DelegationOnWindowMouseMove().Execute(&e);
		} else if (event.type == EnterNotify) {
			EnterLeaveEvent e(&event.xcrossing);
			DelegationOnWindowEnter().Execute(&e);
		} else if (event.type == LeaveNotify) {
			EnterLeaveEvent e(&event.xcrossing);
			DelegationOnWindowLeave().Execute(&e);
		} else if (event.type == FocusIn) {
			FocusEvent e(&event.xfocus);
			DelegationOnWindowFocus().Execute(&e);
		} else if (event.type == FocusOut) {
			FocusEvent e(&event.xfocus);
			DelegationOnWindowFocus().Execute(&e);
		} else if (event.type == KeymapNotify) {
			KeymapEvent e(&event.xkeymap);
			DelegationOnWindowKeymap().Execute(&e);
		} else if (event.type == Expose) { 
			DrawEvent e(gc, &event.xexpose);
			DelegationOnWindowDraw().Execute(&e);
		} else if (event.type == VisibilityNotify) {
			VisibilityEvent e(&event.xvisibility);
			DelegationOnWindowVisibilityChange().Execute(&e);
		} else if (event.type == UnmapNotify) {
			ShowEvent e(false);
			DelegationOnWindowShow().Execute(&e);
		} else if (event.type == MapNotify) {
			ShowEvent e(true);
			DelegationOnWindowShow().Execute(&e);
		} else if (event.type == ConfigureNotify) {			
			if (x != event.xconfigure.x || y != event.xconfigure.y) {
				WindowMoveEvent e(&event.xconfigure);
				DelegationOnWindowMove().Execute(&e);
			}
			if (width != event.xconfigure.width || height != event.xconfigure.height) {
				WindowResizeEvent e(&event.xconfigure);
				DelegationOnWindowResize().Execute(&e);
			}
			
			x = event.xconfigure.x;
			y = event.xconfigure.y;
			width = event.xconfigure.width;
			height = event.xconfigure.height;
			borderwidth = event.xconfigure.border_width;			
		} else if (event.type == ColormapNotify) {
			ColormapEvent e(&event.xcolormap);
			DelegationOnWindowColormapChange().Execute(&e);
		} else if (event.type == MappingNotify) {
			KeyboardMappingEvent e(&event.xmapping);
			DelegationOnWindowKeymap().Execute(&e);
		} else if (event.type == ClientMessage) {
			if (event.xclient.data.l[0] == wmDeleteMessage)
				break;
		}
		
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
	} while (true);
	
	Dispose();
}

void XWindow::ExecuteDelegation(const NDelegation &d, void *params)
{
	// Add delegation item to delegationsToExecute collection
	windowMutex->Lock();
	void **item = new void *[2];
	item[0] = new NDelegation(d);
	item[1] = params;
	delegationsToExecute->Add(item);
	windowMutex->Unlock();
	
	// Create an event
	XEvent ev;
	ev.xclient.type = ClientMessage;
	ev.xclient.window = window;
	ev.xclient.message_type = 0;
	ev.xclient.format = 32;
	
	// It sends and flushes the event
	int res = XSendEvent(windowDisplay, window, false, NoEventMask, &ev);
	XException::CheckResult(res);
	XFlush(windowDisplay);
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

int XWindow::GetX()
{
	return x;
}

int XWindow::GetY()
{
	return y;
}

int XWindow::GetWidth()
{
	return width;
}

int XWindow::GetHeight()
{
	return height;
}

int XWindow::GetBorderWidth()
{
	return borderwidth;
}

int XWindow::GetColorDepth()
{
	return colordepth;
}

void XWindow::Prepare()
{
	
}

void XWindow::Dispose()
{
	
}

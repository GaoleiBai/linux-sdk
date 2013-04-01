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
#include "Graphics/ncolor.h"
#include "Controls/control.h"
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
	init(XDisplay::Default());
}

XWindow::XWindow(const XDisplay &d)
{
	init(d);	
}

XWindow::~XWindow()
{
	Dispose();
	
	// Hide window
	SetVisible(false);

	// Destroy controls
	controls->DeleteAndClear();
	delete controls;
	
	// Destroy helper objects
	delete gc;
	delete area;
	delete backcolor;
	delete font;
	
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
	controls = new Collection<Control *>();
	
	windowDisplay = d.d;
	windowScreen = XDefaultScreen(windowDisplay);
	windowParent = XRootWindow(windowDisplay, windowScreen);
	windowVisual = DefaultVisual(windowDisplay, windowScreen);
	area = new NRectangle(0, 0, 400, 300);
	borderwidth = 1;
	colordepth = DefaultDepth(windowDisplay, windowScreen);
	visible = false;
	backcolor = new NColor(0.7, 0.7, 0.8, 1.0);
	font = new NFont("Ubuntu Mono", NFont::FontWeightBold, 12);
	drawEnabled = true;
	
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
		windowDisplay, windowParent, area->GetX(), area->GetY(), 
		area->GetWidth(), area->GetHeight(), borderwidth, colordepth, InputOutput, 
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
		} else if (event.type == Expose && event.xexpose.count == 0) { 
			DrawEvent e(gc, &event.xexpose);
			Draw();
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
			bool generateWindowMoveEvent = 
				area->GetX() != event.xconfigure.x || 
				area->GetY() != event.xconfigure.y;
			bool generateWindowResizeEvent = 
				area->GetWidth() != event.xconfigure.width || 
				area->GetHeight() != event.xconfigure.height;
			
			*area = NRectangle(event.xconfigure.x, event.xconfigure.y, event.xconfigure.width, event.xconfigure.height);
			borderwidth = event.xconfigure.border_width;		
						
			if (generateWindowMoveEvent) {
				WindowMoveEvent e(&event.xconfigure);
				DelegationOnWindowMove().Execute(&e);
			}
			if (generateWindowResizeEvent) {
				gc->Resize(area->GetWidth(), area->GetHeight());	// Resize XWindowGraphics
				WindowResizeEvent e(&event.xconfigure);
				DelegationOnWindowResize().Execute(&e);
			}			
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

void XWindow::Invalidate()
{
	XEvent ev;
	ev.type = Expose;
	ev.xexpose.window = window;
	ev.xexpose.count = 0;
	ev.xexpose.send_event = true;
	ev.xexpose.type = Expose;
	ev.xexpose.x = area->GetX();
	ev.xexpose.y = area->GetY();
	ev.xexpose.width = area->GetWidth();
	ev.xexpose.height = area->GetHeight();
	
	int res = XSendEvent(windowDisplay, window, false, Expose, &ev);
	XException::CheckResult(res);
	XFlush(windowDisplay);
}

void XWindow::DrawEnable()
{
	drawEnabled = true;
	Draw();
}

void XWindow::DrawDisable()
{
	drawEnabled = false;
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

void XWindow::SetArea(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	XMoveResizeWindow(windowDisplay, window, rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
}

void XWindow::SetBackColor(const NColor &c)
{
	*backcolor = c;
	Invalidate();
}

void XWindow::SetFont(const NFont &f)
{
	*font = f;
}

bool XWindow::IsVisible()
{
	return visible;
}

NRectangle XWindow::Area()
{
	return *area;
}

NColor XWindow::BackColor()
{
	return *backcolor;
}

NFont XWindow::Font()
{
	return *font;
}

int XWindow::GetBorderWidth()
{
	return borderwidth;
}

int XWindow::GetColorDepth()
{
	return colordepth;
}

void XWindow::ControlAdd(Control *c)
{
	if (ControlExists(c)) return;	
	c->Init();
	controls->Add(c);
	Invalidate();
}

void XWindow::ControlRemove(Control *c)
{
	controls->Remove(c);
	Invalidate();
}

bool XWindow::ControlExists(Control *c)
{
	return controls->Contains(c);
}

void XWindow::Prepare()
{
	
}

void XWindow::Dispose()
{
	
}

void XWindow::Draw()
{
	if (!drawEnabled) return;
	
	gc->Clear(*backcolor);
	for (int i=0; i<controls->Count(); i++)
		(*controls)[i]->Draw(gc);
}

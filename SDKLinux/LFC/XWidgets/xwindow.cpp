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
#include "../nwchar.h"
#include "../Text/text.h"
#include "../Threading/mutex.h"
#include "../Threading/thread.h"
#include "Graphics/xwindowgraphics.h"
#include "Graphics/ncolor.h"
#include "Graphics/npoint.h"
#include "Controls/control.h"
#include "Events/windoweventkey.h"
#include "Events/windoweventmousebutton.h"
#include "Events/windoweventmousemove.h"
#include "Events/windowevententerleave.h"
#include "Events/windoweventfocus.h"
#include "Events/windoweventkeymap.h"
#include "Events/windoweventdraw.h"
#include "Events/windoweventvisible.h"
#include "Events/windoweventshow.h"
#include "Events/windoweventmove.h"
#include "Events/windoweventresize.h"
#include "Events/windoweventkeyboardmapping.h"
#include "Events/windoweventcreate.h"
#include "Events/windoweventdestroy.h"
#include "Events/windoweventcolormap.h"
#include "Events/controleventfocused.h"
#include "Events/controleventkey.h"
#include "Events/controleventmousebutton.h"
#include "Events/controleventmousemove.h"
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

	// Destroy controls list
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
	delete dOnWindowKeymap;
	delete dOnWindowKeyboardMapping;
	delete dOnWindowMouseDown;
	delete dOnWindowMouseUp;
	delete dOnWindowMouseMove;
	delete dOnWindowEnterLeave;
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
	backcolor = new NColor(0.95, 0.95, 0.97, 1.0);
	font = new NFont("Ubuntu Mono", NFont::FontWeightBold, 10);
	drawEnabled = true;
	
	// Creates delegates
	dOnWindowKeyPress = new NDelegationManager();
	dOnWindowKeyRelease = new NDelegationManager();
	dOnWindowKeymap = new NDelegationManager();
	dOnWindowKeyboardMapping = new NDelegationManager();
	dOnWindowMouseDown = new NDelegationManager();
	dOnWindowMouseUp = new NDelegationManager();
	dOnWindowMouseMove = new NDelegationManager();
	dOnWindowEnterLeave = new NDelegationManager();
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

NDelegationManager &XWindow::DelegationOnKeyPress()
{
	return *dOnWindowKeyPress;
}

NDelegationManager &XWindow::DelegationOnKeyRelease()
{
	return *dOnWindowKeyRelease;
}

NDelegationManager &XWindow::DelegationOnKeymap()
{
	return *dOnWindowKeymap;
}

NDelegationManager &XWindow::DelegationOnKeyboardMapping()
{
	return *dOnWindowKeyboardMapping;
}

NDelegationManager &XWindow::DelegationOnMouseDown()
{
	return *dOnWindowMouseDown;
}

NDelegationManager &XWindow::DelegationOnMouseUp()
{
	return *dOnWindowMouseUp;
}

NDelegationManager &XWindow::DelegationOnMouseMove()
{
	return *dOnWindowMouseMove;
}

NDelegationManager &XWindow::DelegationOnEnterLeave()
{
	return *dOnWindowEnterLeave;
}

NDelegationManager &XWindow::DelegationOnDraw()
{
	return *dOnWindowDraw;
}

NDelegationManager &XWindow::DelegationOnShow()
{
	return *dOnWindowShow;
}

NDelegationManager &XWindow::DelegationOnMove()
{
	return *dOnWindowMove;
}

NDelegationManager &XWindow::DelegationOnResize()
{
	return *dOnWindowResize;
}

NDelegationManager &XWindow::DelegationOnFocus()
{
	return *dOnWindowFocus;
}

NDelegationManager &XWindow::DelegationOnProperty()
{
	return *dOnWindowPropertyChange;
}

NDelegationManager &XWindow::DelegationOnColormap()
{
	return *dOnWindowColormapChange;
}

NDelegationManager &XWindow::DelegationOnGrabButton()
{
	return *dOnWindowGrabButton;
}

NDelegationManager &XWindow::DelegationOnVisible()
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

Visual *XWindow::HandlerVisual()
{
	return windowVisual;
}

int XWindow::HandlerScreen()
{
	return windowScreen;
}

IGraphics *XWindow::HandlerGraphics()
{
	return gc;
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
			WindowEventKey e(&event.xkey);
			OnKeyPress(&e);
		} else if (event.type == KeyRelease) {
			WindowEventKey e(&event.xkey);
			OnKeyRelease(&e);
		} else if (event.type == ButtonPress) {
			WindowEventMouseButton e(&event.xbutton);
			OnMouseDown(&e);
		} else if (event.type == ButtonRelease) {
			WindowEventMouseButton e(&event.xbutton);
			OnMouseUp(&e);
		} else if (event.type == MotionNotify) {
			WindowEventMouseMove e(&event.xmotion);
			OnMouseMove(&e);
		} else if (event.type == EnterNotify) {
			WindowEventEnterLeave e(&event.xcrossing);
			OnMouseEnterLeave(&e);
		} else if (event.type == LeaveNotify) {
			WindowEventEnterLeave e(&event.xcrossing);
			OnMouseEnterLeave(&e);
		} else if (event.type == FocusIn) {
			WindowEventFocus e(&event.xfocus);
			OnFocus(&e);
		} else if (event.type == FocusOut) {
			WindowEventFocus e(&event.xfocus);
			OnFocus(&e);
		} else if (event.type == KeymapNotify) {
			WindowEventKeymap e(&event.xkeymap);
			OnKeymap(&e);
		} else if (event.type == Expose && event.xexpose.count == 0) { 
			WindowEventDraw e(gc, &event.xexpose);
			OnDraw(&e);
		} else if (event.type == VisibilityNotify) {
			WindowEventVisible e(&event.xvisibility);
			OnVisible(&e);
		} else if (event.type == UnmapNotify) {
			WindowEventShow e(false);
			OnShow(&e);
		} else if (event.type == MapNotify) {
			WindowEventShow e(true);
			OnShow(&e);
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
				WindowEventMove e(&event.xconfigure);
				OnMove(&e);
			}
			if (generateWindowResizeEvent) {
				gc->Resize(area->GetWidth(), area->GetHeight());	// Resize XWindowGraphics
				WindowEventResize e(&event.xconfigure);
				OnResize(&e);
			}			
		} else if (event.type == ColormapNotify) {
			WindowEventColormap e(&event.xcolormap);
			OnColormap(&e);
		} else if (event.type == MappingNotify) {
			WindowEventKeyboardMapping e(&event.xmapping);
			OnKeyboardMapping(&e);
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

void XWindow::Close()
{
	XDestroyWindow(windowDisplay, window);
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
	//Draw();
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
	Invalidate();
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
	controls->Add(c);
	c->Init(this, NULL);
	if (c->IsVisible()) Invalidate();
}

void XWindow::ControlRemove(Control *c)
{
	controls->Remove(c);
	if (c->IsVisible()) Invalidate();
}

bool XWindow::ControlExists(Control *c)
{
	return controls->Contains(c);
}

Collection<Control *> XWindow::ControlsEnumFocusable()
{
	Collection<Control *> focusables;
	for (int i=0; i<controls->Count(); i++)
		focusables.AddRange((*controls)[i]->EnumFocusableChildren());
	focusables.QuickSort(Control::COMPARER_BY_ORDER_TABULATION);
	return focusables;
}

Control *XWindow::ControlGetFocused()
{
	Collection<Control *> focusables = ControlsEnumFocusable();
	for (int i=0; i<focusables.Count(); i++)
		if (focusables[i]->IsFocused())
			return focusables[i];
}

void XWindow::ControlFocusNext()
{
	Collection<Control *> focusables = ControlsEnumFocusable();
	if (focusables.Count() == 0) return;
	
	Control *focused = ControlGetFocused();
	int ix = focused == NULL ? 0 : controls->FindFirstIx(focused);
	if (ix == -1) return;
	
	ix += 1;
	ix = ix % controls->Count();
	(*controls)[ix]->SetFocus(true);
}

void XWindow::ControlFocusPrevious()
{
	Collection<Control *> focusables = ControlsEnumFocusable();
	if (focusables.Count() == 0) return;
	
	Control *focused = ControlGetFocused();
	int ix = focused == NULL ? 0 : controls->FindFirstIx(focused);
	if (ix == -1) return;
	
	ix += controls->Count() - 1;
	ix = ix % controls->Count();
	(*controls)[ix]->SetFocus(true);
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
	controls->QuickSort(Control::COMPARER_BY_ORDER_VISIBILITY);
	
	for (int i=0; i<controls->Count(); i++)
		(*controls)[i]->Draw();
}

void XWindow::OnKeyPress(WindowEventKey *e)
{
	ControlEventKey ek(*e);
	
	// Key preview to every control
	for (int i=0; i<controls->Count(); i++)
		(*controls)[i]->OnKeyPreview(&ek);
	
	// OnKeyPress until the focused control catches it
	bool redirected = false;
	for (int i=0; i<controls->Count() && !redirected; i++)
		redirected = (*controls)[i]->OnKeyPress(&ek);
		
	// Noone catched the event?
	if (!redirected) {
		if (e->KeyCode().Value() == 23) {
			// Window focus rotate
			if (!e->PressedShift()) ControlFocusNext();
			else ControlFocusPrevious();
		} else if (e->KeyCode().Value() == 13) {
			// Return: Window Accept
		} else if (e->KeyCode().Value() == 27) {
			// Escape: Window Cancel
		} else if (e->KeyCode().Value() == 20) {
			// Return: Window Accept
		}
	}	
	
	DelegationOnKeyPress().Execute(e);	
}

void XWindow::OnKeyRelease(WindowEventKey *e)
{
	ControlEventKey kr(*e);
	
	// Key redirection until the focused control catches it
	bool redirected = false;
	for (int i=0; i<controls->Count() && !redirected; i++)
		redirected = (*controls)[i]->OnKeyRelease(&kr);	
		
	DelegationOnKeyRelease().Execute(e);
}

void XWindow::OnMouseDown(WindowEventMouseButton *e)
{
	// OnCheckFocus to every control
	for (int i=0; i<controls->Count(); i++) {
		ControlEventMouseButton *mb = new ControlEventMouseButton(*e, (*controls)[i]->Position());
		try {
			(*controls)[i]->OnCheckFocus(mb);
		} catch (Exception *ee) {
			delete ee;
		}
		delete mb;
	}

	// OnMouseDown until one control catch it
	bool encontrado = false;
	for (int i=0; i<controls->Count() && !encontrado; i++) {
		ControlEventMouseButton *mb = new ControlEventMouseButton(*e, (*controls)[i]->Position());
		try {
			encontrado = (*controls)[i]->OnMouseButtonDown(mb);
		} catch (Exception *ee) {
			delete ee;
		}
		delete mb;
	}
	
	DelegationOnMouseDown().Execute(e);		
}

void XWindow::OnMouseUp(WindowEventMouseButton *e)
{
	// OnMouseUp until one control catch it
	for (int i=0; i<controls->Count(); i++) {
		ControlEventMouseButton *mb = new ControlEventMouseButton(*e, (*controls)[i]->Position());
		try {
			(*controls)[i]->OnMouseButtonUp(mb);	
		} catch (Exception *ee) {
			delete ee;
		}
		delete mb;
	}
		
	DelegationOnMouseUp().Execute(e);
}

void XWindow::OnMouseMove(WindowEventMouseMove *e)
{	
	// OnCheckEnterLeave for all
	for (int i=0; i<controls->Count(); i++) {
		ControlEventMouseMove *mm = new ControlEventMouseMove(*e, (*controls)[i]->Position());
		try {
			(*controls)[i]->OnCheckEnterLeave(mm);
		} catch (Exception *ee) {
			delete ee;
		}
		delete mm;
	}
	
	// OnMouseMove
	for (int i=0; i<controls->Count(); i++) {
		ControlEventMouseMove *mm = new ControlEventMouseMove(*e, (*controls)[i]->Position());
		try {
			(*controls)[i]->OnMouseMove(mm);
		} catch (Exception *ee) {
			delete ee;
		}
		delete mm;
	}
			
	DelegationOnMouseMove().Execute(e);
}

void XWindow::OnMouseEnterLeave(WindowEventEnterLeave *e)
{
	DelegationOnEnterLeave().Execute(e);
}

void XWindow::OnFocus(WindowEventFocus *e)
{
	DelegationOnFocus().Execute(e);
}

void XWindow::OnKeymap(WindowEventKeymap *e)
{
	DelegationOnKeymap().Execute(e);
}

void XWindow::OnDraw(WindowEventDraw *e)
{
	// Clear
	gc->Clear(*backcolor);
	
	// Delegation drawings
	DelegationOnDraw().Execute(e);
	
	// Control drawings
	Draw();
}

void XWindow::OnVisible(WindowEventVisible *e)
{
	DelegationOnVisible().Execute(&e);	
}

void XWindow::OnShow(WindowEventShow *e)
{
	DelegationOnVisible().Execute(&e);	
}

void XWindow::OnMove(WindowEventMove *e)
{
	DelegationOnMove().Execute(e);
}

void XWindow::OnResize(WindowEventResize *e)
{
	DelegationOnResize().Execute(e);
}

void XWindow::OnColormap(WindowEventColormap *e)
{
	DelegationOnColormap().Execute(&e);
}

void XWindow::OnKeyboardMapping(WindowEventKeyboardMapping *e)
{
	DelegationOnKeyboardMapping().Execute(e);
}
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
	
	DelegationOnDestroyWindow().Execute(NULL);
	
	delete dOnShowWindow;
	delete dOnDestroyWindow;
	delete dOnCreateWindow;
	delete dOnDraw;
}

void XWindow::init(const XDisplay &d)
{
	windowDisplay = d.d;
	windowScreen = XDefaultScreen(windowDisplay);
	windowParent = XRootWindow(windowDisplay, windowScreen);
	
	// Creates delegates
	dOnShowWindow = new NDelegation();
	dOnDestroyWindow = new NDelegation();
	dOnCreateWindow = new NDelegation();
	dOnDraw = new NDelegation();
	
	Visual *v = DefaultVisual(windowDisplay, windowScreen);
	XSetWindowAttributes attrs;
	attrs.background_pixel = XWhitePixel(windowDisplay, windowScreen);
	attrs.border_pixel = XBlackPixel(windowDisplay, windowScreen);
	int x = 10, y = 10, w = 100, h = 100, borderw = 3, depth = 32;
	
	w = XCreateWindow(
		windowDisplay, windowParent, x, y, w, h, borderw, depth, InputOutput, v, 
		CWBackPixel | CWBorderPixel, &attrs);
	XException::CheckResult(w);
	
	int res = XDefineCursor(windowDisplay, window, XCreateFontCursor(windowDisplay,XC_heart));
	res = XSelectInput(windowDisplay, w, ExposureMask | ButtonPressMask | KeyPressMask);
	XException::CheckResult(res);
	
	SetVisible(true);
}

NDelegation &XWindow::DelegationOnShowWindow()
{
	return *dOnShowWindow;
}

NDelegation &XWindow::DelegationOnDestroyWindow()
{
	return *dOnDestroyWindow;
}

NDelegation &XWindow::DelegationOnCreateWindow()
{
	return *dOnCreateWindow;
}

NDelegation &XWindow::DelegationOnDraw()
{
	return *dOnDraw;
}

void XWindow::Run()
{
	
}

int XWindow::RunModal()
{
	XEvent event;
	do {
		XNextEvent(windowDisplay, &event);
		if (event.type == Expose) DelegationOnDraw().Execute(NULL);
	} while (event.type != KeyPress);
}

void XWindow::SetVisible(bool visible)
{
	if (this->visible == visible) return;
	
	this->visible = visible;
	int res = visible ? 
		XMapWindow(windowDisplay, window) :
		XUnmapWindow(windowDisplay, window);
	XException::CheckResult(res);
	
	// Shows the window
	DelegationOnShowWindow().Execute(&visible);
}

bool XWindow::IsVisible()
{
	return visible;
}


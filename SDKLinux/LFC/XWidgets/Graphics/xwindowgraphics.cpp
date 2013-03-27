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
#include "xwindowgraphics.h"
#include "nsize.h"
#include "../xwindow.h"
#include "../xexception.h"

XWindowGraphics::XWindowGraphics(const XWindow &w)
{
	// Create cairo surface
	XWindow *ww = (XWindow *)&w;
	surface = cairo_xlib_surface_create(
		ww->HandlerDisplay(), ww->HandlerWindow(), ww->HandlerVisual(), 
		ww->GetWidth(), ww->GetHeight());	
	
	// Create cairo drawing context
	gc = cairo_create(surface);
}

XWindowGraphics::~XWindowGraphics()
{
	// Destroy cairo drawing context
	cairo_destroy(gc);
	
	// Destroy cairo surface
	cairo_surface_destroy(surface);
}

void XWindowGraphics::Resize(int width, int height)
{
	cairo_xlib_surface_set_size(surface, width, height);
}

NSize XWindowGraphics::GetSize()
{
	return NSize(cairo_xlib_surface_get_width(surface), cairo_xlib_surface_get_height(surface));
}

int XWindowGraphics::GetColorDepth()
{
	return cairo_xlib_surface_get_depth(surface);
}

Screen *XWindowGraphics::HandlerScreen()
{
	return cairo_xlib_surface_get_screen(surface);
}

Display *XWindowGraphics::HandlerDisplay()
{
	return cairo_xlib_surface_get_display(surface);
}

Visual *XWindowGraphics::HandleVisual()
{
	return cairo_xlib_surface_get_visual(surface);
}

Window XWindowGraphics::HandleWindow()
{
	return cairo_xlib_surface_get_drawable(surface);
}
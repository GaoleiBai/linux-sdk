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
#include "cairographics.h"
#include "../xwindow.h"
#include "nsize.h"

CairoGraphics::CairoGraphics(const XWindow &w)
{
	// Create cairo surface
	XWindow *ww = (XWindow *)&w;
	surface = cairo_xlib_surface_create(
		ww->HandlerDisplay(), ww->HandlerWindow(), ww->HandlerVisual(), 
		ww->GetWidth(), ww->GetHeight());	
}

CairoGraphics::~CairoGraphics()
{
	// Destroy cairo surface
	cairo_surface_destroy(surface);
}

void CairoGraphics::Resize(int width, int height)
{
	cairo_xlib_surface_set_size(surface, width, height);
}

NSize CairoGraphics::GetSize()
{
	return NSize(cairo_xlib_surface_get_width(surface), cairo_xlib_surface_get_height(surface));
}

int CairoGraphics::GetColorDepth()
{
	return cairo_xlib_surface_get_depth(surface);
}

Screen *CairoGraphics::HandlerScreen()
{
	return cairo_xlib_surface_get_screen(surface);
}

Display *CairoGraphics::HandlerDisplay()
{
	return cairo_xlib_surface_get_display(surface);
}

Visual *CairoGraphics::HandleVisual()
{
	return cairo_xlib_surface_get_visual(surface);
}

Window CairoGraphics::HandleWindow()
{
	return cairo_xlib_surface_get_drawable(surface);
}


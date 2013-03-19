#include "xwindowgraphics.h"
#include "nsize.h"
#include "../xwindow.h"

XWindowGraphics::XWindowGraphics(const XWindow &w)
{
	// Create cairo surface
	XWindow *ww = (XWindow *)&w;
	surface = cairo_xlib_surface_create(
		ww->HandlerDisplay(), ww->HandlerWindow(), ww->HandlerVisual(), 
		ww->GetWidth(), ww->GetHeight());	
}

XWindowGraphics::~XWindowGraphics()
{
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
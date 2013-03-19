#ifndef XWINDOWGRAPHICS_H
#define XWINDOWGRAPHICS_H

#include "../../n_object.h"
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

class XWindow;
class NSize;

class XWindowGraphics : public NObject {
	cairo_surface_t *surface;
	
public:
	XWindowGraphics(const XWindow &w);
	virtual ~XWindowGraphics();

	void Resize(int width, int height);
	NSize GetSize();
	int GetColorDepth();
	
	Screen *HandlerScreen();
	Display *HandlerDisplay();
	Visual *HandleVisual();
	Window HandleWindow();

};

#endif // XWINDOWGRAPHICS_H

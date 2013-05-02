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
#include <X11/keysym.h>

class XDisplay;
class Mutex;
class XWindowGraphics;
class Control;
class NColor;
class NRectangle;
class NFont;
class ControlEventFocused;
class IGraphics;
class WindowEventDraw;
class WindowEventKey;
class WindowEventKeySymbol;
class WindowEventMouseButton;
class WindowEventMouseMove;
class WindowEventEnterLeave;
class WindowEventFocus;
class WindowEventKeymap;
class WindowEventDraw;
class WindowEventVisible;
class WindowEventShow;
class WindowEventMove;
class WindowEventResize;
class WindowEventColormap;
class WindowEventKeyboardMapping;
class XKeyboard;

class XWindow : public NObject {
private:
	Mutex *windowMutex;
	Collection<void *> *delegationsToExecute;
	Collection<Control *> *controls;
		
	Window window;
	Window windowParent;
	Display *windowDisplay;
	Visual *windowVisual;
	XKeyboard *keyboard;
	int windowScreen;
	bool visible;
	NRectangle *area;
	int borderwidth, colordepth;
	XWindowGraphics *gc;
	NColor *backcolor;
	NFont *font;
	bool drawEnabled;
	Text *composeKeySymBuffer;
	
	NDelegationManager *dOnWindowKeyPress;
	NDelegationManager *dOnWindowKeyRelease;
	NDelegationManager *dOnWindowKeySymbol;
	NDelegationManager *dOnWindowKeymap;
	NDelegationManager *dOnWindowKeyboardMapping;
	NDelegationManager *dOnWindowMouseDown;
	NDelegationManager *dOnWindowMouseUp;
	NDelegationManager *dOnWindowMouseMove;
	NDelegationManager *dOnWindowEnterLeave;
	NDelegationManager *dOnWindowDraw;
	NDelegationManager *dOnWindowShow;
	NDelegationManager *dOnWindowMove;
	NDelegationManager *dOnWindowResize;
	NDelegationManager *dOnWindowFocus;
	NDelegationManager *dOnWindowPropertyChange;
	NDelegationManager *dOnWindowColormapChange;
	NDelegationManager *dOnWindowGrabButton;
	NDelegationManager *dOnWindowVisibilityChange;
	
	void init(const XDisplay &d);	
	
public:
	XWindow();
	XWindow(const XDisplay &d);
	virtual ~XWindow();
	
	NDelegationManager &DelegationOnKeyPress();			// Arg: WindowEventKey *
	NDelegationManager &DelegationOnKeyRelease();		// Arg: WindowEventKey *
	NDelegationManager &DelegationOnKeySymbol();		// Arg: WindowEventKeySymbol *
	NDelegationManager &DelegationOnKeymap();			// Arg: WindowKeymap *
	NDelegationManager &DelegationOnKeyboardMapping();	// Arg: WindowEventKeyboardMapping *
	NDelegationManager &DelegationOnMouseDown();		// Arg: WindowEventMouseButton *
	NDelegationManager &DelegationOnMouseUp();			// Arg: WindowEventMouseButton *
	NDelegationManager &DelegationOnMouseMove();		// Arg: WindoWEventMouseMove *
	NDelegationManager &DelegationOnEnterLeave();		// Arg: WindowEventEnterLeave *
	NDelegationManager &DelegationOnDraw();				// Arg: WindowEventDraw *
	NDelegationManager &DelegationOnShow();				// Arg: WindowEventShow *
	NDelegationManager &DelegationOnMove();				// Arg: WindowEventMove *
	NDelegationManager &DelegationOnResize();			// Arg: WindowEventResize *
	NDelegationManager &DelegationOnFocus();			// Arg: WindowEventFocus *
	NDelegationManager &DelegationOnProperty();			// Arg: WindowEventProperty *
	NDelegationManager &DelegationOnColormap();			// Arg: WindowEventColormap *
	NDelegationManager &DelegationOnGrabButton();		// Arg: WindowEventGrabButton *
	NDelegationManager &DelegationOnVisible();			// Arg: WindowEventVisible *
	
	Display *HandlerDisplay();
	Window HandlerWindow();
	Window HandlerParentWindow();
	Visual *HandlerVisual();
	int HandlerScreen();
	IGraphics *HandlerGraphics();
	
	void Run();
	int RunModal();
	void Close();
	void ExecuteDelegation(const NDelegation &d, void *params);
	void Invalidate();
	void DrawDisable();
	void DrawEnable();
	
	int GetBorderWidth();
	int GetColorDepth();
	
	void SetVisible(bool visible);
	void SetArea(const NRectangle &r);
	void SetBackColor(const NColor &c);
	void SetFont(const NFont &f);

	bool IsVisible();
	NRectangle Area();
	NColor BackColor();
	NFont Font();
	
	void ControlAdd(Control *c);
	void ControlRemove(Control *c);
	bool ControlExists(Control *c);
	
	Collection<Control *> ControlsEnumFocusable();
	Control *ControlGetFocused();
	void ControlFocusNext();
	void ControlFocusPrevious();
	
protected:

	virtual void Prepare();
	virtual void Dispose();
	virtual void Draw();
	virtual void OnKeyPress(WindowEventKey *e);
	virtual void OnKeyRelease(WindowEventKey *e);
	virtual void OnKeySymbol(WindowEventKeySymbol *e);
	virtual void OnMouseDown(WindowEventMouseButton *e);
	virtual void OnMouseUp(WindowEventMouseButton *e);
	virtual void OnMouseMove(WindowEventMouseMove *e);
	virtual void OnMouseEnterLeave(WindowEventEnterLeave *e);
	virtual void OnFocus(WindowEventFocus *e);
	virtual void OnKeymap(WindowEventKeymap *e);
	virtual void OnDraw(WindowEventDraw *e);
	virtual void OnVisible(WindowEventVisible *e);
	virtual void OnShow(WindowEventShow *e);
	virtual void OnMove(WindowEventMove *e);
	virtual void OnResize(WindowEventResize *e);
	virtual void OnColormap(WindowEventColormap *e);
	virtual void OnKeyboardMapping(WindowEventKeyboardMapping *e);
	
};

#endif // XWINDOW_H

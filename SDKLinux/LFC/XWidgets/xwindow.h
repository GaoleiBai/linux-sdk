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

class XDisplay;
class Mutex;
class XWindowGraphics;
class DrawEvent;
class Control;
class NColor;
class NRectangle;
class NFont;
class ControlEventChanged;

class XWindow : public NObject {
	
protected:
	
	Window window;
	Window windowParent;
	Display *windowDisplay;
	Visual *windowVisual;
	int windowScreen;
	bool visible;
	NRectangle *area;
	int borderwidth, colordepth;
	XWindowGraphics *gc;
	NColor *backcolor;
	NFont *font;
	bool drawEnabled;
	
	Mutex *windowMutex;
	Collection<void *> *delegationsToExecute;
	Collection<Control *> *controls;
	
	NDelegationManager *dOnWindowKeyPress;
	NDelegationManager *dOnWindowKeyRelease;
	NDelegationManager *dOnWindowKeymap;
	NDelegationManager *dOnWindowMouseDown;
	NDelegationManager *dOnWindowMouseUp;
	NDelegationManager *dOnWindowMouseMove;
	NDelegationManager *dOnWindowEnter;
	NDelegationManager *dOnWindowLeave;
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
	
	NDelegationManager &DelegationOnWindowKeyPress();
	NDelegationManager &DelegationOnWindowKeyRelease();
	NDelegationManager &DelegationOnWindowKeymap();
	NDelegationManager &DelegationOnWindowMouseDown();
	NDelegationManager &DelegationOnWindowMouseUp();
	NDelegationManager &DelegationOnWindowMouseMove();
	NDelegationManager &DelegationOnWindowEnter();
	NDelegationManager &DelegationOnWindowLeave();
	NDelegationManager &DelegationOnWindowDraw();
	NDelegationManager &DelegationOnWindowShow();
	NDelegationManager &DelegationOnWindowMove();
	NDelegationManager &DelegationOnWindowResize();
	NDelegationManager &DelegationOnWindowFocus();
	NDelegationManager &DelegationOnWindowPropertyChange();
	NDelegationManager &DelegationOnWindowColormapChange();
	NDelegationManager &DelegationOnWindowGrabButton();
	NDelegationManager &DelegationOnWindowVisibilityChange();
	
	Display *HandlerDisplay();
	Window HandlerWindow();
	Window HandlerParentWindow();
	Visual *HandlerVisual();
	int HandlerScreen();
	
	void Run();
	int RunModal();
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
	
protected:

	virtual void Prepare();
	virtual void Dispose();
	void Draw();
	void *OnControlChanged(ControlEventChanged *e);

};

#endif // XWINDOW_H

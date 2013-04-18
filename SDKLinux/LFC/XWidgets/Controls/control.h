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
#ifndef CONTROL_H
#define CONTROL_H

#include "../Graphics/nrectangle.h"
#include "../../Delegations/ndelegationmanager.h"
#include "../../Collections/collection.h"

class IGraphics;
class NColor;
class NFont;
class XWindow;
class ControlEventMoved;
class ControlEventKey;
class ControlEventFocused;
class ControlEventMouseButton;
class ControlEventBackColor;
class ControlEventFont;
class ControlEventVisible;
class ControlEventMouseMove;
class ControlEventEnterLeave;
class ControlEventMouseClick;
class ControlEventMouseDoubleClick;
class ControlEventFocusedColor;

class Control : public NObject {
	friend class XWindow;
	
protected:
	XWindow *window;
	Control *parent;
	NRectangle *area;
	NColor *backcolor;
	NColor *focusedcolor;
	NFont *font;
	void *userdata;
	Collection<Control *> *children;
	bool visible;
	bool entered;
	bool focused;
	int orderTabulation;
	int orderVisibility;
	ControlEventMouseButton *lastMouseDown;
	ControlEventMouseButton *lastMouseClick;
	
	NDelegationManager *onMouseButtonDown;
	NDelegationManager *onMouseButtonUp;
	NDelegationManager *onMouseMove;
	NDelegationManager *onMouseClick;
	NDelegationManager *onMouseDoubleClick;
	NDelegationManager *onKeyPreview;
	NDelegationManager *onKeyPress;
	NDelegationManager *onKeyRelease;
	NDelegationManager *onMove;
	NDelegationManager *onVisible;
	NDelegationManager *onEnter;
	NDelegationManager *onLeave;
	NDelegationManager *onFocus;
	NDelegationManager *onBackColor;
	NDelegationManager *onFont;
	NDelegationManager *onFocusedColor;
	
	void Init();
	NPoint Position();
	
public:
	Control();
	Control(const NRectangle &area);
	virtual ~Control();
	
	static int COMPARER_BY_ORDER_TABULATION(const void *u, const void *v);
	static int COMPARER_BY_ORDER_VISIBILITY(const void *u, const void *v);

	virtual void Init(XWindow *w, Control *parent);
	virtual void ChildControlAdd(Control *c);
	virtual void ChildControlRemove(Control *c);
	virtual bool ChildControlExists(Control *c);

	virtual NPoint GetPosition();
	virtual NSize GetSize();
	virtual NRectangle Area();
	virtual NColor BackColor();
	virtual NColor FocusedColor();
	virtual NFont Font();
	virtual void *GetUserData();
	virtual bool IsVisible();
	virtual bool IsFocused();
	virtual int OrderTabulation();
	virtual int OrderVisibility();
	
	virtual void SetPosition(const NPoint &p);
	virtual void SetSize(const NSize &s);
	virtual void SetArea(const NRectangle &area);
	virtual void SetBackColor(const NColor &backcolor);
	virtual void SetFocusedColor(const NColor &focusedcolor);
	virtual void SetFont(const NFont &font);
	virtual void SetUserData(void *userdata);
	virtual void SetVisible(bool visible);
	virtual void SetFocus(bool focused);
	virtual void SetOrderTabulation(int orderTabulation);
	virtual void SetOrderVisibility(int orderVisibility);
	
	virtual void Draw();
	virtual void Prepare();
	virtual void Release();
	virtual bool IsFocusable();
	virtual bool CaptureTabKey();
	virtual bool CaptureEnterKey();
	virtual bool CaptureSpaceKey();
	virtual bool CaptureEscapeKey();

protected:

	virtual bool OnMove(ControlEventMoved *e);
	virtual bool OnBackColor(ControlEventBackColor *e);
	virtual bool OnFont(ControlEventFont *e);
	virtual bool OnVisible(ControlEventVisible *e);
	virtual bool OnKeyPreview(ControlEventKey *e);
	virtual bool OnKeyPress(ControlEventKey *e);
	virtual bool OnKeyRelease(ControlEventKey *e);
	virtual bool OnCheckFocus(ControlEventMouseButton *e);
	virtual bool OnMouseButtonDown(ControlEventMouseButton *e);
	virtual bool OnMouseButtonUp(ControlEventMouseButton *e);
	virtual bool OnMouseClick(ControlEventMouseClick *e);
	virtual bool OnMouseDoubleClick(ControlEventMouseDoubleClick *e);
	virtual bool OnCheckEnterLeave(ControlEventMouseMove *e);
	virtual bool OnMouseMove(ControlEventMouseMove *e);
	virtual bool OnMouseEnter(ControlEventEnterLeave *e);
	virtual bool OnMouseLeave(ControlEventEnterLeave *e);
	virtual bool OnFocus(ControlEventFocused *e);
	virtual bool OnFocusedColor(ControlEventFocusedColor *e);
	virtual bool OnDrawBackground(IGraphics *g, NRectangle *r);
	virtual bool OnDraw(IGraphics *g, NRectangle *r);
		
public:

	Collection<Control *> EnumFocusableChildren();
	
	NDelegationManager &DelegationOnMouseButtonDown();	// Arg: ControlEventMouseButton *
	NDelegationManager &DelegationOnMouseButtonUp();		// Arg: ControlEventMouseButton *
	NDelegationManager &DelegationOnMouseMove();	// Arg: ControlEventMouseMove *
	NDelegationManager &DelegationOnMouseClick();	// Arg: ControlEventMouseClick *
	NDelegationManager &DelegationOnMouseDoubleClick();	// Arg: ControlEventMouseDoubleClick *
	NDelegationManager &DelegationOnKeyPreview();	// Arg: ControlEventKey *
	NDelegationManager &DelegationOnKeyPress();		// Arg: ControlEventKey *
	NDelegationManager &DelegationOnKeyRelease();	// Arg: ControlEventKey *
	NDelegationManager &DelegationOnMove();			// Arg: ControlEventMoved *
	NDelegationManager &DelegationOnVisible();		// Arg: ControlEventVisible *
	NDelegationManager &DelegationOnMouseEnter();	// Arg: ControlEventEnterLeave *
	NDelegationManager &DelegationOnMouseLeave();	// Arg: ControlEventEnterLeave *
	NDelegationManager &DelegationOnFocus();		// Arg: ControlEventFocus *
	NDelegationManager &DelegationOnBackColor();	// Arg: ControlEventBackColor *
	NDelegationManager &DelegationOnFont();			// Arg: ControlEventFont *
	NDelegationManager &DelegationOnFocusedColor();	// Arg: ControlEventFocusedColor *
	
};

#endif // CONTROL_H

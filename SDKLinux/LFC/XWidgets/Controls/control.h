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
class XWindow;
class ControlEventMoved;
class ControlEventKey;
class ControlEventFocused;
class ControlEventMouseButton;
class ControlEventBackColor;
class ControlEventVisible;
class ControlEventMouseMove;
class ControlEventEnterLeave;
class ControlEventMouseClick;
class ControlEventMouseDoubleClick;

class Control : public NObject {
	friend class XWindow;
	
protected:
	XWindow *window;
	Control *parent;
	NRectangle *area;
	NColor *backcolor;
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
	
	void Init();
	NPoint Position();
	
public:
	Control();
	Control(const NRectangle &area);
	virtual ~Control();
	
	static int COMPARER_BY_ORDER_TABULATION(const void *u, const void *v);
	static int COMPARER_BY_ORDER_VISIBILITY(const void *u, const void *v);

	void Init(XWindow *w, Control *parent);
	void ChildControlAdd(Control *c);
	void ChildControlRemove(Control *c);
	bool ChildControlExists(Control *c);

	NRectangle Area();
	NColor BackColor();
	void *GetUserData();
	bool IsVisible();
	bool IsFocused();
	int OrderTabulation();
	int OrderVisibility();
	
	void SetArea(const NRectangle &area);
	void SetBackColor(const NColor &backcolor);
	void SetUserData(void *userdata);
	void SetVisible(bool visible);
	void SetFocus(bool focused);
	void SetOrderTabulation(int orderTabulation);
	void SetOrderVisibility(int orderVisibility);
	
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
	
};

#endif // CONTROL_H

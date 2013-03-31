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

class Control : public NObject {
protected:
	NRectangle *area;
	NColor *backcolor;
	void *userdata;
	Collection<Control *> *children;
	bool visible;
	bool entered;
	bool focused;	
	
	NDelegationManager *onControlChanged;
	NDelegationManager *onMouseDown;
	NDelegationManager *onMouseUp;
	NDelegationManager *onMouseMove;
	NDelegationManager *onClick;
	NDelegationManager *onDoubleClick;
	NDelegationManager *onKeyPress;
	NDelegationManager *onKeyRelease;
	NDelegationManager *onMove;
	NDelegationManager *onVisible;
	NDelegationManager *onEnter;
	NDelegationManager *onFocus;
	NDelegationManager *onBackColor;
	
	void *InternalOnMouseDown(void *params);
	void *InternalOnMouseUp(void *params);
	
public:
	Control();
	Control(const NRectangle &area);
	virtual ~Control();

	void Init();
	void ChildControlAdd(Control *c);
	void ChildControlRemove(Control *c);
	bool ChildControlExists(Control *c);

	NRectangle Area();
	NColor BackColor();
	void *GetUserData();
	bool IsVisible();
	bool IsFocused();
	
	void SetArea(const NRectangle &area);
	void SetBackColor(const NColor &backcolor);
	void SetUserData(void *userdata);
	void SetVisible(bool visible);
	void SetFocused(bool focused);
	
	virtual void Draw(IGraphics *g);
	virtual void Prepare();
	virtual void Release();
	
	NDelegationManager &DelegationOnControlChanged();
	NDelegationManager &DelegationOnMouseDown();
	NDelegationManager &DelegationOnMouseUp();
	NDelegationManager &DelegationOnMouseMove();
	NDelegationManager &DelegationOnClick();
	NDelegationManager &DelegationOnDoubleClick();
	NDelegationManager &DelegationOnKeyPress();
	NDelegationManager &DelegationOnKeyRelease();
	NDelegationManager &DelegationOnMove();
	NDelegationManager &DelegationOnVisible();
	NDelegationManager &DelegationOnEnter();
	NDelegationManager &DelegationOnFocus();
	NDelegationManager &DelegationOnBackColor();
	
};

#endif // CONTROL_H

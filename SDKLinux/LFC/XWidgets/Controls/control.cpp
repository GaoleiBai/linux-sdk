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
#include "control.h"
#include "../xwindow.h"
#include "../Graphics/igraphics.h"
#include "../Events/controleventmoved.h"
#include "../Events/controleventbackcolor.h"
#include "../Events/controleventfocused.h"
#include "../Events/controleventvisible.h"
#include "../../Delegations/ndelegation.h"
#include <stdlib.h>

Control::Control()
{
	area = new NRectangle();
	backcolor = new NColor(0, 0, 0, 1.0);
	userdata = NULL;
	children = new Collection<Control *>();
	visible = true;
	focused = false;
	entered = false;
	taborder = 0;
	
	onControlChanged = new NDelegationManager();
	onMouseDown = new NDelegationManager();
	onMouseUp = new NDelegationManager();
	onMouseMove = new NDelegationManager();
	onClick = new NDelegationManager();
	onDoubleClick = new NDelegationManager();
	onKeyPress = new NDelegationManager();
	onKeyRelease = new NDelegationManager();
	onMove = new NDelegationManager();
	onVisible = new NDelegationManager();
	onEnter = new NDelegationManager();
	onFocus = new NDelegationManager();
	onBackColor = new NDelegationManager();
	
}

Control::Control(const NRectangle &area)
{
	this->area = new NRectangle(area);
	backcolor = new NColor(0, 0, 0, 1.0);
	userdata = NULL;
	children = new Collection<Control *>();
	visible = true;
	focused = false;
	entered = false;
	taborder = 0;
	
	onControlChanged = new NDelegationManager();
	onMouseDown = new NDelegationManager();
	onMouseUp = new NDelegationManager();
	onMouseMove = new NDelegationManager();
	onClick = new NDelegationManager();
	onDoubleClick = new NDelegationManager();
	onKeyPress = new NDelegationManager();
	onKeyRelease = new NDelegationManager();
	onMove = new NDelegationManager();
	onVisible = new NDelegationManager();
	onEnter = new NDelegationManager();
	onFocus = new NDelegationManager();
	onBackColor = new NDelegationManager();
		
}

Control::~Control()
{
	Release();
	
	delete area;
	delete backcolor;
	children->DeleteAndClear();
	delete children;
			
	delete onControlChanged;
	delete onMouseDown;
	delete onMouseUp;
	delete onMouseMove;
	delete onClick;
	delete onDoubleClick;
	delete onKeyPress;
	delete onKeyRelease;
	delete onMove;
	delete onVisible;
	delete onEnter;
	delete onFocus;
	delete onBackColor;
		
}

int Control::COMPARER(const void *u, const void *v)
{
	Control **uu = (Control **)u;
	Control **vv = (Control **)v;
	int diff = (*uu)->TabOrder() - (*vv)->TabOrder();
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else 
		return 0;
}

void *Control::InternalOnMouseDown(void *params)
{

}

void *Control::InternalOnMouseUp(void *params)
{
	
}

void *Control::InternalOnChildFocusChanged(ControlEventFocused *e)
{
	DelegationOnFocus().Execute(e);
}

NRectangle Control::Area()
{
	return *area;
}

NColor Control::BackColor()
{
	return *backcolor;
}

void *Control::GetUserData()
{
	return userdata;
}

bool Control::IsVisible()
{
	return visible;
}

bool Control::IsFocused()
{
	if (focused) return true;
	for (int i=0; i<children->Count(); i++)
		if ((*children)[i]->IsFocused())
			return true;
	return false;
}

int Control::TabOrder()
{
	return taborder;
}

void Control::SetArea(const NRectangle &area)
{
	if (this->area->Equals(area)) return;
	*this->area = area;	
	ControlEventMoved me(this, area);
	DelegationOnMove().Execute(&me);
	window->Invalidate();
}

void Control::SetBackColor(const NColor &backcolor)
{
	if (this->backcolor->Equals(backcolor)) return;
	*this->backcolor = backcolor;
	ControlEventBackColor bce(this, backcolor);
	DelegationOnBackColor().Execute(&bce);
	Draw();
}

void Control::SetUserData(void *userdata)
{
	this->userdata = userdata;
}

void Control::SetVisible(bool visible)
{
	if (this->visible == visible) return;
	this->visible = visible;
	ControlEventVisible ve(this, visible);
	DelegationOnVisible().Execute(&ve);
	if (visible) 
		Draw();
	else 
		window->Invalidate();
}

void Control::SetFocus(bool focus)
{
	if (!IsFocusable()) return;
	if (this->focused == focus) return;
	this->focused = focus;
	ControlEventFocused fe(this, focus);
	DelegationOnFocus().Execute(&fe);
	Draw();
}

void Control::SetTabOrder(int taborder)
{
	this->taborder = taborder;
}

void Control::Init(XWindow *w)
{
	// Get the graphics context
	this->window = w;
	
	// For detecting click and double click events
	DelegationOnMouseDown() += NDelegation(this, (Delegate)&Control::InternalOnMouseDown);
	DelegationOnMouseUp() += NDelegation(this, (Delegate)&Control::InternalOnMouseUp);
	
	// Call prepare
	Prepare();
}

void Control::ChildControlAdd(Control *c)
{
	if (ChildControlExists(c)) return;
	children->Add(c);
	c->Init(window);
	c->DelegationOnFocus() += NDelegation(this, (Delegate)&Control::InternalOnChildFocusChanged);
	c->Draw();
}

void Control::ChildControlRemove(Control *c)
{
	c->DelegationOnFocus() -= NDelegation(this, (Delegate)&Control::InternalOnChildFocusChanged);
	children->Remove(c);
	window->Invalidate();
}

bool Control::ChildControlExists(Control *c)
{
	return children->Contains(c);
}

void Control::Draw()
{
	IGraphics *gc = window->HandlerGraphics();
	gc->ClipRegionSet(*area);
	gc->SetColor(*backcolor);
	gc->FillRectangle(*area);
	gc->ClipRegionReset();
	
	for (int i=0; i<children->Count(); i++)
		(*children)[i]->Draw();
}

void Control::Prepare()
{
	
}

void Control::Release()
{
	
}

bool Control::IsFocusable()
{
	return false;
}

bool Control::CaptureTabKey()
{
	return false;
}

bool Control::CaptureEnterKey()
{
	return false;
}

bool Control::CaptureSpaceKey()
{
	return false;
}

bool Control::CaptureEscapeKey()
{
	return false;
}

Collection<Control *> Control::EnumFocusableChildren()
{
	Collection<Control *> result;
	if (IsFocusable()) result.Add(this);
	for (int i=0; i<children->Count(); i++) 
		result.AddRange((*children)[i]->EnumFocusableChildren());
	return result;
}

NDelegationManager &Control::DelegationOnControlChanged()
{
	return *onControlChanged;
}

NDelegationManager &Control::DelegationOnMouseDown()
{
	return *onMouseDown;
}

NDelegationManager &Control::DelegationOnMouseUp()
{
	return *onMouseUp;
}

NDelegationManager &Control::DelegationOnMouseMove()
{
	return *onMouseMove;
}

NDelegationManager &Control::DelegationOnClick()
{
	return *onClick;
}

NDelegationManager &Control::DelegationOnDoubleClick()
{
	return *onDoubleClick;
}

NDelegationManager &Control::DelegationOnKeyPress()
{
	return *onKeyPress;
}

NDelegationManager &Control::DelegationOnKeyRelease()
{
	return *onKeyRelease;
}

NDelegationManager &Control::DelegationOnMove()
{
	return *onMove;
}

NDelegationManager &Control::DelegationOnVisible()
{
	return *onVisible;
}

NDelegationManager &Control::DelegationOnEnter()
{
	return *onEnter;
}

NDelegationManager &Control::DelegationOnFocus()
{
	return *onFocus;
}

NDelegationManager &Control::DelegationOnBackColor()
{
	return *onBackColor;
}

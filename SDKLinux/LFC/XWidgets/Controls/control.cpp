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
#include "../Graphics/npoint.h"
#include "../Events/controleventmoved.h"
#include "../Events/controleventbackcolor.h"
#include "../Events/controleventfocused.h"
#include "../Events/controleventvisible.h"
#include "../Events/controleventkey.h"
#include "../Events/controleventmousebutton.h"
#include "../Events/controleventmousemove.h"
#include "../Events/controlevententerleave.h"
#include "../Events/controleventmouseclick.h"
#include "../Events/controleventmousedoubleclick.h"
#include "../../Delegations/ndelegation.h"
#include "../../nwchar.h"
#include "../../Time/datetime.h"
#include <stdlib.h>

Control::Control()
{
	area = new NRectangle();
	Init();
}

Control::Control(const NRectangle &area)
{
	this->area = new NRectangle(area);
	Init();
}

void Control::Init()
{
	backcolor = new NColor(0, 0, 0, 1.0);
	userdata = NULL;
	children = new Collection<Control *>();
	visible = true;
	focused = false;
	entered = false;
	orderTabulation = 0;
	lastMouseDown = NULL;
	lastMouseClick = NULL;
	
	onMouseButtonDown = new NDelegationManager();
	onMouseButtonUp = new NDelegationManager();
	onMouseMove = new NDelegationManager();
	onMouseClick = new NDelegationManager();
	onMouseDoubleClick = new NDelegationManager();
	onKeyPreview = new NDelegationManager();
	onKeyPress = new NDelegationManager();
	onKeyRelease = new NDelegationManager();
	onMove = new NDelegationManager();
	onVisible = new NDelegationManager();
	onEnter = new NDelegationManager();
	onLeave = new NDelegationManager();
	onFocus = new NDelegationManager();
	onBackColor = new NDelegationManager();
}

NPoint Control::GetLocation()
{
	if (parent != NULL) 
		return area->GetOrigin() + parent->GetLocation();
	
	return area->GetOrigin();
}

Control::~Control()
{
	Release();
	
	delete area;
	delete backcolor;
	children->DeleteAndClear();
	delete children;
	if (lastMouseDown != NULL) delete lastMouseDown;
	if (lastMouseClick != NULL) delete lastMouseClick;
			
	delete onMouseButtonDown;
	delete onMouseButtonUp;
	delete onMouseMove;
	delete onMouseClick;
	delete onMouseDoubleClick;
	delete onKeyPreview;
	delete onKeyPress;
	delete onKeyRelease;
	delete onMove;
	delete onVisible;
	delete onEnter;
	delete onLeave;
	delete onFocus;
	delete onBackColor;
		
}

int Control::COMPARER_BY_ORDER_TABULATION(const void *u, const void *v)
{
	Control **uu = (Control **)u;
	Control **vv = (Control **)v;
	int diff = (*uu)->OrderTabulation() - (*vv)->OrderTabulation();
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else 
		return 0;
}

int Control::COMPARER_BY_ORDER_VISIBILITY(const void *u, const void *v)
{
	Control **uu = (Control **)u;
	Control **vv = (Control **)v;
	int diff = (*uu)->OrderVisibility() - (*vv)->OrderVisibility();
	if (diff > 0)
		return 1;
	else if (diff < 0)
		return -1;
	else 
		return 0;
}

bool Control::OnMove(ControlEventMoved *e)
{
	DelegationOnMove().Execute(e);
	return true;
}

bool Control::OnBackColor(ControlEventBackColor *e)
{
	DelegationOnBackColor().Execute(e);
	return true;
}

bool Control::OnVisible(ControlEventVisible *e)
{
	DelegationOnVisible().Execute(e);
	return true;
}

bool Control::OnKeyPreview(ControlEventKey *e)
{
	for (int i=0;i<children->Count(); i++) 
		(*children)[i]->OnKeyPreview(e);
	
	DelegationOnKeyPreview().Execute(e);
	return true;
}

bool Control::OnKeyPress(ControlEventKey *e)
{
	for (int i=0;i<children->Count(); i++) 
		if ((*children)[i]->OnKeyPress(e)) 
			return true;
	
	if (!IsVisible()) return false;
	if (!IsFocused()) return false;
	if (e->KeyCode().Value() == 23 && !CaptureTabKey() || 		// Window focus rotate
		e->KeyCode().Value() == 13 && !CaptureEnterKey() || 	// Return: Window Accept
		e->KeyCode().Value() == 27 && !CaptureEscapeKey() || 	// Escape: Window Cancel
		e->KeyCode().Value() == 20 && !CaptureSpaceKey()) 		// Return: Window Accept
	{
		return false;
	}
	
	DelegationOnKeyPress().Execute(e);
	return true;
}

bool Control::OnKeyRelease(ControlEventKey *e)
{
	for (int i=0;i<children->Count(); i++) 
		if ((*children)[i]->OnKeyRelease(e)) 
			return true;
	
	if (!IsVisible()) return false;
	if (!IsFocused()) return false;
	if (e->KeyCode().Value() == 23 && !CaptureTabKey() || 		// Window focus rotate
		e->KeyCode().Value() == 13 && !CaptureEnterKey() || 	// Return: Window Accept
		e->KeyCode().Value() == 27 && !CaptureEscapeKey() || 	// Escape: Window Cancel
		e->KeyCode().Value() == 20 && !CaptureSpaceKey()) 		// Return: Window Accept
	{
		return false;
	}
	
	DelegationOnKeyRelease().Execute(e);
	return true;
}

bool Control::OnCheckFocus(ControlEventMouseButton *e)
{
	if (!IsVisible()) return false;
	
	if (!area->Contains(e->Position())) {
		if (IsFocusable() && IsFocused()) SetFocus(false);
		return false;
	} 
	
	ControlEventMouseButton mb(*e, NPoint(area->GetX() - e->Position().GetX(), area->GetY() - e->Position().GetY()));
	for (int i=0; i<children->Count(); i++) 
		if ((*children)[i]->OnMouseButtonDown(&mb))
			return true;
	
	if (!IsFocusable()) return false;
	if (!IsFocused()) SetFocus(true);
	return true;
}

bool Control::OnMouseButtonDown(ControlEventMouseButton *e)
{
	if (!IsVisible()) return false;
	if (!area->Contains(e->Position())) return false;
	
	ControlEventMouseButton mb(*e, NPoint(area->GetX() - e->Position().GetX(), area->GetY() - e->Position().GetY()));
	for (int i=0;i<children->Count(); i++) 
		if ((*children)[i]->OnMouseButtonDown(&mb))
			return true;
	
	DelegationOnMouseButtonDown().Execute(&mb);	
	return true;
}

bool Control::OnMouseButtonUp(ControlEventMouseButton *e)
{
	if (!IsVisible()) return false;
	if (!area->Contains(e->Position())) return false;
	
	ControlEventMouseButton mb(*e, NPoint(area->GetX() - e->Position().GetX(), area->GetY() - e->Position().GetY()));
	for (int i=0;i<children->Count(); i++) 
		if ((*children)[i]->OnMouseButtonUp(e)) 
			return true;
				
	bool samebuttonsclick = lastMouseDown != NULL &&
		lastMouseDown->SourceButton1() == e->SourceButton1() &&
		lastMouseDown->SourceButton2() == e->SourceButton2() &&
		lastMouseDown->SourceButton3() == e->SourceButton3() &&
		lastMouseDown->SourceButton4() == e->SourceButton4() &&
		lastMouseDown->SourceButton5() == e->SourceButton5();
	
	if (samebuttonsclick) {
		// Throws click event
		ControlEventMouseClick mc(mb, DateTime() - lastMouseDown->Time());
		OnMouseClick(&mc);
		
		bool samebuttonsdoubleclick = lastMouseClick != NULL &&
			lastMouseClick->SourceButton1() == e->SourceButton1() &&
			lastMouseClick->SourceButton2() == e->SourceButton2() &&
			lastMouseClick->SourceButton3() == e->SourceButton3() &&
			lastMouseClick->SourceButton4() == e->SourceButton4() &&
			lastMouseClick->SourceButton5() == e->SourceButton5();
		
		if (samebuttonsdoubleclick) {
			// Throws double click event
			ControlEventMouseDoubleClick mdc(mb, DateTime() - lastMouseClick->Time());
			OnMouseDoubleClick(&mdc);
			
			// Deletes lastMouseClick
			if (lastMouseClick) delete lastMouseClick;
			lastMouseClick = NULL;
		}
		
		// Updates lastMouseClick
		if (lastMouseClick == NULL) lastMouseClick = new ControlEventMouseButton(*e);
		else *lastMouseClick = *e;
	}
	
	// Deletes lastMouseDown 
	if (lastMouseDown != NULL) delete lastMouseDown;
	lastMouseDown = NULL;
	
	DelegationOnMouseButtonUp().Execute(e);
	return true;
}

bool Control::OnMouseClick(ControlEventMouseClick *e)
{
	DelegationOnMouseClick().Execute(e);
	return true;
}

bool Control::OnMouseDoubleClick(ControlEventMouseDoubleClick *e)
{
	DelegationOnMouseDoubleClick().Execute(e);
	return true;
}

bool Control::OnCheckEnterLeave(ControlEventMouseMove *e)
{
	if (!IsVisible()) return false;
	bool inarea = area->Contains(e->Position());
	
	ControlEventMouseMove mm(*e, NPoint(area->GetX() - e->Position().GetX(), area->GetY() - e->Position().GetY()));
	for (int i=0; children->Count(); i++)
		(*children)[i]->OnCheckEnterLeave(&mm);
	
	if (!entered && inarea) {
		ControlEventEnterLeave el(true);
		OnMouseEnter(&el);
	} else if (entered && !inarea) {
		ControlEventEnterLeave el(false);
		OnMouseLeave(&el);
	}
	return true;
}

bool Control::OnMouseMove(ControlEventMouseMove *e)
{
	if (!IsVisible()) return false;
	if (!area->Contains(e->Position())) return false;

	ControlEventMouseMove ee(*e, NPoint(area->GetX() - e->Position().GetX(), area->GetY() - e->Position().GetY()));
	for (int i=0; children->Count(); i++)
		if ((*children)[i]->OnMouseMove(&ee))
			return true;

	DelegationOnMouseMove().Execute(e);
	return true;
}

bool Control::OnMouseEnter(ControlEventEnterLeave *e)
{
	DelegationOnMouseEnter().Execute(e);
	return true;
}

bool Control::OnMouseLeave(ControlEventEnterLeave *e)
{
	DelegationOnMouseLeave().Execute(e);
	return true;
}

bool Control::OnFocus(ControlEventFocused *e)
{
	DelegationOnFocus().Execute(e);
	return true;
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

int Control::OrderTabulation()
{
	return orderTabulation;
}

int Control::OrderVisibility()
{
	return orderVisibility;
}

void Control::SetArea(const NRectangle &area)
{
	if (this->area->Equals(area)) return;
	*this->area = area;
	
	ControlEventMoved me(this, area);
	OnMove(&me);
	
	window->Invalidate();
}

void Control::SetBackColor(const NColor &backcolor)
{
	if (this->backcolor->Equals(backcolor)) return;
	*this->backcolor = backcolor;
	
	ControlEventBackColor bce(this, backcolor);
	OnBackColor(&bce);
	
	window->Invalidate();
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
	OnVisible(&ve);
	
	window->Invalidate();
}

void Control::SetFocus(bool focus)
{
	if (!IsVisible()) return;
	if (!IsFocusable()) return;
	if (this->focused == focus) return;
	this->focused = focus;
	
	ControlEventFocused fe(this, focus);
	OnFocus(&fe);
	
	window->Invalidate();
}

void Control::SetOrderTabulation(int taborder)
{
	this->orderTabulation = orderTabulation;
}

void Control::SetOrderVisibility(int orderVisibility)
{
	this->orderVisibility = orderVisibility;
}

void Control::Init(XWindow *w, Control *parent)
{
	// Get the graphics context
	this->window = w;
	this->parent = parent;
	
	// Call prepare
	Prepare();
}

void Control::ChildControlAdd(Control *c)
{
	if (ChildControlExists(c)) return;
	c->Init(window, this);
	children->Add(c);	
	window->Invalidate();
}

void Control::ChildControlRemove(Control *c)
{
	children->Remove(c);
	window->Invalidate();
}

bool Control::ChildControlExists(Control *c)
{
	return children->Contains(c);
}

void Control::Draw()
{
	if (!IsVisible()) return;
	
	NPoint p = GetLocation();
	NRectangle r(p.GetX(), p.GetY(), area->GetWidth(), area->GetHeight());
	
	IGraphics *gc = window->HandlerGraphics();
	gc->ClipRegionSet(r);
	
	// Draw background
	gc->SetColor(*backcolor);
	gc->FillRectangle(r);
	
	// Draw children controls
	for (int i=0; i<children->Count(); i++)	(*children)[i]->Draw();
	
	gc->ClipRegionReset();	
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
	children->QuickSort(Control::COMPARER_BY_ORDER_TABULATION);

	Collection<Control *> result;
	if (IsFocusable()) result.Add(this);	
	for (int i=0; i<children->Count(); i++) 
		result.AddRange((*children)[i]->EnumFocusableChildren());
		
	return result;
}

NDelegationManager &Control::DelegationOnMouseButtonDown()
{
	return *onMouseButtonDown;
}

NDelegationManager &Control::DelegationOnMouseButtonUp()
{
	return *onMouseButtonUp;
}

NDelegationManager &Control::DelegationOnMouseMove()
{
	return *onMouseMove;
}

NDelegationManager &Control::DelegationOnMouseClick()
{
	return *onMouseClick;
}

NDelegationManager &Control::DelegationOnMouseDoubleClick()
{
	return *onMouseDoubleClick;
}

NDelegationManager &Control::DelegationOnKeyPreview()
{
	return *onKeyPreview;
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

NDelegationManager &Control::DelegationOnMouseEnter()
{
	return *onEnter;
}

NDelegationManager &Control::DelegationOnMouseLeave()
{
	return *onLeave;
}

NDelegationManager &Control::DelegationOnFocus()
{
	return *onFocus;
}

NDelegationManager &Control::DelegationOnBackColor()
{
	return *onBackColor;
}

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
	taborder = 0;
	lastmousedown = NULL;
	lastmouseclick = NULL;
	
	onMouseDown = new NDelegationManager();
	onMouseUp = new NDelegationManager();
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

Control::~Control()
{
	Release();
	
	delete area;
	delete backcolor;
	children->DeleteAndClear();
	delete children;
	if (lastmousedown != NULL) delete lastmousedown;
	if (lastmouseclick != NULL) delete lastmouseclick;
			
	delete onMouseDown;
	delete onMouseUp;
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

bool Control::OnMove(ControlEventMoved *e)
{
	DelegationOnMove().Execute(e);
}

bool Control::OnBackColor(ControlEventBackColor *e)
{
	DelegationOnBackColor().Execute(e);
}

bool Control::OnVisible(ControlEventVisible *e)
{
	DelegationOnVisible().Execute(e);
}

bool Control::OnKeyPreview(ControlEventKey *e)
{
	for (int i=0;i<children->Count(); i++) 
		(*children)[i]->OnKeyPreview(e);
	
	DelegationOnKeyPreview().Execute(e);
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

bool Control::OnMouseButtonDown(ControlEventMouseButton *e)
{
	if (!IsVisible()) return false;
	bool mousedownonchildren = false;
	bool inarea = area->Contains(e->Position());
	if (inarea) {
		ControlEventMouseButton eee(*e, NPoint(area->GetX() - e->Position().GetX(), area->GetY() - e->Position().GetY()));
		for (int i=0;i<children->Count() && !mousedownonchildren; i++) 
			mousedownonchildren |= (*children)[i]->OnMouseButtonDown(&eee);
	}
	if (inarea && !mousedownonchildren) {
		lastmousedown = new ControlEventMouseButton(*e);
		if (IsFocusable() && !IsFocused()) SetFocus(true);
	} else {
		if (IsFocusable() && IsFocused()) SetFocus(false);		
	}
	
	return inarea;
}

bool Control::OnMouseButtonUp(ControlEventMouseButton *e)
{
	if (!IsVisible()) return false;
	bool mouseuponchildren = false;
	bool inarea = area->Contains(e->Position());
	if (inarea) {
		ControlEventMouseButton eee(*e, NPoint(area->GetX() - e->Position().GetX(), area->GetY() - e->Position().GetY()));
		for (int i=0;i<children->Count() && !mouseuponchildren; i++) 
			mouseuponchildren |= (*children)[i]->OnMouseButtonUp(e);
	}
	if (inarea && !mouseuponchildren) {		
		DelegationOnMouseUp().Execute(e);
		
		bool samebuttonsclick = lastmousedown != NULL &&
			lastmousedown->SourceButton1() == e->SourceButton1() &&
			lastmousedown->SourceButton2() == e->SourceButton2() &&
			lastmousedown->SourceButton3() == e->SourceButton3() &&
			lastmousedown->SourceButton4() == e->SourceButton4() &&
			lastmousedown->SourceButton5() == e->SourceButton5();
		
		if (samebuttonsclick) {
			ControlEventMouseClick ee(*e, DateTime() - lastmousedown->Time());
			OnMouseClick(&ee);
			
			bool samebuttonsdoubleclick = lastmouseclick != NULL &&
				lastmouseclick->SourceButton1() == e->SourceButton1() &&
				lastmouseclick->SourceButton2() == e->SourceButton2() &&
				lastmouseclick->SourceButton3() == e->SourceButton3() &&
				lastmouseclick->SourceButton4() == e->SourceButton4() &&
				lastmouseclick->SourceButton5() == e->SourceButton5();
			
			if (samebuttonsdoubleclick) {
				ControlEventMouseDoubleClick eee(*e, DateTime() - lastmouseclick->Time());
				OnMouseDoubleClick(&eee);
				
				if (lastmouseclick) delete lastmouseclick;
				lastmouseclick = NULL;
			}
			
			if (lastmouseclick == NULL) lastmouseclick = new ControlEventMouseButton(*e);
			else *lastmouseclick = *e;
		}
	}
	if (lastmousedown != NULL) delete lastmousedown;
	lastmousedown = NULL;
	
	return inarea;
}

bool Control::OnMouseClick(ControlEventMouseClick *e)
{
	DelegationOnMouseClick().Execute(e);
}

bool Control::OnMouseDoubleClick(ControlEventMouseDoubleClick *e)
{
	DelegationOnMouseDoubleClick().Execute(e);
}

bool Control::OnMouseMove(ControlEventMouseMove *e)
{
	if (!IsVisible()) return false;
	bool inarea = area->Contains(e->Position());
	if (inarea) {
		ControlEventMouseMove ee(*e, NPoint(area->GetX() - e->Position().GetX(), area->GetY() - e->Position().GetY()));
		for (int i=0; children->Count(); i++)
			(*children)[i]->OnMouseMove(&ee);
			
		DelegationOnMouseMove().Execute(e);
	}
		
	if (!entered && inarea) {
		ControlEventEnterLeave eee(true);
		OnMouseEnter(&eee);
	} else if (entered && !inarea) {
		ControlEventEnterLeave eee(false);
		OnMouseLeave(&eee);
	}
	
	return inarea;
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

int Control::TabOrder()
{
	return taborder;
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
	OnFocus(&fe);
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
	
	// Call prepare
	Prepare();
}

void Control::ChildControlAdd(Control *c)
{
	if (ChildControlExists(c)) return;
	children->Add(c);
	c->Init(window);
	c->Draw();
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

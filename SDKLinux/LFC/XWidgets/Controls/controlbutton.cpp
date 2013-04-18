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
#include "controlbutton.h"
#include "../Graphics/ncolor.h"
#include "../Graphics/npoint.h"
#include "../Graphics/nsize.h"
#include "../Graphics/nrectangle.h"
#include "../Graphics/igraphics.h"
#include "../Graphics/graphicspattern.h"
#include "../Graphics/graphicspatternlinear.h"
#include "../Events/controleventkey.h"
#include "../Events/controleventaction.h"
#include "../../nwchar.h"
#include "../../Delegations/ndelegationmanager.h"
#include "../xwindow.h"

ControlButton::ControlButton(const Text &t) : Control()
{
	text = new Text(t);
	textcolor = new NColor(0, 0, 0, 1.0);
	forecolor = new NColor(0.95, 0.95, 0.97, 1.0);
	autosize = true;
	calculateAreaOnInit = true;
	isPressed = false;
	onAction = new NDelegationManager();
}

ControlButton::ControlButton(const Text &t, const NPoint &p) 
	: Control(NRectangle(p, NSize(0, 0)))
{
	text = new Text(t);
 	textcolor = new NColor(0, 0, 0, 1.0);
	forecolor = new NColor(0.95, 0.95, 0.97, 1.0);
	autosize = true;
	calculateAreaOnInit = true;
	isPressed = false;
	onAction = new NDelegationManager();
}

ControlButton::ControlButton(const Text &t, const NRectangle &r)
	: Control(r)
{
	text = new Text(t);
	textcolor = new NColor(0, 0, 0, 1.0);
	forecolor = new NColor(0.95, 0.95, 0.97, 1.0);
	autosize = false;
	calculateAreaOnInit = false;
	isPressed = false;
	onAction = new NDelegationManager();
}

ControlButton::~ControlButton()
{
	delete text;
	delete textcolor;
	delete forecolor;
	delete onAction;
}

void ControlButton::UpdateSize()
{
	if (autosize && window != NULL) {
		NSize ss = window->HandlerGraphics()->GetTextExtents(text == NULL ? "" : *text, *font);
		NRectangle r(area->GetX(), area->GetY(), ss.GetWidth() + 10, ss.GetHeight() + 6);		
		Control::SetArea(r);
	}	
}

bool ControlButton::OnAction(ControlEventAction *e)
{
	DelegationOnAction().Execute(e);
	return true;
}

void ControlButton::SetAutoSize(bool autosize)
{
	this->autosize = autosize;
	UpdateSize();
}

void ControlButton::SetText(const Text &t)
{
	*text = t;
	UpdateSize();
}

void ControlButton::SetTextColor(const NColor &c)
{
	*textcolor = c;
	Draw();
}

void ControlButton::SetForeColor(const NColor &c)
{
	*forecolor = c;
	Draw();
}

bool ControlButton::GetAutoSize()
{
	return autosize;
}

Text ControlButton::GetText()
{
	return *text;
}

NColor ControlButton::GetTextColor()
{
	return *textcolor;
}

NColor ControlButton::GetForeColor()
{
	return *forecolor;
}

void ControlButton::SetFont(const NFont &f)
{
	*this->font = f;
	UpdateSize();
}

void ControlButton::SetArea(const NRectangle &r)
{
	this->area->SetPosition(((NRectangle *)&r)->GetPosition());
	
	if (autosize)
		UpdateSize();
	else
		Control::SetArea(r);
}

bool ControlButton::IsFocusable()
{
	return true;
}

bool ControlButton::CaptureSpaceKey()
{
	return true;
}

bool ControlButton::CaptureEnterKey()
{
	return true;
}

void ControlButton::Init(XWindow *w, Control *parent)
{
	Control::Init(w, parent);
	UpdateSize();
}

bool ControlButton::OnDrawBackground(IGraphics *g, NRectangle *r)
{
	g->SetColor(*backcolor);
	g->FillRectangle(*r);
	return true;
}

bool ControlButton::OnDraw(IGraphics *g, NRectangle *r)
{
	g->SetLineWidth(1);
	NRectangle rr(r->GetX() + 1, r->GetY() + 1, r->GetWidth() - 1, r->GetHeight() - 1);
	NRectangle rrr(r->GetX() + 2, r->GetY() + 2, r->GetWidth() - 2, r->GetHeight() - 2);
	
	if (isMouseOver && !isPressed) {
		GraphicsPatternLinear pp(NPoint(0, 0), NPoint(0, r->GetHeight()));
		NColor c(forecolor->R() * 1.12, forecolor->G() * 1.12, forecolor->B() * 1.12, forecolor->A());
		pp.AddColorAtDistance(c, 0);
		pp.AddColorAtDistance(*forecolor, r->GetHeight() / 2);
		pp.AddColorAtDistance(c, r->GetHeight());
		g->SetPattern(pp);
	} else if (isPressed && isMouseOver) {
		GraphicsPatternLinear pp(NPoint(0, 0), NPoint(0, r->GetHeight()));
		NColor c(forecolor->R() * 0.75, forecolor->G() * 0.75, forecolor->B() * 0.75, forecolor->A());
		pp.AddColorAtDistance(*forecolor, 0);
		pp.AddColorAtDistance(c, r->GetHeight() / 2);
		pp.AddColorAtDistance(*forecolor, r->GetHeight());
		g->SetPattern(pp);
	} else {
		GraphicsPatternLinear pp(NPoint(0, 0), NPoint(0, r->GetHeight()));
		NColor c(forecolor->R() * 0.88, forecolor->G() * 0.88, forecolor->B() * 0.88, forecolor->A());
		pp.AddColorAtDistance(*forecolor, 0);
		pp.AddColorAtDistance(c, r->GetHeight() / 2);
		pp.AddColorAtDistance(*forecolor, r->GetHeight());
		g->SetPattern(pp);
	}
	g->FillRoundRectangle(rr, 5);
	
	g->SetColor(*textcolor);
	if (isPressed) {
		g->DrawText(*text, 6, 2, *font);
	} else {
		g->DrawText(*text, 5, 1, *font);
	}
		
	NColor ccc(forecolor->R() * 1.12, forecolor->G() * 1.12, forecolor->B() * 1.12, forecolor->A());	
	g->SetColor(ccc);
	g->DrawRoundRectangle(rrr, 5);
	g->SetColor(NColor(0, 0, 0, 1.0));
	g->DrawRoundRectangle(rr, 5);
}

bool ControlButton::OnMouseButtonDown(ControlEventMouseButton *e)
{
	if (!Control::OnMouseButtonDown(e)) return false;
	if (!isPressed) {
		isPressed = true;
		Draw();
	}
	return true;
}

bool ControlButton::OnMouseButtonUp(ControlEventMouseButton *e)
{
	if (isPressed) {
		isPressed = false;
		Draw();
	}
	if (!Control::OnMouseButtonUp(e)) return false;
	
	ControlEventAction a(this);
	OnAction(&a);
	
	return true;
}

bool ControlButton::OnMouseMove(ControlEventMouseMove *e)
{
	if (!Control::OnMouseMove(e)) {
		if (isMouseOver) {
			isMouseOver = false;
			Draw();
		}
		return false;
	}
	
	if (!isMouseOver) {
		isMouseOver = true;
		Draw();
	}
	
	return true;
}

bool ControlButton::OnKeyPress(ControlEventKey *e)
{
	if (!Control::OnKeyPress(e)) return false;
	isPressed = e->KeyCode().Value() == '\r' || e->KeyCode().Value() == ' ';
	Draw();
	return true;
}

bool ControlButton::OnKeyRelease(ControlEventKey *e)
{
	if (!Control::OnKeyRelease(e)) return false;
	if (!isPressed) return true;
	isPressed = false;
	Draw();
	
	ControlEventAction a(this);
	OnAction(&a);
	
	return true;
}

NDelegationManager &ControlButton::DelegationOnAction()
{
	return *onAction;
}

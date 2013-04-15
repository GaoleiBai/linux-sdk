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
#include "../xwindow.h"

ControlButton::ControlButton(const Text &t) : Control()
{
	text = new Text(t);
	textcolor = new NColor(0, 0, 0, 1.0);
	forecolor = new NColor(0.95, 0.95, 0.97, 1.0);
	autosize = true;
	calculateAreaOnInit = true;
}

ControlButton::ControlButton(const Text &t, const NPoint &p) 
	: Control(NRectangle(p, NSize(0, 0)))
{
	text = new Text(t);
	textcolor = new NColor(0, 0, 0, 1.0);
	forecolor = new NColor(0.95, 0.95, 0.97, 1.0);
	autosize = true;
	calculateAreaOnInit = true;
}

ControlButton::ControlButton(const Text &t, const NRectangle &r)
	: Control(r)
{
	text = new Text(t);
	textcolor = new NColor(0, 0, 0, 1.0);
	forecolor = new NColor(0.95, 0.95, 0.97, 1.0);
	autosize = false;
	calculateAreaOnInit = false;
}

ControlButton::~ControlButton()
{
	delete text;
	delete textcolor;
	delete forecolor;
}

void ControlButton::UpdateSize()
{
	if (autosize && window != NULL) {
		NSize ss = window->HandlerGraphics()->GetTextExtents(text == NULL ? "" : *text, *font);
		NRectangle r(area->GetX(), area->GetY(), ss.GetWidth() + 6, ss.GetHeight() + 6);		
		Control::SetArea(r);
	}	
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
	
}
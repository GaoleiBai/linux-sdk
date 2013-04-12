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
#include "controllabel.h"
#include "../../Text/text.h"
#include "../xwindow.h"
#include "../Graphics/nsize.h"
#include "../Graphics/igraphics.h"
#include <stdlib.h>

ControlLabel::ControlLabel(const Text &text) 
	: Control()
{
	this->text = NULL;
	*textcolor = NColor(0, 0, 0, 1.0);
}

ControlLabel::ControlLabel(const Text &text, const NRectangle &area)
	: Control(area)
{
	this->text = new Text(text);
	*this->area = area;
	*textcolor = NColor(0, 0, 0, 1.0);
}

ControlLabel::~ControlLabel()
{
	if (text != NULL) delete text;
	delete textcolor;
}

void ControlLabel::SetText(const Text &t)
{
	if (text == NULL) text = new Text(t);
	*text = t;
	
	NSize ss = window->HandlerGraphics()->GetTextExtents(text == NULL ? "" : *text, *font);
	*area = NRectangle(area->GetX(), area->GetY(), ss.GetWidth() + 6, ss.GetHeight() + 6);
	
	Draw();
}

Text ControlLabel::GetText()
{
	if (text == NULL) return "";
	return *text;
}

void ControlLabel::SetTextColor(const NColor &c)
{
	*textcolor = c;
	Draw();
}

NColor ControlLabel::GetTextColor()
{
	return *textcolor;
}

void ControlLabel::Init(XWindow *w, Control *parent)
{
	Control::Init(w, parent);
	
	NSize ss = w->HandlerGraphics()->GetTextExtents(text == NULL ? "" : *text, *font);
	*area = NRectangle(area->GetX(), area->GetY(), ss.GetWidth(), ss.GetHeight());
}

bool ControlLabel::OnDrawBackground(IGraphics *gc, NRectangle *r)
{
	gc->SetColor(*backcolor);
	gc->FillRectangle(*r);
	return true;
}

bool ControlLabel::OnDraw(IGraphics *gc, NRectangle *r)
{
	gc->SetColor(*textcolor);
	gc->DrawText(*text, 3, 3, *font);
}


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
}

ControlLabel::ControlLabel(const Text &text, const NRectangle &area)
	: Control(area)
{
	this->text = new Text(text);
	*this->area = area;
}

ControlLabel::~ControlLabel()
{
	if (text != NULL) delete text;
}

void ControlLabel::SetText(const Text &t)
{
	if (text == NULL) text = new Text(t);
	*text = t;
	
	NSize ss = window->HandlerGraphics()->GetTextExtents(text == NULL ? "" : *text, *font);
	*area = NRectangle(area->GetX(), area->GetY(), ss.GetWidth(), ss.GetHeight());
	
	Draw();
}

Text ControlLabel::GetText()
{
	if (text == NULL) return "";
	return *text;
}

void ControlLabel::Init(XWindow *w, Control *parent)
{
	Control::Init(w, parent);
	
	NSize ss = w->HandlerGraphics()->GetTextExtents(text == NULL ? "" : *text, *font);
	*area = NRectangle(area->GetX(), area->GetY(), ss.GetWidth(), ss.GetHeight());
}


bool ControlLabel::OnDraw(IGraphics *gc, NRectangle *r)
{
	
}


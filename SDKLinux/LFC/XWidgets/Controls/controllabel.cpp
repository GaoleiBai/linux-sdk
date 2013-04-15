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
#include "../Graphics/npoint.h"
#include "../Graphics/nsize.h"
#include "../Graphics/igraphics.h"
#include <stdlib.h>

ControlLabel::ControlLabel(const Text &text) 
	: Control()
{
	this->text = new Text(text);
	textcolor = new NColor(0, 0, 0, 1.0);
	autosize = true;
}

ControlLabel::ControlLabel(const Text &text, const NPoint &position)
	: Control(NRectangle(position, NSize(0, 0)))
{
	this->text = new Text(text);
	textcolor = new NColor(0, 0, 0, 1.0);
	autosize = true;
}

ControlLabel::ControlLabel(const Text &text, const NRectangle &area)
	: Control(area)
{
	this->text = new Text(text);
	textcolor = new NColor(0, 0, 0, 1.0);
	autosize = false;
}

ControlLabel::~ControlLabel()
{
	if (text != NULL) delete text;
	delete textcolor;
}

void ControlLabel::UpdateSize() {
	if (autosize && window != NULL) {
		NSize ss = window->HandlerGraphics()->GetTextExtents(text == NULL ? "" : *text, *font);
		NRectangle r(area->GetX(), area->GetY(), ss.GetWidth() + 6, ss.GetHeight() + 6);
		Control::SetArea(r);
	}
}

void ControlLabel::SetText(const Text &t)
{
	if (text == NULL) text = new Text(t);
	*text = t;
	
	UpdateSize();
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

void ControlLabel::SetAutoSize(bool autosize)
{
	this->autosize = autosize;
	UpdateSize();
}

bool ControlLabel::GetAutoSize()
{
	return autosize;
}

void ControlLabel::SetFont(const NFont &font)
{
	Control::SetFont(font);
	UpdateSize();
}

void ControlLabel::SetArea(const NRectangle &area)
{
	this->area->SetPosition(((NRectangle *)&area)->GetPosition());
	
	if (autosize)
		UpdateSize();
	else
		Control::SetArea(area);
}

void ControlLabel::Init(XWindow *w, Control *parent)
{
	Control::Init(w, parent);
	UpdateSize();
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
	gc->DrawText(*text, 1, 1, *font);
}


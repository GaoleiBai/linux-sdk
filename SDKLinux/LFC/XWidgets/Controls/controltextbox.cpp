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
#include "controltextbox.h"
#include "../Graphics/ncolor.h"
#include "../Graphics/npoint.h"
#include "../Graphics/igraphics.h"

ControlTextBox::ControlTextBox(const NRectangle &r)
	: Control(r)
{
	text = new Text("");
	selectionStart = 0;
	selectionLength = 0;
	textColor = new NColor(0, 0, 0, 1.0);
	textBackColor = new NColor(1.0, 1.0, 1.0, 1.0);
}

ControlTextBox::ControlTextBox(const Text &t, const NRectangle &r)
{
	text = new Text(t);
	selectionStart = 0;
	selectionLength = 0;
	textColor = new NColor(0, 0, 0, 1.0);
	textBackColor = new NColor(1.0, 1.0, 1.0, 1.0);
}

ControlTextBox::~ControlTextBox()
{
	delete text;
	delete textColor;
	delete textBackColor;
}

Text ControlTextBox::GetText()
{
	return *text;
}

Text ControlTextBox::GetSelectedText()
{
	return text->SubText(selectionStart, selectionLength);
}

int ControlTextBox::GetSelectionStart()
{
	return selectionStart;
}

int ControlTextBox::GetSelectionLenght()
{
	return selectionLength;
}

NColor ControlTextBox::GetTextColor()
{
	return *textColor;
}

NColor ControlTextBox::GetTextBackColor()
{
	return *textBackColor;
}

void ControlTextBox::SetText(const Text &t)
{
	*text = t;
	selectionStart = 0;
	selectionLength = ((Text *)&t)->Length();
	Draw();
}

void ControlTextBox::SetSelectedText(const Text &t)
{
	*text = text->Replace(GetSelectedText(), t);
	selectionLength = ((Text *)&t)->Length();
	Draw();
}

void ControlTextBox::SetSelectionStart(int s)
{
	if (s >= text->Length()) {
		selectionStart = text->Length() - 1;
		selectionLength = 0;
	} else if (s + selectionLength >= text->Length()) {
		selectionStart = s;
		selectionLength = text->Length() - s;
	} else {
		selectionStart = s;
	}
	Draw();
}

void ControlTextBox::SetSelectionLength(int l)
{
	selectionLength = 
		selectionStart + l >= text->Length() ? 
		text->Length() - selectionStart : l;
	Draw();
}

void ControlTextBox::SetTextColor(const NColor &c)
{
	*textColor = c;
	Draw();
}

void ControlTextBox::SetTextBackColor(const NColor &c)
{
	*textBackColor = c;
	Draw();
}

bool ControlTextBox::IsFocusable()
{
	return true;
}

bool ControlTextBox::CaptureSpaceKey()
{
	return true;
}

bool ControlTextBox::OnDrawBackground(IGraphics *g, NRectangle *r)
{
	g->SetColor(*backcolor);
	g->FillRectangle(*area);
}

bool ControlTextBox::OnDraw(IGraphics *g, NRectangle *r)
{
	g->SetColor(*textBackColor);
	g->FillRoundRectangle(*r, 5);
	
	// Draw a subtle inline
	g->SetLineWidth(2);
	double rr =	(backcolor->R() + textBackColor->R()) / 2;
	double gg =	(backcolor->G() + textBackColor->G()) / 2;
	double bb =	(backcolor->B() + textBackColor->B()) / 2;
	double aa =	(backcolor->A() + textBackColor->A()) / 2;
	g->SetColor(NColor(rr, gg, bb, aa));
	g->DrawRoundRectangle(NRectangle(r->GetPosition() + NPoint(1, 1), r->GetSize() - NSize(2, 2)), 5);

	// Draw outline
	g->SetLineWidth(1);
	if (focused)
		g->SetColor(*focusedcolor);
	else
		g->SetColor(NColor(0, 0, 0, 1.0));
	g->DrawRoundRectangle(NRectangle(r->GetPosition() + NPoint(1, 1), r->GetSize() - NSize(2, 2)), 5);
	
	g->Save();
	g->TransformTranslate(3, 3);
	g->ClipRegionSet(NRectangle(r->GetPosition(), r->GetSize() - NSize(6, 6)));
	
	// TODO: Draw Text
	NSize ss = g->GetTextExtents(*text, *font);
	g->DrawText(*text, (area->GetWidth() - ss.GetWidth()) / 2, (area->GetHeight() - ss.GetHeight()) / 2, *font);
	
	g->Restore();
}

bool ControlTextBox::OnKeyPress(ControlEventKey *e)
{
	if (!Control::OnKeyPress(e)) return false;
	
	
	return true;
}

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

void ControlTextBox::Draw()
{
}

bool ControlTextBox::IsFocusable()
{
	return true;
}

bool ControlTextBox::CaptureTabKey()
{
	return false;
}

bool ControlTextBox::CaptureEnterKey()
{
	return false;
}

bool ControlTextBox::CaptureSpaceKey()
{
	return true;
}

bool ControlTextBox::CaptureEscapeKey()
{
	return true;
}


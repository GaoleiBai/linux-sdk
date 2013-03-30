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
#include "../Graphics/igraphics.h"
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
	
	onControlChanged = new NDelegationManager();
	onMouseDown = new NDelegationManager();
	onMouseUp = new NDelegationManager();
	onMouseMove = new NDelegationManager();
	onClick = new NDelegationManager();
	onDoubleClick = new NDelegationManager();
	onKeyDown = new NDelegationManager();
	onKeyUp = new NDelegationManager();
	onMove = new NDelegationManager();
	onVisible = new NDelegationManager();
	onEnter = new NDelegationManager();
	onFocus = new NDelegationManager();
	
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
	
	onControlChanged = new NDelegationManager();
	onMouseDown = new NDelegationManager();
	onMouseUp = new NDelegationManager();
	onMouseMove = new NDelegationManager();
	onClick = new NDelegationManager();
	onDoubleClick = new NDelegationManager();
	onKeyDown = new NDelegationManager();
	onKeyUp = new NDelegationManager();
	onMove = new NDelegationManager();
	onVisible = new NDelegationManager();
	onEnter = new NDelegationManager();
	onFocus = new NDelegationManager();
		
}

Control::~Control()
{
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
	delete onKeyDown;
	delete onKeyUp;
	delete onMove;
	delete onVisible;
	delete onEnter;
	delete onFocus;
		
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

void Control::SetArea(const NRectangle &area)
{
	*this->area = area;
}

void Control::SetBackColor(const NColor &backcolor)
{
	*this->backcolor = backcolor;
}

void Control::SetUserData(void *userdata)
{
	this->userdata = userdata;
}

void Control::SetFocused(bool focused)
{
	if (this->focused == focused) return;
	DelegationOnControlChanged().Execute(this);
}

void Control::SetVisible(bool visible)
{
	
}

void Control::Draw(IGraphics *g)
{
	g->ClipRegionSet(*area);
	g->SetColor(*backcolor);
	g->FillRectangle(*area);
	g->ClipRegionReset();
}

void Control::Prepare()
{
	
}

void Control::Release()
{
	
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

NDelegationManager &Control::DelegationOnKeyDown()
{
	return *onKeyDown;
}

NDelegationManager &Control::DelegationOnKeyUp()
{
	return *onKeyUp;
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

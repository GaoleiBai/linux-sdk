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
#include "windoweventbutton.h"
#include "../../Time/datetime.h"
#include "../Graphics/npoint.h"

WindowEventButton::WindowEventButton(XButtonEvent *e)
{
	this->e = e;
}

WindowEventButton::~WindowEventButton()
{
}

DateTime WindowEventButton::Time()
{
	return DateTime((time_t)e->time);
}

NPoint WindowEventButton::Position()
{
	return NPoint(e->x, e->y);
}

NPoint WindowEventButton::PositionRoot()
{
	return NPoint(e->x_root, e->y_root);
}

bool WindowEventButton::PressedButton1()
{
	return e->state & Button1Mask != 0;
}

bool WindowEventButton::PressedButton2()
{
	return e->state & Button2Mask != 0;
}

bool WindowEventButton::PressedButton3()
{
	return e->state & Button3Mask != 0;
}

bool WindowEventButton::PressedButton4()
{
	return e->state & Button4Mask != 0;
}

bool WindowEventButton::PressedButton5()
{
	return e->state & Button5Mask != 0;
}

bool WindowEventButton::PressedControl()
{
	return e->state & ControlMask != 0;
}

bool WindowEventButton::PressedLock()
{
	return e->state & LockMask != 0;
}

bool WindowEventButton::PressedShift()
{
	return e->state & ShiftMask != 0;
}

bool WindowEventButton::PressedMod1()
{
	return e->state & Mod1Mask != 0;
}

bool WindowEventButton::PressedMod2()
{
	return e->state & Mod2Mask != 0;
}

bool WindowEventButton::PressedMod3()
{
	return e->state & Mod3Mask != 0;
}

bool WindowEventButton::PressedMod4()
{
	return e->state & Mod4Mask != 0;
}

bool WindowEventButton::PressedMod5()
{
	return e->state & Mod5Mask != 0;
}

bool WindowEventButton::SourceButton1()
{
	return e->button == Button1;
}

bool WindowEventButton::SourceButton2()
{
	return e->button == Button2;
}

bool WindowEventButton::SourceButton3()
{
	return e->button == Button3;
}

bool WindowEventButton::SourceButton4()
{
	return e->button == Button4;
}

bool WindowEventButton::SourceButton5()
{
	return e->button == Button5;
}


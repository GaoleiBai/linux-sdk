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
#include "buttonevent.h"
#include "../../Time/datetime.h"
#include "../Graphics/npoint.h"

ButtonEvent::ButtonEvent(XButtonEvent *e)
{
	this->e = e;
}

ButtonEvent::~ButtonEvent()
{
}

DateTime ButtonEvent::Time()
{
	return DateTime((time_t)e->time);
}

NPoint ButtonEvent::Position()
{
	return NPoint(e->x, e->y);
}

NPoint ButtonEvent::PositionRoot()
{
	return NPoint(e->x_root, e->y_root);
}

bool ButtonEvent::PressedButton1()
{
	return e->state & Button1Mask != 0;
}

bool ButtonEvent::PressedButton2()
{
	return e->state & Button2Mask != 0;
}

bool ButtonEvent::PressedButton3()
{
	return e->state & Button3Mask != 0;
}

bool ButtonEvent::PressedButton4()
{
	return e->state & Button4Mask != 0;
}

bool ButtonEvent::PressedButton5()
{
	return e->state & Button5Mask != 0;
}

bool ButtonEvent::PressedControl()
{
	return e->state & ControlMask != 0;
}

bool ButtonEvent::PressedLock()
{
	return e->state & LockMask != 0;
}

bool ButtonEvent::PressedShift()
{
	return e->state & ShiftMask != 0;
}

bool ButtonEvent::PressedMod1()
{
	return e->state & Mod1Mask != 0;
}

bool ButtonEvent::PressedMod2()
{
	return e->state & Mod2Mask != 0;
}

bool ButtonEvent::PressedMod3()
{
	return e->state & Mod3Mask != 0;
}

bool ButtonEvent::PressedMod4()
{
	return e->state & Mod4Mask != 0;
}

bool ButtonEvent::PressedMod5()
{
	return e->state & Mod5Mask != 0;
}

bool ButtonEvent::SourceButton1()
{
	return e->button == Button1;
}

bool ButtonEvent::SourceButton2()
{
	return e->button == Button2;
}

bool ButtonEvent::SourceButton3()
{
	return e->button == Button3;
}

bool ButtonEvent::SourceButton4()
{
	return e->button == Button4;
}

bool ButtonEvent::SourceButton5()
{
	return e->button == Button5;
}


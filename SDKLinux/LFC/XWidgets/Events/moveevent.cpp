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
#include "moveevent.h"
#include "../../Time/datetime.h"
#include "../Graphics/npoint.h"

MoveEvent::MoveEvent(XMotionEvent *e)
{
	this->e = e;
}

MoveEvent::~MoveEvent()
{
}

DateTime MoveEvent::Time()
{
	return DateTime((time_t)e->time);
}

NPoint MoveEvent::Position()
{
	return NPoint(e->x, e->y);
}

NPoint MoveEvent::PositionRoot()
{
	return NPoint(e->x_root, e->y_root);
}

bool MoveEvent::PressedButton1()
{
	return e->state & Button1Mask != 0;
}

bool MoveEvent::PressedButton2()
{
	return e->state & Button2Mask != 0;
}

bool MoveEvent::PressedButton3()
{
	return e->state & Button3Mask != 0;
}

bool MoveEvent::PressedButton4()
{
	return e->state & Button4Mask != 0;
}

bool MoveEvent::PressedButton5()
{
	return e->state & Button5Mask != 0;
}

bool MoveEvent::PressedControl()
{
	return e->state & ControlMask != 0;
}

bool MoveEvent::PressedLock()
{
	return e->state & LockMask != 0;
}

bool MoveEvent::PressedShift()
{
	return e->state & ShiftMask != 0;
}

bool MoveEvent::PressedMod1()
{
	return e->state & Mod1Mask != 0;
}

bool MoveEvent::PressedMod2()
{
	return e->state & Mod2Mask != 0;
}

bool MoveEvent::PressedMod3()
{
	return e->state & Mod3Mask != 0;
}

bool MoveEvent::PressedMod4()
{
	return e->state & Mod4Mask != 0;
}

bool MoveEvent::PressedMod5()
{
	return e->state & Mod5Mask != 0;
}

bool MoveEvent::IsHint()
{
	return e->is_hint;
}
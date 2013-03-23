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
#include "keypressevent.h"
#include "../../Time/datetime.h"
#include "../../nwchar.h"
#include "../Graphics/npoint.h"

KeyPressEvent::KeyPressEvent(XKeyEvent *e)
{
	keyEvent = e;
}

KeyPressEvent::~KeyPressEvent()
{
}

DateTime KeyPressEvent::Time()
{
	return DateTime((time_t)keyEvent->time);
}

NWChar KeyPressEvent::KeyCode()
{
	return NWChar(keyEvent->keycode);
}

NPoint KeyPressEvent::Position()
{
	return NPoint(keyEvent->x, keyEvent->y);
}

NPoint KeyPressEvent::PositionRoot()
{
	return NPoint(keyEvent->x_root, keyEvent->y_root);
}

bool KeyPressEvent::PressedButton1()
{
	return keyEvent->state & Button1Mask != 0;
}

bool KeyPressEvent::PressedButton2()
{
	return keyEvent->state & Button2Mask != 0;
}

bool KeyPressEvent::PressedButton3()
{
	return keyEvent->state & Button3Mask != 0;
}

bool KeyPressEvent::PressedButton4()
{
	return keyEvent->state & Button4Mask != 0;
}

bool KeyPressEvent::PressedButton5()
{
	return keyEvent->state & Button5Mask != 0;
}

bool KeyPressEvent::PressedControl()
{
	return keyEvent->state & ControlMask != 0;
}

bool KeyPressEvent::PressedLock()
{
	return keyEvent->state & LockMask != 0;
}

bool KeyPressEvent::PressedShift()
{
	return keyEvent->state & ShiftMask != 0;
}

bool KeyPressEvent::PressedMod1()
{
	return keyEvent->state & Mod1Mask != 0;
}

bool KeyPressEvent::PressedMod2()
{
	return keyEvent->state & Mod2Mask != 0;
}

bool KeyPressEvent::PressedMod3()
{
	return keyEvent->state & Mod3Mask != 0;
}

bool KeyPressEvent::PressedMod4()
{
	return keyEvent->state & Mod4Mask != 0;
}

bool KeyPressEvent::PressedMod5()
{
	return keyEvent->state & Mod5Mask != 0;
}


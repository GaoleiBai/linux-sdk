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
#include "keyevent.h"
#include "../../Time/datetime.h"
#include "../../nwchar.h"
#include "../Graphics/npoint.h"

KeyEvent::KeyEvent(XKeyEvent *e)
{
	keyEvent = e;
}

KeyEvent::~KeyEvent()
{
}

DateTime KeyEvent::Time()
{
	return DateTime((time_t)keyEvent->time);
}

NWChar KeyEvent::KeyCode()
{
	return NWChar(keyEvent->keycode);
}

NPoint KeyEvent::Position()
{
	return NPoint(keyEvent->x, keyEvent->y);
}

NPoint KeyEvent::PositionRoot()
{
	return NPoint(keyEvent->x_root, keyEvent->y_root);
}

bool KeyEvent::PressedButton1()
{
	return keyEvent->state & Button1Mask != 0;
}

bool KeyEvent::PressedButton2()
{
	return keyEvent->state & Button2Mask != 0;
}

bool KeyEvent::PressedButton3()
{
	return keyEvent->state & Button3Mask != 0;
}

bool KeyEvent::PressedButton4()
{
	return keyEvent->state & Button4Mask != 0;
}

bool KeyEvent::PressedButton5()
{
	return keyEvent->state & Button5Mask != 0;
}

bool KeyEvent::PressedControl()
{
	return keyEvent->state & ControlMask != 0;
}

bool KeyEvent::PressedLock()
{
	return keyEvent->state & LockMask != 0;
}

bool KeyEvent::PressedShift()
{
	return keyEvent->state & ShiftMask != 0;
}

bool KeyEvent::PressedMod1()
{
	return keyEvent->state & Mod1Mask != 0;
}

bool KeyEvent::PressedMod2()
{
	return keyEvent->state & Mod2Mask != 0;
}

bool KeyEvent::PressedMod3()
{
	return keyEvent->state & Mod3Mask != 0;
}

bool KeyEvent::PressedMod4()
{
	return keyEvent->state & Mod4Mask != 0;
}

bool KeyEvent::PressedMod5()
{
	return keyEvent->state & Mod5Mask != 0;
}


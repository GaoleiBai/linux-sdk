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
#include "windoweventkey.h"
#include "../xexception.h"
#include "../../Time/datetime.h"
#include "../../Text/text.h"
#include "../../Devices/stdout.h"
#include "../../nwchar.h"
#include "../Graphics/npoint.h"
#include <X11/keysym.h>

WindowEventKey::WindowEventKey(XKeyEvent *e)
{
	keyEvent = e;
}

WindowEventKey::~WindowEventKey()
{
}

WindowEventKey &WindowEventKey::operator =(const WindowEventKey &e)
{
	keyEvent = e.keyEvent;
	return *this;
}

XKeyEvent *WindowEventKey::Handle()
{
	return keyEvent;
}

DateTime WindowEventKey::Time()
{
	return DateTime((time_t)keyEvent->time);
}

NPoint WindowEventKey::Position()
{
	return NPoint(keyEvent->x, keyEvent->y);
}

NPoint WindowEventKey::PositionRoot()
{
	return NPoint(keyEvent->x_root, keyEvent->y_root);
}

bool WindowEventKey::PressedButton1()
{
	return keyEvent->state & Button1Mask != 0;
}

bool WindowEventKey::PressedButton2()
{
	return keyEvent->state & Button2Mask != 0;
}

bool WindowEventKey::PressedButton3()
{
	return keyEvent->state & Button3Mask != 0;
}

bool WindowEventKey::PressedButton4()
{
	return keyEvent->state & Button4Mask != 0;
}

bool WindowEventKey::PressedButton5()
{
	return keyEvent->state & Button5Mask != 0;
}

bool WindowEventKey::PressedControl()
{
	return keyEvent->state & ControlMask != 0;
}

bool WindowEventKey::PressedLock()
{
	return keyEvent->state & LockMask != 0;
}

bool WindowEventKey::PressedShift()
{
	return keyEvent->state & ShiftMask != 0;
}

bool WindowEventKey::PressedMod1()
{
	return keyEvent->state & Mod1Mask != 0;
}

bool WindowEventKey::PressedMod2()
{
	return keyEvent->state & Mod2Mask != 0;
}

bool WindowEventKey::PressedMod3()
{
	return keyEvent->state & Mod3Mask != 0;
}

bool WindowEventKey::PressedMod4()
{
	return keyEvent->state & Mod4Mask != 0;
}

bool WindowEventKey::PressedMod5()
{
	return keyEvent->state & Mod5Mask != 0;
}


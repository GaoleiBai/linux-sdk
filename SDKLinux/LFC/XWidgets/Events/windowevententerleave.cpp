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
#include "windowevententerleave.h"
#include "../../Time/datetime.h"
#include "../Graphics/npoint.h"

WindowEventEnterLeave::WindowEventEnterLeave(XCrossingEvent *e)
{
	this->e = e;
}

WindowEventEnterLeave::~WindowEventEnterLeave()
{
}

DateTime WindowEventEnterLeave::Time()
{
	return DateTime((time_t)e->time);
}

NPoint WindowEventEnterLeave::Position()
{
	return NPoint(e->x, e->y);
}

NPoint WindowEventEnterLeave::PositionRoot()
{
	return NPoint(e->x_root, e->y_root);
}

bool WindowEventEnterLeave::PressedButton1()
{
	return e->state & Button1Mask != 0;
}

bool WindowEventEnterLeave::PressedButton2()
{
	return e->state & Button2Mask != 0;
}

bool WindowEventEnterLeave::PressedButton3()
{
	return e->state & Button3Mask != 0;
}

bool WindowEventEnterLeave::PressedButton4()
{
	return e->state & Button4Mask != 0;
}

bool WindowEventEnterLeave::PressedButton5()
{
	return e->state & Button5Mask != 0;
}

bool WindowEventEnterLeave::PressedControl()
{
	return e->state & ControlMask != 0;
}

bool WindowEventEnterLeave::PressedLock()
{
	return e->state & LockMask != 0;
}

bool WindowEventEnterLeave::PressedShift()
{
	return e->state & ShiftMask != 0;
}

bool WindowEventEnterLeave::PressedMod1()
{
	return e->state & Mod1Mask != 0;
}

bool WindowEventEnterLeave::PressedMod2()
{
	return e->state & Mod2Mask != 0;
}

bool WindowEventEnterLeave::PressedMod3()
{
	return e->state & Mod3Mask != 0;
}

bool WindowEventEnterLeave::PressedMod4()
{
	return e->state & Mod4Mask != 0;
}

bool WindowEventEnterLeave::PressedMod5()
{
	return e->state & Mod5Mask != 0;
}

int WindowEventEnterLeave::NotifyMode()
{
	if (e->mode == NotifyNormal) return NotifyModeNormal;
	else if (e->mode == NotifyGrab) return NotifyModeGrab;
	else if (e->mode == NotifyUngrab) return NotifyModeUngrab;
	else if (e->mode == NotifyWhileGrabbed) return NotifyModeWhileGrabbed;
	return -1;
}

int WindowEventEnterLeave::NotifyDetail()
{
	if (e->detail == NotifyAncestor) return NotifyDetailAncestor;
	else if (e->detail == NotifyVirtual) return NotifyDetailVirtual;
	else if (e->detail == NotifyInferior) return NotifyDetailInferior;
	else if (e->detail == NotifyNonlinear) return NotifyDetailNonLinear;
	else if (e->detail == NotifyNonlinearVirtual) return NotifyDetailNonlinearVirrual;
	else if (e->detail == NotifyPointer) return NotifyDetailPointer;
	else if (e->detail == NotifyPointerRoot) return NotifyDetailPointerRoot;
	else if (e->detail == NotifyDetailNone) return NotifyDetailNONE;
}

bool WindowEventEnterLeave::IsTheFocusWindow()
{
	return e->focus;
}


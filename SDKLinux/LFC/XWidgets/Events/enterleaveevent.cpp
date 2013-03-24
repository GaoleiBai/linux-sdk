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
#include "enterleaveevent.h"
#include "../../Time/datetime.h"
#include "../Graphics/npoint.h"

EnterLeaveEvent::EnterLeaveEvent(XCrossingEvent *e)
{
	this->e = e;
}

EnterLeaveEvent::~EnterLeaveEvent()
{
}

DateTime EnterLeaveEvent::Time()
{
	return DateTime((time_t)e->time);
}

NPoint EnterLeaveEvent::Position()
{
	return NPoint(e->x, e->y);
}

NPoint EnterLeaveEvent::PositionRoot()
{
	return NPoint(e->x_root, e->y_root);
}

bool EnterLeaveEvent::PressedButton1()
{
	return e->state & Button1Mask != 0;
}

bool EnterLeaveEvent::PressedButton2()
{
	return e->state & Button2Mask != 0;
}

bool EnterLeaveEvent::PressedButton3()
{
	return e->state & Button3Mask != 0;
}

bool EnterLeaveEvent::PressedButton4()
{
	return e->state & Button4Mask != 0;
}

bool EnterLeaveEvent::PressedButton5()
{
	return e->state & Button5Mask != 0;
}

bool EnterLeaveEvent::PressedControl()
{
	return e->state & ControlMask != 0;
}

bool EnterLeaveEvent::PressedLock()
{
	return e->state & LockMask != 0;
}

bool EnterLeaveEvent::PressedShift()
{
	return e->state & ShiftMask != 0;
}

bool EnterLeaveEvent::PressedMod1()
{
	return e->state & Mod1Mask != 0;
}

bool EnterLeaveEvent::PressedMod2()
{
	return e->state & Mod2Mask != 0;
}

bool EnterLeaveEvent::PressedMod3()
{
	return e->state & Mod3Mask != 0;
}

bool EnterLeaveEvent::PressedMod4()
{
	return e->state & Mod4Mask != 0;
}

bool EnterLeaveEvent::PressedMod5()
{
	return e->state & Mod5Mask != 0;
}

int EnterLeaveEvent::NotifyMode()
{
	if (e->mode == NotifyNormal) return NotifyModeNormal;
	else if (e->mode == NotifyGrab) return NotifyModeGrab;
	else if (e->mode == NotifyUngrab) return NotifyModeUngrab;
	else if (e->mode == NotifyWhileGrabbed) return NotifyModeWhileGrabbed;
	return -1;
}

int EnterLeaveEvent::NotifyDetail()
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

bool EnterLeaveEvent::IsTheFocusWindow()
{
	return e->focus;
}


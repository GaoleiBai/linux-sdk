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
#include "focusevent.h"
#include "../Graphics/npoint.h"
#include "../../Time/datetime.h"

FocusEvent::FocusEvent(XFocusChangeEvent *e)
{
	this->e = e;
}

FocusEvent::~FocusEvent()
{
}

int FocusEvent::NotifyMode()
{
	if (e->mode == NotifyNormal) return NotifyModeNormal;
	else if (e->mode == NotifyGrab) return NotifyModeGrab;
	else if (e->mode == NotifyUngrab) return NotifyModeUngrab;
	else if (e->mode == NotifyWhileGrabbed) return NotifyModeWhileGrabbed;
	return -1;
}

int FocusEvent::NotifyDetail()
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

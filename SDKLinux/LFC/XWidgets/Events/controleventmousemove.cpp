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
#include "controleventmousemove.h"
#include "windoweventmousemove.h"
#include "../../Time/datetime.h"
#include "../Graphics/npoint.h"

ControlEventMouseMove::ControlEventMouseMove(const WindowEventMouseMove &e)
{
	WindowEventMouseMove *ee = (WindowEventMouseMove *)&e;
	status = 0;
	if (ee->PressedButton1()) status |= StatusPressedButton1;
	if (ee->PressedButton2()) status |= StatusPressedButton2;
	if (ee->PressedButton3()) status |= StatusPressedButton3;
	if (ee->PressedButton4()) status |= StatusPressedButton4;
	if (ee->PressedButton5()) status |= StatusPressedButton5;
	if (ee->PressedControl()) status |= StatusPressedControl;
	if (ee->PressedLock()) status |= StatusPressedLock;
	if (ee->PressedShift()) status |= StatusPressedShift;
	if (ee->PressedMod1()) status |= StatusPressedMod1;
	if (ee->PressedMod2()) status |= StatusPressedMod2;
	if (ee->PressedMod3()) status |= StatusPressedMod3;
	if (ee->PressedMod4()) status |= StatusPressedMod4;
	if (ee->PressedMod5()) status |= StatusPressedMod5;
	
	time = new DateTime(ee->Time());
	position = new NPoint(ee->Position());
	positionRoot = new NPoint(ee->PositionRoot());
}

ControlEventMouseMove::ControlEventMouseMove(const ControlEventMouseMove &e, const NPoint &controlPosition)
{
	status = e.status;
	time = new DateTime(*e.time);
	position = new NPoint(*e.position - controlPosition);
	positionRoot = new NPoint(*e.positionRoot);
}

ControlEventMouseMove::~ControlEventMouseMove()
{
	delete time;
	delete position;
	delete positionRoot;
}

ControlEventMouseMove &ControlEventMouseMove::operator =(const ControlEventMouseMove &e)
{
	status = e.status;
	*time = *e.time;
	*position = *e.position;
	*positionRoot = *e.positionRoot;
	return *this;
}

DateTime ControlEventMouseMove::Time()
{
	return *time;
}

NPoint ControlEventMouseMove::Position()
{
	return *position;
}

NPoint ControlEventMouseMove::PositionRoot()
{
	return *positionRoot;
}

bool ControlEventMouseMove::PressedButton1()
{
	return status & StatusPressedButton1 != 0;
}

bool ControlEventMouseMove::PressedButton2()
{
	return status & StatusPressedButton2 != 0;
}

bool ControlEventMouseMove::PressedButton3()
{
	return status & StatusPressedButton3 != 0;
}

bool ControlEventMouseMove::PressedButton4()
{
	return status & StatusPressedButton4 != 0;
}

bool ControlEventMouseMove::PressedButton5()
{
	return status & StatusPressedButton5 != 0;
}

bool ControlEventMouseMove::PressedControl()
{
	return status & StatusPressedControl != 0;
}

bool ControlEventMouseMove::PressedLock()
{
	return status & StatusPressedLock != 0;
}

bool ControlEventMouseMove::PressedShift()
{
	return status & StatusPressedShift != 0;
}

bool ControlEventMouseMove::PressedMod1()
{
	return status & StatusPressedMod1 != 0;
}

bool ControlEventMouseMove::PressedMod2()
{
	return status & StatusPressedMod2 != 0;
}

bool ControlEventMouseMove::PressedMod3()
{
	return status & StatusPressedMod3 != 0;
}

bool ControlEventMouseMove::PressedMod4()
{
	return status & StatusPressedMod4 != 0;
}

bool ControlEventMouseMove::PressedMod5()
{
	return status & StatusPressedMod5 != 0;
}






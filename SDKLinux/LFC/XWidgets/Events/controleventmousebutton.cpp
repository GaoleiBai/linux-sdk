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
#include "controleventmousebutton.h"
#include "windoweventmousebutton.h"
#include "../../Time/datetime.h"
#include "../Graphics/npoint.h"
#include <typeinfo>

ControlEventMouseButton::ControlEventMouseButton(const WindowEventMouseButton &e)
{
	WindowEventMouseButton *ee = (WindowEventMouseButton *)&e;
	
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
	if (ee->SourceButton1()) status |= StatusSourceButton1;
	if (ee->SourceButton2()) status |= StatusSourceButton2;
	if (ee->SourceButton3()) status |= StatusSourceButton3;
	if (ee->SourceButton4()) status |= StatusSourceButton4;
	if (ee->SourceButton5()) status |= StatusSourceButton5;
	
	time = new DateTime(ee->Time());
	position = new NPoint(ee->Position());
	positionroot = new NPoint(ee->PositionRoot());
}

ControlEventMouseButton::ControlEventMouseButton(const ControlEventMouseButton &e, const NPoint &controlPosition)
{
	status = e.status;
	time = new DateTime(*e.time);
	position = new NPoint((*e.position) - controlPosition);
	positionroot = new NPoint(*e.positionroot);
}

ControlEventMouseButton::~ControlEventMouseButton()
{
	delete time;
	delete position;
	delete positionroot;
}

ControlEventMouseButton &ControlEventMouseButton::operator =(const ControlEventMouseButton &e)
{
	status = e.status;
	*time = *e.time;
	*position = *e.position;
	*positionroot = *e.positionroot;
}

DateTime ControlEventMouseButton::Time()
{
	return *time;
}

NPoint ControlEventMouseButton::Position()
{
	return *position;
}

NPoint ControlEventMouseButton::PositionRoot()
{
	return *positionroot;
}

bool ControlEventMouseButton::PressedButton1()
{
	return status & StatusPressedButton1 != 0;
}

bool ControlEventMouseButton::PressedButton2()
{
	return status & StatusPressedButton2 != 0;
}

bool ControlEventMouseButton::PressedButton3()
{
	return status & StatusPressedButton3 != 0;
}

bool ControlEventMouseButton::PressedButton4()
{
	return status & StatusPressedButton4 != 0;
}

bool ControlEventMouseButton::PressedButton5()
{
	return status & StatusPressedButton5 != 0;
}

bool ControlEventMouseButton::PressedControl()
{
	return status & StatusPressedControl != 0;
}

bool ControlEventMouseButton::PressedLock()
{
	return status & StatusPressedLock != 0;
}

bool ControlEventMouseButton::PressedShift()
{
	return status & StatusPressedShift != 0;
}

bool ControlEventMouseButton::PressedMod1()
{
	return status & StatusPressedMod1 != 0;
}

bool ControlEventMouseButton::PressedMod2()
{
	return status & StatusPressedMod2 != 0;
}

bool ControlEventMouseButton::PressedMod3()
{
	return status & StatusPressedMod3 != 0;
}

bool ControlEventMouseButton::PressedMod4()
{
	return status & StatusPressedMod4 != 0;
}

bool ControlEventMouseButton::PressedMod5()
{
	return status & StatusPressedMod5 != 0;
}

bool ControlEventMouseButton::SourceButton1()
{
	return status & StatusSourceButton1 != 0;
}

bool ControlEventMouseButton::SourceButton2()
{
	return status & StatusSourceButton2 != 0;
}

bool ControlEventMouseButton::SourceButton3()
{
	return status & StatusSourceButton3 != 0;
}

bool ControlEventMouseButton::SourceButton4()
{
	return status & StatusSourceButton4 != 0;
}

bool ControlEventMouseButton::SourceButton5()
{
	return status & StatusSourceButton5 != 0;
}

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
#include "controleventmouseclick.h"
#include "../Graphics/npoint.h"
#include "../../Time/datetime.h"
#include "controleventmousebutton.h"

ControlEventMouseClick::ControlEventMouseClick(const ControlEventMouseButton &e, const DateTime &clickduration)
{
	ControlEventMouseButton *ee = (ControlEventMouseButton *)&e;
	position = new NPoint(ee->Position());
	this->clickduration = new DateTime(clickduration);
	
	status = 0;
	if (ee->PressedButton1()) status |= StatusDoneWithButton1;
	if (ee->PressedButton2()) status |= StatusDoneWithButton2;
	if (ee->PressedButton3()) status |= StatusDoneWithButton3;
	if (ee->PressedButton4()) status |= StatusDoneWithButton4;
	if (ee->PressedButton5()) status |= StatusDoneWithButton5;
}

ControlEventMouseClick::~ControlEventMouseClick()
{
	delete position;
	delete clickduration;
}

NPoint ControlEventMouseClick::Position()
{
	return *position;
}

DateTime ControlEventMouseClick::ClickDuration()
{
	return *clickduration;
}

bool ControlEventMouseClick::DoneWithButton1()
{
	return status & StatusDoneWithButton1 != 0;
}

bool ControlEventMouseClick::DoneWithButton2()
{
	return status & StatusDoneWithButton2 != 0;
}

bool ControlEventMouseClick::DoneWithButton3()
{
	return status & StatusDoneWithButton3 != 0;
}

bool ControlEventMouseClick::DoneWithButton4()
{
	return status & StatusDoneWithButton4 != 0;
}

bool ControlEventMouseClick::DoneWithButton5()
{
	return status & StatusDoneWithButton5 != 0;
}


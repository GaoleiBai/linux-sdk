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
#include "controleventmousedoubleclick.h"
#include "../Graphics/npoint.h"
#include "../../Time/datetime.h"
#include "controleventmousebutton.h"

ControlEventMouseDoubleClick::ControlEventMouseDoubleClick(const ControlEventMouseButton &e, const DateTime &doubleclickduration)
{
	ControlEventMouseButton *ee = (ControlEventMouseButton *)&e;
	position = new NPoint(ee->Position());
	this->doubleclickduration = new DateTime(doubleclickduration);
	
	status = 0;
	if (ee->PressedButton1()) status |= StatusDoneWithButton1;
	if (ee->PressedButton2()) status |= StatusDoneWithButton2;
	if (ee->PressedButton3()) status |= StatusDoneWithButton3;
	if (ee->PressedButton4()) status |= StatusDoneWithButton4;
	if (ee->PressedButton5()) status |= StatusDoneWithButton4;
	
}

ControlEventMouseDoubleClick::~ControlEventMouseDoubleClick()
{
	delete position;
	delete doubleclickduration;
}

ControlEventMouseDoubleClick &ControlEventMouseDoubleClick::operator =(const ControlEventMouseDoubleClick &e)
{
	status = e.status;
	*position = *e.position;
	*doubleclickduration = *e.doubleclickduration;
	return *this;
}

NPoint ControlEventMouseDoubleClick::Position()
{
	return *position;
}

DateTime ControlEventMouseDoubleClick::DoubleClickDuration()
{
	return *doubleclickduration;
}

bool ControlEventMouseDoubleClick::DoneWithButton1()
{
	return status & StatusDoneWithButton1 != 0;
}

bool ControlEventMouseDoubleClick::DoneWithButton2()
{
	return status & StatusDoneWithButton2 != 0;
}

bool ControlEventMouseDoubleClick::DoneWithButton3()
{
	return status & StatusDoneWithButton3 != 0;
}

bool ControlEventMouseDoubleClick::DoneWithButton4()
{
	return status & StatusDoneWithButton4 != 0;
}

bool ControlEventMouseDoubleClick::DoneWithButton5()
{
	return status & StatusDoneWithButton5 != 0;
}


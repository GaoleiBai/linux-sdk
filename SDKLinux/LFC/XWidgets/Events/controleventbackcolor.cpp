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
#include "controleventbackcolor.h"

ControlEventBackColor::ControlEventBackColor(Control *source, const NColor &backcolor)
{
	this->source = source;
	this->backcolor = new NColor(backcolor);
}

ControlEventBackColor::ControlEventBackColor(const ControlEventBackColor &e)
{
	source = e.source;
	backcolor = e.backcolor;
}

ControlEventBackColor::~ControlEventBackColor()
{
	delete backcolor;
}

NColor ControlEventBackColor::BackColor()
{
	return *backcolor;
}

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
#ifndef CONTROLEVENTFONT_H
#define CONTROLEVENTFONT_H

#include "controlevent.h"

class NFont;

class ControlEventFont : public ControlEvent {
protected:
	NFont *font;

public:
	ControlEventFont(Control *source, const NFont &font);
	ControlEventFont(const ControlEventFont &e);
	virtual ~ControlEventFont();

	NFont Font();
	ControlEventFont &operator =(const ControlEventFont &e);
};

#endif // CONTROLEVENTFONT_H

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
#ifndef CONTROLEVENTMOUSECLICK_H
#define CONTROLEVENTMOUSECLICK_H

#include "controlevent.h"

class DateTime;
class NPoint;
class ControlEventMouseButton;

class ControlEventMouseClick : public ControlEvent {
	DateTime *clickduration;
	NPoint *position;
	int status;
	
public:
	static const int StatusDoneWithButton1 = 1;
	static const int StatusDoneWithButton2 = 2;
	static const int StatusDoneWithButton3 = 4;
	static const int StatusDoneWithButton4 = 8;
	static const int StatusDoneWithButton5 = 16;
	
	ControlEventMouseClick(const ControlEventMouseButton &e, const DateTime &clickduration);
	virtual ~ControlEventMouseClick();
	
	virtual ControlEventMouseClick &operator =(const ControlEventMouseClick &e);
	
	NPoint Position();
	DateTime ClickDuration();
	bool DoneWithButton1();
	bool DoneWithButton2();
	bool DoneWithButton3();
	bool DoneWithButton4();
	bool DoneWithButton5();	


};

#endif // CONTROLEVENTMOUSECLICK_H

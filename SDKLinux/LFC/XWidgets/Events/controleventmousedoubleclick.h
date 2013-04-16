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
#ifndef CONTROLEVENTMOUSEDOUBLECLICK_H
#define CONTROLEVENTMOUSEDOUBLECLICK_H

#include "controlevent.h"

class NPoint;
class DateTime;
class ControlEventMouseButton;

class ControlEventMouseDoubleClick : public ControlEvent {
	NPoint *position;
	DateTime *doubleclickduration;
	int status;
	
public:
	static const int StatusDoneWithButton1 = 1;
	static const int StatusDoneWithButton2 = 2;
	static const int StatusDoneWithButton3 = 4;
	static const int StatusDoneWithButton4 = 8;
	static const int StatusDoneWithButton5 = 16;	

	ControlEventMouseDoubleClick(const ControlEventMouseButton &e, const DateTime &doubleclickduration);
	virtual ~ControlEventMouseDoubleClick();
	
	virtual ControlEventMouseDoubleClick &operator =(const ControlEventMouseDoubleClick &e);

	NPoint Position();
	DateTime DoubleClickDuration();
	bool DoneWithButton1();
	bool DoneWithButton2();
	bool DoneWithButton3();
	bool DoneWithButton4();
	bool DoneWithButton5();

};

#endif // CONTROLEVENTMOUSEDOUBLECLICK_H

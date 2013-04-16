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
#ifndef CONTROLEVENTMOUSEBUTTON_H
#define CONTROLEVENTMOUSEBUTTON_H

#include "controlevent.h"

class WindowEventMouseButton;
class DateTime;
class NPoint;

class ControlEventMouseButton : public ControlEvent {
protected:
	
	int status;
	DateTime *time;
	NPoint *position;
	NPoint *positionroot;
	
public:
	static const int StatusPressedButton1 = 1;
	static const int StatusPressedButton2 = 2;
	static const int StatusPressedButton3 = 4;
	static const int StatusPressedButton4 = 8;
	static const int StatusPressedButton5 = 16;
	static const int StatusPressedControl = 32;
	static const int StatusPressedLock = 64;
	static const int StatusPressedShift = 128;
	static const int StatusPressedMod1 = 256;
	static const int StatusPressedMod2 = 512;
	static const int StatusPressedMod3 = 1024;
	static const int StatusPressedMod4 = 2048;
	static const int StatusPressedMod5 = 4096;
	static const int StatusSourceButton1 = 8192;
	static const int StatusSourceButton2 = 16384;
	static const int StatusSourceButton3 = 32768;
	static const int StatusSourceButton4 = 65536;
	static const int StatusSourceButton5 = 131072;

	ControlEventMouseButton(const WindowEventMouseButton &e);
	ControlEventMouseButton(const ControlEventMouseButton &e, const NPoint &controlPosition);
	virtual ~ControlEventMouseButton();
	
	virtual ControlEventMouseButton &operator =(const ControlEventMouseButton &e);

	DateTime Time();
	NPoint Position();
	NPoint PositionRoot();
	
	bool PressedButton1();
	bool PressedButton2();
	bool PressedButton3();
	bool PressedButton4();
	bool PressedButton5();
	bool PressedShift();
	bool PressedLock();
	bool PressedControl();
	bool PressedMod1();
	bool PressedMod2();
	bool PressedMod3();
	bool PressedMod4();
	bool PressedMod5();
	
	bool SourceButton1();
	bool SourceButton2();
	bool SourceButton3();
	bool SourceButton4();
	bool SourceButton5();
	
};

#endif // CONTROLEVENTMOUSEBUTTON_H

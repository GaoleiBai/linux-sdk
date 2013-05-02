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
#ifndef CONTROLEVENTKEY_H
#define CONTROLEVENTKEY_H

#include "controlevent.h"
#include <X11/XKBlib.h>

class WindowEventKey;
class DateTime;
class NWChar;
class NPoint;
class KeyCompositionSymbol;

class ControlEventKey : public ControlEvent {
protected:
	int status;
	DateTime *time;
	NPoint *position;
	NPoint *positionRoot;
	KeyCompositionSymbol *symbol;
	
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

	ControlEventKey(const WindowEventKey &e, const KeyCompositionSymbol &s);
	virtual ~ControlEventKey();
	
	DateTime Time();
	NPoint Position();
	NPoint PositionRoot();
	KeyCompositionSymbol Symbol();
	
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
	
	ControlEventKey &operator =(const ControlEventKey &e);

};

#endif // CONTROLEVENTKEY_H

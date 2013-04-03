#ifndef CONTROLEVENTMOUSEMOVE_H
#define CONTROLEVENTMOUSEMOVE_H

#include "controlevent.h"

class WindowEventMouseMove;
class NPoint;
class DateTime;

class ControlEventMouseMove : public ControlEvent {
protected:
	int status;
	DateTime *time;
	NPoint *position;
	NPoint *positionroot;
	
	static const int StatusPressedButton1 = 1;
	static const int StatusPressedButton2 = 2;
	static const int StatusPressedButton3 = 4;
	static const int StatusPressedButton4 = 8;
	static const int StatusPressedButton5 = 16;
	static const int StatusPressedShift = 32;
	static const int StatusPressedLock = 64;
	static const int StatusPressedControl = 128;
	static const int StatusPressedMod1 = 256;
	static const int StatusPressedMod2 = 512;
	static const int StatusPressedMod3 = 1024;
	static const int StatusPressedMod4 = 2048;
	static const int StatusPressedMod5 = 4096;	
	
public:
	ControlEventMouseMove(const WindowEventMouseMove &e);
	virtual ~ControlEventMouseMove();
	
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

};

#endif // CONTROLEVENTMOUSEMOVE_H

#include "controleventkey.h"
#include "../Graphics/npoint.h"
#include "../../nwchar.h"
#include "../../Time/datetime.h"

ControlEventKey::ControlEventKey(const KeyEvent &e)
{
	KeyEvent *ee = (KeyEvent *)&e;
	
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
	
	time = new DateTime(ee->Time());
	position = new NPoint(ee->Position());
	positionRoot = new NPoint(ee->PositionRoot());
	keycode = new NWChar(ee->KeyCode());
}

ControlEventKey::~ControlEventKey()
{
	delete time;
	delete position;
	delete positionRoot;
	delete keycode;
}

DateTime ControlEventKey::Time()
{
	return *time;
}

NPoint ControlEventKey::Position()
{
	return *position;
}

NPoint ControlEventKey::PositionRoot()
{
	return *positionRoot;
}

NWChar ControlEventKey::KeyCode()
{
	return *keycode;
}

bool ControlEventKey::PressedButton1()
{
	return status & StatusPressedButton1;
}

bool ControlEventKey::PressedButton2()
{
	return status & StatusPressedButton2;
}

bool ControlEventKey::PressedButton3()
{
	return status & StatusPressedButton3;
}

bool ControlEventKey::PressedButton4()
{
	return status & StatusPressedButton4;
}

bool ControlEventKey::PressedButton5()
{
	return status & StatusPressedButton5;
}

bool ControlEventKey::PressedControl()
{
	return status & StatusPressedControl;
}

bool ControlEventKey::PressedLock()
{
	return status & StatusPressedLock;
}

bool ControlEventKey::PressedShift()
{
	return status & StatusPressedShift;
}

bool ControlEventKey::PressedMod1()
{
	return status & StatusPressedMod1;
}

bool ControlEventKey::PressedMod2()
{
	return status & StatusPressedMod2;
}

bool ControlEventKey::PressedMod3()
{
	return status & StatusPressedMod3;
}

bool ControlEventKey::PressedMod4()
{
	return status & StatusPressedMod4;
}

bool ControlEventKey::PressedMod5()
{
	return status & StatusPressedMod5;
}


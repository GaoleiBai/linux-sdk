#include "controleventmousemove.h"
#include "windoweventmousemove.h"
#include "../../Time/datetime.h"
#include "../Graphics/npoint.h"

ControlEventMouseMove::ControlEventMouseMove(const WindowEventMouseMove &e)
{
	WindowEventMouseMove *ee = (WindowEventMouseMove *)&e;
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
}

ControlEventMouseMove::ControlEventMouseMove(const ControlEventMouseMove &e, const NPoint &parentposition)
{
	status = e.status;
	time = new DateTime(*time);
	NPoint *pp = (NPoint *)&parentposition;
	position = new NPoint(e.position->GetX() - pp->GetX(), e.position->GetY() - pp->GetY());
	positionroot = new NPoint(*e.positionroot);
}

ControlEventMouseMove::~ControlEventMouseMove()
{
	delete time;
	delete position;
	delete positionroot;
}

DateTime ControlEventMouseMove::Time()
{
	return *time;
}

NPoint ControlEventMouseMove::Position()
{
	return *position;
}

NPoint ControlEventMouseMove::PositionRoot()
{
	return *positionroot;
}

bool ControlEventMouseMove::PressedButton1()
{
	return status & StatusPressedButton1 != 0;
}

bool ControlEventMouseMove::PressedButton2()
{
	return status & StatusPressedButton2 != 0;
}

bool ControlEventMouseMove::PressedButton3()
{
	return status & StatusPressedButton3 != 0;
}

bool ControlEventMouseMove::PressedButton4()
{
	return status & StatusPressedButton4 != 0;
}

bool ControlEventMouseMove::PressedButton5()
{
	return status & StatusPressedButton5 != 0;
}

bool ControlEventMouseMove::PressedControl()
{
	return status & StatusPressedControl != 0;
}

bool ControlEventMouseMove::PressedLock()
{
	return status & StatusPressedLock != 0;
}

bool ControlEventMouseMove::PressedShift()
{
	return status & StatusPressedShift != 0;
}

bool ControlEventMouseMove::PressedMod1()
{
	return status & StatusPressedMod1 != 0;
}

bool ControlEventMouseMove::PressedMod2()
{
	return status & StatusPressedMod2 != 0;
}

bool ControlEventMouseMove::PressedMod3()
{
	return status & StatusPressedMod3 != 0;
}

bool ControlEventMouseMove::PressedMod4()
{
	return status & StatusPressedMod4 != 0;
}

bool ControlEventMouseMove::PressedMod5()
{
	return status & StatusPressedMod5 != 0;
}






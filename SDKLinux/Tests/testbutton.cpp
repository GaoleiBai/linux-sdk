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
#include "testbutton.h"

TestButton::TestButton()
{
}

TestButton::~TestButton()
{
}

int TestButton::Perform()
{
	class VentanaInicio : public XWindow {
		ControlButton *buttonClose;
		ControlButton *buttonTest1;
	protected:
		virtual void Prepare() {
			buttonClose = new ControlButton("Close", NPoint(10, 10));
			buttonTest1 = new ControlButton("Test 1", NRectangle(10, 30, 50, 20));
			buttonTest1->DelegationOnAction() += NDelegation(this, (Delegate)&VentanaInicio::OnAction_ButtonTest1);
			ControlAdd(buttonClose);
			ControlAdd(buttonTest1);
		}
		
		virtual void Destroy() {
			ControlRemove(buttonClose);
			ControlRemove(buttonTest1);
			delete buttonClose;
			delete buttonTest1;
		}
		
		void *OnAction_ButtonTest1(ControlEventAction *e)
		{
			NPoint p = buttonTest1->GetPosition();
			buttonTest1->SetPosition(p + NPoint(10, 10));
		}
		
	public:
		VentanaInicio(const XDisplay &d) : XWindow(d) {}
		
	};
	
	XDisplay d;
	VentanaInicio v(d);
	v.RunModal();
	
	return 0;
}


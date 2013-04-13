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
#include "testcontrollabel.h"
#include "../LFC/LFC.h"

TestControlLabel::TestControlLabel()
{
}

TestControlLabel::~TestControlLabel()
{
}

int TestControlLabel::Perform()
{
	class VentanaInicio : public XWindow {
	protected:
		ControlLabel *tagTest;
		
	public:
		VentanaInicio(const XDisplay &d) : XWindow(d) { }
		
		virtual void Prepare() {
			tagTest = new ControlLabel("Hola LFC");
			ControlAdd(tagTest);
			tagTest->SetPosition(NPoint(10, 10));
			tagTest->SetVisible(true);
			
			DelegationOnDraw() += NDelegation(this, (Delegate)&VentanaInicio::CustomDraw);
		}
		
		virtual void Dispose() {
			ControlRemove(tagTest);
			delete tagTest;
		}
		
		virtual void *CustomDraw(WindowEventDraw *e) {
			e->Graphics().SetColor(1.0, 0, 0, 1.0);
			e->Graphics().DrawLine(0, 0, 100, 100);
		}
	};
	
	XDisplay d;
	VentanaInicio w(d);
	w.RunModal();
	
	return 0;
}


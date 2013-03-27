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
#include "testwindow.h"
#include "../LFC/LFC.h"

TestWindow::TestWindow()
{
}

TestWindow::~TestWindow()
{
}

int TestWindow::Perform()
{
	try {
		class VentanaInicio : public XWindow {
		public:
			VentanaInicio(const XDisplay &d) : XWindow(d) { }
			virtual void OnDraw(DrawEvent *e) {
				e->Graphics().ClipRegionSet(50, 50, 50, 50);
				e->Graphics().SetLineWidth(1);
				e->Graphics().SetColor(1.0, 0, 0, 1.0);
				e->Graphics().DrawLine(0, 0, 100, 100);
				e->Graphics().SetColor(0, 1.0, 0, 0.5);
				e->Graphics().DrawRectangle(75, 75, 12, 12);
			}
		};
		
		XDisplay d;
		VentanaInicio w(d);
		w.RunModal();
		
	} catch (Exception *e) {
		delete e;
		return -1;
	}
	return 0;
}


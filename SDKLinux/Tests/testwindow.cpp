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
		protected:
			virtual void Prepare() {
				DelegationOnWindowDraw() += NDelegation(this, (Delegate)&VentanaInicio::OnDraw);
			}
			
			
		public:
			VentanaInicio(const XDisplay &d) : XWindow(d) { }
			
			void *OnDraw(WindowEventDraw *e) {
				e->Graphics().ClipRegionSet(50, 50, 50, 50);
				e->Graphics().SetLineWidth(1);
				e->Graphics().SetColor(1.0, 0, 0, 1.0);
				e->Graphics().DrawLine(0, 0, 100, 100);
				e->Graphics().SetColor(0, 1.0, 0, 0.5);
				e->Graphics().DrawRectangle(75, 75, 12, 12);
				
				e->Graphics().SetColor(0, 0, 1.0, 0.5);
				e->Graphics().ClipRegionReset();
				e->Graphics().DrawEllipse(25, 25, 100, 50);
				e->Graphics().DrawRectangle(25, 25, 100, 50);
				e->Graphics().DrawEllipse(50, 10, 50, 100);
				e->Graphics().DrawRectangle(50, 10, 50, 100);
				
				e->Graphics().SetColor(0.5, 0.5, 0.5, 0.5);
				e->Graphics().FillEllipse(200, 10, 100, 20);
				e->Graphics().FillRectangle(200, 40, 100, 20);
				
				e->Graphics().FillArc(200, 70, 100, 100, Math::PI / 2, Math::PI);
				e->Graphics().SetLineCap(IGraphics::LineCapRound);
				e->Graphics().SetLineWidth(4);
				e->Graphics().SetColor(0.5, 0, 0, 0.5);
				e->Graphics().DrawArc(200, 70, 100, 100, Math::PI / 2, Math::PI);
				
				e->Graphics().WriteToPng("test.png");
				ImageGraphics imgg(e->Graphics());
				imgg.WriteToPng("test2.png");
				
				Text hm = "Hola mundo2";
				NFont f("Ubuntu Mono", NFont::FontWeightNormal, 8);
				NSize shm = e->Graphics().GetTextExtents(hm, f);
				e->Graphics().SetLineWidth(1);
				e->Graphics().DrawText(hm, 10, 110, f);
				e->Graphics().DrawLine(10, 112 + shm.GetHeight(), 10 + shm.GetWidth(), 112 + shm.GetHeight());
				e->Graphics().DrawLine(12 + shm.GetWidth(), 112, 12 + shm.GetWidth(), 112 + shm.GetHeight());
				
				GraphicsPatternLinear pl(NPoint(10, 130), NPoint(10, 170));
				pl.AddColorAtDistance(NColor(0.8, 0.8, 0.85, 1), 0);
				pl.AddColorAtDistance(NColor(0.7, 0.7, 0.75, 1), 40);
				e->Graphics().SetPattern(pl);
				e->Graphics().FillRoundRectangle(10, 130, 50, 40, 3);
				
				e->Graphics().SetColor(NColor(0.7, 0.7, 0.7, 1));
				e->Graphics().DrawRoundRectangle(10, 130, 50, 40, 3);
				/*
				Collection<Text *> families = NFont::GetAvaliableFamilies();
				for (int i=0; i<families.Count(); i++)
					StdOut::PrintLine(*families[i]);
				families.DeleteAndClear();
				*/
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


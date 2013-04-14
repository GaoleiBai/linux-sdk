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
#ifndef CONTROLLABEL_H
#define CONTROLLABEL_H

#include "control.h"

class ControlLabel : public Control {
protected:
	Text *text;
	NColor *textcolor;
	
	bool autosize;
	bool updateAreaOnInit;
	
public:
	ControlLabel(const Text &text);
	ControlLabel(const Text &text, const NPoint &position);
	ControlLabel(const Text &text, const NRectangle &area);
	virtual ~ControlLabel();

	void SetText(const Text &text);
	Text GetText();
	void SetTextColor(const NColor &c);
	NColor GetTextColor();
	void SetAutoSize(bool autosize);
	bool GetAutoSize();
	
	virtual void SetFont(const NFont &font);
	virtual void SetArea(const NRectangle &area);

	virtual void Init(XWindow *w, Control *parent);
	virtual bool OnDrawBackground(IGraphics *gc, NRectangle *r);
	virtual bool OnDraw(IGraphics *gc, NRectangle *r);
	
};

#endif // CONTROLLABEL_H

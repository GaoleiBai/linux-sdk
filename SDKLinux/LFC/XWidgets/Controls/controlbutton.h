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
#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include "control.h"

class Text;
class NColor;
class NPoint;
class NRectangle;
class ControlEventAction;

class ControlButton : public Control {
protected:
	Text *text;
	NColor *textcolor;
	NColor *forecolor;
	bool autosize;
	bool calculateAreaOnInit;
	bool isMouseOver;
	bool isPressed;
	NDelegationManager *onAction;
	
	void UpdateSize();
	bool OnAction(ControlEventAction *e);

public:
	ControlButton(const Text &t);
	ControlButton(const Text &t, const NPoint &p);
	ControlButton(const Text &t, const NRectangle &r);
	virtual ~ControlButton();

	bool GetAutoSize();
	Text GetText();
	NColor GetTextColor();
	NColor GetForeColor();
	void SetAutoSize(bool autosize);
	void SetText(const Text &t);
	void SetTextColor(const NColor &c);
	void SetForeColor(const NColor &c);
	
	virtual void SetFont(const NFont &f);
	virtual void SetArea(const NRectangle &r);
	
	virtual bool IsFocusable();
	virtual bool CaptureSpaceKey();
	virtual bool CaptureEnterKey();
	
	virtual void Init(XWindow *w, Control *parent);
	virtual bool OnDrawBackground(IGraphics *g, NRectangle *r);
	virtual bool OnDraw(IGraphics *g, NRectangle *r);
	virtual bool OnMouseButtonDown(ControlEventMouseButton *e);
	virtual bool OnMouseButtonUp(ControlEventMouseButton *e);
	virtual bool OnMouseMove(ControlEventMouseMove *e);
	virtual bool OnKeyPress(ControlEventKey *e);
	virtual bool OnKeyRelease(ControlEventKey *e);
	
	NDelegationManager &DelegationOnAction();	// Arg: ControlEventAction *
	
};

#endif // CONTROLBUTTON_H

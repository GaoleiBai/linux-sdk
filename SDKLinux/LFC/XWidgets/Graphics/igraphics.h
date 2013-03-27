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
#ifndef IGRAPHICS_H
#define IGRAPHICS_H

#include "nrectangle.h"
#include "ncolor.h"
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

class IGraphics : public NObject {
	
protected:
	cairo_surface_t *surface;
	cairo_t *gc;
	
public:
	IGraphics();
	
	cairo_t *Handle();
	cairo_surface_t *HandleSurface();

	static const int AntialiasModeDefault = CAIRO_ANTIALIAS_DEFAULT;
	static const int AntialiasModeNone = CAIRO_ANTIALIAS_NONE;
	static const int AntialiasModeGray = CAIRO_ANTIALIAS_GRAY;
	static const int AntialiasModeSubpixel = CAIRO_ANTIALIAS_SUBPIXEL;
	
	static const int LineCapNone = CAIRO_LINE_CAP_BUTT;
	static const int LineCapRound = CAIRO_LINE_CAP_ROUND;
	static const int LineCapSquare = CAIRO_LINE_CAP_SQUARE;
	
	static const int LineJointNone = CAIRO_LINE_JOIN_MITER;
	static const int LineJointRound = CAIRO_LINE_CAP_ROUND;
	static const int LineJointBebel = CAIRO_LINE_JOIN_BEVEL;

	void SetAntialiasMode(int mode);
	int GetAntialiasMode();
	void SetLineCap(int cap);
	int GetLineCap();
	void SetLineJoint(int joint);
	int GetLineJoint();
	void SetLineWidth(double width);
	int GetLineWidth();
	NRectangle ClipRegionGetCurrent();
	bool ClipRegionIsIn(int x, int y);
	void ClipRegionReset();
	void ClipRegionSet(int x, int y, int width, int height);
	void ClipRegionSet(const NRectangle &r);
	void SetStrokeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void SetStrokeColor(double r, double g, double b, double a);
	void SetStrokeColor(const NColor &c);

	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawRectangle(int x, int y, int width, int height);
	void DrawRectangle(const NRectangle &r);

};

#endif // IGRAPHICS_H

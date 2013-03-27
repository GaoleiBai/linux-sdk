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
#include "igraphics.h"
#include "../xexception.h"
#include "../../Text/text.h"

IGraphics::IGraphics()
{
	surface = NULL;
	gc = NULL;
}

cairo_t *IGraphics::Handle()
{
	return gc;
}

cairo_surface_t *IGraphics::HandleSurface()
{
	return surface;
}

void IGraphics::SetAntialiasMode(int mode)
{
	cairo_set_antialias(gc, (cairo_antialias_t)mode);
	XException::CheckCairo(gc);
}

int IGraphics::GetAntialiasMode()
{
	cairo_get_antialias(gc);
}

void IGraphics::SetLineCap(int cap)
{
	cairo_set_line_cap(gc, (cairo_line_cap_t)cap);
	XException::CheckCairo(gc);
}

int IGraphics::GetLineCap()
{
	return cairo_get_line_cap(gc);
}

void IGraphics::SetLineJoint(int joint)
{
	cairo_set_line_join(gc, (cairo_line_join_t)joint);
	XException::CheckCairo(gc);
}

int IGraphics::GetLineJoint()
{
	return cairo_get_line_join(gc);
}

void IGraphics::SetLineWidth(double width)
{
	cairo_set_line_width(gc, width);
	XException::CheckCairo(gc);
}

int IGraphics::GetLineWidth()
{
	return cairo_get_line_width(gc);
}

NRectangle IGraphics::ClipRegionGetCurrent()
{
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	cairo_clip_extents(gc, &x1, &y1, &x2, &y2);
	return NRectangle(x1, y1, x2 - x1, y2 - y1);
}

bool IGraphics::ClipRegionIsIn(int x, int y)
{
	return cairo_in_clip(gc, x, y);
}

void IGraphics::ClipRegionReset()
{
	cairo_reset_clip(gc);
}

void IGraphics::ClipRegionSet(int x, int y, int width, int height)
{
	cairo_new_path(gc);
	cairo_rectangle(gc, x, y, width, height);
	cairo_clip(gc);
	//cairo_close_path(g);
}

void IGraphics::ClipRegionSet(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	cairo_new_path(gc);
	cairo_rectangle(gc, rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
	cairo_clip(gc);
	//cairo_close_path(g);
}

void IGraphics::SetStrokeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	cairo_set_source_rgba(gc, r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}

void IGraphics::SetStrokeColor(double r, double g, double b, double a)
{
	cairo_set_source_rgba(gc, r, g, b, a);
}

void IGraphics::SetStrokeColor(const NColor &c)
{
	NColor *cc = (NColor *)&c;
	cairo_set_source_rgba(gc, cc->R(), cc->G(), cc->B(), cc->A());
}

void IGraphics::DrawLine(int x1, int y1, int x2, int y2)
{
	cairo_move_to(gc, x1, y1);
	cairo_line_to(gc, x2, y2);
	cairo_stroke(gc);
}

void IGraphics::DrawRectangle(int x, int y, int width, int height)
{
	cairo_new_path(gc);
	cairo_rectangle(gc, x, y, width, height);
	cairo_close_path(gc);
}

void IGraphics::DrawRectangle(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	cairo_new_path(gc);
	cairo_rectangle(gc, rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
	cairo_close_path(gc);
}

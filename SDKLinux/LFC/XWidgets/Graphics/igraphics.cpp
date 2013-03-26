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
	throw new XException((Text)"This class cannot be instanciated. Please use XWindowGraphics or any other that inherit from this :)", __FILE__, __LINE__, __func__);
}

cairo_t *IGraphics::Handle()
{
	return g;
}

cairo_surface_t *IGraphics::HandleSurface()
{
	return surface;
}

void IGraphics::SetAntialiasMode(int mode)
{
	cairo_set_antialias(g, (cairo_antialias_t)mode);
	XException::CheckCairo(g);
}

int IGraphics::GetAntialiasMode()
{
	cairo_get_antialias(g);
}

void IGraphics::SetLineCap(int cap)
{
	cairo_set_line_cap(g, (cairo_line_cap_t)cap);
	XException::CheckCairo(g);
}

int IGraphics::GetLineCap()
{
	return cairo_get_line_cap(g);
}

void IGraphics::SetLineJoint(int joint)
{
	cairo_set_line_join(g, (cairo_line_join_t)joint);
	XException::CheckCairo(g);
}

int IGraphics::GetLineJoint()
{
	return cairo_get_line_join(g);
}

void IGraphics::SetLineWidth(double width)
{
	cairo_set_line_width(g, width);
	XException::CheckCairo(g);
}

int IGraphics::GetLineWidth()
{
	return cairo_get_line_width(g);
}

NRectangle IGraphics::ClipRegionGetCurrent()
{
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	cairo_clip_extents(g, &x1, &y1, &x2, &y2);
	return NRectangle(x1, y1, x2 - x1, y2 - y1);
}

bool IGraphics::ClipRegionIsIn(int x, int y)
{
	return cairo_in_clip(g, x, y);
}

void IGraphics::ClipRegionReset()
{
	cairo_reset_clip(g);
}

void IGraphics::ClipRegionSet(int x, int y, int width, int height)
{
	cairo_new_path(g);
	cairo_rectangle(g, x, y, width, height);
	cairo_clip(g);
	//cairo_close_path(g);
}

void IGraphics::ClipRegionSet(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	cairo_new_path(g);
	cairo_rectangle(g, rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
	cairo_clip(g);
	//cairo_close_path(g);
}

void IGraphics::DrawLine(int x1, int y1, int x2, int y2)
{
	cairo_new_path(g);
	cairo_move_to(g, x1, y1);
	cairo_line_to(g, x1, y1);
	cairo_close_path(g);
}

void IGraphics::DrawRectangle(int x, int y, int width, int height)
{
	cairo_new_path(g);
	cairo_rectangle(g, x, y, width, height);
	cairo_close_path(g);
}

void IGraphics::DrawRectangle(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	cairo_new_path(g);
	cairo_rectangle(g, rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
	cairo_close_path(g);
}

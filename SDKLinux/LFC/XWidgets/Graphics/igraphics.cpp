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
#include "npoint.h"
#include "nfont.h"
#include "../xexception.h"
#include "../../Text/text.h"
#include "../../Math/math.h"

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

void IGraphics::WriteToPng(const Text &filename)
{
	char fn[10000];
	((Text *)&filename)->GetAnsiString(fn, 10000);
	
	cairo_surface_write_to_png(surface, fn);
	XException::CheckCairo(gc);
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
	cairo_rectangle(gc, x, y, width, height);
	cairo_clip(gc);
}

void IGraphics::ClipRegionSet(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	cairo_rectangle(gc, rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
	cairo_clip(gc);
}

void IGraphics::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	cairo_set_source_rgba(gc, r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}

void IGraphics::SetColor(double r, double g, double b, double a)
{
	cairo_set_source_rgba(gc, r, g, b, a);
}

void IGraphics::SetColor(const NColor &c)
{
	NColor *cc = (NColor *)&c;
	cairo_set_source_rgba(gc, cc->R(), cc->G(), cc->B(), cc->A());
}

void IGraphics::SetPattern(const GraphicsPattern &p)
{
	GraphicsPattern *pp = (GraphicsPattern *)&p;
	cairo_set_source(gc, pp->Handle());
	XException::CheckCairo(gc);
}

void IGraphics::Clear(const NColor &color)
{
	ClipRegionReset();
	SetColor(color);
	cairo_paint(gc);
}

void IGraphics::DrawLine(int x1, int y1, int x2, int y2)
{
	cairo_move_to(gc, x1 - 0.5, y1 - 0.5);
	cairo_line_to(gc, x2 - 0.5, y2 - 0.5);
	cairo_stroke(gc);
}

void IGraphics::DrawRectangle(int x, int y, int width, int height)
{
	cairo_rectangle(gc, x - 0.5, y - 0.5, width, height);
	cairo_stroke(gc);
}

void IGraphics::DrawRectangle(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	DrawRectangle(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
}

void IGraphics::FillRectangle(int x, int y, int width, int height)
{
	cairo_rectangle(gc, x - 0.5, y - 0.5, width, height);
	cairo_fill(gc);
}

void IGraphics::FillRectangle(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	FillRectangle(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
}

void IGraphics::DrawRoundRectangle(int x, int y, int width, int height, int roundradius)
{
	double xx = x - 0.5;
	double yy = y - 0.5;
	int rr = roundradius;
	if (rr > height / 2) rr = height / 2;
	if (rr > width / 2) rr = width / 2;
	
	cairo_new_path(gc);
	cairo_arc(gc, xx + rr, yy + rr, rr, -1 * Math::PI, -1 * Math::PI / 2);
	cairo_arc(gc, xx + width - rr, yy + rr, rr, -1 * Math::PI / 2, 0);
	cairo_arc(gc, xx + width - rr, yy + height - rr, rr, 0, Math::PI / 2);
	cairo_arc(gc, xx + rr, yy + height - rr, rr, Math::PI / 2, Math::PI);
	cairo_close_path(gc);
	cairo_stroke(gc);
}

void IGraphics::DrawRoundRectangle(const NRectangle &r, int roundradius)
{
	NRectangle *rr = (NRectangle *)&r;
	DrawRoundRectangle(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight(), roundradius);
}

void IGraphics::FillRoundRectangle(int x, int y, int width, int height, int roundradius)
{
	int rr = roundradius;
	if (rr > height / 2) rr = height / 2;
	if (rr > width / 2) rr = width / 2;
	
	cairo_arc(gc, x + rr, y + rr, rr, -1 * Math::PI, -1 * Math::PI / 2);
	cairo_arc(gc, x + width - rr, y + rr, rr, -1 * Math::PI / 2, 0);
	cairo_arc(gc, x + width - rr, y + height - rr, rr, 0, Math::PI / 2);
	cairo_arc(gc, x + rr, y + height - rr, rr, Math::PI / 2, Math::PI);
	cairo_fill(gc);
}

void IGraphics::FillRoundRectangle(const NRectangle &r, int roundradius)
{
	NRectangle *rr = (NRectangle *)&r;
	FillRoundRectangle(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight(), roundradius);
}

void IGraphics::DrawEllipse(int x, int y, int width, int height)
{
	cairo_save(gc);
	cairo_translate(gc, x + width / 2, y + height / 2);
	cairo_scale(gc, 1.0, 1.0 * height / width);
	cairo_arc(gc, -0.5, -0.5, width / 2, 0, 2 * Math::PI);
	cairo_stroke(gc);
	cairo_restore(gc);
}

void IGraphics::DrawEllipse(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	DrawEllipse(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
}

void IGraphics::FillEllipse(int x, int y, int width, int height)
{
	cairo_save(gc);
	cairo_translate(gc, x + width / 2, y + height / 2);
	cairo_scale(gc, 1.0, 1.0 * height / width);
	cairo_arc(gc, -0.5, -0.5, width / 2, 0, 2 * Math::PI);
	cairo_fill(gc);
	cairo_restore(gc);
}

void IGraphics::FillEllipse(const NRectangle &r)
{
	NRectangle *rr = (NRectangle *)&r;
	FillEllipse(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight());
}

void IGraphics::DrawArc(int x, int y, int width, int height, double startangle, double endangle)
{
	cairo_save(gc);
	cairo_translate(gc, x + width / 2, y + height / 2);
	cairo_scale(gc, 1.0, 1.0 * height / width);
	cairo_arc(gc, -0.5, -0.5, width / 2, startangle, endangle);
	cairo_stroke(gc);
	cairo_restore(gc);
}

void IGraphics::DrawArc(const NRectangle &r, double startangle, double endangle)
{
	NRectangle *rr = (NRectangle *)&r;
	DrawArc(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight(), startangle, endangle);
}

void IGraphics::FillArc(int x, int y, int width, int height, double startangle, double endangle)
{
	cairo_save(gc);
	cairo_translate(gc, x + width / 2, y + height / 2);
	cairo_scale(gc, 1.0, 1.0 * height / width);
	cairo_arc(gc, -0.5, -0.5, width / 2, startangle, endangle);
	cairo_fill(gc);
	cairo_restore(gc);
}

void IGraphics::FillArc(const NRectangle &r, double startangle, double endangle)
{
	NRectangle *rr = (NRectangle *)&r;
	FillArc(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight(), startangle, endangle);
}

void IGraphics::DrawGraphics(int x, int y, int width, int height, const IGraphics &src, int src_x, int src_y)
{
	IGraphics *gg = (IGraphics *)&src;
	
	cairo_save(gc);
	cairo_set_source_surface(gc, gg->HandleSurface(), src_x, src_y);
	cairo_rectangle(gc, x, y, width, height);
	cairo_fill(gc);
	cairo_restore(gc);
}

void IGraphics::DrawGraphics(const NRectangle &r, const IGraphics &src, const NPoint &srcp)
{
	NRectangle *rr = (NRectangle *)&r;
	NPoint *pp = (NPoint *)&srcp;
	DrawGraphics(rr->GetX(), rr->GetY(), rr->GetWidth(), rr->GetHeight(), src, pp->GetX(), pp->GetY());
}

void IGraphics::DrawText(const Text &text, int x, int y, const NFont &font)
{
	Text *tt = (Text *)&text;
	char *ttt = new char[2 * tt->Length() + 1];
	tt->GetAnsiString(ttt, 2 * tt->Length());
	NFont *ff = (NFont *)&font;
	
	PangoLayout *layout = pango_cairo_create_layout(gc);
	pango_layout_set_font_description(layout, ff->Handle());
	pango_layout_set_text(layout, ttt, -1);
	
	cairo_move_to(gc, x, y);
	pango_cairo_show_layout(gc, layout);
	
	g_object_unref(layout);
	delete ttt;
}

void IGraphics::DrawText(const Text &text, const NPoint &p, const NFont &font)
{
	NPoint *pp = (NPoint *)&p;
	DrawText(text, pp->GetX(), pp->GetY(), font);
}

NSize IGraphics::GetTextExtents(const Text &text, const NFont &font)
{
	Text *tt = (Text *)&text;
	char *ttt = new char[2 * tt->Length() + 1];
	tt->GetAnsiString(ttt, 2 * tt->Length());
	NFont *ff = (NFont *)&font;
	
	PangoLayout *layout = pango_cairo_create_layout(gc);
	pango_layout_set_font_description(layout, ff->Handle());
	pango_layout_set_text(layout, ttt, -1);
	
	PangoRectangle inkrect;
	PangoRectangle logicalrect;
	pango_layout_get_pixel_extents(layout, &inkrect, &logicalrect);
	
	g_object_unref(layout);
	delete ttt;
	
	return NSize(inkrect.width, inkrect.height);
}
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
#include "graphicspatternradial.h"
#include "../../Text/text.h"
#include "../xexception.h"

GraphicsPatternRadial::GraphicsPatternRadial(const NPoint &a, double radiusa, const NPoint &b, double radiusb)
{
	NPoint *aa = (NPoint *)&a;
	NPoint *bb = (NPoint *)&b;
	pattern = cairo_pattern_create_radial(aa->GetX(), aa->GetY(), radiusa, bb->GetX(), bb->GetY(), radiusb);
}

GraphicsPatternRadial::~GraphicsPatternRadial()
{
	cairo_pattern_destroy(pattern);
}

cairo_pattern_t *GraphicsPatternRadial::Handle()
{
	return pattern;
}

void GraphicsPatternRadial::AddColorAtDistance(const NColor &c, double distance)
{
	NColor *cc = (NColor *)&c;
	cairo_pattern_add_color_stop_rgba(pattern, distance, cc->R(), cc->G(), cc->B(), cc->A());
}

int GraphicsPatternRadial::GetColorsCount()
{
	int colors = 0;
	cairo_pattern_get_color_stop_count(pattern, &colors);
	return colors;
}

NColor GraphicsPatternRadial::GetColorAndDistance(int index, double &distance)
{
	if (index < 0) throw new XException((Text)"Index " + index + " out of bounds", __FILE__, __LINE__, __func__);
	int numColors = GetColorsCount();
	if (index >= numColors) throw new XException((Text)"Index " + index + " out of bounds (" + numColors + ")", __FILE__, __LINE__, __func__);
	
	double r = 0, g = 0, b = 0, a = 0;
	cairo_pattern_get_color_stop_rgba(pattern, index, &distance, &r, &g, &b, &a);
	return NColor(r, g, b, a);
}

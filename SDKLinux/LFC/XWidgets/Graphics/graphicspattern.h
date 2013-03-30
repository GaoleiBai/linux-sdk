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
#ifndef GRAPHICSPATTERN_H
#define GRAPHICSPATTERN_H

#include "../../n_object.h"
#include <cairo/cairo.h>

class GraphicsPattern : public NObject {
protected:
	cairo_pattern_t *pattern;
	
public:
	GraphicsPattern();
	virtual ~GraphicsPattern();
	
	virtual cairo_pattern_t *Handle() = 0;

};

#endif // GRAPHICSPATTERN_H

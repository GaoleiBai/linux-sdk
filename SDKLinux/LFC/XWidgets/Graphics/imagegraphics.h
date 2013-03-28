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
#ifndef IMAGEGRAPHICS_H
#define IMAGEGRAPHICS_H

#include "igraphics.h"

class ImageGraphics : public IGraphics {
	
public:
	static const int ImageFormatARGB32 = CAIRO_FORMAT_ARGB32;
	static const int ImageFormatRGB24 = CAIRO_FORMAT_RGB24;
	static const int ImageFormatAlpha8 = CAIRO_FORMAT_A8;
	static const int ImageFormatAlpha1 = CAIRO_FORMAT_A1;
	static const int ImageFormatRGB16_565 = CAIRO_FORMAT_RGB16_565;
	
	ImageGraphics();
	ImageGraphics(int width, int height, int format);
	ImageGraphics(const ImageGraphics &i);
	virtual ~ImageGraphics();
	
	unsigned char *Data();
	int Format();
	int Width();
	int Height();
	int Stride();

};

#endif // IMAGEGRAPHICS_H

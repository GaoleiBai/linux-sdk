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
#include "imagegraphics.h"
#include "../xexception.h"

ImageGraphics::ImageGraphics()
{
	surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 1, 1);
	gc = cairo_create(surface);
	XException::CheckCairo(gc);
}

ImageGraphics::ImageGraphics(int width, int height, int format)
{
	surface = cairo_image_surface_create((cairo_format_t)format, width, height);
	gc = cairo_create(surface);
	XException::CheckCairo(gc);
}

ImageGraphics::ImageGraphics(const ImageGraphics &i)
{
	ImageGraphics *ii = (ImageGraphics *)&i;
	surface = cairo_image_surface_create_for_data(ii->Data(), (cairo_format_t)ii->Format(), ii->Width(), ii->Height(), ii->Stride());
	gc = cairo_create(surface);
	XException::CheckCairo(gc);
}

ImageGraphics::~ImageGraphics()
{
	cairo_destroy(gc);
	cairo_surface_destroy(surface);
}

unsigned char *ImageGraphics::Data()
{
	return cairo_image_surface_get_data(surface);
}

int ImageGraphics::Format()
{
	return cairo_image_surface_get_format(surface);
}

int ImageGraphics::Width()
{
	return cairo_image_surface_get_width(surface);
}

int ImageGraphics::Height()
{
	return cairo_image_surface_get_height(surface);
}

int ImageGraphics::Stride()
{
	return cairo_image_surface_get_stride(surface);
}

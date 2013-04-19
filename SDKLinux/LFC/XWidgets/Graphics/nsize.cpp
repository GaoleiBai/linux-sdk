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
#include "nsize.h"
#include "../../FileSystem/serializator.h"
#include <typeinfo>

NSize::NSize()
{
	width = 0;
	height = 0;
}

NSize::NSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

NSize::NSize(const NSize &s)
{
	width = s.width;
	height = s.height;
}

NSize::~NSize()
{
}

int NSize::GetWidth()
{
	return width;
}

int NSize::GetHeight()
{
	return height;
}

void NSize::SetWidth(int width)
{
	this->width = width;
}

void NSize::SetHeight(int height)
{
	this->height = height;
}

NObject *NSize::NewInstance()
{
	return new NSize();
}

bool NSize::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	NSize *ss = (NSize *)&o;
	return width == ss->width && height == ss->height;
}

void NSize::Serialize(const Serializator &s)
{
	Serializator *ss = (Serializator *)&s;
	ss->Put(width);
	ss->Put(height);
}

void NSize::Deserialize(const Serializator &s)
{
	Serializator *ss = (Serializator *)&s;
	width = ss->GetInt();
	height = ss->GetInt();
}

NSize &NSize::operator =(const NSize &s)
{
	width = s.width;
	height = s.height;
	
	return *this;
}

NSize NSize::operator +(const NSize &s)
{
	return NSize(width + s.width, height + s.height);
}

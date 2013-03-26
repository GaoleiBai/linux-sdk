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
#include "nrectangle.h"
#include "npoint.h"
#include "../../FileSystem/serializator.h"
#include <typeinfo>

NRectangle::NRectangle()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

NRectangle::NRectangle(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

NRectangle::NRectangle(const NRectangle &r)
{
	x = r.x;
	y = r.y;
	width = r.width;
	height = r.height;
}

NRectangle::~NRectangle()
{
}

int NRectangle::GetX()
{
	return x;
}

int NRectangle::GetY()
{
	return y;
}

int NRectangle::GetWidth()
{
	return width;
}

int NRectangle::GetHeight()
{
	return height;
}

void NRectangle::SetX(int x)
{
	this->x = x;
}

void NRectangle::SetY(int y)
{
	this->y = y;
}

void NRectangle::SetWidth(int width)
{
	this->width = width;
}

void NRectangle::SetHeight(int height)
{
	this->height = height;
}

bool NRectangle::Contains(int x, int y)
{
	if (x < this->x) return false;
	if (y < this->y) return false;
	if (x > this->x + width) return false;
	if (y > this->y + height) return false;
	return true;
}

bool NRectangle::Contains(const NPoint &p)
{
	NPoint *pp = (NPoint *)&p;
	return Contains(pp->GetX(), pp->GetY());
}

NObject *NRectangle::NewInstance()
{
	return new NRectangle();
}

bool NRectangle::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	NRectangle &rr = (NRectangle &)o;
	return rr.x == x && rr.y == y && rr.width == width && rr.height == height;
}

void NRectangle::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(x);
	((Serializator *)&s)->Put(y);
	((Serializator *)&s)->Put(width);
	((Serializator *)&s)->Put(height);
}

void NRectangle::Deserialize(const Serializator &s)
{
	x = ((Serializator *)&s)->GetInt();
	y = ((Serializator *)&s)->GetInt();
	width = ((Serializator *)&s)->GetInt();
	height = ((Serializator *)&s)->GetInt();
}
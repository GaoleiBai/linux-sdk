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
#include "npoint.h"
#include "../../FileSystem/serializator.h"
#include <typeinfo>

NPoint::NPoint()
{
	x = 0;
	y = 0;
}

NPoint::NPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

NPoint::NPoint(const NPoint &p)
{
	x = p.x;
	y = p.y;
}

NPoint::~NPoint()
{
}

int NPoint::GetX()
{
	return x;
}

int NPoint::GetY()
{
	return y;
}

void NPoint::SetX(int x)
{
	this->x = x;
}

void NPoint::SetY(int y)
{
	this->y = y;
}

NObject *NPoint::NewInstance()
{
	return new NPoint();
}

bool NPoint::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	NPoint &pp = (NPoint &)o;
	return pp.x == x && pp.y == y;
}

void NPoint::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(x);
	((Serializator *)&s)->Put(y);
}

void NPoint::Deserialize(const Serializator &s)
{
	x = ((Serializator *)&s)->GetInt();
	y = ((Serializator *)&s)->GetInt();
}
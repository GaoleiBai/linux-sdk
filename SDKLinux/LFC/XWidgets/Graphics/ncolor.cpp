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
#include "ncolor.h"
#include "../../FileSystem/serializator.h"
#include <typeinfo>

NColor::NColor()
{
	r = 0;
	g = 0;
	b = 0;
	a = 1;
}

NColor::NColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	this->r = r / 255.0;
	this->g = g / 255.0;
	this->b = b / 255.0;
	this->a = a / 255.0;
}

NColor::NColor(double r, double g, double b, double a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

NColor::NColor(const NColor &c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	this->a = c.a;
}

NColor::NColor(const NColor &c, double a)
{
	r = c.r;
	g = c.g;
	b = c.b;
	this->a = a;
}

NColor::~NColor()
{
}

NObject *NColor::NewInstance()
{
	return new NColor();
}

bool NColor::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	NColor *c = (NColor *)&o;
	return r == c->r && g == c->g && b == c->b && a == c->a;
}

void NColor::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(r);
	((Serializator *)&s)->Put(g);
	((Serializator *)&s)->Put(b);
	((Serializator *)&s)->Put(a);
}

void NColor::Deserialize(const Serializator &s)
{
	r = ((Serializator *)&s)->GetDouble();
	g = ((Serializator *)&s)->GetDouble();
	b = ((Serializator *)&s)->GetDouble();
	a = ((Serializator *)&s)->GetDouble();
}

double NColor::R()
{
	return r;
}

double NColor::G()
{
	return g;
}

double NColor::B()
{
	return b;
}

double NColor::A()
{
	return a;
}

NColor &NColor::operator =(const NColor &color)
{
	a = color.a;
	r = color.r;
	g = color.g;
	b = color.b;
	
	return *this;
}
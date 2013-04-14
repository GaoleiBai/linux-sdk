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
#ifndef NCOLOR_H
#define NCOLOR_H

#include "../../n_object.h"

class NColor : public NObject {
	double r, g, b, a;
	
public:
	NColor();
	NColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	NColor(double r, double g, double b, double a);
	NColor(const NColor &c);
	NColor(const NColor &c, double a);
	virtual ~NColor();
	
	virtual NObject *NewInstance();
	virtual bool Equals(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	double R();
	double G();
	double B();
	double A();
	
	NColor &operator =(const NColor &color);

};

#endif // NCOLOR_H

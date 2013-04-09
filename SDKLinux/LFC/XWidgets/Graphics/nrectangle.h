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
#ifndef NRECTANGLE_H
#define NRECTANGLE_H

#include "../../n_object.h"

class Serializator;
class NPoint;
class NSize;

class NRectangle : public NObject {
	int x, y, width, height;
	
public:
	NRectangle();
	NRectangle(int x, int y, int width, int height);
	NRectangle(const NRectangle &r);
	virtual ~NRectangle();

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	void SetX(int x);
	void SetY(int y);
	void SetWidth(int width);
	void SetHeight(int height);
	
	NPoint GetOrigin();
	NSize GetSize();
	
	bool Contains(int x, int y);
	bool Contains(const NPoint &p);
	
	NObject *NewInstance();
	bool Equals(const NObject &o);
	void Serialize(const Serializator &s);
	void Deserialize(const Serializator &s);

};

#endif // NRECTANGLE_H

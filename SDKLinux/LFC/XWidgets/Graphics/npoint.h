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
#ifndef NPOINT_H
#define NPOINT_H

#include "../../n_object.h"

class Serializator;

class NPoint : public NObject {
	int x, y;
	
public:
	NPoint();
	NPoint(int x, int y);
	NPoint(const NPoint &p);
	virtual ~NPoint();
	
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
	
	double Distance(const NPoint &p);
	
	NPoint operator +(const NPoint &p);
	NPoint operator -(const NPoint &p);
	NPoint &operator =(const NPoint &p);

	virtual NObject *NewInstance();
	virtual bool Equals(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
};

#endif // NPOINT_H

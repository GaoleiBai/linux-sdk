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
#ifndef NSIZE_H
#define NSIZE_H

#include "../../n_object.h"

class NSize : public NObject {
	int width, height;
	
public:
	NSize();
	NSize(int width, int height);
	NSize(const NSize &s);
	virtual ~NSize();

	int GetWidth();
	int GetHeight();
	void SetWidth(int width);
	void SetHeight(int height);
	
	virtual NObject *NewInstance();
	virtual bool Equals(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	NSize &operator =(const NSize &s);
};

#endif // NSIZE_H

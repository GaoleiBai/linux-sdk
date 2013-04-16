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
#include "nbool.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <typeinfo>

NBool::NBool()
{
	value = false;
}

NBool::NBool(const NBool &b)
{
	value = b.value;
}

NBool::NBool(bool b)
{
	value = b;
}

NBool::~NBool()
{
}

NBool &NBool::operator =(const NBool &n)
{
	value = n.value;
	return *this;
}

bool NBool::Parse(const Text &text)
{
	bool b = false;
	if (!TryParse(text, b))
		throw new Exception("Not bool found", __FILE__, __LINE__, __func__);
	return b;
}

bool NBool::TryParse(const Text &text, bool &b)
{
	if (*((Text *)&text) == "true") b = true;
	else if (*((Text *)&text) == "false") b = false;
	else return false;
	return true;
}

bool &NBool::Value()
{
	return value;
}

NObject *NBool::NewInstance()
{
	return new NBool();
}

Text NBool::ToText()
{
	return value ? (Text)"true" : (Text)"false";
}

int NBool::Compare(const NObject &o)
{
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NBool &)o);
}

int NBool::Compare(const NBool &b)
{
	if (value && !b.value) return 1;
	else if (!value && b.value) return -1;
	else return 0;
}

bool NBool::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(o) != typeid(*this)) return false;
	
	return Value() == ((NBool &)o).Value();
}

void NBool::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NBool::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetBool();
}

int NBool::COMPARER(const void *u, const void *v)
{
	bool *uu = (bool *)u;
	bool *vv = (bool *)v;
	
	if (*uu && !*vv) return 1;
	else if (!*uu && *vv) return -1;
	else 0;
}
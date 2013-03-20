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
#include <typeinfo>
#include "n_object.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <ctype.h>

NObject::NObject()
{
}

NObject::~NObject()
{
}

Text NObject::ClassName()
{
	char *p = (char *)typeid(*this).name();
	while (isdigit(*p)) p++;
	return Text(p);
}

NObject *NObject::NewInstance()
{
	throw new Exception(ClassName() + "::NewInstance() needs to be implemented to be able to deserializate a class.", __FILE__, __LINE__, __func__);
}

Text NObject::ToText()
{
	return ClassName();
}

int NObject::Compare(const NObject &o)
{
	return ToText().Compare(((NObject *)&o)->ToText());	
}

bool NObject::Equals(const NObject &o)
{
	return ToText().Compare(((NObject *)&o)->ToText());
}

void NObject::Serialize(const Serializator &s)
{
	throw new Exception(ClassName() + "::Serialize() must be able to serialize.", __FILE__, __LINE__, __func__);
}

void NObject::Deserialize(const Serializator &s)
{
	throw new Exception(ClassName() + "Deserialize() must be implemented to be able to deserialize.", __FILE__, __LINE__, __func__);
}

/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva
   This file is part of LFC Library.

   LFC Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   LFC Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with LFC Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA. or see http://www.gnu.org/licenses/. */
   
   
#include "nbool.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <typeinfo>

NBool::NBool()
{
	value = false;
}

NBool::NBool(bool b)
{
	value = b;
}

NBool::~NBool()
{
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
	if (typeid(*this) == typeid(o)){
		if (value == ((NBool *)&o)->value) return 0;
		else if (value) return 1;
		else return 0;
	}
	return NObject::Compare(o);
}

void NBool::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NBool::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetBool();
}
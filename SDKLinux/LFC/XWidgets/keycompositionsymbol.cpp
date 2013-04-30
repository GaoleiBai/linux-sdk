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
#include "keycompositionsymbol.h"
#include "../Text/text.h"
#include <typeinfo>

KeyCompositionSymbol::KeyCompositionSymbol(KeySym s, const Text &t)
{
	symbolValue = s;
	textValue = new Text(t);
}

KeyCompositionSymbol::KeyCompositionSymbol(const KeyCompositionSymbol &s)
{
	symbolValue = s.symbolValue;
	textValue = new Text(s.textValue);
}

KeyCompositionSymbol::~KeyCompositionSymbol()
{
	delete textValue;
}

KeyCompositionSymbol &KeyCompositionSymbol::operator =(const KeyCompositionSymbol &s)
{
	symbolValue = s.symbolValue;
	*textValue = *s.textValue;
}

Text KeyCompositionSymbol::ToText()
{
	return *textValue;
}

bool KeyCompositionSymbol::Equals(const NObject &o)
{
	if (typeid(*this) != typeid(o)) return false;
	KeyCompositionSymbol *oo = (KeyCompositionSymbol *)&o;
	return oo->symbolValue == symbolValue;
}

KeySym KeyCompositionSymbol::SymbolValue()
{
	return symbolValue;
}

Text KeyCompositionSymbol::TextValue()
{
	return *textValue;
}


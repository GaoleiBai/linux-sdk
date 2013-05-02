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
#include "controleventkeysymbol.h"
#include "windoweventkeysymbol.h"
#include "../keycompositionsymbol.h"

ControlEventKeySymbol::ControlEventKeySymbol(const ControlEventKeySymbol &e)
{
	source = e.source;
	symbol = new KeyCompositionSymbol(*e.symbol);
}

ControlEventKeySymbol::ControlEventKeySymbol(const WindowEventKeySymbol &e)
{
	source = NULL;
	symbol = new KeyCompositionSymbol(((WindowEventKeySymbol *)&e)->Symbol());
}

ControlEventKeySymbol::ControlEventKeySymbol(const KeyCompositionSymbol &s, Control *source)
{
	this->source = source;
	symbol = new KeyCompositionSymbol(s);
}

ControlEventKeySymbol::~ControlEventKeySymbol()
{
	delete symbol;
}

ControlEventKeySymbol &ControlEventKeySymbol::operator =(const ControlEventKeySymbol &s)
{
	source = s.source;
	*symbol = *s.symbol;
}

KeyCompositionSymbol &ControlEventKeySymbol::Symbol()
{
	return *symbol;
}




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
#ifndef KEYCOMPOSITIONSYMBOL_H
#define KEYCOMPOSITIONSYMBOL_H

#include "../n_object.h"
#include "keysymbols.h"
#include <X11/Xlib.h>

class KeyCompositionSymbol : public NObject {
protected:
	KeySym symbolValue;
	Text *textValue;
	
public:
	KeyCompositionSymbol(KeySym sym, const Text &t);
	KeyCompositionSymbol(const KeyCompositionSymbol &s);
	virtual ~KeyCompositionSymbol();
	
	virtual KeyCompositionSymbol &operator =(const KeyCompositionSymbol &s);
	virtual Text ToText();
	virtual bool Equals(const NObject &o);

	KeySym SymbolValue();
	Text TextValue();
	
	
};

#endif // KEYCOMPOSITIONSYMBOL_H

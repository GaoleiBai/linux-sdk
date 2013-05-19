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
#include "keycompositionmanager.h"
#include "keycompositionpath.h"
#include "xexception.h"
#include "../Text/text.h"

KeyCompositionManager *KeyCompositionManager::defaultKeyCompositionManager = NULL;

KeyCompositionManager::KeyCompositionManager()
{
	if (defaultKeyCompositionManager != NULL) 
		throw new XException("KeyComposition manager is a singleton class so that it can only be instantiated once", __FILE__, __LINE__, __func__);
	defaultKeyCompositionManager = this;
	
	paths = new Collection<KeyCompositionPath *>();
	
	paths->Add(new KeyCompositionPath("^^", "^", false));
	paths->Add(new KeyCompositionPath("^ ", "^", false));
	paths->Add(new KeyCompositionPath("^a", "â", false));
	paths->Add(new KeyCompositionPath("^e", "ê", false));
	paths->Add(new KeyCompositionPath("^i", "î", false));
	paths->Add(new KeyCompositionPath("^o", "ô", false));
	paths->Add(new KeyCompositionPath("^u", "û", false));
	paths->Add(new KeyCompositionPath("^A", "Â", false));
	paths->Add(new KeyCompositionPath("^E", "Ê", false));
	paths->Add(new KeyCompositionPath("^I", "Î", false));
	paths->Add(new KeyCompositionPath("^O", "Ô", false));
	paths->Add(new KeyCompositionPath("^U", "Û", false));
	
	paths->Add(new KeyCompositionPath("\"\"", "¨", false));
	paths->Add(new KeyCompositionPath("\" ", "\"", false));
	paths->Add(new KeyCompositionPath("¨a", "ä", false));
	paths->Add(new KeyCompositionPath("¨e", "ë", false));
	paths->Add(new KeyCompositionPath("¨i", "ï", false));
	paths->Add(new KeyCompositionPath("¨o", "ö", false));
	paths->Add(new KeyCompositionPath("¨u", "ü", false));
	paths->Add(new KeyCompositionPath("¨A", "Ä", false));
	paths->Add(new KeyCompositionPath("¨E", "Ë", false));
	paths->Add(new KeyCompositionPath("¨I", "Ï", false));
	paths->Add(new KeyCompositionPath("¨O", "Ö", false));
	paths->Add(new KeyCompositionPath("¨U", "Ü", false));
	
	paths->Add(new KeyCompositionPath("` ", "`", false));
	paths->Add(new KeyCompositionPath("``", "", false));
	paths->Add(new KeyCompositionPath("`a", "à", false));
	paths->Add(new KeyCompositionPath("`e", "è", false));
	paths->Add(new KeyCompositionPath("`i", "ì", false));
	paths->Add(new KeyCompositionPath("`o", "ò", false));
	paths->Add(new KeyCompositionPath("`u", "ù", false));
	paths->Add(new KeyCompositionPath("`A", "À", false));
	paths->Add(new KeyCompositionPath("`E", "È", false));
	paths->Add(new KeyCompositionPath("`I", "Ì", false));
	paths->Add(new KeyCompositionPath("`O", "Ò", false));
	paths->Add(new KeyCompositionPath("`U", "Ù", false));
	
	paths->Add(new KeyCompositionPath("' ", "'", false));
	paths->Add(new KeyCompositionPath("''", "", false));
	paths->Add(new KeyCompositionPath("'a", "á", false));
	paths->Add(new KeyCompositionPath("'e", "é", false));
	paths->Add(new KeyCompositionPath("'i", "í", false));
	paths->Add(new KeyCompositionPath("'o", "ó", false));
	paths->Add(new KeyCompositionPath("'u", "ú", false));
	paths->Add(new KeyCompositionPath("'A", "Á", false));
	paths->Add(new KeyCompositionPath("'E", "É", false));
	paths->Add(new KeyCompositionPath("'I", "Í", false));
	paths->Add(new KeyCompositionPath("'O", "Ó", false));
	paths->Add(new KeyCompositionPath("'U", "Ú", false));
}

KeyCompositionManager::~KeyCompositionManager()
{
	paths->DeleteAndClear();
	delete paths;
}

Text KeyCompositionManager::GetComposedKeySym(const Text &t, bool &continueComposing)
{
	Text *tt = (Text *)&t;

	for (int i=0; i<paths->Count(); i++) {
		Text &pathComposition = (*paths)[i]->Composition();
		if (pathComposition.StartsWith(t) && pathComposition.Length() > tt->Length()) {
			continueComposing = true;
			return "";
		} else if (pathComposition == t) {
			continueComposing = false;
			return (*paths)[i]->Result();
		}
	}
	
	continueComposing = false;
	return t;
}

KeyCompositionManager &KeyCompositionManager::Default()
{
	if (defaultKeyCompositionManager == NULL)
		defaultKeyCompositionManager = new KeyCompositionManager();
	return *defaultKeyCompositionManager;
}

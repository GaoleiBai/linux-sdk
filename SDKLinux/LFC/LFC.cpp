#include "LFC.h"


void lfc_init()
{
	// Set current locale
	Locale::SetLocale("");
	
	// Register classes to allow byname instanciation
	NObjectRegistry::Register(NObject());
	NObjectRegistry::Register(Text());
	NObjectRegistry::Register(DateTime());
	NObjectRegistry::Register(NObjectCollection());
	NObjectRegistry::Register(NObjectDictionary());
	NObjectRegistry::Register(Buffer());
	NObjectRegistry::Register(TextBuffer());
	
}
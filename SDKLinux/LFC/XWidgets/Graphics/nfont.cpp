#include "nfont.h"
#include "../../Text/text.h"
#include "../../Devices/stdout.h"

NFont::NFont(const Text &fontfamily, int weight, int size)
{
	this->familyName = new Text(fontfamily);
	this->weight = weight;
	this->size = size;
	
	char family[10000];
	familyName->GetAnsiString(family, 10000);
	
	fontdescription = pango_font_description_new();
	pango_font_description_set_family(fontdescription, family);
	pango_font_description_set_weight(fontdescription, (PangoWeight)weight);
	pango_font_description_set_absolute_size(fontdescription, size * PANGO_SCALE);
}

NFont::NFont(const NFont &font)
{
	this->familyName = new Text(font.familyName);
	this->weight = font.weight;
	this->size = font.size;
	
	char family[10000];
	familyName->GetAnsiString(family, 10000);
	
	fontdescription = pango_font_description_new();
	pango_font_description_set_family(fontdescription, family);
	pango_font_description_set_weight(fontdescription, (PangoWeight)weight);
	pango_font_description_set_absolute_size(fontdescription, size * PANGO_SCALE);
}

NFont::~NFont()
{
	delete familyName;
	pango_font_description_free(fontdescription);
}

PangoFontDescription *NFont::Handle()
{
	return fontdescription;
}

Text NFont::Family()
{
	return *familyName;
}

int NFont::Weight()
{
	return weight;
}

int NFont::Size()
{
	return size;
}

NFont NFont::operator =(const NFont &font)
{
	pango_font_description_free(fontdescription);
	delete this->familyName;
	
	this->familyName = new Text(font.familyName);
	this->weight = font.weight;
	this->size = font.size;
	
	char family[10000];
	familyName->GetAnsiString(family, 10000);
	
	fontdescription = pango_font_description_new();
	pango_font_description_set_family(fontdescription, family);
	pango_font_description_set_weight(fontdescription, (PangoWeight)weight);
	pango_font_description_set_absolute_size(fontdescription, size * PANGO_SCALE);
}

Collection<Text *> NFont::GetAvaliableFamilies()
{
	PangoFontMap *fontmap = pango_cairo_font_map_get_default();
	PangoFontFamily **families;
	int numFamilies = 0;
	
	Collection<Text *> result;
	pango_font_map_list_families(fontmap, &families, &numFamilies);
	for (int i=0; i<numFamilies; i++)
		result.Add(new Text(pango_font_family_get_name(families[i])));
	
	g_free(families);
	return result;
}


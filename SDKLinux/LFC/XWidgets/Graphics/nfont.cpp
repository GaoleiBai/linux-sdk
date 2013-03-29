#include "nfont.h"
#include "../../Text/text.h"

NFont::NFont(const Text &fontdescription)
{
	char fd[1000];
	((Text *)&fontdescription)->GetAnsiString(fd, 1000);
	this->fontdescription = pango_font_description_from_string(fd);
}

NFont::NFont(const Text &fontfamily, int weight, int size)
{
	char family[1000];
	((Text *)&fontfamily)->GetAnsiString(family, 1000);
	
	fontdescription = pango_font_description_new();
	pango_font_description_set_family(fontdescription, family);
	pango_font_description_set_weight(fontdescription, (PangoWeight)weight);
	pango_font_description_set_absolute_size(fontdescription, size * PANGO_SCALE);
}

NFont::~NFont()
{
	pango_font_description_free(fontdescription);
}

Text NFont::ToText()
{
	return pango_font_description_to_string(fontdescription);
}

PangoFontDescription *NFont::Handle()
{
	return fontdescription;
}

Text NFont::Name()
{
	return pango_font_description_to_string(fontdescription);
}

Text NFont::Family()
{
	return pango_font_description_get_family(fontdescription);
}

int NFont::Weight()
{
	return pango_font_description_get_weight(fontdescription);
}

int NFont::Size()
{
	return pango_font_description_get_size(fontdescription) / PANGO_SCALE;
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


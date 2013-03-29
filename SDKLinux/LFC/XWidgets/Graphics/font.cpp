#include "font.h"
#include "../../Text/text.h"

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

PangoFontDescription *NFont::Handle()
{
	return fontdescription;
}


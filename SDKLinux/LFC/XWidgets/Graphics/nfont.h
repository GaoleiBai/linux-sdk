#ifndef FONT_H
#define FONT_H

#include "../../n_object.h"
#include "../../Collections/collection.h"
#include <pango/pangocairo.h>

class NFont : public NObject {
	PangoFontDescription *fontdescription;
	Text *familyName;
	int weight;
	int size;
	
public:
	static const int FontWeightUltraLight = PANGO_WEIGHT_ULTRALIGHT;
	static const int FontWeightLight = PANGO_WEIGHT_LIGHT;
	static const int FontWeightNormal = PANGO_WEIGHT_NORMAL;
	static const int FontWeightBold = PANGO_WEIGHT_BOLD;
	static const int FontWeightUltraBold = PANGO_WEIGHT_ULTRABOLD;
	static const int FontWeightHeavy = PANGO_WEIGHT_HEAVY;

	NFont(const Text &fontfamily, int weight, int size);
	NFont(const NFont &font);
	virtual ~NFont();
	PangoFontDescription *Handle();
	
	Text Family();
	int Weight();
	int Size();
	
	NFont operator =(const NFont &font);
	
	static Collection<Text *> GetAvaliableFamilies();

};

#endif // FONT_H

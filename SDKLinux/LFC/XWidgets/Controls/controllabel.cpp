#include "controllabel.h"
#include "../../Text/text.h"

ControlLabel::ControlLabel(const Text &text, const NRectangle &area)
	: Control(area)
{
	this->text = new Text(text);
}

ControlLabel::~ControlLabel()
{
	delete text;
}

void ControlLabel::Draw(IGraphics *gc)
{
	
}


#ifndef CONTROLLABEL_H
#define CONTROLLABEL_H

#include "control.h"

class ControlLabel : public Control {
protected:
	Text *text;
	
public:
	ControlLabel(const Text &text, const NRectangle &area);
	virtual ~ControlLabel();

	virtual void Draw(IGraphics *gc);
	
};

#endif // CONTROLLABEL_H

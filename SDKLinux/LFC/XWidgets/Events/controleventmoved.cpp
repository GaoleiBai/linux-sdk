#include "controleventmoved.h"
#include "../Graphics/nrectangle.h"

ControlEventMoved::ControlEventMoved(Control *source, const NRectangle &currentArea)
{
	this->source = source;
	this->currentArea = new NRectangle(currentArea);
}

ControlEventMoved::ControlEventMoved(const ControlEventMoved &e)
{
	source = e.source;
	currentArea = e.currentArea;
}

ControlEventMoved::~ControlEventMoved()
{
	delete currentArea;
}

NRectangle ControlEventMoved::CurrentArea()
{
	return *currentArea;
}

#ifndef CONTROLEVENTMOVED_H
#define CONTROLEVENTMOVED_H

#include "controlevent.h"

class NRectangle;

class ControlEventMoved : public ControlEvent {
protected:
	NRectangle *currentArea;
	
public:
	ControlEventMoved(Control *source, const NRectangle &currentArea);
	ControlEventMoved(const ControlEventMoved &e);
	virtual ~ControlEventMoved();
	
	NRectangle CurrentArea();

};

#endif // CONTROLEVENTMOVED_H

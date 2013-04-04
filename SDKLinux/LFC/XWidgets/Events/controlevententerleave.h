#ifndef CONTROLEVENTENTERLEAVE_H
#define CONTROLEVENTENTERLEAVE_H

#include "controlevent.h"

class ControlEventEnterLeave : public ControlEvent {
protected:
	bool entered;
	
public:
	ControlEventEnterLeave(bool entered);
	virtual ~ControlEventEnterLeave();

};

#endif // CONTROLEVENTENTERLEAVE_H

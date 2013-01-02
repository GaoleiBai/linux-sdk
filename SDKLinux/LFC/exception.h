#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "n_object.h"

class Text;

class Exception : public NObject {

public:
	Exception();
	Exception(const Exception &e);
	Exception(const Text &t, const char *file, int line, const char *func);
	virtual ~Exception();
	
	Text ToText();

protected:
	Text *t;
	
};

#endif // EXCEPTION_H

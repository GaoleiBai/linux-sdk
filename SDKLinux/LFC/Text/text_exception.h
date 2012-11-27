#ifndef TEXTEXCEPTION_H
#define TEXTEXCEPTION_H

#include "../exception.h"

class TextException : public Exception {

public:
	TextException();
	TextException(const char *t);
	TextException(const Text &t);
	TextException(const TextException &e);
	virtual ~TextException();

};

#endif // TEXTEXCEPTION_H

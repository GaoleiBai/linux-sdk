#ifndef TEXTEXCEPTION_H
#define TEXTEXCEPTION_H

#include "../exception.h"

class TextException : public Exception {

public:
	TextException();
	TextException(const char *t, const char *file, int line, const char *func);
	TextException(const Text &t, const char *file, int line, const char *func);
	virtual ~TextException();

};

#endif // TEXTEXCEPTION_H

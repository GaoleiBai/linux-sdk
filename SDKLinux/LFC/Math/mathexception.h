#ifndef MATHEXCEPTION_H
#define MATHEXCEPTION_H

#include "../exception.h"

class MathException : Exception {

public:
	MathException();
	MathException(const Text &t, const char *file, int line, const char *func);
	virtual ~MathException();

};

#endif // MATHEXCEPTION_H

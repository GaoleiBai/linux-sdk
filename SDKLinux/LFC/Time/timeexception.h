#ifndef TIMEEXCEPTION_H
#define TIMEEXCEPTION_H

#include "../exception.h"

class Text;

class TimeException : Exception {

public:
	TimeException();
	TimeException(const Text &t, const char *file, int line, const char *func);
	virtual ~TimeException();


};

#endif // TIMEEXCEPTION_H

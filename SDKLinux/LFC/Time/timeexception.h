#ifndef TIMEEXCEPTION_H
#define TIMEEXCEPTION_H

#include "../exception.h"

class Text;

class TimeException : Exception {

public:
	TimeException();
	TimeException(const char *c);
	TimeException(const Text &t);
	TimeException(const TimeException &t);
	virtual ~TimeException();


};

#endif // TIMEEXCEPTION_H

#ifndef DEVICEEXCEPTION_H
#define DEVICEEXCEPTION_H

#include "../exception.h"

class DeviceException : public Exception {

public:
	DeviceException();
	DeviceException(const Text &reason, const char *file, int line, const char *function);
	virtual ~DeviceException();

};

#endif // DEVICEEXCEPTION_H

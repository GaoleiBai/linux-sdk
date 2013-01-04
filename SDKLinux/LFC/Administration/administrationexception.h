#ifndef ADMINISTRATIONEXCEPTION_H
#define ADMINISTRATIONEXCEPTION_H

#include "../exception.h"

class AdministrationException : public Exception {

public:
	AdministrationException();
	AdministrationException(const Text &t, const char *file, int line, const char *func);
	virtual ~AdministrationException();

};

#endif // ADMINISTRATIONEXCEPTION_H

#ifndef DIRECTORYEXCEPTION_H
#define DIRECTORYEXCEPTION_H

#include "../exception.h"

class FileSystemException : public Exception {

public:
	FileSystemException();
	FileSystemException(const Exception &e);
	FileSystemException(const Text &t, const char *file, int line, const char *func);
	virtual ~FileSystemException();

};

#endif // DIRECTORYEXCEPTION_H

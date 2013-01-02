#include "filesystemexception.h"
#include "../Text/text.h"

FileSystemException::FileSystemException() : Exception()
{
}

FileSystemException::FileSystemException(const Exception &e) : Exception(e)
{

}

FileSystemException::FileSystemException(const Text &t, const char *file, int line, const char *func) : Exception(t, file, line, func)
{
	
}

FileSystemException::~FileSystemException()
{
}




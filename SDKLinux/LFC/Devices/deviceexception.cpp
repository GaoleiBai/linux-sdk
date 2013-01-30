#include "deviceexception.h"

DeviceException::DeviceException() : Exception()
{
}

DeviceException::DeviceException(const Text &reason, const char *file, int line, const char *func) : Exception(reason, file, line, func)
{
}

DeviceException::~DeviceException()
{
}


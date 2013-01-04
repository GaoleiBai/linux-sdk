#include "administrationexception.h"

AdministrationException::AdministrationException()
{
}

AdministrationException::AdministrationException(const Text &t, const char *file, int line, const char *func) : Exception(t, file, line, func)
{
	
}

AdministrationException::~AdministrationException()
{
}


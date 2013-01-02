#include "exception.h"
#include "LFC.h"
#include "Devices/stdout.h"

Exception::Exception()
{
	t = new Text("");
}

Exception::Exception(const Exception &e)
{
	t = new Text(e.t);
	StdOut::PrintLine(t);
}

Exception::Exception(const Text &p, const char *file, int line, const char *func)
{
	t = new Text((Text)p + " in " + file + " at " + line + " : " + func);
	StdOut::PrintLine(t);
}

Exception::~Exception()
{
	delete t;
}

Text Exception::ToText()
{
	return *t;
}


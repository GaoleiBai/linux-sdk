#ifndef STDOUT_H
#define STDOUT_H

#include "../Text/text.h"

class StdOut {

public:
	StdOut();
	virtual ~StdOut();
	
	static void Print(const Text &t);
	static void PrintLine(const Text &t);
	static void PrintLine();
	
};

#endif // STDOUT_H

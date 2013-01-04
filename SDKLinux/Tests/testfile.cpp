#include "testfile.h"
#include "../LFC/LFC.h"

TestFile::TestFile()
{
}

TestFile::~TestFile()
{
}

int TestFile::Perform()
{
	try {
		Collection<Text *> lines = File::ReadAllLines("../main.cpp");
		
		for (int i=0; i<lines.Count(); i++)
		{
			StdOut::PrintLine(lines[i]);
		}	
	} catch (Exception *e) {
		int kk = 1;
		delete e;
	}
	
	return 0;
}

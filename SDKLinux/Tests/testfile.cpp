#include "../LFC/LFC.h"
#include "testfile.h"

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
			StdOut::PrintLine(lines[i]);

		Text t = Text::Join(lines, "\n");
		Text u = File::ReadAllText("../main.cpp");		
		
		if (t != u) {
			StdOut::PrintLine("Diferent results between ReadAllLines and ReadAllText");
			return -1;
		}
	} catch (Exception *e) {
		delete e;
		return -1;
	}
	
	return 0;
}

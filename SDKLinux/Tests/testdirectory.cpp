#include "testdirectory.h"
#include "../LFC/LFC.h"
#include <stdio.h>

TestDirectory::TestDirectory()
{
}

TestDirectory::~TestDirectory()
{
}

int TestDirectory::Perform()
{
	Collection<Text *> files = Directory::GetFiles(".");
	for (int i=0; i<files.Count(); i++) {
		files[i]->Print();
		printf("\r\n");
	}
	return 0;
}




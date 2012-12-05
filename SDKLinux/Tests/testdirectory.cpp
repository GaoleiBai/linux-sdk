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
	Collection<Text *> directories = Directory::GetDirectories("..");
	for (int i=0; i<directories.Count(); i++) {
		directories[i]->Print();
		printf("\r\n");
	}

	return 0;
}




#include "testdirectory.h"
#include "../LFC/LFC.h"

TestDirectory::TestDirectory()
{
}

TestDirectory::~TestDirectory()
{
}

void TestDirectory::Perform()
{
	Collection<Text *> files = Directory::GetFiles(".");
}




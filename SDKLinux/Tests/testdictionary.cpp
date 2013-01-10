#include "../LFC/LFC.h"
#include "testdictionary.h"

TestDictionary::TestDictionary()
{
}

TestDictionary::~TestDictionary()
{
}

int TestDictionary::Perform()
{
	Dictionary<Text *, int> d1(Text::COMPARER);
	d1.SetKey(new Text("Luis"), 10);
	d1.SetKey(new Text("Pedro"), 4);
	d1.SetKey(new Text("Alvaro"), 20);
	d1.SetKey(new Text("Luis"), 12);
	
	
	return 0;
}


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
	d1.SetKey(new Text("Zacarias"), 23);
	d1.SetKey(new Text("Armando"), 15);
	
	int iAux = 0;
	Collection<Text *> keys = d1.Keys();
	Collection<int> values = d1.Values();
	for (int i=0; i<keys.Count(); i++) {
		if (!d1.GetKey(keys[i], iAux)) {
			StdOut::PrintLine("Dictionary<K, V>::GetKey didn't work!!!");
			return -1;
		}
		if (iAux != values[i]) {
			StdOut::PrintLine("Dictionary<K, V>::Values didn't work!!!");
			return -1;
		}
		StdOut::PrintLine(*keys[i] + " " + iAux);
	}
	
	Text t = "Luis";
	d1.ClearKey(&t);
	if (d1.ExistsKet(&t)) {
		StdOut::PrintLine("ClearKey and ExistsKey doesn't work!!!");
		return -1;
	}
	
	return 0;
}


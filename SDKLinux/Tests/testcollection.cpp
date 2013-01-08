#include "testcollection.h"
#include "../LFC/LFC.h"

TestCollection::TestCollection()
{
}

TestCollection::~TestCollection()
{
}

int TestCollection::Perform()
{
	Collection<Text *> c1;
	c1.Add(new Text("Balón"));
	c1.Add(new Text("Escoba"));
	c1.Add(new Text("Pala"));
	c1.Add(new Text("General"));
	c1.Add(new Text("Camino"));
	c1.Add(new Text("Cáñamo"));
	c1.Add(new Text("Barrotes"));
	c1.Add(new Text("Sol"));
	c1.Add(new Text("Luna"));
	c1.Add(new Text("Tierra"));
	c1.Sort(Text::COMPARER);
	for (int i=0; i<c1.Count(); i++)
		StdOut::PrintLine(*c1[i]);
}

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
	c1.Add(new Text("Cóngrio"));
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
	c1.Add(new Text("Balon"));
	c1.Add(new Text("Canalización"));
	c1.Add(new Text("Camarilla"));
	c1.Add(new Text("Cooperación"));
	c1.QuickSort(Text::COMPARER);
	for (int i=1; i<c1.Count(); i++) {
		if (*c1[i-1] > *c1[i]) {
			StdOut::PrintLine("Collection<T>::Sort didn't work!!!");
			return -1;
		}
	}
	
	Text ttierra = "Tierra";
	int ixTierra = c1.BinarySearchIx(&ttierra, Text::COMPARER);
	if (ixTierra != 14) {
		StdOut::PrintLine("Collection<T>::BinarySearchIx didn't work!!!");
		return -1;
	}
	
	Text tpetardo = "Petardo";
	int ixpetardo = c1.BinarySearchIx(&tpetardo, Text::COMPARER);
	if (ixpetardo != -1) {
		StdOut::PrintLine("Collection<T>::BinarySearchIx didn't work!!!");
		return -1;
	}
	
	c1.InsertAt(0, new Text("Primero"));
	c1.InsertAt(c1.Count(), new Text("Ultimo"));
	if ((Text)"Primero" != c1.First() ||
		(Text)"Ultimo" != c1.Last()) 
	{
		StdOut::PrintLine("Collection<T>::InsertAt didn't work!!!");
		return -1;
	}
	
	for (int i=0; i<c1.Count(); i++)
		StdOut::PrintLine(*c1[i]);
	c1.DeleteAndClear();
	if (c1.Count() != 0) {
		StdOut::PrintLine("Collection<T>::DeleteAndClear didn't work!!!");
		return -1;
	}
	
	Collection<DateTime *> c2;
	c2.Add(new DateTime(1977, 6, 3));
	c2.Add(new DateTime(1981, 3, 1));
	c2.Add(new DateTime(1976, 7, 9));
	c2.Add(new DateTime(1975, 8, 21));
	c2.Add(new DateTime(1974, 11, 14));
	c2.QuickSort(DateTime::COMPARER);
	for (int i=0; i<c2.Count(); i++)
		StdOut::PrintLine(c2[i]->ToText());
		
	if (c2.Count() != 5) {
		StdOut::PrintLine("Collection<T>::Add didn't work!!!");
		return -1;
	}
	
	c2.DeleteAndClear();
	if (c2.Count() != 0) {
		StdOut::PrintLine("Collection<T>::DeleteAndClear didn't work!!!");
		return -1;
	}
	
	Collection<int> c3;
	c3.Add(1);
	c3.Clear();
	
	return 0;
}

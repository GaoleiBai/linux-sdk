#include "testdelegation.h"
#include "../LFC/LFC.h"
#include "stdio.h"

TestDelegation::TestDelegation()
{
}

TestDelegation::~TestDelegation()
{
}

int TestDelegation::Perform()
{
	class A : public NObject
	{
	public:
		A() {};
		void *amethod(char *param) { 
			StdOut::PrintLine((Text)"Hello " + param + " world!!!");
			return (void *)"Wolomolo!!!"; 
		};
	};
	
	A aa;
	NDelegation d(&aa, (Delegate)&A::amethod, (char *)"Aparam");
	Text wolomolo = (char *)d.Exec();
	StdOut::PrintLine(wolomolo);
	
	int kk = 0;
	return 1;
}


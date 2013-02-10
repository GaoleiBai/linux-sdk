#include "testthread.h"
#include "../LFC/LFC.h"
#include "ThreadHelpClasses/classforthreading.h"

TestThread::TestThread()
{
}

TestThread::~TestThread()
{
}

int TestThread::Perform()
{
	ClassForThreading c;
	c.Start();
	c.Stop();
}

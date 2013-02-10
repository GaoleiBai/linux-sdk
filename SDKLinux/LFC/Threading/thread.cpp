#include "thread.h"
#include <unistd.h>

Thread::Thread()
{
}

Thread::Thread(const Text &name)
{
	
}

Thread::Thread(const Text &name, bool joinable)
{
	
}

Thread::~Thread()
{
}

void Thread::Launch(NObject *nobject, void (NObject::*method)())
{
	void **params = new void *[2];
	params[0] = nobject;
	params[1] = (void*)method;
	pthread_create(&thread, NULL, threadFunction, params);
	//((*nobject).*method)();
}

void *Thread::Join()
{
	
}

void Thread::Sleep(unsigned long microseconds)
{
	usleep(microseconds);
}

void *Thread::threadFunction(void *params)
{
	
}


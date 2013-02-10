#ifndef THREAD_H
#define THREAD_H

#include "../n_object.h"
#include <pthread.h>

typedef void (NObject::*THREAD_DELEGATE)() ;

class Thread : public NObject {

public:
	Thread();
	Thread(const Text &name);
	Thread(const Text &name, bool joinable);
	virtual ~Thread();
	
	void Launch(NObject *nobject, void (NObject::*method)());
	void *Join();
	static void Sleep(unsigned long microseconds);
	
private:
	Text *name;
	bool joinable;
	
	pthread_t thread;
	static void *threadFunction(void *params);

};

#endif // THREAD_H

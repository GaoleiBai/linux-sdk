#ifndef THREAD_H
#define THREAD_H

#include "../n_object.h"

class Thread {

public:
	Thread();
	Thread(const Text &name);
	Thread(const Text &name, bool joinable);
	virtual ~Thread();
	
	void Launch(void *(*function)(void *params), void *paramsForTheThreadFunction);
	void *Join();
	
private:
	Text *name;
	bool joinable;

};

#endif // THREAD_H

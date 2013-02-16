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
	Thread::Sleep(500000);
	c.Stop();
	
	
	class Q : public NObject {
		Mutex *m;
	public:
		Q(const Mutex *m) { this->m = (Mutex *)m; }
		void *Perform(void *q) {
			while (true) {
				m->Lock();
				int *qq = (int *)q; 
				if (*qq == 0) {
					m->Unlock();
					break;
				}
				if (*qq % 2 == 1) {
					StdOut::PrintLine((Text)"i = " + *qq);
					*qq = *qq - 1;
				}
				m->Unlock();
			}
			StdOut::PrintLine("Q ends");
		}
	};
	class R : public NObject {
		Mutex *m;
	public:
		R(const Mutex *m) { this->m = (Mutex *)m; }
		void *Perform(void *r) {
			while (true) {
				{
					MutexLock L(m);
					
					int *rr = (int *)r; 
					if (*rr == 0) break;
					if (*rr % 2 == 0) {
						StdOut::PrintLine((Text)"i = " + *rr);
						*rr = *rr - 1;
					}
				}
			}
			StdOut::PrintLine("R ends");
		}
	};
	Mutex m;
	int i = 500;
	Q q(&m);
	R r(&m);
	Thread tQ;
	Thread tR;
	tQ.Launch(&q, (Delegate)&Q::Perform, &i);
	tR.Launch(&r, (Delegate)&R::Perform, &i);
	while (i != 0) Thread::Sleep(1000);
	
	
	class Work : public NObject {
		int bullets;
		Mutex *m;
		WaitCondition *w;
	public:
		Work() {
			bullets = 500;
			m = new Mutex(true);
			w = new WaitCondition();
		}
		
		~Work() {
			delete m;
			delete w;
		}
		
		void Shot() {
			w->Signal();
		}
		
		void *Perform(void *param) {
			while (bullets != 0) {
				{
					MutexLock L(m);
					
					w->Wait(*m);
				}
				StdOut::PrintLine((Text)bullets-- + " bullets");
				bool *trigger = (bool *)param;
				*trigger = true;
			}
			StdOut::PrintLine("I've run out of bullets");
		}
	};
	
	
	bool trigger = false;
	Work w;
	Thread tW;
	tW.Launch(&w, (Delegate)&Work::Perform, &trigger);
	for (int i=0; i<500; i++) {
		trigger = false;
		w.Shot();
		while(!trigger) Thread::Sleep(100);
	}
	
	return 0;
}

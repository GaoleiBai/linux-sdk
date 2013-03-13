/* 
* LFC Library - Linux toolkit
* 
* Copyright (C) 2012, 2013 Daniel Mosquera Villanueva 
* (milkatoffeecuco@gmail.com)
* This file is part of LFC Library.
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*
**/
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
				Thread::Sleep(1);
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
				StdOut::PrintLine("RR");
				Thread::Sleep(1);
				m->Lock();
				int *rr = (int *)r; 
				if (*rr == 0) {
					m->Unlock();
					break;
				}
				if (*rr % 2 == 0) {
					StdOut::PrintLine((Text)"i = " + *rr);
					*rr = *rr - 1;
				}
				m->Unlock();
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
	Thread::Sleep(100000);
	for (int i=0; i<500; i++) {
		trigger = false;
		w.Shot();
		while(!trigger) Thread::Sleep(100);
	}
	
	class JoinableWork : public NObject {
	public:
		void *DoWork(void *param) {
			for (int i=0; i<5; i++) StdOut::PrintLine((Text)"Done " + (long)param + ":" + i);
			delete this;
			return param;
		}
	};
	Collection<Thread *> threadcol;
	for (long i=0; i<100; i++) threadcol.Add(new Thread((Text)"JoinableWork " + i, true));
	for (long i=0; i<100; i++) threadcol[i]->Launch(new JoinableWork(), (Delegate)&JoinableWork::DoWork, (void *)i);
	for (long i=0; i<100; i++) StdOut::PrintLine((Text)"Finished " + (long)threadcol[i]->Join());
	threadcol.DeleteAndClear();
	
	return 0;
}

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
#ifndef THREAD_H
#define THREAD_H

#include "../ndelegation.h"
#include <pthread.h>

class Text;

typedef void (NObject::*THREAD_DELEGATE)() ;

class Thread : public NObject {

public:
	Thread();
	Thread(const Text &name);
	Thread(const Text &name, bool joinable);
	virtual ~Thread();
	
	void Launch(NObject *nobject, Delegate method, void *param);
	void Launch(const NDelegation &delegation, void *param);
	void *Join();
	static void Sleep(unsigned long microseconds);
	
private:
	Text *name;
	bool joinable;
	
	pthread_t thread;
	static void *threadFunction(void *params);
	
	Text ToText();

};

#endif // THREAD_H

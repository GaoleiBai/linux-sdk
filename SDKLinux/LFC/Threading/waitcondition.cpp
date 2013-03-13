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
#include "waitcondition.h"
#include "threadingexception.h"
#include "mutex.h"
#include "../Text/text.h"
#include <errno.h>

WaitCondition::WaitCondition()
{
	if (pthread_cond_init(&cond, NULL) != 0)
		throw new ThreadingException("Cannot create condition", __FILE__, __LINE__, __func__);
}

WaitCondition::~WaitCondition()
{
	if (pthread_cond_destroy(&cond) != 0)
		throw new ThreadingException("Cannot destroy condition", __FILE__, __LINE__, __func__);
}

void WaitCondition::Wait(const Mutex &lockedmutex)
{
	int i = pthread_cond_wait(&cond, &((Mutex *)&lockedmutex)->mutex);
	if (i == EINVAL) throw new ThreadingException("Invalid condition or trying to wait over a condition locked by different mutexes", __FILE__, __LINE__, __func__);
	else if (i == EPERM) throw new ThreadingException("Mutex not owned by the current thread right now", __FILE__, __LINE__, __func__);
	else if (i != 0) throw new ThreadingException("Unspecified error", __FILE__, __LINE__, __func__);
}

bool WaitCondition::Wait(const Mutex &lockedmutex, unsigned long nanoseconds)
{
	struct timespec timeout;
	timeout.tv_sec = nanoseconds / 1000000000;
	timeout.tv_nsec = nanoseconds % 1000000000;
	
	int i = pthread_cond_timedwait(&cond, &((Mutex *)&lockedmutex)->mutex, &timeout);
	if (i == EINVAL) throw new ThreadingException("Invalid condition or trying to wait over a condition locked by different mutexes", __FILE__, __LINE__, __func__);
	else if (i == EPERM) throw new ThreadingException("Mutex not owned by the current thread right now", __FILE__, __LINE__, __func__);
	else if (i == ETIMEDOUT) return false;
	else if (i != 0) throw new ThreadingException("Unspecified error", __FILE__, __LINE__, __func__);
	
	return true;
}

void WaitCondition::Signal()
{
	int i = pthread_cond_signal(&cond);
	if (i == EINVAL) throw new ThreadingException("Invalid condition variable", __FILE__, __LINE__, __func__);
	else if (i != 0) throw new ThreadingException("Unspecified error", __FILE__, __LINE__, __func__);
}

void WaitCondition::SignalAll()
{
	int i = pthread_cond_broadcast(&cond);
	if (i == EINVAL) throw new ThreadingException("Invalid condition variable", __FILE__, __LINE__, __func__);
	else if (i != 0) throw new ThreadingException("Unspecified error", __FILE__, __LINE__, __func__);
}

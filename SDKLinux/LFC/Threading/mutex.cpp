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
#include "mutex.h"
#include "threadingexception.h"
#include "../Text/text.h"
#include <errno.h>

void Mutex::init(bool recursive)
{
	pthread_mutexattr_t attrs;
	pthread_mutexattr_init(&attrs);
	pthread_mutexattr_settype(&attrs, recursive ? PTHREAD_MUTEX_RECURSIVE : PTHREAD_MUTEX_NORMAL);
	int i = pthread_mutex_init(&mutex, &attrs);
	pthread_mutexattr_destroy(&attrs);
	
	if (i == EAGAIN) throw new ThreadingException("Insufficient resources", __FILE__, __LINE__, __func__);
	else if (i == ENOMEM) throw new ThreadingException("Insufficient memory", __FILE__, __LINE__, __func__);
	else if (i == EPERM) throw new ThreadingException("Insufficient permissions", __FILE__, __LINE__, __func__);
	else if (i == EBUSY) throw new ThreadingException("Mutex in use?", __FILE__, __LINE__, __func__);
	else if (i == EINVAL) throw new ThreadingException("Invalid attibute", __FILE__, __LINE__, __func__);
}

Mutex::Mutex()
{
	init(false);
}

Mutex::Mutex(bool recursive)
{
	init(recursive);
}

Mutex::~Mutex()
{
	int i = pthread_mutex_destroy(&mutex);
	if (i == EBUSY) throw new ThreadingException("The mutex is currently in use and cannot be destroyed", __FILE__, __LINE__, __func__);
	else if (i == EINVAL) throw new ThreadingException("Invalid mutex", __FILE__, __LINE__, __func__);
}

void Mutex::Lock()
{
	int i = pthread_mutex_lock(&mutex);
	if (i == EDEADLK) throw new ThreadingException("Current thread has already locked the mutex", __FILE__, __LINE__, __func__);
	else if (i == EINVAL) throw new ThreadingException("Thread priority higher than mutex priority or mutex not initialized", __FILE__, __LINE__, __func__);
	else if (i == EAGAIN) throw new ThreadingException("Maximum recursive locks may be exceeded", __FILE__, __LINE__, __func__);
}

bool Mutex::TryLock()
{
	int i = pthread_mutex_trylock(&mutex);
	if (i == 0) return true;
	else if (i == EBUSY) return false;
	else if (i == EINVAL) throw new ThreadingException("Thread priority higher than mutex priority or mutex not initialized", __FILE__, __LINE__, __func__);
	else if (i == EAGAIN) return false;
}

void Mutex::Unlock()
{
	int i = pthread_mutex_unlock(&mutex);
	if (i == EPERM) throw new ThreadingException("Current thread haven't locked the mutex yet", __FILE__, __LINE__, __func__);
	else if (i == EINVAL) throw new ThreadingException("Thread priority higher than mutex priority or mutex not initialized", __FILE__, __LINE__, __func__);
	else if (i == EAGAIN) throw new ThreadingException("Maximum recursive locks may be exceeded", __FILE__, __LINE__, __func__);
}


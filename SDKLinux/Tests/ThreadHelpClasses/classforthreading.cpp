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
#include "classforthreading.h"

ClassForThreading::ClassForThreading()
{
	status = 2;
	thread = NULL;
}

ClassForThreading::~ClassForThreading()
{
	Stop();
}

void ClassForThreading::Start()
{
	if (thread != NULL) return;
	status = 0;
	thread = new Thread("Thread ClassForThreading", false);
	thread->Launch(this, (Delegate)&ClassForThreading::funcionThread, NULL);
}

void ClassForThreading::Stop()
{
	if (thread == NULL) return;
	if (status == 0) status = 1;
	while (status != 2) Thread::Sleep(100000);
	delete thread;
	thread = NULL;
}

void *ClassForThreading::funcionThread(void *param)
{
	int i = 0;
	while (status == 0) {
		Thread::Sleep(1000);
		StdOut::PrintLine((Text)"ClassForThreading printing " + i++);
	}
	
	status = 2;
}
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
#include "LFC.h"
#include <execinfo.h>
#include <signal.h>

void sigsegv_handler(int signal) 
{
	void *addresses[1000];
	size_t numberOfFrames = backtrace(addresses, 1000);
	StdErr::PrintLine((Text)"Error signal:" + signal);
	backtrace_symbols_fd(addresses, numberOfFrames, 2);
}

void lfc_init()
{
	// Set current locale
	Locale::SetLocale("");
	
	// Register classes to allow byname instanciation
	NObjectRegistry::Register(Text());
	NObjectRegistry::Register(DateTime());
	NObjectRegistry::Register(NObjectCollection());
	NObjectRegistry::Register(NObjectDictionary());
	NObjectRegistry::Register(Buffer());
	NObjectRegistry::Register(TextBuffer());
	NObjectRegistry::Register(NChar());
	NObjectRegistry::Register(NWChar());
	NObjectRegistry::Register(NShort());
	NObjectRegistry::Register(NInt());
	NObjectRegistry::Register(NBool());
	NObjectRegistry::Register(NLong());
	NObjectRegistry::Register(NLongLong());
	NObjectRegistry::Register(NUChar());
	NObjectRegistry::Register(NUShort());
	NObjectRegistry::Register(NUInt());
	NObjectRegistry::Register(NULong());
	NObjectRegistry::Register(NULongLong());
	NObjectRegistry::Register(NFloat());
	NObjectRegistry::Register(NDouble());
	NObjectRegistry::Register(NLongDouble());
	
	// Register sigsegv (segmentation fault)
	signal(SIGSEGV, sigsegv_handler);
}
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
#ifndef IFILE_H
#define IFILE_H

#include <sys/types.h>

class Text;

class IFile {

public:
	IFile();
	virtual ~IFile();

	virtual int Read(char *buffer, int lonBuffer);
	virtual void Read(char *buffer, int lonBuffer, long nanoseconds_timeout);
	virtual int Write(const char *buffer, int lonBuffer);
	virtual bool WaitForDataComming(long nanoseconds_timeout);
	virtual bool WaitForDataGoing(long nanoseconds_timeout);
	
	virtual Text ReadLine();
	virtual Text ReadLine(long nanoseconds_timeout);
	virtual void Write(const Text &text);
	virtual void WriteLine(const Text &text);
	virtual void WriteLine();
	

	
protected:
	int fd;
	
};

#endif // IFILE_H

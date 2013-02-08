/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva (daniel.m.v@terra.es)
   This file is part of LFC Library.

   LFC Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   LFC Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with LFC Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA. or see http://www.gnu.org/licenses/. */
   
   
#include "ifile.h"
#include "../Text/text.h"
#include "../exception.h"
#include <unistd.h>

IFile::IFile()
{
}

IFile::~IFile()
{
}

int IFile::Read(char *buffer, int lonBuffer)
{
	if (fd == -1)
		throw new Exception("Cannot read from a closed device or file", __FILE__, __LINE__, __func__);
	size_t leido = read(fd, buffer, lonBuffer);
	if (leido == -1)
		throw new Exception(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return leido;
}

int IFile::Write(const char *buffer, int lonBuffer)
{
	if (fd == -1)
		throw new Exception("Cannot write in a closed device or file", __FILE__, __LINE__, __func__);
	size_t escrito = 0;
	while (escrito < lonBuffer) {
		int quedan = lonBuffer - escrito;
		size_t res = write(fd, buffer + escrito, quedan > 1000 ? 1000 : quedan);
		if (res == -1) throw new Exception(Text::FromErrno(), __FILE__, __LINE__, __func__);
		escrito += res;
	}
	return escrito;
}

bool IFile::WaitForDataComming(unsigned long nanoseconds)
{
	if (fd == -1)
		throw new Exception("Can only perform actions on an open device", __FILE__, __LINE__, __func__);
		
	struct timeval timeout;
	timeout.tv_sec = nanoseconds / 1000000000;
	timeout.tv_usec = nanoseconds % 1000000000;
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(fd, &readSet);
	if (select(fd + 1, &readSet, NULL, NULL, &timeout) == -1)
		throw new Exception(Text::FromErrno(), __FILE__, __LINE__, __func__);
	bool thereIsData = FD_ISSET(fd, &readSet);	
	FD_CLR(fd, &readSet);
	return thereIsData;
}

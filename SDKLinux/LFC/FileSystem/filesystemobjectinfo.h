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
#ifndef FILESYSTEMOBJECTINFO_H
#define FILESYSTEMOBJECTINFO_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filesystem.h"
#include "../Text/text.h"
#include "../Time/datetime.h"

class FileSystemObjectInfo : NObject {

public:
	FileSystemObjectInfo(const Text &path);
	virtual ~FileSystemObjectInfo();
	
	Text Name();
	int Size();
	bool IsFile();
	bool IsDirectory();
	bool IsBlockDevice();
	bool IsCharacterDevice();
	bool IsNamedPipe();
	bool IsSymbolicLink();
	bool IsDomainSocket();
	bool IsUnknown();
	bool UserCanRead();
	bool UserCanWrite();
	bool UserCanExec();
	bool GroupCanRead();
	bool GroupCanWrite();
	bool GroupCanExec();
	bool OthersCanRead();
	bool OthersCanWrite();
	bool OthersCanExec();
	int Type();
	int UserID();
	int GroupID();
	int DeviceID();
	int BlockSize();
	int BlocksAllocated();
	ino_t Inode();
	DateTime LastAccessTime();
	DateTime LastModificationTime();
	DateTime LastStatusChangeTime();
	
	Text ToText();

private:
	Text *name;
	int type;
	int size;
	mode_t mode;
	int userID;
	int groupID;
	int deviceID;
	int blockSize;
	int blocksAllocated;
	ino_t inode;
	DateTime *lastAccessTime;
	DateTime *lastModificationTime;
	DateTime *lastStatusChangeTime;
};

#endif // FILESYSTEMOBJECTINFO_H

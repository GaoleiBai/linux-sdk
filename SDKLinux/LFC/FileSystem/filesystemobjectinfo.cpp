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
#include "filesystemobjectinfo.h"
#include "filesystemexception.h"
#include "../Text/text_buffer.h"

FileSystemObjectInfo::FileSystemObjectInfo(const Text &path)
{
	char cadena[10001];
	struct stat buf;
	
	((Text)path).GetAnsiString(cadena, 10000);
	if (stat(cadena, &buf)) throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	
	name = new Text(path);
	mode = buf.st_mode;
	size = buf.st_size;
	userID = buf.st_uid;
	groupID = buf.st_gid;
	deviceID = buf.st_rdev;
	blockSize = buf.st_blksize;
	blocksAllocated = buf.st_blocks;
	lastAccessTime = new DateTime(buf.st_atime);
	lastModificationTime = new DateTime(buf.st_mtime);
	lastStatusChangeTime = new DateTime(buf.st_ctime);
	
	if (S_ISREG(mode)) type = FSOK_File;
	else if (S_ISDIR(mode)) type = FSOK_Directory;
	else if (S_ISBLK(mode)) type = FSOK_BlockDevice;
	else if (S_ISCHR(mode)) type = FSOK_CharacterDevice;
	else if (S_ISFIFO(mode)) type = FSOK_NamedPipe;
	else if (S_ISLNK(mode)) type = FSOK_SymbolicLink;
	else if (S_ISSOCK(mode)) type = FSOK_DomainSocket;
	else type = FSOK_UnknownFileSystemObject;
}

FileSystemObjectInfo::~FileSystemObjectInfo()
{
	delete name;
	delete lastAccessTime;
	delete lastModificationTime;
	delete lastStatusChangeTime;
}

Text FileSystemObjectInfo::Name()
{
	return *name;
}

int FileSystemObjectInfo::Size()
{
	return size;
}

DateTime FileSystemObjectInfo::LastAccessTime()
{
	return *lastAccessTime;
}

DateTime FileSystemObjectInfo::LastModificationTime()
{
	return *lastModificationTime;
}

DateTime FileSystemObjectInfo::LastStatusChangeTime()
{
	return *lastStatusChangeTime;
}

bool FileSystemObjectInfo::IsFile()
{
	return S_ISREG(mode); 
}

bool FileSystemObjectInfo::IsDirectory()
{
	return S_ISDIR(mode);
}

bool FileSystemObjectInfo::IsBlockDevice()
{
	return S_ISBLK(mode);
}

bool FileSystemObjectInfo::IsCharacterDevice()
{
	return S_ISCHR(mode);
}

bool FileSystemObjectInfo::IsNamedPipe()
{
	return S_ISFIFO(mode);
}

bool FileSystemObjectInfo::IsSymbolicLink()
{
	return S_ISLNK(mode);
}

bool FileSystemObjectInfo::IsDomainSocket()
{
	return S_ISSOCK(mode);
}

bool FileSystemObjectInfo::IsUnknown()
{
	return !S_ISREG(mode) && !S_ISDIR(mode) && !S_ISBLK(mode) && !S_ISCHR(mode) && !S_ISFIFO(mode) && !S_ISLNK(mode) && !S_ISSOCK(mode);
}

bool FileSystemObjectInfo::UserCanRead()
{
	return mode & S_IRUSR;
}

bool FileSystemObjectInfo::UserCanWrite()
{
	return mode & S_IWUSR;
}

bool FileSystemObjectInfo::UserCanExec()
{
	return mode & S_IXUSR;
}

bool FileSystemObjectInfo::GroupCanRead()
{
	return mode & S_IRGRP;
}

bool FileSystemObjectInfo::GroupCanWrite()
{
	return mode & S_IWGRP;
}

bool FileSystemObjectInfo::GroupCanExec()
{
	return mode & S_IXGRP;
}

bool FileSystemObjectInfo::OthersCanRead()
{
	return mode & S_IROTH;
}

bool FileSystemObjectInfo::OthersCanWrite()
{
	return mode & S_IWOTH;
}

bool FileSystemObjectInfo::OthersCanExec()
{
	return mode & S_IXOTH;
}

int FileSystemObjectInfo::Type()
{
	return type;
}

int FileSystemObjectInfo::UserID()
{
	return userID;
}

int FileSystemObjectInfo::GroupID()
{
	return groupID;
}

int FileSystemObjectInfo::DeviceID()
{
	return deviceID;
}

int FileSystemObjectInfo::BlockSize()
{
	return blockSize;
}

int FileSystemObjectInfo::BlocksAllocated()
{
	return blocksAllocated;
}

ino_t FileSystemObjectInfo::Inode()
{
	return inode;
}

Text FileSystemObjectInfo::ToText()
{
	TextBuffer b;
	b.AppendLine(*name);
	if (type == FSOK_File) b.AppendLine("File");
	else if (type == FSOK_Directory) b.AppendLine("Directory");
	else if (type == FSOK_BlockDevice) b.AppendLine("Block device");
	else if (type == FSOK_CharacterDevice) b.AppendLine("Character device");
	else if (type == FSOK_NamedPipe) b.AppendLine("Named pipe");
	else if (type == FSOK_SymbolicLink) b.AppendLine("Symbolic link");
	else if (type == FSOK_DomainSocket) b.AppendLine("Domain socket");
	else b.AppendLine("Unknown");
	b.AppendLine((Text)size + " bytes long");
	b.AppendLine((Text)"User ID: " + userID);
	b.AppendLine((Text)"Group ID: " + groupID);
	if (IsBlockDevice() || IsCharacterDevice()) b.AppendLine((Text)"Device ID: " + deviceID);
	b.AppendLine((Text)"Block size: " + blockSize);
	b.AppendLine((Text)"Blocks allocated: " + blocksAllocated);
	b.AppendLine((Text)"Inode: " + inode);
	b.AppendLine((Text)"Last access time: " + lastAccessTime->ToText("%d/%m/%Y %H:%M:%S"));
	b.AppendLine((Text)"Last modification time: " + lastModificationTime->ToText("%d/%m/%Y %H:%M:%S"));
	b.AppendLine((Text)"Last status modification time: " + lastStatusChangeTime->ToText("%d/%m/%Y %H:%M:%S"));
	return b.ToText();
}
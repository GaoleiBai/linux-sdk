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
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "../Collections/collection.h"
#include "filesystemobjectinfo.h"
#include <sys/types.h>
#include <dirent.h>
#include "filesystem.h"

class Text;

class Directory : NObject {

public:
	Directory();
	virtual ~Directory();
	
	static Collection<Text *> GetFileSystemObjects(const Text &path, const Text &textInName, int FSOK_FileSystemObjectKind);
	static Collection<Text *> GetFiles(const Text &path);
	static Collection<Text *> GetFiles(const Text &path, const Text &textInName);
	static Collection<Text *> GetDirectories(const Text &path);
	static Collection<Text *> GetDirectories(const Text &path, const Text &textInName);
	static Collection<Text *> GetBlockDevices(const Text &path);
	static Collection<Text *> GetBlockDevices(const Text &path, const Text &textInName);
	static Collection<Text *> GetCharacterDevices(const Text &path);
	static Collection<Text *> GetCharacterDevices(const Text &path, const Text &textInName);
	static Collection<Text *> GetNamedPipes(const Text &path);
	static Collection<Text *> GetNamedPipes(const Text &path, const Text &textInName);
	static Collection<Text *> GetSymbolicLinks(const Text &path);
	static Collection<Text *> GetSymbolicLinks(const Text &path, const Text &textInName);
	static Collection<Text *> GetDomainSockets(const Text &path);
	static Collection<Text *> GetDomainSockets(const Text &path, const Text &textInName);
	static Collection<Text *> GetUnknownFileSystemObjects(const Text &path);
	static Collection<Text *> GetUnknownFileSystemObjects(const Text &path, const Text &textInName);
	static Collection<FileSystemObjectInfo *> GetFileSystemObjectList(const Text &path, const Text &textInName, int FSOK_FileSystemObjectKind);
	static Collection<FileSystemObjectInfo *> GetFileList(const Text &path);
	static Collection<FileSystemObjectInfo *> GetFileList(const Text &path, const Text &textInName);
	static Collection<FileSystemObjectInfo *> GetDirectoryList(const Text &path);
	static Collection<FileSystemObjectInfo *> GetDirectoryList(const Text &path, const Text &textInName);
	static Collection<FileSystemObjectInfo *> GetBlockDeviceList(const Text &path);
	static Collection<FileSystemObjectInfo *> GetBlockDeviceList(const Text &path, const Text &textInName);
	static Collection<FileSystemObjectInfo *> GetCharacterDeviceList(const Text &path);
	static Collection<FileSystemObjectInfo *> GetCharacterDeviceList(const Text &path, const Text &textInName);
	static Collection<FileSystemObjectInfo *> GetNamedPipeList(const Text &path);
	static Collection<FileSystemObjectInfo *> GetNamedPipeList(const Text &path, const Text &textInName);
	static Collection<FileSystemObjectInfo *> GetSymbolicLinkList(const Text &path);
	static Collection<FileSystemObjectInfo *> GetSymbolicLinkLink(const Text &path, const Text &textInName);
	static Collection<FileSystemObjectInfo *> GetDomainSocketLink(const Text &path);
	static Collection<FileSystemObjectInfo *> GetDomainSocketLink(const Text &path, const Text &textInName);
	static bool CheckFileSystemObject(const Text &t);
	static void CreateDirectory(const Text &t);
	static void DeleteDirectory(const Text &t);
	static void ChangeDirectory(const Text &t);
	static Text CurrentDirectory();
	static void Chmod(const Text &objectPath, mode_t mode);
	

};

#endif // DIRECTORY_H

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
   
   
#include "directory.h"
#include "filesystemexception.h"
#include "filesystemobjectinfo.h"
#include "../Text/text.h"
#include "../Collections/collection.h"
#include "../Devices/stdout.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

Directory::Directory()
{
}

Directory::~Directory()
{
}

Collection<Text *> Directory::GetFileSystemObjects(const Text &path, const Text &textInName, int FSOK_FileSystemObjectKind)
{
	char strPath[1001];
	Text p = &path;
	Text sp = &textInName;
	p.GetAnsiString(strPath, 1000);

	Collection<Text *> result;
	struct dirent *dent = NULL;
	
	DIR *d = opendir(strPath);
	while (dent = readdir(d)) {
		bool descartar = true;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_File) && dent->d_type == DT_REG) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_Directory) && dent->d_type == DT_DIR) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_BlockDevice) && dent->d_type == DT_BLK) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_CharacterDevice) && dent->d_type == DT_CHR) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_NamedPipe) && dent->d_type == DT_FIFO) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_SymbolicLink) && dent->d_type == DT_LNK) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_DomainSocket) && dent->d_type == DT_SOCK) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_UnknownFileSystemObject) && dent->d_type == DT_UNKNOWN) descartar = false;
		if (descartar) continue;
		if (sp.Length() != 0 && ((Text)dent->d_name).Contains(sp) == false) continue;
		result.Add(new Text(p + "/" + dent->d_name));
	}	
	
	return result;
}

Collection<Text *> Directory::GetFiles(const Text &path)
{
	return GetFileSystemObjects(path, "", FSOK_File);
}

Collection<Text *> Directory::GetFiles(const Text &path, const Text &textInName)
{
	return GetFileSystemObjects(path, textInName, FSOK_File);
}

Collection<Text *> Directory::GetDirectories(const Text &path)
{
	return GetFileSystemObjects(path, "", FSOK_Directory);
}

Collection<Text *> Directory::GetDirectories(const Text &path, const Text &textInName)
{
	return GetFileSystemObjects(path, textInName, FSOK_Directory);
}

Collection<Text *> Directory::GetBlockDevices(const Text &path)
{
	return GetFileSystemObjects(path, "", FSOK_BlockDevice);	
}

Collection<Text *> Directory::GetBlockDevices(const Text &path, const Text &textInName)
{
	return GetFileSystemObjects(path, textInName, FSOK_BlockDevice);	
}

Collection<Text *> Directory::GetCharacterDevices(const Text &path)
{
	return GetFileSystemObjects(path, "", FSOK_CharacterDevice);	
}

Collection<Text *> Directory::GetCharacterDevices(const Text &path, const Text &textInName)
{
	return GetFileSystemObjects(path, textInName, FSOK_CharacterDevice);	
}

Collection<Text *> Directory::GetNamedPipes(const Text &path)
{
	return GetFileSystemObjects(path, "", FSOK_NamedPipe);	
}

Collection<Text *> Directory::GetNamedPipes(const Text &path, const Text &textInName)
{
	return GetFileSystemObjects(path, textInName, FSOK_NamedPipe);	
}

Collection<Text *> Directory::GetSymbolicLinks(const Text &path)
{
	return GetFileSystemObjects(path, "", FSOK_SymbolicLink);	
}

Collection<Text *> Directory::GetSymbolicLinks(const Text &path, const Text &textInName)
{
	return GetFileSystemObjects(path, textInName, FSOK_SymbolicLink);
}

Collection<Text *> Directory::GetDomainSockets(const Text &path)
{
	return GetFileSystemObjects(path, "", FSOK_DomainSocket);	
}

Collection<Text *> Directory::GetDomainSockets(const Text &path, const Text &textInName)
{
	return GetFileSystemObjects(path, textInName, FSOK_DomainSocket);	
}

Collection<Text *> Directory::GetUnknownFileSystemObjects(const Text &path)
{
	return GetFileSystemObjects(path, "", FSOK_UnknownFileSystemObject);	
}

Collection<Text *> Directory::GetUnknownFileSystemObjects(const Text &path, const Text &textInName)
{
	return GetFileSystemObjects(path, textInName, FSOK_UnknownFileSystemObject);	
}

Collection<FileSystemObjectInfo *> Directory::GetFileSystemObjectList(const Text &path, const Text &textInName, int FSOK_FileSystemObjectKind)
{
	char strPath[1001];
	Text p = &path;
	Text sp = &textInName;
	p.GetAnsiString(strPath, 1000);

	Collection<FileSystemObjectInfo *> result;
	struct dirent *dent = NULL;
	
	DIR *d = opendir(strPath);
	while (dent = readdir(d)) {
		bool descartar = true;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_File) && dent->d_type == DT_REG) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_Directory) && dent->d_type == DT_DIR) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_BlockDevice) && dent->d_type == DT_BLK) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_CharacterDevice) && dent->d_type == DT_CHR) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_NamedPipe) && dent->d_type == DT_FIFO) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_SymbolicLink) && dent->d_type == DT_LNK) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_DomainSocket) && dent->d_type == DT_SOCK) descartar = false;
		if (descartar && (FSOK_FileSystemObjectKind & FSOK_UnknownFileSystemObject) && dent->d_type == DT_UNKNOWN) descartar = false;
		if (descartar) continue;
		if (sp.Length() != 0 && ((Text)dent->d_name).Contains(sp) == false) continue;
		
		try { result.Add(new FileSystemObjectInfo((Text)path + "/" + dent->d_name)); }
		catch (FileSystemException *e) { delete e; }
	}	
	
	return result;	
}

Collection<FileSystemObjectInfo *> Directory::GetFileList(const Text &path)
{
	return GetFileSystemObjectList(path, "", FSOK_File);
}

Collection<FileSystemObjectInfo *> Directory::GetFileList(const Text &path, const Text &textInName)
{
	return GetFileSystemObjectList(path, textInName, FSOK_File);
}

Collection<FileSystemObjectInfo *> Directory::GetDirectoryList(const Text &path)
{
	return GetFileSystemObjectList(path, "", FSOK_Directory);
}

Collection<FileSystemObjectInfo *> Directory::GetDirectoryList(const Text &path, const Text &textInName)
{
	return GetFileSystemObjectList(path, textInName, FSOK_Directory);
}

Collection<FileSystemObjectInfo *> Directory::GetBlockDeviceList(const Text &path)
{
	return GetFileSystemObjectList(path, "", FSOK_BlockDevice);
}

Collection<FileSystemObjectInfo *> Directory::GetBlockDeviceList(const Text &path, const Text &textInName)
{
	return GetFileSystemObjectList(path, textInName, FSOK_BlockDevice);
}

Collection<FileSystemObjectInfo *> Directory::GetCharacterDeviceList(const Text &path)
{
	return GetFileSystemObjectList(path, "", FSOK_CharacterDevice);
}

Collection<FileSystemObjectInfo *> Directory::GetCharacterDeviceList(const Text &path, const Text &textInName)
{
	return GetFileSystemObjectList(path, textInName, FSOK_CharacterDevice);
}

Collection<FileSystemObjectInfo *> Directory::GetNamedPipeList(const Text &path)
{
	return GetFileSystemObjectList(path, "", FSOK_NamedPipe);
}

Collection<FileSystemObjectInfo *> Directory::GetNamedPipeList(const Text &path, const Text &textInName)
{
	return GetFileSystemObjectList(path, textInName, FSOK_NamedPipe);
}

Collection<FileSystemObjectInfo *> Directory::GetSymbolicLinkList(const Text &path)
{
	return GetFileSystemObjectList(path, "", FSOK_SymbolicLink);
}

Collection<FileSystemObjectInfo *> Directory::GetSymbolicLinkLink(const Text &path, const Text &textInName)
{
	return GetFileSystemObjectList(path, textInName, FSOK_SymbolicLink);
}

Collection<FileSystemObjectInfo *> Directory::GetDomainSocketLink(const Text &path)
{
	return GetFileSystemObjectList(path, "", FSOK_DomainSocket);
}

Collection<FileSystemObjectInfo *> Directory::GetDomainSocketLink(const Text &path, const Text &textInName)
{
	return GetFileSystemObjectList(path, textInName, FSOK_DomainSocket);
}

bool Directory::CheckFileSystemObject(const Text &t)
{
	struct stat s;
	char cadena[10001];
	((Text *)&t)->GetAnsiString(cadena, 10000);
	
	int res = stat(cadena, &s);
	return res == 0;
}

void Directory::CreateDirectory(const Text &t)
{
	char cadena[10001];	
	Text pathToCheck;	
	Text path = !((Text *)&t)->StartsWith("/") ? CurrentDirectory() + "/" + t : t;
	Collection<Text *> folders = path.Split((Text)"/", false);
	int result = 0;
	
	for (int i=1; i<folders.Count(); i++) {
		if (folders[i]->Length() == 0) continue;
		pathToCheck += (Text)"/" + folders[i];
		if (CheckFileSystemObject(pathToCheck)) continue;
		
		pathToCheck.GetAnsiString(cadena, 10000);
		result = mkdir(cadena, 0700);
		if (result) break;
	}
	folders.DeleteAndClear();
	
	if (result) throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void Directory::DeleteDirectory(const Text &t)
{
	char cadena[10001];
	
	((Text)t).GetAnsiString(cadena, 10000);
	if (rmdir(cadena)) throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void Directory::ChangeDirectory(const Text &t)
{
	char cadena[10001];
	
	((Text)t).GetAnsiString(cadena, 10000);
	if (chdir(cadena)) throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

Text Directory::CurrentDirectory()
{
	char *dn = get_current_dir_name();
	Text t = dn;
	delete dn;
	return t;
}

void Directory::Chmod(const Text &objectPath, mode_t mode)
{
	char cadena[10001];
	((Text *)&objectPath)->GetAnsiString(cadena, 10000);
	if (chmod(cadena, mode) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

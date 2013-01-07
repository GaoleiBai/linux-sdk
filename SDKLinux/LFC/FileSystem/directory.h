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

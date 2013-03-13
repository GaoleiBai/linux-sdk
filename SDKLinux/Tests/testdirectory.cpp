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
#include "testdirectory.h"
#include "../LFC/LFC.h"
#include <stdio.h>

TestDirectory::TestDirectory()
{
}

TestDirectory::~TestDirectory()
{
}

int TestDirectory::Perform()
{
	Collection<Text *> files = Directory::GetFiles(".");
	for (int i=0; i<files.Count(); i++)
		StdOut::PrintLine(files[i]);
	StdOut::PrintLine();
	
	Collection<Text *> directories = Directory::GetDirectories("..");
	for (int i=0; i<directories.Count(); i++)
		StdOut::PrintLine(directories[i]);
	StdOut::PrintLine();
	
	Collection<Text *> blockDevices = Directory::GetBlockDevices("/dev");
	for (int i=0; i<blockDevices.Count(); i++) 
		StdOut::PrintLine(blockDevices[i]);
	StdOut::PrintLine();
	
	Collection<Text *> characterDevices = Directory::GetCharacterDevices("/dev");
	for (int i=0; i<characterDevices.Count(); i++)
		StdOut::PrintLine(characterDevices[i]);
	StdOut::PrintLine();
		
	Collection<FileSystemObjectInfo *> fileList = Directory::GetFileList(".");
	Collection<FileSystemObjectInfo *> directoryList = Directory::GetDirectoryList("..");
	Collection<FileSystemObjectInfo *> blockDevicesList = Directory::GetBlockDeviceList("/dev");
	Collection<FileSystemObjectInfo *> characterDevicesList = Directory::GetCharacterDeviceList("/dev");
	
	if (files.Count() != fileList.Count()) {
		StdOut::PrintLine("GetFiles & GetFileList don't match");
		return -1;
	}
	for (int i=0; i<files.Count(); i++)
	{
		StdOut::PrintLine(fileList[i]->ToText());
		if (*files[i] == fileList[i]->Name()) continue;
		StdOut::PrintLine("GetFiles & GetFileList don't match");
		return -1;
	}
	
	if (directories.Count() != directoryList.Count()) {
		StdOut::PrintLine("GetDirectories and GetDirectoryList don't match");
		return -1;
	}
	for (int i=0; i<directories.Count(); i++)
	{
		StdOut::PrintLine(directoryList[i]->ToText());
		if (*directories[i] == directoryList[i]->Name()) continue;
		StdOut::PrintLine("GetDirectories and GetDirectoryList don't match");
		return -1;
	}
	
	if (blockDevices.Count() != blockDevicesList.Count()) {
		StdOut::PrintLine("GetBlockDevices and GetBlockDeviceList don't match");
		return -1;
	}
	for (int i=0; i<blockDevices.Count(); i++)
	{
		StdOut::PrintLine(blockDevicesList[i]->ToText());
		if (*blockDevices[i] == blockDevicesList[i]->Name()) continue;
		StdOut::PrintLine("GetBlockDevices and GetBlockDeviceList don't match");
		return -1;
	}
	
	if (characterDevices.Count() != characterDevicesList.Count())
	{
		StdOut::PrintLine("GetCharacterDevices and GetCharacteDevicesList don't match");
		return -1;
	}
	for (int i=0; i<characterDevices.Count(); i++)
	{
		StdOut::PrintLine(characterDevicesList[i]->ToText());
		if (*characterDevices[i] == characterDevicesList[i]->Name()) continue;
		StdOut::PrintLine("GetCharacterDevices and GetCharacteDevicesList don't match");
		return -1;
	}
	
	files.DeleteAndClear();
	directories.DeleteAndClear();
	blockDevices.DeleteAndClear();
	characterDevices.DeleteAndClear();
	
	fileList.DeleteAndClear();
	directoryList.DeleteAndClear();
	blockDevicesList.DeleteAndClear();
	characterDevicesList.DeleteAndClear();

	Directory::CreateDirectory("test/test1/testñ");
	if (!Directory::CheckFileSystemObject("test") ||
		!Directory::CheckFileSystemObject("test/test1") || 
		!Directory::CheckFileSystemObject("test/test1/testñ")) 
	{
		StdOut::PrintLine("CreateDirectory didn't work");
		return -1;
	}
	
	
	return 0;
}




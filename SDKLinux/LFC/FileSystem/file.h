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
   
   
#ifndef FILE_H
#define FILE_H

#include "filesystem.h"
#include "ifile.h"
#include "buffer.h"
#include "../Text/text.h"
#include "../Collections/collection.h"
#include <sys/types.h>
#include <sys/stat.h>

class File : public IFile {

public:
	File(const Text &filename, int mode);
	virtual ~File();
	
	Text FileName();
	virtual Text ToText();
	
	void Open();
	void Close();
	void Flush();
	virtual off_t FSetStart();
	virtual off_t FSetEnd();
	virtual off_t FSet(int position);
	virtual off_t FGet();
	
	static Text ReadAllText(const Text &filename);
	static Collection<Text *> ReadAllLines(const Text &filename);
	static void WriteAllText(const Text &filename, const Text &contents);
	static void WriteAllLines(const Text &filename, const Collection<Text *> &lines);
	
	static Buffer ReadAllBytes(const Text &filename);
	static void WriteAllBytes(const Text &filename, const Buffer &buffer);
	
	static mode_t Umask(mode_t mode);
	static bool Exists(const Text &filename);
	static void Copy(const Text &from, const Text &to);
	static void Move(const Text &from, const Text &to);
	static void Delete(const Text &filename);
	static void Link(const Text &from, const Text &to);
	static void Symlink(const Text &from, const Text &to);
	static void Chmod(const Text &filename, mode_t mode);
	
private:
	Text *fileName;
	int mode;

};

#endif // FILE_H

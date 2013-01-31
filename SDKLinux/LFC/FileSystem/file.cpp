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
   
   
#include "file.h"
#include "filesystemobjectinfo.h"
#include "filesystemexception.h"
#include "buffer.h"
#include "directory.h"
#include "../Text/text_exception.h"
#include "../Text/text_buffer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

File::File(const Text &filename, int mode)
{
	this->fileName = new Text(filename);
	this->mode = mode;
}

File::~File()
{
	Close();
	delete fileName;
}

Text File::FileName()
{
	return *fileName;
}

Text File::ToText()
{
	return *fileName;
}

void File::Open()
{
	char cadena[1001];
	
	fileName->GetAnsiString(cadena, 1000);
	file = open(cadena, mode, S_IRUSR | S_IWUSR );
	if (file == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);	
}

void File::Close()
{
	if (file != -1) 
		if (close(file) == -1)
			throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	file = -1;
}

void File::Flush()
{
	if (file == -1) throw new FileSystemException("File not propertly open", __FILE__, __LINE__, __func__);

	if (fsync(file) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

off_t File::FSetStart()
{
	if (file == -1) throw new FileSystemException("File not propertly open", __FILE__, __LINE__, __func__);

	if (lseek(file, SEEK_SET, 0) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

off_t File::FSetEnd()
{
	if (file == -1) throw new FileSystemException("File not propertly open", __FILE__, __LINE__, __func__);

	if (lseek(file, SEEK_END, 0) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

off_t File::FSet(int position)
{
	if (file == -1) throw new FileSystemException("File not propertly open", __FILE__, __LINE__, __func__);

	if (lseek(file, SEEK_SET, position) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

off_t File::FGet()
{
	if (file == -1) throw new FileSystemException("File not propertly open", __FILE__, __LINE__, __func__);

	off_t pos = lseek(file, SEEK_CUR, 0);
	if (pos == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return pos;
}

int File::Read(char *buffer, int lonBuffer)
{
	if (file == -1) throw new FileSystemException("File not propertly open", __FILE__, __LINE__, __func__);

	ssize_t leido = read(file, buffer, lonBuffer);
	if (leido == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return leido;
}

int File::Write(const char *buffer, int lonBuffer)
{
	if (file == -1) throw new FileSystemException("File not propertly open", __FILE__, __LINE__, __func__);

	ssize_t escrito = 0;
	while (escrito < lonBuffer) {
		ssize_t sss = write(file, buffer + escrito, lonBuffer - escrito);
		if (sss == -1)
			throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
		escrito += sss;
	}
	
	return escrito;
}

Text File::ReadAllText(const Text &filename)
{
	FileSystemObjectInfo fsoi(filename);
	char buffer[10000];
	Buffer b;

	File f(filename, FO_ReadOnly);
	f.Open();
	for (int leido = 0; leido < fsoi.Size(); ) {
		int res = f.Read(buffer, 10000);
		if (!res) continue;
		b.Write(buffer, res);
		leido += res;
	}
	f.Close();
	
	return b.ToText();
}

Collection<Text *> File::ReadAllLines(const Text &filename)
{
	Collection<char> rtrim = "\r";
	Collection<Text *> lines = ReadAllText(filename).Split("\n", false);
	for (int i=0; i<lines.Count(); i++) {
		Text *t = new Text(lines[i]->Trim(rtrim));
		delete lines[i];
		lines[i] = t;
	}
	return lines;
}

void File::WriteAllText(const Text &filename, const Text &contents)
{
	Text *cc = (Text *)&contents;
	
	try {
		File f(filename, FO_Create | FO_Truncate | FO_WriteOnly );
		f.Open();

		char converted[10000];
		Text t;
		for (int i=0; i<cc->Length(); i+=1000) {
			t = i + 1000 > cc->Length() ? cc->SubText(i) : cc->SubText(i, 1000);
			t.GetAnsiString(converted, 10000);
			f.Write(converted, strlen(converted));
		}
	} catch (FileSystemException *e) {
		throw e;
	} catch (TextException *e) {
		FileSystemException *ee = new FileSystemException(*e);
		delete e;
		throw ee;
	}
}

void File::WriteAllLines(const Text &filename, const Collection<Text *> &lines)
{
	Collection<Text *> *ll = (Collection<Text *> *)&lines;
	Text t;
	File f(filename, FO_Create | FO_Truncate | FO_WriteOnly );
	f.Open();
	
	char converted[10000];
	for (int i=0; i<ll->Count(); i++) {
		Text *s = (*ll)[i];
		for (int j=0; j<s->Length(); j+=1000) {
			t = s->Length() - j > 1000 ? s->SubText(j, 1000) : s->SubText(s->Length() - j);
			t.GetAnsiString(converted, 10000);
			f.Write(converted, strlen(converted));
		}
		f.Write((char *)"\n", 1);
	}
	
	f.Flush();
	f.Close();
}

Buffer File::ReadAllBytes(const Text &filename)
{
	char buffer[100000];
	Buffer b;
	
	File f(filename, FO_ReadOnly);
	f.Open();
	int leido = f.Read(buffer, 100000);
	while (leido) {
		b.Write(buffer, leido);
		leido = f.Read(buffer, 100000);
	}
	
	return b;
}

void File::WriteAllBytes(const Text &filename, const Buffer &buffer)
{
	char baux[100000];
	File f(filename, FO_Create | FO_Truncate | FO_WriteOnly );
	f.Open();
	
	((Buffer *)&buffer)->FSetStart();
	int leido = ((Buffer *)&buffer)->Read(baux, 100000);
	while (leido) {
		f.Write(baux, leido);
		leido = ((Buffer *)&buffer)->Read(baux, 100000);
	}
}

mode_t File::Umask(mode_t mode)
{
	return umask(mode);
}

bool File::Exists(const Text &filename)
{
	return Directory::CheckFileSystemObject(filename);
}

void File::Copy(const Text &from, const Text &to)
{
	char buffer[100000];
	File ffrom(from, FO_ReadOnly);
	File fto(to, FO_WriteOnly | FO_Create | FO_Truncate );
	
	ffrom.Open();
	fto.Open();
	
	int leido = ffrom.Read(buffer, 100000);
	while (leido > 0) {
		fto.Write(buffer, leido);
		leido = ffrom.Read(buffer, 100000);
	} 
}

void File::Move(const Text &from, const Text &to)
{
	char strFrom[10001];
	char strTo[10001];
	
	((Text *)&from)->GetAnsiString(strFrom, 10000);
	((Text *)&to)->GetAnsiString(strTo, 10000);
	
	if (rename(strFrom, strTo) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void File::Delete(const Text &filename)
{
	char cadena[10001];
	((Text *)&filename)->GetAnsiString(cadena, 10000);
	if (unlink(cadena) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void File::Link(const Text &from, const Text &to)
{
	char strFrom[10001];
	char strTo[10001];
	
	((Text *)&from)->GetAnsiString(strFrom, 10000);
	((Text *)&to)->GetAnsiString(strTo, 10000);
	
	if (link(strFrom, strTo) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void File::Symlink(const Text &from, const Text &to)
{
	char strFrom[10001];
	char strTo[10001];
	
	((Text *)&from)->GetAnsiString(strFrom, 10000);
	((Text *)&to)->GetAnsiString(strTo, 10000);
	
	if (symlink(strFrom, strTo) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void File::Chmod(const Text &filename, mode_t mode)
{
	char cadena[10001];
	((Text *)&filename)->GetAnsiString(cadena, 10000);
	if (chmod(cadena, mode) == -1)
		throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);	
}
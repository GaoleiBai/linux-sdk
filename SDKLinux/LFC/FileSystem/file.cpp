#include "file.h"
#include "filesystemobjectinfo.h"
#include "filesystemexception.h"
#include "buffer.h"
#include "../Text/text_exception.h"
#include "../Text/text_buffer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

File::File(const Text &filename, int mode)
{
	this->fileName = new Text(filename);
	this->mode = mode;
	this->creationFlags = 0;
}

File::File(const Text &filename, int mode, int creationFlags)
{
	this->fileName = new Text(filename);
	this->mode = mode;
	this->creationFlags = creationFlags;
}

File::~File()
{
	Close();
	delete fileName;
}

void File::Open()
{
	char cadena[1001];
	
	fileName->GetAnsiString(cadena, 1000);
	file = open(cadena, mode, creationFlags);
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

void File::Write(char *buffer, int lonBuffer)
{
	if (file == -1) throw new FileSystemException("File not propertly open", __FILE__, __LINE__, __func__);

	ssize_t escrito = 0;
	while (escrito < lonBuffer) {
		ssize_t sss = write(file, buffer + escrito, lonBuffer - escrito);
		if (sss == -1)
			throw new FileSystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
		escrito += sss;
	}
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
	Collection<Text *> lines = ReadAllText(filename).Split((Collection<char>)"\n", false);
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
		File f(filename, FO_Create | FO_Truncate | FO_WriteOnly, USER_READ | USER_WRITE | GROUP_READ | OTHERS_READ );
		f.Open();

		char converted[10000];
		Text t;
		for (int i=0; i<cc->Length(); i+=1000) {
			t = i + 1000 > cc->Length() ? cc->SubText(i) : cc->SubText(i, 1000);
			t.GetAnsiString(converted, 10000);
			f.Write(converted, strlen(converted));
		}
		f.Flush();
		f.Close();
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
	File f(filename, FO_Create | FO_Truncate | FO_WriteOnly, USER_READ | USER_WRITE | GROUP_READ | OTHERS_READ );
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
#ifndef FILE_H
#define FILE_H

#include "filesystem.h"
#include "ifile.h"
#include "buffer.h"
#include "../Text/text.h"
#include "../Collections/collection.h"
#include <sys/types.h>
#include <sys/stat.h>

class File : public NObject, IFile {

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
	virtual int Read(char *buffer, int lonBuffer);
	virtual void Write(char *buffer, int lonBuffer);
	
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
	int file;
	Text *fileName;
	int mode;

};

#endif // FILE_H

#ifndef FILE_H
#define FILE_H

#include "filesystem.h"
#include "ifile.h"
#include "buffer.h"
#include "../Text/text.h"
#include "../Collections/collection.h"


#define FO_Append O_APPEND
#define FO_Create O_CREAT
#define FO_Truncate O_TRUNC
#define FO_ReadWrite O_RDWR
#define FO_WriteOnly O_WRONLY
#define FO_ReadOnly O_RDONLY

class File : public NObject, IFile {

public:
	File(const Text &filename, int mode);
	File(const Text &filename, int mode, int creationFlags);
	virtual ~File();
	
	Text FileName();
	
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
	
	static void Copy(const Text &from, const Text &to);
	static void Move(const Text &from, const Text &to);
	static void Delete(const Text &filename);
	static void Link(const Text &from, const Text &to);
	static void Symlink(const Text &from, const Text &to);
	
private:
	int file;
	Text *fileName;
	int mode;
	int creationFlags;

};

#endif // FILE_H

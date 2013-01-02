#ifndef IFILE_H
#define IFILE_H

#include <sys/types.h>

class Text;

class IFile {

public:
	IFile();
	virtual ~IFile();

	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void Flush() = 0;
	virtual off_t FSetStart() = 0;
	virtual off_t FSetEnd() = 0;
	virtual off_t FSet(int position) = 0;
	virtual off_t FGet() = 0;
	virtual int Read(char *buffer, int lonBuffer) = 0;
	virtual void Write(char *buffer, int lonBuffer) = 0;
	
};

#endif // IFILE_H

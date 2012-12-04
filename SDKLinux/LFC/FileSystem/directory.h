#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "../Collections/collection.h"

class Text;

class Directory {

public:
	Directory();
	virtual ~Directory();
	
	static Collection<Text *> GetFiles(const Text &path);
	static Collection<Text *> GetFiles(const char *path);
	static Collection<Text *> GetFiles(const wchar_t *path);
	static Collection<Text *> GetFiles(const Text &path, Text &searchPattern);
	static Collection<Text *> GetFiles(const char *path, const char *searchPattern);
	static Collection<Text *> GetFiles(const wchar_t *path, const wchar_t *searchPattern);
	static Collection<Text *> GetDirectories(const Text &path);
	static Collection<Text *> GetDirectories(const char *path);
	static Collection<Text *> GetDirectories(const wchar_t *path);
	static Collection<Text *> GetDirectories(const Text &path, const Text &searchPattern);
	static Collection<Text *> GetDirectories(const char *path, const char *searchPattern);
	static Collection<Text *> GetDirectories(const wchar_t *path, const wchar_t *searchPattern);

private:
	
	static void GetFiles(const char *path, const char *searchPattern, Collection<Text *> &result);

};

#endif // DIRECTORY_H

#include "directory.h"
#include "../Text/text.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

Directory::Directory()
{
}

Directory::~Directory()
{
}

Collection<Text *> Directory::GetFiles(const char *path)
{
	return Directory::GetFiles(path, NULL);
}

Collection<Text *> Directory::GetFiles(const char *path, const char *searchPattern)
{
	Collection<Text *> result;
	struct dirent *dent = NULL;
	
	DIR *d = opendir(path);
	while (dent = readdir(d)) {
		if (dent->d_type != DT_REG) continue;
		if (searchPattern && strstr(dent->d_name, searchPattern) == NULL) continue;
		result.Add(new Text(dent->d_name));
	}	
	
	return result;
}

Collection<Text *> Directory::GetFiles(const wchar_t *path)
{
	return GetFiles(path, NULL);
}

Collection<Text *> Directory::GetFiles(const wchar_t *path, const wchar_t *searchPattern)
{
	char strPath[1001];
	char strSearchPattern[1001];
	wcstombs(strPath, path, 1000);
	wcstombs(strSearchPattern, searchPattern, 1000);
	return GetFiles(strPath, strSearchPattern);
}

Collection<Text *> Directory::GetFiles(const Text &path)
{
	return GetFiles(path.p, NULL);
}

Collection<Text *> Directory::GetFiles(const Text &path, const Text &searchPattern)
{
	return GetFiles(path.p, searchPattern.p);
}

Collection<Text *> Directory::GetDirectories(const char *path)
{
	return Directory::GetDirectories(path, NULL);
}

Collection<Text *> Directory::GetDirectories(const char *path, const char *searchPattern)
{
	Collection<Text *> result;
	struct dirent *dent = NULL;
	
	DIR *d = opendir(path);
	while (dent = readdir(d)) {
		if (dent->d_type != DT_DIR) continue;
		if (searchPattern && strstr(dent->d_name, searchPattern) == NULL) continue;
		result.Add(new Text(dent->d_name));
	}	
	
	return result;
}

Collection<Text *> Directory::GetDirectories(const wchar_t *path)
{
	return GetDirectories(path, NULL);
}

Collection<Text *> Directory::GetDirectories(const wchar_t *path, const wchar_t *searchPattern)
{
	char strPath[1001];
	char strSearchPattern[1001];
	wcstombs(strPath, path, 1000);
	wcstombs(strSearchPattern, searchPattern, 1000);
	return GetDirectories(strPath, strSearchPattern);
}

Collection<Text *> Directory::GetDirectories(const Text &path)
{
	return GetDirectories(path.p, NULL);
}

Collection<Text *> Directory::GetDirectories(const Text &path, const Text &searchPattern)
{
	return GetDirectories(path.p, searchPattern.p);
}

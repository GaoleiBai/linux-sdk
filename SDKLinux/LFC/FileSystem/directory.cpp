#include "directory.h"
#include "../Text/text.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

Directory::Directory()
{
}

Directory::~Directory()
{
}

void Directory::GetFiles(const char *path, const char *searchPattern, Collection<Text *> &result)
{
	struct dirent *dent = NULL;
	
	DIR *d = opendir(path);
	while (dent = readdir(d)) {
		if (dent->d_type == DT_REG) continue;
		if (searchPattern && strstr(dent->d_name, searchPattern) == NULL) continue;
		result.Add(new Text(dent->d_name));
	}	
}

Collection<Text *> Directory::GetFiles(const char *path)
{
	Collection<Text *> result;
	Directory::GetFiles(path, NULL, result);
	return result;
}

Collection<Text *> Directory::GetFiles(const char *path, const char *searchPattern)
{
	Collection<Text *> result;
	Directory::GetFiles(path, searchPattern, result);
	return result;
}


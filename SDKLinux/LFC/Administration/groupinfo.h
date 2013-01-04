#ifndef GROUPINFO_H
#define GROUPINFO_H

#include "../Collections/collection.h"

class Text;

class GroupInfo : public NObject {

public:
	GroupInfo(int groupID);
	GroupInfo(const Text &name, int groupID, const Collection<Text *> &users);
	GroupInfo(const Text &groupName);
	virtual ~GroupInfo();
	
	Text Name();
	int GroupID();
	Collection<Text *> Users();
	
	virtual Text ToText();

private:
	Text *name;
	int groupID;
	Collection<Text *> *users;

};

#endif // GROUPINFO_H

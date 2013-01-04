#ifndef USERINFO_H
#define USERINFO_H

#include "../n_object.h"

class Text;

class UserInfo : public NObject {

public:
	UserInfo(int userID);
	UserInfo(const Text &name, int userID, int groupID, const Text &initialDirectory, const Text &defaultShell);
	UserInfo(const Text &userName);
	virtual ~UserInfo();
	
	Text Name();
	int UserID();
	int GroupID();
	Text InitialDirectory();
	Text DefaultShell();
	
	Text ToText();

private:
	Text *name;
	int userID;
	int groupID;
	Text *dir;
	Text *shell;
	
};

#endif // USERINFO_H

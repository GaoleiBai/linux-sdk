#ifndef EXCEPTION_H
#define EXCEPTION_H

class Text;

class Exception {

public:
	Exception();
	Exception(const char *t);
	Exception(const Text &t);
	virtual ~Exception();

protected:
	Text *t;
	
};

#endif // EXCEPTION_H

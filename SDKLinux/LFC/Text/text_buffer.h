#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include "../n_object.h"

class Text;

class TextBuffer : NObject {

public:
	TextBuffer();
	TextBuffer(int size);
	TextBuffer(Text &t);
	TextBuffer(const char *c);
	TextBuffer(const wchar_t *c);
	virtual ~TextBuffer();
	
	void Append(const Text &t);
	void AppendLine(const Text &t);
	void AppendLine();
	
	Text ToText();
	
private:
	void increaseBuffer(int newLen);

	wchar_t *p;
	int length;
	int psize;

};

#endif // TEXTBUFFER_H

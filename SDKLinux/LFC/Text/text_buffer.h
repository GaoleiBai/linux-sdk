#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include "../n_object.h"

class Text;

class TextBuffer : public NObject {

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
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual void Serialize(const Serializator &s);
	virtual NObject *Deserialize(const Serializator &s);
	
private:
	void increaseBuffer(int newLen);

	wchar_t *p;
	int length;
	int psize;

};

#endif // TEXTBUFFER_H

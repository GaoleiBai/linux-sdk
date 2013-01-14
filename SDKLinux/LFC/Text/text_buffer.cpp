#include "text_buffer.h"
#include "text_exception.h"
#include "text.h"
#include "../FileSystem/serializator.h"
#include <string.h>
#include <wchar.h>

TextBuffer::TextBuffer()
{
	p = new wchar_t[10000];
	psize = 1000;
	length = 0;
}

TextBuffer::TextBuffer(int size)
{
	if (size <= 0) throw new TextException("Size cannot be smaller than one", __FILE__, __LINE__, __func__);
	p = new wchar_t[size];
	psize = size;
	length = 0;
}

TextBuffer::TextBuffer(Text &t)
{
	length = t.Length();
	psize = length + 10000;
	p = new wchar_t[psize];
	Text::write(0, p, psize, 0, t.p, t.length);
}

TextBuffer::TextBuffer(const char *t)
{
	length = strlen(t);
	psize = length + 10000;
	p = new wchar_t[psize];
	Text::write(0, p, psize, 0, t, length);
}

TextBuffer::TextBuffer(const wchar_t *t)
{
	length = wcslen(t);
	psize = length + 10000;
	p = new wchar_t[psize];
	Text::write(0, p, psize, 0, t, length);
}

TextBuffer::~TextBuffer()
{
	delete p;
}

void TextBuffer::increaseBuffer(int newLen)
{
	if (newLen >= psize) {
		int qsize = 2 * psize + newLen;
		wchar_t *q = new wchar_t[qsize];
		Text::write(0, q, qsize, 0, p, length); 
		delete p;
		p = q;
		psize = qsize;
	}
}

void TextBuffer::Append(const Text &t)
{
	Text tt = &t;
	increaseBuffer(length + tt.Length());
	
	int len = psize - length - 1;
	tt.GetWideString(p + length, len);
	length += tt.Length();
}

void TextBuffer::AppendLine(const Text &t)
{
	Append(t);
	Append("\n");
}

void TextBuffer::AppendLine()
{
	Append("\n");
}

NObject *TextBuffer::NewInstance()
{
	return new TextBuffer();
}

Text TextBuffer::ToText()
{
	return Text(p, length);
}

void TextBuffer::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(length);
	((Serializator *)&s)->Put((char *)p, sizeof(wchar_t) * length);
}

NObject *TextBuffer::Deserialize(const Serializator &s)
{
	length = ((Serializator *)&s)->GetInt();
	psize = length + 1;
	delete p;
	p = new wchar_t[psize];
	((Serializator *)&s)->Get((char *)p, sizeof(wchar_t) * length);
	p[length] = 0;
}

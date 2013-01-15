/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva
   This file is part of LFC Library.

   LFC Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   LFC Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with LFC Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA. or see http://www.gnu.org/licenses/. */
   
   
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

void TextBuffer::Deserialize(const Serializator &s)
{
	length = ((Serializator *)&s)->GetInt();
	psize = length + 1;
	delete p;
	p = new wchar_t[psize];
	((Serializator *)&s)->Get((char *)p, sizeof(wchar_t) * length);
	p[length] = 0;
}
